#include "Entry.h"
#include <fstream>
Entry::Entry() {
	this->Status = 0;
	this->ModifiedTime=0;
	this->ModifiedDate=0;
	this->BeginSector=0;
	this->Size=0;
	this->MainName = "";
	this->ExtensionName = "";
	this->Password = "";
}
Entry::~Entry() {
	
}
string Entry::getMainName() {
	return this->MainName;
}
string Entry::getExtensionName() {
	return this->ExtensionName;
}
uint8_t Entry::getStatus() {
	return this->Status;
}
uint8_t Entry::getChildren() {
	return this->Children;
}
uint16_t Entry::getModifiedTime() {
	return this->ModifiedTime;
}
uint16_t Entry::getModifiedDate() {
	return this->ModifiedDate;
}
uint32_t Entry::getBeginSector() {
	return this->BeginSector;
}
uint32_t Entry::getSize() {
	return this->Size;
}
string Entry::getPassWord() {
	return this->Password;
}
void Entry::setMainName(const char* name) {
	this->MainName = name;
}
void Entry::setExtensionName(const char* name) {
	this->ExtensionName = name;
}
void Entry::setStatus(uint8_t status) {
	this->Status = status;
}
void Entry::setChildren(uint8_t value) {
	this->Children = value;
}
void Entry::setModifiedTime(uint16_t data) {
	this->ModifiedTime = data;
}
void Entry::setModifiedDate(uint16_t data) {
	this->ModifiedDate = data;
}
void Entry::setBeginSector(uint32_t sector) {
	this->BeginSector = sector;
}
void Entry::setSize(uint32_t size) {
	this->Size = size;
}
void Entry::setPassWord(string password) {
	this->Password = password;
	//cout << "password truyen vao:" << this->getPassWord() << endl;
}
void Entry::write(string volumePath) {
	fstream vol(volumePath, ios::binary | ios::out | ios::in);
	long long pos = 512LL;
	vol.seekg(pos, ios::beg);
	string main = "";
	while (main.size() < 14) main += ' ';
	string ext = "";
	while (ext.size() < 4) ext += ' ';
	vol.read(&main[0], 14);
	vol.read(&ext[0], 4);
	while (main != this->MainName || ext != this->ExtensionName) {
		//cout << pos << endl;
		pos += 96LL;
		vol.seekg(pos, ios::beg);
		vol.read(&main[0], 14);
		vol.read(&ext[0], 4);
		//cout << main << " " << ext << endl;
	}
	//cout << main << " " << ext << " " << this->Password << endl;
	//system("pause");
	//cout << pos << endl;
	//cout << main << " " << ext << endl; 
	//cout << this->MainName << " " << this->ExtensionName << endl; system("pause");
	vol.seekp(pos, ios::beg);
	vol.write(&this->MainName[0], 14);
	vol.write(&this->ExtensionName[0], 4);
	vol.write((char*)&this->Children, 1);
	vol.write((char*)&this->Status, 1);
	vol.write((char*)&this->ModifiedTime, 2);
	vol.write((char*)&this->ModifiedDate, 2);
	vol.write((char*)&this->BeginSector, 4);
	vol.write((char*)&this->Size, 4);
	vol.write(&this->Password[0], 64);
	vol.close();
}

void Entry::clear(string volumePath) {
	fstream vol(volumePath, ios::binary | ios::out | ios::in);
	long long pos = 512LL;
	vol.seekg(pos, ios::beg);
	string main = "";
	while (main.size() < 14) main += ' ';
	string ext = "";
	while (ext.size() < 4) ext += ' ';
	vol.read(&main[0], 14);
	vol.read(&ext[0], 4);
	while (main != this->MainName || ext != this->ExtensionName) {
		//cout << pos << endl;
		pos += 96LL;
		vol.seekg(pos, ios::beg);
		vol.read(&main[0], 14);
		vol.read(&ext[0], 4);
		//cout << main << " " << ext << endl;
	}
	//cout << main << " " << ext << " " << this->Password << endl;
	//system("pause");
	//cout << pos << endl;
	//cout << main << " " << ext << endl; 
	//cout << this->MainName << " " << this->ExtensionName << endl; system("pause");
	vol.seekp(pos, ios::beg);
	uint8_t x = 0;
	for (int i=1;i<=96;i++) vol.write((char*)&x, 1);
	vol.close();
}