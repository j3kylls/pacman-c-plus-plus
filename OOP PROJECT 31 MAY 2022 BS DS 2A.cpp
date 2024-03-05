#include <iostream>
#include <fstream>
#include <cmath>
#include<string>
#include <time.h>
#include <windows.h>
#include<mygraphics.h>
#include<cstdlib>

using namespace std;

const int gridRows = 24; // total number of rows for grid
const int gridCols = 88; // total number of columns for grid

const char gridChar = 178; // ASCII character used to make boundaries & obstacles
const char point = 250; // ASCII character used to make points
const char energizer = 254; // ASCII character used to make energizer
char preItem = point; //previous item status
char preItem1 = ' ';

char item = ' ';
char item1 = ' ';

char pacChar = 'O';
 //array to store grid

char GRID[24][88];

bool flag = true;

int pacX = 15;
int pacY = 20;
int lives=3;


double distance(int x1, int y1, int x2, int y2) //calculate distance using distance formula
{
	int result = pow((x1 - x2), 2) + pow((y1 - y2), 2);
	return sqrt(result);
}


//class Pinky :public Pacman //approach AI ghost 2
//{
//private:
//	char pinky;
//	int pinkyR;
//	int pinkyC;
//public:
//	Pinky()
//	{
//		pinky = 'P';
//		pinkyR = 4;
//		pinkyC = 28;
//	}
//	//to make a function to store pinky in home<3
//	bool moveGhost()
//	{
//		blinkyMovement(pinkyR, pinkyC, getPacR(), getPacC(), preMove, preItem, pinky);
//	}
//
//};
//
//
class Map
{
	//class for map ----
protected:

	
	

public:

	Map()
	{
		/*for (int i = 0; i < gridRows; i++)
		{
			for (int j = 0; j < gridCols; j++)
			{
				GRID[i][j] = 0;
			}
		}*/

	}

	void gridStore(int m = 10, int n = 19, char P = 'O')
	{
		//storing grid in array - - -

		for (int i = 1; i <= gridRows; i++)
		{
			for (int j = 1; j <= gridCols; j++)
			{
				if ((j == 1) && (i == 13 || i == 12)) //tunnel for teleportation left
				{
					GRID[i][j] = ' ';
				}
				else if ((i == 11 || i == 14) && (j >= 2 && j <= 18)) //obstacle
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 11 || i == 14) && (j >= 71 && j <= 87)) //obstacle
				{
					GRID[i][j] = gridChar;
				}
				else if ((j == 18 || j == 70) && (i >= 4 && i <= 8)) //more obstacle
				{
					GRID[i][j] = gridChar;
				}
				else if ((j == 12 || j == 74) && (i >= 17 && i <= 21)) //more obstacle
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 21) && (j >= 13 && j <= 73)) //even more obstacle
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 8) && (j >= 18 && j <= 29)) //even more obstacle
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 8) && (j >= 59 && j <= 70)) //a million obstacles later
				{
					GRID[i][j] = gridChar;
				}
				else if (j == 1 || i == 1) //top & left boundary
				{
					GRID[i][j] = gridChar;
				}
				else if ((j == gridCols) && (i == 13 || i == 12)) //tunnel for teleportation right
				{
					GRID[i][j] = ' ';
				}
				else if (i == gridRows || j == gridCols) //bottom & right boundary
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 10 || i == 11 || i == 12 || i == 13 || i == 14) && (j == 39 || j == 40 || j == 41 || j == 42 || j == 43 || j == 44 || j == 45 || j == 46 || j == 47 || j == 48 || j == 49))
				{
					GRID[i][j] = gridChar; //house in middle
				}

				//proceeding to make obstacles
				else if ((i == 14 || i == 15 || i == 16 || i == 17) && (j == 44))
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 18) && (j >= 37 && j <= 43))
				{
					GRID[i][j] = gridChar;
				}
				else if ((i == 18) && (j >= 45 && j <= 51))
				{
					GRID[i][j] = gridChar;
				}
				else if ((j == 36 || j == 52) && (i >= 17 && i <= 18))
				{
					GRID[i][j] = gridChar;
				}
				else //rest of the grid
				{
					if (GRID[i][j] != gridChar)
					{
						if (j % 2 == 0) //points at even positions
						{
							GRID[i][j] = point;
						}
						else
							GRID[i][j] = ' ';
					}
				}
			}
		}
		GRID[m][n] = P;
	}

	void PrintGrid() //parameterized for Pacman
	{
		//gridStore();
		HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);  //method to change console text color
		for (int i = 1; i <= gridRows; i++)
		{
			for (int j = 1; j <= gridCols; j++)
			{
				if (GRID[i][j] == gridChar)
				{
					SetConsoleTextAttribute(color, 1);
					cout << GRID[i][j];
				}
				else if (GRID[i][j] == 'C') //use get ghost char
				{
					SetConsoleTextAttribute(color, 6);
					cout << GRID[i][j];
				}
				else if (GRID[i][j] == 'P') //use get ghost char
				{
					SetConsoleTextAttribute(color, 13);
					cout << GRID[i][j];
				}
				else if (GRID[i][j] == 'B') //use get ghost char
				{
					SetConsoleTextAttribute(color, 12);
					cout << GRID[i][j];
				}
				else if (GRID[i][j] == 'O') //use get pacman char
				{
					SetConsoleTextAttribute(color, 14);
					cout << GRID[i][j];
				}
				else
				{
					SetConsoleTextAttribute(color, 15);
					cout << GRID[i][j];
				}
			}
			cout << endl;
		}
	}
};

class Pacman :public Map
{
private:

	char Pac;
	int score;
	

public:

	Pacman()
	{
		lives = 3;
		score = 0;
		Pac = 'O';
		pacX = 15;
		pacY = 20;
	}

	void store()
	{
		gridStore(pacX, pacY, Pac);
	}

	void ResetPacman()
	{
		lives--;
		GRID[pacX][pacY] = ' ';
		pacX = 15;
		pacY = 20;
		GRID[15][20] = Pac;

	}

	void checkgamstate()
	{
		if (lives < 1)
			flag = false;

	}
	
	/*int getlives() {

		return lives;
	}

	void setlives(int a) {

		lives=a;
	}*/

	void calculateScore()
	{
		score = score + 10;
		//if (GRID[pacX][pacY] == 'o') energizerIterations = 30;
	}

	void movePacmanLeft()
	{
		if (GRID[pacX][pacY - 1] == ' ' || GRID[pacX][pacY - 1] == point || GRID[pacX][pacY - 1] == 'o')
		{

			GRID[pacX][pacY] = ' ';
			pacY = pacY - 1;
			if (GRID[pacX][pacY] == point || GRID[pacX][pacY] == 'o')
			{
				calculateScore();
			}
			GRID[pacX][pacY] = Pac;
		}
	}

	void movePacmanRight()
	{
		if (GRID[pacX][pacY + 1] == ' ' || GRID[pacX][pacY + 1] == point || GRID[pacX][pacY + 1] == 'o')
		{
			GRID[pacX][pacY] = ' ';
			pacY = pacY + 1;
			if (GRID[pacX][pacY] == point || GRID[pacX][pacY] == 'o')
			{
				calculateScore();
			}
			GRID[pacX][pacY] = Pac;
		}
	}

	void movePacmanUp()
	{
		if (GRID[pacX - 1][pacY] == ' ' || GRID[pacX - 1][pacY] == point || GRID[pacX - 1][pacY] == 'o')
		{
			GRID[pacX][pacY] = ' ';
			pacX = pacX - 1;
			if (GRID[pacX][pacY] == point || GRID[pacX][pacY] == 'o')
			{
				calculateScore();
			}
			GRID[pacX][pacY] = Pac;
		}

	}

	void movePacmanDown()
	{
		if (GRID[pacX + 1][pacY] == ' ' || GRID[pacX + 1][pacY] == point || GRID[pacX + 1][pacY] == 'o')
		{
			GRID[pacX][pacY] = ' ';
			pacX = pacX + 1;
			if (GRID[pacX][pacY] == point || GRID[pacX][pacY] == 'o')
			{
				calculateScore();
			}
			GRID[pacX][pacY] = Pac;
		}
	}

	void printScore()
	{
		cout << endl << "Score: " << score << endl;
		cout << "Lifes: " << lives << endl;
	}

};

class Clyde : public Pacman	//random movement ghost
{
private:

	char clyde;
	int clydeR;
	int clydeC;

public:
	Clyde()
	{
		clyde = 'C';
		clydeR = 9;
		clydeC = 45;
	}
	//to make a function to store clyde in home<3



	bool moveGhost()
	{
		clydeMovement(clydeR, clydeC, clyde, preItem);

		return true;
	}

	int clydeDirection() //determining direction of Clyde
	{
		srand(time(0));
		int result = 1 + (rand() % 4);
		return result;
	}

	bool clydeMovement(int& m, int& n, char C = 'C', char preItem = point)
	{
		int move = clydeDirection();

		if (move == 1) // if clyde goes up
		{
			if (GRID[m][n - 1] == ' ' || GRID[m][n - 1] == point || GRID[m][n - 1] == energizer || GRID[m][n - 1] == pacChar) //have to add condition for pacman
			{

				GRID[m][n] = item; //clears up path according to grid status
				n = n - 1;
				item = GRID[m][n]; //new position for clyde

				if (item == pacChar) //if clyde hits pacman
				{
					item = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}
		if (move == 2) // clyde goes down
		{
			if (GRID[m][n + 1] == ' ' || GRID[m][n + 1] == point || GRID[m][n + 1] == pacChar || GRID[m][n + 1] == energizer)
			{

				GRID[m][n] = item;
				n = n + 1;
				item = GRID[m][n];
				if (item == pacChar)
				{
					item = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}
		if (move == 3) // clyde goes left
		{
			if (GRID[m - 1][n] == ' ' || GRID[m - 1][n] == point || GRID[m - 1][n] == pacChar || GRID[m - 1][n] == energizer)
			{

				GRID[m][n] = item;
				m = m - 1;
				item = GRID[m][n];
				if (item == pacChar)
				{
					item = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}
		if (move == 4) // clyde goes right
		{
			if (GRID[m + 1][n] == ' ' || GRID[m + 1][n] == point || GRID[m + 1][n] == pacChar || GRID[m + 1][n] == energizer)
			{


				GRID[m][n] = item;
				m = m + 1;
				item = GRID[m][n];
				if (item == pacChar)
				{
					item = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}

		return 1;
	}

	void storeclyde()
	{
		GRID[clydeR][clydeC] = clyde;
	}

};


class Blinky :public Pacman //approach AI ghost 1
{
private:
	char blinky;
	int blinkyR;
	int blinkyC;
	int pMove;

public:
	Blinky()
	{
		blinky = 'B';
		blinkyR = 9;
		blinkyC = 50;
		pMove = -1;
	}
	//to make a function to store blinky in home<3
	bool moveGhost()
	{
		blinkyMovement(blinkyR, blinkyC, pacX, pacY, pMove, preItem, blinky);

		return 1;
	}

	void storeblinky()
	{
		GRID[blinkyR][blinkyC] = blinky;
	}

	bool blinkyMovement(int &m, int &n, int pacR, int pacC, int &preMove, char &preItem , char C = 'B')
	{
		int move = blinkyDirection(m, n, pacR, pacC, preMove);
		//preItem = ' ';
		if (move == 1) // if blinky goes up
		{
			if (GRID[m][n - 1] == ' ' || GRID[m][n - 1] == point || GRID[m][n - 1] == energizer || GRID[m][n - 1] == pacChar) //have to add condition for pacman
			{

				GRID[m][n] = item1; //clears up path according to grid status
				n = n - 1;
				item1 = GRID[m][n]; //new position for clyde

				if (item1 == pacChar) //if clyde hits pacman
				{
					item1 = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}
		if (move == 2) // blinky goes down
		{
			if (GRID[m][n + 1] == ' ' || GRID[m][n + 1] == point || GRID[m][n + 1] == pacChar || GRID[m][n + 1] == energizer)
			{

				GRID[m][n] = 1;
				n = n + 1;
				item1 = GRID[m][n];
				if (item1 == pacChar)
				{
					item1 = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}
		if (move == 3) // blinky goes left
		{
			if (GRID[m - 1][n] == ' ' || GRID[m - 1][n] == point || GRID[m - 1][n] == pacChar || GRID[m - 1][n] == energizer)
			{

				GRID[m][n] = item1;
				m = m - 1;
				item1 = GRID[m][n];
				if (item1 == pacChar)
				{
					item1 = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}
		if (move == 4) // blinky goes right
		{
			if (GRID[m + 1][n] == ' ' || GRID[m + 1][n] == point || GRID[m + 1][n] == pacChar || GRID[m + 1][n] == energizer)
			{


				GRID[m][n] = item1;
				m = m + 1;
				item1 = GRID[m][n];
				if (item1 == pacChar)
				{
					item1 = ' ';
					ResetPacman();
					return 0;
				}
				GRID[m][n] = C;
			}
		}

		return 1;
	}

	int blinkyDirection(int &m, int &n, int pacM, int pacN, int &preMove) //blinky boundary check
	{
		double d[] = { 0, 0, 0, 0 };

		//if space left blinky available
		if (GRID[m][n - 1] == ' ' || GRID[m][n - 1] == point || GRID[m][n - 1] == pacChar || GRID[m][n - 1] == energizer)
		{
			d[0] = distance(pacM, pacN, m, n - 1);
		}
		//if space right blinky available
		if (GRID[m][n + 1] == ' ' || GRID[m][n + 1] == point || GRID[m][n + 1] == pacChar || GRID[m][n + 1] == energizer)
		{
			d[1] = distance(pacM, pacN, m, n + 1);
		}
		//if space on blinky's above available
		if (GRID[m - 1][n] == ' ' || GRID[m - 1][n] == point || GRID[m - 1][n] == pacChar || GRID[m - 1][n] == energizer)
		{
			d[2] = distance(pacM, pacN, m - 1, n);
		}
		//if space on blinky's below available
		if (GRID[m + 1][n] == ' ' || GRID[m + 1][n] == point || GRID[m + 1][n] == pacChar || GRID[m + 1][n] == energizer)
		{
			d[3] = distance(pacM, pacN, m + 1, n);
		}

		int min = 0;
		if (preMove == 0)
			min = 1;
		for (int i = min + 1; i < 4; i++)
		{
			if (i == preMove)
				continue;
			if (d[i] < d[min])
				min = i;
		}

		if (d[min] == 0)
		{
			min = preMove;
		}

		preMove = min;

		return min + 1;
	}
};



int main()
{
	Pacman P;
	Clyde C;
	Map M;
	Blinky B;
	
	P.store();

	B.storeblinky();
	C.storeclyde();

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD destCoord;                //to set console cursor back
	destCoord.X = 0;
	destCoord.Y = 0;
	system("cls");
	Sleep(100);
	showConsoleCursor(false);

	while (flag==true)
	{
		SetConsoleCursorPosition(hStdout, destCoord);

		P.checkgamstate();
		M.PrintGrid();
		P.printScore();

		B.moveGhost();
		C.moveGhost();

		if (GetAsyncKeyState(0x41))
		{
			P.movePacmanLeft(); // Function call to move Pacman towards left
		}
		if (GetAsyncKeyState(0x44))
		{
			P.movePacmanRight(); // Function call to move Pacman towards right
		}
		if (GetAsyncKeyState(0x57))
		{
			P.movePacmanUp(); // Function call to move Pacman towards up
		}
		if (GetAsyncKeyState(0x53))
		{
			P.movePacmanDown(); // Function call to move Pacman towards down
		}
		if (GetAsyncKeyState(0x51))
		{
			break; // Stop the game
		}

	}

	
	return 0;
}