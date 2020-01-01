#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <time.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "lisence.c"
int ipcount = 0;
int tcpcount = 0;
int udpcount = 0;
char source_ip[1000][18];
char destination_ip[1000][18];
int ip_num[1000] = {0};
int num = 0;
void countip(char* s,char* d)
{
	int i, bp = 0;
	if(num == 0){
	strcpy(source_ip[num],s);
	strcpy(destination_ip[num],d);
	ip_num[num]++;
	num++;
	}
	else{
		bp = 0;
		for(i = 0; i < num;i++){
		if(strstr(source_ip[i],s) != NULL && strstr(destination_ip[i],d) != NULL){
			bp = 1;
			ip_num[i]++;
			break;
			}
		}
		if(bp == 0){
		strcpy(source_ip[num],s);
		strcpy(destination_ip[num],d);
		ip_num[num]++;
		num++;
		}
	}
}
char* mac_add(u_int8_t *data)
{
	static char mac[18] = "";
	snprintf(mac,sizeof(mac), "%02x:%02x:%02x:%02x:%02x:%02x",data[0],data[1],data[2],data[3],data[4],data[5]);
	return mac;
}

char* ip_ntoa(void *i)
{
	static char ip[INET_ADDRSTRLEN] = "";
	inet_ntop(AF_INET,i,ip,sizeof(ip));
	return ip;
}

void handler(u_char *temp1,const struct pcap_pkthdr *header,const u_char *data)
{
    static int d = 0;
    printf("第%d個封包\n", ++d);
    u_int i=0;
	struct tm *tm;
	char timestr[BUFSIZ];
	tm = localtime(&header->ts.tv_sec);
	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm);
	int usec = header->ts.tv_usec;
	//乙太網路區
	u_int32_t len = header->caplen;
	char dstmac[18] = "", srcmac[18] = "";
	struct ether_header *eth = (struct ether_header *)data;
	struct ip *ip = (struct ip*)(data + ETHER_HDR_LEN);
    snprintf(dstmac,sizeof(dstmac), "%s",mac_add(eth->ether_dhost));
    snprintf(srcmac,sizeof(srcmac), "%s",mac_add(eth->ether_shost));
	u_int16_t eth_type = ntohs(eth->ether_type);
	int ip_in = 0;
	if(eth_type == ETHERTYPE_IP){
        ip_in = 1;
        ipcount++;
	}
	else{
        nothing_lisence(timestr,usec,dstmac,srcmac);
	}
    if(ip_in){
	//IP層
	char dstip[INET_ADDRSTRLEN] = "", srcip[INET_ADDRSTRLEN] = "";
	u_char protocol = ip->ip_p;
    	snprintf(srcip,sizeof(srcip), "%s",ip_ntoa(&ip->ip_src));
    	snprintf(dstip,sizeof(dstip), "%s",ip_ntoa(&ip->ip_dst));
	countip(srcip,dstip);
        if(protocol == IPPROTO_UDP){
	    //UDP層
            struct udphdr *udp = (struct udphdr*)(data + ETHER_HDR_LEN+ (ip->ip_hl << 2));
            u_int16_t dstport = ntohs(udp->uh_dport), srcport = ntohs(udp->uh_sport);
            udp_lisence(timestr,usec,dstmac,srcmac,dstip,srcip,srcport);
            udpcount++;
        }
        else if(protocol == IPPROTO_TCP){
	    //TCP層
            struct tcphdr *tcp = (struct tcphdr*)(data + ETHER_HDR_LEN+ (ip->ip_hl << 2));
            u_int16_t dstport = ntohs(tcp->th_dport), srcport = ntohs(tcp->th_sport);
            tcp_lisence(timestr,usec,dstmac,srcmac,dstip,srcip,srcport);
            tcpcount++;
        }
	else{
		ip_lisence(timestr,usec,dstmac,srcmac,dstip,srcip);
	}
	ip_in = 0;
    }
}

int main(int argc, const char * argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *handle = NULL;
	handle = pcap_open_offline(argv[2], errbuf);
	if(!handle) {
		fprintf(stderr, "pcap_open_offline: %s\n", errbuf);
		exit(1);
	}
	pcap_loop(handle,0,handler,NULL);
	pcap_close(handle);
	printf("the total IP type pcap = %d\n",ipcount);
	int recheck = 0;
	int i;
	for(i = 0; i < num; i++){
		printf("source = %s, destination = %s, IP num = %d\n",source_ip[i],destination_ip[i],ip_num[i]);
		recheck+=ip_num[i];
	}
	printf("total count = %d\n",recheck);
	if(recheck != ipcount) printf("這一定是有問題...(xmx)RIP\n");
	printf("the total TCP type pcap = %d\n",tcpcount);
	printf("the total UDP type pcap = %d\n",udpcount);
    return 0;
}
