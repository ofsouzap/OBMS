#pragma once

#include <vector>

#include "exceptions.h"
#include "TableField.h"
#include "TableStructure.h"

using std::vector;
using std::exception;

namespace OBMS
{

	class Record
	{

	private:

		int valueCount;
		TableField::dataType* values;

		bool checkIndex(int i) const;

	public:

		Record(int valueCount);
		~Record();

		static Record* build(vector<TableField::dataType> values);

		int getValueCount() const;

		TableField::dataType get(int i) const;
		void set(int i, TableField::dataType v);

	};

}