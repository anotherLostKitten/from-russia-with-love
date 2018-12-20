#include "pipe_networking.h"
#include <time.h>
#include <signal.h>

void swap(char*bucket,int a,int b){
	char tmp=bucket[a];
	bucket[a]=bucket[b];
	bucket[b]=tmp;
}

char*shuffle(char*bucket){
  for(int i=strlen(bucket);i-->0;)
    swap(bucket,i,rand()%(i+1));
  return bucket;
}

static void sighandler(int signo){
	if(signo==SIGINT||signo==SIGPIPE){
		printf("server shutting down due to client disconnect or interrupt signal...\n");
		remove(WKP);
		exit(1);
	}
}


int main(){
	signal(SIGINT,sighandler);
	signal(SIGPIPE,sighandler);
	if(mkfifo(WKP,0644)){
		printf("server makeification unsuccesful, please try deleting system32\n%s\n",strerror(errno));
		return 0;
	}
	srand(time(0));
	int to_client,from_client=server_handshake(&to_client);
	//	printf("sever:%d,%d\n",to_client,from_client);
	char*nwli,inp[128];
	while(1){
		read(from_client,inp,128);
		if(nwli=strrchr(inp,'\n'))
			*nwli=0;
		write(to_client,shuffle(inp),128);
	}
	remove(WKP);
	return 0;
}
