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
size_t binary_tree<T>::pre_order_traversal(node* root, Func action) {
	static size_t it = 0;
	static size_t counter = 0;
	if (root == nullptr)
		return 0;
	it++;
	action(root, counter);
	pre_order_traversal(root->left, action);
	pre_order_traversal(root->right, action);

	if (it == size_) {
		it = 0;
		size_t to_return = counter;
		counter = 0;
		return to_return;
	}
	else
		return 0;
}
template <typename T>
template<typename Func>
size_t binary_tree<T>::in_order_traversal(node* root, Func action) {
	static size_t it = 0;
	static size_t counter = 0;
	if (root == nullptr)
		return 0;
	it++;
	in_order_traversal(root->left, action);
	action(root, counter);
	in_order_traversal(root->right, action);

	if (it == size_) {
		size_t to_return = counter;
		//counter = 0;
		//it = 0;
		return to_return;
	}
	else
		return 0;
}
template <typename T>
template<typename Func>
size_t binary_tree<T>::post_order_traversal(node* root, Func action) {
	static size_t it = 0;
	static size_t counter = 0;
	if (root == nullptr)
		return 0;
	it++;
	post_order_traversal(root->left, action);
	post_order_traversal(root->right, action);
	action(root, counter);
	
	
	if (it == size_) {
		it = 0;
		size_t to_return = counter;
		counter = 0;
		return to_return;
	}
	else
		return 0;
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
size_t binary_tree<T>::get_deepness_of_min() {
	size_t deepness = 0;
	if (!empty()) {
		node* curennt = root;
		while (curennt->left != nullptr) {
			curennt = curennt->left;
			deepness++;
		}	
	}
	return deepness;
	
}
template <typename T>
size_t binary_tree<T>::get_deepness_of_max() {
	size_t deepness = 0;
	if (!empty()) {
		node* curennt = root;
		while (curennt->right != nullptr) {
			curennt = curennt->right;
			deepness++;
		}
	}
	return deepness;
}


template <typename T>
void binary_tree<T>::show() {
	auto show_node_lambda = [](node*& elem, size_t& counter) -> bool
	{ 
		std::cout << elem->value << " "; 
		counter++;
		return true;
	};
	in_order_traversal(root, show_node_lambda);
	std::cout << "\n";
}
template <typename T>
void binary_tree<T>::clear() {

	auto clear_node_lambda = [](node*& elem, size_t& counter)
	{ 
		delete elem;
		elem = nullptr;
		counter++;
	};
	post_order_traversal(root, clear_node_lambda);
	size_ = 0;
	root = nullptr;
}


template <typename T>
binary_tree<T>::binary_tree(const binary_tree& other) : binary_tree()  // (PRE ORDER)
{
	auto copy_node_lambda = [this](node*& elem, size_t& counter)
	{ 
		this->add(elem->value);
		counter++;
	};
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

	return compare_trees(this->root, other.root);
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
	return !operator==(other);
}

template <typename T>
void  binary_tree<T>::show_allLieves() {
	auto show_lief_lambda = [this](node*& elem, size_t& counter)  -> bool
	{ 
		if (!has_kid(elem)) {
			std::cout << elem->value << " ";
			counter++;
			return true;
		}
		return false;
	};
	in_order_traversal(root, show_lief_lambda);
	std::cout << "\n";
}

template<typename T>
inline void binary_tree<T>::show_allInternNodes()
{
	auto show_lief_lambda = [this](node*& elem, size_t& counter)
	{
		if (isIntern()) {
			std::cout << elem->value << " ";
			counter++;
			return true;
		}
		return false;
			
	};
	in_order_traversal(root, show_lief_lambda);
	std::cout << "\n";
}

template<typename T>
inline void binary_tree<T>::show_allNodes_with_leftKids()
{
	auto show_lief_lambda = [this](node*& elem, size_t& counter) -> bool
	{
		if (has_leftKid(elem))
		{
			std::cout << elem->value << " ";
			counter++;
			return true;
		}
		return false;
			
	};
	in_order_traversal(root, show_lief_lambda);
	std::cout << "\n";
}

template<typename T>
inline void binary_tree<T>::show_allNodes_with_rightKids()
{
	auto show_lief_lambda = [this](node*& elem, size_t& counter) -> bool
	{
		if (has_rightKid(elem)) {
			std::cout << elem->value << " ";
			counter++;
			return true;
		}
		return false;
			
	};
	in_order_traversal(root, show_lief_lambda);
	std::cout << "\n";
}


template<typename T>
bool binary_tree<T>::isIntern(node*& root) {
	return has_parent(root) && has_kid(root);
}

template<typename T>
bool binary_tree<T>::isTief(node*& root) {
	return !has_kid(root);
}
template<typename T>
bool binary_tree<T>::has_parent(node*& root) {
	return root->parent != nullptr;
}

template<typename T>
bool binary_tree<T>::has_leftKid( node*& root) {
	return root->left != nullptr;
}

template<typename T>
bool binary_tree<T>::has_rightKid( node*& root) {
	return root->right != nullptr;
}
template<typename T>
bool binary_tree<T>::has_kid(node*& root) {
	return has_leftKid(root) || has_rightKid(root);
}
template<typename T>
bool binary_tree<T>::has_twoKids( node*& root) {
	return has_leftKid(root) && has_rightKid(root);
}


template<typename T>
size_t binary_tree<T>::count_traversal() {
	auto show_lief_lambda = [this](node*& elem, size_t& counter) {counter++;};
	return in_order_traversal(root, show_lief_lambda);
}

template<typename T>
size_t binary_tree<T>::tieves_count() {
	auto show_lief_lambda = [this](node*& elem, size_t& counter) -> bool
	{
		if (!has_kid(elem))
		{
			counter++;
			return true;
		}
		return false;

	};
	return in_order_traversal(root, show_lief_lambda);
}

template<typename T>
size_t binary_tree<T>::internNodes_count() {
	auto show_lief_lambda = [this](node*& elem, size_t& counter) -> bool
	{
		if (isIntern(elem))
		{
			counter++;
			return true;
		}
		return false;

	};
	return in_order_traversal(root, show_lief_lambda);
}

template<typename T>
size_t binary_tree<T>::twoKidsNodes_count() {
	auto show_lief_lambda = [this](node*& elem, size_t& counter) -> bool
	{
		if (has_twoKids(elem))
		{
			counter++;
			return true;
		}
		return false;

	};
	return in_order_traversal(root, show_lief_lambda);
}

template<typename T>
size_t binary_tree<T>::oneKidNodes_count() {
	auto show_lief_lambda = [this](node*& elem, size_t& counter) -> bool
	{
		if (has_kid(elem))
		{
			counter++;
			return true;
		}
		return false;

	};
	return in_order_traversal(root, show_lief_lambda);
}



//18. * У двійковому дереві пошуку знайти елемент, наступний за даними. + 
template<typename T>
T binary_tree<T>::next(const T& value) {
	node* searched = search(root, value);
	if (searched != nullptr) {
		if (searched->right != nullptr)
			return get_min(searched->right)->value;
		if (searched->parent != nullptr)
			if(searched = searched->parent->left)
				return searched->parent->value;
	}
	return T();
}
//19!!!. * У двійковому дереві пошуку знайти елемент, що передує даному.
template<typename T>
T binary_tree<T>::last(const T& value) {
	node* searched = search(root, value);
	if (searched != nullptr) {
		if (searched->left != nullptr)
			return get_max(searched->left)->value;
		if (searched->parent != nullptr)
			if (searched = searched->parent->right)
				return searched->parent->value;
	}
	return T();
}


template<typename T>
size_t binary_tree<T>::height() {
	return height(root);
}
template<typename T>
size_t  binary_tree<T>::height(node* root) {
	if (root == nullptr)
		return 0;
	if (isTief(root))
		return 1;
	return 1 + std::max(height(root->left), height(root->right));
}