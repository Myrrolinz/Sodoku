#include"progress.h"

void ProgressBar::start() {
	// 记录开始时间，并初始化定时器
	this->beginTime = steady_clock::now();
	this->lastTime = this->beginTime;
	// 定时器用于定时调用重绘函数
	this->timer.start(this->interval.count(), std::bind(&ProgressBar::show, this));
}

// 重绘函数
void ProgressBar::show() {
	// 清除上次的绘制内容
	std::cout << "\r";
	// 记录重绘的时间点
	steady_clock::time_point now = steady_clock::now();
	// 获取已完成的数量
	unsigned int tmpFinished = this->finishedNum.load();
	// 获取与开始时间和上次重绘时间的时间间隔
	auto timeFromStart = now - this->beginTime;
	auto timeFromLast = now - this->lastTime;
	// 这次完成的数量
	unsigned int gap = tmpFinished - this->lastNum;
	// 计算速度
	double rate = gap / duration<double>(timeFromLast).count();
	// 应显示的百分数
	double present = (100.0 * tmpFinished) / this->totalNum;
	// 打印百分数
	std::cout << std::setprecision(1) << std::fixed << present << "%|";
	// 计算应该绘制多少=符号
	int barWidth = present * this->colsRatio;
	// 打印已完成和未完成进度条
	std::cout << std::setw(barWidth) << std::setfill('=') << "=";
	std::cout << std::setw(this->ncols - barWidth) << std::setfill(' ') << "|";

	// 打印速度
	std::cout << std::setprecision(1) << std::fixed << rate << "op/s|";
	// 之后的两部分内容分别为打印已过的时间和剩余时间
	int timeFromStartCount = duration<double>(timeFromStart).count();

	std::time_t tfs = timeFromStartCount;
	tm tmfs;
	gmtime_s(&tmfs, &tfs);
	std::cout << std::put_time(&tmfs, "%X") << "|";

	int timeLast;
	if (rate != 0) {
		// 剩余时间的估计是用这次的速度和未完成的数量进行估计
		timeLast = (this->totalNum - tmpFinished) / rate;
	}
	else {
		timeLast = INT_MAX;
	}

	if ((this->totalNum - tmpFinished) == 0) {
		timeLast = 0;
	}


	std::time_t tl = timeLast;
	tm tml;
	gmtime_s(&tml, &tl);
	std::cout << std::put_time(&tml, "%X");


	this->lastNum = tmpFinished;
	this->lastTime = now;
}

void ProgressBar::finish() {
	// 停止定时器
	this->timer.stop();
	std::cout << std::endl;
}