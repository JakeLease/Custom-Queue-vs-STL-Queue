// (c) 2019 Jacob Liese all rights reserve
#include <iostream>
#include <string>

#include "queueBase.h"
#include"testQueue.h"
#include "randomStream.h"

int main() {

	bool running = true; 
	// create loop to run till exit
	while (running == true) { 
		int choice;
		// print menu and choices
		std::cout << "Below are options to choose from: " << std::endl;
		std::cout << "	1: Exit" << std::endl;
		std::cout << "	2: Create File" << std::endl;
		std::cout << "	3: Run Test" << std::endl;
		std::cout << "	4: Create File and Run Test" << std::endl;
		std::cout << "Enter one of the options above: ";
		std::cin >> choice;

		// switch statement for choices
		switch (choice){
		case 1: // Exit
		{
			running = false;
			break;
		}
		case 2: // create file and run randomStream
		{
			randomStream(iterationSet(), nameFile());
			break;
		}
		case 3: // run test
		{
			testStack(nameFile());
			break;
		}
		case 4: // createfile, run random strean, and test 
		{
			std::string filename = nameFile();
			randomStream(iterationSet(), filename);
			testStack(filename);
			break;
		}
		}
	
	}
}