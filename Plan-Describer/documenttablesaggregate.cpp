#include "documenttablesaggregate.hpp"

DocumentTablesAggregate::DocumentTablesAggregate(QString db_file_name, QObject *parent) : QObject(parent)
{
    _databasePath = QDir::currentPath()+"/"+db_file_name;
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
