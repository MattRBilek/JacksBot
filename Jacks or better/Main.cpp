#include "game.h"
#include <string>
#include <iostream>
int main() {
	
	int score = 0;
	while (true) {
		Game game = Game();
		game.displayHand();
		bool hands[5];
		
		std::string answer;
		std::cin >> answer;
		for (int i = 0; i < answer.length(); i++) {
			if ('y' == answer[i])
				hands[i] = true;
			else
				hands[i] = false;
		}
		game.returnCards(hands);
		game.displayHand();
		score += game.getScore();
		std::cout << score << " current score" << std::endl;
	}
}