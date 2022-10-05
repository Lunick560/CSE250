

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>


/* read the file content to the dictionary */
void readFile(char fileName[], std::map<std::string, unsigned> &dict)
{
	std::string name;
	unsigned freq = 0;
	std::ifstream f(fileName);
	//open file
	if (!f.is_open())
	{
		std::cout << "Coulde not open the file." << std::endl;
		exit(1);
	}
	//read file
	while (!f.eof())
	{
		f >> name;
		f.ignore(1, ' ');
		f >> freq;
		f.ignore();
		dict.insert(std::pair<std::string, unsigned>(name, freq));
	}
}

/* split the string to names*/
void wordSplit(const char *str, std::vector<std::string> &words)
{
	std::string name;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if ((str[i]<'A'||str[i]>'Z') && name.length() > 0)
		{
			words.push_back(name);
			name.clear();
		}
		else if(str[i]>= 'A'&& str[i]<='Z')
		{
			name.push_back(str[i]);
		}
	}
	if (name.length() > 0)
	{
		words.push_back(name);
	}	
}

/* deletion case */
unsigned match_deletion(std::string dict_name, std::string name)
{
	unsigned mismatch_count = 0;
	unsigned i = 0, j = 0;
	while (i < dict_name.length() && j < name.length())//name to query is longer than name in dict,
	{
		if (dict_name[i] == name[j])
		{
			i++;
			j++;
		}
		else // 
		{
			j++;
			mismatch_count++;
			if (mismatch_count > 1)
			{
				break;
			}
		}
	}
	if (mismatch_count == 0)//if dict_name is one char word,and the first char is same to  name,at least one char mismatch
	{
		mismatch_count = 1;
	}

	return mismatch_count;
}

/* replacement case */
unsigned match_replacement(std::string dict_name, std::string name)
{
	unsigned mismatch_count = 0;
	unsigned i = 0, j = 0;
	while ( i < dict_name.length() && j < name.length())
	{
		if (dict_name[i] != name[j])
		{
			mismatch_count++;
			if (mismatch_count > 1)
			{
				break;
			}
		}
		i++;
		j++;
	}
	return mismatch_count;
}

/* insertion case */
unsigned match_insertion(std::string dict_name, std::string name)
{
	unsigned mismatch_count = 0;
	unsigned i = 0, j = 0;
	while (i < dict_name.length() && j < name.length())//name to query is shorter than name in dict,
	{
		if (dict_name[i] == name[j])
		{
			i++;
			j++;
		}
		else // 
		{
			i++;
			mismatch_count++;
			if (mismatch_count > 1)
			{
				break;
			}
		}
	}
	if (mismatch_count == 0)//if dict_name is one char word,and the first char is same to  name, at least one char mismatch
	{
		mismatch_count = 1;
	}
	return mismatch_count;
}


void query(std::map<std::string, unsigned> &dict, std::vector<std::string> &names)
{
	for (unsigned i = 0; i < names.size(); i++)
	{
		std::string correctSpell;
		unsigned freq = 0;
		int mismacth_count = 0;
		for (auto it = dict.begin(); it != dict.end(); it++)
		{
			std::string temp = it->first;
			if (temp.length() + 1 == names[i].length())
			{
				mismacth_count = match_deletion(temp, names[i]);
			}
			else if (temp.length() == names[i].length())
			{
				mismacth_count = match_replacement(temp, names[i]);
			}
			else if (temp.length() == names[i].length() + 1)
			{
				mismacth_count = match_insertion(temp, names[i]);
			}
			else
			{
				mismacth_count = 2;
			}
			//
			if (mismacth_count == 0)
			{
				freq = it->second;
				correctSpell = it->first;
				break;
			}
			else if (mismacth_count == 1)
			{
				if (it->second > freq || it->first < correctSpell)
				{
					freq = it->second;
					correctSpell = it->first;
				}
			}
			else
			{

			}
		}

		if (correctSpell.length() == 0)
		{
			std::cout << '-' << std::endl;
			dict.insert(std::pair<std::string, unsigned>(names[i], 1));
		}
		else
		{
			std::cout << correctSpell << " " << freq << std::endl;
		}
		if (names[i] == correctSpell)
		{
			auto itTemp = dict.find(correctSpell);
			itTemp->second++;
		}

	}
}




int main(int argc,char *argv[])
{
	std::map<std::string, unsigned> dict;
	std::vector<std::string> names;
	std::string str;

	if (argc < 2) {
		std::cout << "usage: ./a7 file \"GILL BILL BILL DILL SANTA SANTA\" or echo \"GILL BILL BILL DILL SANTA SANTA\" | ./a7 file" << std::endl;
		return -1;
	}
	else if (argc == 2)
	{
		readFile(argv[1], dict);
		while (true)
		{
			str.clear();
			names.clear();
			getline(std::cin, str);
			if (str.length() > 0)
			{
				wordSplit(str.c_str(), names);			
				query(dict, names);
			}
			else
			{
				break;
			}
		}

	}
	return 0;
}