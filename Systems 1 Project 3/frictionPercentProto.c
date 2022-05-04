/*Jake Kennedy Friction Percent Prototype*/
#include <stdio.h>
#include <math.h>

int main(){
    double VX,VY,V,dV,percent;
    scanf("%lf %lf",&VX,&VY);
    V=sqrt(VX*VX+VY*VY);
    dV=.01*386.08858267716*.1;
    if(dV>=V){
	percent=0;
    }else{
	percent=1-dV/V;
    }
    
    VX*=percent;
    VY*=percent;
    printf("Post Friction X Velocity:%.3lf, Y Velocity:%.3lf\n",VX,VY);

    return 0;
}
