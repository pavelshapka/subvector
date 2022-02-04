#include <iostream>
using namespace std;

struct subvector {
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

bool init(subvector *qv) { //инициализация пустого недовектора (top и capacity по нулям, а mas это NULL)
    qv->mas = NULL;
    qv->top = 0;
    qv->capacity = 0;
    return true;
}

bool resize(subvector *qv, unsigned int new_capacity) { //увеличить емкость недовектора
// (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity,
// то копируем только то, что влезает, и уменьшаем top до capacity)
    if (new_capacity != 0) {
        int *mas2 = new int[new_capacity];
        memcpy(mas2, qv->mas, min(new_capacity, qv->capacity) * sizeof(int));
        qv->capacity = new_capacity;
        qv->top = min(qv->top, new_capacity);
        delete[]qv->mas;
        qv->mas = mas2;
    }
    else {
        if (qv->capacity > 0) {
            delete[]qv->mas;
            init(qv);
        }
    }
    return true;
}

bool push_back(subvector *qv, int d) {
//добавление элемента в конец недовектора с выделением дополнительной памяти при необходимости
    if (qv->capacity == 0) {
        qv->mas = new int[10];
        qv->capacity = 10;
    }
    else if (qv->top >= qv->capacity) {
        resize(qv, qv->capacity * 2);
    }
    *(qv->mas + qv->top) = d;
    qv->top++;
    return true;
}

int pop_back(subvector *qv) { //удаление элемента с конца недовектора, значение удаленного элемента вернуть
    if (qv->top > 0) {
        int res = *(qv->mas + qv->top - 1);
        qv->top--;
        return res;
    }
    return 0;
}

void shrink_to_fit(subvector *qv) { //очистить неиспользуемую память
    resize(qv, qv->top);
}

void clear(subvector *qv) { //очистить содержимое недовектора, занимаемое место при этом не меняется
    memset(qv->mas, 0, qv->capacity * sizeof(int));
    qv->top = 0;
}

void destructor(subvector *qv) { //очистить всю используемую память, инициализировать недовектор как пустой
    if (qv->capacity > 0) {
        delete []qv->mas;
        init(qv);
    }
}
