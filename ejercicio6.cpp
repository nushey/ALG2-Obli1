#include <stdio.h>
#include <iostream>
#include "./adts/vector.cpp"

#define vector Vector

using namespace std;

struct Coord
{
    int x;
    int y;
    int h;
};

vector<pair<int, int>> merge(Coord &a, Coord &b)
{
    vector<pair<int, int>> ans;
    if (b.x > a.y)
    {
        ans.push({a.x, a.h});
        ans.push({a.y, 0});
        ans.push({b.x, b.h});
        ans.push({b.y, 0});
    }
    else if (b.x == a.y)
    {
        ans.push({a.x, a.h});
        ans.push({b.x, b.h});
        ans.push({b.y, 0});
    }
    else if (b.x > a.x)
    {
        if (a.h > b.h)
        {
            if (b.y <= a.y)
            {
                ans.push({a.x, a.h});
                ans.push({a.y, 0});
            }
            else
            {
                ans.push({a.x, a.h});
                ans.push({a.y, b.h});
                ans.push({b.y, 0});
            }
        }
        else if (a.h == b.h)
        {
            if (b.y >= a.y)
            {
                ans.push({a.x, a.h});
                ans.push({b.y, 0});
            }
            else
            {
                ans.push({a.x, a.h});
                ans.push({a.y, 0});
            }
        }
        else
        {
            if (b.y >= a.y)
            {
                ans.push({a.x, a.h});
                ans.push({b.x, b.h});
                ans.push({b.y, 0});
            }
            else
            {
                ans.push({a.x, a.h});
                ans.push({b.x, b.h});
                ans.push({b.y, a.h});
                ans.push({a.y, 0});
            }
        }
    }
    else
    {
        if (b.h > a.h)
        {
            if (b.y < a.y)
            {
                ans.push({a.x, b.h});
                ans.push({b.y, a.h});
                ans.push({a.y, 0});
            }
            else
            {
                ans.push({a.x, b.h});
                ans.push({b.y, 0});
            }
        }
        else if (b.h == a.h)
        {
            if (b.y >= a.y)
            {
                ans.push({a.x, a.h});
                ans.push({b.y, 0});
            }
            else
            {
                ans.push({a.x, a.h});
                ans.push({a.y, 0});
            }
        }
        else
        {
            if (b.y <= a.y)
            {
                ans.push({a.x, a.h});
                ans.push({a.y, 0});
            }
            else
            {
                ans.push({a.x, a.h});
                ans.push({a.y, b.h});
                ans.push({b.y, 0});
            }
        }
    }

    vector<pair<int, int>> cleanAns;
    for (int i = 0; i < ans.size(); i++)
    {
        if (i == 0 || ans[i].second != ans[i - 1].second)
        {
            cleanAns.push(ans[i]);
        }
    }
    return cleanAns;
}

vector<pair<int, int>> concat(vector<pair<int, int>> &a, vector<pair<int, int>> &b)
{
    vector<pair<int, int>> ans;
    int i = 0, j = 0, h1 = 0, h2 = 0;
    while (i < a.size() && j < b.size())
    {
        if (a[i].first < b[j].first)
        {
            int x = a[i].first;
            h1 = a[i].second;
            ans.push({x, max(h1, h2)});
            i++;
        }
        else if (a[i].first > b[j].first)
        {
            int x = b[j].first;
            h2 = b[j].second;
            ans.push({x, max(h1, h2)});
            j++;
        }
        else
        {
            int x = a[i].first;
            h1 = a[i].second;
            h2 = b[j].second;
            ans.push({x, max(h1, h2)});
            i++;
            j++;
        }
    }
    while (i < a.size())
    {
        ans.push(a[i++]);
    }
    while (j < b.size())
    {
        ans.push(b[j++]);
    }

    vector<pair<int, int>> cleanAns;
    for (int i = 0; i < ans.size(); i++)
    {
        if (i == 0 || ans[i].second != ans[i - 1].second)
        {
            cleanAns.push(ans[i]);
        }
    }
    return cleanAns;
}

vector<pair<int, int>> solve(int n, Coord *arr, int l, int r)
{
    if (r == l)
    {
        vector<pair<int, int>> result;
        result.push({arr[l].x, arr[l].h});
        result.push({arr[l].y, 0});
        return result;
    }
    if (r - l == 1)
    {
        return merge(arr[l], arr[r]);
    }
    int mid = (l + r) / 2;
    vector<pair<int, int>> left = solve(n, arr, l, mid);
    vector<pair<int, int>> right = solve(n, arr, mid + 1, r);
    return concat(left, right);
}

int main()
{
    int n;
    cin >> n;
    Coord *arr = new Coord[n];
    for (int i = 0; i < n; i++)
    {
        int x, y, h;
        cin >> x >> y >> h;
        arr[i] = {x, y, h};
    }
    vector<pair<int, int>> ans = solve(n, arr, 0, n - 1);
    for (int i = 0; i < ans.size(); i++)
    {
        if (i != 0)
        {
            cout << "\n";
        }
        cout << ans[i].first << " " << ans[i].second;
    }
    cout << "\n";
}