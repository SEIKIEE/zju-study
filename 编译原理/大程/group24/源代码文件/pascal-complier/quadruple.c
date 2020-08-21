#include "quadruple.h"

void initQuadList(){
    QuadListHead = (pQuad)malloc(sizeof(struct Quad));
    QuadListHead->next = NULL;
    QuadListEnd = QuadListHead;
}
char* getTempName() {
    static int nameCnt = 0;
    char* res = malloc(sizeof(char)*10);
    sprintf(res, "var%d", nameCnt);
    nameCnt++;
    return res;
}
char* getTempLabel() {
    static int labelCnt = 0;
    char* res = malloc(sizeof(char)*10);
    sprintf(res, "L%d", labelCnt);
    labelCnt++;
    return res;
}
void genCode(SyntaxTree node, char* resName) {
    if (node == NULL) {
        return;
    }
    /*typedef enum {
     StatementNode,
     ExpressionNode,
     DeclareNode,
     TypeNode
     } NodeKind; // 节点属性：语句、表达式、定义
     */
    switch (node->nodeKind)
    {
        case StatementNode: {
            /*typedef enum {
             LabelStmt,  //1个孩子
             AssignStmt, //
             GotoStmt,   //没有孩子
             IfStmt,     //3个孩子
             RepeatStmt, //2个孩子
             WhileStmt,  //2个孩子
             ForStmt,    //4个孩子
             CaseStmt,   //2个孩子
             ProcIdStmt,
             ProcSysStmt, //一个孩子，是函数参数
             FuncIdStmt,  //函数的ID，后面会是（参数列表），所以是有一个孩子
             FuncSysStmt  //系统函数，孩子是参数列表
             } StmtKind; // 语句类型 */
            switch (node->kind.stmt)
            {
                case LabelStmt: {
                    //1个孩子
                    genCode(node->child[0], resName);
                    break;
                }
                case AssignStmt: {
                    if (node->child[0]->type == ArrayExpType) {
                        //ID LB expression RB ASSIGN expression child0:ID, child1: expression, child2:expression
                        //生成第一个expression
                        char* tempName1;
                        tempName1 = getTempName();
                        genCode(node->child[1], tempName1);
                        //生成第二个expression
                        char* tempName2;
                        tempName2 = getTempName();
                        genCode(node->child[2], tempName2);
                        //生成 id[t1] = t2: addr3[addr1] = addr2
                        pQuad q = (pQuad)malloc(sizeof(struct Quad));
                        q->op = array1;
                        q->addr3.kind = String;
                        //char name[20];
                        char* name = malloc(sizeof(char)*20);
                        sprintf(name,"temp%s", node->child[0]->attr.name);
                        q->addr3.contents.name = name;
                        q->addr1.kind = String;
                        q->addr1.contents.name = tempName1;
                        q->addr2.kind = String;
                        q->addr2.contents.name = tempName2;
                        q->next = NULL;
                        QuadListEnd->next = q;
                        QuadListEnd = QuadListEnd->next;
                        
                    }
                    else if (node->child[0]->type == RecordExpType) {
                        //ID DOT ID ASSIGN expression child0:ID, child1:expression
                        
                        
                        
                    }
                    else {
                        //ID ASSIGN expression child0:ID, cjild1:expression
                        
                        //id = t: addr3 = addr1
                        pQuad q = (pQuad)malloc(sizeof(struct Quad));
                        q->op = assign;
                        q->addr3.kind = String;
                        //char name[20];
                        char* name = malloc(sizeof(char)*20);
                        sprintf(name,"temp%s", node->child[0]->attr.name);
                        q->addr3.contents.name = name;
                        //q->addr3.contents.name = node->child[0]->attr.name;
                        
                        char* tempName;
                        if(node->child[1]->nodeKind==ExpressionNode && node->child[1]->kind.exp ==IdExp){
                            tempName = node->child[1]->attr.name;
                            q->addr1.kind = String;
                            //char name[20];
                            char* name = malloc(sizeof(char)*20);
                            sprintf(name,"temp%s", tempName);
//                            q->addr3.contents.name = name;
                            q->addr1.contents.name = name;
                        }
                        else if(node->child[1]->nodeKind==ExpressionNode && node->child[1]->kind.exp == ConstExp){
                            
                            switch (node->child[1]->type)
                            {
                                case IntExpType:
                                    q->addr1.kind = IntConst;
                                    q->addr1.contents.intVal = node->child[1]->attr.intValue;
                                    break;
                                case RealExpType:
                                    q->addr1.kind = RealConst;
                                    q->addr1.contents.realVal = node->child[1]->attr.realValue;
                                    break;
                                case CharExpType:
                                    q->addr1.kind = String;
                                    char name[10];
                                    sprintf(name, "%c", node->child[1]->attr.charValue);
                                    q->addr1.contents.name = name;
                                    break;
                                case StringExpType:
                                    q->addr1.kind = String;
                                    q->addr1.contents.name = node->child[1]->attr.stringValue;
                                    break;
                                case BoolExpType:
                                    q->addr1.kind = IntConst;
                                    q->addr1.contents.intVal = node->child[1]->attr.intValue;
                                    break;
                                default:
                                    break;
                            }
                            
                            
                            
                        }
                        else{
                            tempName = getTempName();
                            genCode(node->child[1], tempName);
                            q->addr1.kind = String;
                            q->addr1.contents.name = tempName;
                        }
                         
                        q->next = NULL;
                        QuadListEnd->next = q;
                        QuadListEnd = QuadListEnd->next;
                    }
                    break;
                }
                case GotoStmt: {
                    //goto addr3
                    pQuad q = (pQuad)malloc(sizeof(struct Quad));
                    q->op = gotolab;
                    q->addr3.kind = IntConst;
                    q->addr3.contents.intVal = node->attr.intValue;
                    q->next = NULL;
                    QuadListEnd->next = q;
                    QuadListEnd = QuadListEnd->next;
                    break;
                }
                case IfStmt: {
                    //IF expression THEN stmt else_clause, child0:expression, child1:stmt, child2:else_clause
                    //IF expression THEN stmt
                    //生成expression的code
                    char* tempName1;
                    tempName1 = getTempName();
                    genCode(node->child[0], tempName1);
                    //生成label
                    char* tempLabel1;
                    tempLabel1 = getTempLabel();
                    // if_false tempName1 goto L1: if_false addr1 goto addr2
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = if_f_goto;
                    q1->addr1.kind = String;
                    q1->addr1.contents.name = tempName1;
                    q1->addr2.kind = String;
                    q1->addr2.contents.name = tempLabel1;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    //生成stmt的code
                    genCode(node->child[1], resName);
                    //label tempLabel1: label addr3
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = lab;
                    q2->addr3.kind = String;
                    q2->addr3.contents.name = tempLabel1;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    if (node->child[2] != NULL) {
                        //有else，相当于if t1 goto L2; stmt2; L2
                        // if t1 goto label: if addr1 goto addr2
                        char* tempLabel2;
                        tempLabel2 = getTempLabel();
                        pQuad q3 = (pQuad)malloc(sizeof(struct Quad));
                        q3->op = if_goto;
                        q3->addr1.kind = String;
                        q3->addr1.contents.name = tempName1;
                        q3->addr2.kind = String;
                        q3->addr2.contents.name = tempLabel2;
                        q3->next = NULL;
                        QuadListEnd->next = q3;
                        QuadListEnd = QuadListEnd->next;
                        //生成stmt2的code
                        genCode(node->child[2], resName);
                        //label tempLabel2: label addr3
                        pQuad q4 = (pQuad)malloc(sizeof(struct Quad));
                        q4->op = lab;
                        q4->addr3.kind = String;
                        q4->addr3.contents.name = tempLabel2;
                        q4->next = NULL;
                        QuadListEnd->next = q4;
                        QuadListEnd = QuadListEnd->next;
                    }
                    
                    break;
                }
                case RepeatStmt: {
                    //
                    break;
                }
                case WhileStmt: {
                    //WHILE expression DO stmt: child0:expression, child1:stmt
                    /*    label L1
                     tempName1 = result of expression1
                     if_f temName1 goto L2
                     stmt
                     goto L1
                     label L2
                     */
                    //label L1
                    //生成label
                    char* tempLabel1;
                    tempLabel1 = getTempLabel();
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = lab;
                    q1->addr3.kind = String;
                    q1->addr3.contents.name = tempLabel1;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    //生成expression到tempName1
                    char* tempName1;
                    tempName1 = getTempName();
                    genCode(node->child[0], tempName1);
                    
                    //if_false tempName1 goto Label2
                    char* tempLabel2;
                    tempLabel2 = getTempLabel();
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = if_f_goto;
                    q2->addr1.kind = String;
                    q2->addr1.contents.name = tempName1;
                    q2->addr2.kind = String;
                    q2->addr2.contents.name = tempLabel2;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    
                    //生成stmt
                    genCode(node->child[1], resName);
                    
                    //goto L1
                    //goto addr3
                    pQuad q3 = (pQuad)malloc(sizeof(struct Quad));
                    q3->op = gotolab;
                    q3->addr3.kind = String;
                    q3->addr3.contents.name = tempLabel1;
                    q3->next = NULL;
                    QuadListEnd->next = q3;
                    QuadListEnd = QuadListEnd->next;
                    
                    //label L2
                    pQuad q4 = (pQuad)malloc(sizeof(struct Quad));
                    q4->op = lab;
                    q4->addr3.kind = String;
                    q4->addr3.contents.name = tempLabel2;
                    q4->next = NULL;
                    QuadListEnd->next = q4;
                    QuadListEnd = QuadListEnd->next;
                    break;
                }
                case ForStmt: {
                    //FOR ID ASSIGN expression TO(DOWNTO) expression DO stmt
                    /*    tempName1 = result of expression1
                     ID = tempName1
                     label L1
                     tempName2 = result of expression2
                     tempName3 = ID >(or<) tempName2
                     if tempName3 goto L2
                     stmt
                     ID = ID +(or-) 1
                     goto L1
                     label L2
                     */
                    //生成expression到tempName1
                    char* tempName1;
                    //ID = tempName1
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = assign;
                    q1->addr3.kind = String;
                    //char name[20];
                    char* name = malloc(sizeof(char)*20);
                    sprintf(name,"temp%s", node->child[0]->attr.name);
                    q1->addr3.contents.name = name;
                    //q1->addr3.contents.name = node->child[0]->attr.name;
                    if(node->child[1]->nodeKind==ExpressionNode && node->child[1]->kind.exp ==IdExp){
                        tempName1 = node->child[1]->attr.name;
                        q1->addr1.kind = String;
                        //char name[20];
                        char* name = malloc(sizeof(char)*20);
                        sprintf(name,"temp%s", tempName1);
                        q1->addr1.contents.name = name;
                    }
                    else if(node->child[1]->nodeKind==ExpressionNode && node->child[1]->kind.exp == ConstExp){
                        
                        switch (node->child[1]->type)
                        {
                            case IntExpType:
                                q1->addr1.kind = IntConst;
                                q1->addr1.contents.intVal = node->child[1]->attr.intValue;
                                break;
                            case RealExpType:
                                q1->addr1.kind = RealConst;
                                q1->addr1.contents.realVal = node->child[1]->attr.realValue;
                                break;
                            case CharExpType:
                                q1->addr1.kind = String;
                                char name[10];
                                sprintf(name, "%c", node->child[1]->attr.charValue);
                                q1->addr1.contents.name = name;
                                break;
                            case StringExpType:
                                q1->addr1.kind = String;
                                q1->addr1.contents.name = node->child[1]->attr.stringValue;
                                break;
                            case BoolExpType:
                                q1->addr1.kind = IntConst;
                                q1->addr1.contents.intVal = node->child[1]->attr.intValue;
                                break;
                            default:
                                break;
                        }
                        
                        
                        
                    }
                    else{
                        tempName1 = getTempName();
                        genCode(node->child[1], tempName1);
                        q1->addr1.kind = String;
                        q1->addr1.contents.name = tempName1;
                    }
                    
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    //label L1
                    char* tempLabel1;
                    tempLabel1 = getTempLabel();
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = lab;
                    q2->addr3.kind = String;
                    q2->addr3.contents.name = tempLabel1;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    //tempName2 = result of expression2
                    char* tempName2;
                    tempName2 = getTempName();
                    genCode(node->child[2], tempName2);
                    //tempName3 = ID >(or<) tempName2
                    char* tempName3;
                    tempName3 = getTempName();
                    pQuad q3 = (pQuad)malloc(sizeof(struct Quad));
                    if (node->attr.op == ToOp) {
                        q3->op = gt; //greater than
                    }
                    else if (node->attr.op == DowntoOp) {
                        q3->op = lt; //less than
                    }
                    q3->addr3.kind = String;
                    q3->addr3.contents.name = tempName3;
                    //char name2[20];
                    char* name2 = malloc(sizeof(char)*20);
                    sprintf(name2,"temp%s", node->child[0]->attr.name);
                    q3->addr1.kind = String;
                    q3->addr1.contents.name = name2;
                    //q3->addr1.contents.name = node->child[0]->attr.name;
                    q3->addr2.kind = String;
                    q3->addr2.contents.name = tempName2;
                    q3->next = NULL;
                    QuadListEnd->next = q3;
                    QuadListEnd = QuadListEnd->next;
                    //if tempName3 goto L2
                    char* tempLabel2;
                    tempLabel2 = getTempLabel();
                    pQuad q4 = (pQuad)malloc(sizeof(struct Quad));
                    q4->op = if_goto;
                    q4->addr1.kind = String;
                    q4->addr1.contents.name = tempName3;
                    q4->addr2.kind = String;
                    q4->addr2.contents.name = tempLabel2;
                    q4->next = NULL;
                    QuadListEnd->next = q4;
                    QuadListEnd = QuadListEnd->next;
                    //stmt
                    genCode(node->child[3], resName);
                    //ID=ID+1 or ID=ID-1
                    pQuad q5 = (pQuad)malloc(sizeof(struct Quad));
                    if (node->attr.op == ToOp) {
                        q5->op = plus;
                    }
                    else if (node->attr.op == DowntoOp) {
                        q5->op = sub;
                    }
                    //char name3[20];
                    char* name3 = malloc(sizeof(char)*20);
                    sprintf(name3,"temp%s", node->child[0]->attr.name);
                    q5->addr3.kind = String;
                    //q5->addr3.contents.name = node->child[0]->attr.name;
                    q5->addr3.contents.name = name3;
                    q5->addr1.kind = String;
                    //q5->addr1.contents.name = node->child[0]->attr.name;
                    q5->addr1.contents.name = name3;
                    q5->addr2.kind = IntConst;
                    q5->addr2.contents.intVal = 1;
                    q5->next = NULL;
                    QuadListEnd->next = q5;
                    QuadListEnd = QuadListEnd->next;
                    //goto L1
                    pQuad q6 = (pQuad)malloc(sizeof(struct Quad));
                    q6->op = gotolab;
                    q6->addr3.kind = String;
                    q6->addr3.contents.name = tempLabel1;
                    q6->next = NULL;
                    QuadListEnd->next = q6;
                    QuadListEnd = QuadListEnd->next;
                    //label L2
                    pQuad q7 = (pQuad)malloc(sizeof(struct Quad));
                    q7->op = lab;
                    q7->addr3.kind = String;
                    q7->addr3.contents.name = tempLabel2;
                    q7->next = NULL;
                    QuadListEnd->next = q7;
                    QuadListEnd = QuadListEnd->next;
                    break;
                }
                case CaseStmt: {
                    //CASE expression OF case_expr_list END
                    /*    tempName0 = result of expression
                     (suppose n cases)
                     tempName1 = tempName0== case1.value
                     if_f tempName1 goto L1
                     stmt1
                     L1
                     tempName2 = tempName0== case2.value
                     if_f tempName2 goto L2
                     stmt2
                     L2
                     ...
                     tempNameN = tempName0== caseN.value
                     if_f tempNameN goto LN
                     stmtN
                     LN
                     */
                    char* tempName0;
                    if(node->child[0]->nodeKind==ExpressionNode && node->child[0]->kind.exp==IdExp){
                        tempName0 = node->child[0]->attr.name;
                        sprintf(tempName0, "temp%s", node->child[0]->attr.name);
                    }
                    else{
                        tempName0 = getTempName();
                        genCode(node->child[0], tempName0);
                    }
                    
                    SyntaxTree tmp = node->child[1];
                    while (tmp != NULL) {
                        //tempNamei = tempName0== tmp.attr.
                        char* tempNamei;
                        tempNamei = getTempName();
                        pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                        q1->op = eq;
                        q1->addr3.kind = String;
                        q1->addr3.contents.name = tempNamei;
                        q1->addr1.kind = String;
                        q1->addr1.contents.name = tempName0;
                        if (tmp->child[0]->kind.exp == IdExp) {
                            q1->addr2.kind = String;
                            //char name[20];
                            char* name = malloc(sizeof(char)*20);
                            sprintf(name,"temp%s", tmp->child[0]->attr.name);
                            q1->addr2.contents.name = name;
                            //q1->addr2.contents.name = tmp->child[0]->attr.name;
                        }
                        else if (tmp->child[0]->kind.exp == ConstExp) {
                            switch (tmp->child[0]->type)
                            {
                                case IntExpType:
                                    q1->addr2.kind = IntConst;
                                    q1->addr2.contents.intVal = tmp->child[0]->attr.intValue;
                                    break;
                                case RealExpType:
                                    q1->addr2.kind = RealConst;
                                    q1->addr2.contents.realVal = tmp->child[0]->attr.realValue;
                                    break;
                                case CharExpType:
                                    q1->addr2.kind = String;
                                    char name[10];
                                    sprintf(name, "%c", tmp->child[0]->attr.charValue);
                                    q1->addr2.contents.name = name;
                                    break;
                                case StringExpType:
                                    q1->addr2.kind = String;
                                    q1->addr2.contents.name = tmp->child[0]->attr.stringValue;
                                    break;
                                case BoolExpType:
                                    q1->addr2.kind = IntConst;
                                    q1->addr2.contents.intVal = tmp->child[0]->attr.intValue;
                                    break;
                                default:
                                    break;
                            }
                        }
                        q1->next = NULL;
                        QuadListEnd->next = q1;
                        QuadListEnd = QuadListEnd->next;
                        //if_f tempNamei goto Li
                        char* tempLabeli;
                        tempLabeli = getTempLabel();
                        pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                        q2->op = if_f_goto;
                        q2->addr1.kind = String;
                        q2->addr1.contents.name = tempNamei;
                        q2->addr2.kind = String;
                        q2->addr2.contents.name = tempLabeli;
                        q2->next = NULL;
                        QuadListEnd->next = q2;
                        QuadListEnd = QuadListEnd->next;
                        //stmti
                        genCode(tmp->child[1], resName);
                        //label Li
                        pQuad q3 = (pQuad)malloc(sizeof(struct Quad));
                        q3->op = lab;
                        q3->addr3.kind = String;
                        q3->addr3.contents.name = tempLabeli;
                        q3->next = NULL;
                        QuadListEnd->next = q3;
                        QuadListEnd = QuadListEnd->next;
                        tmp = tmp->sibling;
                    }
                    
                    break;
                }
                case ProcIdStmt: {
                    //语法树里没有
                    break;
                }
                case ProcSysStmt: {
                    if (node->attr.op == ReadOp) {
                        //READ LP factor RP
                        pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                        q1->op = rd;
                        
                        q1->addr3.kind = String;
                        //char name[20];
                        char* name = malloc(sizeof(char)*20);
                        sprintf(name,"temp%s", node->child[0]->attr.name);
                        q1->addr3.contents.name = name;
                        //q1->addr3.contents.name = node->child[0]->attr.name;
                        
                        q1->next = NULL;
                        QuadListEnd->next = q1;
                        QuadListEnd = QuadListEnd->next;
                    }
                    else if (node->attr.op == WriteOp) {
                        pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                        q1->op = wt;
                        if (node->child[0] == NULL) {
                            //WRITE
                            q1->addr3.kind = String;
                            q1->addr3.contents.name = " ";
                        }
                        else {
                            //WRITE LP expression_list RP
                            char* tempName1;
                            tempName1 = getTempName();
                            genCode(node->child[0],tempName1);
                            q1->addr3.kind = String;
                            q1->addr3.contents.name = tempName1;
                        }
                        q1->next = NULL;
                        QuadListEnd->next = q1;
                        QuadListEnd = QuadListEnd->next;
                    }
                    else if (node->attr.op == WritelnOp) {
                        pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                        q1->op = wtln;
                        if (node->child[0] == NULL) {
                            //WRITELN
                            q1->addr3.kind = String;
                            q1->addr3.contents.name = " ";
                        }
                        else {
                            //WRITELN LP expression_list RP
                            char* tempName1;
                            tempName1 = getTempName();
                            genCode(node->child[0],tempName1);
                            q1->addr3.kind = String;
                            q1->addr3.contents.name = tempName1;
                        }
                        q1->next = NULL;
                        QuadListEnd->next = q1;
                        QuadListEnd = QuadListEnd->next;
                    }
                    break;
                }
                case FuncIdStmt: {
                    //ID or ID LP args_list RP
                    /*
                     begin_args
                     arg (result of expression1)
                     ...
                     arg (result of expression n)
                     resName = call ID
                     */
                    //begin_args
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = beginargs;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    SyntaxTree tmp = node->child[0];
                    int paramCnt = 0;
                    while (tmp != NULL) {
                        paramCnt++;
                        char* tempNamei;
                        tempNamei = getTempName();
                        genCode(tmp, tempNamei);
                        pQuad qi = (pQuad)malloc(sizeof(struct Quad));
                        qi->op = argparam;
                        qi->addr3.kind = String;
                        qi->addr3.contents.name = tempNamei;
                        qi->next = NULL;
                        QuadListEnd->next = qi;
                        QuadListEnd = QuadListEnd->next;
                        tmp = tmp->sibling;
                    }
                    //resName = call ff
                    if(strcmp(resName,"ircode")==0){
                        resName = getTempName();
                    }
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    /*if (paramCnt > 0) {
                        q2->op = calln;
                        q2->addr1.kind = IntConst;
                        q2->addr1.contents.intVal = paramCnt;
                    }
                    else {
                        q2->op = call;
                    }*/
                    q2->op = valuefromcall;
                    q2->addr3.kind = String;
                    q2->addr3.contents.name = resName;
                    
                    q2->addr1.kind = String;
                    q2->addr1.contents.name = node->attr.name;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    
                    //resName = return value of f
                    /*if(strcmp(resName, "ircode")!=0){
                        pQuad q3 = (pQuad)malloc(sizeof(struct Quad));
                        q3->op = assign;
                        q3->addr3.kind = String;
                        q3->addr3.contents.name = resName;
                        q3->addr1.kind = String;
                        q3->addr1.contents.name = node->attr.name;
                        q3->next = NULL;
                        QuadListEnd->next = q3;
                        QuadListEnd = QuadListEnd->next;
                    }*/
                    
                    break;
                }
                case FuncSysStmt: {
                    //XXX LP args_list RP
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = beginargs;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    SyntaxTree tmp = node->child[0];
                    int paramCnt = 0;
                    while (tmp != NULL) {
                        paramCnt++;
                        char* tempNamei;
                        tempNamei = getTempName();
                        genCode(tmp, tempNamei);
                        pQuad qi = (pQuad)malloc(sizeof(struct Quad));
                        qi->op = argparam;
                        qi->addr3.kind = String;
                        qi->addr3.contents.name = tempNamei;
                        qi->next = NULL;
                        QuadListEnd->next = qi;
                        QuadListEnd = QuadListEnd->next;
                        tmp = tmp->sibling;
                    }
                    
                    
                    //call
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = call;
                    q2->addr3.kind = String;
                    char funcStr[20];
                    switch (node->attr.op) {
                        case ChrOp:
                            sprintf(funcStr, "chr");
                            break;
                        case OddOp:
                            sprintf(funcStr, "odd");
                            break;
                        case OrdOp:
                            sprintf(funcStr, "ord");
                            break;
                        case PredOp:
                            sprintf(funcStr, "pred");
                            break;
                        case SqrOp:
                            sprintf(funcStr, "sqr");
                            break;
                        case SqrtOp:
                            sprintf(funcStr, "sqrt");
                            break;
                        case SuccOp:
                            sprintf(funcStr, "succ");
                            break;
                        default:
                            break;
                    }
                    q2->addr3.kind = String;
                    q2->addr3.contents.name = funcStr;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    break;
                }
                default:
                    break;
            }
            //stmt通过sibling连接
            genCode(node->sibling, resName);
            
            break;
        }
        case ExpressionNode: {
            /*typedef enum {
             IdExp,      // 一个ID
             ConstExp,   // 常量 就是一个数字或者字符
             OpExp,      // 像1*2 有两个个孩子之类的
             CaseExp     // case形如 1:balabala 有两个孩子
             } ExpKind;  // 表达式类型
             */
            switch (node->kind.exp)
            {
                case IdExp: {
                    //TOKEN_ID
                    //resName = ID
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = assign;
                    q1->addr3.kind = String;
                    q1->addr3.contents.name = resName;
                    
                    q1->addr1.kind = String;
                    //char name[20];
                    char* name = malloc(sizeof(char)*20);
                    sprintf(name,"temp%s", node->attr.name);
                    q1->addr1.contents.name = name;
                    //q1->addr1.contents.name = node->attr.name;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    break;
                }
                case ConstExp: {
                    //INTEGER/REAL/CHAR/STRING/TRUE/...
                    //resName = ...
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = assign;
                    q1->addr3.kind = String;
                    q1->addr3.contents.name = resName;
                    switch (node->type)
                    {
                        case IntExpType:
                            q1->addr1.kind = IntConst;
                            q1->addr1.contents.intVal = node->attr.intValue;
                            break;
                        case RealExpType:
                            q1->addr1.kind = RealConst;
                            q1->addr1.contents.realVal = node->attr.realValue;
                            break;
                        case CharExpType:
                            q1->addr1.kind = String;
                            char name[10];
                            sprintf(name, "%c", node->attr.charValue);
                            q1->addr1.contents.name = name;
                            break;
                            
                        case StringExpType:
                            q1->addr1.kind = String;
                            q1->addr1.contents.name = node->attr.stringValue;
                            break;
                        case BoolExpType:
                            q1->addr1.kind = IntConst;
                            q1->addr1.contents.intVal = node->attr.intValue;
                            break;
                        default:
                            break;
                    }
                    
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    break;
                    break;
                }
                case OpExp: {
                    //if has only child0: tempName = result of child0; resName = op tempName
                    //if has child0, child1: tempName = result of child0; resName = tempName op child1
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->addr3.kind = String;
                    q1->addr3.contents.name = resName;
                    char* tempName1;
                    if(node->child[0]->nodeKind==ExpressionNode && node->child[0]->kind.exp ==IdExp){
                        tempName1 = node->child[0]->attr.name;
                        q1->addr1.kind = String;
                        //char name[20];
                        char* name = malloc(sizeof(char)*20);
                        sprintf(name,"temp%s", tempName1);
                        q1->addr1.contents.name = name;
                        //q1->addr1.contents.name = tempName1;
                    }
                    /*else if(node->child[0]->nodeKind==ExpressionNode && node->child[0]->kind.exp == ConstExp){
                        
                        switch (node->child[0]->type)
                        {
                            case IntExpType:
                                q1->addr1.kind = IntConst;
                                q1->addr1.contents.intVal = node->child[0]->attr.intValue;
                                break;
                            case RealExpType:
                                q1->addr1.kind = RealConst;
                                q1->addr1.contents.realVal = node->child[0]->attr.realValue;
                                break;
                            case CharExpType:
                                q1->addr1.kind = String;
                                char name[10];
                                sprintf(name, "%c", node->child[0]->attr.charValue);
                                q1->addr1.contents.name = name;
                                break;
                            case StringExpType:
                                q1->addr1.kind = String;
                                q1->addr1.contents.name = node->child[0]->attr.stringValue;
                                break;
                            case BoolExpType:
                                q1->addr1.kind = IntConst;
                                q1->addr1.contents.intVal = node->child[0]->attr.intValue;
                                break;
                            default:
                                break;
                        }
                        
                        
                        
                    }*/
                    else{
                        tempName1 = getTempName();
                        genCode(node->child[0], tempName1);
                        q1->addr1.kind = String;
                        q1->addr1.contents.name = tempName1;
                    }
                                        
                    
                    
                    switch (node->attr.op)
                    {
                        case GeOp:
                            q1->op = ge;
                            break;
                        case GtOp:
                            q1->op = gt;
                            break;
                        case LeOp:
                            q1->op = le;
                            break;
                        case LtOp:
                            q1->op = lt;
                            break;
                        case EqualOp:
                            q1->op = eq;
                            break;
                        case UnequalOp:
                            q1->op = ne;
                            break;
                        case PlusOp:
                            q1->op = plus;
                            break;
                        case MinusOp:
                            q1->op = sub;//
                            break;
                        case OrOp:
                            q1->op = ori;
                            break;
                        case MulOp:
                            q1->op = mul;
                            break;
                        case DivOp:
                            q1->op = divide;
                            break;
                        case ModOp:
                            q1->op = mod;
                            break;
                        case AndOp:
                            q1->op = andi;
                            break;
                        case NotOp:
                            q1->op = noti;
                            break;
                        default:
                            break;
                    }
                    
                    if (node->child[1] != NULL) {
                        char* tempName2;
                        if(node->child[1]->nodeKind==ExpressionNode && node->child[1]->kind.exp ==IdExp){
                            tempName2 = node->child[1]->attr.name;
                            q1->addr2.kind = String;
                            //char name[20];
                            char* name = malloc(sizeof(char)*20);
                            sprintf(name,"temp%s", tempName2);
                            q1->addr2.contents.name = name;
                            //q1->addr2.contents.name = tempName2;
                        }
                        /*else if(node->child[1]->nodeKind==ExpressionNode && node->child[1]->kind.exp == ConstExp){
                            
                            switch (node->child[1]->type)
                            {
                                case IntExpType:
                                    q1->addr2.kind = IntConst;
                                    q1->addr2.contents.intVal = node->child[1]->attr.intValue;
                                    break;
                                case RealExpType:
                                    q1->addr2.kind = RealConst;
                                    q1->addr2.contents.realVal = node->child[1]->attr.realValue;
                                    break;
                                case CharExpType:
                                    q1->addr2.kind = String;
                                    char name[10];
                                    sprintf(name, "%c", node->child[1]->attr.charValue);
                                    q1->addr2.contents.name = name;
                                    break;
                                case StringExpType:
                                    q1->addr2.kind = String;
                                    q1->addr2.contents.name = node->child[1]->attr.stringValue;
                                    break;
                                case BoolExpType:
                                    q1->addr2.kind = IntConst;
                                    q1->addr2.contents.intVal = node->child[1]->attr.intValue;
                                    break;
                                default:
                                    break;
                            }
                            
                            
                            
                        }*/
                        else{
                            tempName2 = getTempName();
                            genCode(node->child[1], tempName2);
                            q1->addr2.kind = String;
                            q1->addr2.contents.name = tempName2;
                        }
                        
                    }
                    
                    
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    break;
                    break;
                }
                case CaseExp: {
                    //在上面CaseStmt已经实现了
                    break;
                }
                default:
                    break;
            }
            //genCode(node->sibling, resName);
            break;
        }
        case DeclareNode: {
            /*
             typedef enum {
             ProgramDecl,
             ProgramheadDecl,    //不会出现在语法树中
             RoutineDecl,
             RoutineheadDecl,
             FunctionDecl,
             FunctionheadDecl,   //不会出现在语法树中
             ProcedureDecl,
             ProcedureheadDecl,  //不会出现在语法树中
             ConstDecl,
             VarDecl,
             TypeDecl,
             VarParaDecl
             } DeclKind;
             */
            //定义
            switch (node->kind.decl) {
                case ProgramDecl:{
                    //child0:routine_head child1:routine_body
                    
                    
                    genCode(node->child[0], resName);
                    
                    //fucntion main
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = funcf;
                    q1->addr3.kind = String;
                    //q1->addr3.contents.name = node->attr.name;
                    q1->addr3.contents.name = "main";
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    
                    genCode(node->child[1], resName);
                    
                    //ret0
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = ret0;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    
                    genCode(node->sibling, resName);
                    
                    
                    break;
                }
                case RoutineDecl:{
                    //const_part type_part var_part routine_part
                    genCode(node->child[0], resName);
                    //genCode(node->child[1], resName);
                    //genCode(node->child[2], resName);
                    genCode(node->child[3], resName);
                    genCode(node->sibling, resName);
                    break;
                }
                case RoutineheadDecl:{
                    //const_part type_part var_part routine_part
                    genCode(node->child[0], resName);
                    //genCode(node->child[1], resName);
                    //genCode(node->child[2], resName);
                    genCode(node->child[3], resName);
                    genCode(node->sibling, resName);
                    break;
                }
                case FunctionDecl:{
                    //0:parameters 1:simple_type_decl 2:routine_head 3:routine_body sibling:functionDecl or ProcDecl
                    
                    
                    //genCode(node->child[0], resName); //parameters
                    //genCode(node->child[1], resName); //simple_type_decl
                    genCode(node->child[2], resName);   //routine_head
                    
                    
                    //function f
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = funcf;
                    q1->addr3.kind = String;
                    q1->addr3.contents.name = node->attr.name;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    //parameters
                    SyntaxTree tmp = node->child[0];
                    while(tmp!=NULL){
                        SyntaxTree tmpchild = tmp->child[0];
                        while(tmpchild!=NULL){
                            //param xi
                            pQuad qi = (pQuad)malloc(sizeof(struct Quad));
                            qi->op = param;
                            qi->addr3.kind = String;
                            //char name[20];
                            char* name = malloc(sizeof(char)*20);
                            sprintf(name,"temp%s", tmpchild->attr.name);
                            qi->addr3.contents.name = name;
                            //strcpy(qi->addr3.contents.name, name);
                            //qi->addr3.contents.name = tmp->child[0]->attr.name;
                            qi->next = NULL;
                            QuadListEnd->next = qi;
                            QuadListEnd = QuadListEnd->next;
                            tmpchild = tmpchild->sibling;
                        }
                        
                        tmp = tmp->sibling;
                    }
                    
                    genCode(node->child[3], resName);   //routine_body
                    
                    //return tempf
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = retwithvalue;
                    q2->addr3.kind = String;
                    char* name = malloc(sizeof(char)*20);
                    sprintf(name,"temp%s", node->attr.name);
                    q2->addr3.contents.name = name;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;
                    
                    genCode(node->sibling, resName);
                    
                    break;
                }
                case ProcedureDecl:{
                    //0:parameters 1:NULL 2:routine_head 3:routine_body sibling:functionDecl or ProcDecl
                    
                    
                    //genCode(node->child[0], resName);
                    genCode(node->child[2], resName);   //routine_head
                    
                    //function procedure
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = funcf;
                    q1->addr3.kind = String;
                    q1->addr3.contents.name = node->attr.name;
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    
                    //parameters
                    SyntaxTree tmp = node->child[0];
                    while(tmp!=NULL){
                        SyntaxTree tmpchild = tmp->child[0];
                        while(tmpchild!=NULL){
                            //param xi
                            pQuad qi = (pQuad)malloc(sizeof(struct Quad));
                            qi->op = param;
                            qi->addr3.kind = String;
                            //char name[20];
                            char* name = malloc(sizeof(char)*20);
                            sprintf(name,"temp%s", tmpchild->attr.name);
                            qi->addr3.contents.name = name;
                            //strcpy(qi->addr3.contents.name, name);
                            //qi->addr3.contents.name = tmp->child[0]->attr.name;
                            qi->next = NULL;
                            QuadListEnd->next = qi;
                            QuadListEnd = QuadListEnd->next;
                            tmpchild = tmpchild->sibling;
                        }
                        
                        tmp = tmp->sibling;
                    }
                    
                    genCode(node->child[3], resName);   //routine_body
                    
                    //return 0
                    pQuad q2 = (pQuad)malloc(sizeof(struct Quad));
                    q2->op = ret0;
                    q2->next = NULL;
                    QuadListEnd->next = q2;
                    QuadListEnd = QuadListEnd->next;

                    
                    genCode(node->sibling, resName);
                    
                    break;
                }
                case ConstDecl:{
                    //ID EQUAL const_value SEMI, child0:ID, child1:const_value
                    pQuad q1 = (pQuad)malloc(sizeof(struct Quad));
                    q1->op = constassign;
                    q1->addr3.kind = String;
                    //char name[20];
                    char* name = malloc(sizeof(char)*20);
                    sprintf(name,"temp%s", node->child[0]->attr.name);
                    q1->addr3.contents.name = name;
                    //q1->addr3.contents.name = node->child[0]->attr.name;
                    switch (node->child[1]->type)
                    {
                        case IntExpType:
                            q1->addr1.kind = IntConst;
                            q1->addr1.contents.intVal = node->child[1]->attr.intValue;
                            break;
                        case RealExpType:
                            q1->addr1.kind = RealConst;
                            q1->addr1.contents.realVal = node->child[1]->attr.realValue;
                            break;
                        case CharExpType:
                            q1->addr1.kind = String;
                            char name[10];
                            sprintf(name, "%c", node->child[1]->attr.charValue);
                            q1->addr1.contents.name = name;
                            break;
                            
                        case StringExpType:
                            q1->addr1.kind = String;
                            q1->addr1.contents.name = node->child[1]->attr.stringValue;
                            break;
                        case BoolExpType:
                            q1->addr1.kind = IntConst;
                            q1->addr1.contents.intVal = node->child[1]->attr.intValue;
                            break;
                        default:
                            break;
                    }
                    q1->next = NULL;
                    QuadListEnd->next = q1;
                    QuadListEnd = QuadListEnd->next;
                    //next ConstDecl
                    genCode(node->sibling, resName);
                    break;
                }
                default:{
                    SyntaxTree childtmp;
                    int i = 0;
                    for(i=0; i<MAXCHILDREN; i++){
                        childtmp = node->child[i];
                        genCode(childtmp, resName);
                    }
                    genCode(node->sibling, resName);
                    break;
                }
            }
            
            break;
        }
        case TypeNode: {
            /*
             typedef enum {
             SimpleSysType,
             SimpleIdType,
             SimpleEnumType,
             simpleLimitType,
             ArrayType,
             RecordType  //e.g. begin
             } TypeKind;
             */
            //类型？
            /*SyntaxTree childtmp;
            int i = 0;
            for(i=0; i<MAXCHILDREN; i++){
                childtmp = node->child[i];
                genCode(childtmp, resName);
            }*/
            genCode(node->sibling, resName);
            break;
        }
        default:
            break;
    }
}




void printQuad(int index, pQuad q) {
    char str1[100];
    char str2[100];
    char str3[100];
    
    //addr1
    switch (q->addr1.kind)
    {
        case IntConst:
            sprintf(str1, "#%d", q->addr1.contents.intVal);
            break;
        case RealConst:
            sprintf(str1, "%f", q->addr1.contents.realVal);
            break;
        case String:
            sprintf(str1, "%s", q->addr1.contents.name);
            break;
        default:
            break;
    }
    
    //addr2
    switch (q->addr2.kind)
    {
        case IntConst:
            sprintf(str2, "#%d", q->addr2.contents.intVal);
            break;
        case RealConst:
            sprintf(str2, "%f", q->addr2.contents.realVal);
            break;
        case String:
            sprintf(str2, "%s", q->addr2.contents.name);
            break;
        default:
            break;
    }
    
    //addr3
    switch (q->addr3.kind)
    {
        case IntConst:
            sprintf(str3, "#%d", q->addr3.contents.intVal);
            break;
        case RealConst:
            sprintf(str3, "%f", q->addr3.contents.realVal);
            break;
        case String:
            sprintf(str3, "%s", q->addr3.contents.name);
            //strcpy(str3, q->addr3.contents.name);
            break;
        default:
            break;
    }
    
    /*typedef enum {
     assign, plus, sub, minus, mul, div, rdiv, mod,
     and, or, not,
     lt, eq, gt, le, ge, ne,
     array1, array2,
     if_goto, if_f_goto, lab, gotolab,
     param, call, calln
     wt, wtln, rd
     } QuadOpKind;*/
    //print code
    //fprintf(ircode, "%d: ", index);
    switch (q->op)
    {
        case assign:
            fprintf(ircode, "%s = %s", str3, str1);
            break;
        case constassign:
            fprintf(ircode, "CONST %s = %s", str3, str1);
            break;
        case plus:
            fprintf(ircode, "%s = %s + %s", str3, str1, str2);
            break;
        case sub:
            fprintf(ircode, "%s = %s - %s", str3, str1, str2);
            break;
        case minus:
            fprintf(ircode, "%s = minus %s", str3, str1);
            break;
        case mul:
            fprintf(ircode, "%s = %s * %s", str3, str1, str2);
            break;
        case divide:
            fprintf(ircode, "%s = %s / %s", str3, str1, str2);
            break;
        case mod:
            fprintf(ircode, "%s = %s %% %s", str3, str1, str2);
            break;
        case andi:
            fprintf(ircode, "%s = %s & %s", str3, str1, str2);
            break;
        case ori:
            fprintf(ircode, "%s = %s | %s", str3, str1, str2);
            break;
        case noti:
            fprintf(ircode, "%s = not %s", str3, str1);
            break;
        case lt:
            fprintf(ircode, "%s =  %s < %s", str3, str1, str2);
            break;
        case eq:
            fprintf(ircode, "%s = %s == %s", str3, str1, str2);
            break;
        case gt:
            fprintf(ircode, "%s = %s > %s", str3, str1, str2);
            break;
        case le:
            fprintf(ircode, "%s = %s <= %s", str3, str1, str2);
            break;
        case ge:
            fprintf(ircode, "%s = %s >= %s", str3, str1, str2);
            break;
        case ne:
            fprintf(ircode, "%s = %s != %s", str3, str1, str2);
            break;
        case array1:
            fprintf(ircode, "%s[%s] = %s", str3, str1, str2);
            break;
        case array2:
            fprintf(ircode, "%s = %s[%s]", str3, str1, str2);
            break;
        case if_goto:
            fprintf(ircode, "IF %s GOTO %s", str1, str2);
            break;
        case if_f_goto:
            fprintf(ircode, "IF_FALSE %s GOTO %s", str1, str2);
            break;
        case lab:
            fprintf(ircode, "LABEL %s", str3);
            break;
        case gotolab:
            fprintf(ircode, "GOTO %s", str3);
            break;
        case entryf:
            fprintf(ircode, "ENTRY %s", str3);
            break;
        case funcf:
            fprintf(ircode, "FUNCTION %s :", str3);
            break;
        case ret:
            fprintf(ircode, "RETURN");
            break;
        case ret0:
            fprintf(ircode, "RETURN #0");
            break;
        case retwithvalue:
            fprintf(ircode, "RETURN %s", str3);
            break;
        case beginargs:
            fprintf(ircode, "BEGIN_ARGS");
            break;
        case param:
            fprintf(ircode, "PARAM %s", str3);
            break;
        case argparam:
            fprintf(ircode, "ARG %s", str3);
            break;
        case call:
            fprintf(ircode, "CALL %s", str3);
            break;
        case valuefromcall:
            fprintf(ircode, "%s = CALL %s", str3, str1);
            break;
        case wt:
            fprintf(ircode, "BEGIN_ARGS\n");
            fprintf(ircode, "ARG %s\n", str3);
            fprintf(ircode, "CALL WRITE");
            //fprintf(ircode, "WRITE %s", str3);
            break;
        case wtln:
            fprintf(ircode, "BEGIN_ARGS\n");
            fprintf(ircode, "ARG %s\n", str3);
            fprintf(ircode, "CALL WRITELN");
            //fprintf(ircode, "WRITELN %s", str3);
            break;
        case rd:
            fprintf(ircode, "BEGIN_ARGS\n");
            fprintf(ircode, "ARG %s\n", str3);
            fprintf(ircode, "CALL READ");
            //fprintf(ircode, "READ %s", str3);
            break;
        default:
            break;
    }
    fprintf(ircode, "\n");
}



void printIRcode(){
    int index = 0;
    pQuad tmp = NULL;
    tmp = QuadListHead->next;
    
    while(tmp!=NULL){
        printQuad(index, tmp);
        tmp = tmp->next;
        index++;
    }
    return;
}
