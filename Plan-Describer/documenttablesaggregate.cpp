#include "documenttablesaggregate.hpp"

DocumentTablesAggregate::DocumentTablesAggregate(QString db_file_name, QObject *parent) : QObject(parent)
{
    _databasePath = QDir::currentPath()+"/"+db_file_name;
    _db = QSqlDatabase::addDatabase("QSQLITE",_databasePath.path());
}

DocumentTablesAggregate::~DocumentTablesAggregate()
{
    _db.close();
    _variants.clear();
}

bool DocumentTablesAggregate::loadData()
{
    qDebug() << _databasePath.path();

    if(openDataBase())
    {
        return prepareValues();
    }
    else {
        return false;
    }
}

bool DocumentTablesAggregate::openDataBase()
{
    _db.setDatabaseName(_databasePath.path());

    if(_db.open())
    {
        return true;
    }

    return false;
}

bool DocumentTablesAggregate::prepareValues()
{
    QSqlQuery *query = new QSqlQuery(_db);
    query->prepare("SELECT * FROM target");

    if(query->exec("SELECT * FROM target"))
    {
        while(query->next())
        {
            _variants.append(targetVariant());
            _variants.last().name = query->value("name").toString();
            _variants.last().isUsing = query->value("is_used").toBool();

        }
    }
    else
    {
        qDebug() << query->lastError().text() << query->executedQuery() << query->lastError();
        return false;
    }

    for(int i = 0; i < _variants.count(); ++i)
    {
        query->prepare("SELECT text FROM methods WHERE target_id = :targetID");
        query->bindValue(":targetID",(i+1));
        if(query->exec())
        {
            while(query->next())
            {
                _variants[i].variants.append(query->value("text").toString());
            }
        }
    }

    return true;
}

QList<targetVariant> DocumentTablesAggregate::variants() const
{
    return _variants;
}
