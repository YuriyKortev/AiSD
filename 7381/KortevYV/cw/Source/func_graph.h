
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define res_add "../result_add.bmp"
#define res_del "../result_del.bmp"
#define res_worst_add "../result_worst_add.bmp"
#define res_worst_del "../result_worst_del.bmp"

#pragma pack(1)

typedef struct {
	unsigned short type;
	unsigned int size;
	unsigned int reserved;
	unsigned int offset;
} BMPHEADER;


typedef struct {
	unsigned size;
	int w,h;
	unsigned short planes;
	unsigned short bits;
	unsigned int compression;
	unsigned int imsize;
	int xres,yres;
	unsigned int nclrs;
	unsigned int importantclrs;
} INFOHEADER;

#pragma pack(0)

typedef struct {
	char b,g,r;
} CLR;

void newPIC(BMPHEADER*,INFOHEADER* ,CLR**,char*);
CLR** getCLRS(FILE* , BMPHEADER* , INFOHEADER* );
CLR** initCLR(int );
CLR** crtCLRS(int* , int, int);
void graph(int*,int,int,int ,char*);
