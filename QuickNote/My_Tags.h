#ifndef MY_TAGS_H
#define MY_TAGS_H

class My_Tags
{
public:
	WCHAR tags[100];
	vector <My_Tags> temp_list;
	vector <My_Tags> my_list;
	int tagnum = 0;
public:
	void Read_File();
	void Count_Tags();
	void Arrange_Tag();
	void Unique_Tag();
};

#endif 

