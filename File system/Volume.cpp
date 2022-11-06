#include "Volume.h"
#include "Menu.h"
#include <fstream>
string VolumeListPath = "VolumeList.txt";
Volume::Volume() {
	this->Signature = "DNT";
	this->NumberOfEntry = 0;
	this->BeginSectorOfEntryTable = 1;
	this->Password = "";
	for (int i = 0; i < 64; i++) this->Password += ' ';
	this->Path = "";
}
Volume::~Volume() {

}
uint16_t Volume::getNumberOfEntry() {
	return this->NumberOfEntry;
}
uint32_t Volume::getBeginSectorOfEntryTable() {
	return this->BeginSectorOfEntryTable;
}
string Volume::getPassword() {
	return this->Password;
}
string Volume::getPath() {
	return this->Path;
}
string Volume::getSignature() {
	return this->Signature;
}
void Volume::setNumberOfEntry(uint16_t value) {
	this->NumberOfEntry = value;
}
void Volume::setBeginSectorOfEntryTable(uint32_t value) {
	this->BeginSectorOfEntryTable = value;
}
void Volume::setPassword(string password) {
	this->Password = password;
}
void Volume::setPath(string path) {
	this->Path = path;
}
bool Volume::create() {
	FixConsoleColor(237);
	cout << "-------------------------------------------------- CREATE A NEW VOLUME -------------------------------------------------\n\n\n";
	FixConsoleColor(244);
	cout << "Nhap dia chi thu muc muon tao volume: " << endl;
	cout << "Vui long nhap dung dinh dang. Vi du: C:/Users/PC/Documents/" << endl;
	cout << "Enter your path: ";
	cin >> this->Path;
	string name;
	cout << "Nhap ten cho volume: " << endl;
	cout << "Vi du: MyFS.Dat" << endl;
	cout << "Enter your volume name: ";
	cin >> name;
	this->Path += name;
	fstream tempFile(this->Path, ios_base::in | ios_base::binary);
	if (tempFile.is_open()) {
		tempFile.close();
		cout << "Volume da ton tai!" << endl;
		return false;
	}
	fstream file(this->Path, ios_base::out | ios_base::binary);
	if (!file) {
		cout << "Something went wrong! Please check the path again!" << endl;
		return false;
	}
	if (file.is_open()) {
		file.clear();
		//Write
		file.write(&this->Signature[0], 3);
		file.write((char*)&this->NumberOfEntry, 2);
		file.write((char*)&this->BeginSectorOfEntryTable, 4);
		file.write(&this->Password[0], 64);
		//Ghi tiếp cho đủ 512B
		for (int i = 74; i <= 512; i++) {
			uint8_t x = 0;
			file.write((char*)&x, 1);
		}
		file.close();
		fstream VolumeList(VolumeListPath, ios_base::app);
		VolumeList << this->Path << endl;
		VolumeList.close();
		return true;
	}
	return false;
}

bool Volume::read() {
	fstream file(this->Path, ios_base::in | ios_base::binary);
	if (file.is_open()) {
		//Read
		file.read(&this->Signature[0], 3);
		file.read((char*)&this->NumberOfEntry, 2);
		file.read((char*)&this->BeginSectorOfEntryTable, 4);
		file.read(&this->Password[0], 64);
		file.close();
		return true;
	}
	return false;
}

bool Volume::write() {
	fstream file(this->Path, ios_base::binary|ios::out|ios::in);
	if (file.is_open()) {
		file.seekp(0);
		file.write(this->Signature.c_str(), 3);
		file.write((char*)&this->NumberOfEntry, 2);
		file.write((char*)&this->BeginSectorOfEntryTable, 4);
		file.write(this->Password.c_str(), 64);
		file.close();
		return true;
	}
	return false;
}