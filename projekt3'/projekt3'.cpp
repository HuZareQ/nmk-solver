#include <iostream>
#include <stdio.h>

using namespace std;

int mini(int l, int r);
int maxi(int l, int r);
void Print_tab(int N, int M, int** tab);
int checkHorizontal(int N, int M, int K, int** tab);
int checkVertical(int N, int M, int K, int** tab);
int checkDiagRight(int N, int M, int K, int** tab);
int checkDiagLeft(int N, int M, int K, int** tab);
int check(int N, int M, int K, int ActivePlayer, int** tab);
void GEN_ALL_POS_MOV(int N, int M, int K, int ActivePlayer, int** tab, int combNumber);
int GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(int N, int M, int K, int ActivePlayer, int** tab, int combNumber);
bool isMovesLeft(int N, int M, int** tab);
int minimax(int N, int M, int K, int ActivePlayer, int** tab, int depth, bool isMax);
void SOLVE_GAME_STATE(int N, int M, int K, int ActivePlayer, int** tab, int combNumber);

int main()
{
    int N, M, K, ActivePlayer, combNumber;
    char command[35];
    int** tab;

    while (cin >> command)
    {
        cin >> M >> N >> K >> ActivePlayer;

        combNumber = 0;

        tab = (int**)malloc(M * sizeof(int*));
        for (int i = 0; i < M; i++)
        {
            tab[i] = (int*)malloc(N * sizeof(int));
        }

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> tab[i][j];
                if (tab[i][j] == 0) combNumber++;
            }
        }

        if (strcmp(command, "GEN_ALL_POS_MOV") == 0)
        {
            GEN_ALL_POS_MOV(N, M, K, ActivePlayer, tab, combNumber);
        }
        else if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0)
        {
            GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(N, M, K, ActivePlayer, tab, combNumber);
        }
        else if (strcmp(command, "SOLVE_GAME_STATE") == 0)
        {
            SOLVE_GAME_STATE(N, M, K, ActivePlayer, tab, combNumber); 
        }

        for (int i = 0; i < M; i++)
        {
            free(tab[i]);
        }
        free(tab);
        tab = NULL;
    }
}

int mini(int l, int r) {
    if (l > r) return r;
    else return l;
}
int maxi(int l, int r) {
    if (l < r) return r;
    else return l;
}

void Print_tab(int N, int M, int** tab)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int check(int N, int M, int K, int ActivePlayer, int** tab)
{
    if (checkHorizontal(N, M, K, tab) != 0) return checkHorizontal(N, M, K, tab);
    if (checkVertical(N, M, K, tab) != 0) return checkVertical(N, M, K, tab);
    if (checkDiagRight(N, M, K, tab) != 0) return checkDiagRight(N, M, K, tab);
    if (checkDiagLeft(N, M, K, tab) != 0) return checkDiagLeft(N, M, K, tab);
    return 0;
}

int checkHorizontal(int N, int M, int K,  int** tab)
{
    int count;
    for (int i = 0; i < M; i++)
    {
        count = 1;
        for (int j = 0; j < N - 1; j++)
        {
            if (tab[i][j] != 0)
            {
                if (tab[i][j] == tab[i][j + 1]) count++;
                else {
                    count = 1;
                }
                if (count == K) return tab[i][j];
            }
            else count = 1;
        }
    }
    return 0;
}

int checkVertical(int N, int M, int K, int** tab)
{
    int count;
    for (int i = 0; i < N; i++)
    {
        count = 1;
        for (int j = 0; j < M - 1; j++)
        {
            if (tab[j][i] != 0)
            {
                if (tab[j][i] == tab[j + 1][i]) count++;
                else count = 1;
                if (count == K) return tab[j][i];
            }
            else count = 1;
        }
    }
    return 0;
}

int checkDiagRight(int N, int M, int K, int** tab)
{
    int count;
    for (int i = M - 1; i >= 0; i--)
    {

        count = 1;
        for (int j = 0; j < N - 1 && j + i < M - 1; j++)
        {
            if (tab[i + j][j] != 0)
            {
                if (tab[i + j][j] == tab[i + j + 1][j + 1]) count++;
                else count = 1;
                if (count == K) return tab[i + j][j];
            }
            else count = 1;
        }
    }

    for (int i = 1; i < N - 1; i++)
    {
        count = 1;
        for (int j = 0; j < M - 1 && j + i < N - 1; j++)
        {
            if (tab[j][i + j] != 0)
            {
                if (tab[j][i + j] == tab[j + 1][i + j + 1]) count++;
                else count = 1;
                if (count == K) return tab[j][i + j];
            }
            else count = 1;
        }
    }

    return 0;
}

int checkDiagLeft(int N, int M, int K, int** tab)
{
    int count;
    for (int i = 1; i < M; i++)
    {

        count = 1;
        for (int j = 0; j < N - 2 && i + j < M - 1; j++)
        {
            if (tab[i + j][N - j - 1] != 0)
            {
                if (tab[i + j][N - j - 1] == tab[i + j + 1][N - j - 2]) count++;
                else count = 1;
                if (count == K) return tab[i + j][N - j - 1];
            }
            else count = 1;
        }
    }
    for (int i = N - 1; i >= 0; i--)
    {
        count = 1;
        for (int j = 0; j < M - 1 && i - j >= 1; j++)
        {
            if (tab[j][i - j] != 0)
            {
                if (tab[j][i - j] == tab[j + 1][i - j - 1]) count++;
                else count = 1;
                if (count == K) return tab[j][i - j];
            }
            else count = 1;
        }
    }

    return 0;
}

void GEN_ALL_POS_MOV(int N, int M, int K, int ActivePlayer, int** tab, int combNumber)
{
    if (check(N, M, K, ActivePlayer, tab) == 0)
    {
        printf("%d \n", combNumber);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (tab[i][j] == 0)
                {
                    tab[i][j] = ActivePlayer;
                    Print_tab(N, M, tab);
                    tab[i][j] = 0;

                }
            }
        }
    }
    else {
        combNumber = 0;
        printf("%d \n", combNumber);
    }
}

int GEN_ALL_POS_MOV_CUT_IF_GAME_OVER(int N, int M, int K, int ActivePlayer, int** tab, int combNumber)
{
    if (check(N, M, K, ActivePlayer, tab) == 0 && combNumber != 0)
    {
        int countComb = 0;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (tab[i][j] == 0)
                {
                    tab[i][j] = ActivePlayer;
                   if (check(N, M, K, ActivePlayer, tab) == 0)
                    {
                        countComb++;
                        if (countComb == combNumber) {
                            printf("%d \n", combNumber);
                            tab[i][j] = 0;
                            for (int i = 0; i < M; i++)
                            {
                                for (int j = 0; j < N; j++)
                                {
                                    if (tab[i][j] == 0)
                                    {
                                        tab[i][j] = ActivePlayer;
                                        Print_tab(N, M, tab);
                                        tab[i][j] = 0;

                                    }
                                }
                            }
                        }
                    }
                    else {
                        combNumber = 1;
                        printf("%d \n", combNumber);
                        Print_tab(N, M, tab);
                        return 0;
                    }
                    tab[i][j] = 0;

                }
            }
        }
    }
    else {
        combNumber = 0;
        printf("%d \n", combNumber);
    }
    return 0;
}

bool isMovesLeft(int N, int M, int**tab)
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (tab[i][j] == 0)
                return true;
    return false;
}

int minimax(int N, int M, int K, int ActivePlayer, int** tab, int depth, bool isMax) {

    int hold = check(N, M, K, ActivePlayer, tab);

    if (hold == ActivePlayer) return 1;
    else if (hold != 0) return -1;

    if (isMovesLeft(N, M, tab) == false) {
        return 0;
    }

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (tab[i][j] == 0)
                {
                    tab[i][j] = ActivePlayer;

                    best = maxi(best, minimax(N, M, K, ActivePlayer, tab, depth + 1, !isMax));

                    tab[i][j] = 0;
                    if (best == 1) return best;
                }

            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;
        int opponent = 0;
        if (ActivePlayer == 1) opponent = 2;
        else opponent = 1;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (tab[i][j] == 0)
                {
                    tab[i][j] = opponent;

                    best = mini(best, minimax(N, M, K, ActivePlayer, tab, depth + 1, !isMax));

                    tab[i][j] = 0;
                    if (best == -1) return best;
                }
            }
        }
        return best;
    }
}

void SOLVE_GAME_STATE(int N, int M, int K, int ActivePlayer, int** tab, int combNumber)
{
    int val = -1000;
    int best = -1000;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            
            int hold = check(N, M, K, ActivePlayer, tab);
            if (tab[i][j] == 0 && hold == 0)
            {
                tab[i][j] = ActivePlayer;
                val = minimax( N, M, K, ActivePlayer, tab, 0, false);
                tab[i][j] = 0;
                
               
            }
            else {
                if (hold == ActivePlayer) val = 1;
                else if (hold != 0) val = -1;
            }
            if (val > best) best = val;
        }
    }

    if (best == 1) {
        if(ActivePlayer == 1) printf("FIRST_PLAYER_WINS \n");
        else printf("SECOND_PLAYER_WINS \n");
    }
    else if (best == -1) {
        if (ActivePlayer == 2) printf("FIRST_PLAYER_WINS \n");
        else printf("SECOND_PLAYER_WINS \n");
    }
    else if(best == 0)printf("BOTH_PLAYERS_TIE \n");
    
}