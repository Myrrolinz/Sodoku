#include"progress.h"

void ProgressBar::start() {
	// ��¼��ʼʱ�䣬����ʼ����ʱ��
	this->beginTime = steady_clock::now();
	this->lastTime = this->beginTime;
	// ��ʱ�����ڶ�ʱ�����ػ溯��
	this->timer.start(this->interval.count(), std::bind(&ProgressBar::show, this));
}

// �ػ溯��
void ProgressBar::show() {
	// ����ϴεĻ�������
	std::cout << "\r";
	// ��¼�ػ��ʱ���
	steady_clock::time_point now = steady_clock::now();
	// ��ȡ����ɵ�����
	unsigned int tmpFinished = this->finishedNum.load();
	// ��ȡ�뿪ʼʱ����ϴ��ػ�ʱ���ʱ����
	auto timeFromStart = now - this->beginTime;
	auto timeFromLast = now - this->lastTime;
	// �����ɵ�����
	unsigned int gap = tmpFinished - this->lastNum;
	// �����ٶ�
	double rate = gap / duration<double>(timeFromLast).count();
	// Ӧ��ʾ�İٷ���
	double present = (100.0 * tmpFinished) / this->totalNum;
	// ��ӡ�ٷ���
	std::cout << std::setprecision(1) << std::fixed << present << "%|";
	// ����Ӧ�û��ƶ���=����
	int barWidth = present * this->colsRatio;
	// ��ӡ����ɺ�δ��ɽ�����
	std::cout << std::setw(barWidth) << std::setfill('=') << "=";
	std::cout << std::setw(this->ncols - barWidth) << std::setfill(' ') << "|";

	// ��ӡ�ٶ�
	std::cout << std::setprecision(1) << std::fixed << rate << "op/s|";
	// ֮������������ݷֱ�Ϊ��ӡ�ѹ���ʱ���ʣ��ʱ��
	int timeFromStartCount = duration<double>(timeFromStart).count();

	std::time_t tfs = timeFromStartCount;
	tm tmfs;
	gmtime_s(&tmfs, &tfs);
	std::cout << std::put_time(&tmfs, "%X") << "|";

	int timeLast;
	if (rate != 0) {
		// ʣ��ʱ��Ĺ���������ε��ٶȺ�δ��ɵ��������й���
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
	// ֹͣ��ʱ��
	this->timer.stop();
	std::cout << std::endl;
}