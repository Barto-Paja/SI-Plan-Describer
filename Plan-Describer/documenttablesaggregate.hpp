#ifndef DOCUMENTTABLESAGGREGATE_HPP
#define DOCUMENTTABLESAGGREGATE_HPP

#include <QObject>

class DocumentTablesAggregate : public QObject
{
    Q_OBJECT
public:
    explicit DocumentTablesAggregate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DOCUMENTTABLESAGGREGATE_HPP
