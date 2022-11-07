#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Volume.h"
#include <vector>
#include <fstream>
#include <string>
#include "SHA256.h"
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include "numeric.h"
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

vector<string>VolumeMenu= {"HIEN THI DANH SACH TAP TIN", "TAO PASSWORD", "THAY DOI PASSWORD", "IMPORT TAP TIN", "THOAT"};
vector<string>FileMenu = {"XEM THONG TIN FILE", "TAO PASSWORD", "THAY DOI PASSWORD", "OUTPORT", "THOAT"};


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
		getline(file, path);
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
						VolumeList[i].initEntryTable();
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
								OPENFILE:
									system("cls");
									FixConsoleColor(237);
									cout << "---------------------------------------------------DANH SACH TAP TIN---------------------------------------------------\n\n\n";
									EntryTable entryTable;
									entryTable.readEntryList(VolumeList[i].getPath());
									VolumeList[i].setNumberOfEntry(entryTable.getEntryList().size());
									VolumeList[i].setEntryTable(entryTable);
									FixConsoleColor(244);
									cout << "   Huong dan:" << endl;
									cout << "   - Nhan ESC de quay lai" << endl;
									cout << "   - Volume dang mo: " << VolumeList[i].getPath() << endl;
									if (VolumeList[i].getNumberOfEntry() <= 0) {
										FixConsoleColor(244);
										cout << "Chua co tap tin nao!" << endl;
										system("pause");
										goto DETAILVOLUME;
									}
									for (int j = 0; j < VolumeList[i].getNumberOfEntry(); j++) {
										GoToXY(48, 12 + j * 2);
										FixConsoleColor(237);
										string MainName = VolumeList[i].getEntryTable().getEntryList()[j].getMainName();
										string ExtensionName = VolumeList[i].getEntryTable().getEntryList()[j].getExtensionName();
										while (MainName.size() > 0 && MainName.back() == ' ') MainName.pop_back();
										while (ExtensionName.size() > 0 && ExtensionName.back() == ' ') ExtensionName.pop_back();
										cout << MainName+"."+ExtensionName << endl;
									}

									FixConsoleColor(244);
									for (int j = 38; j < 79; j++)
									{
										GoToXY(j, 12 + VolumeList[i].getNumberOfEntry() * 2);
										cout << ngang;
										GoToXY(116 - j, 10);
										cout << ngang;
										Sleep(10);
									}
									GoToXY(37, 10);
									cout << goc1;
									GoToXY(79, 12 + VolumeList[i].getNumberOfEntry() * 2);
									cout << goc4;
									for (int j = 11; j < VolumeList[i].getNumberOfEntry() * 2 + 12 + 1; j++)
									{
										GoToXY(37, j);
										cout << doc;
										GoToXY(79, VolumeList[i].getNumberOfEntry() * 2 + 12 + 10 - j);
										cout << doc;
										Sleep(10);
									}
									GoToXY(79, 10);
									cout << goc2;
									GoToXY(37, VolumeList[i].getNumberOfEntry() * 2 + 12);
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
											if (line <= 12 + VolumeList[i].getNumberOfEntry() * 2 - 4)
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
											goto DETAILVOLUME;
										}
										else if (_COMMAND == 13) {//Mở file
											id = (line - 12) / 2;
											system("cls");
											if (VolumeList[i].getEntryTable().getEntryList()[id].getPassWord()[0] != ' ' && VolumeList[i].getEntryTable().getEntryList()[id].getPassWord() != "") {
												string pass = " ";
												cout << "Enter your password to open: ";
												getline(cin, pass);
												if (SHA256(pass.c_str()) != VolumeList[i].getEntryTable().getEntryList()[id].getPassWord()) {
													cout << "Wrong password!" << endl;
													system("pause");
													goto OPENFILE;
												}
											}
										DETAILFILE:
											int id = (line - 12) / 2;
											Entry curEntry = VolumeList[i].getEntryTable().getEntryList()[id];
											system("cls");
											FixConsoleColor(237);
											string MainName = curEntry.getMainName();
											string ExtensionName = curEntry.getExtensionName();
											while (MainName.size() > 0 && MainName.back() == ' ') MainName.pop_back();
											while (ExtensionName.size() > 0 && ExtensionName.back() == ' ') ExtensionName.pop_back();
											cout << "----" << MainName<<"."<<ExtensionName << "----\n\n\n";
											FixConsoleColor(244);
											cout << "   Huong dan:" << endl;
											cout << "   - Nhan ESC de quay lai" << endl;
											cout << "   - File dang mo: " << MainName<<"."<<ExtensionName << endl;

											for (int j = 0; j < FileMenu.size(); j++) {
												GoToXY(48, 12 + j * 2);
												FixConsoleColor(237);
												cout << FileMenu[j];
											}

											FixConsoleColor(244);
											for (int j = 38; j < 79; j++)
											{
												GoToXY(j, FileMenu.size() * 2 + 12);
												cout << ngang;
												GoToXY(116 - j, 10);
												cout << ngang;
												Sleep(10);
											}
											GoToXY(37, 10);
											cout << goc1;
											GoToXY(79, FileMenu.size() * 2 + 12);
											cout << goc4;
											for (int j = 11; j < FileMenu.size() * 2 + 12 + 1; j++)
											{
												GoToXY(37, j);
												cout << doc;
												GoToXY(79, FileMenu.size() * 2 + 12 + 10 - j);
												cout << doc;
												Sleep(10);
											}
											GoToXY(79, 10);
											cout << goc2;
											GoToXY(37, FileMenu.size() * 2 + 12);
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
													if (line <= FileMenu.size() * 2 + 12 - 4)
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
													goto OPENFILE;
												}
												else if (_COMMAND == 13) {
													int choose = (line - 12) / 2;
													if (choose == 0) {//Hiển thị thông tin file

													}
													else if (choose == 1) {//Tạo password
														system("cls");
														if (curEntry.getPassWord()[0] != ' ' && curEntry.getPassWord() != "") {
															cout << "This file already had a password!" << endl;
															//cout << VolumeList[i].getPassword() << endl;
															system("pause");
															goto DETAILFILE;
														}
														cout << "Attention: Password should not start with a space character!" << endl;
														string pass = " ";
														while (pass[0] == ' ' || pass == "") {
															cout << "Enter your password: ";
															getline(cin, pass);
														}
														string retype = "";
														while (retype != pass) {
															cout << "Retype your password: ";
															getline(cin, retype);
														}
														curEntry.setPassWord(SHA256(pass.c_str()));
														curEntry.write(VolumeList[i].getPath());
														EntryTable entryTable = VolumeList[i].getEntryTable();
														vector<Entry>list = entryTable.getEntryList();
														list[id] = curEntry;
														entryTable.setEntryList(list);
														VolumeList[i].setEntryTable(entryTable);
														system("pause");
													}
													else if (choose == 2) {//Đổi password
														system("cls");
														if (curEntry.getPassWord()[0] == ' ' || curEntry.getPassWord() == "") {
															cout << "This file did not have a password!" << endl;
															cout << "Create your pasword first!" << endl;
															//cout << VolumeList[i].getPassword() << endl;
															system("pause");
															goto DETAILFILE;
														}
														string pass = " ";
														cout << "Enter your current password: ";
														getline(cin, pass);
														if (SHA256(pass.c_str()) != curEntry.getPassWord()) {
															cout << "Wrong password!" << endl;
															system("pause");
															goto DETAILFILE;
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
														curEntry.setPassWord(SHA256(pass.c_str()));
														curEntry.write(VolumeList[i].getPath());
														EntryTable entryTable = VolumeList[i].getEntryTable();
														vector<Entry>list = entryTable.getEntryList();
														list[id] = curEntry;
														entryTable.setEntryList(list);
														VolumeList[i].setEntryTable(entryTable);
														system("pause");
													}
													else if (choose == 3) {//Outport

													}
													else {
														goto OPENFILE;
													}
													goto DETAILFILE;
												}
											} while (true);
										}
									} while (true);
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
								else if (choose == 3) {//Import tap tin
									cout << "Nhap duong dan cua tap tin: " << endl;
									cout << "Vui long nhap dung dinh dang. Vi du: C:/Users/PC/Documents/HeDieuHanh.pdf" << endl;
									cout << "Enter your path: ";
									string path;
									getline(cin, path);
									fstream temp(path, ios::in);
									if (!temp) {
										cout << "File khong ton tai!" << endl;
										system("pause");
										goto DETAILVOLUME;
									}
									Entry* e = new Entry;
									string MainName = "", ExtensionName = "";
									for (int i = path.size() - 1; i >= 0; i--) {
										if (path[i] == '.') {
											for (int j = i - 1; j >= 0; j--) {
												if (path[j] == '/') {
													break;
												}
												MainName = path[j] + MainName;
											}
											break;
										}
										ExtensionName = path[i] + ExtensionName;
									}
									while (MainName.size() < 14) MainName += ' ';
									while (ExtensionName.size() < 4) ExtensionName += ' ';


									uint16_t ModifiedTime; //Thời gian cập nhật
									uint16_t ModifiedDate; //Ngày cập nhật
									uint32_t Size; //Kích thước
									uint8_t Status=0; //Trạng thái (0: chưa bị xóa, 1: đã bị xóa)
									uint8_t Children=0; //Số file/folder con
									string Password=""; //Mật khẩu
									uint32_t BeginSector; //Sector bắt đầu
									struct stat fileInfo;

									while (Password.size() < 64) Password += ' ';
									if (stat(path.c_str(), &fileInfo) != 0) {  // Use stat() to get the info
										std::cerr << "Error: " << strerror(errno) << '\n';
									}
									//cout << MainName << endl << ExtensionName << endl;
									/*std::cout << "Type:         : ";
									if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) { // From sys/types.h
										std::cout << "Directory\n";
									}
									else {
										std::cout << "File\n";
									}

									std::cout << "Size          : " <<
										fileInfo.st_size << '\n';               // Size in bytes
									std::cout << "Device        : " <<
										(char)(fileInfo.st_dev + 'A') << '\n';  // Device number
									std::cout << "Created       : " <<
										std::ctime(&fileInfo.st_ctime);         // Creation time
									std::cout << "Modified      : " <<
										std::ctime(&fileInfo.st_mtime);         // Last mod time*/
									tm tm = *localtime(&fileInfo.st_mtime);
									long long gio = tm.tm_hour,
										phut = tm.tm_min,
										giay = tm.tm_sec/2,
										ngay = tm.tm_mday,
										thang = tm.tm_mon + 1,
										nam = tm.tm_year + 1900 - 1980;
									gio = decToBinary(gio);
									phut = decToBinary(phut);
									giay = decToBinary(giay);
									ngay = decToBinary(ngay);
									thang = decToBinary(thang);
									nam = decToBinary(nam);
									long long time = gio * 100000000000LL + phut * 100000LL + giay;
									long long date = nam*1000000000LL + thang*100000LL + ngay;
									ModifiedDate = binaryToDecimal(date);
									ModifiedTime = binaryToDecimal(time);
									Size = (uint32_t)fileInfo.st_size;
									//Ghi thong tin file len entry table va vung data
									fstream vol(VolumeList[i].getPath(), ios_base::binary | ios::out | ios::in);
									vol.seekp(0, ios::end);
									BeginSector = (uint32_t)((uint32_t)vol.tellp() / (uint32_t)512);
									fstream file(path, ios_base::binary | ios::in);
									char* data = NULL;
									file.seekg(0, ios::end);
									long long dataSize = file.tellg();
									data = new char[dataSize+1];
									file.read(data, dataSize);
									file.close();
									vol.write(data, dataSize);
									uint8_t x = 0;
									for (int i = dataSize; i % 512 != 0; i++) {
										vol.write((char*)&x, 1);
									}
									long long start = VolumeList[i].getBeginSectorOfEntryTable() * 512;
									vol.seekp(start);
									vol.read((char*)&x, 1);
									while (x != 0) {
										start += 96LL;
										vol.seekp(start);
										vol.read((char*)&x, 1);
										if (start+96 > (UINT16_MAX + 1) * 512) {
											cout << "Volume is full!" << endl;
											system("pause");
											goto OPENVOLUME;
											break;
										}
									}
									//cout << start << endl; system("pause");
									vol.seekp(start);
									//cout << start << endl; system("pause");
									vol.write(&MainName[0], 14);
									vol.write(&ExtensionName[0], 4);
									vol.write((char*)&Children, 1);
									vol.write((char*)&Status, 1);
									vol.write((char*)&time, 2);
									vol.write((char*)&date, 2);
									vol.write((char*)&BeginSector, 4);
									vol.write((char*)&Size, 4);
									vol.write(&Password[0], 64);
									vol.close();
									//cout << MainName;
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
				getline(cin, path);
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