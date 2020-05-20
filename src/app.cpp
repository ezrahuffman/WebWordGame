#include <server.h>
#include <algorithm>
#include <Game.h>

using namespace ucm;


int main(int argc, char** argv){

    Server server(argc, argv);

    Game wordGame;

    server.renderHTML("/", "index.html");

    server.route("/list", [&](const request& req, response& res){

        res.sendJSON(wordGame.generateList());

    });

    server.route("/checkWord", [&](const request& req, response& res){
        if (req.has_params({"word"})){
            std::string word = req.url_params.get("word");
            res.sendJSON(wordGame.checkWord(word));
        }
        else{
            res.sendError400();
        }
    });

    server.route("/solution", [&](const request& req, response& res){
        if (req.has_params({"letters"})){
            std::string letters = req.url_params.get("letters");
            res.sendJSON(wordGame.solution(letters));
        } else
        {
            res.sendError400();
        }
        
    });

    server.run();
}

