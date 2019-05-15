#ifndef LINUX_CON_HPP
#define LINUX_CON_HPP
#include <iostream>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#endif


int getch()
{
	system("stty -echo");
	int ret = getchar();
	system("stty echo");
	return ret;
}
//是否显示光标
void showcursor(bool is)
{
	if(is)
	  std::cout<<"\33[?25h";
	else
	  std::cout<<"\033[?25l";
}

//kbhit函数
int kbhit(void)
{
	struct termios oldt, newt;

	int ch;

	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	
	newt = oldt;
	
	newt.c_lflag &= ~(ICANON | ECHO);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	
	ch = getchar();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	
	if(ch != EOF)
	  
	{
	
	ungetc(ch, stdin);
	
	return 1;
	
	}
	
	return 0;
}

//终端光标坐标
void setpos(int x,int y)
{
	std::cout<<"\033["<<x<<";"<<y<<"H";
}

//清除屏幕
void clear()
{
	system("clear");
}

