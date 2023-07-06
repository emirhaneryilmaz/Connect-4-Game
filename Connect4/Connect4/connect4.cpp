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

void CheckBelow(char board[][10], playerInfo activePlayer, int dropChoice);

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


int PlayerDrop(char board[][10], playerInfo activePlayer)

{

	int dropChoice;
	int dropRow;
	int dropLocation;
	do

	{

		cout << activePlayer.playerName << "'s Turn ";

		cout << "Please enter a number between 1 and 9: ";

		cin >> dropChoice;



		if (!(dropChoice >= 1 && dropChoice <= 9)) {

			cout << "You entered an invalid number!" << " Please enter a number between 1 and 9." << endl;

			cin >> dropChoice;

		}


		// Find the first available row in the selected column
		dropRow = 9;
		while (board[dropRow][dropChoice] != '*')
		{
			dropRow--;
			if (dropRow == 0)
			{
				cout << "This column is full. Please enter a number for an empty column. " << endl;
				break;
			}
		}
	} while (!(dropChoice >= 1 && dropChoice <= 9) || dropRow == 0);


	dropLocation = dropRow * 10 + dropChoice;
	return dropLocation;  // To return the row and column as a single value

}

void CheckBelow(char board[][10], playerInfo activePlayer, int dropChoice)

{

	int length, turn;
	length = 9;
	turn = 0;

	do
	{
		if (board[length][dropChoice] != 'X' && board[length][dropChoice] != 'O')
		{
			board[length][dropChoice] = activePlayer.playerID;
			turn = 1;
		}
		else
			--length;
	} while (turn != 1);
}

void DisplayBoard(char board[][10])

{

	int rows = 9, columns = 9, i, j;

	// Open the file

	ofstream file("tahta.txt");

	for (i = 1; i <= rows; i++)

	{

		cout << "|";

		file << "|";



		for (j = 1; j <= columns; j++)

		{

			if (board[i][j] != 'X' && board[i][j] != 'O')

				board[i][j] = '*';



			cout << board[i][j];

			file << board[i][j];

		}
		cout << "|" << endl;

		file << "|" << endl;

	}


	// Close the file

	file.close();

}

int CheckFour(char board[][10], playerInfo activePlayer)

{

	char XO;
	int win;
	XO = activePlayer.playerID;
	win = 0;

	// Vertical

	for (int i = 9; i >= 1; i--)

	{

		for (int j = 9; j >= 1; j--)

		{

			if (board[i][j] == XO && //9,9 9,9 9,5... 9,1

				board[i - 1][j] == XO && //5,9 ... .5,1

				board[i - 2][j] == XO && //4,9 .... 4,1

				board[i - 3][j] == XO) //3,9 ... 3,1

				return 1;

		}

	}



	// Horizontal

	for (int i = 9; i >= 1; i--)

	{
		for (int j = 9; j >= 1; j--)

		{

			if (board[i][j] == activePlayer.playerID &&

				board[i][j - 1] == activePlayer.playerID &&

				board[i][j - 2] == activePlayer.playerID &&

				board[i][j - 3] == activePlayer.playerID)

				return 1;

		}

	}



	// Cross check (top left to bottom right)

	for (int i = 1; i <= 9; i++)

	{

		for (int j = 1; j <= 9; j++)

		{

			if (board[i][j] == XO &&

				board[i + 1][j + 1] == XO &&

				board[i + 2][j + 2] == XO &&

				board[i + 3][j + 3] == XO)

				return 1;

		}

	}



	// Cross check (bottom left to top right)

	for (int i = 9; i >= 1; i--)

	{

		for (int j = 1; j <= 9; j++)

		{

			if (board[i][j] == XO && // 9,1

				board[i - 1][j + 1] == XO && // 5,2

				board[i - 2][j + 2] == XO && //4,3

				board[i - 3][j + 3] == XO) // 3,4

				return 1;

		}

	}



	return win;

}

int FullBoard(char board[][10])

{

	int full;
	full = 0;
	for (int i = 1; i <= 9; ++i)
	{
		if (board[1][i] != '*')
			++full;
	}

	return full;

}

void PlayerWin(playerInfo activePlayer)

{
	cout << endl << activePlayer.playerName << " WON!" << endl;
}