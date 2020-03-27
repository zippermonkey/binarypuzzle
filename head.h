#ifndef HEAD
#define HEAD

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 数据结构定义
typedef struct literal
{
    int index;
    struct literal *next;
} Literal;

typedef struct clause
{
    Literal *head;
    struct clause *next;
    int num;
} Clause;

// 全局变量
int variableNumber, clauseNumber;
int *valuation;


// 生成空子句
Clause *createClause();

// 生成空文字
Literal *createLiteral();

// 读取cnf文件
Clause *readClauseSet(char *filename);

void assign(Clause *root, int var);
int findunitclause(Clause *root);
Clause *cloneClause(Clause *origin);
Clause *branch(Clause *root, int var);
int choosevar(Clause *root);
int IsEmptyClause(Clause *root);
int dpll(Clause *root);
void printClauseSet(Clause *root);
int sign(int x);
int saveanswer(char *filename);
int verify(Clause * root);
void startDPLL(char*);
// 菜单
void Mainmenu();
void Puzzlemenu();
int Getchoose();
void SATmenu();

int Statisticsrows(char * filename);
int Generatecnf(void);

#endif // HEAD
