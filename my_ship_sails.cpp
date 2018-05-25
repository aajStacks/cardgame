//My Ship Sails
//Cardgame
//Mohammed Hossain

#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


typedef vector<vector<int> > vector2d;
//define vector <vector <int> > as vector2d to avoid redundant typing.

string cards[52] = { "" };
void printVector(vector<int> &v, bool isCard, bool asOption);
//function that can print a vector as number or as a the card
void game();
void cardDeck(string* cards);

int main() {
	srand(time(0));
	cardDeck(cards);
	game();
}

void cardDeck(string* cards){
	string suits[4] = { "C", "D", "H", "S" };
	string numbers[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
			"J", "K", "Q" };
	int k = 0;
	for (unsigned int i = 0; i < sizeof(suits) / sizeof(suits[0]); i++) {
		for (unsigned int j = 0; j < sizeof(numbers) / sizeof(numbers[0]);
				j++) {
			cards[k++] = suits[i] + numbers[j];
		}
	}
}

void createDeck(vector2d &player, vector2d &count){
	vector<int> cardIndex;

	int i = 0;
	while (i < 52) {
		cardIndex.push_back(i);
		i++;
	}

	for (i = 0; i < 35; i++) {
		int randIndex = rand() % cardIndex.size();
		int choice = i % 5;
		int value = cardIndex[randIndex];
		if (value < 13)
			count[choice][0]++;
		else if (value < 26)
			count[choice][1]++;
		else if (value < 39)
			count[choice][2]++;
		else if (value < 52)
			count[choice][3]++;
		player[choice].erase(player[choice].begin());
		player[choice].push_back(cardIndex[randIndex]);
		cardIndex.erase(cardIndex.begin() + randIndex);
	}
}
void sortDeck(vector<int> &v){
	for (unsigned int i = 0; i < v.size(); i++){
		sort(v.begin(),v.end());
	}
}

void printVector(vector<int> &v, bool isCard, bool asOption) {
	for (unsigned int i = 0; i < v.size(); i++) {
		if (isCard && asOption)
			cout << setw(4) << "(" << (char) (i + 'a') << ")" << cards[v[i]]
					<< " ";
		else if (isCard && !asOption)
			cout << setw(4) << cards[v[i]] << " ";
		else if (!(isCard && asOption))
			cout << setw(2) << v[i] << " ";
	}
	cout << endl;
}


void passCard(int &value, vector<int> &deck, vector<int> &count) {
	int idxDeck = 0;
	int smallest = 0;
	int temp = 0;
	int sCount = 8;
	for (unsigned int i = 0; i < count.size(); i++) {
		if (count[i] < sCount && count[i] > 0) {
			sCount = count[i];
			smallest = i;
		}
	}
	temp = smallest; //smallest holds the index which has the lowest value in count

	while (smallest >= 0) {
		idxDeck += count[smallest--];
	}
	idxDeck--;
	value = deck[idxDeck]; //we take the value to be passed
	deck.erase(deck.begin() + idxDeck); //passed card gets deleted from player deck
	count[temp]--; //we pass this card so count goes down
}
void recieveCard(const int &value, vector<int> &deck, vector<int> &count) {
	if (value < 13)
		count[0]++;
	else if (value < 26)
		count[1]++;
	else if (value < 39)
		count[2]++;
	else if (value < 52)
		count[3]++;

	deck.push_back(value);
	sort(deck.begin(), deck.end());
}
bool checkWin(vector<int> &count) {
	for (unsigned int i = 0; i < count.size(); i++) {
		if (count[i] == 7) {
			return true;
		}
	}
	return false;
}
void game() {
	vector2d player(5, vector<int>(7));
	vector2d count(5, vector<int>(4));
	bool flag = false;
	createDeck(player,count);
	sortDeck(player[0]);
	int val = 0;
	while (!flag) {
		printVector(player[0], true, true);
		char c;
		cout << "Enter a choice : ";
		cin >> c;
		c = tolower(c);
		int indexToRemove = c - 'a';
		if (!(indexToRemove >= 0 && indexToRemove <= 6))
			continue;
		for (unsigned int i = 0; i < player.size(); i++) {
			if (i != 0)
				passCard(val, player[i], count[i]);
			else {
				val = player[i][indexToRemove];
				player[i].erase(player[i].begin() + indexToRemove);
				if (val < 13)
					count[i][0]--;
				else if (val < 26)
					count[i][1]--;
				else if (val < 39)
					count[i][2]--;
				else if (val < 52)
					count[i][3]--;
			}
			if (i == 3)
				cout << endl<<"\t";
			cout << "Hint : Player " << i << " passed \"" << cards[val]
					<< "\" to Player " << (i + 1) % 5 << " ... ";

			recieveCard(val, player[(i + 1) % 5], count[(i + 1) % 5]);
			if (checkWin(count[(i + 1) % 5])) {
				flag = true;
				cout << endl << endl << "MY SHIP SAILS ... ";
				cout << "Player " << (i + 1) % 5 << " Won ..." << endl;
				break;
			}
		}
		cout << endl;

	}
	cout << "Final card distribution" << endl;
	for (unsigned int i = 0; i < player.size(); i++) {
		cout << "\tPlayer " << i << " : ";
		printVector(player[i], true, false);
	}

}
