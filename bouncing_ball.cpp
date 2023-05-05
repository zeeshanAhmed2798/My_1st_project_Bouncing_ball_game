#include <iostream>
#include <windows.h>
#include <conio.h>


#define SCREEN_WIDTH 52
#define SCREEN_HEIGHT 20

#define MINX 2
#define MINY 2
#define MAXX 49
#define MAXY 19

using namespace std;
void for_menu(); // Proto_type.
int bricks[24][2] = { {2,7},{2,12},{2,17},{2,22},{2,27},{2,32},{2,37},{2,42},// to display bricks, basically it is position of brics.It's right side show x-axis and left show y-axis.
					 {4,7},{4,12},{4,17},{4,22},{4,27},{4,32},{4,37},{4,42},
					 {6,7},{6,12},{6,17},{6,22},{6,27},{6,32},{6,37},{6,42}

};
int visible_bricks[24] = { 1,1,1,1,     1,1,1,1,     1,1,1,1,     1,1,1,1, 1,1,1,1,  1,1,1,1 };// for destroy bricks.
int bar_pos[2] = { 18,22 };  //for slider position.
int ball_pos[2] = { 17,26 };// for ball position.
int dir = 1;                      // for directions.
int bricks_left = 24;// to count left bricks.
int win = 0;  
int lose = 0;
int start_ball = 0;
int level = 0;
int score_pos[2] = { 4,54 };
void gotoxy(int x, int y)
{
	COORD b;
	b.X = x;
	b.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), b);
}

void draw_border()
{
	gotoxy(0, 0);
	{
		cout << "-----------------------------------------------------";
	}
	gotoxy(0, SCREEN_HEIGHT);
	{
		cout << "-----------------------------------------------------";
	}
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		gotoxy(0, i);
		{
			cout << "|";
		}
		gotoxy(SCREEN_WIDTH, i);
		{
			cout << "|";
		}

	}

}
void draw_bricks()
{
	for (int i = 0; i < 24; i++)
	{
		if (visible_bricks[i] == 1)
		{
			gotoxy(bricks[i][1], bricks[i][0]);
			{

				cout << "|____| ";
			}
		}
	}
}
void ball_hit_bar()
{
	if (ball_pos[1] >= bar_pos[1] && ball_pos[1] <= bar_pos[1] + 8)
	{
		if (ball_pos[0] == bar_pos[0] - 1)
		{
			if (dir == 3)
			{
				dir = 2;
			}

			else if (dir == 4)
			{
				dir = 1;
			}
		}
	}
}
void ball_hit_bricks()
{
	for (int i = 0; i < 24; i++)
	{
		if (visible_bricks[i] == 1)
		{
			if (ball_pos[1] >= bricks[i][1] && ball_pos[1] <= bricks[i][1] + 8)
			{
				if (ball_pos[0] == bricks[i][0])
				{
					visible_bricks[i] = 0;
					bricks_left--;
				}
			}
		}
	}
}
void instruction()
{
	system("cls");
	cout << "instructions ";
	cout << " ------------------------------";
	cout << "\n use 'a' key to move bar left ";
	cout << "\n use 'd' key to move slider right";
	cout << "\n press space bar to start game : ";
	cout << "\n\n press G key to back to menu ";
	char kay = _getch();
	if (kay == 'G' || kay == 'g')
	{
		for_menu();
	}

}
void play1()
{
	while (1)
	{

		system("cls");
		draw_border();
		draw_bricks();
		gotoxy(bar_pos[1], bar_pos[0]);
		{
			cout << "==========";
		}

		gotoxy(ball_pos[1], ball_pos[0]);
		{
			cout << "0";
			if (_kbhit())
			{

				char ch = _getch();
				if (ch == 'D' || ch == 'd' || ch == 77)
				{
					if (bar_pos[1] < 42)
					{
						bar_pos[1] = bar_pos[1] + 4;
					}
				}
				if (ch == 'a' || ch == 'A' || ch == 75)
				{
					if (bar_pos[1] > 2)
					{
						bar_pos[1] = bar_pos[1] - 4;
					}
				}
				if (ch == 32)
				{
					start_ball = 1;
				}
				if (ch == 27)
				{
					break;
				}

			}
			if (start_ball == 1)
			{
				if (dir == 1)//top right
				{
					ball_pos[0] = ball_pos[0] - 1;
					ball_pos[1] = ball_pos[1] + 2;
					if (ball_pos[1] > MAXX)
					{
						dir = 2;
					}
					else if (ball_pos[0] < MINY)
					{
						dir = 4;
					}
				}
				else if (dir == 2)//top left
				{
					ball_pos[0] = ball_pos[0] - 1;
					ball_pos[1] = ball_pos[1] - 2;
					if (ball_pos[0] < MINY)
					{
						dir = 3;
					}
					else if (ball_pos[1] < MINX)
					{
						dir = 1;
					}
				}
				else if (dir == 3) //bottom left
				{
					ball_pos[0] = ball_pos[0] + 1;
					ball_pos[1] = ball_pos[1] - 2;
					if (ball_pos[1] < MINX)
					{
						dir = 4;
					}
					else if (ball_pos[0] > MAXY)
					{
						lose = 1;
						break;
					}
				}
				else if (dir == 4)//bottom right
				{
					ball_pos[0] = ball_pos[0] + 1;
					ball_pos[1] = ball_pos[1] + 2;
					if (ball_pos[0] > MAXY)
					{
						lose = 1;
						break;
					}
					else if (ball_pos[1] > MAXX)
					{
						dir = 3;
					}
				}
				ball_hit_bar();


			}
			ball_hit_bricks();
			if (bricks_left == 0)
			{
				win = 1;
				break;
			}


			Sleep(95);
		}



	}

	if (lose == 1)
	{
		system("cls");
		gotoxy(10, 5); cout << " -------------------------------------------";
		gotoxy(10, 6); cout << "             YOU LOSE                       ";
		gotoxy(10, 7); cout << "                                            ";
		gotoxy(10, 8); cout << "--------------------------------------------";
		gotoxy(10, 9); cout << "E key to exit ";
		char kay = _getch();
		if (kay == 'e' || kay == 'E')
		{
			exit(0);
		}
	}
	if (win == 1)
	{
		system("cls");
		gotoxy(10, 5); cout << " -------------------------------------------";
		gotoxy(10, 6); cout << "             YOU WIN                        ";
		gotoxy(10, 7); cout << "                                            ";
		gotoxy(10, 8); cout << "--------------------------------------------";
		gotoxy(10, 9); cout << "any G to go back ";
		char kay = _getch();
		if (kay == 'G' || kay == 'g')
		{
			for_menu();
		}
	}

}

void play2()
{
	{
		while (1)
		{

			system("cls");
			draw_border();
			draw_bricks();
			gotoxy(bar_pos[1], bar_pos[0]);
			{
				cout << "=======";
			}

			gotoxy(ball_pos[1], ball_pos[0]);
			{
				cout << "0";
				if (_kbhit())
				{

					char ch = _getch();
					if (ch == 'D' || ch == 'd' || ch == 77)
					{
						if (bar_pos[1] < 42)
						{
							bar_pos[1] = bar_pos[1] + 4;
						}
					}
					if (ch == 'a' || ch == 'A' || ch == 75)
					{
						if (bar_pos[1] > 2)
						{
							bar_pos[1] = bar_pos[1] - 3;
						}
					}
					if (ch == 32)
					{
						start_ball = 1;
					}
					if (ch == 27)
					{
						break;
					}

				}
				if (start_ball == 1)
				{
					if (dir == 1)//top right
					{
						ball_pos[0] = ball_pos[0] - 1;
						ball_pos[1] = ball_pos[1] + 2;
						if (ball_pos[1] > MAXX)
						{
							dir = 2;
						}
						else if (ball_pos[0] < MINY)
						{
							dir = 4;
						}
					}
					else if (dir == 2)//top left
					{
						ball_pos[0] = ball_pos[0] - 1;
						ball_pos[1] = ball_pos[1] - 2;
						if (ball_pos[0] < MINY)
						{
							dir = 3;
						}
						else if (ball_pos[1] < MINX)
						{
							dir = 1;
						}
					}
					else if (dir == 3) //bottom left
					{
						ball_pos[0] = ball_pos[0] + 1;
						ball_pos[1] = ball_pos[1] - 2;
						if (ball_pos[1] < MINX)
						{
							dir = 4;
						}
						else if (ball_pos[0] > MAXY)
						{
							lose = 1;
							break;
						}
					}
					else if (dir == 4)//bottom right
					{
						ball_pos[0] = ball_pos[0] + 1;
						ball_pos[1] = ball_pos[1] + 2;
						if (ball_pos[0] > MAXY)
						{
							lose = 1;
							break;
						}
						else if (ball_pos[1] > MAXX)
						{
							dir = 3;
						}
					}
					ball_hit_bar();


				}
				ball_hit_bricks();
				if (bricks_left == 0)
				{
					win = 1;
					break;
				}


				Sleep(60);
			}



		}


		if (lose == 1)
		{
			system("cls");
			gotoxy(10, 5); cout << " -------------------------------------------";
			gotoxy(10, 6); cout << "             YOU LOSE                       ";
			gotoxy(10, 7); cout << "                                            ";
			gotoxy(10, 8); cout << "--------------------------------------------";
			gotoxy(10, 9); cout << "press E key to exit ";
			char kay = _getch();
			if (kay == 'e' || kay == 'E')
			{
				exit(0);
			}
		}
		if (win == 1)
		{
			system("cls");
			gotoxy(10, 5); cout << " -------------------------------------------";
			gotoxy(10, 6); cout << "             YOU WIN                        ";
			gotoxy(10, 7); cout << "                                            ";
			gotoxy(10, 8); cout << "--------------------------------------------";
			gotoxy(10, 9); cout << "any ' G 'key to go back ";
			char kay = _getch();
			if (kay == 'G' || kay == 'g')
			{
				for_menu();
			}
		}

	}
}
void for_menu()
{
	gotoxy(10, 5); cout << "-------------------------------------------";
	gotoxy(10, 6); cout << "|           BREAK BREAKS \ BOUNCING BALL   |";
	gotoxy(10, 7); cout << "-------------------------------------------";
	gotoxy(10, 9); cout << "enter   1  for 'SIMPLE' level \t";
	gotoxy(10, 11); cout << "enter   2 for 'HARD' level \n\t ";
	gotoxy(10, 12); cout << "\n\tenter 3 for  instruction  ";
	gotoxy(10, 13); cout << " \n\tenter 4 for quit ";

	char op = _getch();
	if (op == '1')
	{
		play1();
	}
	else if (op == '2')
	{
		play2();
	}

	else if (op == '3')
	{
		instruction();
	}
	else if (op == '4')
	{
		exit(0);
	}
}


int main()
{

	do {
		system("cls");
		for_menu();
	} while (1);
	{
		cout << "entrer 1 or 2 " << endl;
		char en = 0;
		cin >> en;
		if (en == '1')
		{
			play1();
		}
		else if (en == '2')
		{
			play2();
		}
		else if (en == '3')
		{
			instruction();
		}
		else if (en == '4')
		{
			exit(0);
		}
	}
	return 0;
}

