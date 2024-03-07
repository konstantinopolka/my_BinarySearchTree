#pragma once
#include "node.h"

template <typename T>
binary_tree<T>::node::node() : value(T()), left(nullptr), right(nullptr)
{}
template <typename T>
binary_tree<T>::node::node(T value, node* left, node* right, node* parent) : value(value), left(left), right(right), parent(parent)
{}
template <typename T>
inline binary_tree<T>::node::node(T value, node* parent) : value(value), left(nullptr), right(nullptr), parent(parent)
{}
template <typename T>
inline binary_tree<T>::node::node(node* left, node* right) : value(T()), left(left), right(right), parent(nullptr)
{}

template <typename T>
inline binary_tree<T>::node::node(T value) : value(value), left(nullptr), right(nullptr), parent(nullptr)
{}

template <typename T>
binary_tree<T>::node::~node()
{}