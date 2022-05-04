/*Jake Kennedy CSE 2421 Lab 3 File*/

#include <stdio.h>
#include "structs.h"
#include "linkedlist.h"
#include "lib8ball.h"
#include "table.h"
#include "debug.h"
#include "movement.h"
#include "allocation.h"
#define THOU 1000
#define TWOTHOU 2000
#define FIVE 5

/*compares the two ball numbers, returning true if data1 is lower*/
int numberOrder(void *data1, void *data2){
    struct BallData *one=data1;
    struct BallData *two=data2;
    int oneNum=one->ballNum;
    int twoNum=two->ballNum;
    int result=0;
    if(oneNum<twoNum) result=1;
    return result;       
}

/*adds dynamically allocated balls to the linked list*/
int addBall(struct Simulation *table, struct BallData *ball){
    struct BallData *bp;
    int result=0;
    if(bp=allocateBall(ball)){	
	*bp=*ball;
	if(insert(&table->balls,bp,numberOrder,TEXT)){
	    result=1;
	}else{
	    freeBall(bp);
	    printf("Error inserting ball into list\n");
	}
    }else{
	printf("Error allocating ball\n");
    }

    return result;
}

/*initializes the static ball struct with the scanned values*/
void initializeStruct(struct BallData *ball,int ballNum,double xPos,double yPos,double xVel,double yVel){
    ball->ballNum=ballNum;
    ball->xPos=xPos;
    ball->yPos=yPos;
    ball->xVel=xVel;
    ball->yVel=yVel;
}

/* function attempts to read in ball data from file and if data exists, puts it in a struct and adds to the sim*/
int readBalls(struct Simulation *table){
    int loop=FIVE,ballNum,result=0,count;
    double xPos,yPos,xVel,yVel;
    struct BallData Ball;
    struct BallData *BallP;
   
    BallP=&Ball;
    BallP->table=table;
   
    while(loop==FIVE){
	loop=scanf("%d %lf %lf %lf %lf",&ballNum,&xPos,&yPos,&xVel,&yVel);
	if(loop==FIVE){
	    initializeStruct(BallP,ballNum,xPos,yPos,xVel,yVel);
	    if(addBall(table,BallP)) result=1;
	}
    }
    if(TEXT)printf("read_one: scanf returned %d\n",loop);
    return result;
}

/*Prints the data for a single ball to the screen*/
void printBall(void *data){
    struct BallData *ball=data;
    printf("Ball # %d is at (%.3lf, %.3lf) moving (   %.4lf,    %.4lf)\n",ball->ballNum,ball->xPos,ball->yPos,ball->xVel,ball->yVel);
}

/*Prints the elapsed time then iterates over the list to print every ball*/
int printBalls(struct Simulation *table){
    printf("At time %.4lf:\n",table->elapsedT);
    iterate(table->balls,printBall);
    printf("\n");
    return 0;
}

/*draws a single ball to the table*/
void drawBall(void *data){
    struct BallData *ball=data;
    eb_ball(ball->ballNum,ball->xPos,ball->yPos);
}

/*iterates over the list to draw every ball to the screen*/
int drawBalls(struct Simulation *table){
    eb_clear();
    iterate(table->balls,drawBall);
    eb_refresh();
    millisleep((unsigned int)(THOU*table->dt));
    return 0; 
}

/*If in text mode it prints balls, if in graphics mode and table can be initialized
 * draws balls*/
int output(struct Simulation *table){
    if(TEXT) printBalls(table);
    if(GRAPHICS) drawBalls(table);
    return 0;
}

/*Computes the frame time for each ball's velocity data*/ 
double frameTime(void *data){
    struct BallData *ball=data;
    double dtX=frameTimeX(ball);
    double dtY=frameTimeY(ball);
    double fDT;
    
    if(dtX<dtY){
	fDT=dtX;
    }else{
	fDT=dtY;
    }
    return fDT;
}

/*Handles all the table output, ball movement, and taking balls off the table
 * Master Simulation Function*/
int runTable(struct Simulation *table){
    table->dt=least(table->balls,frameTime);
    while(table->balls!=NULL&&some(table->balls,inMotion)){
	output(table);
	iterate(table->balls,moveBalls);
	deleteSome(&table->balls,offTable,freeBall,TEXT);
	table->elapsedT+=table->dt;
    }
    output(table);
    return 0;
}

/*always returns true*/
int alwaysTrue(void *data){
    return 1;
}

/*Clears the screen and sleeps for 2 seconds*/
void clearSleep(){
    eb_clear();
    eb_refresh();
    millisleep(TWOTHOU);
}

/*finishing touches once simulation is ran, if text mode prints elapsed time
 * if graphics mode, clears screen, also deletes every ball left on the table*/
void finishing(struct Simulation *table){
    if(TEXT)printf("Simulation ends at sim elapsed time of %.4lf seconds.\n",table->elapsedT);
    if(GRAPHICS) clearSleep();
    deleteSome(&table->balls,alwaysTrue,freeBall,TEXT);
}

/*if it can read balls, it will launch the simulation*/
int attemptSim(){
    int result=0;
    struct Simulation pooltable={0,0,NULL};
    struct Simulation *tableP=&pooltable;
    if(readBalls(tableP)){
	runTable(tableP);
	finishing(tableP);
	result=1;
    }   
    return result;
}

/*gets time for simulation to run and attempts the sim*/
int main(){
    double iTime=now();
   
    if(TEXT||(GRAPHICS&&eb_initialize(0))){
	int simVal=attemptSim();
    
	if(GRAPHICS)  eb_teardown();
    }

    printf("Total run time is %.9lf seconds.\n",now()-iTime);
    return 0;
}
