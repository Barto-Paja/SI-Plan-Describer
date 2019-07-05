#ifndef DOCUMENTPARSER_HPP
#define DOCUMENTPARSER_HPP

#include <QObject>

#include <QDate>

struct documentCoreSave
{
    QDate dateStart;
    QDate dateEnd;

    QString studentName;
    QString therapistName;

    QList<QString> targets;
};

class DocumentParser : public QObject
{
    Q_OBJECT
public:
    explicit DocumentParser(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DOCUMENTPARSER_HPP
