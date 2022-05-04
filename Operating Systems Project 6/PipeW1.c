/*Jake Kennedy CSE 2431 Lab6*/
/*Part B, PipeW1.c File*/
/*COMPILED USING gcc -std=c99 -pedantic -o PipeW1 PipeW1.c*/

#define _XOPEN_SOURCE 500
#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int x,char **y ){
    char bufferB[6]="001aaa";
    /*convert arg string back to fid int*/
    int fid1=atoi(*y),i,writeRes;

    /*iterate 500 times*/
    for(i=1;i<501;i++){
	/*write buffer to pipe*/
	writeRes=write(fid1,bufferB,6);
	if(writeRes<0){printf("Error writing to pipe\n");exit(-1);}
	/*adjust buffer by altering needed chars per each iteration*/
	bufferB[2]++;
	if(bufferB[2]>'9'){
	    bufferB[2]='0';
	    bufferB[1]++;
	    if(bufferB[1]>'9'){
	        bufferB[1]='0';
	        bufferB[0]++;
	    }
	}
	/*sleep every 100 iteratios*/
	if(i%100==0)usleep(100000);	
    }
	exit(0);	
}
