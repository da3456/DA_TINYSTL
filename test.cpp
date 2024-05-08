#include<iostream>
#include "map.h"

int main()
{
    using namespace mystl;
    using std::cout;
    using std::endl;

    myclass d1(10, 't'), d2(20, 'y'), d3(50, 'g'), d4(99, 'r'), d5(1, 'u');
    map<myclass, char> da_map;
    da_map.insert({{d1, 'z'}, {d2, 'x'}, {d3, 'c'}});
    for (auto iterate = da_map.begin(); iterate != da_map.end(); ++iterate)
    {
        cout << iterate << endl;
    }
    cout << "************************" << endl;

    for (auto iterate = da_map.rbegin(); iterate != da_map.rend(); ++iterate)
    {
        cout << iterate << endl;
    }

    //cout << da_map.rend() << endl;

    // map<myclass,char> dd_map = {{d3, 'z'}, {d4, 'x'}, {d5, 'c'}};
    // //dd_map = {{d3, 'z'}, {d4, 'x'}, {d5, 'c'}};
    // for (auto iterate = dd_map.begin(); iterate != dd_map.end(); ++iterate)
    // {
    //     cout << iterate << endl;
    // }

    // auto tmp = dd_map.upper_bound(d5);
    // cout << tmp << endl;

    return 0;
}