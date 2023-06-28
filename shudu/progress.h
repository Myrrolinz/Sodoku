#pragma once
#include <ctime>
#include <chrono>
#include <iostream>
#include <iomanip>
#include "timer.h"


using namespace std::chrono;

class ProgressBar
{
protected:
	// �������ĳ��ȣ�������ǰ��׺��
	unsigned int ncols;
	// ����ɵ�����
	std::atomic<unsigned int> finishedNum;
	// �ϴε����������
	unsigned int lastNum;
	// ����
	unsigned int totalNum;
	// ������������ٷֱ�֮���ϵ��
	double colsRatio;
	// ��ʼʱ��
	steady_clock::time_point beginTime;
	// �ϴ��ػ��ʱ��
	steady_clock::time_point lastTime;
	// �ػ�����
	milliseconds interval;
	Timer timer;
public:
	ProgressBar(unsigned int totalNum, milliseconds interval) : totalNum(totalNum), interval(interval), finishedNum(0), lastNum(0), ncols(80), colsRatio(0.8) {}
	// ��ʼ
	void start();
	// ���
	void finish();
	// ����
	void update() { return this->update(1); }
	// һ�θ��¶������
	void update(unsigned int num) { this->finishedNum += num; }
	// ��ȡ����������
	unsigned int getCols() { return this->ncols; }
	// ���ý���������
	void setCols(unsigned int ncols) { this->ncols = ncols; this->colsRatio = ncols / 100; }
	// �ػ�
	void show();
};
