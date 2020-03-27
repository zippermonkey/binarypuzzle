/*  将数独归约成SAT问题保存为cnf文件   */
#include "head.h"
int Generatecnf(void)
{

    int i = 0;
    int j = 0;
    int k = 0;

    FILE *fp = NULL;
    fp = fopen("puzzle.cnf", "w");
    int n = 8;
    printf("Please enter the order n(the file will be saved in puzzle.cnf): ");
    scanf("%d",&n);

    if(n<4||n%2==1)
    {
        printf("Please enter an even number greater than or equal to 4.\n");
        return 0;
    }


    int constraint1 = 0;
    constraint1 = 4*n*(n-2);
    int constraint2 = 0;
    int constraint3 = 0;
    int sum_dm = 1;
    int sum_ne = 1;
    for (i = 1, j = n; i <= n / 2 - 1; i++, j--)
    {
        sum_dm *= i;
        sum_ne *= j;
    }
    constraint2 = 4*n*(sum_ne)/(sum_dm);
    constraint3 = n*(n-1)*(10*n+1);
    fprintf(fp, "p cnf %d %d\n", n * n + n * (n - 1) * (3 * n + 1), constraint1+constraint2+constraint3);

    // 约束1
    for (i = 1; i <= n; i++)
    {
        // 行
        for (j = 1; j <= n - 2; j++)
        {
            int a = n * (i - 1) + j;
            fprintf(fp, "%d %d %d 0\n", a, a + 1, a + 2);
            fprintf(fp, "%d %d %d 0\n", -a, -(a + 1), -(a + 2));
        }
        // 列
        if (i > n - 2)
            continue;
        for (j = 1; j <= n; j++)
        {
            int b = n * (i - 1) + j; // i行j列
            fprintf(fp, "%d %d %d 0\n", b, b + n, b + n + n);
            fprintf(fp, "%d %d %d 0\n", -b, -b - n, -b - n - n);
        }
    }

    // 约束2
    int *array = (int *)malloc(sizeof(int) * (n / 2 + 1));
    int base = n / 2;
    int change = n / 2;

    for (i = 0; i < n / 2 + 1; i++)
    {
        array[i] = i + 1;
    }
    int re = 0;
    while (base >= 0)
    {
        for (k = 0; k < n; k++)
        {
            //  行
            for (i = 0; i < n / 2 + 1; i++)
            {
                fprintf(fp, "%d ", array[i] + 8 * k);
            }
            fprintf(fp, "0\n");
            for (i = 0; i < n / 2 + 1; i++)
            {
                fprintf(fp, "%d ", -(array[i] + 8 * k));
            }
            fprintf(fp, "0\n");

            for (i = 0; i < n / 2 + 1; i++)
            {
                fprintf(fp, "%d ", ((array[i] - 1) * 8 + 1) + k);
            }
            fprintf(fp, "0\n");
            for (i = 0; i < n / 2 + 1; i++)
            {
                fprintf(fp, "%d ", -(((array[i] - 1) * 8 + 1) + k));
            }
            fprintf(fp, "0\n");
        }
        while (array[change] < n)
        {
            array[change]++;
            for (k = 0; k < n; k++)
            {
                //  行
                for (i = 0; i < n / 2 + 1; i++)
                {
                    fprintf(fp, "%d ", array[i] + 8 * k);
                }
                fprintf(fp, "0\n");
                for (i = 0; i < n / 2 + 1; i++)
                {
                    fprintf(fp, "%d ", -(array[i] + 8 * k));
                }
                fprintf(fp, "0\n");

                for (i = 0; i < n / 2 + 1; i++)
                {
                    fprintf(fp, "%d ", ((array[i] - 1) * 8 + 1) + k);
                }
                fprintf(fp, "0\n");
                for (i = 0; i < n / 2 + 1; i++)
                {
                    fprintf(fp, "%d ", -(((array[i] - 1) * 8 + 1) + k));
                }
                fprintf(fp, "0\n");
            }
        }
        while (change >= 0 && array[change] >= n)
        {
            change--;
            array[change]++;
        }
        if (array[0] == n / 2 + 1)
            break;
        do
        {
            re = 0;
            for (j = change + 1; j <= n / 2; j++)
            {

                array[j] = array[j - 1] + 1;
                if (array[j] == n && j != n / 2)
                {
                    re = 1;
                    change--;
                    array[change]++;
                }
            }
        }
        while (re == 1);

        if (base > change)
            base = change;
        change = n / 2;
    }

    // 约束3
    int x = n * n + 1, y = n * n + 2, z = n * n + 3; // 三个辅助变元  * n 次  65 66 67，   68 69 70， ...
    int all;                                         // 最后把整个聚起来的辅助变元
    all = n*n;

    for (int a = 1; a <= (n - 1); a++)
    {
        for (int b = a + 1; b <= n; b++)
        {
            x = all + 1;
            y = x + 1;
            z = y + 1;
            for (i = 1; i <= n; i++)
            {
                // 行

                fprintf(fp, "%d %d 0\n", n * (a - 1) + i, -x); // a  相关
                fprintf(fp, "%d %d 0\n", n * (b - 1) + i, -x); // b  相关
                fprintf(fp, "%d %d %d 0\n", -(n * (a - 1) + i), -(n * (b - 1) + i), x);

                fprintf(fp, "%d %d 0\n", -(n * (a - 1) + i), -y); // a  相关
                fprintf(fp, "%d %d 0\n", -(n * (b - 1) + i), -y); // b  相关
                fprintf(fp, "%d %d %d 0\n", n * (a - 1) + i, n * (b - 1) + i, y);

                fprintf(fp, "%d %d 0\n", z, -x);
                fprintf(fp, "%d %d 0\n", z, -y);
                fprintf(fp, "%d %d %d 0\n", -z, x, y);

                if (i < n)
                {
                    x = z + 1;
                    y = x + 1;
                    z = y + 1;
                }
            }
            all = z + 1;
            //  还有n+1个子句

            for (i = n; i >= 1; i--)
            {
                fprintf(fp, "%d %d 0\n", all - i, all);
            }

            for (i = n; i >= 1; i--)
            {
                fprintf(fp, "%d ", -(all - i));
            }
            fprintf(fp, "%d 0\n", -all);

            x = all + 1;
            y = x + 1;
            z = y + 1;
            for (i = 1; i <= n; i++)
            {
                // 列

                fprintf(fp, "%d %d 0\n", n * (i - 1) + a, -x); // a  相关
                fprintf(fp, "%d %d 0\n", n * (i - 1) + b, -x); // b  相关
                fprintf(fp, "%d %d %d 0\n", -(n * (i - 1) + a), -(n * (i - 1) + b), x);

                fprintf(fp, "%d %d 0\n", -(n * (i - 1) + a), -y); // a  相关
                fprintf(fp, "%d %d 0\n", -(n * (i - 1) + b), -y); // b  相关
                fprintf(fp, "%d %d %d 0\n", n * (i - 1) + a, n * (i - 1) + b, y);

                fprintf(fp, "%d %d 0\n", z, -x);
                fprintf(fp, "%d %d 0\n", z, -y);
                fprintf(fp, "%d %d %d 0\n", -z, x, y);

                if (i < n)
                {
                    x = z + 1;
                    y = x + 1;
                    z = y + 1;
                }
            }
            all = z + 1;
            //  还有n+1个子句

            for (i = n; i >= 1; i--)
            {
                fprintf(fp, "%d %d 0\n", all - i, all);
            }

            for (i = n; i >= 1; i--)
            {
                fprintf(fp, "%d ", -(all - i));
            }
            fprintf(fp, "%d 0\n", -all);
        }
    }

    fclose(fp);
    char filename[81];
    startDPLL(filename);
    printf("Successful!\n");
    displaysudoku(n);
    return 1;
}

int displaysudoku(int n)
{
    FILE *fp = NULL;
    if ((fp = fopen("sb", "r") )== NULL)
    {

        exit(1);
    }


    int i = 0;
    int j = 0;
    int temp, display;
    for(i = 0; i<n; i++)
    {
        for(j = 0; j<n; j++)
        {
            fscanf(fp,"%d %d\n",&temp,&display);
            printf("|%d",display);
        }
        printf("|\n");
    }
     fclose(fp);
     return 1;
}
