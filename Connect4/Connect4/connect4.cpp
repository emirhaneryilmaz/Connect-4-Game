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
	cout << "hello";
}