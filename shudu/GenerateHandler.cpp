#include <iostream>
#include <fstream>
#include <sstream>
#include "GenerateHandler.h"
#include <ctime>
using namespace std;

bool Generatehandler::generate(int num, int beginNum, int endNum, bool isUnion) {
	/*思路：从beginNum开始挖空，
	如果需要判断union：
	判断不成立后，重新迭代100次，
	超过100次则挖空数+1后重新生成
	直至endNum*/
	fstream infile(absolatePath+FinalPath, ios::in);
	fstream outfile(absolatePath+outputPath, ios::out);
	if (!infile.is_open()) {
		cout << "未找到输入文件的路径!" << endl;
	}
	if (!outfile.is_open()) {
		cout << "文件打开失败!" << endl;
		return false;
	}
	cout << "---------------正在生成" << num << "个数独题目---------------" << endl;
	input(infile);//将终局读入matrix数组
	infile.close();
	if (isUnion == false) {
		for (int i = 0; i < num; i++) {
			//在范围内随机生成挖空个数
			current_HoleNum = generateRandomNumber(beginNum, endNum);
			
			//挖current_HoleNum个洞
			holehole();
			
			//随机挑选一个终局
			SelectFinal();
		
			//将终局挖空后的结果输出到文件
			for (int row = 0; row < 9; row++) {
				if (holeboard[row][0] == 1) {
					outfile << " $";
				}
				else {
					outfile << " " << matrix[current_selectFinal][row][0];
				}
				for (int col = 1; col < 9; col++) {
					if (holeboard[row][col] == 1) {
						outfile << " $";
					}
					else {
						outfile << " " << matrix[current_selectFinal][row][col];
					}
				}
				outfile << endl;
			}
			outfile << endl;
		}
		outfile.close();
	}
	else {
		//使用回溯法生成唯一解的数独
		vector<std::vector<int>> board;
		for (int t = 0; t < num; t++) {
			//在范围内随机生成挖空个数
			current_HoleNum = generateRandomNumber(beginNum, endNum);
			generateSudoku(board);
			holehole();
			//std::cout << std::endl << "数独游戏题目 #" << i + 1 << ":" << std::endl;
			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 9; col++) {

				}
			}
			output(outfile, board);
		}
		outfile.close();
	}
	cout << "生成完成!";
	return true;
}

int Generatehandler::generateRandomNumber(int min, int max) {
	// 设置随机数引擎和分布
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);

	// 生成随机数
	int randomNumber = dis(gen);
	return randomNumber;
}

void Generatehandler::output(fstream& outfile, vector<std::vector<int>>& board) {
	for (int row = 0; row < 9; row++) {
		if (holeboard[row][0] == 1) {
			outfile << " $";
		}
		else {
			outfile << " " << board[row][0];
		}
		for (int col = 1; col < 9; col++) {
			if (holeboard[row][col] == 1) {
				outfile << " $";
			}
			else {
				outfile << " " << board[row][col];
			}
		}
		outfile << endl;
	}
	outfile << endl;
}
bool Generatehandler::isValid(const std::vector<std::vector<int>>& board, int row, int col, int num) {
	// 检查行是否有重复数字
	for (int i = 0; i < 9; ++i) {
		if (board[row][i] == num) {
			return false;
		}
	}

	// 检查列是否有重复数字
	for (int i = 0; i < 9; ++i) {
		if (board[i][col] == num) {
			return false;
		}
	}

	// 检查小九宫格是否有重复数字
	int startRow = row - row % 3;
	int startCol = col - col % 3;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			size_t rowIndex = static_cast<size_t>(startRow) + i;
			size_t colIndex = static_cast<size_t>(startCol) + j;
			if (board[rowIndex][colIndex] == num) {
				return false;
			}
			/*if (board[startRow + i][startCol + j] == num) {
				return false;
			}*/
		}
	}

	return true;  // 可以放置数字
}

bool Generatehandler::solveSudoku(std::vector<std::vector<int>>& board) {
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			if (board[row][col] == 0) {  // 当前位置为空
				for (int num = 1; num <= 9; ++num) {  // 尝试数字 1 到 9
					if (isValid(board, row, col, num)) {
						board[row][col] = num;  // 放置数字

						if (solveSudoku(board)) {
							return true;  // 找到解
						}

						board[row][col] = 0;  // 回溯，重置为空
					}
				}

				return false;  // 无解
			}
		}
	}

	return true;  // 完成数独
}
void Generatehandler::generateSudoku(std::vector<std::vector<int>>& board) {
	std::srand(static_cast<unsigned int>(std::time(0)));  // 设置随机数种子

	// 清空数独游戏
	board.clear();
	board.resize(9, std::vector<int>(9, 0));

	// 随机填充第一行
	for (int col = 0; col < 9; ++col) {
		board[0][col] = col + 1;
	}

	// 混洗第一行的数字
	std::random_shuffle(board[0].begin(), board[0].end());

	// 生成唯一解的数独游戏
	solveSudoku(board);
}

void Generatehandler::holehole() {
	//置零
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			holeboard[i][j] = 0;
		}
	}
	//先挖掉，每行挖两个，再从剩余的空中挖
	for (int i = 0; i < 9; i++) {
		// 设置种子，确保每次运行生成的随机数序列不同
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		// 生成1到9之间的随机数
		int hole1 = generateRandomNumber(0, 8);
		int hole2 = generateRandomNumber(0, 8);
		while (hole1 == hole2) {
			hole2 = generateRandomNumber(0, 8);
		}
		//将这两个位置设置为挖去状态
		holeboard[i][hole1] = 1;
		holeboard[i][hole2] = 1;
	}


	int restHole = current_HoleNum - 18;
	while (restHole--) {
		int row= generateRandomNumber(0, 8);
		int col= generateRandomNumber(0, 8);
		while (holeboard[row][col] == 1) {
			row = generateRandomNumber(0, 8);
			col = generateRandomNumber(0, 8);
		}
		holeboard[row][col] = 1;
	}
	return;
}

void Generatehandler::input(fstream& file) {
	//获取一个终局，将其存入matrix数组
	string line;
	int a=0, b=0, c=0;//[a][b][c]
	bool isbreak = false;
	while (std::getline(file, line)) {
		if (line.empty()) {
			// 遇到空行时，跳过并处理下一组数据
			// 这里可以将numbers存储到适当的数据结构中，或进行其他操作
			// 清空numbers以准备下一组数据的读取
			a++;
			b = 0;
			if (isbreak) {
				FinalNum = a - 1;
				break;
			}
			continue;
			isbreak = true;
		}
		isbreak = false;
		std::istringstream iss(line);
		int num;
		for (int i = 0; i < 9; i++) {
			iss >> num;
			matrix[a][b][i] = num;
			//cout << "matrix[" << a << "," << b << "," << i << "]:" << num << endl;
		}
		
		b++;
		if (a > 100) {//只存100个终局
			break;
		}
	}
}

int Generatehandler::isNum(const string& s) {
	size_t size = s.size();
	if (size > 7)
		return -1;
	for (size_t i = 0; i < size; i++) {
		int ascii = int(s[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return -1;
	}
	return stoi(s);
}

void Generatehandler::SelectFinal() {
	//随机挑选一个终局
	std::srand(static_cast<unsigned int>(std::time(0)));  // 设置种子，确保每次运行生成的随机数序列不同
	current_selectFinal = generateRandomNumber(0, FinalNum);  // 生成1到100之间的随机数
}