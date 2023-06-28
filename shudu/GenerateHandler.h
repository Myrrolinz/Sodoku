#pragma once
#include <iostream>
#include <string>
#include<math.h>
#include "timer.h"
#include <algorithm>
#include <vector>
#include <random>
#include "SolveHandler.h"
using namespace std;

class Generatehandler {
private:
	string FinalPath = "final.txt";
	string outputPath = "question.txt";
	string absolatePath = "D:\\LessonProjects\\shudu\\shudu";
	int FinalNum = 0;//�վ���Ŀ
	int current_HoleNum = 0;//��ǰ�ڿ���
	int current_selectFinal = 0;//��ǰʹ�õ������վ�
	int matrix[100][9][9] = { 0 };//����һ�������飬�洢���100���վ�
	int holeboard[9][9] = { 0 };//��ǰ�ڿյ�����λ��
public:
	void generate(int num, int beginNum, int endNum, bool isUnion);
	void holehole();//��ѽ��ѽ��
	void input(fstream& f);
	void output(fstream& f, vector<std::vector<int>>& board);
	void SelectFinal();
	int isNum(const string &s);
	// ����ڸ���λ�� (row, col) �Ƿ���Է������� num
	bool isValid(const vector<std::vector<int>>& board, int row, int col, int num);
	// ʹ�û����㷨����������Ϸ��Ψһ��
	bool solveSudoku(vector<std::vector<int>>& board);
	// ����������Ϸ��Ŀ
	void generateSudoku(vector<std::vector<int>>& board);
	//������min-max��Χ��������
	int generateRandomNumber(int min, int max);
	//���þ���·��
	void setAbsPath(string abs) {
		absolatePath = abs;
	}
};
