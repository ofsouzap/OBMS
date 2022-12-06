#pragma once

#include <string>

using std::string;

namespace OBMS
{
	class TableField
	{

	private:

		string fieldName;

	public:

		typedef int dataType; // TODO: implement being able to use other data types (not just ints)

		TableField(string fieldName);
		~TableField();

		string getFieldName() const;

		int getDataSize() const;

	};
}