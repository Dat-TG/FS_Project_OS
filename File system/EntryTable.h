#pragma once
#include <iostream>
#include <vector>
#include "Entry.h"
using namespace std;
class EntryTable {
private:
	vector<Entry*> EntryList;//Danh s�ch c�c Entry 
public:
	EntryTable();
	~EntryTable();
};