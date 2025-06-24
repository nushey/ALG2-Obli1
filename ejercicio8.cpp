#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "./adts/vector.cpp"

using namespace std;

Vector<Vector<int>> memo;

bool solve(int i, int j, const string &palabra, const string &patron)
{
    if (j == patron.length())
        return i == palabra.length(); // Si recorri todo el patron se acaba la palabra
    if (memo[i][j] != -1)
        return memo[i][j];

    bool match = (i < palabra.length() && (palabra[i] == patron[j] || patron[j] == '.'));
    // Recorro la palabra y me fijo si matchea patron con letra o punto

    if (j + 1 < patron.length() && patron[j + 1] == '*')
    {
        return memo[i][j] = (solve(i, j + 2, palabra, patron) ||           // ignorar x*
                             (match && solve(i + 1, j, palabra, patron))); // usar x* una vez y seguir
    }
    else
    {
        return memo[i][j] = (match && solve(i + 1, j + 1, palabra, patron));
    }
}

bool grepear(const string &palabra, const string &patron)
{
    return solve(0, 0, palabra, patron);
}

int main()
{
    string palabra;
    // cout << "Ingrese la palabra" << "\n";
    cin >> palabra;

    string patron;
    // cout << "Ingrese el patron" << "\n";
    cin >> patron;
    int n = palabra.size();
    int m = patron.size();
    memo = Vector<Vector<int>>(n + 1);
    for (int i = 0; i <= n; i++)
    {
        memo[i] = Vector<int>(m + 1);
        for (int j = 0; j <= m; j++)
        {
            memo[i][j] = -1;
        }
    }
    grepear(palabra, patron) ? cout << "true" << "\n" : cout << "false" << "\n";

    return 0;
}