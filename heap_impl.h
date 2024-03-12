#pragma once
#include "heap.h"

template <typename T>
class heap<T>::node
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




template <typename T>
heap<T>::node::node() : value(T()), left(nullptr), right(nullptr)
{}
template <typename T>
heap<T>::node::node(T value, node* left, node* right, node* parent) : value(value), left(left), right(right), parent(parent)
{}
template <typename T>
inline heap<T>::node::node(T value, node* parent) : value(value), left(nullptr), right(nullptr), parent(parent)
{}
template <typename T>
inline heap<T>::node::node(node* left, node* right) : value(T()), left(left), right(right), parent(nullptr)
{}

template <typename T>
inline heap<T>::node::node(T value) : value(value), left(nullptr), right(nullptr), parent(nullptr)
{}

template <typename T>
heap<T>::node::~node()
{}




template <typename T>
heap<T>::~heap()
{
	clear();
}


template <typename T>
void heap<T>::clear() {

	auto clear_node_lambda = [](node*& elem, size_t& counter)
	{
		delete elem;
		elem = nullptr;
		counter++;
	};
	post_order_traversal(root, clear_node_lambda);
	size = 0;
	root = nullptr;
}

template<typename T>
inline void heap<T>::max_heap()
{
	max_heap(root);
}


template<typename T>
inline void heap<T>::max_heap(node* root)
{
	using std::swap;
	if (isTief(root))
		return;

	if(has_leftKid(root))
		if (has_kid(root->left))
			max_heap(root->left);

	if(has_rightKid(root))
		if (has_kid(root->right))
			max_heap(root->right);

	T max_;

	if (has_twoKids(root)) {
		max_ = max(root->value, max(root->left->value, root->right->value));
		if (max_ == root->left->value)
			swap(root->value, root->left->value);

		if(max_ == root->right->value)
			swap(root->value, root->right->value);
	}
	else if (has_leftKid(root)) {
		max_ = max(root->value, root->left->value);
		if (max_ == root->left->value)
			swap(root->value, root->left->value);
		}
	else if (has_rightKid(root)) {
			max_ = max(root->value, root->right->value);
		if (max_ == root->right->value)
			swap(root->value, root->right->value);
	}
}

template<typename T>
inline void heap<T>::delete_root()
{
	if (root == nullptr)
		return;

	using std::swap;

	node* current = root;
	if (!has_kid(root)) {
		root = nullptr;
	}
	else
	{
		if (has_leftKid(root)) {
			while (current->left != nullptr)
				current = current->left;

			if (current->right != nullptr) {
				current = current->right;
				current->parent->right = nullptr;
			}
			else
				current->parent->left = nullptr;
		}
			

		else if (has_rightKid(root)) {
			while (current->right != nullptr)
				current = current->right;

			if (current->left != nullptr) {
				current = current->left;
				current->parent->left = nullptr;
			}
			else
				current->parent->right = nullptr;
			
		}
		swap(root->value, current->value);
	}

	
	size--;
	delete current;
	current = nullptr;
}

template<typename T>
void heap<T>::min_heap(node* root) {
	using std::swap;
	if (isTief(root))
		return;

	if (has_leftKid(root))
		if (has_kid(root->left))
			min_heap(root->left);

	if (has_rightKid(root))
		if (has_kid(root->right))
			min_heap(root->right);

	T min_;

	if (has_twoKids(root)) {
		min_ = min(root->value, min(root->left->value, root->right->value));
		if (min_ == root->left->value)
			swap(root->value, root->left->value);

		if (min_ == root->right->value)
			swap(root->value, root->right->value);
	}
	else if (has_leftKid(root)) {
		min_ = min(root->value, root->left->value);
		if (min_ == root->left->value)
			swap(root->value, root->left->value);
	}
	else if (has_rightKid(root)) {
		min_ = min(root->value, root->right->value);
		if (min_ == root->right->value)
			swap(root->value, root->right->value);
	}
}

template<typename T>
void heap<T>::min_heap() {
	min_heap(root);
}

template<typename T>
vector<T> heap<T>::descendingSort() {
	vector<T> to_return;
	while (size) {
		min_heap();
		to_return.push_back(root->value);
		delete_root();
	}
	return to_return;
}

template<typename T>
inline vector<T> heap<T>::ascendingSort()
{
	vector<T> to_return;
	while (size) {
		max_heap();
		to_return.push_back(root->value);
		delete_root();
	}
	return to_return;
}


template <typename T>
template<typename Func>
size_t heap<T>::post_order_traversal(node* root, Func action) {
	static size_t it = 0;
	static size_t counter = 0;
	if (root == nullptr)
		return 0;
	it++;
	post_order_traversal(root->left, action);
	post_order_traversal(root->right, action);
	action(root, counter);


	if (it == size) {
		it = 0;
		size_t to_return = counter;
		counter = 0;
		return to_return;
	}
	else
		return 0;
}






template<typename T>
bool heap<T>::isIntern(node*& root) {
	return has_parent(root) && has_kid(root);
}

template<typename T>
bool heap<T>::isTief(node*& root) {
	return !has_kid(root);
}
template<typename T>
bool heap<T>::has_parent(node*& root) {
	return root->parent != nullptr;
}

template<typename T>
bool heap<T>::has_leftKid(node*& root) {
	return root->left != nullptr;
}

template<typename T>
bool heap<T>::has_rightKid(node*& root) {
	return root->right != nullptr;
}
template<typename T>
bool heap<T>::has_kid(node*& root) {
	return has_leftKid(root) || has_rightKid(root);
}
template<typename T>
bool heap<T>::has_twoKids(node*& root) {
	return has_leftKid(root) && has_rightKid(root);
}



template<typename T>
heap<T>::heap(const vector<T>& arr) : root(nullptr), size(arr.size()) {
	// Erstellen der Heap-Struktur aus dem Array
	for (size_t i = 0; i < arr.size(); ++i) {
		add(arr[i]);
	}
}


template<typename T>
void heap<T>::add(const T& value) {
	if (root == nullptr) {
		root = new node(value);
	}
	else {
		// Suche nach der Position zum Einfügen des neuen Werts
		// Beachte, dass wir hier die Indexierung 0-basiert verwenden
		// Wenn wir also an einem Knoten i arbeiten, dann haben sein linkes Kind
		// den Index 2*i+1 und das rechte Kind den Index 2*i+2
		vector<node*> levelNodes; // Knoten auf dem aktuellen Level
		vector<node*> nextLevelNodes; // Knoten auf dem nächsten Level

		// Beginnen beim Wurzelknoten
		levelNodes.push_back(root);

		while (!levelNodes.empty()) {
			for (auto& n : levelNodes) {
				// Überprüfen, ob das linke Kind vorhanden ist
				if (n->left == nullptr) {
					n->left = new node(value, n);
					return; // Einfügen abgeschlossen
				}
				// Überprüfen, ob das rechte Kind vorhanden ist
				else if (n->right == nullptr) {
					n->right = new node(value, n);
					return; // Einfügen abgeschlossen
				}
				else {
					// Wenn beide Kinder vorhanden sind, fügen wir die Kinder in die nächste Ebene ein
					nextLevelNodes.push_back(n->left);
					nextLevelNodes.push_back(n->right);
				}
			}
			// Setze die aktuelle Ebene auf die nächste Ebene
			levelNodes = std::move(nextLevelNodes);
			nextLevelNodes.clear();
		}
	}
}