#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void nothing_lisence(char* t, int us,char* mac_a,char* mac_b)
{
printf("封包資訊:\n");
printf("*=================================*\n");
printf("時間戳記 : %s.%d\n",t,us);
printf("來源MAC位址 : %s\n",mac_b);
printf("目的MAC位址 : %s\n",mac_a);
printf("這不是IP封包，滾！！＼(owo)/\n");
printf("*=================================*\n");
}
void ip_lisence(char* t, int us,char* mac_a,char* mac_b,char* ip_a,char* ip_b)
{
printf("封包資訊:\n");
printf("*=================================*\n");
printf("時間戳記 : %s.%d\n",t,us);
printf("來源MAC位址 : %s\n",mac_b);
printf("目的MAC位址 : %s\n",mac_a);
printf("這是個IP封包\n");
printf("來源IP位址 : %s\n",ip_b);
printf("目的IP位址 : %s\n",ip_a);
printf("這不是TCP/UDP封包，滾！！＼(owo)/\n");
printf("*=================================*\n");
}
void tcp_lisence(char* t, int us,char* mac_a,char* mac_b,char* ip_a,char* ip_b,int port)
{
printf("封包資訊:\n");
printf("*=================================*\n");
printf("時間戳記 : %s.%d\n",t,us);
printf("來源MAC位址 : %s\n",mac_b);
printf("目的MAC位址 : %s\n",mac_a);
printf("這是個IP封包\n");
printf("來源IP位址 : %s\n",ip_b);
printf("目的IP位址 : %s\n",ip_a);
printf("這是個TCP封包\n");
printf("Port號碼 : %d\n",port);
printf("*=================================*\n");
}
void udp_lisence(char* t, int us,char* mac_a,char* mac_b,char* ip_a,char* ip_b,int port)
{
printf("封包資訊:\n");
printf("*=================================*\n");
printf("時間戳記 : %s.%d\n",t,us);
printf("來源MAC位址 : %s\n",mac_b);
printf("目的MAC位址 : %s\n",mac_a);
printf("這是個IP封包\n");
printf("來源IP位址 : %s\n",ip_b);
printf("目的IP位址 : %s\n",ip_a);
printf("這是個UDP封包\n");
printf("Port號碼 : %d\n",port);
printf("*=================================*\n");
}
