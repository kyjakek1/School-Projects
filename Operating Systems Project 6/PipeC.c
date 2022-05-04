/*Jake Kennedy CSE 2431 Lab6*/
/*Part B, PipeC.c File*/
/*COMPILED USING gcc -std=c99 -pedantic -o PipeC PipeC.c*/

#define _XOPEN_SOURCE 500
#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int res,x1,x2,fd[2],procB,procC,procD;
 
    /*create pipe*/ 
    x1=pipe(fd);
    if(x1<0){printf("Error creating pipe\n");exit(-1);}

    /*Allocate space for fid string and convert write fid to string*/
    char *fid1=malloc(sizeof(fd[1]));
    snprintf(fid1,sizeof(fd[1]),"%d",fd[1]); 
    /*Allocate space for fid string and convert read fid to screen*/
    char *fid0=malloc(sizeof(fd[0]));
    snprintf(fid0,sizeof(fd[0]),"%d",fd[0]);
    /*initialize args for exec call*/
    char *arg1[2]={fid1,0};
    char *arg0[2]={fid0,0};

    /*fork to create process B*/
    procB=fork();
    if(procB<0){printf("Error using fork\n");exit(-1);}

    /*if in process B*/
    if(procB==0){
	/*close reading pipe*/
	close(fd[0]);
	/*execute PipeW1 file*/
	execv("PipeW1",arg1);
	perror("execv");
	printf("Child execv error\n");
	exit(-1);	
    }

    /*fork to create process C*/
    procC=fork();
    if(procC<0){printf("Error using fork\n");exit(-1);}

    /*if in process C*/
    if(procC==0){
	/*close reading pipe*/
	close(fd[0]);
	/*execute PipeW2 file*/
	execv("PipeW2",arg1);
	perror("execv");
	printf("Child execv error\n");
	exit(-1);
    }

    /*fork to create process D*/
    procD=fork();
    if(procD<0){printf("Error using fork\n");exit(-1);}

    /*if in process D*/
    if(procD==0){
	/*close writing pipe*/
	close(fd[1]);
	/*execute PipeR file*/
	execv("PipeR",arg0);
	perror("execv");
	printf("Child execv error\n");
	exit(-1);
    }
    /*close rest of pipe*/
    close(fd[0]);
    close(fd[1]);
    /*free allocated space*/
    free(fid0);
    free(fid1);
    exit(0);
}

/*CODE OUTPUT FROM CONSOLE
[kennedy.1138@cse-sl4 Lab6]$ PipeC
[kennedy.1138@cse-sl4 Lab6]$ 001aaa002aaa003aaa004aaa005aaa006aaa007aaa008aaa009aaa010aaa011aaa012aaa013aaa014aaa015aaa016aaa017a
aa018aaa019aaa020aaa021aaa022aaa023aaa024aaa025aaa026aaa027aaa028aaa029aaa030aaa031aaa032aaa033aaa03
4aaa035aaa036aaa037aaa038aaa039aaa040aaa041aaa042aaa043aaa044aaa045aaa046aaa047aaa048aaa049aaa050aaa
051aaa052aaa053aaa054aaa055aaa056aaa057aaa058aaa059aaa060aaa061aaa062aaa063aaa064aaa065aaa066aaa067a
aa068aaa069aaa070aaa071aaa072aaa073aaa074aaa075aaa076aaa077aaa078aaa079aaa080aaa081aaa082aaa083aaa08
4aaa085aaa086aaa087aaa088aaa089aaa090aaa091aaa092aaa093aaa094aaa095aaa096aaa097aaa098aaa099aaa100aaa
Ax0Bx0Cx0Dx0Ex0Fx0Gx0Hx0Ix0Jx0Kx0Lx0Mx0Nx0Ox0Px0Qx0Rx0Sx0Tx0Ux0Vx0Wx0Xx0Yx0Zx0Ax1Bx1Cx1Dx1Ex1Fx1Gx1H
x1Ix1Jx1Kx1Lx1Mx1Nx1Ox1Px1Qx1Rx1Sx1Tx1Ux1Vx1Wx1Xx1Yx1Zx1Ax2Bx2Cx2Dx2Ex2Fx2Gx2Hx2
101aaa102aaa103aaa104aaa105aaa106aaa107aaa108aaa109aaa110aaa111aaa112aaa
113aaa114aaa115aaa116aaa117aaa118aaa119aaa120aaa121aaa122aaa123aaa124aaa125aaa126aaa127aaa128aaa129a
aa130aaa131aaa132aaa133aaa134aaa
135aaa136aaa137aaa138aaa
139aaa140aaa141aaa
142aaa143aaa144aaa
145aaa146aaa147aaa148aaa
149aaa150aaa151aaa
152aaa153aaa154aaa
155aaa156aaa157aaa
158aaa159aaa160aaa161aaa
162aaa163aaa164aaa
165aaa166aaa167aaa
168aaa169aaa170aaa
171aaa172aaa173aaa174aaa
175aaa176aaa177aaa
178aaa179aaa180aaa
181aaa182aaa183aaa
184aaa185aaa186aaa187aaa
188aaa189aaa190aaa
191aaa192aaa193aaa
194aaa195aaa196aaa
197aaa198aaa199aaa
200aaa
201aaa202aaa203aaa204aaa205aaa206aaa207aaa208aaa209aaa210aaa211aaa212aaa
213aaa214aaa215aaa216aaa217aaa218aaa219aaa220aaa221aaa222aaa223aaa224aaa225aaa226aaa227aaa228aaa229a
aa230aaa231aaa232aaa233aaa234aaa235aaa
236aaa237aaa238aaa
239aaa240aaa241aaa
242aaa243aaa244aaa245aaa
246aaa247aaa248aaa
249aaa250aaa251aaa
252aaa253aaa254aaa
255aaa256aaa257aaa258aaa
259aaa260aaa261aaa
262aaa263aaa264aaa
265aaa266aaa267aaa268aaa
269aaa270aaa271aaa
272aaa273aaa274aaa
275aaa276aaa277aaa
278aaa279aaa280aaa281aaa
282aaa283aaa284aaa
285aaa286aaa287aaa288aaa289aaa290aaa291aaa292aaa293aaa294aaa295aaa296aaa297aaa298aaa299aaa300aaaIx2J
x2Kx2Lx2Mx2Nx2Ox2Px2Qx2Rx2Sx2Tx2Ux2Vx2Wx2Xx2Yx2Zx2Ax3Bx3Cx3Dx3Ex3Fx3Gx3Hx3Ix3Jx3Kx3Lx3Mx3Nx3Ox3Px3Qx
3Rx3Sx3Tx3Ux3Vx3Wx3Xx3Yx3Zx3Ax4Bx4Cx4Dx4Ex4Fx4Gx4Hx4Ix4Jx4Kx4Lx4Mx4Nx4Ox4Px4301aaa302aaa303aaa304aaa
305aaa306aaa307aaa308aaa309aaa310aaa311aaa312aaa313aaa314aaa315aaa316aaa317aaa318aaa319aaa320aaa321a
aa322aaa323aaa324aaa325aaa326aaa327aaa328aaa329aaa330aaa331aaa332aaa333aaa334aaa335aaa336aaa337aaa33
8aaa339aaa340aaa341aaa342aaa343aaa344aaa345aaa346aaa347aaa348aaa349aaa350aaa351aaa352aaa353aaa354aaa
355aaa356aaa357aaa358aaa359aaa360aaa361aaa362aaa363aaa364aaa365aaa366aaa367aaa368aaa369aaa370aaa371a
aa372aaa373aaa374aaa375aaa376aaa377aaa378aaa379aaa380aaa381aaa382aaa383aaa384aaa385aaa386aaa387aaa38
8aaa389aaa390aaa391aaa392aaa393aaa394aaa395aaa396aaa397aaa398aaa399aaa400aaa
401aaa402aaa403aaa404aaa405aaa
406aaa407aaa408aaa409aaa410aaa
411aaa412aaa413aaa
414aaa415aaa416aaa417aaa
418aaa419aaa420aaa
421aaa422aaa423aaa
424aaa425aaa426aaa
427aaa428aaa429aaa430aaa
431aaa432aaa433aaa
434aaa435aaa436aaa
437aaa438aaa439aaa440aaa
441aaa442aaa443aaa
444aaa445aaa446aaa
447aaa448aaa449aaa
450aaa451aaa452aaa
453aaa454aaa455aaa456aaa
457aaa458aaa459aaa
460aaa461aaa462aaa
463aaa464aaa465aaa466aaa
467aaa468aaa469aaa470aaa471aaa472aaa473aaa474aaa475aaa
476aaa477aaa478aaa479aaa
480aaa481aaa482aaa
483aaa484aaa485aaa486aaa
487aaa488aaa489aaa
490aaa491aaa492aaa493aaa
494aaa495aaa496aaa
497aaa498aaa499aaa
500aaa
Qx4Rx4Sx4Tx4Ux4Vx4Wx4Xx4Yx4Zx4Ax5Bx5Cx5Dx5Ex5Fx5Gx5Hx5Ix5Jx5Kx5Lx5Mx5Nx5Ox5Px5Qx5Rx5Sx5Tx5Ux5Vx5Wx5X
x5Yx5Zx5Ax6Bx6Cx6Dx6Ex6Fx6Gx6Hx6Ix6Jx6Kx6Lx6Mx6Nx6Ox6Px6Qx6Rx6Sx6Tx6Ux6Vx6Wx6Xx6
Yx6Zx6Ax7Bx7Cx7Dx7Ex7Fx7Gx7Hx7Ix7Jx7Kx7Lx7Mx7Nx7Ox7Px7Qx7Rx7Sx7Tx7Ux7Vx7Wx7Xx7Yx7Zx7Ax8Bx8Cx8Dx8Ex8F
x8Gx8Hx8Ix8Jx8Kx8Lx8Mx8Nx8Ox8Px8Qx8Rx8Sx8Tx8Ux8Vx8Wx8Xx8Yx8Zx8Ax9Bx9Cx9Dx9Ex9Fx9
Gx9Hx9Ix9Jx9Kx9Lx9Mx9Nx9Ox9Px9Qx9Rx9Sx9Tx9Ux9Vx9Wx9Xx9Yx9Zx9

Process D: There were 93 issued read statements and
3780 characters read from the pipe and 3780 characters written to the screen

*/
