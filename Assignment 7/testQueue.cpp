#include <iostream>
#include <string>
#include <fstream>
#include <queue>

#include "queueBase.h"
#include "testQueue.h"
#include "STLqueueWrapper.h"

void testStack(std::string filename) {

	// input filename
	std::string fname = filename;
	
	int passFail = testStream(fname);

	// check if error or passes
	if (passFail == 0) {
		std::cout << "All Instructions passed the test" << std::endl;
	}
	else {
		std::cout << "The instruction on line " << passFail << " of file " << fname << " failed due to not all queues being the same." << std::endl;
	}

}

int testStream(std::string fileName) {
	// initialize queues
	queueBase::queue q1;
	queueBase::queue q2;
	STLQueue::queue STLq;

	// open file
	std::string filename = fileName;
	std::ifstream file(filename);


	// read file
	std::string letterInstructions;
	// loop through file
	int lineNum = 0; // keepst track of file line
	while (file >> letterInstructions) {
		++lineNum;

		// A instructions
		if (letterInstructions == "A") {
			std::string storeNum;
			file >> storeNum;
			// check how many of the queues pass or fail
			// shouldnt need this anymore since all dynamically allocated but keeping as extra protection
			int errorNum = 0;
			if (queueBase::FAILURE == q1.enqueue(storeNum)) { ++errorNum; }
			if (queueBase::FAILURE == q2.enqueue(storeNum)) { ++errorNum; }
			if (queueBase::FAILURE == STLq.enqueue(storeNum)) { ++errorNum; }

			// check if theres one 1 or 2 errors
			else if (errorNum == 1 || errorNum == 2) {
				return lineNum;
			}
		}

		// P instructions
		else if (letterInstructions == "P") {
			// returnElements for peek
			std::string q1peek, q2peek, q3peek;

			// check how many queues pass or fail
			int errorNum = 0;

			if (queueBase::FAILURE == q1.peek(q1peek)) { ++errorNum; }
			if (queueBase::FAILURE == q2.peek(q2peek)) { ++errorNum; }
			if (queueBase::FAILURE == STLq.peek(q3peek)) { ++errorNum; }

			// check if theres one 1 or 2 errors
		    if (errorNum == 1 || errorNum == 2) { 
				return lineNum;
			}
			// if 3 failures then no need to test
			if (errorNum != 3) {
				if (q1peek != q2peek || q2peek != q3peek || q3peek != q1peek) {
					return lineNum;
				}
			}

			// check if returnedElements are equal 
			
		}

		else if (letterInstructions == "D") {
			// returnElements for pop
			std::string q1pop, q2pop, q3pop;

			// check how many queues pass or fail
			int errorNum = 0;

			if (queueBase::FAILURE == q1.dequeue(q1pop)) { ++errorNum; }
			if (queueBase::FAILURE == q2.dequeue(q2pop)) { ++errorNum; }
			if (queueBase::FAILURE == STLq.dequeue(q3pop)) { ++errorNum; }

			// check if theres one 1 or 2 errors
			if (errorNum == 1 || errorNum == 2) {
				return lineNum;
			}

			// check if returnedElements are equal 
			if (errorNum != 3) {
				if (q1pop != q2pop || q2pop != q3pop || q3pop != q1pop) {
					return lineNum;
				}
			}
			
		}
		else if (letterInstructions == "E") {
			// check if all queues isEmpty are equal
			if(q1.isEmpty() != q2.isEmpty() || q1.isEmpty() != STLq.isEmpty() || q2.isEmpty() != STLq.isEmpty()) {
				return lineNum;
			}
		}
	}
	file.close();
	return 0;
}