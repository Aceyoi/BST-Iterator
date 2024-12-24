//Сапожников Юрий ИВТ-22
#pragma once

#include<exception>
#include <iostream>
#include <vector>

using namespace std;

//Шаблонный класс узела дерева
template<typename T>
class TreeNode {  //Название класса
public:
    T value;            // Хранимое значение узла                                                              
    TreeNode<T>* left;  // Указатель на левую ветку
    TreeNode<T>* right; // Указатель на правую ветку

    ///Конструктор без параметров
    TreeNode() {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    //Конструктор с одним параметрами
    // val - Корень дерева
    TreeNode(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    //Конструктор с параметрами
    // val - Корень дерева
    // left - Указатель на левую ветку
    // right - Указатель на правую ветку
    TreeNode(T val, TreeNode<T>* left, TreeNode<T>* right) {
        this->value = val;
        this->left = left;
        this->right = right;
    }

    // Вспомогательная функция для отображения дерева (Симметричный обход)
    void printTree(int level = 0) const {
        if (right != nullptr) {
            right->printTree(level + 1);  // Рекурсивный вывод правого поддерева
        }
        for (int i = 0; i < level; ++i) {
            cout << "    ";  // Отступ для уровня дерева
        }
        cout << value << endl;  // Вывод значения узла
        if (left != nullptr) {
            left->printTree(level + 1);  // Рекурсивный вывод левого поддерева
        }
    }

    // Проверка, пустое ли дерево
    bool isEmpty() const {
        if (value == T{} && left == nullptr && right == nullptr)
            return true;
        else 
            return false;
    }

    // Удаление всех узлов
    void deleteTree() {
        if (left != nullptr) {
            left->deleteTree();  // Рекурсивное удаление левого поддерева        
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            right->deleteTree();  // Рекурсивное удаление правого поддерева
            delete right;
            right = nullptr;
        }
        if (left == nullptr && right == nullptr) {
            value = 0;
        }
    }

    // Симметричный обход (LNR) // Вывод в виде массива
    void traverseInOrder() {
        if (left != nullptr) {
            left->traverseInOrder();  // Левая часть
        }
        cout << value << " ";  // Вывод
        if (right != nullptr) {
            right->traverseInOrder();  // Правая часть
        }
    }

    // Прямой обход (NLR) // Вывод в виде массива
    void traversePreOrder() {
        cout << value << " ";  // Вывод значения текущего узла
        if (left != nullptr) {
            left->traversePreOrder();  // Рекурсивный обход левого поддерева
        }
        if (right != nullptr) {
            right->traversePreOrder();  // Рекурсивный обход правого поддерева
        }
    }

    // Обратный обход (LRN) // Вывод в виде массива
    void traversePostOrder() {
        if (left != nullptr) {
            left->traversePostOrder();  // Левая часть
        }
        if (right != nullptr) {
            right->traversePostOrder();  // Правая часть
        }
        cout << value << " ";  // Вывод
    }

    // Подсчёт количества узлов в дереве  
    int countNodes() {
        if (isEmpty() == true) {
            return 0;
        }
        else {

            int count = 1;  // Считаем корень
            if (left != nullptr) {
                count += left->countNodes();  // Подсчёт в левой части
            }
            if (right != nullptr) {
                count += right->countNodes();  // Подсчёт в правой части
            }
            return count;
        }
    }

    // Определение глубины дерева
    int depth() {
        if (isEmpty() == true) {
            return -1;
        }
        else {

            int leftDepth = left ? left->depth() : 0;
            int rightDepth = right ? right->depth() : 0;
            return 1 + max(leftDepth, rightDepth);
        }
    }

    // Поверхностное копирование
    TreeNode<T>* easycopy() {
        return this;
    }

    // Глубокое копирование
    TreeNode<T>* deepcopy() {
        TreeNode<T>* newTreeNode = new TreeNode<T>(value);  // Копируем значение текущего узла        
        if (left != nullptr) {
            newTreeNode->left = left->deepcopy();  // Рекурсивно копируем левое поддерево
        }
        if (right != nullptr) {
            newTreeNode->right = right->deepcopy();  // Рекурсивно копируем правое поддерево
        }
        return newTreeNode;
    }

    // Метод для заполнения векторного массива значениями дерева в порядке LNR (In-order обход)
    void TreeArray(vector<T>& arr) {


        if (left != nullptr) {
            left->TreeArray(arr);  // Рекурсивный обход левого поддерева
        }

        arr.push_back(value);  // Добавляем значение текущего узла

        if (right != nullptr) {
            right->TreeArray(arr);  // Рекурсивный обход правого поддерева
        }
    }
};    

//Шаблонный класс узела двоичного дерева
template<typename T>
class BinTreeNode : public TreeNode<T> {  //Название класса
public:

    //Конструктор с одним параметрами
    // val - Корень дерева
    BinTreeNode(T val){
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    // Вставка значения в дерево  
    void popbtn(T val) {
        if (this->left == nullptr) {
            this->left = new BinTreeNode<T>(val);  // Вставляем в левую ветку
        }
        else {
        if (this->right == nullptr) {
            this->right = new BinTreeNode<T>(val);  // Вставляем в правую ветку
        }
        else {
            static_cast<BinTreeNode<T>*>(this->left)->popbtn(val);
        }}
    }
};

//Шаблонный класс узела дерева поиска
template<typename T>
class BinSearchNode : public TreeNode<T> {  //Название класса
public:

    //Конструктор с одним параметрами
    // val - Корень дерева
    BinSearchNode(T val) {
        this->value = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    // O(n) — для несбалансированного дерева
    // O(log2n) — для сбалансированного дерева  
    // Вставка значения в дерево поиска                                                               
    void popbsn(T val) {
        if (val < this->value) {  // Если значение меньше текущего, идем в левую ветку
            if (this->left == nullptr) {
                this->left = new BinSearchNode<T>(val);  // Вставляем в левую ветку, если она пуста
            }
            else {
                static_cast<BinSearchNode<T>*>(this->left)->popbsn(val);  // Рекурсивная вставка в левое поддерево
                /*
                Оператор static_cast использовать преобразование указателя в базовый класс в указатель на производный класс
                */
            }
        }
        else 
            if (val > this->value) {  // Если значение больше текущего, идем в правую ветку
            if (this->right == nullptr) {
                this->right = new BinSearchNode<T>(val);  // Вставляем в правую ветку, если она пуста
            }
            else {
                static_cast<BinSearchNode<T>*>(this->right)->popbsn(val);  // Рекурсивная вставка в правое поддерево
            }
        }
    }

    // O(n) — для не сбалансированного дерева
    // O(log2n) — для сбалансированного дерева
    T successor(T val) {
        T bigval;  // Переменная для хранения преемника
        bool found = false;  // Флаг для отслеживания, был ли найден узел с val
        BinSearchNode<T>* current = this;  // Начинаем с текущего узла

        // Итеративный поиск значения и потенциального преемника
        while (current != nullptr) {
            if (val < current->value) {
                // Если значение меньше текущего, запоминаем текущий элемент как возможного преемника
                bigval = current->value;
                current = static_cast<BinSearchNode<T>*>(current->left);
            }
            else if (val > current->value) {
                // Если значение больше текущего, идём вправо
                current = static_cast<BinSearchNode<T>*>(current->right);
            }
            else {
                // Узел с искомым значением найден  
                found = true;///                        
                if (current->right != nullptr) {
                    // Если есть правое поддерево, находим минимальный элемент в нём
                    return findMinValue(static_cast<BinSearchNode<T>*>(current->right));

                }
                break;
            }
        }
        if (found == true) {
            return bigval;
        }
        else {
            return val;
        }
    }

    // Вспомогательный метод для нахождения минимального значения в поддереве
    T findMinValue(BinSearchNode<T>* node) {
        while (node->left != nullptr) {
            node = static_cast<BinSearchNode<T>*>(node->left);
        }
        return node->value;
    }

    // O(n) — для несбалансированного дерева
    // O(log2n) — для сбалансированного дерева
    // Метод для поиска значения в дереве поиска (используется при удалении)
    T search(T val) {
        // Сравнение значения с текущим узлом
        if (val == this->value) {
            return this->value;  // Значение найдено
        }
        if (val < this->value && this->left != nullptr) {
            // Если значение меньше, то ищем в левом поддереве
            return static_cast<BinSearchNode<T>*>(this->left)->search(val);  // Поиск в левом поддереве        }
        }
        if (val > this->value && this->right != nullptr) {
            // Если значение больше, то ищем в правом поддереве
            return static_cast<BinSearchNode<T>*>(this->right)->search(val);  // Поиск в правом поддереве        }
        }
    return -1;
    }

    // O(n) — для несбалансированного дерева
    // O(log2n) — для сбалансированного дерева
    // Метод для проверки поиска значения в дереве поиска
    bool searchbool(T val) {
        // Сравнение значения с текущим узлом
        if (val == this->value) {
            return true;  // Значение найдено
        }
        if (val < this->value && this->left != nullptr) {
            // Если значение меньше, то ищем в левом поддереве
            return static_cast<BinSearchNode<T>*>(this->left)->searchbool(val);  // Поиск в левом поддереве        }
        }
        if (val > this->value && this->right != nullptr) {
            // Если значение больше, то ищем в правом поддереве
            return static_cast<BinSearchNode<T>*>(this->right)->searchbool(val);  // Поиск в правом поддереве        }
        }
        return false;
    }

    // O(n) — для несбалансированного дерева
    // O(log2n) — для сбалансированного дерева
    // Удаление значения из дерева поиска
    void del(T val) {
        // Если значение меньше текущего узла, идём влево
        if (val < this->value && this->left != nullptr) {
            // Проверяем, является ли левый потомок искомым узлом
            if (this->left->value == val) {
                TreeNode<T>* target = this->left; // Узел для удаления
                // Обрабатываем случай, если у узла есть потомки
                if (target->left == nullptr && target->right == nullptr) {
                    // Узел не имеет потомков
                    delete target;
                    this->left = nullptr;
                }
                else if (target->left != nullptr && target->right == nullptr) {
                    // Узел имеет только левого потомка
                    this->left = target->left;
                    delete target;
                }
                else if (target->left == nullptr && target->right != nullptr) {
                    // Узел имеет только правого потомка
                    this->left = target->right;
                    delete target;
                }
                else {
                    // Узел имеет обоих потомков
                    TreeNode<T>* successorParent = target;
                    TreeNode<T>* successor = target->right;
                    while (successor->left != nullptr) {
                        successorParent = successor;
                        successor = successor->left;
                    }
                    target->value = successor->value; // Замена значений
                    if (successorParent->left == successor) {
                        successorParent->left = successor->right;
                    }
                    else {
                        successorParent->right = successor->right;
                    }
                    delete successor;
                }
            }
            else {
                // Рекурсивное удаление в левом поддереве
                static_cast<BinSearchNode<T>*>(this->left)->del(val);
            }
        }
        // Если значение больше текущего узла, идём вправо
        else if (val > this->value && this->right != nullptr) {
            // Проверяем, является ли правый потомок искомым узлом
            if (this->right->value == val) {
                TreeNode<T>* target = this->right; // Узел для удаления
                // Обрабатываем случай, если у узла есть потомки
                if (target->left == nullptr && target->right == nullptr) {
                    // Узел не имеет потомков
                    delete target;
                    this->right = nullptr;
                }
                else if (target->left != nullptr && target->right == nullptr) {
                    // Узел имеет только левого потомка
                    this->right = target->left;
                    delete target;
                }
                else if (target->left == nullptr && target->right != nullptr) {
                    // Узел имеет только правого потомка
                    this->right = target->right;
                    delete target;
                }
                else {
                    // Узел имеет обоих потомков
                    TreeNode<T>* successorParent = target;
                    TreeNode<T>* successor = target->right;
                    while (successor->left != nullptr) {
                        successorParent = successor;
                        successor = successor->left;
                    }
                    target->value = successor->value; // Замена значений
                    if (successorParent->left == successor) {
                        successorParent->left = successor->right;
                    }
                    else {
                        successorParent->right = successor->right;
                    }
                    delete successor;
                }
            }
            else {
                // Рекурсивное удаление в правом поддереве
                static_cast<BinSearchNode<T>*>(this->right)->del(val);
            }
        }
        // Если значение совпадает с корнем дерева
        else if (val == this->value) {
            // Обработка корневого узла при удалении, если потребуется
            cout << "Удаление корня дерева не поддерживается этим методом." << endl;
        }
        else {
            // Значение не найдено
            cout << "Значение " << val << " не найдено в дереве." << endl;
        }
    }
};