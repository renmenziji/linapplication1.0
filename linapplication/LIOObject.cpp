#include "LIOObject.h"


LIOObject::LIOObject()
{
}


LIOObject::~LIOObject()
{
}

bool LIOObject::Save(QString fn)
{
	QFile file(fn);
	if (!file.open(QFile::WriteOnly))
	{
		return false;
	}
	QJsonObject jo;
	WriteJson(jo);
	QJsonDocument jd(jo);
	file.write(jd.toJson());
	file.close();
	return true;
}
bool LIOObject::Load(QString fn)
{
	QFile file(fn);
	if (!file.open(QFile::ReadOnly))
	{
		return false;
	}
	QJsonDocument jd = QJsonDocument::fromJson( file.readAll() );
	file.close();
	QJsonObject jo = jd.object();
	ReadJson(jo);
	return true;
}
bool LIOObject::WriteJson(QJsonObject &ob)
{
	return true;
}
bool LIOObject::ReadJson(QJsonObject &ob)
{
	return true;
}