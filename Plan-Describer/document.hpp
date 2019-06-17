#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <QObject>

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = nullptr);

    int startYear;
    QList<QString> tableTargets;
    QList<QString> tableMethodsOfRealization;
    QString therapistName;
    QString childName;

signals:

public slots:
};

#endif // DOCUMENT_HPP
