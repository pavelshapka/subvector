#include <iostream>
#include "subvector_class.h"
#include "forward_list"
#include "subforwardlist_class.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include <list>
#include <map>
#include <set>
using namespace std;

double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int rand_uns(int min, int max)
{
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        static std::default_random_engine e(seed);
        std::uniform_int_distribution<int> d(min, max);
        return d(e);
}

int main() {
    subvector_class<int> sv;
    vector<int> vect;
    subforwardlist<int> sfl;
    forward_list<int> fl;
    list<int> m;
    map<int, int> q;
    set<int> l;
    int n = 500, ind, val, tmp;
    double start = 0, finish = 0, total = 0;
    ofstream f("data_my.txt");
    ofstream h("data_vect.txt");
    double s = 0;
    while (n <= 100000) {
        for (int i = 0; i < 500; i++) {
            val = rand_uns(0, 10000);
            vect.push_back(val);
            sv.push_back(val);
        }
        double s1 = 0, s2 = 0, c1 = 0, c2 = 0;
        vector<double> data_v, data_sv;
        vector<int> inds;
        for (int i = 0; i < 10000; i++) {
            for (int j = 0; j < 100; j++)
                inds.push_back(rand_uns(0, n - 1));
            val = rand_uns(0, 10000);
            start = get_time();
            for (int j = 0; j < 100; j++) {
                vect[inds[i]];
            }
            finish = get_time();
            total = finish - start;
            c1++;
            s1 += total;
//        for (int i = 0; i < 1000; i++) {
//            ind = rand_uns(0, n - 2);
//            val = rand_uns(0, 10000);
//            start = get_time();
//            vect.insert(vect.begin(), val);
//            finish = get_time();
//            total = finish - start;
//            c1++;
//            s1 += total;
//        }
//
            start = get_time();
            for (int j = 0; j < 100; j++) {
                sv[inds[i]];
            }
            finish = get_time();
            total = finish - start;
            c2++;
            s2 += total;
//        }

        }
        f << n << ' ' << s1 / c1 << endl;
        h << n << ' ' << s2 / c2 << endl;
        n += 500;
    }
//    for (int el : sv)
//        cout << el << ' ';
//    int n = 100000;
//    vector<pair<int, unsigned int>> data;
//
//    int tmp;
//    for (int i = 0; i < 10; i++) {
//        tmp = rand_uns(0, n);
//        sv.push_back(i);
//        vect.push_back(i);
//    }

//    start = get_time();
//    f.close();
//    h.close();
//    sv.erase(10);
//    subvector_class<int>::Iterator it = sv.begin();
//
//    for(auto &i : sv) {
//        cout << i << ' ';
//    }

return 0;
}

























//int main()
//{
//    int n = 100000;
//    int *test_sequence = new int[n], sum_for_O3 = 0, sum_check = 0,
//        *pop_push_sequence_eq = new int[n],
//        *pop_push_sequence_push = new int[n],
//        *pop_push_sequence_pushpush = new int[n];
//    double start = 0, finish = 0, total = 0;
//    cout << std::fixed;
//    cout.precision(4);
//
////----------- Initialization
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        test_sequence[i] = rand_uns(0, n - 1);
//        pop_push_sequence_eq[i] = rand_uns(0, 1);
//        pop_push_sequence_push[i] = rand_uns(0, 5);
//        pop_push_sequence_pushpush[i] = rand_uns(0, 10);
//    }
//    finish = get_time();
//
//    cout << "Test sequence initialization: \t\t" << finish - start << endl;
//
//    subvector_class<int> sv;
//
////----------- Test 000 Straight push_back
//
//    start = get_time();
//    for (int i = 0; i < 10; i++)
//    {
//        sv.push_back(test_sequence[i]);
//    }
//    finish = get_time();
//
//    for (int i = 0; i < n; i++)   //!!! This is a hack to bamboozle the O3 optimization.
//        sum_for_O3 += sv.mas[i];  // I might as well use it to test push/pop.
//
//    cout << "000 Straight push_back: \t\t" << finish - start << endl;
//    total += finish - start;
//
////----------- Test 001 Straight pop_back
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        sum_check += sv.pop_back();
//    }
//    finish = get_time();
//
//    if (sum_check != sum_for_O3)
//    {
//        cout <<endl <<"--- !!! Failed push/pop consistency !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "001 Straight pop_back: \t\t\t" << finish - start << endl;
//    total += finish - start;
//
////----------- Test 002 Straight resize up
//
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        sv.resize(i);
//    }
//    finish = get_time();
//
//    sv.shrink_to_fit();
//    if (sv.capacity)
//    {
//        cout <<endl <<"--- !!! Failed resize/shrink consistency !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "002 Straight resize up: \t\t" << finish - start << endl;
//    total += finish - start;
//
////----------- Test 003 Random pop/push equal amount
//
//    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        if (pop_push_sequence_eq[i])
//            sv.push_back(test_sequence[i]);
//        else
//            sum_for_O3 += sv.pop_back();
//    }
//    finish = get_time();
//
//    sv.clear();
//    sv.shrink_to_fit();
//    if (sv.top)
//    {
//        cout <<endl <<"--- !!! Falied clear !!! ---" << endl;
//        return 0;
//    }
//    if (sv.capacity)
//    {
//        cout <<endl <<"--- !!! Falied shrink_to_fit !!! ---" << endl;
//        return 0;
//    }
//
//    cout << "003 Random pop/push equal amount: \t" << finish - start << "\t\t" << sum_for_O3 << endl;
//    total += finish - start;
//
////----------- Test 004 Random pop/push more push
//
//    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        if (pop_push_sequence_push[i])
//            sv.push_back(test_sequence[i]);
//        else
//            sum_for_O3 += sv.pop_back();
//    }
//    finish = get_time();
//
//    sv.clear();
//    sv.shrink_to_fit();
//
//    cout << "004 Random pop/push more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
//    total += finish - start;
//
////----------- Test 005 Random pop/push much more push
//
//    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
//    start = get_time();
//    for (int i = 0; i < n; i++)
//    {
//        if (pop_push_sequence_pushpush[i])
//            sv.push_back(test_sequence[i]);
//        else
//            sum_for_O3 += sv.pop_back();
//    }
//    finish = get_time();
//
//    cout << "005 Random pop/push much more push: \t" << finish - start << "\t\t" << sum_for_O3 << endl;
//    total += finish - start;
//
////----------- End of tests
//    cout << "-----------" << endl <<"Alltests finished, total time: \t" << total << endl;
//
//    delete[] test_sequence;
//    delete[] pop_push_sequence_eq;
//    delete[] pop_push_sequence_push;
//    delete[] pop_push_sequence_pushpush;
//
//    return 0;
//}
