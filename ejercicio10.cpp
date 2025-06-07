#include <stdio.h>
#include <iostream>

using namespace std;

bool isSafe(int **&grid, int n, int m, int row, int col, int num)
{
    for (int i = 0; i < m; i++)
    {
        if (grid[row][i] == num)
            return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (grid[i][col] == num)
            return false;
    }

    int startR = row - (row % (n / 3));
    int startC = col - (col % (m / 3));
    for (int i = 0; i < (n / 3); i++)
    {
        for (int j = 0; j < (m / 3); j++)
        {
            if (grid[i + startR][j + startC] == num)
                return false;
        }
    }
    return true;
}

bool solve(int **grid, int n, int m, int row, int col)
{
    if (row == n)
        return true;
    if (col == m)
        return solve(grid, n, m, row + 1, 0);
    if (grid[row][col] != 0)
        return solve(grid, n, m, row, col + 1);
    for (int i = 1; i <= max(n, m); i++)
    {
        if (isSafe(grid, n, m, row, col, i))
        {
            grid[row][col] = i;
            if (solve(grid, n, m, row, col + 1))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int **grid = new int *[n];
    for (int i = 0; i < n; i++)
    {
        grid[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    solve(grid, n, m, 0, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}