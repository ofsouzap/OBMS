#pragma once

#include <exception>
#include <string>

using std::exception;
using std::string;

class TableFieldDoesNotExistException : public exception
{

private:

	string fieldName;

public:

	TableFieldDoesNotExistException(string fieldName);
	string getFieldName();

};

class TableNameAlreadyExistsException : public exception
{

private:

	string tableName;

public:

	TableNameAlreadyExistsException(string tableName);

	string getTableName();

};

class TableNameDoesNotExistException : public exception
{

private:

	string tableName;

public:

	TableNameDoesNotExistException(string tableName);

	string getTableName();

};

class TableDoesNotExistException : public exception {};

class IncompatibleRecordException : public exception {};

class FieldIndexOutOfRangeException : public exception {};
