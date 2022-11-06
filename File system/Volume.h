#pragma once
#include "EntryTable.h"
class Volume {
private:
	string Signature; //Dấu hiệu DNT
	uint16_t NumberOfEntry; //Số entry của Entry Table
	uint32_t BeginSectorOfEntryTable; //Sector bắt đầu của Entry Table
	string Password; //Mật khẩu của volume đã mã hóa
	string Path; //Địa chỉ lưu Volume
public:
	Volume();
	~Volume();
	//Getter
	uint16_t getNumberOfEntry();
	uint32_t getBeginSectorOfEntryTable();
	string getPassword();
	string getPath();
	string getSignature();
	//Setter
	void setNumberOfEntry(uint16_t value);
	void setBeginSectorOfEntryTable(uint32_t value);
	void setPassword(string password); 
	bool create(); // Tạo volume
	void setPath(string path);
	bool read(); // Đọc thông tin volume
	bool write(); //Ghi sửa thông tin volume
};