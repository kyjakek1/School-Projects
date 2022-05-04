/*Jake Kennedy CSE 2431 Lab6*/
/*Part B, PipeR.c File*/
/*COMPILED USING gcc -std=c99 -pedantic -o PipeR PipeR.c*/

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
    int fid0=atoi(*y);
    char bufferA[100];
    int writeRes,readCount,loop=1,writtenCount=0,j=0,totalReadCount=0;

    /*loop until other processes are terminated and pipe is empty*/
    while(loop){
	/*read from buffer*/
	readCount=read(fid0,bufferA,100);
	if(readCount<0){printf("Error reading from pipe\n");exit(-1);}

	/*keep track of number of reads and total chars read*/
	j++;
	totalReadCount+=readCount;

	/*if pipe isnt empty*/
	if(readCount>0){
	    /*write results to screen*/
	    writeRes=write(1,bufferA,readCount);
	    if(writeRes<0){printf("Error writing to screen\n");exit(-1);}
	    printf("\n");
	    /*keep track of number of chars written*/
	    writtenCount+=writeRes;
	}else{
	    /*if pipe is empty end loop*/
	    loop=0;
	}
	/*sleep every 50 iterations*/
	if(j%50==0) usleep(200000);
    }
    printf("\nProcess D: There were %d issued read statements and\n%d characters read from the pipe and %d characters written to the screen\n",j,totalReadCount,writtenCount); 
    exit(0);
}
