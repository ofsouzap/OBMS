#include "TableStructure.h"

using namespace OBMS;

TableStructure::TableStructure()
{
	fields = vector<TableField*>();
}

TableStructure::~TableStructure()
{
}

void TableStructure::addField(TableField* field)
{
	fields.push_back(field);
}

int TableStructure::getFieldCount() const
{
	return fields.size();
}

TableStructure* TableStructure::build(vector<TableField*> fields)
{

	TableStructure* s = new TableStructure();

	for (TableField* field : fields)
	{
		s->addField(field);
	}

	return s;

}

int TableStructure::calcTotalByteSize() const
{

	int size = 0;

	for (TableField* field : fields)
	{
		size += field->getDataSize();
	}

	return size;

}

int TableStructure::getFieldIndex(string name) const
{

	for (int i = 0; i < fields.size(); i++)
	{
		if (fields[i]->getFieldName() == name)
			return i;
	}

	throw new TableFieldDoesNotExistException(name);

}

bool TableStructure::hasFieldOfName(string name) const
{

	// This does use the exceptions as the main control flow but since...
	//     ...I'm using a custom type of exception I think its fine

	try
	{
		getFieldIndex(name);
		return true;
	}
	catch (TableFieldDoesNotExistException)
	{
		return false;
	}

}

string TableStructure::getFieldName(int index) const
{
	
	if (index < 0 || index >= fields.size())

		throw new FieldIndexOutOfRangeException();

	else
		return fields[index]->getFieldName();

}

vector<string>* TableStructure::getFieldNames() const
{

	vector<string>* out = new vector<string>();

	for (TableField* field : fields)
		out->push_back(field->getFieldName());

	return out;

}
