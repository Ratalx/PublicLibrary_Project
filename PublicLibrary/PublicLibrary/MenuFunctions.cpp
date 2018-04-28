#include"MenuFunctions.h"
namespace publicLibrary {
	void MenuFunctions::AddBook(const std::string &bookFileName)
	{

		Book tempBook(GetNextID(bookFileName));
		tempBook.save(bookFileName);
	}

	void MenuFunctions::AddStudent(const std::string &studentFileName)
	{
		Student tempStudent(GetNextID(studentFileName));
		tempStudent.save(studentFileName);
	}

	bool MenuFunctions::BookMenu(const std::string &bookFileName)
	{
		std::fstream bookFile;
		bookFile.open(bookFileName, std::ios::in);
		if (!bookFile)
		{
			MakeBookList(bookFileName);
		}
		ShowFile(bookFileName);
		std::cout << "\n1.Add Book  2.Back to Main Menu" << std::endl;
		int userChoosedOption;
		std::cin >> userChoosedOption;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			userChoosedOption = 3;
		}
		switch (userChoosedOption)
		{
		case 1:
			AddBook(bookFileName);
			std::cin.clear();
			std::cin.ignore();
			std::cin.sync();
			break;
		case 2:
			return false;
			break;
		default:
			std::cout << std::endl << "Not a vaild option!" << std::endl;
			break;
		}
		return true;
	}

	void MenuFunctions::Borrow(Book & bookToBorrow, Student & borrowingStudent)
	{
		std::stringstream streamOfBooks, streamOfStudents;
		borrowingStudent.borrowedBooks.clear();
		streamOfBooks << bookToBorrow.id << "_" << GetTime() << " Borrowed";
		for (auto i : streamOfBooks.str())
			borrowingStudent.borrowedBooks.push_back(i);
		borrowingStudent.numberOfBorrowedBooks++;
		streamOfStudents << borrowingStudent.id << "_" << GetTime() << " Borrowed";
		bookToBorrow.status.clear();
		for (auto i : streamOfStudents.str())
			bookToBorrow.status.push_back(i);
	}

	bool MenuFunctions::BorrowMenu(const std::string &bookFileName, const std::string &studentFileName)
	{
		int bookID, studentID, studentColumnNumber, bookColumnNumber;
		std::string studentContent, bookContent;
		if (!ShowFile(studentFileName))
		{
			return false;
		}
		std::cout << "Choose Student.. Type his ID here : ";
		std::cin >> studentID;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			std::cout << "Error!!\n ID should be integer. Try again..\n";
			return false;
		}
		tie(studentContent, studentColumnNumber) = GetObjectFromFile(studentID, studentFileName);
		if (studentContent == "")
		{
			std::cout << "No student with this ID. Try again.." << std::endl;
			return false;
		}
		Student borrowingStudent(studentContent, studentID);
		if (!borrowingStudent.CanBorrow())
		{
			std::cout << "This Student is already having a book!!" << std::endl;
			return false;
		}
		ShowFile(bookFileName);
		std::cout << "Choose Book. Type ID here : ";
		std::cin >> bookID;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			std::cout << "Error!!\n ID should be integer. Try again..\n";
			return false;
		}
		tie(bookContent, bookColumnNumber) = GetObjectFromFile(bookID, bookFileName);
		if (bookContent == "")
		{
			std::cout << "No Book with this ID. Try again.." << std::endl;
			return false;
		}
		Book bookToBorrow(bookContent, bookID);
		if (!bookToBorrow.CanBeBorrowed())
		{
			std::cout << "Book not avaible!" << std::endl;
			return false;
		}
		Borrow(bookToBorrow, borrowingStudent);
		SaveAfterAction(borrowingStudent, studentFileName, studentColumnNumber);
		SaveAfterAction(bookToBorrow, bookFileName, bookColumnNumber);
		return false;
	}

	void MenuFunctions::ExcelMenu(const std::string &bookFileName, const std::string &studentFileName)
	{
		int i;
		std::cout << "1.Open " << bookFileName << std::endl << "2.Open " << studentFileName << std::endl << "0.Return" << std::endl;
		std::cin >> i;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			i = 0;
		}
		if (i == 1)
		{
			std::fstream bookFile;
			bookFile.open(bookFileName, std::ios::in);
			if (bookFile)
			{
				const char * constCharFileName = bookFileName.c_str();
				system(constCharFileName);
			}
			else
				std::cout << "No file" << std::endl;
		}
		else if (i == 2)
		{
			std::fstream studentFile;
			studentFile.open(studentFileName, std::ios::in);
			if (studentFile)
			{
				const char * ConstCharFileName = studentFileName.c_str();
				system(ConstCharFileName);
			}
			else std::cout << "No file" << std::endl;
		}
	}

	int MenuFunctions::GetNextID(const std::string &fileName)
	{
		std::fstream file;
		file.open(fileName, std::ios::in);
		std::string tempID;
		int searchedID;
		file.seekg(0, std::ios_base::beg);
		for (tempID; std::getline(file, tempID);) 
		{
			//getline(file, tempID, '\n');
			if (tempID != "")
			{
				searchedID = tempID.find_first_of(';');
				tempID = tempID.substr(0, searchedID);
				if (tempID == "ID")
				{
					searchedID = 1;
				}
				else
				{
					searchedID = stoi(tempID);
					++searchedID;
				}
			}
		}


		return searchedID;
	}

	std::tuple<std::string, int> MenuFunctions::GetObjectFromFile(int ID, const std::string &fileName)
	{
		int numberOfColumn = 0;
		std::string tempString;
		std::fstream file;
		std::string contentOfRow;
		file.open(fileName, std::ios::in);
		if (file)
		{
			std::getline(file, tempString);
			while (std::getline(file, tempString)&&contentOfRow.empty())
			{
				numberOfColumn++;
				if (stoi(tempString) == ID)
				{
					contentOfRow = tempString;
				}
			}
		}
		else
			std::cout << "None student registered :(" << std::endl;
		return { contentOfRow, numberOfColumn };
	}

	std::string MenuFunctions::GetTime()
	{
		time_t rawTime;
		struct  tm  timeInfo;
		char buff[26];
		time(&rawTime);
		localtime_s(&timeInfo, &rawTime);
		ctime_s(buff, sizeof buff, &rawTime);
		strftime(buff, sizeof buff, "%F", &timeInfo);
		return buff;
	}

	bool MenuFunctions::MainMenu(const std::string &bookFileName, const std::string &studentFileName)
	{
		std::cout << "1.Book\n2.Student\n3.Return\n4.Borrow\n5.Excel files\n0.Exit" << std::endl;
		int userChoosedOption;
		std::cin >> userChoosedOption;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			userChoosedOption = 20;
		}
		switch (userChoosedOption)
		{
		case 1:
			while (BookMenu(bookFileName));
			break;
		case 2:
			while (StudentMenu(studentFileName));
			break;
		case 3:
			while (ReturnMenu(bookFileName, studentFileName));
			break;
		case 4:
			while (BorrowMenu(bookFileName, studentFileName));
			break;
		case 5:
			ExcelMenu(bookFileName, studentFileName);
			break;
		case 0:
			return false;
		default:
			std::cout << "Not a vaild Option" << std::endl;
			break;
		}
		return true;
	}

	void MenuFunctions::MakeBookList(const std::string &bookFileName)
	{
		std::fstream booksFile;
		booksFile.open(bookFileName, std::ios::out);
		if (booksFile)
		{
			booksFile << "ID;Type;Title;Author;Status;" << std::endl;
		}
		else
			std::cout << "Error";
	}

	void MenuFunctions::MakeStudentList(const std::string &studentFileName)
	{
		std::fstream file;
		file.open(studentFileName, std::ios::out);
		if (file)
		{
			file << "ID;First Name ;Last Name ;Number of Borrowed Books;Borrowed Books;" << std::endl;
		}
		else
			std::cout << "Error";
	}

	void MenuFunctions::Return(Book & bookToReturn, Student & studentReturningBook)
	{
		studentReturningBook.borrowedBooks.clear();
		for (auto i : "None")
			studentReturningBook.borrowedBooks.push_back(i);
		studentReturningBook.borrowedBooks.resize(29);
		studentReturningBook.numberOfBorrowedBooks--;
		bookToReturn.status.clear();

		for (auto i : "In stock")
			bookToReturn.status.push_back(i);
		bookToReturn.status.resize(29);
	}

	bool MenuFunctions::ReturnMenu(const std::string &bookFileName, const std::string &studentFileName)
	{
		int userChoosedOption;
		std::cout << "1.By Student ID\n2.By Book ID\n0.Back" << std::endl;
		std::cin >> userChoosedOption;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			userChoosedOption = 0;
		}
		int studentColumnNumber, bookColumnNumber;
		std::string studentContent, bookContent;
		if (userChoosedOption == 1)
		{
			std::cout << "Student ID : ";
			std::cin >> userChoosedOption;
			if (!std::cin)
			{
				std::cin.clear();
				std::cin.sync();
				std::cin.ignore();
				userChoosedOption = 0;
				std::cout << "ID not valide!" << std::endl;
				return true;
			}
			tie(studentContent, studentColumnNumber) = GetObjectFromFile(userChoosedOption, studentFileName);;
			if (studentContent == "")
			{
				std::cout << "No Student with this ID. Try again ..." << std::endl;
				return true;
			}
			Student studentReturningBook(studentContent, userChoosedOption);

			if (studentReturningBook.CanBorrow())
			{
				std::cout << "Student dont have any book :(" << std::endl;
				return true;
			}

			int idOfBook = studentReturningBook.GetBookID();
			tie(bookContent, bookColumnNumber) = GetObjectFromFile(idOfBook, bookFileName);
			Book returningBook(bookContent, idOfBook);
			Return(returningBook, studentReturningBook);
			SaveAfterAction(studentReturningBook, studentFileName, studentColumnNumber);
			SaveAfterAction(returningBook, bookFileName, bookColumnNumber);
			return false;

		}
		if (userChoosedOption == 2)
		{
			std::cout << "Book ID : ";
			std::cin >> userChoosedOption;
			if (!std::cin)
			{
				std::cin.clear();
				std::cin.sync();
				std::cin.ignore();
				userChoosedOption = 0;
				std::cout << "ID not valide!" << std::endl;
				return true;
			}
			tie(bookContent, bookColumnNumber) = GetObjectFromFile(userChoosedOption, bookFileName);
			if (bookContent == "")
			{
				std::cout << "No Book with this ID. Try again ..." << std::endl;
				return true;
			}
			Book returningBook(bookContent, userChoosedOption);
			if (returningBook.CanBeBorrowed())
			{
				std::cout << "Book with this ID is not borrowed" << std::endl;
				return true;
			}
			int idOfStudent = returningBook.GetStudentID();
			tie(studentContent, studentColumnNumber) = GetObjectFromFile(idOfStudent, studentFileName);
			Student studentReturningBook(studentContent, idOfStudent);
			Return(returningBook, studentReturningBook);
			SaveAfterAction(studentReturningBook, studentFileName, studentColumnNumber);
			SaveAfterAction(returningBook, bookFileName, bookColumnNumber);
			return false;

		}
		if (userChoosedOption == 0)
		{
			return false;
		}
		return false;
	}

	void MenuFunctions::SaveAfterAction(Book & bookToBorrow, const std::string &bookFileName, int numberOfColumn)
	{
		std::string tempString;
		std::fstream file;
		file.open(bookFileName, std::ios::in | std::ios::out);
		if (file)
		{
			for (int i = 0; i < numberOfColumn; i++)
			{
				getline(file, tempString, '\n');
				if (tempString == "")
				{
					break;
				}
			}
			file.seekg(file.tellp(), std::ios::beg);
			tempString = "";
			std::stringstream streamOfBooks;
			streamOfBooks << bookToBorrow.id << ";" << bookToBorrow.type << ";" << bookToBorrow.title << ";" << bookToBorrow.author << ";";
			for (auto i : bookToBorrow.status)
			{
				streamOfBooks << i;
			}
			tempString = streamOfBooks.str();
			file << tempString;
		}
		else
			std::cout << "Error" << std::endl;

	}

	void MenuFunctions::SaveAfterAction(Student & borrowingStudent, const std::string &studentFileName, int numberOfColumn)
	{
		std::string tempString;
		std::fstream file;
		file.open(studentFileName, std::ios::in | std::ios::out);
		if (file)
		{
			for (int i = 0; i < numberOfColumn; i++)
			{
				getline(file, tempString, '\n');
				if (tempString == "")
				{
					break;
				}
			}
			file.seekg(file.tellp(), std::ios::beg);
			tempString = "";
			std::stringstream streamOfStudents;
			streamOfStudents << borrowingStudent.id << ";" << borrowingStudent.firstName << ";" << borrowingStudent.lastName << ";" << borrowingStudent.numberOfBorrowedBooks << ";";
			for (auto i : borrowingStudent.borrowedBooks)
				streamOfStudents << i;
			tempString = streamOfStudents.str();
			file << tempString;
		}
		else
			std::cout << "Error" << std::endl;

	}

	bool MenuFunctions::ShowFile(const std::string &fileName)
	{
		std::fstream	file;
		file.open(fileName, std::ios::in);
		std::string tempString;
		if (file)
		{
			for (tempString; std::getline(file, tempString, ';');)
			{
				//getline(file, tempString, ';');
				std::cout << tempString << "  " << std::setw(20);
			}
		}
		else
		{
			std::cout << "error" << std::endl;
			return false;
		}
		return true;
	}

	bool MenuFunctions::StudentMenu(const std::string &studentFileName)
	{
		std::fstream studentsFile;
		studentsFile.open(studentFileName, std::ios::in);
		if (!studentsFile)
		{
			MakeStudentList(studentFileName);
		}
		ShowFile(studentFileName);
		std::cout << "\n1.Add Student  2.Back to Main Menu" << std::endl;
		int userChoosedOption;
		std::cin >> userChoosedOption;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.sync();
			std::cin.ignore();
			userChoosedOption = 3;
		}
		switch (userChoosedOption)
		{
		case 1:
			AddStudent(studentFileName);
			break;
		case 2:
			return false;
			break;
		default:
			std::cout << std::endl << "Not a vaild option!" << std::endl;
			break;
		}
		return true;
	}

	
}