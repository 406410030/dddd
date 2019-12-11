#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdatomic.h>
#define PORT 1234
#define MAXDATASIZE 100
#define game "ooxxinvite"
#define in "join"
#define out "disagree"
#define record "history"
char sendbuf[1024];
char recvbuf[1024];
char name[100];
int gamemode = 0;
int gametable[3][3];
int fd;
int player[2] = {0,0};
int counter = 0;
int painter = -1;
int invitei = 0;
int round = 0;
int repeat[10] = {0};
char rule01[]="邀請人的方式:<<ooxxinvite>> <<name>>";
char rule02[]="接受邀請的方式:<<join>> <<name>>";
char rule03[]="拒絕邀請的方式:<<disagree>> <<name>>";
char rule00[]="查詢人員歷史紀錄:<<history>>";
int gamecheckwin(int id)
{
	if(id != painter)printf("error check\n");
	if(gametable[0][0] == id && gametable[0][1] == id && gametable[0][2] == id)
	return 1;
	else if(gametable[1][0] == id && gametable[1][1] == id && gametable[1][2] == id)
	return 1;
	else if(gametable[2][0] == id && gametable[2][1] == id && gametable[2][2] == id)
	return 1;
	else if(gametable[0][0] == id && gametable[1][0] == id && gametable[2][0] == id)
	return 1;
	else if(gametable[0][1] == id && gametable[1][1] == id && gametable[2][1] == id)
	return 1;
	else if(gametable[0][2] == id && gametable[1][2] == id && gametable[2][2] == id)
	return 1;
	else if(gametable[0][0] == id && gametable[1][1] == id && gametable[2][2] == id)
	return 1;
	else if(gametable[0][2] == id && gametable[1][1] == id && gametable[2][0] == id)
	return 1;
	else
	return 0;
}
int gamechecklose(int id)
{
	if(id == painter)printf("error check\n");
	if(gametable[0][0] == id && gametable[0][1] == id && gametable[0][2] == id)
	return 1;
	else if(gametable[1][0] == id && gametable[1][1] == id && gametable[1][2] == id)
	return 1;
	else if(gametable[2][0] == id && gametable[2][1] == id && gametable[2][2] == id)
	return 1;
	else if(gametable[0][0] == id && gametable[1][0] == id && gametable[2][0] == id)
	return 1;
	else if(gametable[0][1] == id && gametable[1][1] == id && gametable[2][1] == id)
	return 1;
	else if(gametable[0][2] == id && gametable[1][2] == id && gametable[2][2] == id)
	return 1;
	else if(gametable[0][0] == id && gametable[1][1] == id && gametable[2][2] == id)
	return 1;
	else if(gametable[0][2] == id && gametable[1][1] == id && gametable[2][0] == id)
	return 1;
	else
	return 0;
}
void gamecheck(void)
{
	int win, lose, result;
	if(painter == 0){
		win = gamecheckwin(0);
		lose = gamechecklose(1);
		if(win == 1){
			printf("you win!!!\n");
			gamemode = 0;
		}
		if(lose == 1){
			printf("you lose...QAQ\n");
			gamemode = 0;
		}
	}
	if(painter == 1){
		win = gamecheckwin(1);
		lose = gamechecklose(0);
		if(win == 1){
			printf("you win!!!\n");
			gamemode = 0;
		}
		if(lose == 1){
			printf("you lose...QAQ\n");
			gamemode = 0;
		}
	}
}
int charcmp(int flag)
{
	if(flag == 2){
		if(strstr(sendbuf,"a0") != NULL)return 1;
		else if(strstr(sendbuf,"a1") != NULL)return 4;
		else if(strstr(sendbuf,"a2") != NULL)return 7;
		else if(strstr(sendbuf,"b0") != NULL)return 2;
		else if(strstr(sendbuf,"b1") != NULL)return 5;
		else if(strstr(sendbuf,"b2") != NULL)return 8;
		else if(strstr(sendbuf,"c0") != NULL)return 3;
		else if(strstr(sendbuf,"c1") != NULL)return 6;
		else if(strstr(sendbuf,"c2") != NULL)return 9;
		else return 0;
	}
	if(flag == 3){
		if(strstr(recvbuf,"a0") != NULL)return 1;
		else if(strstr(recvbuf,"a1") != NULL)return 4;
		else if(strstr(recvbuf,"a2") != NULL)return 7;
		else if(strstr(recvbuf,"b0") != NULL)return 2;
		else if(strstr(recvbuf,"b1") != NULL)return 5;
		else if(strstr(recvbuf,"b2") != NULL)return 8;
		else if(strstr(recvbuf,"c0") != NULL)return 3;
		else if(strstr(recvbuf,"c1") != NULL)return 6;
		else if(strstr(recvbuf,"c2") != NULL)return 9;
		else return 0;
	}
}
void blockit(int id,int flag)
{
	int i,j, stop = 0, me;
	if(flag == 0){
	if(player[0] == getpid())me = 0;
	if(player[1] == getpid())me = 1;
	}
	if(flag == 1){
	if(player[0] == getpid())me = 1;
	if(player[1] == getpid())me = 0;
	}
	repeat[id] = 1;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++){
			stop++;
			if(stop == id && gametable[i][j] == -1)
			gametable[i][j] = me;
		}
}
void printtable(void)
{
	int i,j;
	printf("\n===============================================\n");
	printf("\tooxx game\n");
	printf("===============================================\n");
	printf("\ta\tb\tc\n");
	printf("===============================================\n");
	for(i = 0; i < 3; i++){
		printf("%d",i);
		for(j = 0; j < 3; j++)
			printf("\t%d",gametable[i][j]);
	printf("\n");
	}
	printf("===============================================\n");
	printf("example : b2\n");
	printf("===============================================\n");
	counter++;
	printf("turn = %d\n",counter);
	if(counter == 10){
		gamecheck();
		printf("GAME_OVER\n");
		gamemode = 0;
		invitei = 0;
	}
	else{
		gamecheck();
		if(gamemode == 0){
		printf("GAME_OVER\n");
		invitei = 0;
		}
	}
}
void tableset(void)
{
	int i,j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++){
			gametable[i][j] = -1;
		}
	for(i = 0; i <= 9; i++)
			repeat[i] = 0;
	counter = 0;
	painter = -1;
	invitei = 0;
}
void pthread_recv(void* ptr)
{
int i;
    while(1)
    {
	char tmp[1024] = "";
	char catchname[50] = "";
    if ((recv(fd,recvbuf,MAXDATASIZE,0)) == -1){
        printf("recv() error\n");
        exit(1);
        }
	strcpy(tmp, recvbuf);
	int j = 0;
	if(strstr(recvbuf, name) != NULL){
		if(strstr(recvbuf,game) != NULL){
			for(j = 0; j < strlen(tmp); j++){
				if(recvbuf[j] == ':')break;
				catchname[j] = recvbuf[j];
			}
			printf("%s 邀請你進入圈圈叉叉遊戲，請問是否接受?\n",catchname);
			invitei = 1;
		}
		if(invitei == 1 && strstr(recvbuf,in) != NULL){
			gamemode = 1;
			for(j = 0; j < strlen(tmp); j++){
				if(recvbuf[j] == ':')break;
				catchname[j] = recvbuf[j];
			}
			printf("%s 接受你的邀請\n",catchname);
			printf("start_game\n");
			printtable();
		}
		if(invitei == 1 && strstr(recvbuf,out) != NULL){
			gamemode = 0;
			for(j = 0; j < strlen(tmp); j++){
				if(recvbuf[j] == ':')break;
				catchname[j] = recvbuf[j];
			}
			printf("%s 拒絕你的邀請\n",catchname);
		}
		if(strstr(recvbuf,record) != NULL)
		printf("%s",recvbuf);
	}
	else printf("%s",recvbuf);
	if(gamemode == 1){
	int id;
	if(counter > 0){
		id = charcmp(3);
		if(id > 0)
		blockit(id,1);
		round = 0;
	}
	if(id > 0)
	printtable();
	}
    	memset(recvbuf,0,sizeof(recvbuf));
    }
}



    int main(int argc, char *argv[])
    {
    int  numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;


    if (argc !=2) {         printf("Usage: %s <IP Address>\n",argv[0]);
    exit(1);
    }


    if ((he=gethostbyname(argv[1]))==NULL){
    printf("gethostbyname() error\n");
    exit(1);
    }

    if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
    printf("socket() error\n");
    exit(1);
    }

    bzero(&server,sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr = *((struct in_addr *)he->h_addr);
    if(connect(fd, (struct sockaddr *)&server,sizeof(struct sockaddr))==-1){
    printf("connect() error\n");
    exit(1);
    }

    printf("connect success\n");
    char str[]=":已進入遊戲聊天室\n";
    printf("请输入姓名：");
    fgets(name,sizeof(name),stdin);
    send(fd,name,(strlen(name)-1),0);
    send(fd,str,(strlen(str)),0);
    printf("%s\n%s\n%s\n%s\n",rule00,rule01,rule02,rule03);

    pthread_t tid;
    pthread_create(&tid,NULL,pthread_recv,NULL);

    while(1)
    {
        memset(sendbuf,0,sizeof(sendbuf));
        fgets(sendbuf,sizeof(sendbuf),stdin);
        if(strstr(sendbuf,"exit")!=NULL){
            printf("您已退出\n");
            send(fd,name,(strlen(name)-1),0);
            send(fd,":",1,0);
	    send(fd,sendbuf,(strlen(sendbuf)),0);
	    
            memset(sendbuf,0,sizeof(sendbuf));
            break;
        }
	if(charcmp(2) != 0 && invitei == 0){
		printf("you are not player\n");
		continue;
	}
	if(gamemode){
		int id = charcmp(2);
		if(id != 0){
		if(repeat[id] == 1){
		printf("you can not put there\n");
		continue;
		}
		if(round == 1){
		printf("not your turn\n");
		continue;
		}
		round = 1;
		blockit(id,0);
		printtable();
		}
		else{
		printf("unaccept input\n");
		continue;
		}
	}
	if(strstr(sendbuf,game) != NULL){
		player[1] = getpid();
		tableset();
		painter = 1;
		invitei = 1;
	}
	if(strstr(sendbuf,in) != NULL){
		if(invitei == 1){
		gamemode = 1;
		player[0] = getpid();
		tableset();
		printf("start_game\n");
		painter = 0;
		invitei = 1;
		printtable();
		}
		else{
		printf("not you\n");
		continue;
		}
	}
	if(strstr(sendbuf,out) != NULL && invitei == 0){
	printf("not you\n");
	continue;
	}
        send(fd,name,(strlen(name)-1),0);
        send(fd,":",1,0);
	send(fd,sendbuf,(strlen(sendbuf)),0);


    }
//  sprintf("")
//  if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){
 // printf("recv() error\n");
 // exit(1);
 // }

    close(fd);
 }
