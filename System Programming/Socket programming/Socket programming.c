
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
//Emir Muhammet Aydemir 171419008
int main(int argc, char *argv[]){

  char hostname[]="www.marmara.edu.tr";  
  char ipv6[INET6_ADDRSTRLEN] = "";
  
  if(argc > 2 ){
  	exit(1);
  }

  struct addrinfo *result;    
  struct addrinfo hints;      

  struct sockaddr_in *saddr;  

  int s; 
  
 

  memset(&hints,0,sizeof(struct addrinfo));  
  hints.ai_family = AF_INET; 

  
  
  if( (s = getaddrinfo(argv[1], NULL, &hints, &result)) != 0){
    fprintf(stderr, "getaddrinfo: %s\n",gai_strerror(s));
    exit(1);int hostname_to_ip(char *hostname , char *ip)
{
	int sockfd;  
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_in *h;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;

	if ( (rv = getaddrinfo( hostname , "http" , &hints , &servinfo)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	
	for(p = servinfo; p != NULL; p = p->ai_next) 
	{
		h = (struct sockaddr_in *) p->ai_addr;
		strcpy(ip , inet_ntoa( h->sin_addr ) );
	}
	
	freeaddrinfo(servinfo); 
	return 0;
}
  }


  saddr = (struct sockaddr_in *) result->ai_addr;

 
  printf("%s has address %s\n",argv[1], inet_ntoa(saddr->sin_addr));
  inet_ntop(AF_INET6,inet_ntoa(saddr->sin_addr),ipv6,INET6_ADDRSTRLEN);
  printf("%s  ipv6 has address %s\n",argv[1], ipv6);
  

  freeaddrinfo(result);
}



