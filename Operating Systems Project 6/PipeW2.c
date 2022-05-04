/*Jake Kennedy CSE 2431 Lab6*/
/*Part B, PipeW2.c File*/
/*COMPILED USING gcc -std=c99 -pedantic -o PipeW2 PipeW2.c*/

#define _XOPEN_SOURCE 500
#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int x,char **y){
    /*convert arg string back to fid int*/
    int fid1=atoi(*y),i,writeRes;
    char bufferC[3]="Ax0";
    
    /*iterate 260 times*/
    for(i=1;i<261;i++){
	/*write buffer to pipe*/
        writeRes=write(fid1,bufferC,3);
        if(writeRes<0){printf("Error writing to pipe\n");exit(-1);}

	/*adjust buffer by incrementing/reseting needed char values each iteration*/
        bufferC[0]++;
        if(bufferC[0]>'Z'){
   	    bufferC[0]='A';
	    bufferC[2]++;
	    if(bufferC[2]>'9'){
	        bufferC[2]='0';
	    }
	}
	
	/*sleep every 60 iterations*/
	if(i%60==0)usleep(300000);
    }
    exit(0);
}
