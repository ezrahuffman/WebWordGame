#include <Game.h>
#include <algorithm>
#include <random>
#include <TimeSupport.h>


void Game::readWordsFile(std::string filename){
    std::ifstream file(filename);
    std::string str;

    while(std::getline(file, str)){
        theWords.insert({boost::to_upper_copy(str),true});
        allTheWords.push_back(boost::to_upper_copy(str));
    }

}

void Game::read9File(std::string filename){
    std::ifstream file(filename);
    std::string str;

    while(std::getline(file, str)){
        nineWords.push_back(boost::to_upper_copy(str));
    }

}

Game::Game(){
    readWordsFile("misc/english.txt");
    read9File("misc/9ltrs.txt");
}

ucm::json Game::checkWord(std::string word){

    timestamp start = current_time();
    auto pos = theWords.find(word);

    bool found = true;
    bool prevFound = inList(word);

    if (pos == theWords.end() || prevFound){
        found = false;
    } 
    

    timestamp end = current_time();

    long duration = time_diff(start, end);

    std::cout << "Took: " << duration << " ms." << std::endl;

    ucm::json temp;
    temp["word"] = word;
    temp["valid"] = found;
    if(found){
        foundWords.insert({word, true});
    }

    return temp;
}

bool Game::inList(std::string word){
    bool found = true;
    auto pos = foundWords.find(word);
    if (pos == foundWords.end()){
        found = false;
    }

    return found;
}

ucm::json Game::generateList(){
    std::uniform_int_distribution<> distribution(0, nineWords.size());
    std::mt19937_64 gen;
    gen.seed(std::random_device()());
    
    ucm::json temp;
    std::string word = nineWords[distribution(gen)];
    std::cout << "word: " << word << std::endl;
    temp.push_back(mixup(word));

    return temp;
}

std::vector<std::string> Game::getAllPossibleSubstrings(std::string word){
    std::vector<std::string> possible;
    std::unordered_map<std::string, bool> curr;
    permute(word, "", word.length(), curr );
    for(auto element : curr){
      possible.push_back(element.first);
    }

    return possible;
}

void Game::permute(std::string a,std::string b, int l, std::unordered_map<std::string, bool>& results){
    auto pos = results.find(b);
    if (pos == results.end()){
        if (theWords.find(b) != theWords.end()){
            results.insert({b,true});
        }
    }

    for (int i = 0; i < a.length(); i++){
        char* cpy = new char[a.length()];
        strcpy(cpy, a.c_str());
        std::string cpyStr(cpy);
        permute(cpyStr.erase(i,1),b+a[i],l, results);
    }
}

std::vector<char> Game::mixup(std::string word){
    std::vector<char> result;

    for(int i = 0; i < word.size(); i++){
        result.push_back(word[i]);
    }

    std::random_shuffle(result.begin(), result.end());

    return result;
}

ucm::json Game::solution(std::string ltrs){
    ucm::json sol;

    //all possible subs function checks if the word is in theWords so it doesn't ned to be checked here
    std::vector<std::string> pos = getAllPossibleSubstrings(ltrs);

    for (std::string str: pos){
        sol.push_back(str);
    }
    std::cout  << "pos.size = " << pos.size() << std::endl;
    std::cout  << "sol.size = " << sol.size() << std::endl;
    return sol;
}