#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
#include"标头.h"
using namespace std;
void main()
{
	srand((int)time(0));    //随机种子
	show player;
	player.HideCursor();
	player.play();	
}
