#include "User.h"
using namespace publicLibrary;
void User::save(const std::string & fileName) const
{
	{
		std::fstream usersFile;
		usersFile.open(fileName,std::ios::out | std::ios::app);
		if (usersFile)
		{
			std::string temp = "";
			temp += ";" + firstName + ";" + lastName + ";";
			usersFile << id << temp << numberOfBorrowedBooks << ";";
			temp.clear();
			for (auto i : borrowedBooks)
				temp += i;
				usersFile<<temp<< ";" << std::endl;
		}
		else
		{
			std::cout << "Error";
		}
	}
}

bool User::CanBorrow() const
{
	return(numberOfBorrowedBooks < 1);
}

int User::GetBookID() const
{

	std::string temp;
	std::stringstream ss;
		for (auto i : borrowedBooks)
		{
			ss << i;
		}
	getline(ss, temp, '_');
	int id = stoi(temp);
	return id;
}
