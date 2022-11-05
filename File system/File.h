#pragma once
#include <vector>
#include "Entry.h"
class File: public Entry {
private:
	vector<Entry*>subFileList;//Danh sách entry của các file/folder con nếu có
public:
	File();
	~File();
};
