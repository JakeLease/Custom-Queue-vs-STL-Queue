#pragma once

#ifndef H_STLQUEUEWRAPPER
#define H_STLQUEUEWRAPPER
// wrapper class for std::queue
namespace STLQueue {
	enum statusCode { SUCCESS, FAILURE };
	class queue;
}

class STLQueue::queue {
private:
	// creates STL queue
	std::queue<std::string> Queue;

public:

	inline bool isEmpty() const { return Queue.empty(); }
	statusCode enqueue(std::string addMe);
	statusCode dequeue(std::string &returnedElement);
	statusCode peek(std::string &returnedElement) const;
};

#endif