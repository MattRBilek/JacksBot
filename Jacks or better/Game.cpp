#include "Game.h"
#include <cstdlib> 
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <time.h>
Game::Game() {
	for (int i = 0; i < sizeof(hand)/sizeof(*hand); i++) {
		hand[i] = i;
	}
	returnCards(new bool[5]{true,true,true,true,true});
}

//gets new cards might need to redo the random as it is sudo
void Game::returnCards(bool returns[5]) {
	int cardsDone = 0;
	for (int i = 0; i < handSize; i++)
		if (!returns[i])
			cardsDone++;
	srand(time(0));
	for (int i = 0; i < handSize; i++) {
		if (returns[i]) {
			int tempCard = rand() % (52 - cardsDone); //gets random number between 0 and cards left i.e. not being used or being returned
			int tempCount = 0;
			for (int j = 0; j < handSize; j++) {
				if (hand[j] <= tempCard && !returns[j]) {
					tempCard++; //as temp card counted something that was being used
					for (int k = j; k >= 0; k--) {
						for (int l = j; l >= 0; l--) {
							if (!returns[l] && tempCard == hand[l]) {
								tempCard++;
							}
						}
					}
				}
			}
			hand[i] = tempCard;
			cardsDone++; //one more card done
			returns[i] = false;
		}
	}
	std::sort(hand, hand + handSize, 
		[this](const int& t1, const int& t2) {return Game::getNumber(t1) < Game::getNumber(t2);});
}

//assumes that hand is sorted in number order suit does not matter
int Game::getScore() const {
	bool flush = true;
	for (int i = 0; i < handSize; i++)
		if (getSuit(hand[i]) != getSuit(hand[0]))
			flush = false;
	bool straight = true;
	for (int i = 0; i < handSize - 1; i++) {
		if (getNumber(hand[i]) + 1 != getNumber(hand[i + 1]))
			if (!(i == 3 && getNumber(hand[i]) == 4 && getNumber(hand[i + 1])))
				straight = false;
	}
	if (flush || straight) {
		if (flush && straight) {
			if (hand[0] == 9)
				return royal;
			return straightFlush;
		}
		if (flush)
			return ranks::flush;
		return ranks::staight;
	}
	int pairOne = 0; //holds last index of that card
	int countOne = 1;
	for (int i = 1; i < handSize; i++) {
		if (getNumber(hand[pairOne]) == getNumber(hand[i])) {
			pairOne = i;
			countOne++;
		}
		else if (countOne == 1) {
			pairOne = i;
		}
	}
	int pairTwo = pairOne + 1; //holds last index of that card
	int countTwo = 1;
	for (int i = pairTwo + 1; i < handSize; i++) {
		if (getNumber(hand[pairTwo]) == getNumber(hand[i])) {
			pairTwo = i;
			countTwo++;
		}
		else if (countOne == 1) {
			pairTwo = i;
		}
	}
	if (countOne == 4)
		return ranks::fourOfAKind;
	else if (countOne == 3 || countTwo == 3)
		if (countOne == 2 || countTwo == 2)
			return ranks::fullHouse;
		else
			return ranks::threeOfAKind;
	else if (countOne == 2 && countTwo == 2)
		return ranks::twoPair;
	else if (countOne == 2 && getNumber(hand[pairOne]) >= 10)
		return ranks::pair;

	//hand not a winner needs to pay 1 unit
	return -1;
}
// returns a suit 0-3
int Game::getSuit(int number) const {
	return number/13;
}
//ace is 13 two is 1
int Game::getNumber(int number) const {
	return int(number)%13 + 1;
}

void Game::displayHand() {
	for (int i = 0; i < handSize; i++) {
		std::cout << (std::to_string(i) + ") " + std::to_string(getNumber(hand[i])) + " of " + std::to_string(getSuit(hand[i]))) << std::endl;
	}
	std::cout << "Score = " + std::to_string(getScore()) << std::endl;
}
