#include "LOption.h"

LOption* LOption::g_option=NULL;
LOption::LOption()
{
}


LOption::~LOption()
{
}
bool LOption::WriteJson(QJsonObject &ob)
{
	return true;
}
bool LOption::ReadJson(QJsonObject &ob)
{
	return true;
}

LOption* LOption::Instance()
{
	if (!g_option)
	{
		g_option = new LOption();

	}
	return g_option;

}