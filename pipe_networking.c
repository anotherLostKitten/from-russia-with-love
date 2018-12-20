#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int*to_client){
	char pied[HANDSHAKE_BUFFER_SIZE],i=0,sied[HANDSHAKE_BUFFER_SIZE],ackchck[HANDSHAKE_BUFFER_SIZE];
	for(int p=getpid();i<HANDSHAKE_BUFFER_SIZE&&p;sied[i++]=p%10+'0',p/=10);
	for(;i<HANDSHAKE_BUFFER_SIZE;sied[i++]=0);
	if(mkfifo(sied,0644)){
		printf("server makeification unsuccesful, please try attending the computer interaction club\n%s\n",strerror(errno));
		return 0;
	}
	int wkp,uppity;
	read(wkp=open(WKP,O_RDONLY),pied,HANDSHAKE_BUFFER_SIZE);
	close(wkp);
	*to_client=open(pied,O_WRONLY);
	write(*to_client,sied,HANDSHAKE_BUFFER_SIZE);
	read(uppity=open(sied,O_RDONLY),ackchck,HANDSHAKE_BUFFER_SIZE);
	remove(sied);
	if(strcmp(ACK,ackchck)){
		printf("cleint had the big RUDE and did not properly acknowledge\n");
		return 0;
	}
	return uppity;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int*to_server){
	char pied[HANDSHAKE_BUFFER_SIZE],i=0,sied[HANDSHAKE_BUFFER_SIZE];
	for(int p=getpid();i<HANDSHAKE_BUFFER_SIZE&&p;pied[i++]=p%10+'0',p/=10);
	for(;i<HANDSHAKE_BUFFER_SIZE;pied[i++]=0);
	if(mkfifo(pied,0644)){
		printf("server makeification unsuccesful, please try installing more ram\n%s\n",strerror(errno));
		return 0;
	}
	int wkp=open(WKP,O_WRONLY),downitty;
	write(wkp,pied,HANDSHAKE_BUFFER_SIZE);
	close(wkp);
	read(downitty=open(pied,O_RDONLY),sied,HANDSHAKE_BUFFER_SIZE);
	remove(pied);
	write(*to_server=open(sied,O_WRONLY),ACK,HANDSHAKE_BUFFER_SIZE);
	
	return downitty;
}
