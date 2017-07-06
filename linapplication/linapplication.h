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
void slotOnChangefile2();//�ٶ��׸�ʽ�ļ�ת��
void slotOnactionChange_HANDVEL_type();
void slotOnChangeTops();
void slotOnChangeDXDY2Angle();
void slotOnChangeGss2InlineXlineTimeValue();//ת��gss�ļ�ΪInlineCmpTimeValue
void slotTiqu();
private:
	Ui::linapplicationClass ui;
};

#endif // LINAPPLICATION_H
