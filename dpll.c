#include "head.h"

void assign(Clause *root, int var)
{
    // 赋值
    valuation[abs(var)] = (var > 0) ? 1 : 0;

    Clause *itr = root->next;
    Clause *prevclause = root;
    Clause *temp = NULL;
    while (itr)
    {
        Literal *l = itr->head;
        Literal *prevliteral = NULL;
        while (l)
        {
            if (l->index == var)
            {
                //  将当前itr子句删除
                temp = itr;
                prevclause->next = itr->next;
                itr = prevclause;
                // removeclause(temp);
                break;
            }
            else if (l->index == -var)
            {
                // 将当前l删除
                if (prevliteral == NULL)
                {
                    itr->head = l->next;
                    // removeliteral(l);
                    l = itr->head;
                }
                else
                {
                    prevliteral->next = l->next;
                    // removeliteral(l);
                    l = prevliteral->next;
                }
                continue;
            }
            prevliteral = l;
            l = l->next;
        }
        prevclause = itr;
        itr = itr->next;
    }
}

int findunitclause(Clause *root)
{
    Clause *itr = root->next;
    while (itr)
    {
        if (itr->head && !itr->head->next)
            return itr->head->index;

        itr = itr->next;
    }
    return 0;
}

Clause *cloneClause(Clause *origin)
{
    Clause *cloneClause = (Clause *)malloc(sizeof(Clause));
    cloneClause->head = NULL;
    cloneClause->next = NULL;
    Literal *iteratorLiteral = origin->head;
    Literal *previousLiteral = NULL;

    while (iteratorLiteral)
    {
        Literal *literalClone = (Literal *)malloc(sizeof(Literal));
        literalClone->next = NULL;
        literalClone->index = iteratorLiteral->index;
        if (cloneClause->head == NULL)
            cloneClause->head = literalClone;
        if (previousLiteral != NULL)
        {
            previousLiteral->next = literalClone;
        }
        previousLiteral = literalClone;
        iteratorLiteral = iteratorLiteral->next;
    }
    cloneClause->num = origin->num;
    return cloneClause;
}

Clause *branch(Clause *root, int var)
{
    Clause *itr = root;
    Clause *newclone = NULL;
    Clause *prev = NULL;
    while (itr)
    {
        Clause *clone = cloneClause(itr);
        if (newclone == NULL)
            newclone = clone;
        if (prev != NULL)
            prev->next = clone;
        prev = clone;
        itr = itr->next;
    }

    // 加一个包含literalIndex 的单位子句 方便回溯;
    // 以保证回溯选取的是同一个文字
    Clause *addClause = createClause();
    Literal *addLiteral = createLiteral();
    addLiteral->index = var;
    addClause->head = addLiteral;
    addClause->next = newclone->next;
    newclone->next = addClause;
    // printClauseSet(newclone);
    return newclone;
}

int choosevar(Clause *root)
{
    Clause *itr = root->next;
    int flag = 0;
    while (itr)
    {
        if (itr->num <= 2 && itr->num != 0)
        {
            flag = 1;
            break;
        }
        itr = itr->next;
    }
    if (flag == 1)
        return itr->head->index;
    else
        return root->next->head->index;
}

int IsEmptyClause(Clause *root)
{
    Clause *tmp = root->next;
    while (tmp)
    {
        if (!tmp->head)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

int findPureLiteral(Clause *root)
{
    Clause *itr = root->next;
    int *literalLookup = (int *)malloc(sizeof(int) * (variableNumber + 1));
    int i = 0;
    for (i = 0; i < variableNumber + 1; i++)
        literalLookup[i] = 0;
    while (itr != NULL)
    {
        Literal *l = itr->head;
        while (l != NULL)
        {
            int seen = literalLookup[abs(l->index)];
            if (seen == 0)
                literalLookup[abs(l->index)] = sign(l->index);
            else if (seen == 1 && sign(l->index) == -1)
                literalLookup[abs(l->index)] = 2;

            else if (seen == -1 && sign(l->index) == 1)
                literalLookup[abs(l->index)] = 2;
            l = l->next;
        }
        itr = itr->next;
    }
    for (i = 1; i < variableNumber + 1; i++)
    {
        if (literalLookup[i] == 1 || literalLookup[i] == -1)
            return i * literalLookup[i];
    }
    return 0;
}

int dpll(Clause *root)
{
    Clause *tmp = root;
    int unitvar = findunitclause(tmp);
    // printClauseSet(tmp);
    while (unitvar)
    {
        assign(tmp, unitvar);
        // printClauseSet(tmp);
        if (tmp->next == NULL)
            return 1;
        else if (IsEmptyClause(tmp))
            return 0;
        unitvar = findunitclause(tmp);
    }

    int pureliteral = findunitclause(tmp);
    while (pureliteral)
    {
        assign(tmp, pureliteral);
        // printClauseSet(tmp);
        if (tmp->next == NULL)
            return 1;
        else if (IsEmptyClause(tmp))
            return 0;
        pureliteral = findunitclause(tmp);
    }

    int var = choosevar(root);
    if (dpll(branch(root, var)))
        return 1;
    return dpll(branch(root, -var));
}

void printClauseSet(Clause *root)
{
    Clause *itr = root->next;
    while (itr != NULL)
    {
        Literal *l = itr->head;
        while (l != NULL)
        {
            printf("%d ", l->index);
            l = l->next;
        }
        putchar('\n');
        itr = itr->next;
    }
}

int sign(int x)
{
    return (x > 0) ? 1 : -1;
}


void startDPLL(char * filename)
{
    clock_t start_time, end_time;
    printf("input a cnf filename: ");
    scanf("%s", filename);
    Clause *root = readClauseSet(filename);
    if(root == NULL)
    {
        return ;
    }


    start_time = clock();
    int sta = dpll(root);
    end_time = clock();
    if (sta == 1) // SAT
    {
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
        printf("UNSAT\n");
    }
    printf("\n  %ldms\n", end_time - start_time);
}
