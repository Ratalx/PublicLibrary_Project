#include "Student.h"
namespace publicLibrary {
	Student::Student(int id)
	{
		this->id = id;
		std::cin.ignore();
		std::cout << "First Name :";
		getline(std::cin, firstName, '\n');
		while (firstName.empty())
		{
			std::cout << "Name cant be empty" << std::endl;
			std::cout << "First Name :";
			getline(std::cin, firstName, '\n');
		}
		std::cout << "Last Name : ";
		getline(std::cin, lastName, '\n');
		while (lastName.empty())
		{
			std::cout << "Name cant be empty" << std::endl;
			std::cout << "First Name :";
			getline(std::cin, lastName, '\n');
		}
		numberOfBorrowedBooks = 0;
		borrowedBooks.clear();
		for (auto i : "None")
			borrowedBooks.push_back(i);
		borrowedBooks.resize(29);
	}

	Student::Student(const std::string &studentFromFile, int ID)
	{
		std::string tempString;
		std::stringstream streamOfStudents(studentFromFile);
		id = ID;
		getline(streamOfStudents, tempString, ';');
		getline(streamOfStudents, tempString, ';');
		firstName = tempString;
		getline(streamOfStudents, tempString, ';');
		lastName = tempString;
		getline(streamOfStudents, tempString, ';');
		numberOfBorrowedBooks = stoi(tempString);
		getline(streamOfStudents, tempString, ';');
		borrowedBooks.clear();
		for (auto i : tempString)
			borrowedBooks.push_back(i);
	}

}