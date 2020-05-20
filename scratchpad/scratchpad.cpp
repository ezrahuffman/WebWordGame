#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;


// A function that reads the lines from a text file and stores them as a vector of strings
std::vector<std::string> readWordsFile(std::string filename){
	std::ifstream file(filename);
	std::string str; 

	std::vector<std::string> words;

	while (std::getline(file, str)){
		words.push_back(boost::to_upper_copy(str));
		
	}

	return words;
}

int main(){

	// An exampe of using the above function

	std::vector<std::string> words = readWordsFile("misc/english.txt");

	// Printing out the first 5 elements of the vector produced above

	for (int i = 0; i < 5; i++){
		std::cout << words[i] << std::endl;
	}
	

	return 0;
}
