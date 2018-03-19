#define SAMPLERATE 16000

typedef struct{
	char chunkID[4];
	unsigned int chunkSize;
	char format[4];
	char subchunk1ID[4];
	unsigned int subchunk1Size;
	unsigned short audioFormat;
	unsigned short numChannels;
	unsigned short sampleRate;
	unsigned int byteRate;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	char subChunk2ID[4];
	unsigned int subchunk2Size;
}WAVHeader;
void dispWAVHeader(char filename[]);
void dispWAVData(char filename[]);
void printID(char []);
