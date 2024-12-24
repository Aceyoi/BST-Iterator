//���������� ���� ���-22
#pragma once

#include <iostream>
#include <chrono>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

// ��������� ����� ���� ������
template <typename T>
class Node {
public:
    T value;         // �������� ����
    Node<T>* left;        // ����� �������
    Node<T>* right;       // ������ �������

    // ����������� ����
    Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

// ��������� ����� ��� ��������� ������ ������
template <typename T>
class BST {
private:
    Node<T>* root; // ������ ������

    // O(log2n) � ��� ����������������� ������  
    // ����� ������� �������� � ��������� ������ ������                                                             
    Node<T>* insert(Node<T>* node, T value) {
        if (!node) {
            return new Node<T>(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // ����� ��� ������ ������ � ������� �����������
    void traverseInOrder(Node<T>* node) {
        if (node) {
            traverseInOrder(node->left);
            cout << node->value << " ";
            traverseInOrder(node->right);
        }
    }

    // ����� ��� �������� ������� ���� � ������
    bool search(Node<T>* node, T value) {
        if (!node) {
            return false;
        }
        if (value == node->value) {
            return true;
        }
        else if (value < node->value) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    // ����� ��� ������� ���� � ������
    Node<T>* remove(Node<T>* node, T value) {
        if (!node) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = remove(node->left, value);
        }
        else if (value > node->value) {
            node->right = remove(node->right, value);
        }
        else {
            if (!node->left) {
                Node<T>* rightChild = node->right;
                delete node;
                return rightChild;
            }
            else if (!node->right) {
                Node<T>* leftChild = node->left;
                delete node;
                return leftChild;
            }
            else {
                Node<T>* successorParent = node;
                Node<T>* successor = node->right;
                while (successor->left) {
                    successorParent = successor;
                    successor = successor->left;
                }
                node->value = successor->value;
                if (successorParent->left == successor) {
                    successorParent->left = successor->right;
                }
                else {
                    successorParent->right = successor->right;
                }
                delete successor;
            }
        }
        return node;
    }
public:
    // ����������� ��� ����������
    BST() : root(nullptr) {}

    // ����� ������� �������� � ������
    void insert(T value) {
        root = insert(root, value);
    }

    // ����� ��� ������ �������� ������ � ������� ����������� (in order)
    void traverseInOrder() {
        traverseInOrder(root);
        cout << endl;
    }

    // ����� ������ (�������� ���� �� ��������) �������� � ������
    bool search(T value) {
        return search(root, value);
    }

    // ����� �������� �������� ������
    void remove(T value) {
        root = remove(root, value);
    }

    // ����� ��������� ����� ��� ������(LNR) ��� ��������� ������ ������
    class Iterator {
    private:
        stack<Node<T>*> nodeStack; // ���� ��� �������� ������ �� ������ ������

        // ����� ������ ������ 
        void pushLeft(Node<T>* node) {
            while (node) {
                nodeStack.push(node);
                node = node->left;
            }
        }

    public:
        // �����������
        Iterator(Node<T>* root) {
            pushLeft(root);
        }

        // ����� �������� ���� �� ��������� �������
        bool hasNext() {
            return !nodeStack.empty();
        }

        // ����� ������ BST ������ �� �������� LNR
        T next() {
            Node<T>* current = nodeStack.top();
            nodeStack.pop();
            T value = current->value;
            if (current->right) {
                pushLeft(current->right);
            }
            return value;
        }
    };

    // ����� ������ ������������ ������ ���������
    Iterator getIterator() {
        return Iterator(root);
    }
};