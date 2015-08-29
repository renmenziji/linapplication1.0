#include "linapplication.h"

linapplication::linapplication(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.action_basename, SIGNAL(active()), this, SLOT(slotOnBasename()));
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