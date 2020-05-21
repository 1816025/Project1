#include <algorithm>
#include <Windows.h>
#include "DxLib.h"
#include "Event.h"
#include "BookList.h"

	FILE *fp;
BookList::BookList()
{
	WIN32_FIND_DATA fd;
	HANDLE handle = FindFirstFile("data/BookArchive/List/*.dat",&fd);

	Book_Status tmp_status;
	if (BookArchive.size() == 0)
	{
		if (handle != INVALID_HANDLE_VALUE)
		{
			do
			{
				string tmp_fh = fd.cFileName;
				BookArchive.emplace_back(tmp_fh.erase(tmp_fh.find(".")));
			} while (FindNextFile(handle, &fd));
		}
	}
	for (auto n : BookLibrary)
	{
		BookLibrary[n] = false;
	}
	for (auto n : BookArchive)
	{
		fopen_s(&fp, ("data/BookArchive/List/" + n + ".dat").c_str(), "rb");
		fread(&tmp_status, sizeof(tmp_status), 1, fp);
		BookStatus[n] = tmp_status;
		fclose(fp);
	}
	//			BookLibrary.emplace_back(false);

}

const string BookList::GetArchive(int member)
{
	return BookArchive[member];
}

void BookList::SetLibrary(int num,bool flag)
{
	BookLibrary[num] = flag;
}

 const int BookList::GetLibraryIndex(string member)
{
	 vector<string>::iterator itr;
	 itr = std::find(BookArchive.begin(), BookArchive.end(), member);
	 auto index = std::distance(BookArchive.begin(), itr);
	// printfDx("%d", index);
	return index;
}

 const vector<string> BookList::GetAuthor()
 {
	 if (BookAuthorList.empty())
	 {
		 for (auto n : BookStatus)
		 {
			 BookAuthorList.emplace_back(n.second.Author);
		 }
	 }
	 return BookAuthorList;
 }

 const Library_Tbl BookList::GetLibrary()
 {
	 return BookLibrary;
 }

const int BookList::GetArchiveSize()
{
	return BookArchive.size();
}

const int BookList::GetLibrarySize()
{
	return BookLibrary.size();
}

void BookList::ChangeStatus(string author)
{
	auto itr = BookAuthorList.begin();
	if (author != "unkown")
	{
		while (1)
		{
			itr = find(itr, BookAuthorList.end(), author);
			if (itr == BookAuthorList.end())
			{
				break;
			}
			switch ((BookRank)(rand() % static_cast<size_t>(BookRank::Max)))
			{
			case BookRank::Common:
				if (BookStatus[BookArchive[distance(BookAuthorList.begin(),itr)]].rank <= static_cast<int>(BookRank::Common))
				{
					BookStatus[BookArchive[distance(BookAuthorList.begin(), itr)]].rank = static_cast<int>(BookRank::Common);
					BookStatus[BookArchive[distance(BookAuthorList.begin(), itr)]].Evaluation = 100;
				}
				break;
			case BookRank::Rare:
				if (BookStatus[BookArchive[distance(BookAuthorList.begin(), itr)]].rank <= static_cast<int>(BookRank::Rare))
				{
					BookStatus[BookArchive[distance(BookAuthorList.begin(), itr)]].rank = static_cast<int>(BookRank::Rare);
					BookStatus[BookArchive[distance(BookAuthorList.begin(), itr)]].Evaluation = 1000;
				}
				break;
			default:
				break;
			}
			++itr;
		}
	}
}

void BookList::DataSave(string title)
{
	int tmp_size = 0;/*
	for (int num = 0; num < BookLibrary.size(); num++)
	{
		tmp_size = tmp_size + BookLibrary[num].size();
	}*/
	if (title == "BookArchive")
	{
		fopen_s(&fp, ("data/BookArchive/" + title + ".dat").c_str(), "wb");
		fwrite(&BookArchive, sizeof(tmp_size), 1,fp);
	}
	else
	{

	}
	fclose(fp);
}

void BookList::DataLoad(string title)
{
	int tmp_size = 0;
	for (int num = 0; num < BookArchive.size(); num++)
	{
		tmp_size = tmp_size + BookArchive[num].size();
	}
}

BookList::~BookList()
{
}
