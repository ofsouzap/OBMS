#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "exceptions.h"
#include "TableStructure.h"
#include "Table.h"

using std::vector;
using std::string;
using std::exception;
using std::istream;
using std::ostream;

namespace OBMS
{

	class Database
	{

	private:

		vector<Table*> tables;

		bool checkTableNameExists(string name) const;
		bool checkTableNameExists(Table* table) const;

		void addTable(Table* table);
		void deleteTable(Table* table);

	public:

		Database();
		~Database();

		/// <summary>
		/// Create a table using the provided table structure
		/// </summary>
		void create(string name, TableStructure* structure);

		/// <summary>
		/// Drop a table by its unique name
		/// </summary>
		void drop(string tableName);

		/// <summary>
		/// Performs a join by comparing two fields in two tables with each other
		/// </summary>
		/// <param name="tableNameA">The first table's name</param>
		/// <param name="tableNameB">The second table's name</param>
		/// <param name="fieldA">The name of the field to look at in the first table</param>
		/// <param name="fieldB">The name of the field to look at in the second table</param>
		/// <returns>A newly-created table with the result of the join</returns>
		Table* crossJoin(string tableNameA, string tableNameB, string fieldA, string fieldB) const;

		/// <summary>
		/// Returns a pointer to a table in the database's tables queried by its name or nullptr if the table doesn't exist
		/// </summary>
		Table* findTableByName(string name) const;

		/// <summary>
		/// Outputs a table pretty-printed to a stream
		/// </summary>
		static void printTable(Table* table, ostream& os = std::cout);
		
	};

}
