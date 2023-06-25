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