#pragma once
#include <vector>
#include <iostream>
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
	

	//1. У двійковому дереві пошуку роздрукувати всі ключі, що містяться в листі.
	//2. У двійковому дереві пошуку роздрукувати всі ключі, що містяться у внутрішніх вузлах.
	//3. У двійковому дереві пошуку роздрукувати всі ключі, що містяться у вузлах, у яких є тільки лівий син.
	//4. У двійковому дереві пошуку роздрукувати всі ключі, що містяться у вузлах, у яких є тільки правий син.
	//5. Знайти глибину мінімального елемента
	//6. Знайти глибину максимального елемента.
	//7. Визначити кількість елементів в дереві.
	//8. Визначити кількість листя в дереві.
	//9. Визначити кількість внутрішніх вузлів.
	//10. Визначити кількість вузлів, у яких два сини.
	//11. Визначити кількість вузлів, у яких один син.
	//12. Визначити кількість вузлів, у яких є лівий син.
	//13. Визначити кількість вузлів, у яких є правий син.
	//14. Визначити кількість вузлів, у яких є тільки лівий син.
	//15. Визначити кількість вузлів, у яких є тільки правий син.
	//16. Визначити середнє арифметичне всіх ключів.
	//17. Знайти висоту дерева.
	//18. * У двійковому дереві пошуку знайти елемент, наступний за даними.
	//19. * У двійковому дереві пошуку знайти елемент, що передує даному.
	//20. * У двійковому дереві пошуку видалити елемент із заданим ключем.
	//21. * Відсортувати масив, використовуючи проміжне представлення у вигляді двійкової купи.

	
private:
	size_t size_;
	
	static void pre_order_traversal(node* root, vector<T>& vec);
	static void in_order_traversal(node* root, vector<T>& vec);
	static void post_order_traversal(node* root, vector<T>& vec);

	template<typename Func>
	void pre_order_traversal(node* root, Func action);

	template<typename Func>
	void in_order_traversal(node* root, Func action);

	template<typename Func>
	void post_order_traversal(node* root, Func action);

	
	static node*  get_min(node* root) {
		if (root == nullptr)
			return nullptr;
		if (root->left == nullptr)
			return root;
		return get_min(root->left);
	}

	
	static node*  get_max(node* root) {
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
	

	
};




//Реалізувати збалансоване двійкове дерево пошуку :
//1. АВЛ - дерева
//2. Червоно - чорні дерева
//3. Декартові дерева(рандомізовані дерева пошуку)


// TO DO понять как сравнивать любые обьекты в С++ 