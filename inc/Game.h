#ifndef GAME_H
#define GAME_H   // You need to do this for all your .h files, to make sure 
                 // they don't get included in a project more than once

#include <server.h>
#include <unordered_map>


class Game {

	std::vector<std::string> allTheWords;
	std::vector<std::string> nineWords;
	std::unordered_map<std::string, bool> theWords;
	std::unordered_map<std::string, bool> foundWords;

	void readWordsFile(std::string filename);
	void read9File(std::string filename);
	
public:
	
	Game();

	ucm::json checkWord(std::string word);
	ucm::json generateList();
    ucm::json solution(std::string ltrs);
	bool inList(std::string);

    void permute(std::string a,std::string b,int l, std::unordered_map<std::string, bool>& results);
    std::vector<std::string> getAllPossibleSubstrings(std::string word);
    std::vector<char> mixup(std::string word);

};







#endif
