#include <iostream>
#include<random>
#include <string>
#include <fstream>
#include <climits>
#include "randomStream.h"


std::string nameFile() {
	std::string filename;
	std::cout << "Please enter the name of the file: ";
	std::cin >> filename;
	return filename;

}
int iterationSet() {
	

	// input number of lines
	int len;
	std::cout << "How many iterations: ";
	std::cin >> len;
	//call method
	return len;
}

void randomStream(int length, std::string filename) {
	// create file
	std::ofstream file;
	// assign file name
	file.open(filename);
	// loop for the length and assign to each line
	for (int i = 0; i < length; ++i) {
		file << randomLetter() << std::endl;
	}
	file.close();
}

// generator for random letter
std::string randomLetter() { 
	// create random number for letter
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> letterNum(0, 5); // sets limit between 0 and 5
	int ranLetter = letterNum(gen);
	// check which number was generated and assign to letter
	if (ranLetter == 0) {
		// if A then add number after A between min and max
		std::uniform_int_distribution<> num(INT_MIN, INT_MAX); // sets limit between min and max for an int
		int minMaxNum = num(gen);
		// convert num into a string and add A to it 
		std::string aLetter = "A " + std::to_string(minMaxNum);
		// return as string
		return aLetter; 
	}
	// return letters associated with their number that are not A
	else if (ranLetter == 1) { return "D"; }
	else if (ranLetter == 2) { return "P"; }
	else if (ranLetter == 3) { return "E"; }
	else if (ranLetter == 4) { return "C"; }
	else { return "S"; }
}