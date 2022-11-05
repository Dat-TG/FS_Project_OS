#pragma once
#include <iostream>
using namespace std;
class Entry {
protected:
	string MainName; //Tên chính
	string ExtensionName; //Tên mở rộng
	uint8_t Status; //Trạng thái (0: chưa bị xóa, 1: đã bị xóa)
	uint8_t Children; //Số file/folder con
	uint16_t ModifiedTime; //Thời gian cập nhật
	uint16_t ModifiedDate; //Ngày cập nhật
	uint16_t BeginSector; //Sector bắt đầu
	uint32_t Size; //Kích thước
	string Password; //Mật khẩu
public:
	Entry();
	~Entry();
	string getMainName();
	string getExtensionName();
	uint8_t getStatus();
	uint8_t getChildren();
	uint16_t getModifiedTime();
	uint16_t getModifiedDate();
	uint16_t getBeginSector();
	uint32_t getSize();
	string getPassWord();
	void setMainName(const char* name);
	void setExtensionName(const char* name);
	void setStatus(uint8_t status);
	void setModifiedTime(uint16_t data);
	void setModifiedDate(uint16_t data);
	void setBeginSector(uint16_t sector);
	void setSize(uint32_t size);
	void setPassWord(const char* password);
	void setChildren(uint8_t value);
};