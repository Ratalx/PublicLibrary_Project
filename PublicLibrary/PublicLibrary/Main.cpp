#include"MenuFunctions.h"
using namespace publicLibrary;
int main()
{
	const std::string BookFileName = "Book_Register.csv";
	const std::string StudentFileName = "Student_Register.csv";
	while (MenuFunctions::MainMenu(BookFileName,StudentFileName));
	return EXIT_SUCCESS;
}
