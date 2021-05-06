#include <cstdio>

int Q, N, matrix[35][35];
int rows[35], cols[35], diag1=0, diag2=0;

bool check()
{
    scanf("%d", &N);                                // get size of square
    for (int i=1; i<=N; ++i)
        for (int j=1; j<=N; ++j)                    // for each cell
        {
            scanf("%d", &matrix[i][j]);             // input into the matrix and
        }

    for (int i=1; i<=N; ++i)
        rows[i] = cols[i] = 0;                      // clear row and column counts
    diag1 = diag2 = 0;                              // clear the diagonal counts

    for (int i=1; i<=N; ++i)                        // sum the diagonals
    {
        diag1 += matrix[i][i];
        diag2 += matrix[i][N-i+1];
    }

    for (int i=1; i<=N; ++i)
        for (int j=1; j<=N; ++j)
        {
            rows[i] += matrix[i][j];                // sum the rows
            cols[j] += matrix[i][j];                // sum the columns
        }

    for (int i=1; i<=N; ++i)                        // for each row and column
        if (rows[i] != diag1 || cols[i] != diag1)   // if they aren't equal to the diagonal
            return 0;                               // return false

    return diag1 == diag2;                          // everything else equals diag1, so just check it with diag2
}

int main()
{
    scanf("%d", &Q);                                // number of queries
    for (int i=1; i<=Q; ++i)
        printf("%d\n", check());
}

