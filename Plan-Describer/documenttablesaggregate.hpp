#ifndef DOCUMENTTABLESAGGREGATE_HPP
#define DOCUMENTTABLESAGGREGATE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>

struct targetVariant
{
    QString name;
    QList<QString> variants;
};

class DocumentTablesAggregate : public QObject
{
    Q_OBJECT
public:
    explicit DocumentTablesAggregate(QString db_file_name, QObject *parent = nullptr);

signals:

public slots:

private:

    bool openDataBase();

    QSqlDatabase _db = QSqlDatabase::addDatabase("QSQLITE");
    QDir _databasePath = QDir::currentPath();
};

#endif // DOCUMENTTABLESAGGREGATE_HPP
