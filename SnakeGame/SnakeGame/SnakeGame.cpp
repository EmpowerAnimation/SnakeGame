#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool GameOver;

const int ScreenWidth = 20;
const int ScreenHeight = 20;
int SnakeX, SnakeY, FruitX, FruitY, Score;
int TailX[100], TailY[100], TailLength;

enum SnakeDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
SnakeDirection SnakeDir;

void Setup() 
{
	GameOver = false;
	SnakeDir = STOP;
	SnakeX = ScreenWidth / 2;
	SnakeY = ScreenHeight / 2;
	FruitX = rand() % ScreenWidth;
	FruitY = rand() % ScreenHeight;
	Score = 0;
}

void Draw()
{
	system("cls"); //system("clear");
	system("color 0A");

	for (int i = 0; i < ScreenWidth + 2; i++)
	{
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < ScreenHeight; i++) {
		for (int j = 0; j < ScreenWidth; j++) {
			if (j == 0) cout << "#";

			if (i == SnakeY && j == SnakeX)
				cout << "O";
			else if (i == FruitY && j == FruitX)
				cout << "F";
			else {
				bool Print = false;
				for (int k = 0; k < TailLength; k++) {
					if (TailX[k] == j && TailY[k] == i) {
						cout << "o";
						Print = true;
					}
				}
				if (!Print)
					cout << " ";
			}

			if (j == ScreenWidth - 1) cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < ScreenWidth + 2; i++) 
	{
		cout << "#";
	}

	cout << endl;
	cout << "Score: " << Score;

}

void Input()
{
	if (_kbhit())
	{
		switch (_getch()) 
		{
			case 'a':
				SnakeDir = LEFT;
				break;
			case 'd': 
				SnakeDir = RIGHT;
				break;
			case 'w':
				SnakeDir = UP;
				break;
			case 's': 
				SnakeDir = DOWN;
				break;
			case 'x':
				GameOver = true;
				break;
		}
	}
}

void Logic() 
{
	int PreviousX = TailX[0];
	int PreviousY = TailY[0];
	int Previous2X, Previous2Y;
	TailX[0] = SnakeX;
	TailY[0] = SnakeY;

	for (int i = 1; i < TailLength; i++) {
		Previous2X = TailX[i];
		Previous2Y = TailY[i];
		TailX[i] = PreviousX;
		TailY[i] = PreviousY;
		PreviousX = Previous2X;
		PreviousY = Previous2Y;
	}

	switch (SnakeDir) {
		case LEFT:
			SnakeX--;
			break;
		case RIGHT: 
			SnakeX++;
			break;
		case UP: 
			SnakeY--;
			break;
		case DOWN:
			SnakeY++;
			break;
		default: 
			break;
	}

	//if (SnakeX > ScreenWidth || SnakeX < 0) GameOver = true;
	//else if (SnakeY > ScreenHeight || SnakeY < 0) GameOver = true;

	if (SnakeX >= ScreenWidth) SnakeX = 0; else if (SnakeX < 0) SnakeX = ScreenWidth - 1;
	if (SnakeY >= ScreenHeight) SnakeY = 0; else if (SnakeY < 0) SnakeY = ScreenHeight - 1;

	for (int i = 0; i < TailLength; i++) {
		if (TailX[i] == SnakeX && TailY[i] == SnakeY) GameOver = true;
	}

	if (SnakeX == FruitX && SnakeY == FruitY) {
		Score += 10;
		FruitX = rand() % ScreenWidth;
		FruitY = rand() % ScreenHeight;
		TailLength++;
	}
}

int main() {
	Setup();
	
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
	
	return 0;
}