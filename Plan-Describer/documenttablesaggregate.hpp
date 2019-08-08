#ifndef DOCUMENTTABLESAGGREGATE_HPP
#define DOCUMENTTABLESAGGREGATE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDir>

#include <QSqlError>
#include <QDebug>

struct method
{
    int id;
    QString name;
    bool isUsing;
};

struct target
{
    int id;
    QString name;
    bool isUsing;
    QList<method> methods;
};

class DocumentTablesAggregate : public QObject
{
    Q_OBJECT
public:
    explicit DocumentTablesAggregate(QString db_file_name, QObject *parent = nullptr);
    ~DocumentTablesAggregate();
    bool loadData();
    QList<target> variants() const;

    int insertNewTarget(QString value);
    bool updateTargetStatus(QString name, bool status);
    bool updateTargetName(QString old_value, QString new_value);

    bool insertNewMethod(QString text, int index_target);
    bool updateMethodText(QString old_value, QString new_text, int index);
    bool removeMethod(int index);

signals:

public slots:

private:

    bool openDataBase();
    bool prepareValues();

    QSqlDatabase _db;
    QDir _databasePath = QDir::currentPath();

    QList<target> _variants;
};

#endif // DOCUMENTTABLESAGGREGATE_HPP
