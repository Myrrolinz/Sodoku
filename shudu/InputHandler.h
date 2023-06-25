#pragma once
#include <iostream>
#include <string>

using namespace std;

class InputHandler {
public:
	void check(int argc, char** argv);

private:
	int isNum(const string& s);
};

