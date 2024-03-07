#pragma once
#include "binary_tree.h"

template <typename T>
class binary_tree<T>::node
{
public:
	node();
	~node();
	node(T value, node* left, node* right, node* parent = nullptr);
	node(T value, node* parent);
	node(node* left, node* right);
	node(T value);
	T value;
	node* parent;
	node* left;
	node* right;
	
};

