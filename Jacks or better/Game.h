#pragma once
#include <random>

class Game
{
public:
	//payouts times x units wagered
	enum ranks {
		royal = 250,
		straightFlush = 40,
		fourOfAKind = 25,
		fullHouse = 9,
		flush = 6,
		staight = 4,
		threeOfAKind = 3,
		twoPair = 2,
		pair = 1
	};
	Game();
	void returnCards(bool returns[5]);
	int getScore() const;
	int getSuit(int number) const;
	int getNumber(int number) const;
	void displayHand();
	int* getHandNumbers();
private:
	int hand[5];
	int handSize = sizeof(hand) / sizeof(*hand);
	
};