#include <stdio.h>
#include <string>
#include "./adts/openMap.cpp"
#include "./auxiliary/hash_string.cpp"

using namespace std;

int main(){

    int n;
    cin >> n;
    HashFunc<string> *h = new HashString();
    Map<string,string>* om = new OpenMap<string,string>(h, n);

    while(n--){

    }
    return 0;
}