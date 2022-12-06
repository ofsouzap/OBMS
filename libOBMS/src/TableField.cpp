#include "TableField.h"

using namespace OBMS;

TableField::TableField(string fieldName) : fieldName(fieldName)
{
}

TableField::~TableField()
{
}

string TableField::getFieldName() const
{
	return fieldName;
}

int TableField::getDataSize() const
{
	return sizeof(dataType); // Until different data types implemented
}
