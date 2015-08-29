#pragma once

#include "LIOObject.h"
#include <QJsonObject>
class LOption:public LIOObject
{
public:
	static LOption* Instance();
	~LOption();

	virtual bool WriteJson(QJsonObject &ob);
	virtual bool ReadJson(QJsonObject &ob);


private:
	LOption();
	static LOption* g_option;
};

