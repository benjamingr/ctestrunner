#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#define ok(...) __ok_hidden((ok_hidden_args){__VA_ARGS__});
#define equal(...) __equal_hidden((equal_hidden_args){__VA_ARGS__});
#include "add.h"
typedef struct { bool predicate; char * message;} ok_hidden_args;
typedef struct { void * first; void * second; char * message;} equal_hidden_args;

void __ok_hidden(ok_hidden_args inp) {
    inp.message= inp.message ? inp.message : "";
    printf("%s",inp.message);
    if(!inp.predicate) exit(-1); 
}
                  

void __equal_hidden(equal_hidden_args inp) {
    inp.message= inp.message ? inp.message : "";
    printf("%s",inp.message);
    if(inp.first != inp.second) { printf("\nExpected %d to be equal %d",inp.first,inp.second);exit(-1); }
}
                  
int main(void){ 
    equal(10,10,"10 is 10");    return 0;
}
