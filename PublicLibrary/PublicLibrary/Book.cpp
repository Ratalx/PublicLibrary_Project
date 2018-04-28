#include "Book.h"
namespace publicLibrary {
	Book::Book(int ID)
	{
		isBorrowed = false;
		id = ID;
		std::cin.ignore();
		std::cout << "Title - ";
		getline(std::cin, title);
		while (title.empty())
		{
			std::cout << "Title cant be empty" << std::endl;
			std::cout << "Title - ";
			getline(std::cin, title);
		}
		std::cout << "Author - ";
		getline(std::cin, author);
		while (author.empty())
		{
			std::cout << "Author cant be empty" << std::endl;
			std::cout << "Author - ";
			getline(std::cin, title);
		}
		std::cout << "Type - ";
		getline(std::cin, type);
		while (type.empty())
		{
			std::cout << "Type cant be empty" << std::endl;
			std::cout << "Type - ";
			std::getline(std::cin, type);
		}
		std::vector<char> stats;
		status.clear();
		for (const auto i : "In Stock")
			status.push_back(i);
		status.resize(29);
	}

	Book::Book(const std::string &bookFromFile, int ID)
	{
		std::string temp;
		std::stringstream streamOfBooks(bookFromFile);
		getline(streamOfBooks, temp, ';');
		id = ID;
		getline(streamOfBooks, temp, ';');
		type = temp;
		getline(streamOfBooks, temp, ';');
		title = temp;
		getline(streamOfBooks, temp, ';');
		author = temp;
		getline(streamOfBooks, temp, ';');
		status.clear();
		for (const auto i : temp)
		{
			status.push_back(i);
		}
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (temp.find("in stock") == std::string::npos)
		{
			isBorrowed = true;
		}
		else
			isBorrowed = false;
	}

	bool Book::CanBeBorrowed() const
	{
		return(!isBorrowed);
	}

	int Book::GetStudentID() const
	{
		std::string temp;
		std::stringstream ss;
		for (const auto i : status)
		{
			ss << i;
		}
		getline(ss, temp, '_');
		return stoi(temp);
	}

	void Book::save(const std::string &bookFileName) const
	{
		std::fstream booksFile;
		booksFile.open(bookFileName, std::ios::out | std::ios::app);
		if (booksFile)
		{
			std::string temp = "";
			temp += ";" + type + ";" + title + ";" + author + ";";
			for (const auto i : status)
			{
				temp += i;
			}
			temp += ";";
			booksFile << id << temp << std::endl;
		}
		else
		{
			std::cout << "Error";
		}

	}

	
}