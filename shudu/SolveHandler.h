#pragma once
#include<iostream>
#include<fstream>
#include<algorithm>
#include<stack>
#include<assert.h>
using namespace std;

struct SolverHandler
{
public:
    int matrix[9][9] = { 0 };
    stack<pair<int, int>> blank;    //blank coordinates
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
};