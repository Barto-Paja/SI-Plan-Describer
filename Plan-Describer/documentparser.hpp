#ifndef DOCUMENTPARSER_HPP
#define DOCUMENTPARSER_HPP

#include <QObject>

#include <QDate>
#include <QXmlStreamWriter>
#include <QByteArray>
#include <QFile>

struct documentCoreSave
{
    QDate dateStart;

    QString studentName;
    QString therapistName;

    QList<QString> targets;
};

class DocumentParser : public QObject
{
    Q_OBJECT
public:
    explicit DocumentParser(QObject *parent = nullptr);

    QByteArray generateXML(documentCoreSave &documentData);
    bool readXML(QFile &file, documentCoreSave &documentData);

signals:

public slots:
};

#endif // DOCUMENTPARSER_HPP
