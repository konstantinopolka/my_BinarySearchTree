#pragma once
#include <vector>
#include <iostream>
#include <cmath>
using std::vector;
template <typename T>
class binary_tree
{
private:
	class node;
	using action_with_node = void(*)(node*&);
public:
	node* root;

	binary_tree();
	binary_tree(const binary_tree& other); // TO DO (PRE ORDER)
	binary_tree& operator=(binary_tree other); // (PRE ORDER)
	~binary_tree(); // OK (POST ORDER)
	static void swap(binary_tree& tree1, binary_tree& tree2);
	bool operator==(binary_tree& other);
	
	bool operator!=(binary_tree& other);
	void clear();
	void add(const T& value); // OK
	bool remove(const T& value); // OK
	bool search(const T& value) const;

	void pre_order_traversal( vector<T>& vec);
	void in_order_traversal( vector<T>& vec);
	void post_order_traversal( vector<T>& vec);

	T get_min();
	T get_max();


	

	static bool compare_trees(node* root1, node* root2);

	bool empty();
	size_t size();
	void show(); // IN ORDER
	

	//1. Werte aller Blätter drucken
	void show_allLieves(); // IN ORDER


	//2. Werte aller internen Knoten ausdrucken
	void show_allInternNodes();

	//3. Werte aller Knoten mit linken Kindern ausdrucken
	void show_allNodes_with_leftKids();
	
	//4.  Werte aller Knoten mit rechten Kindern ausdrucken
	void show_allNodes_with_rightKids();

	//5. die Tiefe des Minimums 
	size_t get_deepness_of_min();

	//6. die Tiefe des Maximums
	size_t get_deepness_of_max();
	//7. die Anzahl der Elemente herausfinden
	size_t count_traversal();
	//8. die Anzahl der Blätter herausfinden
	size_t tieves_count();
	//9. die Anzahl der internen Knoten herausfinden
	size_t internNodes_count();
	//10. die Anzahl der Knoten mit zwei Kindern herausfinden
	size_t twoKidsNodes_count();
	//11. die Anzahl der Knoten mit einem Kind herausfinden
	size_t oneKidNodes_count();
	
	//16. Визначити середнє арифметичне всіх ключів.
	//17!!!. Знайти висоту дерева.
	size_t height(); // OK
	static size_t height(node* root); // OK
	//18. * У двійковому дереві пошуку знайти елемент, наступний за даними. + 
	T next(const T& value);
	//19!!!. * У двійковому дереві пошуку знайти елемент, що передує даному.
	T last(const T& value);
	//20. * У двійковому дереві пошуку видалити елемент із заданим ключем. + 
	 // bool remove(const T& value);
	 
	//21. * Відсортувати масив, використовуючи проміжне представлення у вигляді двійкової купи.

	void heapSort();
	
private:
	size_t size_;
	
	static void pre_order_traversal(node* root, vector<T>& vec);
	static void in_order_traversal(node* root, vector<T>& vec);
	static void post_order_traversal(node* root, vector<T>& vec);

	template<typename Func>
	size_t pre_order_traversal(node* root, Func action);

	template<typename Func>
	size_t in_order_traversal(node* root, Func action);

	template<typename Func>
	size_t post_order_traversal(node* root, Func action);

	size_t return_from_traversal(size_t& it, size_t& counter);

	
	static node*  get_min(node* root) {
		if (root == nullptr)
			return nullptr;
		if (root->left == nullptr)
			return root;
		return get_min(root->left);
	}

	
	static node* get_max(node* root) {
		if (root == nullptr)
			return nullptr;
		if (root->right == nullptr)
			return root;
		return get_max(root->right);
	}

	static node* search(node* root, const T& value) {
		if (root == nullptr)
			return nullptr;
		if (root->value == value)
			return root;

		if (value < root->value)
			return search(root->left, value);
		else
			return search(root->right, value);
	}
	

	static bool isIntern(node*&);
	static bool has_parent(node*&);
	static bool has_leftKid( node*&);
	static bool has_rightKid( node*&);
	static bool has_kid(node*&);
	static bool has_twoKids( node*&);
	static bool isTief(node*& root);
};




//Реалізувати збалансоване двійкове дерево пошуку :
//1. АВЛ - дерева
//2. Червоно - чорні дерева
//3. Декартові дерева(рандомізовані дерева пошуку)


// TO DO понять как сравнивать любые обьекты в С++ 