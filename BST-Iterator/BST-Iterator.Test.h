//Сапожников Юрий ИВТ-22
#pragma once

#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>	
#include "BST-Iterator.Class.h"

using namespace std;

// Тестирование
void testcheck() {

    BST<int> tesrtree;

    tesrtree.insert(10);
    tesrtree.insert(5);
    tesrtree.insert(20);
    tesrtree.insert(3);
    tesrtree.insert(7);

    assert(tesrtree.search(10) == true);
    assert(tesrtree.search(5) == true);
    assert(tesrtree.search(20) == true);
    assert(tesrtree.search(3) == true);
    assert(tesrtree.search(7) == true);
    assert(tesrtree.search(15) == false);

    auto it = tesrtree.getIterator();
    assert(it.hasNext() == true);
    assert(it.next() == 3);
    assert(it.next() == 5);
    assert(it.next() == 7);
    assert(it.next() == 10);
    assert(it.next() == 20);
    assert(it.hasNext() == false);

    tesrtree.remove(3);
    assert(tesrtree.search(3) == false);

    tesrtree.remove(5);
    assert(tesrtree.search(5) == false);

    tesrtree.remove(7);
    assert(tesrtree.search(7) == false);

};
