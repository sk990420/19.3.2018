// this file contains the main function of our project
#include "sound.h"
#include <stdlib.h>
#include <signal.h>
//so far this main funcion contains
int main(void){
	int ret;
	while(1){
		ret = system("arecord -r16000 -c1 -f s16_LE -d1 test.wav");
		if(WIFSIGNALED(ret) && (WTERMSIG(ret)==SIGINT)) break;
		dispWAVHeader("test.wav");
		dispWAVData("test.wav");
		//break;
	}
	return 0;
}
