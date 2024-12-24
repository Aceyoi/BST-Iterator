//Сапожников Юрий ИВТ-22
#pragma once

#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include <stack>
#include "TreeNode.Class.h"

using namespace std;

// Шаблонный класс узла дерева
template <typename T>
class Node {
public:
    T value;         // Значение узла
    Node<T>* left;        // Левый потомок
    Node<T>* right;       // Правый потомок

    // Конструктор узла
    Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

// Шаблонный класс для бинарного дерева поиска
template <typename T>
class BST {
private:
    BinSearchNode<T>* root; // Корень дерева

    //Node<T>* root; // Корень дерева

    //// O(log2n) — для сбалансированного дерева  
    //// Метод вставки значения в бинарного дерева поиска                                                             
    //Node<T>* insert(Node<T>* node, T value) {
    //    if (!node) {
    //        return new Node<T>(value);
    //    }
    //    if (value < node->value) {
    //        node->left = insert(node->left, value);
    //    }
    //    else if (value > node->value) {
    //        node->right = insert(node->right, value);
    //    }
    //    return node;
    //}

    //// Метод для обхода дерева в порядке возрастания
    //void traverseInOrder(Node<T>* node) {
    //    if (node) {
    //        traverseInOrder(node->left);
    //        cout << node->value << " ";
    //        traverseInOrder(node->right);
    //    }
    //}

    //// Метод для проверки наличия узла в дереве
    //bool search(Node<T>* node, T value) {
    //    if (!node) {
    //        return false;
    //    }
    //    if (value == node->value) {
    //        return true;
    //    }
    //    else if (value < node->value) {
    //        return search(node->left, value);
    //    }
    //    else {
    //        return search(node->right, value);
    //    }
    //}

    //// Метод для удаленя узла в дереве
    //Node<T>* remove(Node<T>* node, T value) {
    //    if (!node) {
    //        return nullptr;
    //    }

    //    if (value < node->value) {
    //        node->left = remove(node->left, value);
    //    }
    //    else if (value > node->value) {
    //        node->right = remove(node->right, value);
    //    }
    //    else {
    //        if (!node->left) {
    //            Node<T>* rightChild = node->right;
    //            delete node;
    //            return rightChild;
    //        }
    //        else if (!node->right) {
    //            Node<T>* leftChild = node->left;
    //            delete node;
    //            return leftChild;
    //        }
    //        else {
    //            Node<T>* successorParent = node;
    //            Node<T>* successor = node->right;
    //            while (successor->left) {
    //                successorParent = successor;
    //                successor = successor->left;
    //            }
    //            node->value = successor->value;
    //            if (successorParent->left == successor) {
    //                successorParent->left = successor->right;
    //            }
    //            else {
    //                successorParent->right = successor->right;
    //            }
    //            delete successor;
    //        }
    //    }
    //    return node;
    //}
public:
    // Конструктор без параметров
    BST() : root(nullptr) {}

    // Метод вставки значения в дерево
    void insert(T value) {
        if (!root) {
            root = new BinSearchNode<T>(value);
        }
        else {
            root->popbsn(value);
        }
    }

    // Метод для вывода значений дерева в порядке возрастания (in order)
    void traverseInOrder() {
        if (root) {
            root->traverseInOrder();
        }
        cout << endl;
    }

    // Метод поиска (проверки если ли значение) значения в дереве
    bool search(T value) {
        if (root) {
            return root->searchbool(value);
        }
        return false;
    }

    // Метод удаления значения дерева
    void remove(T value) {
        if (root) {
            root->del(value);
        }
    }

    // Класс итератора имеет тип обхода(LNR) для бинарного дерева поиска
    class Iterator {
    private:
        stack<BinSearchNode<T>*> nodeStack; // Стек для хранения данных об обходе дерева

        // Метод левого обхода 
        void pushLeft(BinSearchNode<T>* node) {
            while (node) {
                nodeStack.push(node);
                node = static_cast<BinSearchNode<T>*>(node->left);
            }
        }

    public:
        // Конструктор
        Iterator(BinSearchNode<T>* root) {
            pushLeft(root);
        }

        // Метод проверки если ли следующий элемент
        bool hasNext() {
            return !nodeStack.empty();
        }

        // Метод обхода BST дерева по принципу LNR
        T next() {
            BinSearchNode<T>* current = nodeStack.top();
            nodeStack.pop();
            T value = current->value;
            if (current->right) {
                pushLeft(static_cast<BinSearchNode<T>*>(current->right));
            }
            return value;
        }
    };

    // Метод дерева возвращающий начало итератора
    Iterator getIterator() {
        return Iterator(root);
    }
};