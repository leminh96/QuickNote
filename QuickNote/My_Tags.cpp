#include "stdafx.h"
#include "My_Tags.h"

//Doc tu file txt
void My_Tags::Read_File()
{
	My_Tags *temp;
	temp = new My_Tags;
	WCHAR buffer[100];
	wifstream fi;
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
	fi.open(L"My Tags\\Tags.txt", ios::in | ios::app);
	fi.imbue(utf8_locale);
	fi.getline(temp->tags, 100);
	if (wcscmp(temp->tags, L"") != 0)
	{
		while (wcscmp(temp->tags, L"") != 0)
		{
			temp_list.push_back(*temp);
			fi.getline(buffer, 100);
			fi.getline(temp->tags, 100);
		}
		fi.close();
		Count_Tags();
		Unique_Tag();
		Arrange_Tag();
	}
}

//Dem so luong tag
void My_Tags::Count_Tags()
{
	for (int i = 0; i < temp_list.size(); i++)
	{
		for (int j = 0; j < temp_list.size(); j++)
		{
			if (wcscmp(temp_list[i].tags, temp_list[j].tags) == 0)
				temp_list[i].tagnum++;
		}
	}
}

//Sap xep lai cac tag theo thu tu tang dan so luong
void My_Tags::Arrange_Tag()
{
	for (int i = 0; i < my_list.size() - 1; i++)
	{
		for (int j = i; j < my_list.size(); j++)
		{
			if (my_list[i].tagnum < my_list[j].tagnum)
				swap(my_list[i], my_list[j]);
		}
	}
}

//Xoa cac tag trung nhau, tang so luong
void My_Tags::Unique_Tag()
{
	My_Tags *temp;
	temp = new My_Tags;
	wcscpy(temp->tags, temp_list[0].tags);
	temp->tagnum = temp_list[0].tagnum;
	my_list.push_back(*temp);
	int n = 0;
	for (int i = 1; i < temp_list.size(); i++)
	{
		for (int j = 0; j < my_list.size(); j++)
		{
			//Neu tag trung nhau thi tang bien dem
			if (wcscmp(temp_list[i].tags, my_list[j].tags) == 0)
			{
				n++;
			}
		}
		if (n == 0)
		{
			wcscpy(temp->tags, temp_list[i].tags);
			temp->tagnum = temp_list[i].tagnum;
			my_list.push_back(*temp);
		}
		n = 0;
	}
}