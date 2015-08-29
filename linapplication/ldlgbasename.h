#ifndef LDLGBASENAME_H
#define LDLGBASENAME_H

#include <QDialog>
#include "ui_ldlgbasename.h"
#include "qinclude.h"
class LDLgBasename : public QDialog
{
	Q_OBJECT

public:
	LDLgBasename(QWidget *parent = 0);
	~LDLgBasename();

	public slots:
	void slotOnFolder1();
	void slotOnFolder2();
	void slotOnSync();
private:
	Ui::LDLgBasename ui;
};

#endif // LDLGBASENAME_H
