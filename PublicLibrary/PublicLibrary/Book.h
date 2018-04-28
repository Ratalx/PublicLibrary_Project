#include<iomanip>
#include<chrono>
#include<tuple>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
namespace publicLibrary {
class Student;
class Book;
class MenuFunctions;
	class Book
	{
		friend class MenuFunctions;
	private:
		std::string title, author, type;
		std::vector<char> status;
		int id;
		bool isBorrowed;
	public:
		explicit Book(int);
		explicit Book(const std::string &bookFileName, int id);
		void save(const std::string &bookFileName) const;
		bool CanBeBorrowed() const;
		int GetStudentID() const;

	};
}