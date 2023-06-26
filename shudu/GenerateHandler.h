#pragma once
#include <iostream>
#include <string>
#include<math.h>
#include "timer.h"
#include <algorithm>
using namespace std;

class Generatehandler {
public:
	string FinalPath = "final.txt";
	string outputPath = "question.txt";
	void generate(int num, int beginNum, int endNum, bool isUnion = false);
	static char ques_board[10][20];
};
