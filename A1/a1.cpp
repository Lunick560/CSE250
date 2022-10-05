// File: a1.cpp
// Xin
// Jiang
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES


#include<string>
#include<iostream>
#include<math.h>
#include<vector>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

int Get_Index(const char  *pStr,int len)
{
	int index = 0;
	int temp = 0;

	for ( int i = 0; i < len ; i++)
	{
		if (pStr[i] == 'A')
		{
			temp = 0;
		}
		else if (pStr[i] == 'C')
		{
			temp = 1;
		}
		else if (pStr[i] == 'G')
		{
			temp = 2;
		}
		else if (pStr[i] == 'T')
		{
			temp = 3;
		}

		index += temp*(int)pow(4,len - i);
	}

	return index;
}


unsigned freq[10000000];
vector<string> k_mer;
int main(int argc,char *argv[])
{
	FILE *fp;

	char *file_name = argv[1];
	int k = atoi(argv[2]);
	int dna_seq_len = 0;
	int As_num = 0;
	int Cs_num = 0;
	int Gs_num = 0;
	int Ts_num = 0;
	int Ns_num = 0;

	char str[10];
	unsigned int str_index = 0;
	bool is_contain_N = false;

	for (int i = 0; i < 10000000; i++)
	{
		freq[i] = 0;
	}

	fp = fopen(file_name, "r");

	if (fp == NULL)
	{
		cout << "can't open file." << endl;
		exit(0);
	}
	char c = 0;
	while (c != EOF)
	{	
        c = getc(fp);
        if(c == '\n' || c == '\r' || c == EOF )//end of file, invalid char
        {
           break;
        }	
		dna_seq_len++;

	    if (dna_seq_len >= k)
		{
                if(dna_seq_len > k)
                {
				  for (int i = 1; i < k ; i++)
				  {
					 str[i - 1] = str[i];
				  }
                }
				str[k - 1] = c;
				str[k] = 0;

				is_contain_N = false;
				for (int i = 0; i < k; i++)
				{
					if (str[i] == 'N')
					{
						is_contain_N = true;
						break;
					}
				}

				if (!is_contain_N)//do not contain N
				{
					int index = Get_Index(str, k);
					freq[index] ++;
					if (freq[index] == 1)
					{
						k_mer.push_back(str);
					}
				}
		}
		else
		{
			str[str_index++] = c;
		}
		switch (c)
		{
			case 'A':
				As_num++;
				break;
			case 'C':
				Cs_num++;
				break;
			case 'G':
				Gs_num++;
				break;
			case 'T':
				Ts_num++;
				break;
			case 'N':
				Ns_num++;
				break;
			default:
				break;
		}
				
	}
	
	//first line
	cout << "0" <<" "<< k <<" "<< dna_seq_len << endl;
	//second line
	cout << "1" << " " << As_num << " " << Cs_num << " " << Gs_num << " " << Ts_num << " " << Ns_num << endl;

	//error, k larger than  length of dna sequence
	if (k > dna_seq_len)
	{
		cout << "error" << endl;
		return 0;
	}
	for (unsigned int i = 0; i < k_mer.size(); i++)
	{
		cout << k_mer[i] << " " << freq[Get_Index(k_mer[i].c_str(),k)] << endl;
	}
	fclose(fp);
    return 0;
}

