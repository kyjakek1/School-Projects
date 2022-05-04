/*Jake Kennedy Table File*/
#include <stdio.h>
#include <math.h>
#include "dimensions.h"
#include "structs.h"
#include "linkedlist.h"
#define TWO 2.0

/*determines if the ball is off the table i.e. in a pocket*/
int offTable(void *data){
    struct BallData *ball=data;
    int result=0;
    
    if(ball->xPos<=cornerPLength||ball->xPos>=tLength-cornerPLength){
	if(ball->yPos<0.0||ball->yPos>=tWidth){
	    result=1;
	}
    }else if(ball->xPos>=tLength/TWO-sidePWidth/TWO&&ball->xPos<=tLength/TWO+sidePWidth/TWO){
	if(ball->yPos>=tWidth||ball->yPos<0.0){
	    result=1;
	}
    }else if(ball->yPos<=cornerPLength||ball->yPos>=tWidth-cornerPLength){
	if(ball->xPos<0.0||ball->xPos>=tLength)result=1;
    }

    return result;
}

/*calculates the friction percent for the balls velocity*/
double frictionPercent(struct BallData *ball){
    double percent,dV,V;
    dV=mu*G_IPS2*ball->table->dt;
    V=sqrt((ball->xVel)*(ball->xVel)+(ball->yVel)*(ball->yVel));
    if(dV>=V){
	percent=0;
    }else{
	percent=1-(dV/V);
    }
    return percent;
}

/*reflects the ball off the left rail*/
void reflectLeft(struct BallData *ball){
    double intrude=(-1.0)*(ball->xPos-bRadius);
    ball->xPos+=TWO*intrude;
    ball->xVel=((-1.0)*ball->xVel)/TWO;
    ball->yVel=(ball->yVel)/TWO;
}

/*reflects the ball off the right rail*/
void reflectRight(struct BallData *ball){
    double intrude=ball->xPos+bRadius-tLength;
    ball->xPos-=TWO*intrude;
    ball->xVel=((-1.0)*ball->xVel)/TWO;
    ball->yVel=(ball->yVel)/TWO;
}

/*reflects the ball off the top rail*/
void reflectTop(struct BallData *ball){
    double intrude=ball->yPos+bRadius-tWidth;
    ball->yPos-=TWO*intrude;
    ball->yVel=((-1.0)*ball->yVel)/TWO;
    ball->xVel=(ball->xVel)/TWO;
}

/*reflects teh ball off the bottom rail*/
void reflectBottom(struct BallData *ball){
    double intrude=(-1.0)*(ball->yPos-bRadius);
    ball->yPos+=TWO*intrude;
    ball->yVel=((-1.0)*ball->yVel)/TWO;
    ball->xVel=(ball->xVel)/TWO;
}

/*determines if ball is in the left rail*/
int inLeftRail(struct BallData *ball){
    int result=0;
    if(ball->xPos<bRadius){
	if(ball->yPos>cornerPLength&&ball->yPos<tWidth-cornerPLength) result=1;
    }
    return result;
}

/*determines if ball is in right rail*/
int inRightRail(struct BallData *ball){
    int result=0;
    if(ball->xPos>tLength-bRadius){
	if(ball->yPos>cornerPLength&&ball->yPos<tWidth-cornerPLength) result=1;
    }
    return result;
}

/*determines if ball is in top rail*/
int inTopRail(struct BallData *ball){
    int result=0;
    if(ball->yPos>tWidth-bRadius){
	if(ball->xPos>=cornerPLength&&ball->xPos<=tLength-cornerPLength){
	    if(ball->xPos<=tLength/2-sidePWidth/2||ball->xPos>=tLength/2+sidePWidth/2)result=1;
	}
    }
    return result;
}

/*determines if ball is in bottom rail*/
int inBottomRail(struct BallData *ball){
    int result=0;
    if(ball->yPos<bRadius){
	if(ball->xPos>cornerPLength&&ball->xPos<tLength-cornerPLength){
	    if((ball->xPos<=(tLength/2-sidePWidth/2))||(ball->xPos>=(tLength/2+sidePWidth/2)))result=1;
	}
    }
    return result;
}

/*determines the frame time for the x velocity*/
double frameTimeX(struct BallData *ball){
    double fDT,xVel=ball->xVel;

    if(xVel<0){
	xVel=(-1.0)*xVel;
    }
    if(xVel==0){
	fDT=smoothTime;
    }else{
	fDT=0.5*bRadius/xVel;
	if(fDT>smoothTime){
	    fDT=smoothTime;
	}
    }
    return fDT;
}

/*determines the frame time for the y velocity*/
double frameTimeY(struct BallData *ball){
    double fDT,yVel=ball->yVel;

    if(yVel<0){
	yVel=(-1.0)*yVel;
    }
    if(yVel==0){
	fDT=smoothTime;
    }else{
	fDT=0.5*bRadius/yVel;
	if(fDT>smoothTime){
	    fDT=smoothTime;
	}
    }
    return fDT;
}
