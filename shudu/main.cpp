#include <iostream>
#include <string>
#include "InputHandler.h"
using namespace std;

int main(int argc, char* argv[]) {
	InputHandler ih;
	cout << "������洢�ļ��ľ���·��:" << endl;
	string abs;
	cin >> abs;
	ih.setAbsPath(abs);
	ih.check(argc, argv);
	return 0;
}