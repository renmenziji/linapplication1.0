#include "linapplication.h"
#include <QTextStream>
#define PI 3.141592653579798
#ifndef MAX
#define	MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#ifndef MIN
#define	MIN(x,y) ((x) < (y) ? (x) : (y))
#endif
linapplication::linapplication(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.action_basename, SIGNAL(triggered()), this, SLOT(slotOnBasename()));
	connect(ui.actionChangefile, SIGNAL(triggered()), this, SLOT(slotOnChangefile()));
	connect(ui.actionChangefile2, SIGNAL(triggered()), this, SLOT(slotOnChangefile2()));
	connect(ui.actionChange_HANDVEL_type, SIGNAL(triggered()), this, SLOT(slotOnactionChange_HANDVEL_type()));
	connect(ui.actionchangeTops, SIGNAL(triggered()), this, SLOT(slotOnChangeTops()));
	connect(ui.actionChangeDXDY2Angle, SIGNAL(triggered()), this, SLOT(slotOnChangeDXDY2Angle()));
	connect(ui.actionSdf, SIGNAL(triggered()), this, SLOT(slotOnChangeGss2InlineXlineTimeValue()));
	connect(ui.actionTiqu, SIGNAL(triggered()), this, SLOT(slotTiqu()));
}

linapplication::~linapplication()
{

}
#include "ldlgbasename.h"
void linapplication::slotOnBasename()
{
	LDLgBasename *dlg= new LDLgBasename(this);
	dlg->show();
}

struct CVelItem
{
	QString x, y, t, d;
};
void linapplication::slotOnChangefile()
{
	QString strFileIn = QFileDialog::getOpenFileName();
	if (strFileIn.isEmpty())
	{
		return;
	}
	QFile fileIn(strFileIn);
	if (fileIn.open(QFile::ReadOnly)==false)
	{
		QMessageBox::warning(this, "error", "read file failed");
		return;
	}
	QFile fileOut(strFileIn + ".out");
	if (!fileOut.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, "error", "write file failed");
		return;
	}
	CVelItem velitem;
	QList<CVelItem> lstItem;
	bool bSpntFirst = true; 
	while (!fileIn.atEnd())
	{
		QString strLine = fileIn.readLine();
		if (strLine.contains("SPNT"))
		{
			strLine = strLine.simplified();
			QStringList lstPart = strLine.split(" ");
			if (lstPart.count()>3)
			{
				velitem.x = lstPart[lstPart.count() - 1 - 1];
				velitem.y = lstPart[lstPart.count() - 1 ];
			}
			bSpntFirst = true;
		}
		else if (strLine.contains("VELF"))
		{
			strLine = strLine.simplified();
			QStringList lstPart = strLine.split(" ");

			if (bSpntFirst)
			{
				//去除
				//VELF      91960    0 
				lstPart.removeFirst();
				lstPart.removeFirst();
				lstPart.removeFirst();
			}
			else
			{
				//去除
				//VELF      
				lstPart.removeFirst();

			}
			bSpntFirst = false;

			for (int i = 0;i < lstPart.count()/2;i++)
			{
				velitem.t = lstPart[i * 2];
				velitem.d = lstPart[i * 2+1];
				lstItem.append(velitem);
			}
		}
	}
	fileIn.close();


	QTextStream ts(&fileOut);
	for (int i = 0; i < lstItem.count(); i++)
	{
		ts << lstItem[i].x << "\t"
			<< lstItem[i].y << "\t"
			<< lstItem[i].t << "\t"
			<< lstItem[i].d << "\n";
	}
	fileOut.close();
}


void linapplication::slotOnactionChange_HANDVEL_type()
{
	QString strFileIn = QFileDialog::getOpenFileName();
	if (strFileIn.isEmpty())
	{
		return;
	}
	QFile fileIn(strFileIn);
	if (fileIn.open(QFile::ReadOnly)==false)
	{
		QMessageBox::warning(this, "error", "read file failed");
		return;
	}
	QFile fileOut(strFileIn + ".out");
	if (!fileOut.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, "error", "write file failed");
		return;
	}
	QStringList lstOut;
	QString str4len;//4位长度
	while (!fileIn.atEnd())
	{
		QString strLine = fileIn.readLine();
		strLine.remove("\n");
		//两种情况
		//HANDVEL1010      620         75456                                             
		//变为
		//HANDVEL 1010 620         75456                   

		//HANDVEL1010      1620         75456                                             
		//变为
		//HANDVEL 10101620         75456                             

		if (strLine.contains("HANDVEL"))
		{
			strLine = strLine.simplified();
			strLine.remove("HANDVEL");
			if (strLine[8]!=' ')//不为空格，则为数字，则为4位的数字
			{
				strLine.remove(4, 1);
			}
			strLine = "HANDVEL " + strLine;
			lstOut.append(strLine);
		}
		else 
		{
			lstOut.append(strLine);
		}
	}
	fileIn.close();


	QTextStream ts(&fileOut);
	for (int i = 0; i < lstOut.count(); i++)
	{
		ts << lstOut[i]<< "\n";
	}
	fileOut.close();
}
void linapplication::slotOnChangefile2()//速度谱格式文件转换
{
	QString strFileIn = QFileDialog::getOpenFileName();
	if (strFileIn.isEmpty())
	{
		return;
	}
	QFile fileIn(strFileIn);
	if (fileIn.open(QFile::ReadOnly)==false)
	{
		QMessageBox::warning(this, "error", "read file failed");
		return;
	}
	QFile fileOut(strFileIn + ".out");
	if (!fileOut.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, "error", "write file failed");
		return;
	}
	CVelItem velitem;
	QList<CVelItem> lstItem;
	bool bSpntFirst = true; 
	while (!fileIn.atEnd())
	{
		QString strLine = fileIn.readLine();
		if (strLine.contains("#"))
		{
			continue;
		}
		else 
		{
			strLine = strLine.simplified();
			QStringList lstPart = strLine.split(" ");

			if (lstPart.count()==4)
			{
				//去除
				//    HANDVEL  30        120         37240          
				velitem.x = lstPart[1];
				velitem.y = lstPart[2];
// 				velitem.t = lstPart[3];
// 				velitem.d = lstPart[4];
			}
			else if (lstPart.count()%2==0)//整除2
			{
				for (int i = 0; i < lstPart.count();i+=2)
				{
					velitem.t = lstPart[i];
					velitem.d = lstPart[i + 1];
					lstItem.append(velitem);
				}
			}
		}
	}
	fileIn.close();


	QTextStream ts(&fileOut);
	for (int i = 0; i < lstItem.count(); i++)
	{
		ts << lstItem[i].x << "\t"
			<< lstItem[i].y << "\t"
			<< lstItem[i].t << "\t"
			<< lstItem[i].d << "\n";
	}
	fileOut.close();
}

#include <QAxObject>
#include <QInputDialog>

struct CItemTop
{
	QString strWell;
	QString strTop;
	double data;
};



//#include "ui_ldlgchangeexceltops.h"
void linapplication::slotOnChangeTops()
{
	int i, j;
	//int dataStart = 4;//层位数据起始行
	int topDataIndex = 1;//顶深	底深	砂层厚度 1 2 3 ，如果遇到这种格式，一个层名里有多个属性，这里可以进行选择
	QPoint posWell = QPoint(4, 1);//第一个井所在的位置
	QPoint posTops = QPoint(2,4);//第一个层名所在的位置
	QString strFileIn = QFileDialog::getOpenFileName();
	if (strFileIn.isEmpty())
	{
		return;
	}

	QStringList lstWells, lstTops;
	QString strWell, strTop;
	QList<CItemTop> lstItem;
	CItemTop item0;
	{
		QAxObject excel("Excel.Application");
		excel.setProperty("Visible", false);
		QAxObject *work_books = excel.querySubObject("WorkBooks");
		work_books->dynamicCall("Open (const QString&)", QString(strFileIn));
		QVariant title_value = excel.property("Caption");  //获取标题
		qDebug() << QString("excel title : ") << title_value;
		QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
		QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

		int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
		qDebug() << QString("sheet count : ") << sheet_count;
		QStringList lstWorkSheets;
		for ( i = 1; i <= sheet_count; i++)
		{
			QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);  //Sheets(int)也可换用Worksheets(int)
			QString work_sheet_name = work_sheet->property("Name").toString();  //获取工作表名称
			QString message = QString("sheet ") + QString::number(i, 10) + QString(" name");
			qDebug() << message << work_sheet_name;
			lstWorkSheets.append(work_sheet_name);
		}
		bool bok;
		QString getname = QInputDialog::getItem(this, "选择表", "表", lstWorkSheets ,0,true,&bok	);
		if (!bok)
		{
			work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
			excel.dynamicCall("Quit(void)");  //退出
			return;
		}


		//lint
		//QDialog dlgset(this);
		//Ui_LDLgChangeExcelTops uidlgset;
		//uidlgset.setupUi(&dlgset);
		//if (dlgset.exec()!=QDialog::Accepted)
		//{
		//	work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
		//	excel.dynamicCall("Quit(void)");  //退出
		//	return;
		//}
		//posTops.setX(uidlgset.m_pEdtFirstTopRow->text().toInt());
		//posTops.setY(uidlgset.m_pEdtFirstTopCol->text().toInt());
		//posWell.setX(uidlgset.m_pEdtFirstWellRow->text().toInt());
		//posWell.setY(uidlgset.m_pEdtFirstWellCol->text().toInt());

		sheet_count = lstWorkSheets.indexOf(getname)+1;

		if (sheet_count > 0)
		{
			QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", sheet_count);
			QAxObject *used_range = work_sheet->querySubObject("UsedRange");
			QAxObject *rows = used_range->querySubObject("Rows");
			QAxObject *columns = used_range->querySubObject("Columns");
			int row_start = used_range->property("Row").toInt();  //获取起始行   
			int column_start = used_range->property("Column").toInt();  //获取起始列
			int row_count = rows->property("Count").toInt();  //获取行数
			int column_count = columns->property("Count").toInt();  //获取列数

			QMap<QString, int> mapTops;//层名，位置
			//获取层名
			i = posTops.x();
			for (j = posTops.y(); j <= column_count; j++)
			{
				QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
				if (!cell)
				{
					continue;
				}
				QVariant cell_value = cell->property("Value");  //获取单元格内容
				QString strTop =  cell_value.toString();
				if (strTop.isEmpty())
				{
					continue;
				}
				if (mapTops.contains(strTop)==false)
				{
					qDebug() << strTop;
					mapTops[strTop] = j;
				}
			}

			//读取数据
			for ( i = posWell.x();i<row_count; i++)
			{
				QString strWell;
				//首先读取井名，不存在则下一行
				{
					QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, posWell.y());
					if (!cell)
					{
						continue;
					}
					QVariant cell_value = cell->property("Value");  //获取单元格内容
					item0.strWell = cell_value.toString();
				}

				//读取数据

				QMap<QString, int>::const_iterator it;
				for (it = mapTops.constBegin(); it != mapTops.constEnd(); ++it) {
					qDebug() << it.key() << ":" << it.value();
					j = it.value();

					QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
					if (!cell)
					{
						continue;
					}
					bool bok;
					QVariant cell_value = cell->property("Value");  //获取单元格内容
					QString temp = cell_value.toString();
					double topdata = cell_value.toDouble(&bok);
					if (!bok)
					{
						topdata = temp.toDouble(&bok);
					}
					if (bok)
					{
						item0.strTop = it.key();
						item0.data = topdata;
						lstItem.append(item0);
						qDebug() << item0.strWell << "\t" << item0.strTop << "\t" << item0.data << "\t";
					}

				}
			}
		}
		
		work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
		excel.dynamicCall("Quit(void)");  //退出
	}





	QFile fileIn(strFileIn);
	if (fileIn.open(QFile::ReadOnly)==false)
	{
		QMessageBox::warning(this, "error", "read file failed");
		return;
	}
	QFile fileOut(strFileIn + ".out");
	if (!fileOut.open(QFile::WriteOnly))
	{
		QMessageBox::warning(this, "error", "write file failed");
		return;
	}

	QTextStream ts(&fileOut);
 	for (int i = 0; i < lstItem.count(); i++)
 	{
 		ts << lstItem[i].strWell << "\t"
 			<< lstItem[i].strTop << "\t"
 			<< lstItem[i].data << "\n";
 	}
	fileOut.close();
}




void changeSigleAngle(QString strFileName)
{
	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly))
	{
		return;
	}
	QFile fileOut(strFileName + ".out");
	if (!fileOut.open(QFile::WriteOnly))
	{
		return;
	}
	QList<double> dataMd;
	QList<double> dataDX;
	QList<double> dataDY;
	int dataLine = 0;
	while (!file.atEnd())
	{
		QString strLine = file.readLine();
		if (strLine.contains("*"))
		{
			continue;
		}
		strLine = strLine.simplified();
		QStringList strData = strLine.split(" ");
		if (strData.count()<5)
		{
			continue;
		}
		dataMd.append(strData[0].toDouble());
		dataDX.append(strData[2].toDouble());
		dataDY.append(strData[3].toDouble());
		dataLine++;
	}
	file.close();


	QTextStream ts(&fileOut);
	ts << "md \t dx \t dy \t dip \t azi \n";
	int i;
	double predx = 0;
	double predy = 0;
	double premd = 0;
	double ri, mapr,dx,dy;
	double* dataDip = new double[dataLine];//倾角
	double* dataAzi = new double[dataLine];//方位角
	for ( i = 0; i < dataLine; i++)
	{
		mapr = sqrt((dataDX[i] - predx)*(dataDX[i] - predx) +
			(dataDY[i] - predy)*(dataDY[i] - predy));
		ri = dataMd[i] - premd;
		dx = dataDX[i] - predx;
		dy = dataDY[i] - predy;
		if (mapr == 0)
		{
			dataDip[i] = 0;
			dataAzi[i] = 0;
		}
		else{
			dataDip[i] = asin( MIN(1,mapr / ri)) * 180. / PI;
			if (dx ==0)//y轴
			{
				if (dy>=0)
				{
					dataAzi[i] = 0;
				}
				else{
					dataAzi[i] = 180;
				}
			}
			else if (dy ==0)//x轴
			{
				if (dx >= 0)
				{
					dataAzi[i] = 90;
				}
				else{
					dataAzi[i] = 270;
				}
			}
			else
			{
				dataAzi[i] = atan( fabs(dx / dy)) * 180. / PI;
				 if (dx > 0 && dy < 0)//4
				{
					dataAzi[i] = 180 - dataAzi[i];
				}
				else if (dx < 0 && dy < 0)//3
				{
					dataAzi[i] = 180 + dataAzi[i];
				}
				else if (dx > 0 && dy < 0)//2
				{
					dataAzi[i] = 360 - dataAzi[i];
				}
			}

		}
		premd = dataMd[i];
		predx = dataDX[i];
		predy = dataDY[i];
	}

	for (i = 0; i < dataLine; i++)
	{
		ts << dataMd[i] << "\t"
			<< dataDX[i] << "\t"
			<< dataDY[i] << "\t"
			<< dataDip[i] << "\t"
			<< dataAzi[i] << "\n";
	}
	delete[]dataDip;
	delete[]dataAzi;
	fileOut.close();
}


void linapplication::slotOnChangeDXDY2Angle()
{
	QStringList lstfile = QFileDialog::getOpenFileNames(this, "", "");
	for (int i = 0; i < lstfile.count();i++)
	{
		changeSigleAngle(lstfile[i]);
	}

}

struct CLineCmpTimeValue
{
	double Line;
	double Cmp;
	double Time;
	double Value;
};
void ChangeGss2InlineXlineTimeValue(QString strFileName)
{
	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly))
	{
		return;
	}
	QFile fileOut(strFileName + ".out");
	if (!fileOut.open(QFile::WriteOnly))
	{
		return;
	}

	QList<CLineCmpTimeValue> lstDatas;
	int dataLine = 0;

		//: DBAVI      VN01, VTYPE : VRMS,
		//	LINE200,
		//	CMP300, X0, Y0, DACT0,
		//	T16V2090, T317V2377, T507V2553,
		//	T641V2677, T849V2770, T1055V2883,
		//	T1261V3017, T1501V3167, T1628V3220,
		//	T1909V3310, T2111V3340, T2311V3563,
		//	T2529V3817, T3039V4453, T3497V4927,
		//	T4279V5513, T5934V6523,
		//	VF6500,
		//	CMP310, X0, Y0, DACT0,
		//	T16V2108, T317V2418, T507V2595,
		//	T641V2713, T849V2798, T1055V2892,
		//	T1261V3012, T1501V3172, T1628V3220,
		//	T1909V3308, T2111V3346, T2311V3535,
		//	T2529V3804, T3039V4453, T3497V4927,
		//	T4279V5517, T5934V6516,
		//	VF6500,

	CLineCmpTimeValue data0;
	QString strLine = file.readAll();
	char t = 32;
	strLine = strLine.simplified().remove(t);
	file.close();
	QStringList lstAllRead= strLine.simplified().split(",");
	int i;
	for ( i = 0; i < lstAllRead.count(); i++)
	{
		QString strLine = lstAllRead[i].toLower();

		QString sss = strLine.left(1);
		if (strLine.contains("line"))
		{
			data0.Line = strLine.remove("line").toDouble();
		}
		else if (strLine.contains("cmp"))
		{
			data0.Cmp = strLine.remove("cmp").toDouble();
		}
		else if (strLine.left(1) == "t" && strLine.contains("v"))
		{
			QStringList lst = strLine.remove("t").split("v");

			data0.Time = lst[0].toDouble();
			data0.Value = lst[1].toDouble();
			lstDatas.append(data0);
		}
	}


	QTextStream ts(&fileOut);
	ts << "line \t cmp \t time \t value\n";
	for (i = 0; i < lstDatas.count(); i++)
	{
		ts << QString::number(lstDatas[i].Line) << "\t"
			<< QString::number(lstDatas[i].Cmp) << "\t" 
			<< QString::number(lstDatas[i].Time) << "\t"
			<< QString::number(lstDatas[i].Value) << "\t"
			<<"\n"
			;
	}

	fileOut.close();
}
void linapplication::slotOnChangeGss2InlineXlineTimeValue()//转换gss文件为InlineCmpTimeValue
{
	QStringList lstfile = QFileDialog::getOpenFileNames(this, "", "");
	for (int i = 0; i < lstfile.count();i++)
	{
		ChangeGss2InlineXlineTimeValue(lstfile[i]);
	}

}
struct CWellbyUwi
{
	QString name;
	QStringList lsttext;
};

void tiqu(QString strFileName)
{
	QFile file(strFileName);
	if (!file.open(QFile::ReadOnly))
	{
		return;
	}
	QList<double> dataMd;
	QList<double> dataDX;
	QList<double> dataDY;
	int dataLine = 0;

	QList<CWellbyUwi> lstWells;
	CWellbyUwi well0;
	while (!file.atEnd())
	{
		QString strLine = file.readLine();
		if (strLine.contains("LOG1",Qt::CaseInsensitive))
		{
			if (well0.lsttext.count()>0)
			{
				lstWells.append(well0);
			}
			well0.lsttext.clear();
			QStringList lst = strLine.split("UWI:");
			if (lst.count()>1)
			{
				QString strName = lst[1].simplified();
				lst = strName.split(" ");
				well0.name = lst.first();
			}
		}
		else if (strLine.contains("LOG5", Qt::CaseInsensitive))
		{
			strLine.replace("LOG5", "");
			strLine.replace("\n", "");
			well0.lsttext.append(strLine);
		}
	}
	if (well0.lsttext.count()>0)
	{
		lstWells.append(well0);
	}
	file.close();

	QFileInfo fi(strFileName);

	QDir dir(fi.absoluteDir());
	dir.mkdir("output");
	dir.cd("output");
	for (int i = 0; i < lstWells.count(); i++)
	{
		QString strFilename0 = dir.absolutePath()+"/" + lstWells[i].name + ".dat";
		QFile fileOut(strFilename0);
		if (!fileOut.open(QFile::WriteOnly))
		{
			return;
		}
		QTextStream ts(&fileOut);
		ts << "Measr. Depth    TVD Depth            Log Value \n";
		for (int j = 0; j < lstWells[i].lsttext.count(); j++)
		{
			ts << lstWells[i].lsttext[j]+"\n";
		}
		fileOut.close();
	}

}

void linapplication::slotTiqu()
{
	QStringList lstfile = QFileDialog::getOpenFileNames(this, "", "");
	for (int i = 0; i < lstfile.count();i++)
	{
		tiqu(lstfile[i]);
	}

	QMessageBox::warning(NULL, "", "ok");

}