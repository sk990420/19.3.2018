// this file contains the main function of our project
#include "sound.h"
#include <stdlib.h>
//so far this main funcion contains
int main(void){
	while(1){
		system("arecord -r16000 -c1 -f s16_LE -d1 test.wav");
		dispWAVHeader("test.wav");
		break;
	}
	return 0;
}
