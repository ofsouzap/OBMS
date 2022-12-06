add_executable (SchoolExample "main.cpp")

target_link_libraries (SchoolExample PUBLIC libOBMS)
target_include_directories (SchoolExample PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/libOBMS/include"
)
