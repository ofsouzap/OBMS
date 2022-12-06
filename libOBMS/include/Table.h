#pragma once

#include <string>
#include <vector>

#include "exceptions.h"
#include "TableStructure.h"
#include "Record.h"

using std::string;
using std::vector;
using std::exception;

namespace OBMS
{

	class Table
	{

	private:

		string name;
		TableStructure* structure;

		vector<Record*> records;

		TableStructure* getStructure() const;

		bool recordIsCompatible(Record* record) const;

		void addRecord(Record* record);

		int getFieldIndex(string fieldName) const;

		/// <summary>
		/// Concatenates records together for a cross join
		/// </summary>
		static Record* crossJoinMergeRecord(const Record* recordA, const Record* recordB);

	public:

		// TODO - need to find a way for Table to have its own copy of its TableStructure so it can't be edited or deleted externally
		Table(string name, TableStructure* structure);
		~Table();

		string getName() const;
		string getFieldName(int index) const;

		const vector<Record*>& viewRecords() const;

		int getFieldCount() const;

		void insert(vector<TableField::dataType> row);

		/// <summary>
		/// Returns the records that match a certain condition
		/// </summary>
		vector<Record*>* getRecordsWhere(string fieldName, TableField::dataType value) const;
		//TODO - allow for proper where conditions, not just field value equality

		/// <summary>
		/// Checks if the Table has a record with the specified name in it
		/// </summary>
		bool hasFieldOfName(string name) const;

		/// <summary>
		/// Performs a join by comparing two fields in this table and another
		/// </summary>
		/// <param name="tableA">The first table</param>
		/// <param name="tableB">The second table</param>
		/// <param name="fieldA">The name of the field to look at in the first table</param>
		/// <param name="fieldB">The name of the field to look at in the second table</param>
		/// <param name="outTableName">The name to give to the outputted table (default "")</param>
		/// <returns>A newly-created table with the result of the join</returns>
		static Table* crossJoin(const Table* tableA, const Table* tableB, string fieldA, string fieldB, string outTableName = "");
		//TODO - allow cross join to have proper conditions no just compare field equality

		//TODO - when adding a field, must extend size of each record

	};

}