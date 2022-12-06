# CMakeList.txt : CMake project for OBMS, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (libOBMS STATIC

	"include/exceptions.h"
	"src/exceptions.cpp"

	"include/TableStructure.h"
	"src/TableStructure.cpp"

	"include/Record.h"
	"src/Record.cpp"

	"include/Table.h"
	"src/Table.cpp"

	"include/Database.h"
	"src/Database.cpp"
	
	"src/TableField.cpp"
	"include/TableField.h")

target_include_directories (libOBMS PRIVATE "include")
target_include_directories (libOBMS PRIVATE "src")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libOBMS PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
