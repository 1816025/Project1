#pragma once
#include <string>
#include <vector>

#define lpBookList BookList::GetInstance()
using namespace std;

enum class BookRank
{
	Nameless,
	Common,
	Rare,
	Prohibited,
	Max
};

struct BookStatus
{
	char title[25];
	char rank;
	char Evaluation;
};

class BookList
{
public:
	static BookList &GetInstance(void)
	{
		static BookList s_Instance;
		return s_Instance;
	}

	string GetArchive(int member);
	void SetLibrary(string member);
	int GetArchiveSize();
private:
	BookList();
	~BookList();
	vector<string> BookArchive;
	vector<string> BookLibrary;
};