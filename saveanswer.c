#include "head.h"

int saveanswer(char *filename)
{
    FILE *fp = NULL;
    if ((fp = fopen(filename, "w") )== NULL)
    {
        printf("can not open %s.\n", filename);
        exit(1);
    }
    int i = 0;
    for (i = 1; i <= variableNumber; i++)
    {
        fprintf(fp, "%d %d\n", i, valuation[i]);
    }
    fclose(fp);
    return 1;
}
