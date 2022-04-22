#ifndef _LINKED_STACK_
#define _LINKED_STACK_


#include <stdio.h>
#include <stdlib.h>

typedef struct StackNodeType
{
	char data;
	struct StackNodeType	*pLink;
} StackNode;

typedef struct ArrayStackType
{
	int currentElementCount;
	int	maxElementCount;
	StackNode	*pTopElement;
} ArrayStack;

void 		deleteArrayStack(ArrayStack* pStack);
ArrayStack	*createArrayStack(int maxElementCount);

StackNode	*peekAS(ArrayStack *pStack);
StackNode	*popAS(ArrayStack *pStack);
int 		pushAS(ArrayStack *pStack, StackNode element);

int 		isArrayStackFull(ArrayStack* pStack);
int 		isArrayStackEmpty(ArrayStack* pStack);

// additional
void		displayArrayStack(ArrayStack *pStack);
void		NULLCHECK(void *ptr);
int			SAME(int x, int y);
int			ZERO(int x);
#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#endif