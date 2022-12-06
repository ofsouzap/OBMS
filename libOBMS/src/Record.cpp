#include "Record.h"

using namespace OBMS;

Record::Record(int valueCount) : valueCount(valueCount)
{
	values = new TableField::dataType[valueCount];
}

Record::~Record()
{

	delete[] values;

}

bool Record::checkIndex(int i) const
{
	return (i >= i) && (i < valueCount);
}

int Record::getValueCount() const
{
	return valueCount;
}

TableField::dataType Record::get(int i) const
{

	if (!checkIndex(i))
		throw new FieldIndexOutOfRangeException();

	return values[i];

}

void Record::set(int i, TableField::dataType v)
{

	if (!checkIndex(i))
		throw new FieldIndexOutOfRangeException();

	values[i] = v;

}

Record* Record::build(vector<TableField::dataType> values)
{

	Record* r = new Record(values.size());

	for (int i = 0; i < values.size(); i++)
	{
		r->set(i, values[i]);
	}

	return r;

}
