#include<iostream>
#include<stdlib.h>
#include <string>
#include<Windows.h>
#include<ctime>
#include <assert.h>
#include<iomanip>
#include<fstream>
using namespace std;
//global declarations
int  temp = 0;
string gameID;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void mainMenu();
void record() {
	string st2;
	ifstream read("records.txt");
	while (!read.eof()) {
		getline(read, st2);
		cout << "\n" << st2;
	}
}
//function for toss
void Toss(string name1, string name2, string& toss, string& x) {
	//declarations
	srand((unsigned)time(0));
	bool chk = false;
	int count = 0, tempr = 0;
	//to check user enters the correct input
	do {
		if (count == 0) {
			cout << "\n\n(TOSS)\nCHOOSE HEADS OR TAILS(0 FOR HEADS 1 FOR TAILS)\n"; getline(cin, toss);
		}
		else {
			SetConsoleTextAttribute(h, 12);
			cout << "INVALID INPUT! CHOOSE BETWEEN 0/1(0 FOR HEADS 1 FOR TAILS) \n"; getline(cin, toss);
			SetConsoleTextAttribute(h, 6);
		}
		if (toss == "0" || toss == "1") {
			chk = true;
		}
		++count;
	} while (!chk);
	//rand for toss
	tempr = rand() % 2;
	x = to_string(tempr);
}
//functon to genrated random game id
void gameId() {
	//generating random gameid
	int tempg = 0;
	string idCheck;
	srand((unsigned)time(0));
	tempg = rand() % (9999) + 999;
	gameID = to_string(tempg);

	ifstream op;

	op.open("gameid's.txt");
	while (!op.eof()) {
		getline(op, idCheck);
		if (idCheck == gameID) {
			gameId();
			break;
		}
	}
	op.close();

	ofstream inp;
	inp.open("gameid's.txt",ios::app);
	inp << gameID << "\n";
	inp.close();
}
//function to print any card/array
void printCard(int arr[][5]) {
	//loops helping to make a grid of 5*5 matrix
	cout << "\n\n\tGAME ID: " << gameID << "\n\n";
	SetConsoleTextAttribute(h, 13);
	for (int i = 0; i < 5; ++i) {
		cout << "\t\t\t\t\t\t\t\t\t"; for (int x = 0; x < 5; ++x) { cout << setw(3) << " ----"; }
		cout << endl << "\t\t\t\t\t\t\t\t\t|";
		for (int j = 0; j < 5; ++j) {
			cout << setw(3) << arr[i][j] << " |";
		}
		cout << endl;
		if (i == 4) {
			cout << "\t\t\t\t\t\t\t\t\t";
			for (int x = 0; x < 5; ++x) { cout << setw(3) << " ----"; }
		}
	}
	SetConsoleTextAttribute(h, 6);
}
//function to display BINGO on homescreen
void BINGO() {
	//startup/homescreen display
	cout << "\n\n\n\n";
	cout << "\t\t\t\t\t\t *****       *******    ***       **       **********       ********  \n";
	cout << "\t\t\t\t\t\t *    *        *        ** **     **      **               **      ** \n";
	cout << "\t\t\t\t\t\t *    *        *        **  **    **      **               **      ** \n";
	cout << "\t\t\t\t\t\t *****         *        **   **   **      **     ***       **      ** \n";
	cout << "\t\t\t\t\t\t *    *        *        **    **  **      **       **      **      ** \n";
	cout << "\t\t\t\t\t\t *    *        *        **     ** **      **       **      **      ** \n";
	cout << "\t\t\t\t\t\t *****       ******     **       ***       *********        ********  \n";
	cout << "\n\n";
	cout << "Press enter to start Bingo\n";
}
//function to clear everything on screen
void clearScreen() {
	system("CLS");
}
//function containing instructions how to play
void instructions() {
	//how to play
	char x = '1';
	cout << "HOW TO PLAY BINGO! \n";
	cout << "1. YOU WILL CHOOSE A CARD FILLED WITH RANDOMLY GENERATED NUMBERS FROM 1 TO 25. \n";
	cout << "2. EACH CARD WILL BE SHOWN TO RESPECTIVE PLAYER.\n";
	cout << "3. YOU WILL HAVE TO ENTER THE NUMBER YOU WANT TO REMOVE FROM YOUR CARD.\n";
	cout << "4. NUMBER ENTERED WILL BECOME '0' ZERO.\n";
	cout << "5. 5 ZEROES IN ROW/COLUMN OR DIAGONAL WILL MAKE YOUR SCORE= +1.\n";
	cout << "6. THE FIRST ONE TO SCORE 5 WILL WIN.\n";
	cout << "7. EITHER YOU WIN OR LOSE. NO MATCH DRAWS.\n";
	cout << "8. BINGO!\n";
	cout << "\n\n";
	//to make the screen wait until user reads the instructions and enters something then return to main menu
	x = getchar();
	mainMenu();
}
//function to exit the game if you want
void exit() {
	string choiceToLeave;
	//if user wants to leave
	cout << "\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\t\t\t ARE YOU SURE YOU WANT TO LEAVE ?? \n";
	cout << "\t\t\t\t\t\t\t\t\t\t      YES/NO ?? \n";
	cin >> choiceToLeave;
	if (choiceToLeave == "yes" || choiceToLeave == "Yes" || choiceToLeave == "YES") {
		//if user wants to leave
		doExit = true;
	}
	else if (choiceToLeave == "NO" || choiceToLeave == "no" || choiceToLeave == "No") {
		//if user do not want to leave
		clearScreen();
		doExit = false;
	}
	else {
		clearScreen();
		//recursion in case of invalid input
		exit(doExit);
	}

}
//function that allows player1 to choose their favourite card
void cardOne(string name1, int card1[][5]) {
	bool done = false;
	srand((unsigned)time(0));
	do {
		//initializing array with zero if user wants to change the card
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				card1[i][j] = 0;
			}
		}
		//random rows and cols in which 1 to 25 numbers are stored 
		int row = 0, col = 0;
		string selCard;
		for (int i = 0, count = 1; i < 5; ++i) {
			for (int j = 0; j < 5; ++count, ++j) {
				do {
					row = rand() % 5;
					col = rand() % 5;
					//checking if the location is already filled so it wouldn't be repeated
				} while (card1[row][col] != 0);
				card1[row][col] = count;
			}
		}
		cout << name1 << "'S CARD: \n\n";
		printCard(card1);
		cout << "\n\n\n\n\t TO SELECT THIS CARD ENTER 1 \n\t\t ANY OTHER KEY TO SWITCH CARD\n\t "; getline(cin, selCard);
		//checking if user wants to select this card or switch to another one
		if (selCard == "1") {
			done = true;
		}
		else if (selCard == "0") {
			done = false;
		}
		clearScreen();
	} while (done != true);

}
//function that allows player2 to choose their favourite card
void cardTwo(string name2, int card1[][5], int card2[][5]) {
	bool done = false;
	srand((unsigned)time(0));
	do {
		//initializing array with zero if user wants to change the card
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				card2[i][j] = 0;
			}
		}
		//random rows and cols in which 1 to 25 numbers are stored 
		int row = 0, col = 0;
		string selCard;
		for (int i = 0, count = 1; i < 5; ++i) {
			for (int j = 0; j < 5; ++count, ++j) {
				do {
					row = rand() % 5;
					col = rand() % 5;
					//checking if the location is already filled so it wouldn't be repeated
				} while (card2[row][col] != 0);
				card2[row][col] = count;
			}

		}
		//checking if both cards are same
		int check = 0;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (card1[i][j] == card2[i][j]) {
					++check;
				}
			}
		}
		if (check > 24) {
			continue;
		}
		cout << name2 << "'S CARD: \n\n";
		printCard(card2);
		cout << "\n\n\n\n\t TO SELECT THIS CARD ENTER 1 \n\t\t ENTER ANY OTHER KEY TO SWITCH CARD.\n\t "; getline(cin, selCard);
		//checking if user wants to select this card or switch to another one
		if (selCard == "1") {
			done = true;
		}
		else {
			done = false;
		}
		clearScreen();
	} while (done != true);

}
//function that checks winning conditions
void winCheck(int arr[][5], bool& winchk) {
	//winning conditions
	int sum = 0, score = 0;
	temp = 0;
	//rows check
	for (int i = 0; i < 5; ++i) {
		sum = 0;
		for (int j = 0; j < 5; ++j) {
			sum += arr[i][j];
		}
		if (sum == 0) {
			++score;
		}
	}
	//colums check
	for (int j = 0; j < 5; ++j) {
		sum = 0;
		for (int i = 0; i < 5; ++i) {
			sum += arr[i][j];
		}
		if (sum == 0) {
			++score;
		}
	}
	// (\)diaogonal chk 
	sum = 0;
	for (int i = 0; i < 5; ++i) {
		sum += arr[i][i];
	}
	if (sum == 0) { ++score; }
	sum = 0;
	// (/)diaogonal chk 
	for (int i = 0, j = 4; i < 5 || j >= 0; --j, ++i) {
		sum += arr[i][j];
	}
	if (sum == 0) {
		++score;
	}
	//wincheck if score is 5 every time score increments when a row col or any diagonal is completely 0
	if (score == 5) {
		winchk = true;
	}
	temp = score;
}
//writing record of previous winner of the match
void Wrecord(string winner, string loser, int lScore) {
	//history and records
	ofstream fout("records.txt", ios::app);
	for (int i = 1; i < 5; ++i) {
		if (i == 1) {
			fout << "GAME ID: " << gameID;
		}
		else if (i == 2) {
			fout << "\nWINNER NAME : " << winner << "\t\tLOSER NAME : " << loser;
		}
		else if (i == 3) {
			fout << "\nWINNER'S SCORE : 5\tLOSER'S SCORE : " << lScore;
		}
		else if (i == 4) {
			fout << "\n\n";
		}
	}
}
//function that handles all the midway processing after choosing card until winning conditions are true
void process(int play1[][5], int play2[][5], string name1, string name2) {
	string remNumStr;
	int remNum, score1 = 0, score2 = 0;
	bool winchk = false, check = false, pCheck = false;
	clearScreen();
	do {
		printCard(play1);
		do {
			pCheck = false;
			do {
				cout << "\n\n\t\t\t\t" << name1 << " SELECT ANY NUMBER FROM CARD : "; cin >> remNumStr;
			} while (remNumStr != "1" && remNumStr != "2" && remNumStr != "3" && remNumStr != "4" && remNumStr != "5" && remNumStr != "6" && remNumStr != "7" && remNumStr != "8" && remNumStr != "9" && remNumStr != "10" && remNumStr != "11" && remNumStr != "12" && remNumStr != "13" && remNumStr != "14" && remNumStr != "15" && remNumStr != "16" && remNumStr != "17" && remNumStr != "18" && remNumStr != "19" && remNumStr != "20" && remNumStr != "21" && remNumStr != "22" && remNumStr != "23" && remNumStr != "24" && remNumStr != "25");
			assert(1);
			remNum = stoi(remNumStr);
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					//checking the number exist in the card
					if (remNum == play1[i][j]) pCheck = true;
				}
			}
			//checking the number exist in the range of card
			if (remNum < 26 && remNum > 0 && pCheck == true) {
				check = true;
			}
			else {
				SetConsoleTextAttribute(h, 12);
				cout << "\n NUMBER COULD NOT BE FOUND IN CARD!\n";
				SetConsoleTextAttribute(h, 6);
			}


		} while (!check);
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (play1[i][j] == remNum) {
					play1[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (play2[i][j] == remNum) {
					play2[i][j] = 0;
				}
			}
		}
		winCheck(play1, winchk);
		score1 = temp;
		if (winchk == true) {
			cout << "\n\t\t\t\t" << name1 << " WINS\n";
			Wrecord(name1, name2, score2);
			continue;
		}
		winCheck(play2, winchk);
		score2 = temp;
		if (winchk == true) {
			cout << "\n\t\t\t\t" << name2 << " WINS\n";
			Wrecord(name2, name1, score1);
			continue;
		}

		remNum = 0;
		check = false;
		pCheck = false;
		clearScreen();
		printCard(play2);
		do {
			do {
				cout << "\n\n\t\t\t\t" << name2 << " SELECT ANY NUMBER FROM CARD : "; cin >> remNumStr;
			} while (remNumStr != "1" && remNumStr != "2" && remNumStr != "3" && remNumStr != "4" && remNumStr != "5" && remNumStr != "6" && remNumStr != "7" && remNumStr != "8" && remNumStr != "9" && remNumStr != "10" && remNumStr != "11" && remNumStr != "12" && remNumStr != "13" && remNumStr != "14" && remNumStr != "15" && remNumStr != "16" && remNumStr != "17" && remNumStr != "18" && remNumStr != "19" && remNumStr != "20" && remNumStr != "21" && remNumStr != "22" && remNumStr != "23" && remNumStr != "24" && remNumStr != "25");
			assert(1);
			remNum = stoi(remNumStr);
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					//checking the number exist in the card
					if (remNum == play2[i][j]) {
						pCheck = true;
					}
				}
			}
			if (remNum < 26 && remNum > 0 && pCheck == true) {
				check = true;
			}
			else {
				SetConsoleTextAttribute(h, 12);
				cout << "\n NUMBER COULD NOT BE FOUND IN CARD!\n";
				SetConsoleTextAttribute(h, 6);
			}


		} while (!check);
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (play2[i][j] == remNum) {
					play2[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (play1[i][j] == remNum) {
					play1[i][j] = 0;
				}
			}
		}
		winCheck(play1, winchk);
		score1 = temp;
		if (winchk == true) {
			cout << "\n\t\t\t\t" << name1 << " WINS\n";
			Wrecord(name1, name2, score2);
			continue;
		}
		winCheck(play2, winchk);
		score2 = temp;
		if (winchk == true) {
			cout << "\n\t\t\t\t" << name2 << " WINS\n";
			Wrecord(name2, name1, score1);
			continue;
		}
		check = false;
		clearScreen();

	} while (!winchk);
}
//function that handles all the in game process where the game starts
void playGame() {
	srand((unsigned)time(0));
	string name1, name2, x, toss, temp;
	char wait = {};
	int card1[5][5] = {}, card2[5][5] = {};
	cout << "Player 1's Name: ";
	cin.ignore();
	getline(cin, name1);
	cout << "Player 2's Name: ";
	getline(cin, name2);
	Toss(name1, name2, toss, x);
	if (toss == x) {
		cout << "\t\t\t\tPLAYER ONE WINS THE TOSS\n";
	}
	else if (toss != x) {
		cout << "\t\t\t\tPLAYER TWO WINS THE TOSS\n";
		temp = name1;
		name1 = name2;
		name2 = temp;
	}
	cardOne(name1, card1);
	cardTwo(name2, card1, card2);
	cout << "\n\n\n";
	process(card1, card2, name1, name2);
}
//function that calls play game and also display loading by using sleep funtion
void loadGame() {	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tLoading.";
	Sleep(1000);
	clearScreen();
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tLoading..";
	Sleep(1);
	clearScreen();
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tLoading...";
	Sleep(1000);
	clearScreen();
	playGame();
}
//main menu of the program and it is a main menu driver program
void mainMenu() {
	int errcount = 0;
	char y = '1';
	string choice, ch;
	bool doExit = false;
	SetConsoleTextAttribute(h, 6);
	gameId();
	BINGO();
	getline(cin, ch);
	if (ch == "\n") {
		clearScreen();
	}

	do {
		if (errcount >= 1) {
			SetConsoleTextAttribute(h, 12);
			cout << "\nERROR! CHOOSE BETWEEN 1-4.\n";
			SetConsoleTextAttribute(h, 6);
		}
		cout << "1. PLAY GAME \n";
		cout << "2. HOW TO PLAY\n";
		cout << "3. PREVIOUS HISTORY\n";
		cout << "4. Exit\n";
		cin >> choice;
		++errcount;
	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4");

	if (choice == "1") {
		clearScreen();
		loadGame();
	}
	else if (choice == "2") {
		clearScreen();
		instructions();
	}
	else if (choice == "3") {
		clearScreen();
		record();
	}
	else if (choice == "4") {
		clearScreen();
		exit(doExit);

	}

	if (doExit == true) {
		return;
	}
	else if (doExit == false) {
		y = getchar();
	}
	mainMenu();
}
//int main
int main() {
	mainMenu();
	system("pause");
	return 0;
}