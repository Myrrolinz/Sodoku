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
	// 进度条的长度（不包含前后缀）
	unsigned int ncols;
	// 已完成的数量
	std::atomic<unsigned int> finishedNum;
	// 上次的已完成数量
	unsigned int lastNum;
	// 总数
	unsigned int totalNum;
	// 进度条长度与百分比之间的系数
	double colsRatio;
	// 开始时间
	steady_clock::time_point beginTime;
	// 上次重绘的时间
	steady_clock::time_point lastTime;
	// 重绘周期
	milliseconds interval;
	Timer timer;
public:
	ProgressBar(unsigned int totalNum, milliseconds interval) : totalNum(totalNum), interval(interval), finishedNum(0), lastNum(0), ncols(80), colsRatio(0.8) {}
	// 开始
	void start();
	// 完成
	void finish();
	// 更新
	void update() { return this->update(1); }
	// 一次更新多个数量
	void update(unsigned int num) { this->finishedNum += num; }
	// 获取进度条长度
	unsigned int getCols() { return this->ncols; }
	// 设置进度条长度
	void setCols(unsigned int ncols) { this->ncols = ncols; this->colsRatio = ncols / 100; }
	// 重绘
	void show();
};
