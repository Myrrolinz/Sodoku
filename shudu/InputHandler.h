#pragma once
#include <iostream>
#include <string>

using namespace std;

class InputHandler {
public:
	void check(int argc, char** argv);
	void getFinal(int num);
	void getQues(int num);

private:
	int isNum(const string& s);
};

