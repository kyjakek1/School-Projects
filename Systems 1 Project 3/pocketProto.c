/*Jake Kennedy offtable prototype file*/
#include <stdio.h>
#define CORNER 3.1819805
#define SIDE 4.5

int main(){
    double xPos,yPos;
    int result=0;
    
    scanf("%lf %lf",&xPos,&yPos);
    if(xPos<=CORNER||xPos>=100-CORNER){
	if(yPos<=0.0||yPos>=50.0){
	    result=1;
	}
    }else if(xPos>=100.0/2-SIDE/2&&xPos<=100.0/2+SIDE/2){
	if(yPos>=50.0||yPos<=0.0){
	    result=1;
	}
    }else if(yPos<=CORNER||yPos>=50.0-CORNER){
	if(xPos<0.0||xPos>=100.0) result=1;
    }

    if(result)printf("Ball is in a pocket\n");
    if(!result)printf("Ball is still on table\n");

    return 0;
}
