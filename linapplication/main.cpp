#include "linapplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	linapplication w;
	w.show();
	return a.exec();
}
