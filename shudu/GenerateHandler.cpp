#include <iostream>
#include <fstream>
#include "GenerateHandler.h"
using namespace std;

void Generatehandler::generate(int num, int beginNum, int endNum, bool isUnion = false) {
	/*思路：从beginNum开始挖空，
	如果需要判断union：
	判断不成立后，重新迭代100次，
	超过100次则挖空数+1后重新生成
	直至endNum*/
	fstream infile(FinalPath, ios::in);
	fstream outfile(outputPath, ios::out);
	if (!outfile.is_open()) {
		cout << "文件打开失败！" << endl;
		return;
	}
	cout << "---------------正在生成" << num << "个数独题目---------------" << endl;
	if (beginNum <= 17||beginNum>64) {
		if (isUnion) {
			cout<<""
		}
	}
}