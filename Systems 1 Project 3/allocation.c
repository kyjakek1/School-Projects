/*Jake Kennedy Lab 3 Allocation File*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "linkedlist.h"
#include "debug.h"

/*dynamically allocates a BallData structure and returns a pointer to it*/
struct BallData *allocateBall(struct BallData *ball){
    static int count=0;
    struct BallData *p1;
    p1=malloc(sizeof(struct BallData));
    if(p1!=0){
	count++;
	if(TEXT) printf("DIAGNOSTIC: %d balls allocated.\n",count);
    }
    return p1;
}

/*frees a dynamic structure*/
void freeBall(void *data){
    static int count=0;
    struct BallData *freed=data;
    free(freed);
    freed=NULL;
    count++;
    if(TEXT) printf("DIAGNOSTIC: %d balls freed.\n",count);
}
