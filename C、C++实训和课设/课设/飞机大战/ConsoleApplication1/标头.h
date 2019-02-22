#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
#include<iomanip>
using namespace std;
int score, difficulty;
int scores[3];

class base
{
public:
	void drawRow(COORD a, COORD b, char ch)// ��a, b�������������ͬ��ǰ���£�������[a.x, b.y] ֮�����Ϊ ch
	{
		if (a.Y == b.Y)
			drawRow(a.Y, a.X, b.X, ch);
		else
		{
			SetPos(0, 25);
			cout << "�޷�����У���������������겻���";
			system("pause");
		}
	}
	void drawRow(int y, int x1, int x2, char ch)//�ѵ�y�У�[x1, x2) ֮����������Ϊ ch
	{
		SetPos(x1, y);
		for (int i = 0; i <= (x2 - x1); i++)
			cout << ch;
	}
	void drawCol(int x, int y1, int y2, char ch)//�ѵ�x�У�[y1, y2] ֮����������Ϊ ch
	{

		for (int y = y1; y != y2 + 1; y++)
		{
			SetPos(x, y);
			cout << ch;
		}
	}
	void drawCol(COORD a, COORD b, char ch)//��a,b ��������ͬ��ǰ���£������� [a.y, b.y] ֮�����Ϊ ch
	{
		if (a.X == b.X)
			drawCol(a.X, a.Y, b.Y, ch);
		else
		{
			SetPos(0, 25);
			cout << "�޷������,��Ϊ��������ĺ����겻���";
			system("pause");
		}
	}
	void SetPos(int i, int j)// ������ֵ�趨��
	{
		COORD pos = { i, j };
		SetPos(pos);
	}
	void SetPos(COORD a)//ͨ������趨�� 
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(out, a);
	}

	void HideCursor()//���ع�겢���ù����Ϊ1.
	{
		CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	}
	void drawFrame(int x1, int y1, int x2, int y2, char row, char col)//�������Ϻ����½����������һ�����ο��
	{
		drawRow(y1, x1 + 1, x2 - 1, row);
		drawRow(y2, x1 + 1, x2 - 1, row);
		drawCol(x1, y1 + 1, y2 - 1, col);
		drawCol(x2, y1 + 1, y2 - 1, col);

	}

	void drawPlaying()//�����˽���Ĵ�С
	{
		drawFrame(0, 0, 79, 24, '=', '|');
	}
};
class show:public base
{
private:
	typedef struct Frame
	{
		COORD position[2];
		int flag;
	}Frame;
	COORD weizhi[10];
	COORD zidan[10];
	Frame enemy[6];

public:
	void play()
	{
		int a=0;
		score = 0;
		while (a != 4)
		{
			a=start();
			system("cls");
			switch (a)
			{
			case 1:
				chiocedifficulty();
				Playing();
				break;
			case 2:
				helper(); 
				break;
			case 3:
				rank();
				break;
			case 4:
				close();
				break;
			}
			system("cls");
		}
	}
	int start()
	{
		
		int a;
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
		cout << endl<<endl<< endl ;
		cout << "		�X�����������������������������������������������������[" << endl;
		cout << "		��                     �ɻ���ս                       ��"<<endl;
		cout << "		��������������������������������������������������������" << endl;
		cout << "		��                    1:��ʼ��Ϸ                      ��" << endl;
		cout << "		��������������������������������������������������������" << endl;
		cout << "		��                    2���鿴����                     ��" << endl;
		cout << "		��������������������������������������������������������" << endl;
		cout << "		��                    3���鿴���а�                   ��" << endl;
		cout << "		��������������������������������������������������������" << endl;
		cout << "		��                    4���˳���Ϸ                     ��" << endl;
		cout << "		�^�����������������������������������������������������a" << endl;
		SetConsoleTextAttribute( hOut,FOREGROUND_GREEN |FOREGROUND_BLUE |FOREGROUND_INTENSITY);
		cout << "                          ����1,2,3,4������" << endl;
		cin >> a;
		return a;

	}
	void helper()
	{
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
		char a[1000] = "ʹ��A��D���Ʒ���J������� ������Ա �ݺ�� ������ ";
			for(int i = 0; a[i]!='\0'; i++)
			{
				cout << a[i];
				while (a[i] == ' ')
				{
					cout << endl;
					break;
				}
				Sleep(200);
			}
			system("pause");
			
	}
	void close()
	{
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
		char a[1000] = "��ӭ�ٴ���Ϸ��лл�� ��Ϸ���ڹر� ";
		for (int i = 0; a[i] != '\0'; i++)
		{
			cout << a[i];
			while (a[i] == ' ')
			{
				cout << endl;
				break;
			}
			Sleep(200);
		}
		system("pause");
	}
	void Playing()
	{
		drawFrame(0, 0, 80, 24, '=', '|');
		addEnemy();
		addplane();
		addzidan();
		drawEnemy();
		drawplane();
		int flag_bullet = 0;
		int flag_enemy = 0;

		while (1)
		{
			Sleep(difficulty);
			if (_kbhit())
			{
				char x = _getch();

				if ('a' == x || 's' == x || 'd' == x || 'w' == x)
				{
					cleanplane();
					planeMove(x);
					drawplane();
					planedead();
				}
				else if ('k' == x)
					shoot();
				else if ('e' == x)
				{
					GameOver();
					break;
				}
			}
					/* �����ӵ� */
					if (0 == flag_bullet)
					{
						zidanMove();
						cleanzidan();
						drawzidan();
						planedead();
						puanduanEnemy();
					}
					flag_bullet++;
					if (5 == flag_bullet)
						flag_bullet = 0;
					/* ������� */
					if (0 == flag_enemy)
					{
						cleanEnemy();
						enemyMove();
						drawEnemy();
						planedead();
						puanduanEnemy();
					}
		}
	}
	void chiocedifficulty()
	{
		int a;
		cout << endl << endl;
		cout << "		�X�������������������������������������������������[" << endl;
		cout << "		��                   ��Ϸ�Ѷ�                     ��" << endl;
		cout << "		����������������������������������������������������" << endl;
		cout << "		��             ��Ϸһ����ʮ���Ѷ�                 ��" << endl;
		cout << "		��         �Ѷ�Խ�ߣ������ƶ��ٶ�Խ��             ��" << endl;
		cout << "		�^�������������������������������������������������a" << endl;
		cout << "                ����������Ҫ������Ѷȣ�1-10����";
		while(cin >> a)
		{ 
			if (a >= 1 && a <= 10)
			{
				difficulty = 80 - 8 * (a - 1);
				break;
			}
			else
			{
				cout << "                �Ѷ�ѡ���д������������룺";
			}
		}
		system("cls");
	}


	int random(int a, int b)//�ڣ�a��b���ڲ���һ�������
	{
		int c = (rand() % (a - b)) + a;
		return c;
	}
	COORD random(COORD a, COORD b)//�����������������һ����
	{
		int x = random(a.X, b.X);
		int y = random(a.Y, b.Y);
		COORD c = { x, y };
		return c;
	}

	void addplane()//�����ҷɻ�
	{
		int i;
		COORD place{39 ,22 };
		weizhi[4].X=weizhi[8].X=weizhi[1].X=place.X;
		weizhi[2].X = weizhi[4].X - 2;
		weizhi[6].X = weizhi[4].X + 2;
		weizhi[3].X = weizhi[7].X = weizhi[4].X - 1;
		weizhi[5].X = weizhi[9].X = weizhi[4].X + 1;
		weizhi[1].Y = place.Y - 1;
		weizhi[2].Y = weizhi[3].Y = weizhi[4].Y = weizhi[5].Y = weizhi[6].Y = place.Y;
		weizhi[7].Y = weizhi[8].Y = weizhi[9].Y = place.Y + 1;
		weizhi[0].X = place.X;
		weizhi[0].Y = place.Y - 2;
	}
	void drawplane()
	{
		int i;
		for (i = 1; i < 10; i++)
		{
			SetPos(weizhi[i]);
			if (i == 1)
			{
				cout << "|";
				continue;
			}
			cout << "=";

		}
	}
	void planeMove(char x)//���Ʒɻ��ƶ�
	{
		if (x == 'a')
			if (weizhi[2].X != 1)
				for (int i = 0; i <= 9; i++)
					weizhi[i].X -= 2;

		if (x == 's')
			if (weizhi[8].Y != 23)
				for (int i = 0; i <= 9; i++)
					weizhi[i].Y += 1;

		if (x == 'd')
			if (weizhi[6].X != 79)
				for (int i = 0; i <= 9; i++)
					weizhi[i].X += 2;

		if (x == 'w')
			if (weizhi[1].Y != 3)
				for (int i = 0; i <= 9; i++)
					weizhi[i].Y -= 1;
	}
	void cleanplane()//�����ҷɻ��ƶ����Ӱ
	{
		for (int i = 0; i<10; i++)
		{
			SetPos(weizhi[i]);
			cout << " ";
		}
	}
	void planedead()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j<9; j++)
				if (panduanzhuihui(enemy[i], weizhi[j]))
				{
					SetPos(62, 1);
					cout << "׹��";
					drawFrame(enemy[i].position[0].X, enemy[i].position[0].Y, enemy[i].position[1].X, enemy[i].position[1].Y, '$', '&');
					Sleep(1000);
					GameOver();
					break;
				}
	}

	bool panduanzhuihui(Frame a, COORD spot)
	{
		if (spot.X >= a.position[0].X&&spot.X <= a.position[1].X&&spot.Y >= a.position[0].Y&&spot.Y <= a.position[1].Y)
			return true;
		return false;
	}

	void addzidan()
	{
		for (int i = 0; i<10; i++)
			zidan[i].Y = 30;
	}
	void drawzidan()
	{
		for (int i = 0; i<10; i++)
		{
			if (zidan[i].Y != 30)
			{
				SetPos(zidan[i]);
				cout << "*";
			}
		}
	}
	void cleanzidan()
	{
		for (int i = 0; i<10; i++)
			if (zidan[i].Y != 30)
			{
				COORD pos = { zidan[i].X, zidan[i].Y + 1 };
				SetPos(pos);
				cout << " ";
			}
	}
	void cleanzidan(COORD a)
	{
		SetPos(a);
		cout << " ";
	}
	void zidanMove()
	{
		for (int i = 0; i<10; i++)
		{
			if (zidan[i].Y != 30)
			{
				zidan[i].Y -= 1;
				if (zidan[i].Y == 1)
				{
					COORD pos = { zidan[i].X, zidan[i].Y + 1 };
					SetPos(pos);
					cout << " ";
					zidan[i].Y = 30;
				}
			}
		}
	}

	void shoot()
	{
		for (int i = 0; i<10; i++)
			if (zidan[i].Y == 30)
			{
				zidan[i].X = weizhi[0].X;
				zidan[i].Y = weizhi[0].Y - 1;
				break;
			}
	}

	void addEnemy()
	{
		COORD a = { 1, 1 };
		COORD b = { 77, 5 };
		for (int i = 0; i<8; i++)
		{
			enemy[i].position[0] = random(a, b);
			enemy[i].position[1].X = enemy[i].position[0].X + 3;
			enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
		}
	}
	void drawEnemy()
	{
		for (int i = 0; i<8; i++)
			drawFrame(enemy[i].position[0].X, enemy[i].position[0].Y, enemy[i].position[1].X, enemy[i].position[1].	Y, '-', '|');
	}
	void enemyMove()
	{
		for (int i = 0; i<8; i++)
		{
			for (int j = 0; j<2; j++)
				enemy[i].position[j].Y++;

			if (24 == enemy[i].position[1].Y)
			{
				COORD a = { 1, 1 };
				COORD b = { 77, 5 };
				enemy[i].position[0] = random(a, b);
				enemy[i].position[1].X = enemy[i].position[0].X + 3;
				enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
			}
		}
	}
	void cleanEnemy()
	{
		for (int i = 0; i<8; i++)
		{
			drawFrame(enemy[i].position[0].X, enemy[i].position[0].Y, enemy[i].position[1].X, enemy[i].position[1].Y, ' ', ' ');
		}
	}
	void cleanEnemy(Frame a)
	{
		drawRow(a.position[0].Y, a.position[0].X, a.position[1].X, ' ');
		drawRow(a.position[1].Y, a.position[0].X, a.position[1].X, ' ');
		drawCol(a.position[0].X, a.position[0].Y, a.position[1].Y, ' ');
		drawCol(a.position[1].X, a.position[0].Y, a.position[1].Y, ' ');
	}

	bool puanduandazhongEnemy(Frame frame, COORD spot)
	{
		if (spot.X >= frame.position[0].X)
			if (spot.X <= frame.position[1].X)
				if (spot.Y >= frame.position[0].Y)
					if (spot.Y <= frame.position[0].Y)
						return true;
		return false;
	}
	void puanduanEnemy()
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 10; j++)
				if (puanduandazhongEnemy(enemy[i], zidan[j]))
				{
					score += 5;
					cleanEnemy(enemy[i]);
					COORD a = { 1, 1 };
					COORD b = { 77, 3 };
					enemy[i].position[0] = random(a, b);
					enemy[i].position[1].X = enemy[i].position[0].X + 3;
					enemy[i].position[1].Y = enemy[i].position[0].Y + 2;
					cleanzidan(zidan[j]);
					zidan[j].Y = 30;
				}
	}

	void GameOver()
	{
		system("cls");
		COORD p1 = { 28,9 };
		COORD p2 = { 53,15 };
		drawFrame(0, 0, 79, 24, '=', '|');
		SetPos(36, 12);
		string str = "Game Over!";
		for (int i = 0; i<str.size(); i++)
		{
			Sleep(80);
			cout << str[i];
		}
		Sleep(1000);
		system("cls");
		drawFrame(0, 0, 79, 24, '=', '|');
		SetPos(37, 13);
		cout << "���յ÷֣�";
		cout << score;
		for (int i = 0; i < 3; i++)
		{
			if (score > scores[i])
			{
				scores[i] = score;
				break;
			}
		}
		SetPos(30, 16);
		Sleep(1000);
		cout << "������ �ǣ�y��| ��n��";
	as:
		char x = _getch();
		if (x == 'n')
			exit(0);
		else if (x == 'y')
		{
			show player;
			system("cls");
			player.HideCursor();
			player.play();
		}
		else goto as;
	}

	void rank()
	{
		cout << endl << endl << endl;
		cout << "		�X�������������������������������������������[" << endl;
		cout << "		��               �������а�                 ��" << endl;
		cout << "		����������������������������������������������" << endl;
		cout << "		��             ��һ����";
		cout << setw(5) << scores[0] << "��" << "              ��" << endl;
		cout << "		����������������������������������������������" << endl;
		cout << "		��             �ڶ�����";
		cout << setw(5) << scores[1] << "��" << "              ��" << endl;
		cout << "		����������������������������������������������" << endl;
		cout << "		��             ��������";
		cout << setw(5) << scores[2] << "��" << "              ��" << endl;
		cout << "		�^�������������������������������������������a" << endl;
		system("pause");
	}
};