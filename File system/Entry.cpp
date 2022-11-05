#include "Entry.h"
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
uint16_t Entry::getBeginSector() {
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
void Entry::setBeginSector(uint16_t sector) {
	this->BeginSector = sector;
}
void Entry::setSize(uint32_t size) {
	this->Size = size;
}
void Entry::setPassWord(const char* password) {
	this->Password = password;
}