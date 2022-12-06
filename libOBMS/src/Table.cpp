#include "Table.h"

using namespace OBMS;

Table::Table(string name, TableStructure* structure) : name(name), structure(structure)
{

	records = vector<Record*>();

}

Table::~Table()
{

	for (Record* record : records)
	{
		delete record;
	}

}

bool Table::recordIsCompatible(Record* record) const
{

	// TODO - once other data types allowed, change this method

	return record->getValueCount() == getFieldCount();

}

const vector<Record*>& Table::viewRecords() const
{
	return records;
}

string Table::getName() const
{
	return name;
}

string Table::getFieldName(int index) const
{
	return getStructure()->getFieldName(index);
}

int Table::getFieldCount() const
{
	return getStructure()->getFieldCount();
}

TableStructure* Table::getStructure() const
{
	return structure;
}

void Table::addRecord(Record* record)
{

	if (!recordIsCompatible(record))
		throw new IncompatibleRecordException();

	records.push_back(record);

}

void Table::insert(vector<TableField::dataType> row)
{

	Record* record = Record::build(row);
	addRecord(record);

}

int Table::getFieldIndex(string fieldName) const
{
	return getStructure()->getFieldIndex(fieldName);
}

bool Table::hasFieldOfName(string name) const
{
	return getStructure()->hasFieldOfName(name);
}

vector<Record*>* Table::getRecordsWhere(string fieldName, TableField::dataType value) const
{

	if (!hasFieldOfName(fieldName))
		throw new TableFieldDoesNotExistException(fieldName);

	int fieldIndex = getFieldIndex(fieldName);

	vector<Record*>* out = new vector<Record*>();

	//TODO - once indexes made, if field has an index, try to use it to speed up the query

	for (Record* record : records)
	{

		if (record->get(fieldIndex) == value)
			out->push_back(record);

	}

	return out;

}

Record* Table::crossJoinMergeRecord(const Record* recordA, const Record* recordB)
{

	int aCount = recordA->getValueCount();
	int bCount = recordB->getValueCount();

	Record* out = new Record(aCount + bCount);

	for (int i = 0; i < aCount; i++)
	{
		out->set(i, recordA->get(i));
	}

	for (int j = 0; j < bCount; j++)
	{
		out->set(aCount + j, recordB->get(j));
	}

	return out;

}

Table* Table::crossJoin(const Table* tableA, const Table* tableB, string fieldA, string fieldB, string outTableName)
{

	// Records from tableA will be related to as A-records
	// Likewise for tableB -> B-records
	// Records being added to the output (formed from joining the A- and B-records) will be related to as out-records

	// Get field indexes (exceptions thrown if don't exist)

	int fieldIndexA = tableA->getFieldIndex(fieldA);
	int fieldIndexB = tableB->getFieldIndex(fieldB);

	// Prepare output table values list

	vector<Record*> outRecords = vector<Record*>();

	// Prepare output table structure

	vector<TableField*> outTableFields = vector<TableField*>();
	
	// Add tableA field names (with "{tableA.name}.")
	vector<string>* fieldNamesA = tableA->getStructure()->getFieldNames();
	for (string aFieldName : *fieldNamesA)
	{
		string fieldName = tableA->getName() + '.' + aFieldName;
		TableField* field = new TableField(fieldName);
		outTableFields.push_back(field);
	}
	delete fieldNamesA;

	// Add tableB field names (with "{tableB.name}.")
	vector<string>* fieldNamesB = tableB->getStructure()->getFieldNames();
	for (string bFieldName : *fieldNamesB)
	{
		string fieldName = tableB->getName() + '.' + bFieldName;
		TableField* field = new TableField(fieldName);
		outTableFields.push_back(field);
	}
	delete fieldNamesB;

	TableStructure* outTableStructure = TableStructure::build(outTableFields);

	// Iterate through tableA A-records

	for (Record* recordA : tableA->records)
	{

		// Get compared value
		TableField::dataType targetValue = recordA->get(fieldIndexA);

		// Find matching B-records
		vector<Record*>* matches = tableB->getRecordsWhere(fieldB, targetValue);

		// Merge matching records with A-record

		for (Record* recordB : *matches)
		{

			Record* newRecord = crossJoinMergeRecord(recordA, recordB);
			outRecords.push_back(newRecord);

		}

		delete matches;

	}

	// Create output table and add records

	Table* outTable = new Table(outTableName, outTableStructure);

	for (Record* record : outRecords)
	{
		outTable->addRecord(record);
	}

	// Return output table

	return outTable;

}
