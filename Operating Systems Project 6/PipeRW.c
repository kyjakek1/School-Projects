/*Jake Kennedy CSE 2431 Lab6*/
/*Part A, PipeRW.c File*/
/*COMPILED USING gcc -std=c99 -pedantic -o PipeRW PipeRW.c*/

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
    int i,x1,x2,fd[2],procB,procC,writeRes;

    /*Create Pipe*/
    x1=pipe(fd);
    if(x1<0){printf("Error creating pipe\n");exit(-1);}

    /*fork to create process B*/
    procB=fork();
    if(procB<0){printf("Error using fork\n");exit(-1);}

    /*if in process B*/
    if(procB==0){
	char bufferB[6]="001aaa";
	close(fd[0]); //close read pipe
	/*iterate 500 times writing buffer to the pipe*/
	for(i=1;i<501;i++){
	    writeRes=write(fd[1],bufferB,6);
	    if(writeRes<0){printf("Error writing to pipe\n");exit(-1);}
	    /*increment the buffer by incrementing each char and checking if next place needs to be incremented/reset*/
	    bufferB[2]++;
	    if(bufferB[2]>'9'){
		bufferB[2]='0';
		bufferB[1]++;
		if(bufferB[1]>'9'){
		    bufferB[1]='0';
		    bufferB[0]++;
		}
	    }
	    /*sleep every 100 loops*/
	    if(i%100==0)usleep(100000);	
	}
	exit(0);	
    }

    /*fork to create process C*/
    procC=fork();
    if(procC<0){printf("Error using fork\n");exit(-1);}

    /*if in process C*/
    if(procC==0){
	char bufferC[3]="Ax0";
	close(fd[0]); //close read pipe
	/*iterate 260 times writing buffer to the pipe*/
	for(i=1;i<261;i++){
	    writeRes=write(fd[1],bufferC,3);
	    if(writeRes<0){printf("Error writing to pipe\n");exit(-1);}

	    /*increment the buffer by incrementing each char and checking if next place needs to be incremented/reset*/
	    bufferC[0]++;
	    if(bufferC[0]>'Z'){
		bufferC[0]='A';
		bufferC[2]++;
		if(bufferC[2]>'9'){
		    bufferC[2]='0';
		}
	    }
	    /*sleep every 60 loops*/	
	    if(i%60==0)usleep(300000);
	}
	exit(0);
    }
    /*in Process A close pipe for writing*/
    close(fd[1]);
    char bufferA[100];
    int readCount,loop=1,writtenCount=0,j=0,totalReadCount=0;
    
    /*loop until process B and C are terminated and pipe is empty*/
    while(loop){
	/*read from pipe*/
	readCount=read(fd[0],bufferA,100);
	if(readCount<0){printf("Error reading from pipe\n");exit(-1);}

	/*keep track of number of reads and chars read*/
	j++;
	totalReadCount+=readCount;
	/*if pipe is not empty*/
	if(readCount>0){
	    /*write results to screen*/
	    writeRes=write(1,bufferA,readCount);
	    if(writeRes<0){printf("Error writing to screen\n");exit(-1);}
	    printf("\n");
	
	    /*keep track of number of chars written*/
	    writtenCount+=writeRes;
	}else{
	    /*if pipe is empty break loop*/
	    loop=0;
	}
	/*sleep every 50 loops*/
	if(j%50==0) usleep(200000);
    }
    printf("\nProcess A: There were %d issued read statements and\n%d characters read from the pipe and %d characters written to the screen\n",j,totalReadCount,writtenCount); 
    exit(0);
}

/*CODE OUTPUT FROM CONSOLE
[kennedy.1138@cse-sl4 Lab6]$ PipeRW
001aaaAx0Bx0002aaaCx0003aaa
Dx0004aaaEx0005aaaFx0006aaaGx0007aaaHx0008aaaIx0009aaaJx0010aaaKx0011aaaLx0012aaaMx0013aaaNx0014aaaO
x0015aaaPx0016aaaQx0017aaaRx0018aaaSx0019aaaTx0020aaaUx0021aaaVx0022aaaWx0023aaaXx0024aaaYx0025aaa
Zx0026aaaAx1027aaaBx1028aaa
Cx1029aaaDx1030aaaEx1031aaa
Fx1032aaaGx1033aaaHx1034aaa
Ix1035aaaJx1036aaaKx1037aaa
038aaaLx1039aaaMx1040aaaNx1
041aaaOx1042aaaPx1043aaaQx1
044aaaRx1045aaaSx1046aaaTx1
047aaaUx1048aaaVx1049aaaWx1
050aaaXx1051aaaYx1052aaaZx1
053aaaAx2054aaaBx2055aaaCx2
056aaaDx2057aaaEx2058aaaFx2
059aaaGx2060aaaHx2061aaa
062aaa063aaa064aaa
065aaa066aaa067aaa068aaa
069aaa070aaa071aaa
072aaa073aaa074aaa
075aaa076aaa077aaa
078aaa079aaa080aaa
081aaa082aaa083aaa084aaa
085aaa086aaa087aaa
088aaa089aaa090aaa
091aaa092aaa093aaa094aaa
095aaa096aaa097aaa098aaa099aaa100aaa
101aaa102aaa103aaa104aaa105aaa106aaa107aaa108aaa
109aaa110aaa111aaa112aaa113aaa114aaa115aaa116aaa117aaa118aaa119aaa120aaa121aaa122aaa123aaa
124aaa125aaa126aaa
127aaa128aaa129aaa
130aaa131aaa132aaa133aaa
134aaa135aaa136aaa
137aaa138aaa139aaa
140aaa141aaa142aaa
143aaa144aaa145aaa146aaa
147aaa148aaa149aaa
150aaa151aaa152aaa
153aaa154aaa155aaa
156aaa157aaa158aaa
159aaa160aaa161aaa
162aaa163aaa164aaa165aaa
166aaa167aaa168aaa
169aaa170aaa171aaa
172aaa173aaa174aaa175aaa
176aaa177aaa178aaa
179aaa180aaa181aaa
182aaa183aaa184aaa
185aaa186aaa187aaa
188aaa189aaa190aaa
191aaa192aaa193aaa194aaa
195aaa196aaa197aaa198aaa199aaa200aaa201aaa202aaa203aaa204aaa205aaa206aaa207aaa208aaa209aaa210aaa211a
aa212aaa213aaa214aaa215aaa216aaa217aaa218aaa219aaa220aaa221aaa222aaa223aaa224aaa225aaa226aaa227aaa22
8aaa229aaa230aaa231aaa232aaa233aaa234aaa235aaa236aaa237aaa238aaa239aaa240aaa241aaa242aaa243aaa244aaa
245aaa246aaa247aaa248aaa249aaa250aaa251aaa252aaa253aaa254aaa255aaa256aaa257aaa258aaa259aaa260aaa261a
aa262aaa263aaa264aaa265aaa266aaa267aaa268aaa269aaa270aaa271aaa272aaa273aaa274aaa275aaa276aaa277aaa27
8aaa279aaa280aaa281aaa282aaa283aaa284aaa285aaa286aaa287aaa288aaa289aaa290aaa291aaa292aaa293aaa294aaa
295aaa296aaa297aaa298aaa299aaa300aaaIx2Jx2Kx2Lx2Mx2Nx2Ox2Px2Qx2Rx2Sx2Tx2Ux2Vx2Wx2Xx2Yx2Zx2Ax3Bx3Cx3D
x3Ex3Fx3Gx3Hx3Ix3Jx3Kx3Lx3Mx3Nx3Ox3Px3Qx3Rx3Sx3Tx3Ux3Vx3Wx3Xx3Yx3Zx3Ax4Bx4Cx4Dx4Ex4Fx4Gx4Hx4Ix4Jx4Kx
4Lx4Mx4Nx4Ox4Px4
301aaa302aaa303aaa304aaa305aaa306aaa307aaa308aaa
309aaa310aaa311aaa312aaa313aaa314aaa315aaa316aaa317aaa
318aaa319aaa320aaa
321aaa322aaa323aaa
324aaa325aaa326aaa
327aaa328aaa329aaa330aaa
331aaa332aaa333aaa
334aaa335aaa336aaa
337aaa338aaa339aaa
340aaa341aaa342aaa
343aaa344aaa345aaa346aaa
347aaa348aaa349aaa
350aaa351aaa352aaa
353aaa354aaa355aaa
356aaa357aaa358aaa
359aaa360aaa361aaa362aaa
363aaa364aaa365aaa
366aaa367aaa368aaa
369aaa370aaa371aaa
372aaa373aaa374aaa
375aaa376aaa377aaa378aaa
379aaa380aaa381aaa
382aaa383aaa384aaa
385aaa386aaa387aaa
388aaa389aaa390aaa391aaa
392aaa393aaa394aaa
395aaa396aaa397aaa
398aaa399aaa400aaa
401aaa402aaa403aaa404aaa405aaa406aaa407aaa408aaa409aaa410aaa411aaa412aaa413aaa414aaa415aaa416aaa417a
aa418aaa419aaa420aaa421aaa422aaa423aaa424aaa425aaa426aaa427aaa428aaa429aaa430aaa431aaa432aaa433aaa43
4aaa435aaa436aaa437aaa438aaa439aaa440aaa441aaa442aaa443aaa444aaa445aaa446aaa447aaa448aaa449aaa450aaa
451aaa452aaa453aaa454aaa455aaa456aaa457aaa458aaa459aaa460aaa461aaa462aaa463aaa464aaa465aaa466aaa467a
aa468aaa469aaa470aaa471aaa472aaa473aaa474aaa475aaa476aaa477aaa478aaa479aaa480aaa481aaa482aaa483aaa48
4aaa485aaa486aaa487aaa488aaa489aaa490aaa491aaa492aaa493aaa494aaa495aaa496aaa497aaa498aaa499aaa500aaa
Qx4Rx4Sx4Tx4Ux4Vx4Wx4
Xx4Yx4Zx4Ax5Bx5Cx5Dx5Ex5Fx5Gx5Hx5Ix5Jx5Kx5Lx5Mx5
Nx5Ox5Px5
Qx5Rx5Sx5
Tx5Ux5Vx5Wx5
Xx5Yx5Zx5
Ax6Bx6Cx6
Dx6Ex6Fx6Gx6Hx6Ix6Jx6Kx6Lx6Mx6Nx6Ox6Px6Qx6Rx6Sx6Tx6Ux6Vx6Wx6Xx6
Yx6Zx6Ax7Bx7Cx7Dx7Ex7Fx7Gx7Hx7
Ix7Jx7Kx7Lx7Mx7Nx7Ox7Px7Qx7Rx7Sx7Tx7Ux7Vx7Wx7Xx7
Yx7Zx7Ax8
Bx8Cx8Dx8
Ex8Fx8Gx8
Hx8Ix8Jx8Kx8
Lx8Mx8Nx8
Ox8Px8Qx8
Rx8Sx8Tx8
Ux8Vx8Wx8Xx8
Yx8Zx8Ax9
Bx9Cx9Dx9
Ex9Fx9
Gx9Hx9Ix9Jx9Kx9Lx9Mx9Nx9Ox9Px9Qx9Rx9Sx9Tx9Ux9Vx9Wx9Xx9Yx9Zx9

Process A: There were 116 issued read statements and
3780 characters read from the pipe and 3780 characters written to the screen
*/
