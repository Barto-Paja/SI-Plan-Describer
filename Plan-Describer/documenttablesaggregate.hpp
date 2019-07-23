#ifndef DOCUMENTTABLESAGGREGATE_HPP
#define DOCUMENTTABLESAGGREGATE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDir>

#include <QSqlError>
#include <QDebug>

struct targetVariant
{
    QString name;
    bool isUsing;
    QList<QString> variants;
};

class DocumentTablesAggregate : public QObject
{
    Q_OBJECT
public:
    explicit DocumentTablesAggregate(QString db_file_name, QObject *parent = nullptr);
    ~DocumentTablesAggregate();
    bool loadData();
    QList<targetVariant> variants() const;

signals:

public slots:

private:

    bool openDataBase();
    bool prepareValues();

    QSqlDatabase _db;
    QDir _databasePath = QDir::currentPath();

    QList<targetVariant> _variants;
};

#endif // DOCUMENTTABLESAGGREGATE_HPP
