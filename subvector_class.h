#ifndef SUBVECTOR_SUBVECTOR_CLASS_H
#define SUBVECTOR_SUBVECTOR_CLASS_H

#include <algorithm>
using namespace std;

class subvector_class {
public:
     subvector_class() { //инициализация пустого недовектора (top и capacity по нулям, а mas это NULL)
        this->mas = nullptr;
        this->top = 0;
        this->capacity = 0;
    }

    bool resize(unsigned int new_capacity) { //увеличить емкость недовектора
    // (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity,
    // то копируем только то, что влезает, и уменьшаем top до capacity)
        if (new_capacity != 0) {
            int *mas2 = new int[new_capacity];
            memcpy(mas2, this->mas, min(new_capacity, this->capacity) * sizeof(int));
            this->capacity = new_capacity;
            this->top = min(this->top, new_capacity);
            delete[]this->mas;
            this->mas = mas2;
        }
        else {
            if (this->capacity > 0) {
                delete[]this->mas;
                this->mas = nullptr;
                this->top = 0;
                this->capacity = 0;
            }
        }
        return true;
    }

    bool push_back(int d) {
    //добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости
        if (this->capacity == 0) {
            this->mas = new int[10];
            this->capacity = 10;
        }
        else if (this->top >= this->capacity) {
            resize(this->capacity * 2);
        }
        *(this->mas + this->top) = d;
        this->top++;
        return true;
    }

    int pop_back() { //удаление элемента с конца недовектора, значение удаленного элемента вернуть
        if (this->top > 0) {
            int res = *(this->mas + this->top - 1);
            this->top--;
            return res;
        }
        return 0;
    }

    void shrink_to_fit() { //очистить неиспользуемую память
        resize(this->top);
    }

    void clear() { //очистить содержимое недовектора, занимаемое место при этом не меняется
        memset(this->mas, 0, this->capacity * sizeof(int));
        this->top = 0;
    }

    ~subvector_class() { //очистить всю используемую память, инициализировать недовектор как пустой
        if (this->capacity > 0) {
            delete []this->mas;
            this->mas = nullptr;
            this->top = 0;
            this->capacity = 0;
        }
    }
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

#endif //SUBVECTOR_SUBVECTOR_CLASS_H
