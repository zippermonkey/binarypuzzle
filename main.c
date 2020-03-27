#include "head.h"

int main()
{

    char filename[81];
    int a = -1;

    while (a)
    {
        system("cls");
        Mainmenu();
        a = Getchoose();
        switch (a)
        {
        case 1:
            // Puzzle
            while (a)
            {
                system("cls");
                Puzzlemenu();
                a = Getchoose();
                if (a == 1)
                {
                    // Generate
                    Generatecnf();
                    getchar();
                    getchar();
                }
                else if (a == 2 || a == 0)
                {
                    // Return
                    break;
                }
            }
            break;
        case 2:
            // SAT
            // startDPLL(filename);
            while (a)
            {
                system("cls");
                SATmenu();
                a = Getchoose();
                if (a == 1)
                {
                    // Compute
                    printf("input a cnf filename: ");
                    scanf("%s", filename);
                    if (startDPLL(filename) == 1)
                    {
                        // SAT
                        printf("SAT\n");
                        int i = 1;
                        for (i = 1; i <= variableNumber; i++)
                            printf("%d   %d\n", i, valuation[i]);
                        // write file
                        printf("input a filename to save answer: ");
                        scanf("%s", filename);
                        saveanswer(filename);
                    }
                    else
                    {
                        // UNSAT
                        printf("UNSAT\n");
                    }

                    getchar();
                    getchar();
                }
                else if (a == 2)
                {
                    // 验证
                    printf("input a cnf filename: ");
                    scanf("%s", filename);
                    if (verify(readClauseSet(filename)) == 1)
                    {
                        printf("CORRECT\n");
                    }
                    else
                    {
                        printf("ERROR\n");
                    }
                    getchar();
                    getchar();
                }
                else if (a == 3 || a == 0)
                {
                    break;
                }
            }
            break;
        case 0:
            // QUIT
            break;
        default:
            // 错误处理
            break;
        }
    }
    return 0;
}
