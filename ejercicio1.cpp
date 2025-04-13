#include <stdio.h>
#include <string>
#include "./adts/openMap.cpp"
#include "./auxiliary/hash_string.cpp"

using namespace std;

int main(){

    ios::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    int n;
    cin >> n;
    HashFunc<string> *h = new HashString();
    Map<string,string>* om = new OpenMap<string,string>(h, n);

    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        om->set(str,str);
    }
    cout << om->size()<< "\n";

    delete h;
    delete om;
    return 0;
}