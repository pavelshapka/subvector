#ifndef SUBFORWARDLIST_SUBFORWARDLIST_CLASS_H
#define SUBFORWARDLIST_SUBFORWARDLIST_CLASS_H

#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* next;
};

template<typename T>
class subforwardlist {
public:
    Node* elem;
    subforwardlist() {
        elem = nullptr;
    }
    subforwardlist(T data, Node* next = nullptr) {
        elem = new Node;
        elem->data = data;
        elem->next = next;
    }

    void push_back(int d) { //добавление элемента в конец недосписка
        subforwardlist<T> *tmp = new subforwardlist(d);
        if (this->elem == nullptr) {
            this->elem = tmp->elem;
        }
        else {
            Node* iter = this->elem;
            while (iter->next != nullptr)
                iter = iter->next;
            iter->next = tmp->elem;
        }
    }

    T pop_back() { //удаление элемента с конца недосписка
        if (elem == nullptr) {
            return -1;
        }
        else {
            Node* iter_first = this->elem;
            Node* iter_second = nullptr;
            while (iter_first->next != nullptr) {
                iter_second = iter_first;
                iter_first = iter_first->next;
            }
            T res = iter_first->data;
            delete iter_first;
            if (iter_second != nullptr)
                iter_second->next = nullptr;
            else
                this->elem = nullptr;
            return res;
        }
    }

    void push_forward(int d) { //добавление элемента в начало недосписка
        subforwardlist* tmp = new subforwardlist(d, this->elem);
        this->elem = tmp->elem;
    }

    T pop_forward() { //удаление элемента из начала недосписка
        if (this->elem == nullptr) {
            return -1;
        }
        else {
            T res = this->elem->data;
            Node* next = this->elem->next;
            delete this->elem;
            this->elem = next;
            return res;
        }
    }
//
    void push_where(unsigned int where, int d) { //добавление элемента с порядковым номером where
        if (where == 0) {
            push_forward(d);
        }
        else if (this->elem != nullptr) {
            Node* iter_first = this->elem;
            Node* iter_second = nullptr;
            int i = 1;
            while (iter_first->next != nullptr && i < where) {
                iter_second = iter_first;
                iter_first = iter_first->next;
                i++;
            }
            if (i == where) {
                subforwardlist* tmp = new subforwardlist(d, iter_first->next);
                iter_first->next = tmp->elem;
            }
        }
    }

    T erase_where(unsigned int where) { //удаление элемента с порядковым номером where
        if (where == 0) {
            return pop_forward();
        }
        else if (this->elem != nullptr){
            Node* iter_first = this->elem;
            Node* iter_second = this->elem;
            int i = 0;
            while (iter_first->next != nullptr && i < where) {
                iter_second = iter_first;
                iter_first = iter_first->next;
                i++;
            }
            if (i == where) {
                iter_second->next = iter_first->next;
                T res = iter_first->data;
                delete iter_first;
                return res;
            }
        }
        return -1;
    }

    unsigned int size() { //определить размер недосписка
        int i = 0;
        Node* iter_last = this->elem;
        while (iter_last != nullptr) {
            iter_last = iter_last->next;
            i++;
        }
        return i;
    }

    ~subforwardlist() { //очистить содержимое недосписка
        Node* iter = this->elem;
        Node* iter_next = nullptr;
        while (iter != nullptr) {
            iter_next = iter->next;
            delete iter;
            iter = iter_next;
        }
        this->elem = nullptr;
    }
};


#endif //SUBFORWARDLIST_SUBFORWARDLIST_CLASS_H
