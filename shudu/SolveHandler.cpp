#include <iostream>
#include "SolveHandler.h"
using namespace std;

void SolverHandler::insert(int i, int j, int num) {
    matrix[i][j] = num;
    if (num == '$') {
        blank.push(make_pair(i, j));
    }
    else {
        row[i] |= (1 << num);
        col[j] |= (1 << num);
        patch[(i / 3) * 3 + j / 3] |= (1 << num);
    }
}

void SolverHandler::remove(int i, int j) {
    int num = matrix[i][j];
    if (num != '$') {
        matrix[i][j] = (int)'$';
        row[i] ^= (1 << num);
        col[j] ^= (1 << num);
        patch[(i / 3) * 3 + j / 3] ^= (1 << num);
    }
    blank.push(make_pair(i, j));
}

void SolverHandler::replace(int i, int j, int newNum) {
    int oldNum = matrix[i][j];
    if (oldNum == '$') {
        insert(i, j, newNum);
    }
    else {
        matrix[i][j] = newNum;
        int mask = (1 << oldNum) | (1 << newNum);
        row[i] ^= mask;
        col[j] ^= mask;
        patch[(i / 3) * 3 + j / 3] ^= mask;
    }
}

int SolverHandler::getMask(int i, int j) {
    int mask = 0;
    mask |= row[i];
    mask |= col[j];
    mask |= patch[(i / 3) * 3 + j / 3];
    return mask;
}

void SolverHandler::input(fstream& f) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char val;
            f >> val;
            int num = val;
            if (val != '$') {
                val -= '0';
            }
            insert(i, j, val);
        }
    }
    // remove empty line
    f.get();
    f.get();
}

void SolverHandler::inputFromMatrix(int** matrix) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            insert(i, j, matrix[i][j]);
        }
    }
}

void SolverHandler::output(fstream& f) {
    for (int i = 0; i < 9; i++) {
        f << matrix[i][0];
        for (int j = 1; j < 9; j++) {
            f << ' ' << matrix[i][j];
        }
        f << endl;
    }
    f << endl;
}

int SolverHandler::solve() {
    if (blank.empty()) {
        // No blank positions, success
        return 0;
    }
    pair<int, int> coord = blank.top();
    blank.pop();
    int mask = getMask(coord.first, coord.second);
    for (int i = 1; i <= 9; i++) {
        if ((mask & (1 << i)) == 0) {
            //Not used, search down
            replace(coord.first, coord.second, i);
            int result = solve();
            if (result == 0) {
                return 0;
            }
        }
    }
    //coords pushed back here
    remove(coord.first, coord.second);
    return -1;
}

