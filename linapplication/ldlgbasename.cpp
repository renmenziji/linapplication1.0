#include "ldlgbasename.h"

LDLgBasename::LDLgBasename(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonFolder1, SIGNAL(clicked()), this, SLOT(slotOnFolder1()));
	connect(ui.pushButtonFolder2, SIGNAL(clicked()), this, SLOT(slotOnFolder2()));
	connect(ui.pushButtonSync, SIGNAL(clicked()), this, SLOT(slotOnSync()));
}

LDLgBasename::~LDLgBasename()
{

}

void LDLgBasename::slotOnFolder1()
{
	QString strFolder = QFileDialog::getExistingDirectory(this);
	if (strFolder.isEmpty())
	{
		return;
	}
	ui.lineEditFolder1->setText(strFolder);
}
void LDLgBasename::slotOnFolder2()
{
	QString strFolder = QFileDialog::getExistingDirectory(this);
	if (strFolder.isEmpty())
	{
		return;
	}
	ui.lineEditFolder2->setText(strFolder);
}
void LDLgBasename::slotOnSync()
{
	QString strFolder1 = ui.lineEditFolder1->text();
	QString strFolder2 = ui.lineEditFolder2->text();

	if (strFolder1.isEmpty() || strFolder2.isEmpty())
	{
		QMessageBox::warning(this, "", tr("folder is empty"));
	}

	QDir dir1(strFolder1);
	QDir dir2(strFolder2);
	QFileInfoList fi1 = dir1.entryInfoList(QDir::Files);
	QFileInfoList fi2 = dir2.entryInfoList(QDir::Files);

	int i;
	QStringList fs2;
	for (i = 0; i < fi2.count(); i++)
	{
		fs2.append(fi2[i].baseName());
	}
	for (i = 0; i < fi1.count(); i++)
	{
		if (fs2.contains(fi1[i].baseName()) == false)
		{
			QFile::remove(fi1[i].absoluteFilePath());
		}
	}



	QStringList fs1;
	for (i = 0; i < fi1.count(); i++)
	{
		fs1.append(fi1[i].baseName());
	}
	for (i = 0; i < fi2.count(); i++)
	{
		if (fs1.contains(fi2[i].baseName()) == false)
		{
			QFile::remove(fi2[i].absoluteFilePath());
		}
	}

	QMessageBox::warning(this, "", tr("sucess"));
}