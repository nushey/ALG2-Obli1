#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// . representa un caracter cualquiera
// * 0 o mas del caracter anterior

/*
bool grepear(string palabra, string patron, int posPalabra, int posPatron, bool cumple){
    if (posPatron < patron.length()) {
        switch(patron[posPatron]) {
            case '.':
                if (posPatron + 1 < patron.length()) {
                    if (patron[posPatron + 1] == '*') {
                        while (posPalabra < palabra.length()) {
                            posPalabra++;
                        }
                        posPatron += 2;
                    } else {
                        posPalabra++;
                        posPatron++;
                    }
                    grepear(palabra, patron, posPalabra, posPatron, cumple);
                } else { cumple = false; }
                break;
            default:
                if (posPatron + 1 < patron.length()) {
                    if (patron[posPatron + 1] == '*') {
                        char caracter = palabra[posPalabra];
                        while (palabra[posPalabra] == caracter && posPalabra < palabra.length()) {
                            posPalabra++;
                        }
                        posPatron += 2;
                    } else {
                        if (palabra[posPalabra] == patron[posPatron]) {
                            posPalabra++;
                            posPatron++;
                        } else {
                            cumple = false;
                        }
                    }
                    grepear(palabra, patron, posPalabra, posPatron, cumple);
                } else { cumple = false; }
            }
    }
    return cumple;
}
*/

/* bool grepear(string palabra, string patron, int posPalabra, int posPatron) {
    if (posPatron == patron.length()) {
        return posPalabra == palabra.length();
    }

    bool match = (posPalabra < palabra.length() &&
                 (patron[posPatron] == palabra[posPalabra] || patron[posPatron] == '.'));

    // Si el siguiente carácter del patrón es '*', intentamos consumir 0 a N ocurrencias
    if (posPatron + 1 < patron.length() && patron[posPatron + 1] == '*') {
        return (grepear(palabra, patron, posPalabra, posPatron + 2) ||  // consumí 0 veces
               (match && grepear(palabra, patron, posPalabra + 1, posPatron)));  // consumí 1+ veces
    } else {
        return match && grepear(palabra, patron, posPalabra + 1, posPatron + 1);
    }
} */
//////////////////////////////
/*
bool dp(int i, int j, const string& palabra, const string& patron, vector<vector<int>>& memo) {
    if (memo[i][j] != -1) return memo[i][j];

    if (j == patron.length()) return memo[i][j] = (i == palabra.length());

    bool match = (i < palabra.length() &&
                 (palabra[i] == patron[j] || patron[j] == '.'));

    if (j + 1 < patron.length() && patron[j + 1] == '*') {
        memo[i][j] = (dp(i, j + 2, palabra, patron, memo) || (match && dp(i + 1, j, palabra, patron, memo)));
    } else {
        memo[i][j] = match && dp(i + 1, j + 1, palabra, patron, memo);
    }

    return memo[i][j];
}

bool grepear(const string& palabra, const string& patron) {
    vector<vector<int>> memo(palabra.length() + 1, vector<int>(patron.length() + 1, -1));
    return dp(0, 0, palabra, patron, memo);
}
*/

bool backtrack(int i, int j, const string& palabra, const string& patron) {
    if (j == patron.length()) return i == palabra.length(); // Si recorri todo el patron se acaba la palabra

    bool match = (i < palabra.length() && (palabra[i] == patron[j] || patron[j] == '.'));
    // Recorro la palabra y me fijo si matchea patron con letra o punto

    if (j + 1 < patron.length() && patron[j + 1] == '*') {
        return backtrack(i, j + 2, palabra, patron) ||  // ignorar x*
               (match && backtrack(i + 1, j, palabra, patron));  // usar x* una vez y seguir
    } else {
        return match && backtrack(i + 1, j + 1, palabra, patron);
    }
}

bool grepear(const string& palabra, const string& patron) {
    return backtrack(0, 0, palabra, patron);
}

int main(){
    string palabra;
    //cout << "Ingrese la palabra" << "\n";
    cin >> palabra;

    string patron;
    //cout << "Ingrese el patron" << "\n";
    cin >> patron;
    
    grepear(palabra, patron) ? cout << "true" << "\n" : cout << "false" << "\n";

    return 0;
}