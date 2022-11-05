#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

void FixConsoleWindow() //Ham co dinh cua so
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GoToXY(int x, int y) //Ham dat toa do
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void FixConsoleColor(int k) // Ham doi mau chu
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}

void MoveDown(int& _X, int& _Y)   //Di chuyen xuong
{
	_Y += 2;
	GoToXY(_X, _Y);
}

void MoveUp(int& _X, int& _Y)   //Di chuyen len
{
	_Y -= 2;
	GoToXY(_X, _Y);
}

void Menu(int& _COMMAND, int& _X, int& line)
{
	system("cls");

	FixConsoleColor(244);
	cout << "   Huong dan co ban:" << endl;
	cout << " - Chuyen ban phim sang che do go tieng anh" << endl;
	cout << " - Nhan phim S de di chuyen xuong duoi" << endl;
	cout << " - Nhan phim W de di chuyen len tren" << endl;

	char doc = 179, ngang = 196;
	char goc1 = 218, goc2 = 191, goc3 = 192, goc4 = 217;
	line = 12;
	_X = 43;

	FixConsoleColor(249);
	Sleep(100);
	GoToXY(20, 5);
	cout << "000000  0  0       000000      00 00  0   0   00 00  0000000  000000  0     0";  Sleep(100);
	FixConsoleColor(250);
	GoToXY(20, 6);
	cout << "0       0  0       0          00       0 0   00         0     0       0 0 0 0 ";  Sleep(100);
	FixConsoleColor(246);
	GoToXY(20, 7);
	cout << "000000  0  0       000000       00      0      00       0     000000  0  0  0";   Sleep(100);
	FixConsoleColor(252);
	GoToXY(20, 8);
	cout << "0       0  0       0              00    0        00     0     0       0     0"; Sleep(100);
	FixConsoleColor(243);
	GoToXY(20, 9);
	cout << "0       0  000000  000000     00 00     0    00 00      0     000000  0     0";  Sleep(100);
	GoToXY(48, 12);
	FixConsoleColor(237);
	cout << " CREATE A NEW VOLUME";
	Sleep(100);
	GoToXY(48, 14);
	FixConsoleColor(229);
	cout << " OPEN AN EXISTING VOLUME";
	Sleep(100);
	GoToXY(48, 16);
	FixConsoleColor(225);
	cout << " INSTRUCTION";
	Sleep(100);
	GoToXY(48, 18);
	FixConsoleColor(234);
	cout << " ABOUT" << endl;
	FixConsoleColor(233);
	Sleep(100);
	GoToXY(48, 20);
	FixConsoleColor(236);
	cout << " EXIT" << endl;
	FixConsoleColor(244);
	for (int j = 38; j < 79; j++)
	{
		GoToXY(j, 22);
		cout << ngang;
		GoToXY(116 - j, 10);
		cout << ngang;
		Sleep(25);
	}
	GoToXY(37, 10);
	cout << goc1;
	GoToXY(79, 22);
	cout << goc4;
	for (int i = 11; i < 23; i++)
	{
		GoToXY(37, i);
		cout << doc;
		GoToXY(79, 32 - i);
		cout << doc;
		Sleep(25);
	}
	GoToXY(79, 10);
	cout << goc2;
	GoToXY(37, 22);
	cout << goc3;
	Sleep(100);
	GoToXY(43, 12);
	cout << ">>";
	do {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 87)
		{
			if (line >= 14)
			{
				GoToXY(_X, line);
				cout << "  ";
				MoveUp(_X, line);
				cout << ">>";
			}
		}
		else if (_COMMAND == 83)
		{
			if (line <= 18)
			{
				GoToXY(_X, line);
				cout << "  ";
				MoveDown(_X, line);
				cout << ">>";
			}
		}
		else if (_COMMAND == 27) //Thoat
		{
			system("cls");
			exit(0);
		}
	} while (_COMMAND != 13);
}

void About()
{
	cout << " Truong Dai Hoc Khoa Hoc Tu Nhien DHQG - TPHCM" << endl;
	cout << " Mon: HDH" << endl;
	cout << " Lop: 20_4" << endl;
	cout << " Do an File System" << endl;
	cout << " Thanh vien nhom: " << endl;
	cout << " 1. 20120340 - Tran Nhat Nguyen" << endl;
	cout << " 2. 20120391 - Ha Xuan Truong" << endl;
	cout << " 3. 20120454 - Le Cong Dat" << endl;
}

//demo so ham main
/*
int main()
{
	int _COMMAND = -1; // Bien nhan gia tri phim nguoi dung nhap
	int _X = 0;
	int	_Y = 0; //Toa do hien hanh tren man hinh
	bool _TURN;
	int line;

	FixConsoleWindow();
	X:FixConsoleColor(255);
	while (true) 
	{
		system("cls");
		Menu(_COMMAND, _X, line);
		if (_COMMAND == 13)
		{
			if (line == 12)
			{
				system("cls");
				system("pause");
			}
			if (line == 14)
			{
				system("cls");
				system("pause");
			}
			if (line == 16)
			{
				system("cls");
				system("pause");
			}
			if (line == 18)
			{
				system("cls");
				About();
				system("pause");
			}
			if (line == 20)
			{
				system("cls");
				system("pause");
				exit(0);
			}
		}
	}
}
*/