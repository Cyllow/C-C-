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
	void drawRow(COORD a, COORD b, char ch)// 在a, b两点的纵坐标相同的前提下，把坐标[a.x, b.y] 之间填充为 ch
	{
		if (a.Y == b.Y)
			drawRow(a.Y, a.X, b.X, ch);
		else
		{
			SetPos(0, 25);
			cout << "无法填充行，两个坐标的纵坐标不相等";
			system("pause");
		}
	}
	void drawRow(int y, int x1, int x2, char ch)//把第y行，[x1, x2) 之间的坐标填充为 ch
	{
		SetPos(x1, y);
		for (int i = 0; i <= (x2 - x1); i++)
			cout << ch;
	}
	void drawCol(int x, int y1, int y2, char ch)//把第x列，[y1, y2] 之间的坐标填充为 ch
	{

		for (int y = y1; y != y2 + 1; y++)
		{
			SetPos(x, y);
			cout << ch;
		}
	}
	void drawCol(COORD a, COORD b, char ch)//在a,b 横坐标相同的前提下，把坐标 [a.y, b.y] 之间填充为 ch
	{
		if (a.X == b.X)
			drawCol(a.X, a.Y, b.Y, ch);
		else
		{
			SetPos(0, 25);
			cout << "无法填充列,因为两个坐标的横坐标不相等";
			system("pause");
		}
	}
	void SetPos(int i, int j)// 传坐标值设定点
	{
		COORD pos = { i, j };
		SetPos(pos);
	}
	void SetPos(COORD a)//通过光标设定点 
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(out, a);
	}

	void HideCursor()//隐藏光标并设置光标厚度为1.
	{
		CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	}
	void drawFrame(int x1, int y1, int x2, int y2, char row, char col)//根据左上和右下角坐标来填充一个矩形框架
	{
		drawRow(y1, x1 + 1, x2 - 1, row);
		drawRow(y2, x1 + 1, x2 - 1, row);
		drawCol(x1, y1 + 1, y2 - 1, col);
		drawCol(x2, y1 + 1, y2 - 1, col);

	}

	void drawPlaying()//控制了界面的大小
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
		cout << "		╔──────────────────────────╗" << endl;
		cout << "		┃                     飞机大战                       ┃"<<endl;
		cout << "		┃──────────────────────────┃" << endl;
		cout << "		┃                    1:开始游戏                      ┃" << endl;
		cout << "		┃──────────────────────────┃" << endl;
		cout << "		┃                    2：查看帮助                     ┃" << endl;
		cout << "		┃──────────────────────────┃" << endl;
		cout << "		┃                    3：查看排行榜                   ┃" << endl;
		cout << "		┃──────────────────────────┃" << endl;
		cout << "		┃                    4：退出游戏                     ┃" << endl;
		cout << "		╚──────────────────────────╝" << endl;
		SetConsoleTextAttribute( hOut,FOREGROUND_GREEN |FOREGROUND_BLUE |FOREGROUND_INTENSITY);
		cout << "                          输入1,2,3,4来继续" << endl;
		cin >> a;
		return a;

	}
	void helper()
	{
		HANDLE hOut;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
		char a[1000] = "使用A，D控制方向，J键射击。 制作人员 戚宏成 陈泽青 ";
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
		char a[1000] = "欢迎再次游戏，谢谢。 游戏正在关闭 ";
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
					/* 处理子弹 */
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
					/* 处理敌人 */
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
		cout << "		╔────────────────────────╗" << endl;
		cout << "		┃                   游戏难度                     ┃" << endl;
		cout << "		┃────────────────────────┃" << endl;
		cout << "		┃             游戏一共有十个难度                 ┃" << endl;
		cout << "		┃         难度越高，敌人移动速度越快             ┃" << endl;
		cout << "		╚────────────────────────╝" << endl;
		cout << "                请输入您想要体验的难度（1-10）：";
		while(cin >> a)
		{ 
			if (a >= 1 && a <= 10)
			{
				difficulty = 80 - 8 * (a - 1);
				break;
			}
			else
			{
				cout << "                难度选择有错误，请重新输入：";
			}
		}
		system("cls");
	}


	int random(int a, int b)//在（a，b）内产生一个随机数
	{
		int c = (rand() % (a - b)) + a;
		return c;
	}
	COORD random(COORD a, COORD b)//在两个坐标内随机出一个点
	{
		int x = random(a.X, b.X);
		int y = random(a.Y, b.Y);
		COORD c = { x, y };
		return c;
	}

	void addplane()//添加玩家飞机
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
	void planeMove(char x)//控制飞机移动
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
	void cleanplane()//清除玩家飞机移动后残影
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
					cout << "坠毁";
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
		cout << "最终得分：";
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
		cout << "继续？ 是（y）| 否（n）";
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
		cout << "		╔─────────────────────╗" << endl;
		cout << "		┃               分数排行榜                 ┃" << endl;
		cout << "		┃─────────────────────┃" << endl;
		cout << "		┃             第一名：";
		cout << setw(5) << scores[0] << "分" << "              ┃" << endl;
		cout << "		┃─────────────────────┃" << endl;
		cout << "		┃             第二名：";
		cout << setw(5) << scores[1] << "分" << "              ┃" << endl;
		cout << "		┃─────────────────────┃" << endl;
		cout << "		┃             第三名：";
		cout << setw(5) << scores[2] << "分" << "              ┃" << endl;
		cout << "		╚─────────────────────╝" << endl;
		system("pause");
	}
};