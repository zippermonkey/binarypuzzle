/* veritify */
// from valuation array

// 只要子句有一个满足即可

#include "head.h"
int verify(Clause *root)
{
    if(root == NULL)
    {
        return -2;
    }
    printf("Please input filename of answer: ");
    char filename[81];
    scanf("%s",filename);
    int lines = Statisticsrows(filename);

    if(lines!=variableNumber)
    {
        printf("Cnf file does not match answer file.\n");
        return -1;
    }
    else
    {
        // 将答案保存到valuation数组里面
        FILE *fp = NULL;
        if((fp = fopen(filename,"r")) == NULL)
        {
            printf("ERROR!!!!!\n");
            return -1;
        }
        int var = 0;
        int value = -2;
        for(int i = 0;i<variableNumber;i++)
        {
            fscanf(fp,"%d %d",&var,&value);
            valuation[var] = value;
        }
    }

    // 0 --- 不满足   1 ---- 满足
    int clauseflag = 0; // 子句满足
    Clause *itr = root->next;
    // 遍历
    while (itr)
    {
        clauseflag = 0;
        Literal *l = itr->head;
        while (l)
        {
            if(valuation[abs(l->index)]==-1)
            {
                l = l->next;
                continue;
            }
            if (sign(valuation[abs(l->index)]) == sign(l->index))
                // TRUE
            {
                clauseflag = 1;
                break;
            }
            l = l->next;
        }
        if (clauseflag == 0)
        {
            return 0;
        }

        itr = itr->next;
    }
    return 1;
}

int Statisticsrows(char * filename)
{
    FILE *fp = NULL;
    char buf[10];
    fp = fopen(filename, "r");
    if(!fp)
        printf("ERROR\n");
    int count = 0;
    while (fgets(buf, sizeof(buf), fp) != NULL)
        count++;

    fclose(fp);

    return count;
}
