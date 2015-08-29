#ifndef LDLGBASENAME_H
#define LDLGBASENAME_H

#include <QDialog>
#include "ui_ldlgbasename.h"

class LDLgBasename : public QDialog
{
	Q_OBJECT

public:
	LDLgBasename(QWidget *parent = 0);
	~LDLgBasename();

private:
	Ui::LDLgBasename ui;
};

#endif // LDLGBASENAME_H
