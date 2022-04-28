#include <stdio.h>
struct process
{
    int vote;
};
struct process p[20];
int request(int prn, int val)
{
    if (p[val].vote == 1)
    {
        return 0;
    }
    else if (p[val].vote == 0)
    {
        p[val].vote = 1;
        return 1;
    }
}
void sendrelease(int prn, int val)
{
    p[val].vote = 0;
}
int main()
{
    int i, j, n, grp, len, con, prn, val, count, v, princs = 0;
    int group[10][10];
    printf("How many process\n");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        printf("How many process in Group for P%d\n", i);
        scanf("%d", &len);
        group[i][0] = len;
        for (j = 1; j <= len; j++)
        {
            scanf("%d", &group[i][j]);
        }
    }
    // vote false - 0 true - 1
    for (i = 1; i <= n; i++)
    {
        p[i].vote = 0;
    }
    while (con)
    {
        count = 0;
        printf("1. Request\n");
        printf("2. Exit\n");
        printf("3. Process info\n");
        scanf("%d", &v);
        switch (v)
        {
        case 1:
            printf("Which proces no wants to send Request\n");
            scanf("%d", &prn);
            len = group[prn][0];
            for (j = 1; j <= len; j++)
            {
                val = group[prn][j];
                if (prn != val)
                    count += request(prn, val);
                if (count == (len - 1))
                {
                    printf("Process %d enter into CS\n", prn);
                    p[prn].vote = 1;
                    princs = prn;
                }
            }
            break;
        case 2:
            i = princs;
            if (i == 0)
                printf("No Process is in CS\n");
            else
            {
                printf("Process %d exits from Cs\n", i);
                len = group[i][0];
                for (j = 1; j <= len; j++)
                {
                    val = group[i][j];
                    if (i != val)
                        sendrelease(i, val);
                }
                p[i].vote = 0;
                princs = 0;
                i = 0;
            }
            break;
        case 3:
            for (i = 1; i <= n; i++)
            {
                len = group[i][0];
                printf("Process P%d groups members are", i);
                for (j = 1; j <= len; j++)
                {
                    printf("%d ", group[i][j]);
                }
                printf("\n Vote = %d\n\n", p[i].vote);
            }
            break;
        }
        printf("Continue \n");
        scanf("%d", &con);
    }
}
