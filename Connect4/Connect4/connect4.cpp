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

int restart(char board[][10])

{

	int restart;

	cout << "Do you want to restart the game? Yes(1) No(2): ";

	cin >> restart;
	if (restart == 1)

	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				board[i][j] = '*';
			}
		}
	}

	else

		cout << "Goodbye!" << endl;

	return restart;

}

void ReadBoardFromFile(char board[][10]) {

	ifstream file("tahta.txt");

	if (file.is_open()) {

		string line;

		int row = 1;

		while (getline(file, line)) {

			if (line.length() >= 10) {

				for (int col = 1; col <= 9; col++) {

					board[row][col] = line[col];

				}

				row++;

			}

		}

		file.close();

	}

}

void RecordMoveToFile(const string& filename, const string& move)
{
	ofstream file(filename, ios::app);

	if (file.is_open())
	{
		file << move << endl;
		file.close();
	}
	else
	{
		cout << "Could not open the file." << endl;
	}
}

void StartNewGame(playerInfo playerOne, playerInfo playerTwo, char board[10][10], int trueWidth, int trueLength, int dropChoice, int win, int full, int again, int dropLocation, int dropRow, std::string nameParam, std::string moveParam) {

	cout << "First player please enter your name: ";

	cin >> playerOne.playerName;

	playerOne.playerID = 'X';

	cout << "Second player please enter your name: ";

	cin >> playerTwo.playerName;

	playerTwo.playerID = 'O';

	full = 0;

	win = 0;

	again = 0;

	DisplayBoard(board);

	do

	{

		dropLocation = PlayerDrop(board, playerOne);
		dropRow = dropLocation / 10;
		dropChoice = dropLocation % 10;
		nameParam = playerOne.playerName + string("->");
		moveParam = to_string(dropRow) + to_string(dropChoice);


		CheckBelow(board, playerOne, dropChoice);
		DisplayBoard(board);
		RecordMoveToFile("hamle.txt", nameParam + moveParam);

		win = CheckFour(board, playerOne);

		if (win == 1)
		{
			PlayerWin(playerOne);
			break;
		}

		dropLocation = PlayerDrop(board, playerTwo);
		dropRow = dropLocation / 10;
		dropChoice = dropLocation % 10;
		nameParam = playerTwo.playerName + string("->");
		moveParam = to_string(dropRow) + to_string(dropChoice);

		CheckBelow(board, playerTwo, dropChoice);
		DisplayBoard(board);
		RecordMoveToFile("hamle.txt", nameParam + moveParam);


		win = CheckFour(board, playerTwo);

		if (win == 1)

		{
			PlayerWin(playerTwo);
			break;
		}


		full = FullBoard(board);


		if (full == 9)

		{

			cout << "Board full, draw!" << endl;
			break;

		}

		// Option to stop the game

		cout << "Press the 'ESC' key to stop the game. Press another key to continue: " << endl;


		while (true) {
			if (_kbhit()) {  // Check if any key has been pressed on the keyboard
				char key = _getch();  // Get pressed key
				if (key == 27) {  // Check ESC key
					cout << "The game has been paused!" << endl;


					cout << "Press 2 to restart the game. Press another key to exit: " << endl;

					char key2 = _getch();  // Get pressed key

					if (key2 == 50)

					{
						// Oyunu yeniden baþlatma iþlemleri
						for (int i = 1; i <= 9; i++)
						{
							for (int ix = 1; ix <= 9; ix++)
							{
								board[i][ix] = '*';
							}
						}

						main(); // restart the game by calling main function again
					}

					else

					{
						cout << "Goodbye!" << endl;
						exit(0);
						break;
					}

				}
				else
					break;

			}

		}


	} while (true);


}

void ContinueLastGame(playerInfo playerOne, playerInfo playerTwo, char board[10][10], int dropChoice, int win, int full, int again, int dropLocation, int dropRow, std::string nameParam, std::string moveParam) {
	ifstream file("hamle.txt");
	string line, lastLine, secondLastLine;

	if (file.is_open()) {
		while (getline(file, line)) {
			secondLastLine = lastLine;
			lastLine = line;
		}

		file.close();

		// Assigning playerOneName and playerTwoName by parsing the last two lines
		size_t delimiterPos = secondLastLine.find("->");
		string playerOneName = secondLastLine.substr(0, delimiterPos);
		string playerTwoName = lastLine.substr(0, delimiterPos);
		strcpy_s(playerOne.playerName, playerOneName.c_str());
		strcpy_s(playerTwo.playerName, playerTwoName.c_str());


		playerOne.playerID = 'X';
		playerTwo.playerID = 'O';

		DisplayBoard(board);

		do

		{

			dropLocation = PlayerDrop(board, playerOne);
			dropRow = dropLocation / 10;
			dropChoice = dropLocation % 10;
			nameParam = playerOne.playerName + string("->");
			moveParam = to_string(dropRow) + to_string(dropChoice);


			CheckBelow(board, playerOne, dropChoice);
			DisplayBoard(board);
			RecordMoveToFile("hamle.txt", nameParam + moveParam);

			win = CheckFour(board, playerOne);

			if (win == 1)
			{
				PlayerWin(playerOne);
				break;
			}

			dropLocation = PlayerDrop(board, playerTwo);
			dropRow = dropLocation / 10;
			dropChoice = dropLocation % 10;
			nameParam = playerTwo.playerName + string("->");
			moveParam = to_string(dropRow) + to_string(dropChoice);

			CheckBelow(board, playerTwo, dropChoice);
			DisplayBoard(board);
			RecordMoveToFile("hamle.txt", nameParam + moveParam);


			win = CheckFour(board, playerTwo);

			if (win == 1)

			{
				PlayerWin(playerTwo);
				break;
			}


			full = FullBoard(board);


			if (full == 9)

			{

				cout << "Board full, draw!" << endl;
				break;

			}

			// Option to stop the game

			cout << "Press the 'ESC' key to stop the game. Press another key to continue: " << endl;


			while (true) {
				if (_kbhit()) {  // Check if any key has been pressed on the keyboard
					char key = _getch();  // Get pressed key
					if (key == 27) {  // Check ESC key
						cout << "The game has been paused!" << endl;


						cout << "Press 2 to restart the game. Press another key to exit: " << endl;

						char key2 = _getch();  // Get pressed key

						if (key2 == 50)

						{
							// Game restart procedures
							for (int i = 1; i <= 9; i++)
							{
								for (int ix = 1; ix <= 9; ix++)
								{
									board[i][ix] = '*';
								}
							}

							main(); // restart the game by calling main function again
						}

						else

						{
							cout << "Goodbye!" << endl;
							exit(0);
							break;
						}

					}
					else
						break;

				}

			}


		} while (true);

	}
	else {
		cout << "The file could not be opened." << endl;
	}

}