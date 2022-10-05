// File: a2.hpp
// Xin
// Jiang
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A2_HPP
#define A2_HPP

// IMPLEMENT MISSING FUNCTIONALITY OF sorted_sc_array IN THIS FILE
// YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER HEADERS EXCEPT OF <algorithm>
// YOU CAN CHANGE/EDIT ANY CODE IN THIS FILE AS LONG AS SEMANTICS IS UNCHANGED
// AND MATCHES SPECIFICATION AS PROVIDED IN THE ASSIGNMENT TEXT

#include <algorithm>


class sorted_sc_array {
public:
	sorted_sc_array() : size_(0), ptr_(nullptr),capacity(0) {
		for (int i = 0; i < 256; i++)
		{
			statistic[i] = 0;
		}
	}

	~sorted_sc_array() {
           if(ptr_!=nullptr)delete[] ptr_; }

	// IMPLEMENT ME
	sorted_sc_array(const sorted_sc_array& A);

	// IMPLEMENT ME
	sorted_sc_array& operator=(const sorted_sc_array& A);

	// RETURNS SIZE OF THE ARRAY (i.e. HOW MANY ELEMENTS IT STORES)
	int size() const { return size_; }

	// RETURNS RAW POINTER TO THE ACTUAL DATA, CAN BE INVOKED AT ANY TIME
	const signed char* data() const { return ptr_; }


	// IMPLEMENT ME: AFTER INSERT COMPLETES THE ARRAY MUST BE IN ASCENDING ORDER
	void insert(signed char c);


private:
	int size_;         // size of the array
	signed char* ptr_; // pointer to the array
	int capacity;
	int statistic[256];

}; // class sorted_sc_array

//copy constructor
sorted_sc_array::sorted_sc_array(const sorted_sc_array& A)
{

        this->ptr_ = new signed char[A.capacity];
	this->capacity = A.capacity;
	this->size_ = A.size();
	for (int i = 0; i < A.size(); i++)
	{
		*(this->ptr_ + i) = *(A.data() + i);
	}
	for(int i = 0;i < 256;i++)
	{
		this->statistic[i] = A.statistic[i];
	}
}

//assignment operator
sorted_sc_array& sorted_sc_array::operator=(const sorted_sc_array& A)
{
	if (this->size() < A.size())
	{
                if(this->ptr_!=nullptr)
                {
		  delete[]this->ptr_;
                  this->ptr_ = nullptr;
                }
		this->ptr_ = new signed char[A.size()];
		this->capacity = A.size();
	}
	this->capacity = A.capacity;
	this->size_ = A.size();
	for (int i = 0; i < A.size(); i++)
	{
		*(this->ptr_ + i) = *(A.data() + i);
	}
	for(int i = 0;i < 256;i++)
	{
		this->statistic[i] = A.statistic[i];
	}
	return *this;
}

void sorted_sc_array::insert(signed char c)
{
	if (this->size_ + 1 > this->capacity) // no enough space for saving new char
	{
		if (this->capacity == 0)//first time insert()
		{
			this->capacity = 10;
		}
		this->capacity = this->capacity * 2;

		signed char *tempStr  = new signed char[this->capacity];
		for (int i = 0; i < this->size_; i++)
		{
			*(tempStr + i) = *(this->ptr_ + i) ;
		}

                if(this->ptr_ != nullptr)
                {
		  delete[] this->ptr_;
                  this->ptr_ = nullptr;
                }
                this->ptr_ = tempStr;
	}

	int position = 0;

	for (int i = 0; i < c + 128; i++)
	{
		position += statistic[i];
	}

	int sum_element_num = 0;
	for (int i = 255; i >= c+128; i--)
	{
		if (statistic[i] > 0)
		{
			sum_element_num = 0;
			for (int j = 0; j <= i; j++)
			{
				sum_element_num += statistic[j];
			}
			this->ptr_[sum_element_num] = i - 128;//char of the posiong i
		}
	}

	this->ptr_[position] = c;
	this->size_++;
	statistic[c + 128]++;

}

#endif // A2_HPP
