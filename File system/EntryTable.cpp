#include "EntryTable.h"
#include <fstream>
#include <string>
EntryTable::EntryTable() {

}
EntryTable::~EntryTable() {

}

vector<Entry> EntryTable::getEntryList() {
	return this->EntryList;
}

void EntryTable::addEntry(Entry e) {
	this->EntryList.push_back(e);
}

void EntryTable::readEntryList(string volumePath) {
	fstream file(volumePath, ios::binary | ios::in);
	string MainName = "";
	while (MainName.size() < 14) MainName += ' ';
	string ExtensionName = "";
	while (ExtensionName.size() < 4) ExtensionName += ' ';
	uint16_t ModifiedTime; //Thời gian cập nhật
	uint16_t ModifiedDate; //Ngày cập nhật
	uint32_t Size; //Kích thước
	uint8_t Status = 0; //Trạng thái (0: chưa bị xóa, 1: đã bị xóa)
	uint8_t Children = 0; //Số file/folder con
	string Password = ""; //Mật khẩu
	while (Password.size() < 64) Password += ' ';
 	uint32_t BeginSector; //Sector bắt đầu
	//cout << MainName << endl;
	/*char* data = new char[15];
	file.read(data, 14);
	data[14] = '\0';
	cout << data << endl;*/
	//char* data = new char[97];
	//file.read(data, 96);
	//cout << data << endl;
	uint32_t pos = 512-96;
	while (pos<UINT16_MAX*96+512) {
		pos += 96;
		Entry e;
		file.seekg(pos, ios::beg);
		file.read(&MainName[0], 14);
		if (MainName[0] == NULL) {
			continue;
		}
		//while (MainName.size()>0 && MainName.back() == ' ') MainName.pop_back();
		e.setMainName(MainName.c_str());
		file.read(&ExtensionName[0], 4);
		//while (ExtensionName.size()>0 && ExtensionName.back() == ' ') ExtensionName.pop_back();
		e.setExtensionName(ExtensionName.c_str());
		//cout << MainName.size() << " " << ExtensionName.size() << endl; system("pause");
		file.read((char*)&Children, 1);
		file.read((char*)&Status, 1);
		file.read((char*)&ModifiedTime, 2);
		file.read((char*)&ModifiedDate, 2);
		file.read((char*)&BeginSector, 4);
		file.read((char*)&Size, 4);
		file.read(&Password[0], 64);
		e.setBeginSector(BeginSector);
		e.setChildren(Children);
		e.setModifiedDate(ModifiedDate);
		e.setModifiedTime(ModifiedTime);
		e.setPassWord(Password.c_str());
		e.setSize(Size);
		if (Status == 0) this->EntryList.push_back(e);
		else this->RemoveList.push_back(e);
		file.seekg(pos, ios::beg);
	}
	file.close();
}

void EntryTable::setEntryList(vector<Entry>list) {
	this->EntryList = list;
}

vector<Entry> EntryTable::getRemoveList() {
	return this->RemoveList;
}

void EntryTable::setRemoveList(vector<Entry>list) {
	this->RemoveList = list;
}