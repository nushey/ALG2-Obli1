#include <bits/stdc++.h>
#include "./adts/vector.cpp"

using namespace std;

struct Task
{
    int t;
    int l;
    int p;
};

int main()
{
    int N, S, L;
    cin >> N >> S >> L;

    Task *tasks = new Task[N];
    for (int i = 0; i < N; i++)
    {
        int t, l, p;
        cin >> t >> l >> p;
        tasks[i] = {t, l, p};
    }

    int ***dp = new int **[N + 1];
    for (int i = 0; i <= N; i++)
    {
        dp[i] = new int *[S + 1];
        for (int j = 0; j <= S; j++)
        {
            dp[i][j] = new int[L + 1];
            for (int k = 0; k <= L; k++)
            {
                dp[i][j][k] = 0;
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= S; j++)
        {
            for (int k = 0; k <= L; k++)
            {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j - tasks[i - 1].t >= 0 && k - tasks[i - 1].l >= 0)
                {
                    dp[i][j][k] = max(dp[i - 1][j][k], tasks[i - 1].p + dp[i - 1][j - tasks[i - 1].t][k - tasks[i - 1].l]);
                }
            }
        }
    }

    cout << dp[N][S][L] << "\n";
}