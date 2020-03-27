#include "head.h"

int main()
{

    char filename[81];
    int a = -1;


    while(a)
    {
        system("cls");
        Mainmenu();
        a = Getchoose();
        switch(a)
        {
        case 1:
            // Puzzle
            while(a)
            {
                system("cls");
                Puzzlemenu();
                a = Getchoose();
                if(a==1)
                {
                    // Generate
                    Generatecnf();
                    getchar();
                    getchar();
                }
                else if (a == 2||a==0)
                {
                    // Return
                    break;
                }
            }
            break;
        case 2:
            // SAT
            // startDPLL(filename);
            while(a)
            {
                system("cls");
                SATmenu();
                a = Getchoose();
                if(a==1)
                {
                    // Compute
                    startDPLL(filename);
                    getchar();
                    getchar();
                }
                else if(a == 2)
                {
                    printf("input a cnf filename: ");
                    scanf("%s", filename);
                    if(verify(readClauseSet(filename)) == 1)
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
                else if(a==3||a==0)
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

