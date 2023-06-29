#include <iostream>
#include <fstream>
#include <sstream>
#include "GenerateHandler.h"
#include <ctime>
using namespace std;

bool Generatehandler::generate(int num, int beginNum, int endNum, bool isUnion) {
	/*˼·����beginNum��ʼ�ڿգ�
	�����Ҫ�ж�union��
	�жϲ����������µ���100�Σ�
	����100�����ڿ���+1����������
	ֱ��endNum*/
	fstream infile(absolatePath+FinalPath, ios::in);
	fstream outfile(absolatePath+outputPath, ios::out);
	if (!infile.is_open()) {
		cout << "δ�ҵ������ļ���·��!" << endl;
	}
	if (!outfile.is_open()) {
		cout << "�ļ���ʧ��!" << endl;
		return false;
	}
	cout << "---------------��������" << num << "��������Ŀ---------------" << endl;
	input(infile);//���վֶ���matrix����
	infile.close();
	if (isUnion == false) {
		for (int i = 0; i < num; i++) {
			//�ڷ�Χ����������ڿո���
			current_HoleNum = generateRandomNumber(beginNum, endNum);
			
			//��current_HoleNum����
			holehole();
			
			//�����ѡһ���վ�
			SelectFinal();
		
			//���վ��ڿպ�Ľ��������ļ�
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
		//ʹ�û��ݷ�����Ψһ�������
		vector<std::vector<int>> board;
		for (int t = 0; t < num; t++) {
			//�ڷ�Χ����������ڿո���
			current_HoleNum = generateRandomNumber(beginNum, endNum);
			generateSudoku(board);
			holehole();
			//std::cout << std::endl << "������Ϸ��Ŀ #" << i + 1 << ":" << std::endl;
			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 9; col++) {

				}
			}
			output(outfile, board);
		}
		outfile.close();
	}
	cout << "�������!";
	return true;
}

int Generatehandler::generateRandomNumber(int min, int max) {
	// �������������ͷֲ�
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);

	// ���������
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
	// ������Ƿ����ظ�����
	for (int i = 0; i < 9; ++i) {
		if (board[row][i] == num) {
			return false;
		}
	}

	// ������Ƿ����ظ�����
	for (int i = 0; i < 9; ++i) {
		if (board[i][col] == num) {
			return false;
		}
	}

	// ���С�Ź����Ƿ����ظ�����
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

	return true;  // ���Է�������
}

bool Generatehandler::solveSudoku(std::vector<std::vector<int>>& board) {
	for (int row = 0; row < 9; ++row) {
		for (int col = 0; col < 9; ++col) {
			if (board[row][col] == 0) {  // ��ǰλ��Ϊ��
				for (int num = 1; num <= 9; ++num) {  // �������� 1 �� 9
					if (isValid(board, row, col, num)) {
						board[row][col] = num;  // ��������

						if (solveSudoku(board)) {
							return true;  // �ҵ���
						}

						board[row][col] = 0;  // ���ݣ�����Ϊ��
					}
				}

				return false;  // �޽�
			}
		}
	}

	return true;  // �������
}
void Generatehandler::generateSudoku(std::vector<std::vector<int>>& board) {
	std::srand(static_cast<unsigned int>(std::time(0)));  // �������������

	// ���������Ϸ
	board.clear();
	board.resize(9, std::vector<int>(9, 0));

	// �������һ��
	for (int col = 0; col < 9; ++col) {
		board[0][col] = col + 1;
	}

	// ��ϴ��һ�е�����
	std::random_shuffle(board[0].begin(), board[0].end());

	// ����Ψһ���������Ϸ
	solveSudoku(board);
}

void Generatehandler::holehole() {
	//����
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			holeboard[i][j] = 0;
		}
	}
	//���ڵ���ÿ�����������ٴ�ʣ��Ŀ�����
	for (int i = 0; i < 9; i++) {
		// �������ӣ�ȷ��ÿ���������ɵ���������в�ͬ
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		// ����1��9֮��������
		int hole1 = generateRandomNumber(0, 8);
		int hole2 = generateRandomNumber(0, 8);
		while (hole1 == hole2) {
			hole2 = generateRandomNumber(0, 8);
		}
		//��������λ������Ϊ��ȥ״̬
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
	//��ȡһ���վ֣��������matrix����
	string line;
	int a=0, b=0, c=0;//[a][b][c]
	bool isbreak = false;
	while (std::getline(file, line)) {
		if (line.empty()) {
			// ��������ʱ��������������һ������
			// ������Խ�numbers�洢���ʵ������ݽṹ�У��������������
			// ���numbers��׼����һ�����ݵĶ�ȡ
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
		if (a > 100) {//ֻ��100���վ�
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
	//�����ѡһ���վ�
	std::srand(static_cast<unsigned int>(std::time(0)));  // �������ӣ�ȷ��ÿ���������ɵ���������в�ͬ
	current_selectFinal = generateRandomNumber(0, FinalNum);  // ����1��100֮��������
}