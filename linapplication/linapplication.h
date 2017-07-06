#ifndef LINAPPLICATION_H
#define LINAPPLICATION_H

#include <QtWidgets/QMainWindow>
#include "ui_linapplication.h"

class linapplication : public QMainWindow
{
	Q_OBJECT

public:
	linapplication(QWidget *parent = 0);
	~linapplication();

public slots:
void slotOnBasename();
void slotOnChangefile();
void slotOnChangefile2();//速度谱格式文件转换
void slotOnactionChange_HANDVEL_type();
void slotOnChangeTops();
void slotOnChangeDXDY2Angle();
void slotOnChangeGss2InlineXlineTimeValue();//转换gss文件为InlineCmpTimeValue
void slotTiqu();
private:
	Ui::linapplicationClass ui;
};

#endif // LINAPPLICATION_H
