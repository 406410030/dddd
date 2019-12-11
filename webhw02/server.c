#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#define PORT 1234
#define BACKLOG 1
#define Max 5
#define MAXSIZE 1024

int fdt[Max]={0};
char mes[1024];
char str[]=":已進入遊戲聊天室\n";
char namelist[600];
char callrecord[]="history";
char inhis[]="已進入\n";
char outhis[]="已登出\n";

/**/

void *pthread_service(void* sfd)
{
    int fd=*(int *)sfd;
    while(1)
    {
        int numbytes;
        int i;
	char tmp[100];
        numbytes=recv(fd,mes,MAXSIZE,0);
        if(numbytes<=0){
            for(i=0;i<Max;i++){
                if(fd==fdt[i]){
                    fdt[i]=0;
                }
            }
            printf("numbytes=%d\n",numbytes);
            printf("exit! fd=%d\n",fd);
            break;

        }
        printf("receive message from %d,size=%d\n",fd,numbytes);
        SendToClient(fd,mes,numbytes);
        bzero(mes,MAXSIZE);

    }
    close(fd);

}


/**/
int SendToClient(int fd,char* buf,int Size)
{
        int i;
	char tmp[100];
	if(strstr(buf,"exit") != NULL){
		printf("lalala:%s\n",buf);
	    for(i = 0; buf[i] != ':'; i++){
	    tmp[i] = buf[i];
	    printf("%c\n",buf[i]);
	    }
	    tmp[i] = ' ';
	    strcat(namelist,tmp);
	    strcat(namelist,outhis);
	}
	if(strstr(buf,str) != NULL){
	for(i = 0; buf[i] != ':'; i++){
	tmp[i] = buf[i];
	printf("%c\n",buf[i]);
	}
	tmp[i] = ' ';
	strcat(namelist,tmp);
	strcat(namelist,inhis);
	}
    for(i=0;i<Max;i++){
        printf("fdt[%d]=%d\n",i,fdt[i]);
	if(fdt[i] == fd && strstr(buf,callrecord) != NULL){
            send(fdt[i],namelist,strlen(namelist),0);
            printf("send message to %d\n",fdt[i]);
	}
        else if((fdt[i]!=0)&&(fdt[i]!=fd)){
            send(fdt[i],buf,Size,0);
            printf("send message to %d\n",fdt[i]);
        }
    }
    return 0;


}

int  main()
{


    int listenfd, connectfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sin_size;
    sin_size=sizeof(struct sockaddr_in);
    int number=0;
    int fd;
    strcat(namelist,"遊戲聊天室歷史紀錄:\n");

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Creating socket failed.");
        exit(1);
    }


    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&server,sizeof(server));


    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr = htonl (INADDR_ANY);


    if (bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
    perror("Bind error.");
    exit(1);
    }


    if(listen(listenfd,BACKLOG) == -1){
    perror("listen() error\n");
    exit(1);
    }
    printf("Waiting for client....\n");


    while(1)
    {

        if ((fd = accept(listenfd,(struct sockaddr *)&client,&sin_size))==-1) {
        perror("accept() error\n");
        exit(1);

        }

        if(number>=Max){
            printf("no more client is allowed\n");
            close(fd);
        }

        int i;
        for(i=0;i<Max;i++){
            if(fdt[i]==0){
                fdt[i]=fd;
                break;
            }

        }



        pthread_t tid;
        pthread_create(&tid,NULL,(void*)pthread_service,&fd);

        number=number+1;


    }


    close(listenfd);
    }

