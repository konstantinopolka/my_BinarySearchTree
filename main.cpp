// binary search tree.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "Header.h"
#include <vector>

using namespace std;

 void printArray(int arr[], int n)
 {
	 for (int i = 0; i < n; ++i)
		 cout << arr[i] << " ";
	 cout << "\n";
 }

int main()
{
	using std::cout;
	binary_tree<int> tree;
	tree.add(250);
	tree.add(500);
	tree.add(125);
	tree.add(188);
	tree.add(64);
	tree.add(375);
	tree.add(1000);
	tree.add(750);
	tree.add(2000);
	tree.add(4000);
	tree.add(32);
	tree.add(94);
	tree.add(160);
	tree.add(220);
	tree.add(170);


	binary_tree<int> tree1;

	tree1 = tree;
}

