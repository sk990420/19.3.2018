#include "sound.h"
#include "comm.h"
#include "screen.h"
#include <stdio.h>
#include <math.h>
void printID(char id[]) {
	int i;
	for( i=0;i<4;i++)
		printf("%c", id[i]);

	printf("\n");
}
/*
 This function uses VT100 escape sequence to show the value when you try to make sound to microphone
 and some error message when there is something wrong with "fp"
*/
void dispWAVData(char filename[]) {
	int i,j;	//loop counters
	FILE *fp;	//file handler to open the file "test.wav"
	double rms[80], sum;		//80 pieces of RMS value
	short samples[SAMPLERATE];	//totally 16000 samples in 1 sec
	WAVHeader mh;		//just used to skip over the header of wav file
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Error when open the file!\n");
		return;
	}
	fread(&mh, sizeof(mh), 1, fp);	//skip over the header of wav file
	fread(samples, sizeof(short), SAMPLERATE, fp);
	fclose(fp);
	clearScreen();
	for(i=0; i<80; i++) {
		for(j=0, sum=0.0; j<SAMPLERATE/80; j++) {
			sum += samples[j+i*200] * samples[j+i*200];
		}
		rms[i] = sqrt(sum/200);
#ifdef DEBUG
		printf("rms[%d]: %10.4f, dB = %10.4f\n", i, rms[i], 20*log10(rms[i]));
#else
		dispBar(i, 20*log10(rms[i]));
#endif
	}
#ifdef COMM		// send data to "sound_log.txt"
	sendToServer(rms);
#endif
}

/*
 This function uses VT100 escape sequence to open the file
 and show some error messages when open the file faily
*/
void dispWAVHeader(char filename[]){
	FILE *fp;
	WAVHeader mh;


	fp = fopen(filename,"r");
	if(fp == NULL){
		printf("Error when open the file!\n");
		return;
	}
	fread(&mh, sizeof(mh), 1, fp);
	fclose(fp);
	printf("Chunk ID: ");
	printID(mh.chunkID);
	printf("  chunk size:%d\n", mh.chunkSize);
	printf("Format: ");
	printID(mh.format);
	printf("  subchunk1 ID:  ");
	printID(mh.subchunk1ID);
	printf("  subchunk 1 size: %d\n", mh.subchunk1Size);
	printf("  AudioFormat: %d\n", mh.audioFormat);
	printf("  NumChannels: %d\n");
	printf("SampleRate:  %d\n", mh.sampleRate);
	printf("ByteRate:  %d\n", mh.byteRate);
	printf("  BlockAlign: %d\n", mh.blockAlign);
	printf("  BitsPerSample: %d\n", mh.bitsPerSample);
	printf("subchunk2 ID:  ");
	printID(mh.subchunk2ID);
	printf("Subchunk 2 size:  %d\n", mh.subchunk2Size);
}
