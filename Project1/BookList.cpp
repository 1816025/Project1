#include <Windows.h>
#include "DxLib.h"
#include "Event.h"
#include "BookList.h"

BookList::BookList()
{
	WIN32_FIND_DATA fd;
	HANDLE handle = FindFirstFile("data/BookArchive/*.dat",&fd);

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
}

string BookList::GetArchive(int member)
{
	return BookArchive[member];
}

void BookList::SetLibrary(string member)
{
	BookLibrary.emplace_back(member);
}

int BookList::GetArchiveSize()
{
	return BookArchive.size();
}

BookList::~BookList()
{
}
