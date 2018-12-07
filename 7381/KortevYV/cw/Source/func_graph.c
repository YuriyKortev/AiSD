#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "func_graph.h"

void newPIC(BMPHEADER* bmphd,INFOHEADER* infohd,CLR** arr,char* fname){

	FILE* f=fopen(fname,"w");

	size_t pad = 0;
	while(((infohd->w*3+pad) % 4)!=0)
       		pad++;


	fwrite(bmphd,sizeof(BMPHEADER),1,f);
	fwrite(infohd,sizeof(INFOHEADER),1,f);

	int i,j;


	for(i=0;i< infohd->h;i++){
		for(j=0;j< infohd->w;j++)
			fwrite(&arr[i][j],sizeof(CLR),1,f);
		if(pad!=0)
			fseek(f,pad,SEEK_CUR);

	}

	fclose(f);
	return;
}

CLR** initCLR(int w){
		int i,j;
		CLR** clr=(CLR**)malloc(100 * sizeof(CLR*));

		
		for(i=0; i < 100; i++)
			clr[i]=(CLR*)malloc(w * sizeof(CLR));
		for(i=0;i< 100;i++)
			for(j=0;j< w; j++){
				clr[i][j].r=255;
				clr[i][j].g=255;
				clr[i][j].b=255;
			}
		return clr;

}
CLR** crtCLRS(int* arr,int h, int w){

	CLR** clr=initCLR(w);
	int k,j,i=0;
	
	for(i=0;i<w;i++){
		clr[arr[i]][i].r=0;
		clr[arr[i]][i].g=0;
		clr[arr[i]][i].b=0;
	}


	return clr;
}

CLR** getCLRS(FILE* f, BMPHEADER* bmphd, INFOHEADER* infohd){

	size_t pad = 0;
	while(((infohd->w*3+pad) % 4)!=0)
	pad++;

	CLR** arr=(CLR**)malloc((infohd->h) * sizeof(CLR*));

	int i=0;
	for(i; i < infohd->h; i++)
		arr[i]=(CLR*)malloc((infohd->w) * sizeof(CLR));


	int k,j;

	for(i=0;i< infohd->h;i++){
		for(j=0;j< infohd->w; j++)
			fread(&arr[i][j],sizeof(CLR),1,f);
		if(pad!=0)
			fseek(f,pad,SEEK_CUR);
}

return arr;

}


void graph(int* arr,int h,int w,int colour,char* fname){

	int i,j;
	
	FILE* f;
	BMPHEADER* bmphd=(BMPHEADER*)malloc(sizeof(BMPHEADER));
	INFOHEADER* infohd=(INFOHEADER*)malloc(sizeof(INFOHEADER));
	if((f=fopen(fname,"rb"))==NULL){
	
		CLR** clr=crtCLRS(arr,h,w);
		f=fopen(fname,"w");
		
	
		bmphd->type=19778;
		bmphd->size=h*w*3;
		bmphd->reserved=0;
		bmphd->offset=54;
	
		infohd->size=40;
		infohd->w=w;
		infohd->h=h;
		infohd->planes=1;
		infohd->bits=24;
		infohd->compression=0;
		infohd->imsize=sizeof(BMPHEADER)+sizeof(INFOHEADER)+h*w*3;
		infohd->xres=0;
		infohd->yres=0;
		infohd->nclrs=0;
		infohd->importantclrs=0;

		size_t pad = 0;
		while(((infohd->w*3+pad) % 4)!=0)
	        pad++;
	
	
	
	
		fwrite(bmphd,sizeof(BMPHEADER),1,f);
		fwrite(infohd,sizeof(INFOHEADER),1,f);
	
		

		for(i=0;i< infohd->h;i++){
			for(j=0;j< infohd->w;j++)
				fwrite(&clr[i][j],sizeof(CLR),1,f);
			if(pad!=0)
			fseek(f,pad,SEEK_CUR);

		}
		}
	else{
		fread(bmphd,sizeof(BMPHEADER),1,f);
		fread(infohd,sizeof(INFOHEADER),1,f);
		CLR** clr=getCLRS(f,bmphd,infohd);

		for(i=0;i<infohd->w;i++){
				switch (colour){
					case 0:
						clr[arr[i]][i].r=0;
						clr[arr[i]][i].g=0;
						clr[arr[i]][i].b=255;
					break;
					case 1:
						clr[arr[i]][i].r=0;
						clr[arr[i]][i].g=255;
						clr[arr[i]][i].b=0;
					break;
					case 2:
					
						clr[arr[i]][i].r=255;
						clr[arr[i]][i].g=0;
						clr[arr[i]][i].b=0;
					break;
					case 3:
						clr[arr[i]][i].r=255;
						clr[arr[i]][i].g=255;
						clr[arr[i]][i].b=0;
					break;
				}
			}

		newPIC(bmphd,infohd,clr,fname);
	}

	fclose(f);
	return;
}
