#include"User.h"
namespace publicLibrary {
	
	class Student :public User
	{
		friend class MenuFunctions;
	public:
		explicit Student(int id);
		explicit Student(const std::string & studentFileName, int id);
	};
}