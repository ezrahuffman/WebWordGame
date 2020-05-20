#include <igloo/igloo.h>
#include <Game.h>


Game game;

using namespace igloo;
Context(CheckWordFunction){
	Spec(AimIsFound){
		ucm::json temp;
    	temp["word"] = "AIM";
    	temp["valid"] = true;
		Assert::That(game.checkWord("AIM"), Equals(temp));
	};

	Spec(RRRRRIsNotFound){
		ucm::json temp;
    	temp["word"] = "RRRRR";
    	temp["valid"] = false;
		Assert::That(game.checkWord("RRRRR"), Equals(temp));
	};
};

Context(CheckListFunction){
	Spec(ListIsOneCharArrayNineLong){
		Assert::That(game.generateList()[0].size(), Equals(9));
	};
};

Context(CheckPermutetFunction){
	Spec(PermuteABISABABBA){
		std::unordered_map<std::string, bool> test;
		test.insert({"A",true});
		test.insert({"B",true});
		test.insert({"AB",true});
		test.insert({"BA",true});
		std::unordered_map<std::string, bool> map;
		game.permute("AB","", 2, map);
		Assert::That(map, Equals(test));
	};
};


int main() {
	// Run all the tests defined above
	return TestRunner::RunAllTests();
}
