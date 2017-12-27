#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;
#define numOfPlayers 3 //define the number of players
#define cardsPerPlayer 3 //define how many cards a player has
#define numOfCards 13 //this is const

const string ranks[] = { "2","3","4","5","6","7","8","9","10","B","D","K","A" };
const char*signs[] = { "Heart","Spade","Diamond","Club" };

class Card
{
public:
	Card() :_sign("void"), _rank(0) {}
	Card(Card&&card){swapCard(move(card));}//the move ctor
	Card(string sign, string val)//standard ctor
	{
		_sign = sign;
		_rank = val;
	}
	Card(const Card &card)//copy ctor
	{
		_sign = card._sign;
		_rank = card._rank;
	}
	//move + operator=
	Card&operator=(Card&&card)
	{
		if (this != &card) 
			swapCard(move(card));
		return *this;
	}
	//just operator=
	Card&operator=(Card& card) 
	{
		if (this != &card)
		{
			_sign = card._sign;
			_rank = card._rank;
		}
		return *this;
	}
	void Print() {cout << _sign << " " << _rank << endl;}
	~Card(){_sign.clear();}
private:
	void swapCard(Card&&card) 
	{
		swap(card._sign, _sign);
		swap(card._rank, _rank);
	}
	string _sign="void";
	string _rank;
};

class Player
{
public:
	Player():_name("BLANK"){}
	Player(string name) :_name(name) {}
	Player(const char*name) :_name(name) {}
	void AddCard(Card&&card) {
		//big difference
		//_cards.push_back(card);//calls copy ctor
		_cards.push_back(move(card));//calls move ctor
	}
	~Player(){_name.clear();}
	void Print() {
		cout << _name << endl;
		for (int i = 0; i < _cards.size(); i++)
			_cards[i].Print();
	}
	void ClearHand() {
		_cards.clear();
	}
private:
	string _name;
	vector<Card> _cards;
};

class Deck
{
public:
	Deck()
	{
		init();
	}
	Card&Draw(){
		if (_cardIndex < 0)
			throw exception("No more cards to deal");
		return _deck[_cardIndex--];
	}
	void Shuffle() {
		std::srand(std::time(0));
		random_shuffle(begin(_deck), end(_deck));
	}
	void Reset() {
		_deck.clear();
		init();
	}
	void PrintAll() {
		for (int i = 0; i < _deck.size(); i++)
			_deck[i].Print();
	}
	void PrintLeft() {
		for (int i = 0; i <= _cardIndex; i++)
			_deck[i].Print();
	}
	~Deck(){_deck.clear();}

private:
	void init() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < numOfCards; j++)
				_deck.push_back(Card(signs[i], ranks[j]));
		_cardIndex = _deck.size() - 1;
	}
	vector<Card> _deck;
	int _cardIndex;
};


void ResetGame(Deck*deck,Player players[]) {
	deck->Reset();
	for (int i = 0; i < numOfPlayers; i++)
		players[i].ClearHand();
}


int main() {
	//just some showcases for cards
	//Card c1("heart", 1);
	//Card c2(move(c1));
	////c1.Print();
	////c2.Print();

	Deck deck;
	//deck.Print();
	deck.Shuffle();
	//deck.Print();

	Player players[numOfPlayers]{"P1","P2","P3"};

	for (int i = 0; i < numOfPlayers; i++)
		for (int i = 0; i < cardsPerPlayer; i++)
			players[i].AddCard(move(deck.Draw()));
	
	deck.PrintAll();
	cout << "\n----------------------------------------------\n";
	for (int i = 0; i < numOfPlayers; i++)
		for (int i = 0; i < cardsPerPlayer; i++)
			players[i].Print();

	deck.PrintLeft();
	ResetGame(&deck, players);
	cout << "\nPress enter to continue\n";
	system("pause>0");
	system("cls");//on win
	//system("clear");//on unix
	cout << "After reset" << endl;
	deck.PrintAll();
	cout << "\n----------------------------------------------\n";
	for (int i = 0; i < numOfPlayers; i++)
		for (int i = 0; i < cardsPerPlayer; i++)
			players[i].Print();
}

