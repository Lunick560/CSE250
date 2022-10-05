// File: a3.hpp
// Xin
// Jiang
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A3_HPP
#define A3_HPP

// MAKE SURE TO UPDATE YOUR INFORMATION IN THE HEADER OF THIS FILE
// IMPLEMENT MISSING FUNCTIONALITY OF key_value_sequences IN THIS FILE
// YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER HEADERS THAN
// <algorithm>, <list>, <vector>
// YOU CAN CHANGE/EDIT ANY CODE IN THIS FILE AS LONG AS SEMANTICS IS UNCHANGED
// AND MATCHES SPECIFICATION PROVIDED IN THE ASSIGNMENT TEXT

#include <algorithm>
#include <list>
#include <vector>

class key_value_sequences {
public:
	// YOU SHOULD USE C++ CONTAINERS TO AVOID RAW POINTERS
	// IF YOU DECIDE TO USE POINTERS, MAKE SURE THAT YOU MANAGE MEMORY PROPERLY

	// IMPLEMENT ME: SHOULD RETURN SIZE OF A SEQUENCE FOR GIVEN KEY
	// IF NO SEQUENCE EXISTS FOR A GIVEN KEY RETURN 0
	~key_value_sequences();
	int size(int key) const;

	// IMPLEMENT ME: SHOULD RETURN POINTER TO A SEQUENCE FOR GIVEN KEY
	// IF NO SEQUENCE EXISTS FOR A GIVEN KEY RETURN nullptr
	const int* data(int key) const;

	// IMPLEMENT ME: INSERT VALUE INTO A SEQUENCE IDENTIFIED BY GIVEN KEY
	void insert(int key, int value);
	int findPosition(int key) const;
private:

	std::vector<std::vector<int>> value_container;
	std::vector<int> key_container;

}; // class key_value_sequences

key_value_sequences::~key_value_sequences()
{

	for (auto it = value_container.begin(); it != value_container.end(); it++)
	{
		it->clear();
		std::vector<int>().swap(*it);
		it->resize(0);
    }

	value_container.resize(0);

	key_container.clear();
	std::vector<int>().swap(key_container);
	key_container.resize(0);
}

int  key_value_sequences::findPosition(int key) const
{

	if (key_container.size() == 0)
	{
		return -1;
	}
	unsigned int low = 0;
	unsigned int high = key_container.size() - 1;
	unsigned int mid = low + ((high - low) / 2);
	int position = -1;
	if ( (key < key_container.at(low)) || (key > key_container.at(high)))//do not contain the key
	{
		position = -1;
	}
	else
	{
		while (low <= high)
		{
			if (key == key_container.at(low)) // find the key
			{
				position = low;
				break;
			}
			else if (key == key_container.at(high)) // find the key
			{
				position = high;
				break;
			}
			else
			{
				mid = low + ((high - low) / 2);
				if (key == key_container.at(mid)) // find the key
				{
					position = mid;
					break;
				}
				else if (key < key_container.at(mid))
				{
					high = mid - 1;
					if (high >= key_container.size() )
					{
						high = 0;
					}
				}
				else
				{
					low = mid + 1;
					if (low >= key_container.size())
					{
						low = key_container.size();
					}
				}
			}
		}
		if (low >= high) // do not exists
		{
			position = -1;
		}
	}
	if (position >= (int)key_container.size())
	{
		position = -1;
	}

	return position;
}

void key_value_sequences::insert(int key, int value)
{
	if (key_container.size() == 0)
	{
		key_container.push_back(key);
		std::vector<int> v;
		v.push_back(value);
		value_container.push_back(v);
	}
	else
	{
		unsigned int low = 0;
		unsigned int high = key_container.size() - 1;
		unsigned int  mid = low + ((high - low) / 2);
		if (key < key_container.at(low))
		{
			key_container.insert(key_container.begin(), key);
			std::vector<int> v;
			v.push_back(value);
			value_container.insert(value_container.begin(), v);
		}
		else if (key > key_container.at(high))
		{
			key_container.push_back(key);
			std::vector<int> v;
			v.push_back(value);
			value_container.push_back(v);
		}
		else
		{
			unsigned int position = 0;
			while (low <= high)
			{
				if (key == key_container.at(low))
				{
					position = low;
					break;
				}
				else if (key == key_container.at(high))
				{
					position = high;
					break;
				}
				else
				{
					mid = low + ((high - low) / 2);
					if (key == key_container.at(mid))
					{
						position = mid;
						break;
					}
					else if (key < key_container.at(mid))
					{
						high = mid - 1;
						if (high >= key_container.size())
						{
							high = 0;
						}
					}
					else
					{
						low = mid + 1;
						if (low >= key_container.size())
						{
							low = key_container.size() - 1;
						}
					}
				}
			}
			if (low >= high)
			{
				position = high;
			}

			if (key == key_container.at(position))
			{
				value_container.at(position).push_back(value);
			}
			else if (key < key_container.at(position))
			{
				key_container.insert(key_container.begin() + position, key);
				std::vector<int> v;
				v.push_back(value);
				value_container.insert(value_container.begin() + position, v);
			}
			else if (key > key_container.at(position))
			{
				key_container.insert(key_container.begin() + position + 1, key);
				std::vector<int> v;
				v.push_back(value);
				value_container.insert(value_container.begin() + position + 1, v);
			}
		}
	}
}

int key_value_sequences::size(int key) const
{
	int position = this->findPosition(key);
	if (position < 0)
	{
		return 0;
	}
	else
	{
		return value_container.at(position).size();
	}
}

const int* key_value_sequences::data(int key) const
{
	int position = this->findPosition(key);
	if (position < 0)
	{
		return nullptr;
	}
	else
	{
		return value_container.at(position).data();
	}
}




#endif // A3_HPP
