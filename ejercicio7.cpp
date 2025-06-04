#include <stdio.h>
#include <iostream>

using namespace std;

void convert(string &str, int *digits, int &l, int &r, int &i, bool left, bool cond)
{
    if (cond && digits[i] <= 0)
        return;
    if (!cond && digits[i] <= 1)
    {
        str[str.size() / 2] = char('0' + i);
        return;
    }
    digits[i]--;
    if (left)
    {
        str[l] = char('0' + i);
        ++l;
    }
    else
    {
        str[r] = char('0' + i);
        --r;
    }
    convert(str, digits, l, r, i, !left, cond);
}

int main()
{

    string num;
    cin >> num;
    int *digits = new int[10];
    int n = num.size();
    for (int i = 0; i < 10; i++)
    {
        digits[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        digits[num[i] - '0']++;
    }
    string ans(n, '"');
    int odd = 0;
    bool valid = true;
    int l = 0, r = n - 1;
    for (int i = 9; i >= 0; i--)
    {
        if (digits[i] % 2 != 0)
            odd++;
        if (odd > 1 || (n % 2 == 0 && odd >= 1))
        {
            valid = false;
            break;
        }
        if (digits[i] > 0)
        {
            convert(ans, digits, l, r, i, true, digits[i] % 2 == 0);
        }
    }
    if (valid)
        cout << ans;
    else
        cout << "No";
    return 0;
}