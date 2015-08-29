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
private:
	Ui::linapplicationClass ui;
};

#endif // LINAPPLICATION_H
