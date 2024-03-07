#pragma once
#include "binary_tree.h"
template <typename T>
binary_tree<T>::binary_tree() : root(nullptr), size_(0)
{
}
template <typename T>
binary_tree<T>::~binary_tree()
{
	clear();
}

template<typename T>
inline void binary_tree<T>::swap(binary_tree& tree1, binary_tree& tree2)
{
	using std::swap;
	swap(tree1.root, tree2.root);
	swap(tree1.size_, tree2.size_);
}

template <typename T>
void binary_tree<T>::add(const T& value) {
	if (empty()){
		root = new node(value);
		size_++;
		return;
	}
	node* current = root;
	//node* parent = root;
	while (true) {
		if (value < current->value) {
			if (current->left == nullptr) {
				current->left = new node(value, current);
				break;
			}
			else
				current = current->left;
		}
		else {
			if (current->right == nullptr) {
				current->right = new node(value, current);
				break;
			}
			else
				current = current->right;
		}
			
		
	}
	size_++;
}

template<typename T>
inline bool binary_tree<T>::remove(const T& value)
{
	node* to_remove = search(root, value);
	if (to_remove == nullptr)
		return false;
	node* next;
	if (to_remove->left == nullptr || to_remove->right == nullptr) {
		next = (to_remove->left != nullptr) ? to_remove->left : to_remove->right;
		if (next != nullptr) // проверка на листок
			next->parent = to_remove->parent;
	}
	else {
		// 0. der Ersatzknoten ist der nächste Wert
		// Der istder wenigste bzw. der linkeste Knoten im linken Unterbaum
		next = get_min(to_remove->right);
		
		next->left = to_remove->left; // 1. установили связь с левым потомком удаляемого элемента
		to_remove->left->parent = next; // делаем это спокойно т.к. новый элемент не имеет своих левых потомков

		if (next != to_remove->right) // 2. во левом поддереве правого поддерева удаляемого элемента есть элементы:
		{								// если их нет, и так все работает 
			// 2.1 правое поддерево левого поддерево правого поддерева удаляемого элемента к этому правому поддереву
			// если таковое имеется
			if (next->right != nullptr) 
				next->right->parent = next->parent;
			next->parent->left = next->right;

			// 2.2 новый элемент, то есть следующий к правому поддереву удаляемого элемента

			next->right = to_remove->right;
			to_remove->right->parent = next;
		}
	}
	// Прикрепление нового элемента к высшему поддереву, если таковое имеется
	next->parent = to_remove->parent;
	if (root == to_remove) // проверка на наличие родителя, к которым можно присоединить дочерние ветки
		root = next;
	else {
		if (to_remove->parent->left == to_remove) // если есть родитель, то смотрим слева или справа имеет ли он элемент
			to_remove->parent->left = next;
		else if (to_remove->parent->right == to_remove)
			to_remove->parent->right = next;
	}
	delete to_remove;
	to_remove = nullptr;
	size_--;
	return true;
}

template <typename T>
bool  binary_tree<T>::search(const T& value) const {
	node* current = root;
	while (current != nullptr) {
		if (current->value == value)
			return true;
		if (value < current->value)
			current = current->left;
		else
			current = current->right;
	}
	return false;
}



template <typename T>
bool binary_tree<T>::empty() {
	return size_ == 0;
}
template <typename T>
size_t binary_tree<T>::size() {
	return size_;
}


template <typename T>
void binary_tree<T>::pre_order_traversal(vector<T>& vec) {
	pre_order_traversal(root, vec);
}

template <typename T>
void binary_tree<T>::in_order_traversal(vector<T>& vec) {
	in_order_traversal(root, vec);
}

template <typename T>
void binary_tree<T>::post_order_traversal(vector<T>& vec) {
	post_order_traversal(root, vec);
}

template <typename T>
void binary_tree<T>::pre_order_traversal(node* root, vector<T>& vec) {
	if (root == nullptr)
		return;

	vec.push_back(root->value);
	pre_order_traversal(root->left, vec);
	pre_order_traversal(root->right, vec);
}
template <typename T>
void binary_tree<T>::in_order_traversal(node* root, vector<T>& vec) {
	if (root == nullptr)
		return;
	in_order_traversal(root->left, vec);
	vec.push_back(root->value);
	in_order_traversal(root->right, vec);
	
}
template <typename T>
void binary_tree<T>::post_order_traversal(node* root, vector<T>& vec) {
	if (root == nullptr)
		return;
	post_order_traversal(root->left, vec);
	post_order_traversal(root->right, vec);
	vec.push_back(root->value);
	
}

template <typename T>
template<typename Func>
void binary_tree<T>::pre_order_traversal(node* root, Func action) {
	if (root == nullptr)
		return;

	action(root);
	pre_order_traversal(root->left, action);
	pre_order_traversal(root->right, action);
}
template <typename T>
template<typename Func>
void binary_tree<T>::in_order_traversal(node* root, Func action) {
	if (root == nullptr)
		return;
	in_order_traversal(root->left, action);
	action(root);
	in_order_traversal(root->right, action);
}
template <typename T>
template<typename Func>
void binary_tree<T>::post_order_traversal(node* root, Func action) {
	if (root == nullptr)
		return;
	post_order_traversal(root->left, action);
	post_order_traversal(root->right, action);
	action(root);
}

template <typename T>
T binary_tree<T>::get_min() {
	if (empty())
		return T();
	node* curennt = root;
	while (curennt->left != nullptr)
		curennt = curennt->left;
	return curennt->value;
}
template <typename T>
T binary_tree<T>::get_max() {
	if (empty())
		return T();
	node* curennt = root;
	while (curennt->right != nullptr)
		curennt = curennt->right;
	return curennt->value;
}


template <typename T>
void binary_tree<T>::show() {
	auto show_node_lambda = [](node*& elem) { std::cout << elem->value << " "; };
	in_order_traversal(root, show_node_lambda);
	std::cout << "\n";
}
template <typename T>
void binary_tree<T>::clear() {

	auto clear_node_lambda = [](node*& elem) { delete elem; elem = nullptr; };
	post_order_traversal(root, clear_node_lambda);
	size_ = 0;
	root = nullptr;
}


template <typename T>
binary_tree<T>::binary_tree(const binary_tree& other) : binary_tree()  // (PRE ORDER)
{
	auto copy_node_lambda = [this](node*& elem) { this->add(elem->value); };
	pre_order_traversal(other.root, copy_node_lambda);
}
template <typename T>
binary_tree<T>& binary_tree<T>::operator=(binary_tree other) // (PRE ORDER)
{
	if (&other != this) {
		swap(*this, other);
		/*clear();
		auto copy_node_lambda = [this](node*& elem) { this->add(elem->value); };
		pre_order_traversal(other.root, copy_node_lambda);*/
	}
	

	return *this;
}



template <typename T>
bool binary_tree<T>::operator==(binary_tree& other){
	if (other.size_ != this->size_)
		return false;

	return compare_trees(this, &other);
}


template <typename T>
bool binary_tree<T>::compare_trees(node* root1, node* root2) {
	if (root1 == nullptr && root2 == nullptr)
		return true;
	if (root1 == nullptr || root2 == nullptr)
		return false;
	if (root1->value != root2->value)
		return false;

	bool leftSubtrees_comparison = compare_trees(root1->left, root2->left);

	bool rightSubtrees_comparison = compare_trees(root1->right, root2->right);

	return leftSubtrees_comparison && rightSubtrees_comparison;
}

template <typename T>
bool binary_tree<T>::operator!=(binary_tree& other) {

}