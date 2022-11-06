#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Volume.h"
#include <vector>
#include <fstream>
#include <string>
#include "SHA256.h"
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
	cout << " - Nhan mui ten xuong hoac phim S de di chuyen xuong duoi" << endl;
	cout << " - Nhan mui ten len hoac phim W de di chuyen len tren" << endl;

	char doc = 179, ngang = 196;
	char goc1 = 218, goc2 = 191, goc3 = 192, goc4 = 217;
	line = 12;
	_X = 43;

	FixConsoleColor(249);
	Sleep(100);
	GoToXY(20, 5);
	cout << "000000  0  0       000000      00 00  0   0   00 00  0000000  000000  0     0";  Sleep(50);
	FixConsoleColor(250);
	GoToXY(20, 6);
	cout << "0       0  0       0          00       0 0   00         0     0       0 0 0 0 ";  Sleep(50);
	FixConsoleColor(246);
	GoToXY(20, 7);
	cout << "000000  0  0       000000       00      0      00       0     000000  0  0  0";   Sleep(50);
	FixConsoleColor(252);
	GoToXY(20, 8);
	cout << "0       0  0       0              00    0        00     0     0       0     0"; Sleep(50);
	FixConsoleColor(243);
	GoToXY(20, 9);
	cout << "0       0  000000  000000     00 00     0    00 00      0     000000  0     0";  Sleep(50);
	GoToXY(48, 12);
	FixConsoleColor(237);
	cout << " CREATE A NEW VOLUME";
	Sleep(50);
	GoToXY(48, 14);
	FixConsoleColor(229);
	cout << " OPEN AN EXISTING VOLUME";
	Sleep(50);
	GoToXY(48, 16);
	FixConsoleColor(225);
	cout << " ADD EXIST VOLUME WITH PATH";
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
		Sleep(10);
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
		Sleep(10);
	}
	GoToXY(79, 10);
	cout << goc2;
	GoToXY(37, 22);
	cout << goc3;
	Sleep(50);
	GoToXY(43, 12);
	cout << ">>";
	do {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 87 || _COMMAND == 72)
		{
			if (line >= 14)
			{
				GoToXY(_X, line);
				cout << "  ";
				MoveUp(_X, line);
				cout << ">>";
			}
		}
		else if (_COMMAND == 83 || _COMMAND == 80)
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

vector<string>VolumeMenu= {"HIEN THI DANH SACH TAP TIN", "TAO PASSWORD", "THAY DOI PASSWORD", "THOAT"};

void runMenu()
{
	char doc = 179, ngang = 196;
	char goc1 = 218, goc2 = 191, goc3 = 192, goc4 = 217;
	//Get list of volume
	string VolumeListPath = "VolumeList.txt";
	vector<Volume>VolumeList;
	fstream file(VolumeListPath, ios_base::in);
	string path;
	while (true) {
		if (file.eof()) break;
		path = "";
		file >> path;
		if (path == "") break;
		Volume volume;
		volume.setPath(path);
		volume.read();
		VolumeList.push_back(volume);
	}
	file.close();

	int _COMMAND = -1; // Bien nhan gia tri phim nguoi dung nhap
	int _X = 0;
	int	_Y = 0; //Toa do hien hanh tren man hinh
	bool _TURN;
	int line;

	FixConsoleWindow();
X:FixConsoleColor(255);
	while (true)
	{
	MAIN:
		system("cls");
		Menu(_COMMAND, _X, line);
		if (_COMMAND == 13)
		{
			if (line == 12) // create new volume
			{
				system("cls");
				Volume newVolume;
				bool create=newVolume.create();
				if (!create) {
					system("pause");
					goto MAIN;
				}
				VolumeList.push_back(newVolume);
				system("pause");
			}
			if (line == 14) //Open volume
			{
			OPENVOLUME:
				if (VolumeList.size() == 0) {
					system("cls");
					cout << "Chua co volume nao!" << endl;
					system("pause");
					goto MAIN;
				}
				system("cls");
				FixConsoleColor(237);
				cout << "----------------------------------------------------- OPEN A VOLUME ----------------------------------------------------\n\n\n";
				FixConsoleColor(244);
				cout << "   Huong dan:" << endl;
				cout << "   - Nhan Enter de mo volume" << endl;
				cout << "   - Nhan ESC de tro ve menu" << endl;

				for (int i = 0; i < VolumeList.size(); i++) {
					GoToXY(48, 12 + i * 2);
					FixConsoleColor(237);
					cout << VolumeList[i].getPath();
				}

				FixConsoleColor(244);
				for (int j = 38; j < 79; j++)
				{
					GoToXY(j, 12 + VolumeList.size()*2);
					cout << ngang;
					GoToXY(116 - j, 10);
					cout << ngang;
					Sleep(10);
				}
				GoToXY(37, 10);
				cout << goc1;
				GoToXY(79, 12 + VolumeList.size() * 2);
				cout << goc4;
				for (int i = 11; i < 12+VolumeList.size()*2+1; i++)
				{
					GoToXY(37, i);
					cout << doc;
					GoToXY(79, 12+VolumeList.size()*2+10 - i);
					cout << doc;
					Sleep(10);
				}
				GoToXY(79, 10);
				cout << goc2;
				GoToXY(37, 12 + VolumeList.size() * 2);
				cout << goc3;
				Sleep(50);
				GoToXY(43, 12);
				cout << ">>";
				line = 12;
				do {
					_COMMAND = toupper(_getch());
					if (_COMMAND == 87 || _COMMAND == 72)
					{
						if (line >= 14)
						{
							GoToXY(_X, line);
							cout << "  ";
							MoveUp(_X, line);
							cout << ">>";
						}
					}
					else if (_COMMAND == 83 || _COMMAND == 80)
					{
						if (line <= 12+VolumeList.size()*2-4)
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
						runMenu();
					}
					else if (_COMMAND == 13) { //Mở volume thứ i
						int id = (line - 12) / 2;
						system("cls");
						if (VolumeList[id].getPassword()[0] != ' ' && VolumeList[id].getPassword() != "") {
							string pass = " ";
							cout << "Enter your password to open: ";
							getline(cin, pass);
							if (SHA256(pass.c_str()) != VolumeList[id].getPassword()) {
								cout << "Wrong password!" << endl;
								system("pause");
								goto OPENVOLUME;
							}
						}
					DETAILVOLUME:
						int i = (line - 12) / 2;
						system("cls");
						FixConsoleColor(237);
						cout << "----"<<VolumeList[i].getPath()<<"----\n\n\n";
						FixConsoleColor(244);
						cout << "   Huong dan:" << endl;
						cout << "   - Nhan ESC de quay lai" << endl;
						cout << "   - Volume dang mo: " << VolumeList[i].getPath() << endl;

						for (int i = 0; i < VolumeMenu.size(); i++) {
							GoToXY(48, 12 + i * 2);
							FixConsoleColor(237);
							cout << VolumeMenu[i];
						}

						FixConsoleColor(244);
						for (int j = 38; j < 79; j++)
						{
							GoToXY(j, VolumeMenu.size()*2+12);
							cout << ngang;
							GoToXY(116 - j, 10);
							cout << ngang;
							Sleep(10);
						}
						GoToXY(37, 10);
						cout << goc1;
						GoToXY(79, VolumeMenu.size() * 2 + 12);
						cout << goc4;
						for (int i = 11; i < VolumeMenu.size() * 2 + 12+1; i++)
						{
							GoToXY(37, i);
							cout << doc;
							GoToXY(79, VolumeMenu.size() * 2 + 12+10 - i);
							cout << doc;
							Sleep(10);
						}
						GoToXY(79, 10);
						cout << goc2;
						GoToXY(37, VolumeMenu.size() * 2 + 12);
						cout << goc3;
						Sleep(50);
						GoToXY(43, 12);
						cout << ">>";
						int line = 12;
						do {
							_COMMAND = toupper(_getch());
							if (_COMMAND == 87 || _COMMAND == 72)
							{
								if (line >= 14)
								{
									GoToXY(_X, line);
									cout << "  ";
									MoveUp(_X, line);
									cout << ">>";
								}
							}
							else if (_COMMAND == 83 || _COMMAND == 80)
							{
								if (line <= VolumeMenu.size() * 2 + 12 - 4)
								{
									GoToXY(_X, line);
									cout << "  ";
									MoveDown(_X, line);
									cout << ">>";
								}
							}
							else if (_COMMAND == 27) //Quay lai
							{
								system("cls");
								goto OPENVOLUME;
							}
							else if (_COMMAND == 13) { //Chọn 
								system("cls");
								int choose = (line - 12) / 2;
								if (choose == 0) { //Hiển thị danh sách tập tin
									system("cls");
									system("pause");
								}
								else if (choose == 1) {//Tạo mật khẩu
									//cin.ignore();
									system("cls");
									if (VolumeList[i].getPassword()[0] != ' ' && VolumeList[i].getPassword()!="") {
										cout << "This volume already had a password!" << endl;
										//cout << VolumeList[i].getPassword() << endl;
										system("pause");
										goto DETAILVOLUME;
									}
									cout << "Attention: Password should not start with a space character!" << endl;
									string pass = " ";
									while (pass[0] == ' ' || pass=="") {
										cout << "Enter your password: ";
										getline(cin, pass);
									}
									string retype = "";
									while (retype != pass) {
										cout << "Retype your password: ";
										getline(cin, retype);
									}
									VolumeList[i].setPassword(SHA256(pass.c_str()));
									//cout << VolumeList[i].getPassword() << endl;
									VolumeList[i].write();
									system("pause");
								}
								else if (choose == 2) {//Thay đổi mật khẩu
									//cin.ignore();
									system("cls");
									if (VolumeList[i].getPassword()[0] == ' ' || VolumeList[i].getPassword() == "") {
										cout << "This volume did not have a password!" << endl;
										cout << "Create your pasword first!" << endl;
										//cout << VolumeList[i].getPassword() << endl;
										system("pause");
										goto DETAILVOLUME;
									}
									string pass = " ";
									cout << "Enter your current password: ";
									getline(cin, pass);
									if (SHA256(pass.c_str()) != VolumeList[i].getPassword()) {
										cout << "Wrong password!" << endl;
										system("pause");
										goto DETAILVOLUME;
									}
									cout << "Attention: Password should not start with a space character!" << endl;
									pass = " ";
									while (pass[0] == ' ' || pass == "") {
										cout << "Enter your new password: ";
										getline(cin, pass);
									}
									string retype = "";
									while (retype != pass) {
										cout << "Retype your new password: ";
										getline(cin, retype);
									}
									VolumeList[i].setPassword(SHA256(pass.c_str()));
									//cout << VolumeList[i].getPassword() << endl;
									VolumeList[i].write();
									system("pause");
								}
								else {//Quay lai
									goto OPENVOLUME;
								}
								goto DETAILVOLUME;
							}
						} while (true);
						system("pause");
						goto OPENVOLUME;
					}
				} while (true);
				system("pause");
			}
			if (line == 16) //Huong dan
			{
			ADD:
				system("cls");
				cout << "------------------------------------------------ ADD AN EXIST VOLUME BY PATH -----------------------------------------------\n\n\n";
				FixConsoleColor(244);
				cout << "Nhap dia chi volume: " << endl;
				cout << "Vui long nhap dung dinh dang. Vi du: C:/Users/PC/Documents/MyFS.Dat" << endl;
				cout << "Enter your path: ";
				string path;
				cin >> path;
				fstream temp(path, ios::in);
				if (!temp) {
					cout << "File does not exist!" << endl;
					system("pause");
					goto MAIN;
				}
				temp.close();
				Volume volume;
				volume.setPath(path);
				volume.read();
				if (volume.getSignature() != "DNT") {
					cout << "Volume khong dung dinh dang volume DNT" << endl;
					system("pause");
					goto MAIN;
				}
				bool exist = false;
				for (int i = 0; i < VolumeList.size(); i++) {
					if (path == VolumeList[i].getPath()) {
						exist = true;
						break;
					}
				}
				if (exist) {
					cout << "Volume nay da ton tai trong danh sach!" << endl;
					system("pause");
					goto MAIN;
				}
				VolumeList.push_back(volume);
				fstream file(VolumeListPath, ios_base::app);
				file << path << endl;
				file.close();
				system("pause");
			}
			if (line == 18) //Gioi thieu
			{
			GIOITHIEU:
				system("cls");
				About();
				system("pause");
			}
			if (line == 20) //Thoat
			{
			EXIT:
				system("cls");
				//system("pause");
				exit(0);
			}
		}
	}
}