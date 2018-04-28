#include"Book.h"
namespace publicLibrary {
	class User
	{
	protected:
		std::string firstName, lastName;
		int id;
		std::vector<char> borrowedBooks;
		int numberOfBorrowedBooks;
	public:
		virtual void save(const std::string &fileName) const;
		virtual bool CanBorrow() const;
		virtual int GetBookID() const;
	};
}
