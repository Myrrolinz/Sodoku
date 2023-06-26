#include <iostream>
#include <string>
#include "InputHandler.h"
using namespace std;

int main(int argc, char* argv[]) {
	InputHandler ih;
	/*cout << "请输入存储文件的绝对路径:" << endl;
	string abs;
	cin >> abs;
	ih.setAbsPath(abs);*/
	ih.check(argc, argv);
	return 0;
}