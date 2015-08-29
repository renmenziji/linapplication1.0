#pragma once
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
class LIOObject
{
public:
	LIOObject();
	~LIOObject();

	virtual bool Save(QString fn);
	virtual bool Load(QString fn);
	virtual bool WriteJson(QJsonObject &ob);
	virtual bool ReadJson(QJsonObject &ob);

protected:
	QString m_filename;
};

