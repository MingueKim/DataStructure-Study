#include "simulation.h"

void	insertCustomer(int arrivalTime, int processTime, LinkedQueue *pQueue)
{
	SimCustomer	*newCustomer;
	QueueNode	*newNode;

	if (NULLCHECK(pQueue))
		return ;

	newCustomer = calloc(1, sizeof(SimCustomer));
	if (!newCustomer)
		return ;
	newNode = calloc(1, sizeof(QueueNode));
	if (!newNode)
	{
		free(newCustomer);
		return ;
	}
	newCustomer->arrivalTime = arrivalTime;
	newCustomer->serviceTime = processTime;
	newCustomer->status = arrival;
	newNode->customerData = newCustomer;
	if (isLinkedQueueEmpty(pQueue))
	{
		pQueue->pFrontNode = newNode;
		pQueue->pRearNode = newNode;
	}
	else
	{
		pQueue->pRearNode->pRLink = newNode;
		pQueue->pRearNode = newNode;
	}
	pQueue->currentElementCount++;
}

void	processArrival(int currentTime, LinkedQueue *pArrivalQueue, LinkedQueue *pWaitQueue)
{
	QueueNode	*frontNode;

	if (!pArrivalQueue || !pWaitQueue || isLinkedQueueEmpty(pArrivalQueue))
		return ;
	while (pArrivalQueue->pFrontNode->customerData->arrivalTime <= currentTime)
	{
		frontNode = deleteLQ(pArrivalQueue);
		insertLQ(pWaitQueue, *frontNode);
		free(frontNode);
		if (isLinkedQueueEmpty(pArrivalQueue))
			break ;
	}
}

QueueNode	*processServiceNodeStart(int currentTime, LinkedQueue *pWaitQueue)
{
	QueueNode	*frontNode;
	SimCustomer	*customer;

	if (!pWaitQueue || isLinkedQueueEmpty(pWaitQueue))
		return (NULL);
	if (currentTime < pWaitQueue->pFrontNode->customerData->arrivalTime)
		return (NULL);
	frontNode = pWaitQueue->pFrontNode;
	customer = frontNode->customerData;
	customer->startTime = currentTime;
	customer->endTime = customer->startTime + customer->serviceTime;
	customer->status = start;
	pWaitQueue->pFrontNode = frontNode->pRLink;
	pWaitQueue->currentElementCount--;
	return (frontNode);
}

QueueNode	*processServiceNodeEnd(int currentTime, QueueNode *pServiceNode, int *pServiceUserCount, int *pTotalWaitTime)
{
	QueueNode	*frontNode;
	SimCustomer	*customer;

	customer = pServiceNode->customerData;
	*pServiceUserCount += 1;
	*pTotalWaitTime += customer->startTime - customer->arrivalTime;
	customer->status = end;
	return (pServiceNode);
}

void	printSimCustomer(int currentTime, SimCustomer customer)
{
	printf("current Time = %d\n", currentTime);
	printf("Customer has arrived :%d\n", customer.arrivalTime);
	printf("Required Service Time :%d\n", customer.serviceTime);
	printf("Customer waited for %d\n", currentTime - customer.arrivalTime);
	printf("========================================\n");
}

void	printWaitQueueStatus(int currentTime, LinkedQueue *pWaitQueue)
{
	QueueNode	*frontNode;
	int			idx = 0;

	if (isLinkedQueueEmpty(pWaitQueue))
	{
		printf("Wait List is Empty\n");
		return ;
	}
	printf("Waiting Queue\n");
	printf("========================================\n");
	frontNode = pWaitQueue->pFrontNode;
	while (frontNode)
	{
		printSimCustomer(currentTime, *(frontNode->customerData));
		frontNode = frontNode->pRLink;
	}
}

void	printReport(LinkedQueue *pWaitQueue, int serviceUserCount, int totalWaitTime)
{
	displayLinkedQueue(pWaitQueue);
	printf("service User Count = %d\n", serviceUserCount);
	printf("total wait time = %d\n", totalWaitTime);
}


int main(void)
{
	LinkedQueue	*arrivalQ = createLinkedQueue();
	LinkedQueue	*waitQ = createLinkedQueue();
	int			currentTime = 0;
	int			endTime = 15;
	
	insertCustomer(0, 3, arrivalQ); 
	insertCustomer(1, 2, arrivalQ); 
	insertCustomer(4, 1, arrivalQ); 
	insertCustomer(5, 1, arrivalQ); 
	insertCustomer(7, 0, arrivalQ); 
	insertCustomer(10, 2, arrivalQ);
	insertCustomer(12, 3, arrivalQ);

	int	totalWaitTime = 0;
	int	serviceUserCount = 0;
	QueueNode *agent = NULL;
	while (currentTime < endTime)
	{
		processArrival(currentTime, arrivalQ, waitQ);
		if (agent && agent->customerData->endTime <= currentTime)
		{
			agent = processServiceNodeEnd(currentTime, agent, &serviceUserCount, &totalWaitTime);
			free(agent);
			agent = NULL;
		}
		if (agent == NULL)
			agent = processServiceNodeStart(currentTime, waitQ);
		printWaitQueueStatus(currentTime, waitQ);
		currentTime++;
	}
	printReport(waitQ, serviceUserCount, totalWaitTime);
	agent->customerData->status;
	return (0);
}