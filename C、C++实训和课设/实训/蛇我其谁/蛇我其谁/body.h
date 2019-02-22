#pragma once
#include<iostream>
#include<Windows.h>
#include<deque>
#include <conio.h>
#include<time.h>
using namespace std;
#define INDEX_MAX 5
const int FlashIndex[INDEX_MAX] = { 1,2,3,4 };
int ColorIndex = 0;
class Point
{
private:
	int x, y;
public:
	int rex()
	{
		return x;
	}
	int rey()
	{
		return y;
	}
	Point() {}
	Point(int a, int b)
	{
		x = a;
		y = b;
	}
	static void setoutpoint(int x, int y, HANDLE hout)
	{
		COORD position;
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(hout, position);
	}
	void setpoint(int a, int b)
	{
		this->x = a;
		this->y = b;
	}
	void plot(HANDLE hout)
	{
		setoutpoint(x, y, hout);
		cout << "��";
	}
	bool operator == (Point& point)
	{
		return (point.x == this->x) && (point.y == this->y);
	}
	void Clear()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		cout << " ";
	}
	void Clear(HANDLE hout)
	{
		setoutpoint(x, y, hout);
		cout << "  ";
	}
};

class FOOD
{
private:
	Point position;
public:
	FOOD()
	{
		position.setpoint(20, 20);
	}
	Point& getpoint()
	{
		return position;
	}
	FOOD(int x, int y)
	{
		position.setpoint(x, y);
	}
	void showmyfood(int a, int b)
	{
		position.setpoint(a, b);
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		Point::setoutpoint(a, b, hout);
		cout << "��";
	}
	void Show()
	{
		cout << '(' << position.rex() << ',' << position.rey() << ')';
	}
};

class sshow
{
public:
	int showstart()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "������������������������������������������������������������������������" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "����                                                                ����" << endl;
		cout << "����             �����                                           ����" << endl;
		cout << "����           ����񦨡��        �~                             ����" << endl;
		cout << "����          ������                                            ����" << endl;
		cout << "����         ��                                                     ����" << endl;
		cout << "����          ��                                                    ����" << endl;
		cout << "����            ��                                                  ����" << endl;
		cout << "����              ��                                                ����" << endl;
		cout << "����       ��      ��                                               ����" << endl;
		cout << "����        �����                                                ����" << endl;
		cout << "����                                                                ����" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "����                                           1.��ʼ��Ϸ           ����" << endl;
		cout << "����                                           2.�˳���Ϸ           ����" << endl;
		cout << "����                                                                ����" << endl;
		cout << "����                                                                ����" << endl;
		cout << "����                                                                ����" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "������������������������������������������������������������������������" << endl;
		int choose;
		cin >> choose;
		return choose;
	}
	int  setgame()//δ���
	{
		int chooselevel;
		system("cls");
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "������������������������������������������������������������������������" << endl;
		cout << "����                                                                ����" << endl;
		cout << "����             �����                                           ����" << endl;
		cout << "����           ����񦨡��        �~                             ����" << endl;
		cout << "����          ������                                            ����" << endl;
		cout << "����         ��                                                     ����" << endl;
		cout << "����          ��                                                    ����" << endl;
		cout << "����            ��                                                  ����" << endl;
		cout << "����              ��                                                ����" << endl;
		cout << "����       ��      ��                                               ����" << endl;
		cout << "����        �����                                                ����" << endl;
		cout << "����                                                                ����" << endl;
		cout << "����                       Chose difficulity :                      ����" << endl;
		cout << "����                                              1.Easy            ����" << endl;
		cout << "����                                              2.Normal          ����" << endl;
		cout << "����                                              3.Hard            ����" << endl;
		cout << "����                                                                ����" << endl;
		cout << "������������������������������������������������������������������������" << endl;
		cin >> chooselevel;
		return chooselevel;
	}



	void Gameover()
	{
		system("cls");
		ColorIndex++;
		ColorIndex %= INDEX_MAX;
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FlashIndex[ColorIndex]);//FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		printf("                                                    ����������                                           \n");
		printf("                                                  ������������                                         \n");
		printf("                                                 �������������                                        \n");
		printf("                                                ��      ������      ��                                       \n");
		printf("                                               ��        �����        ��                                      \n");
		printf("                                               ��         ����         ��                                      \n");
		printf("                                                ��       �����       ��                                       \n");
		printf("                                                 ������     ������                                       \n");
		printf("                                                 �������������                                        \n");
		printf("                                                  ���    ����    ���                                         \n");
		printf("                                                                                                                 \n");
		SetConsoleTextAttribute(hOut, FlashIndex[(ColorIndex + 2) % INDEX_MAX]);// FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("          �~�~         �~          �~      �~     �~�~�~           �~�~     �~      �~   �~�~�~    �~�~�~�~     \n");
		printf("       �~            �~  �~      �~  �~   �~ �~   �~             �~    �~    �~    �~    �~        �~      �~   \n");
		printf("       �~   �~�~    �~ �~ �~    �~   �~   �~  �~  �~�~�~        �~      �~    �~  �~     �~�~�~    �~�~�~�~     \n");
		printf("       �~     �~   �~      �~   �~    �~ �~   �~  �~             �~    �~      �~�~      �~        �~    �~     \n");
		printf("         �~�~�~   �~        �~  �~     �~     �~  �~�~�~           �~�~         �~       �~�~�~    �~      �~   \n");
		printf("                                                                                                                \n");
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		printf("  ��������������������������������������������������������������������������������������������������������������                                                                                                                    ");
		printf("                                             DO YOU WANT TO PLAY AGAIN?                                          \n");
		printf("                                                                                                                 \n");
		printf("                                  1.YES                                      2.EXIT                              \n");
		printf("                                                                                                                 \n");

	}
	int re()
	{
		while (!_kbhit())
		{
			Gameover();
			Sleep(1000 / 6);
		}
		int choose3;
		cin >> choose3;
		return choose3;
	}

};

class csnake
{
private:
	deque <Point>snake;
	int direction;
public:
	csnake()        //�߳�ʼʱ��ֻ��������Ԫ�����,��ʼ�ƶ������趨Ϊ����  
	{
		snake.push_back(Point(18, 16));
		snake.push_back(Point(16, 16));
		direction = 4;
	}
	void setdirection(int x)
	{
		direction = x;
	}
	Point& head()
	{
		return *snake.begin();
	}
	Point& end()
	{
		return *(snake.end() - 1);
	}
	bool ChangeDirection(int direction)
	{
		if ((direction + 2) % 4 == this->direction || (direction + 2 == this->direction&&this->direction == 4))
			//������뷽�����ߵ�ǰ�ƶ������෴�����ı��ʱ�ߵ�ǰ������  
			return false;
		else
			this->direction = direction;
		return true;
	}
	void move()
	{

		switch (direction)//���ݴ�ʱ�ķ������жϸ�����ƶ����ƶ�ʱΪ���Ч�ʽ�ֻ��Ҫ������β��Ԫ��  
		{

		case 3:
			snake.push_front(Point(snake.begin()->rex(), snake.begin()->rey() + 1));
			break;
		case 2:
			snake.push_front(Point(snake.begin()->rex() - 2, snake.begin()->rey()));
			break;

		case 4:

			snake.push_front(Point(snake.begin()->rex() + 2, snake.begin()->rey()));
			break;

		case 1:
			snake.push_front(Point(snake.begin()->rex(), snake.begin()->rey() - 1));
			break;
		}
		snake.pop_back();
	}

	void PaintSnake(HANDLE hout)//��ʼ������
	{
		for (Point& point : snake)
		{
			Point::setoutpoint(point.rex(), point.rey(), hout);
			point.plot(hout);
		}
	}
	bool hitme()//�Ե��Լ�
	{
		for (Point& point : snake)
		{
			if (point == *snake.begin())
			{
				if (&point == &(*snake.begin()))    //��������ͷ����ͷ�غϵ������  
					continue;
				else
					return true;
			}
		}
		return false;
	}
	bool foodonme(Point& point)//ʳ��������Լ�����
	{
		for (Point& pointInSnake : snake)
		{
			if (point == pointInSnake)
				return true;
		}
		return false;
	}
	bool HitEdge()//��Ĭ��ǽ��λ�ý��бȽ�  
	{
		int x = snake.begin()->rex();
		int y = snake.begin()->rey();
		if ((x == 0) || (y == 2) || (x == 78) || (y == 24))
			return true;
		else
			return false;
	}
	bool Eat(FOOD& food)//�����ж�ʳ���Ƿ�����ͷ�ƶ������ϵ�ǰ��
	{

		int foodx = food.getpoint().rex();
		int foody = food.getpoint().rey();
		int headx = head().rex();
		int heady = head().rey();
		bool toEat = ((foodx == headx) && (foody == (heady + 1)) && (direction == 3))
			|| ((foodx == headx) && (foody == (heady - 1)) && (direction == 1))
			|| (((foodx + 2) == headx) && (foody == heady) && (direction == 2))
			|| (((foodx - 2) == headx) && (foody == heady) && (direction == 4));
		if (toEat)
		{
			snake.push_front(food.getpoint());
			return true;
		}
		else
			return false;
	}
};

class game :public sshow
{
private:
	csnake ssnake;
	FOOD food;
	int chang;
	int kuan;
	int score;
	int speed = 500;
public:
	bool DirectionChanged()
	{
		char ch;
		if (_kbhit())
		{
			ch = _getch();
			switch (ch)
			{
			case 'w':case 'W':
				return ssnake.ChangeDirection(1);
			case 'a':case 'A':
				return ssnake.ChangeDirection(2);
			case 's':case 'S':
				return  ssnake.ChangeDirection(3);
			case 'd':case 'D':
				return  ssnake.ChangeDirection(4);
			}
		}
		return false;
	}
	void RandomFood(FOOD& food)
	{
		srand(static_cast<unsigned>(time(NULL)));
		int x, y;
		while (true)
		{
			x = rand() % (chang / 2) * 2;
			y = rand() % (kuan / 2) * 2;
			if ((x <= 2) || (y <= 6) || (x >= 70) || (y >= 20))
				continue;
			if (!ssnake.foodonme(Point(x, y)))
				break;
			else
				continue;
		}
		food.showmyfood(x, y);
	}
	void setspeed(int choose2)
	{
		speed = choose2;
	}
	void PaintEdge()
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		for (int x = 0; x <= 78; x += 2)
		{
			for (int y = 0; y < 25; y++)
			{
				if ((x == 0) || (y == 0) || (x == 78) || (y == 24))
				{
					Point::setoutpoint(x, y, hOut);
					cout << "��";
				}
			}
		}

		for (int x = 2; x <= 78; x += 2)
		{
			Point::setoutpoint(x, 2, hOut);
			cout << "��";
		}
	}
	void playgame()
	{

		system("cls");
		void PaintEdge();
		{
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			for (int x = 0; x <= 78; x += 2)
			{
				for (int y = 0; y < 25; y++)
				{
					if ((x == 0) || (y == 0) || (x == 78) || (y == 24))
					{
						Point::setoutpoint(x, y, hOut);
						cout << "��";
					}
				}
			}

			for (int x = 2; x <= 78; x += 2)
			{
				Point::setoutpoint(x, 2, hOut);
				cout << "��";
			}
		}
		food.showmyfood(20, 20);
		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		ssnake.PaintSnake(hout);
		while (true)
		{
			ssnake.end().Clear(hout);
			DirectionChanged();
			bool eaten = ssnake.Eat(food);
			if (!eaten)
				ssnake.move();
			else
				RandomFood(food);
			//UpdateScore(eaten);
			//����ǰ��������Ϊ�ڵװ�ɫ  
			SetConsoleTextAttribute(hout, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			ssnake.head().plot(hout);
			if (ssnake.HitEdge() || ssnake.hitme())
			{
				Sleep(1000);
				SetConsoleTextAttribute(hout, FOREGROUND_RED | FOREGROUND_RED);
				ssnake.head().plot(hout);
				Sleep(1000);
				break;
			}
			Sleep(speed);
		}
	}
	int start()
	{
		int choose, choose2, choose3 = 2;
		system("cls");
		choose = showstart();
		while (choose != 2)
		{
			switch (choose)
			{
			case 1:
				choose2 = setgame();
				system("cls");
				if (choose2 == 1)
					setspeed(600);
				else if (choose2 == 2)
					setspeed(450);
				else
					setspeed(150);
				playgame();
				choose3 = re();
				break;
			case 2:
				break;
			}
			return choose3;
		}

	}
};