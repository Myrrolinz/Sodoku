#pragma once
#include <iostream>
#include <string>
#include<math.h>
#include "timer.h"
#include <algorithm>
#include <vector>
using namespace std;

class Generatehandler {
public:
	string FinalPath = "final.txt";
	string outputPath = "question.txt";
	int holenum=0;
	void generate(int num, int beginNum, int endNum, bool isUnion = false);
	void holehole();//挖呀挖呀挖
	void input(fstream& f);
	int matrix[9][9] = { 0 };
	int isNum(const string &s);
};
