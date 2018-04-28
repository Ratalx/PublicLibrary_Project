#include"Student.h"
namespace publicLibrary {
	class Book;
	class Student;
	class  MenuFunctions {
	public:
		static void AddBook(const std::string &bookFileName);
		static void AddStudent(const std::string &studentFileName);
		static bool BookMenu(const std::string& bookFileName);
		static void Borrow(Book & bookToBorrow, Student& borrowingStudent);
		static bool BorrowMenu(const std::string &bookFileName, const std::string &studentFileName);
		static void ExcelMenu(const std::string &bookFileName, const std::string &studentFileName);
		static int GetNextID(const std::string &fileName);
		static std::tuple<std::string, int> GetObjectFromFile(int ID, const std::string &fileName);
		static std::string GetTime();
		static bool MainMenu(const std::string &bookFileName, const std::string &studentFileName);
		static void MakeBookList(const std::string& bookFileName);
		static void MakeStudentList(const std::string &studentFileName);
		static void Return(Book & bookToReturn, Student & studentReturningBook);
		static bool ReturnMenu(const std::string &bookFileName, const std::string &studentFileName);
		static void SaveAfterAction(Book &bookToBorrow, const std::string& bookFileName, int numberOfColumn);
		static void SaveAfterAction(Student & borrowingStudent, const  std::string &studentFileName, int numberOfColumn);
		static bool ShowFile(const std::string &fileName);
		static bool StudentMenu(const std::string &studentFileName);
	};
}