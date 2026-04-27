#ifndef CONCURRENT_STACK_UNBOUND_H
#define CONCURRENT_STACK_UNBOUND_H

#include <stdlib.h>

// A structure to represent a stack
// here we use a linked list to represent the unbound stack
struct CStackNode {
    int data;
    struct StackNode * next;
};

struct CStackNode * newNode(int data);

int     conc_isEmpty     (struct CStackNode*  root);
void    conc_push        (struct CStackNode** root, int data); 
int     conc_pop         (struct CStackNode** root);
int     conc_top         (struct CStackNode*  root);
void    conc_stackFree   (struct CStackNode*  root);

#endif /* CONCURRENT_STACK_H */