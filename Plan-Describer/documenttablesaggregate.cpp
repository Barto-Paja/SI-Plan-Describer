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
            _variants.append(target());
            _variants.last().name = query->value("name").toString();
            _variants.last().isUsing = query->value("is_used").toBool();
            _variants.last().id = query->value("id").toInt();
        }
    }
    else
    {
        qDebug() << query->lastError().text() << query->executedQuery() << query->lastError();
        return false;
    }

    for(int i = 0; i < _variants.count(); ++i)
    {
        query->prepare("SELECT * FROM methods WHERE target_id = :targetID");
        query->bindValue(":targetID",(i+1));
        if(query->exec())
        {
            while(query->next())
            {
                _variants[i].methods.append(method());
                _variants[i].methods.last().name = query->value("text").toString();
                _variants[i].methods.last().isUsing = query->value("is_used").toInt();
                _variants[i].methods.last().id = query->value("id").toInt();
            }
        }
    }

    return true;
}

QList<target> DocumentTablesAggregate::variants() const
{
    return _variants;
}

int DocumentTablesAggregate::insertNewTarget(QString value)
{
    QSqlQuery *query = new QSqlQuery(_db);
    _db.transaction();
    query->prepare("INSERT INTO target (name) VALUES (:target_name)");
    query->bindValue(":target_name",value);

    if(query->exec())
    {
        auto rowid = query->lastInsertId();
        query->prepare("SELECT ID FROM target WHERE rowid = :row_id");
        query->bindValue(":row_id",rowid);

        if(query->exec())
        {
            if(query->next())
            {
                _db.commit();
                return query->value("ID").toInt();
            }
            else
            {
                _db.rollback();
                return (-1);
            }
        }
        else
        {
            _db.rollback();
            return (-1);
        }

    }
    else
    {
        _db.rollback();
        return (-1);
    }
}

bool DocumentTablesAggregate::updateTargetStatus(QString name, bool status)
{
    int _status {0};

    if(status)
    {
        _status = 1;
    }
    else {
        _status = 0;
    }

    QSqlQuery *query = new QSqlQuery(_db);
    query->prepare("UPDATE target SET is_used = :is_used_status WHERE name = :target_name");
    query->bindValue(":is_used_status",_status);
    query->bindValue(":target_name",name);

    return query->exec();
}

bool DocumentTablesAggregate::updateTargetName(QString old_value, QString new_value)
{
    QSqlQuery *query = new QSqlQuery(_db);
    query->prepare("UPDATE target SET name = :new_name WHERE name = :target_name");
    query->bindValue(":new_name",new_value);
    query->bindValue(":target_name",old_value);

    return query->exec();
}

bool DocumentTablesAggregate::insertNewMethod(QString text, int index_target)
{
    QSqlQuery *query = new QSqlQuery(_db);
    query->prepare("INSERT INTO methods (text, target_id) VALUES (:text_value, :target_id_value)");
    query->bindValue(":text_value",text);
    query->bindValue(":target_id_value",index_target);

    return query->exec();
}

bool DocumentTablesAggregate::removeMethod(int index)
{
    QSqlQuery *query = new QSqlQuery(_db);
    query->prepare("DELETE FROM methods WHERE id = :id_v");
    query->bindValue(":id_v",index);
    return query->exec();
}
