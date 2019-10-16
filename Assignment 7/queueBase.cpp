#include <iostream>
#include <string>
#include "queueBase.h"
#include <new>


// default CTOR
// uses an initialization list
queueBase::queue::queue() 
	:
	oldestIndex(0),
	nextInsertIndex(0),
	currentBufferSize(INITIAL_QUEUE_SIZE)
{
	data = new std::string[currentBufferSize]; // allocate array data
}

//Rule of Three operator=
queueBase::queue & queueBase::queue::operator=(queue copyMe) {
	currentBufferSize = copyMe.currentBufferSize;
	oldestIndex = copyMe.oldestIndex;
	nextInsertIndex = copyMe.nextInsertIndex;
	std::string *temp = data;
	data = copyMe.data;
	copyMe.data = temp;
	return *this;
}
// copy CTOR
queueBase::queue::queue(const queue& copyMe) 
	:
	oldestIndex(copyMe.oldestIndex), // since we're loading into the array from [0], this will stay 0
	nextInsertIndex(copyMe.nextInsertIndex), // will end up as count of items
	currentBufferSize(copyMe.currentBufferSize)
{
	// set oldestIndex, set nextInsertIndex
	// copy the items
	data = new std::string[currentBufferSize]; //allocate array data
	for (int i = copyMe.oldestIndex; i != copyMe.nextInsertIndex; i = copyMe.advanceIndex(i)) {
		// copy the item in position i in copyMe into my position nextInsertIndex
		data[nextInsertIndex] = copyMe.data[i];
		nextInsertIndex = advanceIndex(nextInsertIndex); // really this could be ++ since we never hit the end
	}
	// now nextInsert IS THE COUNT and points to the first free spot
}

//Dtor
queueBase::queue::~queue() {
	delete[] data;
}



queueBase::statusCode queueBase::queue::enqueue(std::string addMe) {
	// if its full, FAIL
	if (isFull()) {
		std::string *temp; // temp data storage

		int newCapacity = 2 * currentBufferSize; // new array size

		// check for exception
		try {
			temp = new std::string[newCapacity];
			std::cerr << "\tReallocating:  buffer-old size = " << currentBufferSize << std::endl;
			std::cerr << "\tReallocating Complete: buffer-new size = " << newCapacity << std::endl;
		}
		catch (std::bad_alloc& ba) { 
			std::cerr << "Bad_alloc caught: " << ba.what() << std::endl;
			return FAILURE;
		}
	
		// loop and add data but make sure oldest is in slot 0 in new queue
		for (int i = 0; oldestIndex !=nextInsertIndex; ++i) {
			temp[i] = data[oldestIndex];
			oldestIndex = advanceIndex(oldestIndex);
		}
		// delete old data
		delete[] data; // return data

		// incert temp into data
		data = temp;
		oldestIndex = 0; // set oldest to 0
		// sets next insert as the last buffer size - 1 since the last element location put into new array will be 2 less than last buffer size, we minus one for next insert
		std::cout << currentBufferSize << " " << nextInsertIndex << std::endl;
		nextInsertIndex = currentBufferSize - 1;
		
		currentBufferSize = newCapacity; // replaces the old buffer size with new one
		std::cout << currentBufferSize << " " << nextInsertIndex << std::endl;

		
	}
	// put the item
	data[nextInsertIndex] = addMe;
	// account for the new item: Note--this is circular
	nextInsertIndex = advanceIndex(nextInsertIndex);
	// return
	return SUCCESS;
}
queueBase::statusCode queueBase::queue::dequeue(std::string &returnedElement) {
	// if empty, fail
	if (isEmpty()) {
		return FAILURE;
	}
	// put the oldest item into returned element
	returnedElement = data[oldestIndex];
	// account for the fact that we're deleting our oldest item (i.e., Remove the oldest)
	oldestIndex = advanceIndex(oldestIndex);
	// return
	return SUCCESS;
}
queueBase::statusCode queueBase::queue::peek(std::string &returnedElement) const {
	// if empty, fail
	if (isEmpty()) {
		return FAILURE;
	}
	// put the oldest item into returned element
	returnedElement = data[oldestIndex];
	// return
	return SUCCESS;
}