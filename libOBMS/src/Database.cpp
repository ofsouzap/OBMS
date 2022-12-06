#include "Database.h"

using namespace OBMS;

using std::find;
using std::find_if;
using std::to_string;
using std::endl;

Database::Database()
{

	//Initialise tables vector
	tables = vector<Table*>();

}

Database::~Database()
{

	// Delete tables referenced by the database
	for (int i = 0; i < tables.size(); i++)
	{
		delete tables[i];
	}

}

Table* Database::findTableByName(string name) const
{

	auto res = find_if(
		tables.begin(),
		tables.end(),
		[name](Table* t) {return t->getName() == name; }
	);

	if (res != tables.end())
		return *res;
	else
		return nullptr;

}

bool Database::checkTableNameExists(string name) const
{
	return findTableByName(name) != nullptr;
}

bool Database::checkTableNameExists(Table* table) const
{
	return checkTableNameExists(table->getName());
}

void Database::addTable(Table* table)
{
	tables.push_back(table);
}

void Database::deleteTable(Table* table)
{

	auto res = find(tables.begin(), tables.end(), table);

	if (res == tables.end())
	{
		throw new TableDoesNotExistException();
	}
	else
	{
		tables.erase(res);
	}

}

void Database::create(string name, TableStructure* structure)
{

	if (checkTableNameExists(name))
		throw new TableNameAlreadyExistsException(name);

	Table* newTable = new Table(name, structure);

	addTable(newTable);

}

void Database::drop(string tableName)
{

	if (!checkTableNameExists(tableName))
		throw new TableNameDoesNotExistException(tableName);

	deleteTable(findTableByName(tableName));

}

Table* Database::crossJoin(string tableNameA, string tableNameB, string fieldA, string fieldB) const
{

	// Get tables (and check existance)

	Table* tableA = findTableByName(tableNameA);

	if (tableA == nullptr)
		throw new TableNameDoesNotExistException(tableNameA);

	Table* tableB = findTableByName(tableNameB);

	if (tableB == nullptr)
		throw new TableNameDoesNotExistException(tableNameB);

	// Pass on joining to Table::crossJoin

	return Table::crossJoin(tableA, tableB, fieldA, fieldB);

}

void Database::printTable(Table* table, ostream& os)
{

	// Preparation

	vector<Record*> records = table->viewRecords();

	int fieldCount = table->getFieldCount();
	int recordCount = records.size();

	// Find required widths of columns

	int* columnSizes = new int[fieldCount];

	// Initialise column sizes
	for (int i = 0; i < fieldCount; i++)
		columnSizes[i] = 1;

	// Go through record names to check column sizes
	for (int columnIndex = 0; columnIndex < fieldCount; columnIndex++)
	{

		string s = table->getFieldName(columnIndex);
		int size = s.size();

		if (size > columnSizes[columnIndex])
		{
			columnSizes[columnIndex] = size;
		}

	}

	// Go through records to check column sizes
	for (Record* record : records)
	{

		for (int columnIndex = 0; columnIndex < fieldCount; columnIndex++)
		{

			//TODO - once different data types introduced, this will need to be implemented differently
			TableField::dataType v = record->get(columnIndex);
			string s = to_string(v);
			int size = s.size();

			if (size > columnSizes[columnIndex])
			{
				columnSizes[columnIndex] = size;
			}

		}

	}

	// Produce output in pretty table

	// Header line

	for (int columnIndex = 0; columnIndex < fieldCount; columnIndex++)
	{

		string columnName = table->getFieldName(columnIndex);
		int columnNameSize = columnName.size();

		os << columnName;

		// Add spaces until column end
		for (int j = columnNameSize; j < columnSizes[columnIndex] - 1; j++) // "-1" is for padding at start
			os << ' ';

		if (columnIndex < fieldCount - 1)
			os << '|';

	}

	os << endl;

	// Separator
	
	for (int columnIndex = 0; columnIndex < fieldCount; columnIndex++)
	{

		for (int j = 0; j < columnSizes[columnIndex]; j++)
			os << '-';

		if (columnIndex < fieldCount - 1)
			os << '+';

	}

	os << endl;

	// Records

	for (int recordIndex = 0; recordIndex < recordCount; recordIndex++)
	{

		for (int columnIndex = 0; columnIndex < fieldCount; columnIndex++)
		{

			string valueString = to_string(records[recordIndex]->get(columnIndex));
			int valueStringSize = valueString.size();

			os << valueString;

			// Add spaces until column end
			for (int spaceIndex = valueStringSize; spaceIndex < columnSizes[columnIndex]; spaceIndex++)
				os << ' ';

			if (columnIndex < fieldCount - 1)
				os << '|';

		}

		os << endl;

	}

}
