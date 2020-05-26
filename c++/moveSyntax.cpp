#include <iostream>
#include <string>
#include <utility>
using namespace std;

class BigMem{
    int* _bigPtr;
    int size;
public:
    BigMem(const BigMem & b):size(b.size),_bigPtr(new int(*b._bigPtr)){
        cout<<"use ref copy constructor"<<endl;
    }
    BigMem(BigMem && b):size(b.size),_bigPtr(b._bigPtr){
        b._bigPtr=nullptr;
        cout<<"using move copy constructor"<<endl;
    }
    explicit BigMem(int s=1024):size(s), _bigPtr(new int[s]){
    }
};

class Data {
    string info="some data information";
    BigMem memory;
public:
    Data(Data && d):info(d.info), memory(move(d.memory)){
        cout<<"Data Right Constructor"<<endl;
    }
    Data()
}
int main(){
}