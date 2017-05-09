#include <string>
using namespace std;
#if !defined(BOOK_H)
#define BOOK_H
class _declspec(dllexport) Book
{
public:
	int ID;
	string Name;
	double Price;
	string CreateTime;
	string UpdateTime;
	bool Status;
};
#endif