#pragma once
#include <string>
#include <array>
#include <vector>
#include <map>

#ifdef _DEBUG
#define AST(){\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目￥0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif    // _DEBUG

#define lpBookList BookList::GetInstance()
using namespace std;
enum class BookTitle
{
	Arthur,
	HanselandGretel,
	Alice,
	Hameln,
	Necronomicon,
	Humanskin,
	Max
};

enum class BookRank
{
	Nameless,
	Common,
	Rare,
	Prohibited,
	Max
};

struct Book_Status
{
	char Author[256];
	BookRank rank;			//レア度
	int Evaluation;	//評価値
	bool Favorability;		//友好度上昇イベ対象かどうか
};
using Library_Tbl = array<bool, static_cast<size_t>(BookTitle::Max)>;
class BookList
{
public:
	static BookList &GetInstance(void)
	{
		static BookList s_Instance;
		return s_Instance;
	}

	const string GetArchive(int member);
	void SetLibrary(int num,bool flag);
	const Library_Tbl GetLibrary(void);
	const int GetLibraryIndex(string member);
	const vector<string> GetAuthor(void);
	const vector<string> GetFavorabilityList(bool flag);
	const int GetArchiveSize(void);
	const int GetLibrarySize(void);
	const int GetFriendshipValue(int index);
	const int SetFriendshipValue(int index,int data);

	void SetLooting(string title, bool flag);
	void ChangeStatus(string author);
	void DataSave(string title);
	void DataLoad(string title);

	vector<int> FriendshipValue;
private:
	BookList();
	~BookList();
	vector<string> BookArchive;
	vector<string> BookAuthorList;
	vector<BookRank>BookRankList;
	Library_Tbl BookLibrary;
	map<string, Book_Status>BookStatus;
};