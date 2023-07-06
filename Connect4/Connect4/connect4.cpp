#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

//Player Fields
struct playerInfo

{
	char playerName[81];
	char playerID;
};

//Function Prototypes
int PlayerDrop(char board[][10], playerInfo activePlayer);

void CheckBellow(char board[][10], playerInfo activePlayer, int dropChoice);

void DisplayBoard(char board[][10]);

int CheckFour(char board[][10], playerInfo activePlayer);

int FullBoard(char board[][10]);

void PlayerWin(playerInfo activePlayer);

int restart(char board[][10]);

void ReadBoardFromFile(char board[][10]);

void RecordMoveToFile(const string&, const string&);

void StartNewGame(playerInfo playerOne, playerInfo playerTwo, char board[10][10], int trueWidth, int trueLength, int dropChoice, int win, int full, int again, int dropLocation, int dropRow, std::string nameParam, std::string moveParam);

void ContinueLastGame(playerInfo playerOne, playerInfo playerTwo, char board[10][10], int dropChoice, int win, int full, int again, int dropLocation, int dropRow, std::string nameParam, std::string moveParam);

int main() {
	playerInfo playerOne{};
	playerInfo playerTwo{};

	char board[10][10]; // I defined the matrix as 10x10 because I don't want to enter 0 to the user and not to get confused while writing the code.

	int trueWidth = 9;
	int trueLength = 9;
	int dropChoice{}, win{}, full{}, again{}, dropLocation{}, dropRow{};
	string nameParam{}, moveParam{};



	cout << "Lets Play Connect 4 !" << endl << endl;
	cout << "1. Start a new game." << endl;
	cout << "2. Load last game." << endl;
	cout << "Make your choice: ";


	int choice;
	cin >> choice;


	if (choice == 1) {
		ofstream file("hamle.txt", ios::out | ios::trunc);
		file.close();
		StartNewGame(playerOne, playerTwo, board, trueWidth, trueLength, dropChoice, win, full, again, dropLocation, dropRow, nameParam, moveParam);

	}

	else if (choice == 2) {
		ReadBoardFromFile(board);
		ContinueLastGame(playerOne, playerTwo, board, dropChoice, win, full, again, dropLocation, dropRow, nameParam, moveParam);



	}

	else {

		cout << "Invalid choice. The game is ending." << endl;
		return 0;

	}

	return 0;
}