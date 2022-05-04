/*Jake Kennedy static block variable prototype*/
#include <stdio.h>

void sCounter(int entry){
    static int count=0;
    if(entry)count++;
    printf("Entry=%d",count);
}

int main(){
    int loop,i,entry=1,predictedCount=0;
    printf("Please enter a number of loops\n");
    scanf("%d",&loop);
    for(i=0;i<loop;i++){
        sCounter(entry);
        if(entry)predictedCount++;
	entry=!entry;
    }
    printf("Expected value of entry was %d\n",predictedCount);
    return 0;
}
