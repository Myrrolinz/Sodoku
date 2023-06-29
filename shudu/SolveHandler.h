// (C) Copyright 2023 Yunmei Guan, Jiaqi Shi
// Description：Sudoku Game
// Author：GYM, SJQ
// Date:2023-6
// Modify Record:
#pragma once
#include<assert.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<stack>
#include <utility>
using namespace std;
//using std::cout;
//using std::endl;

struct SolverHandler {
 public:
    int matrix[9][9] = { 0 };
    stack<pair<int, int>> blank; // blank coordinates
    int row[9] = { 0 };
    int col[9] = { 0 };
    int patch[9] = { 0 };
    void insert(int i, int j, int num);
    void remove(int i, int j);
    void replace(int i, int j, int newNum);
    int getMask(int i, int j);
    void input(fstream& f);
    void output(fstream& f);
    int solve();
    void clean();
};
