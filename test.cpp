#include<iostream>
#include<vector>
using namespace std;

class myclass{
    private:
        int a,b;
    public:
        myclass(){}
        myclass(int x, int y){ a = x, b = y;}
        myclass(myclass& val):a(val.a),b(val.b){};
};

class myclassdd{
    private:
        int a,b;
    public:
        myclassdd(){}
        myclassdd(int x, int y){ a = x, b = y;}
        myclassdd(myclass& val):a(val.a),b(val.b){};
};


int main(){
    myclass deng(9,10);
    myclass fan(deng);
    return 0;
}