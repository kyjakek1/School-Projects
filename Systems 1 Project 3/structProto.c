/*Jake Kennedy Struct Prototype*/
#include <stdio.h>

struct BallData{
	int ballNum;
	double xPos,yPos,xVel,yVel;
};

void dummy(struct BallData *uno){
    printf("%d \n",uno->ballNum);
    printf("%lf \n",uno->xPos);
    printf("%lf \n",uno->yPos);
    printf("%lf \n",uno->xVel);
    printf("%lf \n",uno->yVel);
}

int main(){
    struct BallData foo;
    struct BallData *uno;
    uno=&foo;
    uno->ballNum=1;
    uno->xPos=4.0;
    uno->yPos=5.0;
    uno->xVel=0.0;
    uno->yVel=3.0;
    dummy(uno);

    return 0;
}
