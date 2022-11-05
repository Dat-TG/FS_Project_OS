#include <iostream>
#include "SHA256.h"
using namespace std;
int main() {
	char password[] = "Hello World!";
	cout << SHA256(password) << endl;
	return 0;
}