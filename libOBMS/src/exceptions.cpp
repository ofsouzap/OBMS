#include "exceptions.h"

TableNameAlreadyExistsException::TableNameAlreadyExistsException(string tableName) : tableName(tableName)
{
}

string TableNameAlreadyExistsException::getTableName()
{
	return tableName;
}

TableNameDoesNotExistException::TableNameDoesNotExistException(string tableName) : tableName(tableName)
{
}

string TableNameDoesNotExistException::getTableName()
{
	return tableName;
}

TableFieldDoesNotExistException::TableFieldDoesNotExistException(string fieldName) : fieldName(fieldName)
{
}

string TableFieldDoesNotExistException::getFieldName()
{
	return fieldName;
}
