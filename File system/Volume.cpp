#include "Volume.h"
Volume::Volume() {

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
void Volume::setNumberOfEntry(uint16_t value) {
	this->NumberOfEntry = value;
}
void Volume::setBeginSectorOfEntryTable(uint32_t value) {
	this->BeginSectorOfEntryTable = value;
}
void Volume::setPassword(string password) {
	this->Password = password;
}