#include "head.h"

// 返回一个空子句
Clause *createClause()
{
    Clause *instance = (Clause *)malloc(sizeof(Clause));
    instance->head = NULL;
    instance->next = NULL;
    instance->num = 0;
    return instance;
}

// 返回一个空文字
Literal *createLiteral()
{
    Literal *instance = (Literal *)malloc(sizeof(Literal));
    instance->index = 0;
    instance->next = NULL;
    return instance;
}

// 读取文件
Clause *readClauseSet(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp)
        printf("%s\n", filename);
    else if (!fp)
    {
        printf("ERROR!!!!!\n");
        return NULL;
    }

    char line[256];

    char *token;
    Clause *root = (Clause *)malloc(sizeof(Clause));
    root->head = NULL;
    root->next = NULL;
    Clause *currentClause = NULL, *previousClause = NULL;
    Literal *currentLiteral = NULL, *previousLiteral = NULL;

    while (fgets(line, sizeof(line), fp))
    {
        // ignore comment lines
        if (line[0] == 'c')
            continue;
        // this line is metadata information
        if (line[0] == 'p')
        {
            sscanf(line, "p cnf %d %d", &variableNumber, &clauseNumber);
            valuation = (int *)calloc(variableNumber + 1, sizeof(int));
            int i;
            for (i = 0; i < variableNumber + 1; i++)
                valuation[i] = -1;
        }
        else
        {
            // create a clause for each line
            currentClause = createClause();
            if (root->next ==  NULL)
            {
                root->next = currentClause;
            }
            else if (previousClause != NULL)
            {
                previousClause->next = currentClause;
            }

            // split the line by the space characted and parse integers as literals
            token = strtok(line, " ");
            while (token != NULL)
            {
                int literalIndex = atoi(token);
                currentLiteral = createLiteral();
                currentLiteral->index = literalIndex;
                if (literalIndex != 0)
                {
                    currentClause->num++;
                    if (currentClause->head == NULL)
                    {
                        currentClause->head = currentLiteral;
                    }
                    if (previousLiteral != NULL)
                    {
                        previousLiteral->next = currentLiteral;
                    }
                }
                previousLiteral = currentLiteral;
                token = strtok(NULL, " ");
            }
            previousClause = currentClause;
        }
    }
    fclose(fp);

    return root;
}
