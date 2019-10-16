#include <iostream>
#include <string>
#include <queue>

#include "STLqueueWrapper.h"


STLQueue::statusCode STLQueue::queue::enqueue(std::string addMe) {
	int tempSize = Queue.size();
	Queue.push(addMe);
	// if the last element = the add me then it as pushed correctly if it wasnt then the test was show the the queues dont line up
	if ( addMe != Queue.back()) { // check to make sure it was added
		return FAILURE;
	}
	else {
		return SUCCESS;
	}
}

STLQueue::statusCode STLQueue::queue::dequeue(std::string &returnedElement) {
	// if it is empty it cant pop
	if (isEmpty())
	{
		return FAILURE;
	}

	returnedElement = Queue.front();
	Queue.pop();
	return SUCCESS;
}

STLQueue::statusCode STLQueue::queue::peek(std::string &returnedElement) const{
	if (isEmpty())
	{
		return FAILURE;
	}

	returnedElement = Queue.front();
	return SUCCESS;
}