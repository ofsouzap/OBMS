#include <vector>
#include <exception>
#include <iostream>

#include "Database.h"
#include "TableStructure.h"
#include "TableField.h"

using namespace OBMS;

using std::vector;
using std::exception;
using std::cin;
using std::cout;
using std::endl;

Table* doStudentsJoinTeachers(Database* db)
{
	return db->crossJoin("students", "teachers", "tid", "tid");
}

int main()
{

	// Design students table structure

	vector<TableField*> studentTableFields = vector<TableField*>();
	studentTableFields.push_back(new TableField("sid"));
	studentTableFields.push_back(new TableField("age"));
	studentTableFields.push_back(new TableField("examScore"));
	studentTableFields.push_back(new TableField("tid"));

	TableStructure* studentsTableStructure = TableStructure::build(studentTableFields);

	// Design teachers table structure

	vector<TableField*> teachersTableFields = vector<TableField*>();
	teachersTableFields.push_back(new TableField("tid"));
	teachersTableFields.push_back(new TableField("age"));

	TableStructure* teachersTableStructure = TableStructure::build(teachersTableFields);

	// Create database

	Database* db = new Database();
	db->create("students", studentsTableStructure);
	db->create("teachers", teachersTableStructure);

	// Insert students data

	Table* studentsTable = db->findTableByName("students");
	if (studentsTable == nullptr) throw new exception("Couldn't find students table");

	vector<TableField::dataType> studentData0 = vector<TableField::dataType>();
	studentData0.push_back(0);
	studentData0.push_back(14);
	studentData0.push_back(100);
	studentData0.push_back(0);
	studentsTable->insert(studentData0);

	vector<TableField::dataType> studentData1 = vector<TableField::dataType>();
	studentData1.push_back(1);
	studentData1.push_back(15);
	studentData1.push_back(46);
	studentData1.push_back(1);
	studentsTable->insert(studentData1);

	vector<TableField::dataType> studentData2 = vector<TableField::dataType>();
	studentData2.push_back(2);
	studentData2.push_back(14);
	studentData2.push_back(12);
	studentData2.push_back(1);
	studentsTable->insert(studentData2);

	// Insert teachers data

	Table* teachersTable = db->findTableByName("teachers");
	if (teachersTable == nullptr) throw new exception("Couldn't find teachers table");

	vector<TableField::dataType> teacherData0 = vector<TableField::dataType>();
	teacherData0.push_back(0);
	teacherData0.push_back(39);
	teachersTable->insert(teacherData0);

	vector<TableField::dataType> teacherData1 = vector<TableField::dataType>();
	teacherData1.push_back(1);
	teacherData1.push_back(54);
	teachersTable->insert(teacherData1);

	// Run queries

	Table* studentsJoinTeachers = doStudentsJoinTeachers(db);
	cout << "Joining students with teachers:" << endl;
	db->printTable(studentsJoinTeachers, cout);

	// Clean resources

	delete db;

	// Return code

	return 0;

}
