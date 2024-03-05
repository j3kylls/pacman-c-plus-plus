class Map
{
protected:
	int m;
	int n;
public:
	void gridStore(int m = 10, int n = 19, char P = 'O');
	void PrintGrid();
	bool isEnergizer(bool f);
};

class Pacman :public Map
{
private:
	char Pac;
	int score;
	
public:
	Pacman();
	void store();
	void ResetPacman();
	void checkgamstate();
	void setlives(int a);
	void calculateScore(int n = 5);
	void movePacmanLeft();
	void movePacmanRight();
	void movePacmanUp();
	void movePacmanDown();
	void printScore();
};

class Clyde : public Pacman
{
private:

	char clyde;
	int clydeR;
	int clydeC;

public:
	Clyde();
	void resetclyde(int m, int n);
	bool moveGhost();
	int clydeDirection();
	bool clydeMovement(int& m, int& n, char C = 'C', char preItem = point);
	void storeclyde();
};

class Blinky :public Pacman
{
private:
	char blinky;
	int blinkyR;
	int blinkyC;
	int pMove;

public:
	Blinky();
	void resetblinky(int m, int n);
	bool moveGhost();
	void storeblinky();
	bool blinkyMovement(int& m, int& n, int pacR, int pacC, int& preMove, char& preItem, char C = 'B');
	int blinkyDirection(int& m, int& n, int pacM, int pacN, int& preMove);
};