/*Jake Kennedy Lab 3 Movement File*/

#include <stdio.h>
#include "structs.h"
#include "lib8ball.h"
#include "table.h"
#include "debug.h"

/*determines if ball is still moving*/
int inMotion(void *data){
    int result=0;
    struct BallData *ball=data;
    if(ball->xVel!=0.0||ball->yVel!=0.0) result=1;
    return result;
}

/*if the ball needs to bounce, it calls appropriate reflection fxn*/
int bounce(struct BallData *ball){
    if(inLeftRail(ball)) reflectLeft(ball);
    if(inRightRail(ball)) reflectRight(ball);
    if(inTopRail(ball)) reflectTop(ball);
    if(inBottomRail(ball)) reflectBottom(ball);
    return 0;
}

/*moves ball in accordance with lab2*/
int basicMove(struct BallData *ball,double dt){
    ball->xPos=ball->xPos+ball->xVel*dt;
    ball->yPos=ball->yPos+ball->yVel*dt;
    return 0;
}

/*downgrades velocities by friction percenctage*/
void applyFriction(struct BallData *ball){
    double percent=frictionPercent(ball);
    ball->xVel*=percent;
    ball->yVel*=percent;
}

/*moves a ball, if it remains on the table, bounces it and applies friction*/
void moveBalls(void *data){
    struct BallData *ball=data;
    basicMove(ball,ball->table->dt);
    if(!offTable(ball)){
	bounce(ball);
	applyFriction(ball);
    }    
}
