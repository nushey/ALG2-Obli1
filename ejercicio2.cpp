#include <stdio.h>
#include <string>
#include "./adts/closeMap.cpp"
#include "./auxiliary/hash_string.cpp"
#include "./auxiliary/hash_string2.cpp"

using namespace std;

int main(){

    int n,m;
    cin >> n;
    HashFunc<string> *h1 = new HashString();
    HashFunc<string> *h2 = new HashString2();
    Map<string,string>* om = new ClosedMap<string,string>(h1, h2, n);

    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        om->set(str,str);
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        string str;
        cin >> str;
        cout << om->exists(str) << endl;
    }

    delete om;
    delete h1;
    delete h2;



    return 0;
}