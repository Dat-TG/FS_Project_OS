#pragma once
#include <iostream>
#include <vector>
#include "Entry.h"
using namespace std;
class EntryTable {
private:
	vector<Entry> EntryList;//Danh sách các Entry 
	vector<Entry>RemoveList;//Danh sách File đã xóa
public:
	EntryTable();
	~EntryTable();
	vector<Entry> getEntryList();
	vector<Entry> getRemoveList();
	void addEntry(Entry e);
	void readEntryList(string volumePath);
	void setEntryList(vector<Entry>list);
	void setRemoveList(vector<Entry>list);
};
