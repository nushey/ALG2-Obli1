#include <stdio.h>
#include <iostream>
#include "./adts/vector.cpp"

#define vector Vector

using namespace std;

struct Figure
{
    int x;
    int y;
    int h;
};

struct Point
{
    int x;
    int y;
};

vector<Point> merge(Figure &a, Figure &b)
{
    vector<Point> ans;
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

    vector<Point> cleanAns;
    for (int i = 0; i < ans.size(); i++)
    {
        if (i == 0 || ans[i].y != ans[i - 1].y)
        {
            cleanAns.push(ans[i]);
        }
    }
    return cleanAns;
}

vector<Point> concat(vector<Point> &a, vector<Point> &b)
{
    vector<Point> ans;
    int i = 0, j = 0, h1 = 0, h2 = 0;
    while (i < a.size() && j < b.size())
    {
        if (a[i].x < b[j].x)
        {
            int x = a[i].x;
            h1 = a[i].y;
            ans.push({x, max(h1, h2)});
            i++;
        }
        else if (a[i].x > b[j].x)
        {
            int x = b[j].x;
            h2 = b[j].y;
            ans.push({x, max(h1, h2)});
            j++;
        }
        else
        {
            int x = a[i].x;
            h1 = a[i].y;
            h2 = b[j].y;
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

    vector<Point> cleanAns;
    for (int i = 0; i < ans.size(); i++)
    {
        if (i == 0 || ans[i].y != ans[i - 1].y)
        {
            cleanAns.push(ans[i]);
        }
    }
    return cleanAns;
}

vector<Point> solve(int n, Figure *arr, int l, int r)
{
    if (r == l)
    {
        vector<Point> result;
        result.push({arr[l].x, arr[l].h});
        result.push({arr[l].y, 0});
        return result;
    }
    if (r - l == 1)
    {
        return merge(arr[l], arr[r]);
    }
    int mid = (l + r) / 2;
    vector<Point> left = solve(n, arr, l, mid);
    vector<Point> right = solve(n, arr, mid + 1, r);
    return concat(left, right);
}

int main()
{
    int n;
    cin >> n;
    Figure *arr = new Figure[n];
    for (int i = 0; i < n; i++)
    {
        int x, y, h;
        cin >> x >> y >> h;
        arr[i] = {x, y, h};
    }
    vector<Point> ans = solve(n, arr, 0, n - 1);
    for (int i = 0; i < ans.size(); i++)
    {
        if (i != 0)
        {
            cout << "\n";
        }
        cout << ans[i].x << " " << ans[i].y;
    }
    cout << "\n";
}