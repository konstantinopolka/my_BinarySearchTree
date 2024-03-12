#pragma once
#include <vector>
#include <cmath>
using std::vector;
using std::max;
using std::min;

template <typename T>
class heap {
private:
	class node;
public:
	heap(const vector<T>&);
	~heap(); // OK (POST ORDER)
	void max_heap();
	void min_heap();
	vector<T> descendingSort();
	vector<T> ascendingSort();
private:
	size_t size;
	node* root;
	template<typename Func>
	size_t post_order_traversal(node* root, Func action);
	void clear();
	static void max_heap(node*);
	static void min_heap(node*);
	void add(const T& value);

	void delete_root();
	static bool isIntern(node*&);
	static bool has_parent(node*&);
	static bool has_leftKid(node*&);
	static bool has_rightKid(node*&);
	static bool has_kid(node*&);
	static bool has_twoKids(node*&);
	static bool isTief(node*& root);

	
};

