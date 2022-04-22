#include "linkedstack.h"

StackNode	*popLS(LinkedStack* pStack)
{
	StackNode	*popNode = calloc(1, sizeof(StackNode));
	StackNode	*delNode;

	NULLCHECK(pStack);
	NULLCHECK(popNode);
	// is empty
	if (isLinkedStackEmpty(pStack))
		return (NULL);
	delNode = pStack->pTopElement;
	if (pStack->currentElementCount == 1)
	{
		popNode->data = delNode->data;
		popNode->pLink = delNode->pLink;
		free(delNode);
		delNode = NULL;
		pStack->pTopElement = NULL;
	}
	else
	{
		popNode->data = delNode->data;
		popNode->pLink = delNode->pLink;
		pStack->pTopElement = delNode->pLink;
		free(delNode);
		delNode = NULL;
	}
	pStack->currentElementCount--;
	return (popNode);
}