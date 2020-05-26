#include <iostream>
using namespace std;

template<typename List>
constexpr int len(const List& list){
    return sizeof(list)/sizeof(list[0]);
}
template <typename List>
void print(const List& list){
    for(int i=0; i<len(list); ++i){
        cout << list[i] <<" "
    }
    cout<<endl;
}
int main(){
    int a[5];
    char b[18];
    double c[10];
    constexpr int lena=len(a), lenb=len(b), lenc=len(c);
    cout<<lena<<" "<<lenb<<" "<<lenc<<endl; 
}