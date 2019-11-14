#include "header.h"
#include "typeget.c"
int check_error(SOCKET s){
	int flag;
	if(s >= 0) flag = 1;
	else flag = 0;
	return flag;
}
void error_printer(int flag){
	if(flag == 1) fprintf(stderr, "socket failed. (%d)\n", errno);
	if(flag == 2) fprintf(stderr, "bind failed. (%d)\n", errno);
	if(flag == 3) fprintf(stderr, "listen failed. (%d)\n", errno);
	if(flag == 4) fprintf(stderr, "Out of memory.\n");
	if(flag == 5) fprintf(stderr, "drop_client not found.\n");
	if(flag == 6) fprintf(stderr, "select() failed. (%d)\n", errno);
	if(flag == 7) fprintf(stderr, "accept() failed. (%d)\n",errno);
	if(flag == 8) fprintf(stderr, "400 bad request.\n");
	if(flag == 9) fprintf(stderr, "404 no found.\n");
}
//建立socket
SOCKET create_socket(const char* host, const char *port) {

    struct addrinfo info;
    struct addrinfo *bind_addr;//結果指向

    memset(&info, 0, sizeof(info));//struct清空
    info.ai_family = AF_INET;//IPv4
    info.ai_socktype = SOCK_STREAM;//tcp stream socket
    info.ai_flags = AI_PASSIVE;//ip位置

    getaddrinfo(host, port, &info, &bind_addr);

    SOCKET socket_listen = socket(bind_addr->ai_family, bind_addr->ai_socktype, bind_addr->ai_protocol);
    if (!check_error(socket_listen)) {//socket建立失敗
	error_printer(1);
        exit(1);
    }

    if (bind(socket_listen, bind_addr->ai_addr, bind_addr->ai_addrlen) ) {//綁定地址失敗
	error_printer(2);
        exit(1);
    }

    freeaddrinfo(bind_addr);//free bind addr
    if (listen(socket_listen, 5) < 0) {//人數大於五人
	error_printer(3);
        exit(1);
    }

    return socket_listen;
}

//建立client的struct
struct CLIENT {
    socklen_t addr_len;
    struct sockaddr_storage addr;
    SOCKET socket;
    char request[MAXSIZE+1];
    int received;
    struct CLIENT *next;
};

static struct CLIENT *clients = 0;

struct CLIENT *get_client(SOCKET s){
    struct CLIENT *cinfo = clients;

    while(cinfo) {
        if (cinfo->socket == s)
            break;
        cinfo = cinfo->next;
    }

    if (cinfo) return cinfo;//原來的client
    struct CLIENT *another =(struct CLIENT*)calloc(1, sizeof(struct CLIENT));//配置記憶體空間並全歸零

    if (!another) {
	error_printer(4);
        exit(1);
    }

    another->addr_len = sizeof(another->addr);
    another->next = clients;
    clients = another;
    return another;//新的client
}


void drop_client(struct CLIENT *client) {
    close(client->socket);

    struct CLIENT **temp = &clients;

    while(*temp) {
        if (*temp == client) {
            *temp = client->next;
            free(client);
            return;
        }
        temp = &(*temp)->next;
    }

    error_printer(5);
    exit(1);//drop not found
}


const char *get_client_address(struct CLIENT *ip) {
    static char buffer[100];
    getnameinfo((struct sockaddr*)&ip->addr,ip->addr_len,buffer, sizeof(buffer), 0, 0,NI_NUMERICHOST);
    return buffer;
}

fd_set wait_clients(SOCKET server) {
    fd_set reads;
    FD_ZERO(&reads);//將 reads 清空
    FD_SET(server, &reads);//把server加入reads中
    SOCKET max_socket = server;

    struct CLIENT *temp = clients;

    while(temp) {
        FD_SET(temp->socket, &reads);
        if (temp->socket > max_socket)
            max_socket = temp->socket;
        temp = temp->next;
    }

    if (select(max_socket+1, &reads, 0, 0, 0) < 0) {//select fail
	error_printer(6);
        exit(1);
    }

    return reads;
}

void getresource(struct CLIENT *client, const char *path) {

    printf("serve resource %s %s\n", get_client_address(client), path);

    if (strcmp(path, "/") == 0) path = "/index.html";

    if (strlen(path) > 100) {
	error_printer(8);
        return;
    }

    if (strstr(path, "..")) {
	error_printer(9);
        return;
    }


    char full_path[128];
    sprintf(full_path, "myhttp%s", path);

    FILE *fp = fopen(full_path, "rb");

    if (!fp) {
	error_printer(9);
        return;
    }

    fseek(fp, 0L, SEEK_END);
    size_t cl = ftell(fp);
    rewind(fp);

    const char *ct = get_content_type(full_path);

    char buffer[2048];

    sprintf(buffer, "HTTP/1.1 200 OK\r\n");
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "Connection: close\r\n");
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "Content-Length: %lu\r\n", cl);
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "Content-Type: %s\r\n", ct);
    send(client->socket, buffer, strlen(buffer), 0);

    sprintf(buffer, "\r\n");
    send(client->socket, buffer, strlen(buffer), 0);

    int r = fread(buffer, 1, 2048, fp);
    while (r) {
        send(client->socket, buffer, r, 0);
        r = fread(buffer, 1, 2048, fp);
    }

    fclose(fp);
    drop_client(client);
}


int main() {
    int rcall, req;
    SOCKET server = create_socket(0, "8764");//127.0.0.1:8764

    while(1) {

        fd_set reads;
        reads = wait_clients(server);

        if (FD_ISSET(server, &reads)) {
            struct CLIENT *client = get_client(-1);

            client->socket = accept(server,(struct sockaddr*)&(client->addr),&(client->addr_len));

            if (!check_error(client->socket)) {
		error_printer(7);
                return 1;
            }


            printf("%s 連線......\n",get_client_address(client));
        }


        struct CLIENT *client = clients;

        while(client) {
            struct CLIENT *next = client->next;

            if (FD_ISSET(client->socket, &reads)) {

                if (MAXSIZE == client->received) {
		    error_printer(8);
                    drop_client(client);
                    continue;
                }
                rcall = recv(client->socket,client->request + client->received,MAXSIZE - client->received, 0);

                if (rcall < 1) {
                    printf("%s 未預期斷線......\n",get_client_address(client));
                    drop_client(client);
		}
		else {
                    client->received += rcall;
                    client->request[client->received] = 0;

			char *pointer=strstr(client->request,"image/png");
			int i=0;
			if(pointer){
			FILE *fp;
				fp = fopen("./target.png","wb");
				pointer=pointer+8;
				pointer=pointer+5;
				
				for(i=0;i<3210;i++){
					printf("%c",pointer[i]);
					fprintf(fp,"%c",pointer[i]);
				}
				printf("\n\ni=%d\n",i);
				printf("pointer:%d\n",pointer);
				printf("pointer:%d\n",(client->request) + (client->received));
				fclose(fp);
			}

                    char *req = strstr(client->request, "\r\n\r\n");
                    if (req) {
                        *req = 0;

                        if (strncmp("GET /", client->request, 5)) {
				error_printer(8);
				drop_client(client);//400 error
                        } 

			else {
                            char *path = client->request + 4;
                            char *end = strstr(path, " ");
                            if (!end) {
				error_printer(8);
				drop_client(client);//400 error
                            	}
				else {
                                	*end = 0;
                                	getresource(client, path);
                            	}
                        }
                    }
                }
            }

            client = next;
        }

    }
    close(server);
    return 0;
}

