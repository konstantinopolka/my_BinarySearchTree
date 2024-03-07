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
	

	//1. � ��������� ����� ������ ������������ �� �����, �� �������� � ����.
	//2. � ��������� ����� ������ ������������ �� �����, �� �������� � �������� ������.
	//3. � ��������� ����� ������ ������������ �� �����, �� �������� � ������, � ���� � ����� ���� ���.
	//4. � ��������� ����� ������ ������������ �� �����, �� �������� � ������, � ���� � ����� ������ ���.
	//5. ������ ������� ���������� ��������
	//6. ������ ������� ������������� ��������.
	//7. ��������� ������� �������� � �����.
	//8. ��������� ������� ����� � �����.
	//9. ��������� ������� �������� �����.
	//10. ��������� ������� �����, � ���� ��� ����.
	//11. ��������� ������� �����, � ���� ���� ���.
	//12. ��������� ������� �����, � ���� � ���� ���.
	//13. ��������� ������� �����, � ���� � ������ ���.
	//14. ��������� ������� �����, � ���� � ����� ���� ���.
	//15. ��������� ������� �����, � ���� � ����� ������ ���.
	//16. ��������� ������ ����������� ��� ������.
	//17. ������ ������ ������.
	//18. * � ��������� ����� ������ ������ �������, ��������� �� ������.
	//19. * � ��������� ����� ������ ������ �������, �� ������ ������.
	//20. * � ��������� ����� ������ �������� ������� �� ������� ������.
	//21. * ³���������� �����, �������������� ������� ������������� � ������ ������� ����.

	
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




//���������� ������������ ������� ������ ������ :
//1. ��� - ������
//2. ������� - ���� ������
//3. �������� ������(����������� ������ ������)


// TO DO ������ ��� ���������� ����� ������� � �++ 