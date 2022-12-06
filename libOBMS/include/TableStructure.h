#pragma once

#include <vector>

#include "TableField.h"
#include "exceptions.h"

using std::vector;

namespace OBMS
{

	class TableStructure
	{

	private:

		vector<TableField*> fields;

	public:

		TableStructure();
		~TableStructure();

		void addField(TableField* field);

		int getFieldCount() const;

		static TableStructure* build(vector<TableField*> fields);

		int calcTotalByteSize() const;

		int getFieldIndex(string fieldName) const;

		string getFieldName(int index) const;
		vector<string>* getFieldNames() const;

		/// <summary>
		/// Checks if the TableStructure has a record with the specified name in it
		/// </summary>
		bool hasFieldOfName(string name) const;

	};

}