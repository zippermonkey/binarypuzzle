/* 简单的菜单  按照文档的程序逻辑 */
#include "head.h"

void Mainmenu()
{
    // 主菜单
    printf("\t1. Puzzle\t2. SAT\n");
    printf("\t0. Quit\n");
}

void Puzzlemenu()
{
    // Puzzle菜单
    printf("\t1. Generate\t2. Return\n");
    printf("\t0. Quit\n");
}

void SATmenu()
{
    // DPLL菜单
    printf("\t1. Compute\t2. Verify\n");
    printf("\t3. Return\t0. Quit\n");
}


int Getchoose()
{
    int x = -1;
    printf("Please input x: ");
    scanf("%d",&x);
    return x;
}

