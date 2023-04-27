#include "Vector.h"
#include <iostream>
#include <algorithm>
using namespace std;

template<typename Object>
ostream& operator<< (ostream& out, const Vector<Object>& rhs)
{
    rhs.print(out);
    return out;
}


int main( )
{
    string p1 = "1번 문제: Vector<Object> + Vector<Object>";
    cout << endl << endl << p1 << endl << endl;
    {
        Vector<int> int_array1 = { 1, 2, 3 };
        Vector<int> int_array2 = { 1, 2, 3, 4, 5 };

        cout << int_array1;
        cout << int_array2;
        cout << int_array1 + int_array2 << endl;

        Vector<string> str_array1 = { "cat", "dog", "tiger" };
        Vector<string> str_array2 = { "one", "two", "three", "four", "five" };


        cout << str_array1;
        cout << str_array2;
        cout << str_array1 + str_array2;

    }


    string p2 = "2번 문제: Vector<Object> + Object";
    cout << endl << endl << p2 << endl << endl;
    {
        Vector<int> int_array = { 1, 2, 3 };
        int int_val = 10;

        cout << int_array;
        cout << int_array + int_val;
        cout << int_array + 20 << endl;

        Vector<string> str_array = { "cat", "dog", "tiger" };
        string str_val = "ten";

        cout << str_array;
        cout << str_array + str_val;
        cout << str_array + "twenty";

    }

    string p3 = "3번 문제: Vector<Object>.insert(itr, Object)";
    cout << endl << endl << p3 << endl << endl;
    {
        Vector<int> int_array = { 1, 2, 3 };
        cout << int_array;
        Vector<int>::iterator int_ret_itr = int_array.insert(int_array.end(), 100);
        cout << int_array;
        cout << "itr_val after the insert  : " << *int_ret_itr << endl << endl;


        Vector<string> str_array = { "cat", "dog", "tiger" };
        cout << str_array;
        Vector<string>::iterator str_ret_itr = str_array.insert(str_array.begin() + 1, "hello");
        cout << str_array;
        cout << "itr_val after the insert  : " << *str_ret_itr << endl;
    }

    string p4 = "4번 문제: Vector<Object>.erase(itr)";
    cout << endl << endl << p4 << endl << endl;
    {
        Vector<int> int_array = { 1, 2, 3 };
        cout << int_array;
        Vector<int>::iterator int_ret_itr = int_array.erase(int_array.end() - 2);
        cout << int_array;
        cout << "itr_val after the erase  : " << *int_ret_itr << endl << endl;


        Vector<string> str_array = { "cat", "dog", "tiger" };
        cout << str_array;
        Vector<string>::iterator str_ret_itr = str_array.erase(str_array.begin() + 1);
        cout << str_array;
        cout << "itr_val after the erase  : " << *str_ret_itr << endl;
    }

    return 0;
}

