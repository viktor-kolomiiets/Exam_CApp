/*Создайте игру "Память".
Правила игры на английском языке можно прочесть по этой ссылке (https://www.memozor.com/memory-games/memory-game-rules).
Главные особенности реализации игры:
 - Выбор размера поля.
 - Начальная расстановка карт выполняется компьютером.
 - Звуковое сопровождение игры:
  > Если карты совпали, звучит один звук;
  > Если карты не совпали, звучит другой звук.
 - Статистика:
  > Время игры;
  > Количество переворотов карт
 - Used sound resources:
  > Voiceover Pack #1 by Kenney Vleugels for Kenney (www.kenney.nl)*/

#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "functions.h"
using namespace std;

int boardWidth = 0;		//count of cards by Horizontal-Axis
int boardHeight = 0;	//count of cards by Vertical-Axis
int playTime = 0;		//time spend from start of game
int flipCount = 0;		//count of card flip

struct Card
{
	int cardID = 0;
	int pixelMap[4][6]{};	//contain all characters of card
	int image[2][4]{};		//contain characters that draw image
	bool exist = true;

	//transfer to pixelMap characters that describe image
	void showImage()
	{
		for (int h = 1; h <= 2; h++)
			for (int w = 1; w <= 4; w++)
				pixelMap[h][w] = image[h - 1][w - 1];
	}

	//hide image by redrawing it character-177
	void hideImage()
	{
		for (int h = 1; h <= 2; h++)
			for (int w = 1; w <= 4; w++)
				pixelMap[h][w] = 177;
	}

	//transfer to pixelMap characters of empty card
	void drawBorder()
	{
		pixelMap[0][0] = 218;
		pixelMap[0][1] = 196;
		pixelMap[0][2] = 196;
		pixelMap[0][3] = 196;
		pixelMap[0][4] = 196;
		pixelMap[0][5] = 191;
		//-------------------
		pixelMap[1][0] = 179;
		pixelMap[1][1] = 32;
		pixelMap[1][2] = 32;
		pixelMap[1][3] = 32;
		pixelMap[1][4] = 32;
		pixelMap[1][5] = 179;
		//-------------------
		pixelMap[2][0] = 179;
		pixelMap[2][1] = 32;
		pixelMap[2][2] = 32;
		pixelMap[2][3] = 32;
		pixelMap[2][4] = 32;
		pixelMap[2][5] = 179;
		//-------------------
		pixelMap[3][0] = 192;
		pixelMap[3][1] = 196;
		pixelMap[3][2] = 196;
		pixelMap[3][3] = 196;
		pixelMap[3][4] = 196;
		pixelMap[3][5] = 217;
		//-------------------
	}

	//delete card image
	void toEmpty()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 6; j++)
				pixelMap[i][j] = 32;
		exist = false;
	}
};

struct Selection
{
	int w = 0;	//x-position of selected card
	int h = 0;	//y-position of selected card
};

Card** cboard;

void init()
{
	int selection = 0;
	for (;;)
	{
		system("cls");
		cout << "Select board size:\n 1. 4x4 cells\n 2. 6x8 cells\n 3. 8x10 cells\n 0. Back\n>> "; cin >> selection;
		if (selection == 0)
		{
			system("cls");
			break;
		}
		else if (selection == 1)
		{
			::boardHeight = 4;
			::boardWidth = 4;
			break;
		}
		else if (selection == 2)
		{
			::boardHeight = 6;
			::boardWidth = 8;
			break;
		}
		else if (selection == 3)
		{
			::boardHeight = 8;
			::boardWidth = 10;
			break;
		}
		else
		{
			cout << "Unknown command\n";
			continue;
		}
	}

	//create empty card table
	Card** buffer = new Card * [boardHeight];
	for (int i = 0; i < boardHeight; i++)
		buffer[i] = new Card[boardWidth];

	//initialise card identificator
	for (int i = 0; i < boardHeight / 2; i++)
		for (int j = 0; j < boardWidth; j++)
		{
			int figureID = rand() % IMAGE_COUNT;
			buffer[i][j].cardID = figureID;
			buffer[i + boardHeight / 2][j].cardID = figureID;
		}

	//mixing card positions
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
			swap(buffer[i][j].cardID, buffer[rand() % boardHeight][rand() % boardWidth].cardID);

	//initialise card's image
	for (int i = 0; i < boardHeight; i++)
		for (int j = 0; j < boardWidth; j++)
		{
			writeImage(buffer[i][j].cardID, buffer[i][j].image);
			buffer[i][j].drawBorder();
			buffer[i][j].hideImage();
		}

	cboard = buffer;
}

void drawBoard()
{
	//draw number of column
	for (int i = 0; i < boardWidth; i++)
		cout << "   " << i + 1 << "\t|";
	cout << "\n";

	for (int h = 0; h < boardHeight; h++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int w = 0; w < boardWidth; w++)
			{
				cout << " ";
				for (int x = 0; x < 6; x++)
					cout << (char)cboard[h][w].pixelMap[y][x];
				cout << " ";
			}
			if (y == 1)
				cout << "| " << h + 1 << "\n";
			else
				cout << "|\n";
		}
	}

	string divider(boardWidth * 8 + 6, '-');
	cout << divider << "\n";
	cout << " Count of card flips: " << flipCount << "\n";
	cout << divider << "\n";
}

void clearBoard()
{
	for (int i = 0; i < boardHeight; i++)
		if (cboard[i])
		{
			delete[] cboard[i];
			cboard[i] = nullptr;
		}
	if (cboard)
	{
		delete[] cboard;
		cboard = nullptr;
	}
}

void Update()
{
	system("cls");
	drawBoard();
}

//returns coordinates selected card
Selection selectCard()
{
	Selection select;

	for (;;)
	{
		cout << "Enter row\'s number   : "; cin >> select.h;
		select.h--;
		if (select.h >= 0 && select.h < boardHeight)
			break;
		else
		{
			cout << "Out of range. Selected coordinate doesn\'t exist\n";
			continue;
		}
	}

	for (;;)
	{
		cout << "Enter column\'s number: "; cin >> select.w;
		select.w--;
		if (select.w >= 0 && select.w < boardWidth)
			break;
		else
		{
			cout << "Out of range. Selected coordinate doesn\'t exist\n";
			continue;
		}
	}
	
	return select;
}

int main()
{
	srand(time(NULL));

	//get hwnd of window and set new position and new size of console window
	HWND hwnd;
	hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 250, 50, 1000, 720, TRUE);

	int menu = 0;
	for (;;)
	{
		::flipCount = 0;
		cout << "1. Start game\n2. Instructions\n0. Exit\n>> ";
		cin >> menu;

		if (menu == 0)
			break;
		else if (menu == 1)
		{
			//initialising card board
			init();
			int cardCount = boardHeight * boardWidth;
			int start_t = clock();
			int end_t = 0;

			for (; cardCount >= 2;)
			{
				Update();
				cout << "Select card:\n";
				Selection previous;

				for (;;)
				{
					previous = selectCard();

					if (cboard[previous.h][previous.w].exist)
						break;
					else
					{
						cout << "Selected card does not exist\n";
						continue;
					}
				}

				Card* prevCard = &cboard[previous.h][previous.w];
				prevCard->showImage();
				flipCount++;
				
				Update();
				Selection current;

				for (;;)
				{
					current = selectCard();

					if (current.h == previous.h && current.w == previous.w)
					{
						cout << "You already select this card. Enter other coordinates\n";
						continue;
					}
					else
					{
						if (cboard[current.h][current.w].exist)
							break;
						else
						{
							cout << "Selected card does not exist\n";
							continue;
						}
					}
				}
				
				Card* currCard = &cboard[current.h][current.w];
				currCard->showImage();
				flipCount++;
				Update();

				if (currCard->cardID == prevCard->cardID)
				{
					//cout << "\a";
					PlaySound(TEXT("correct.wav"), NULL, SND_FILENAME);
					Sleep(800);
					prevCard->toEmpty();
					currCard->toEmpty();
					cardCount -= 2;
				}
				else
				{
					//cout << "\a";
					//Sleep(600);
					//cout << "\a";
					PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME);
					Sleep(800);
					prevCard->hideImage();
					currCard->hideImage();
				}

				char confirm = '#';
				bool exit = false;
				if (cardCount > 2)
					for (;;)
					{
						Update();
						cout << "0. Quit (other number to continue)\n>> ";
						cin >> confirm;
						if (confirm == '0')
						{
							exit = true;
							break;
						}
						else
							break;
					}
				
				if (exit)
					break;
			}

			end_t = clock();
			int delta_t = (end_t - start_t) / CLOCKS_PER_SEC;
			int sec = delta_t % 60;
			int min = (delta_t / 60) % 60;
			int hour = (delta_t / 3600) % 24;

			//show game statistic
			string divider(boardWidth * 8 + 6, '-');
			char subMenu = '#';
			for (;;)
			{
				system("cls");
				cout << divider << "\n";
				if (cardCount < 2)
					cout << "\t---Congrats!!!---\n";
				cout << " Card reverse: " << flipCount << "\n";
				cout << " Time used: " << hour << " h " << min << " min "
					<< sec << " sec" << endl;
				cout << divider << "\n";

				cout << "0. Back\n>> "; cin >> subMenu;
				if (subMenu == '0')
					break;
				else
					continue;
			}

			system("cls");
			clearBoard();
		}
		else if (menu == 2)
		{
			string line1 = "At the beginning of the game, all the cards are mixed up and laid in rows, face down\n\
on the table.\n\nPlayer 1 starts and turns over two cards:\n\
 - If the cards don\'t match (it\'s not a pair), he turns them back overand it\'s then\n\
the turn of player 2 to turn over two new cards.\n\
 - However, if the two cards match, it\'s a pair! He keeps the cardsand has the right\n\
to play again.\n\nWhen the players have found all the pairs, the game is over. The player who has the\n\
most cards wins!\n\n";
			string instruction = "Most matching games on memozor are single player mode. \
As there is only one player,\nthe objective of the game is to find all the pairs with \
the fewest strokes and as\nquickly as possible. A stopwatch will show you how much time \
you have spent to find\nall the pairs and also the game will show you the number \
of strokes you have needed";
			
			char subMenu = '#';
			for (;;)
			{
				system("cls");
				cout << line1 << instruction << "\n\n";
				cout << "0. Back\n>> "; cin >> subMenu;
				if (subMenu == '0')
					break;
				else
					continue;
			}
			system("cls");
		}
		else
		{
			cout << menu << " is unknown command\n";
			continue;
		}
	}

	return 0;
}
