#include "pipe_networking.h"

int main(){
	int to_server,from_server=client_handshake(&to_server);

	char inp[128],oup[128];
	while(1){
		printf("tell mr. server something interesting\n");
		fgets(inp,128,stdin);
		write(to_server,inp,128);
		read(from_server,inp,128);
		printf("server man says:\n%s\n",inp);
	}
	return 0;
}
