// File: a6.hpp
// Xin
// Jiang
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A6_HPP
#define A6_HPP

#include <ostream>
#include "symbol.hpp"
#include <vector>
#include <string>

// MAKE SURE TO UPDATE YOUR INFORMATION IN THE HEADER OF THIS FILE
// IMPLEMENT ALL REQUIRED FUNCTIONS BELOW
// YOU ARE NOT ALLOWED TO ALTER ANY INTERFACE
// INSIDE A FUNCTION YOU CAN DO WHATEVER YOU LIKE

// IMPLEMENT YOUR FUNCTION huffman_tree
template <typename Iter>
bnode<symbol>* huffman_tree(Iter first, Iter last);

// IMPLEMENT YOUR FUNCTION print_dictionary
void print_dictionary(std::ostream& os, bnode<symbol>* root);

// IMPLEMENT YOUR FUNCTION release_tree
void release_tree(bnode<symbol>* root);


template <typename Iter>
bnode<symbol>* huffman_tree(Iter first, Iter last)
{
	std::vector<bnode<symbol>*> vec_node;
	for (; first != last; first++)
	{
		bnode<symbol>* node = new bnode<symbol>(*first);
		auto it = vec_node.begin();
		for (; it != vec_node.end(); it++)
		{
			if ((*it)->value < node->value  || (((*it)->value.value == 0 )&& ( node->value.value == 0)))
			{
				break;
			}
		}
		vec_node.insert(it, node);
	}

	while (vec_node.size() > 1)
	{

		bnode<symbol>* node1 = vec_node.back();
		vec_node.pop_back();
		bnode<symbol>* node2 = vec_node.back();
		vec_node.pop_back();

		bnode<symbol>* node = new bnode<symbol>(symbol(static_cast<char>(node1->value.value < node2->value.value? node1->value.value : node2->value.value),
			node1->value.count + node2->value.count));

		if (node1->value < node2->value)
		{
			node->left = node1;
			node->right = node2;
		}
		else
		{
			node->left = node2;
			node->right = node1;
		}

		auto it = vec_node.begin();
		for (; it != vec_node.end(); it++)
		{
			if ((*it)->value < node->value || (((*it)->value.value == 0)&&( node->value.value == 0)))
			{
				break;
			}
		}
		vec_node.insert(it, node);
	}


	bnode<symbol>* root = vec_node[0];
	root->value.count = 0;
	return root;

}

void print_dictionary(std::ostream& os, bnode<symbol>* root)
{
	static char code[30];

	if (root != nullptr)
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			code[root->value.count] = '\0';
			os << root->value.value << " ";
			os << code << std::endl;
		}
		else
		{
			code[root->value.count] = '0';
			root->left->value.count = root->value.count + 1;
			print_dictionary(os, root->left);
			code[root->value.count] = '1';
			root->right->value.count = root->value.count + 1;
			print_dictionary(os, root->right);

		}

	}
}

void release_tree(bnode<symbol>* root)
{
	if (root != nullptr)
	{
		release_tree(root->left);
		release_tree(root->right);
		delete root;
	}

}


#endif // A6_HPP
