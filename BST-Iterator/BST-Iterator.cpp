//Сапожников Юрий ИВТ-22
#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include "BST-Iterator.Class.h"
#include "BST-Iterator.Test.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "Russian");

	testcheck();

	BST<int> tree;

	tree.insert(5);
	tree.insert(10);
	tree.insert(3);
	tree.insert(7);
	tree.insert(12);

	cout << "Вывод дерева:" << endl;
	tree.traverseInOrder();

	cout << "Вывод итератора:" << endl;
	auto it = tree.getIterator();
	while (it.hasNext()) {
		cout << it.next() << " ";
	}

	return 0;
}
