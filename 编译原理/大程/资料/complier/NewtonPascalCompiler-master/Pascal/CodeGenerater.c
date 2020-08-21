#include "CodeGenerater.h"
#include "util.h"

#define CG_CODE(asm)		strcat(CodeBuffer,asm);
#define CG_CODEHEAD(asm)	strcat(CodeHeadBuffer,asm);

FILE* CODEFILE=NULL;
static char CodeHeadBuffer[5000];
static char CodeBuffer[100000];
static int err_cnt = 0;
static int varOffset = 0;
static int paramCnt = 0;
int GenerateCode(TreeNode* pnode);
void GExpCallCode(TreeNode *pnode);

void getOffset(TreeNode* pnode) //generate 
{
	int re = 0;
	char code[200];
	sprintf(code,"");
	st_varInfo tt=st_execute(pnode, pnode->lineno);
	int offset = tt.offset;
	int paramCnt = tt.paramCnt;
	int num1 = tt.num1;
	
	if(offset/4 <paramCnt)
		re = offset+8; 
	else
		re = 0+paramCnt*4-offset-4;

	
	if(pnode->type==EXPTYPE_ARRAY){
		GenerateCode(pnode->child[0]);
		sprintf(code,"sub eax, %d\n",num1);
		CG_CODE(code);
		CG_CODE("sal eax,2\n");
		sprintf(code,"mov edi, %d\n",re);
		CG_CODE(code);
		CG_CODE("sub edi, eax\n");
	}
	else{
		sprintf(code,"mov edi, %d\n",re);
		CG_CODE(code);
	}
	return;
}
int isFatherParameter(TreeNode* pnode){
	int tmp1 =st_execute(pnode, pnode->lineno).isfathervar;
	return (tmp1==1);
}
char* GetLabel()
{
	static int label_cnt = 0;
	char tmp2[1024];
	static char label[1024];
	strcpy(label, "__CG__label");
	sprintf(tmp2, "%d", label_cnt);
	strcat(label, tmp2);
	label_cnt++;
	return label;
}
char* GetDataLabel(){
    static int datalabel_cnt = 0;
    char tmp[100];
    static char datalabel[200];
    strcpy(datalabel,"_REALNUM");
    sprintf(tmp,"%d",datalabel_cnt);
    strcat(datalabel,tmp);
    datalabel_cnt++;
    return datalabel;
}


extern void GExpCode(TreeNode* pnode,int isrightvalue);
void GStmtIfCode( TreeNode *pnode )
{
	char if_label[100], else_label[100], exit_label[100], tmp[1024];
	strcpy(if_label, GetLabel());
	strcpy(else_label, GetLabel());
	strcpy(exit_label, GetLabel());


	GenerateCode(pnode->child[0]);
	sprintf(tmp, "cmp eax, 1\nje %s\t\t; If equal Jump to taken-content; \njmp %s\t\t; Jump to NotTake Content\n", if_label, else_label);
	CG_CODE(tmp);


	sprintf(tmp, "%s: \n", if_label);
	CG_CODE(tmp);
	GenerateCode(pnode->child[1]);
	memset(tmp, 0, 1024);
	sprintf(tmp, "jmp %s\t\t; Jump to The if exit Label\n", exit_label);
	CG_CODE(tmp);
	sprintf(tmp, "%s: \n", else_label);
    CG_CODE(tmp);
	if(pnode->child[2]!=NULL)
	{
		GenerateCode(pnode->child[2]);
	}
	sprintf(tmp, "%s: \n", exit_label);
	CG_CODE(tmp);
}

void GStmtForCode( TreeNode *pnode )
{
	char for_start[100], for_end[100],tmp[1024];
	strcpy(for_start, GetLabel());
	strcpy(for_end, GetLabel());
	if(pnode->attr.op == TOKEN_TO){
		GenerateCode(pnode->child[1]);
		CG_CODE( "mov ecx, eax \t\t;ecx = for1\n");
		
		getOffset(pnode->child[0]);
		if(isFatherParameter(pnode->child[0])){
                sprintf(tmp, "mov ss:[esi+edi], ecx\n");
        }
        else{
                sprintf(tmp, "mov ss:[ebp+edi], ecx\n");
        }
		CG_CODE(tmp);
		GenerateCode(pnode->child[2]);
		CG_CODE( "mov edx, eax \t\t;edx = for2\n");
		CG_CODE( "inc edx\n")
		//
		
		
		//
		sprintf(tmp, "%s:\n cmp ecx, edx\n je %s\t\t;for end\n", for_start,for_end);
		CG_CODE(tmp);
		CG_CODE( "push edx\t\t;save for2\n");
		CG_CODE( "push ecx\t\t;save for1\n");
		GenerateCode(pnode->child[3]);
        CG_CODE( "pop ecx\t\t;restore for1\n");
		CG_CODE( "pop edx\t\t;restore for2\n");
		CG_CODE("inc ecx\n");
		getOffset(pnode->child[0]);
		if(isFatherParameter(pnode->child[0])){
                sprintf(tmp, "mov ss:[esi+edi], ecx\n");
        }
        else{
                sprintf(tmp, "mov ss:[ebp+edi], ecx\n");
        }
		CG_CODE(tmp);
		sprintf(tmp,"jmp %s\n %s:\n",for_start,for_end);
		CG_CODE(tmp);
	}
	else{
		GenerateCode(pnode->child[1]);
		CG_CODE( "mov ecx, eax\t\t;ecx = for1\n");

		getOffset(pnode->child[0]);
		if(isFatherParameter(pnode->child[0])){
                sprintf(tmp, "mov ss:[esi+edi], ecx\n");
        }
        else{
                sprintf(tmp, "mov ss:[ebp+edi], ecx\n");
        }

		GenerateCode(pnode->child[2]);
		CG_CODE( "mov edx, eax\t\t;edx = for2\n");
		CG_CODE( "dec edx\n");

		sprintf(tmp, "%s:\n cmp ecx, edx\n je %s\t\t;for end\n", for_start,for_end);
		CG_CODE(tmp);
		GenerateCode(pnode->child[3]);
		CG_CODE("dec ecx\n");
		getOffset(pnode->child[0]);
		if(isFatherParameter(pnode->child[0])){
                sprintf(tmp, "mov ss:[esi+edi], ecx\n");
        }
        else{
                sprintf(tmp, "mov ss:[ebp+edi], ecx\n");
        }
		CG_CODE(tmp);
		sprintf(tmp,"jmp %s\n %s:\n",for_start,for_end);
		CG_CODE(tmp);
		sprintf(tmp,"%s:\n",for_end);
		CG_CODE(tmp);
	}
}
void GStmtWhileCode( TreeNode *pnode )
{

	char while_start[100], while_end[100],tmp[1024];
	strcpy(while_start, GetLabel());
	strcpy(while_end, GetLabel());
	sprintf(tmp,"%s:\t\t;while start\n",while_start);
	CG_CODE(tmp);
	GenerateCode(pnode->child[0]);
	sprintf(tmp,"cmp eax, 0\n je %s\t\t;while break\n",while_end);
	CG_CODE(tmp);
	GenerateCode(pnode->child[1]);
	sprintf(tmp,"jmp %s\n%s:\n",while_start,while_end);
	CG_CODE(tmp);
}

void GStmtRepeatCode( TreeNode *pnode )
{

	char repeat_start[100], repeat_end[100],tmp[1024];
	strcpy(repeat_start, GetLabel());
	strcpy(repeat_end, GetLabel());
	sprintf(tmp,"%s:\t\t;repeat start\n",repeat_start);
	CG_CODE(tmp);
	GenerateCode(pnode->child[0]);
	GenerateCode(pnode->child[1]);
	sprintf(tmp,"cmp eax, 0\n je %s\t\t;repeat continue\n",repeat_start);
	CG_CODE(tmp);
	sprintf(tmp,"%s:\n",repeat_end);
	CG_CODE(tmp);
}

void GCaseExpCode(TreeNode* pnode){
	char tmp[200];
	char* case_end= GetLabel();

	GExpCode(pnode->child[0],0);
	CG_CODE("cmp eax, edx\n");
	sprintf(tmp,"jne %s\n",case_end);
	CG_CODE(tmp);
	GenerateCode(pnode->child[1]);
	CG_CODE("jmp CASE_OVER\n");
	
	sprintf(tmp,"%s:\n",case_end);
	CG_CODE(tmp);
	if(pnode->sibling!=NULL){
		GCaseExpCode(pnode->sibling);
	}
}
void GStmtCaseCode(TreeNode* pnode){
	GExpCode(pnode->child[0],0);
	CG_CODE("mov edx, eax\n");
	GCaseExpCode(pnode->child[1]);
	CG_CODE("CASE_OVER:\n");

}
void GStmtInputCode(TreeNode *pnode)
{
	char tmp[400];
	st_execute(pnode->child[0],pnode->lineno); //look up the type of parameter
	if(pnode->child[0]->type == EXPTYPE_INT){
        CG_CODE("call input\n");
        getOffset(pnode->child[0]);
        if(isFatherParameter(pnode->child[0])){
            sprintf(tmp, "mov ss:[esi+edi], eax\n");
        }
        else{
            sprintf(tmp, "mov ss:[ebp+edi], eax\n");

        }
        CG_CODE(tmp);
    }
    else if(pnode->child[0]->type==EXPTYPE_REAL){
        CG_CODE("call input_real\n");
        getOffset(pnode->child[0]);
        if(isFatherParameter(pnode->child[0])){
            sprintf(tmp, "fstp dword ptr [esp+edi]\n");
        }
        else{
            sprintf(tmp, "fstp dword ptr [ebp+edi]\n");
        }
        CG_CODE(tmp);
    }
}
void GStmtOutputCode(TreeNode *pnode)
{
	GExpCode(pnode->child[1],0);
	if (pnode->child[1]->type==EXPTYPE_REAL){
        CG_CODE("call output_real\n");
	}
	else{
	    CG_CODE("push eax\n");
        CG_CODE("call output\n");
        CG_CODE("pop  eax\n");
    }

}
void GStmtCode( TreeNode *pnode )
{
	/* TODO */
	char tmp[200];
	switch(pnode->kind.stmt)
	{
	case STMT_IF:
		GStmtIfCode(pnode);
		break;
	case STMT_WHILE:
		GStmtWhileCode(pnode);
		break;
	case STMT_REPEAT:
		GStmtRepeatCode(pnode);
		break;
	case STMT_FOR:
		GStmtForCode(pnode);
		break;
	case STMT_CASE:
		GStmtCaseCode(pnode);
		break;
	case STMT_LABEL:
		sprintf(tmp,"goto_%d:\n",pnode->attr.val);
		CG_CODE(tmp);
		GenerateCode(pnode->child[0]);
		break;
	case STMT_GOTO:
		sprintf(tmp,"jmp goto_%d\n",pnode->attr.val);
		CG_CODE(tmp);
		break;
	case STMT_PROC_SYS:
	{
			switch(pnode->attr.op)
			{
			case TOKEN_READ:
               
				GStmtInputCode(pnode);
				break;
			case TOKEN_WRITELN:
			case TOKEN_WRITE:
				GStmtOutputCode(pnode);
				break;
			default: break;
			}
			break;
	}
	default:
		break;
	}
	CG_CODE("\n");
	return;
}


int pushParam(TreeNode* pnode)
{
	int cnt = 1;
	if(pnode->sibling!=NULL)
		cnt += pushParam(pnode->sibling);
	CG_CODE(";function parameter start\n");
    GExpCode(pnode,0);
	CG_CODE("push eax\t\t; push the parameter\n");
	CG_CODE(";function parameter end\n");
	return cnt;
}


/**
 * Generate Code for Calling a Function
 * Pass the parameters by stack.
 * Push from right to left.
 **/
void GExpCallCode(TreeNode *pnode)
{
	char tmp[1024];
	int cnt  = 0, i;
	if(pnode->child[1]!=NULL)
	{
		TreeNode* tmp = pnode->child[1];
		{
			/* use post order*/
			cnt = pushParam(tmp);
		}
	}
	memset(tmp, 0, 1024);
	sprintf(tmp, "call %s\n", pnode->attr.name);
	CG_CODE(tmp);
	for(i=0; i<cnt; i++) CG_CODE("pop ebx\t\t;pop parameter in order to banlance the stack\n");
	return;
}


/**
 * Generate Code for a const number use in code.
 * We simple move it to eax register.
 **/
void GExpConstCode(TreeNode* pnode)
{
	char tmp[1024];
	char tmp2[1024];
	if(pnode->type==EXPTYPE_REAL){
        strcpy(tmp2,GetDataLabel());
        sprintf(tmp,"%s         dd %lf\n",tmp2,pnode->attr.real_val);
        CG_CODEHEAD(tmp);
        sprintf(tmp,"fld dword ptr[%s]\n",tmp2);
        CG_CODE(tmp);
	}
	else {
        if (pnode->attr.val != 0)
            sprintf(tmp, "mov eax, %d\n", pnode->attr.val);
        else
            sprintf(tmp, "xor eax, eax\n");
        CG_CODE(tmp);
        return;
    }
}
void GExpOpCode_real(TreeNode* pnode){
	char code[1024], tmp[1024];
	strcpy(code, "");
	
	if(pnode->child[0]!=NULL&&pnode->attr.op==TOKEN_ASSIGN){
        st_execute(pnode->child[0],pnode->lineno); //look up the ID type
    }
    else{
        GExpCode(pnode->child[0],0);
    }

	if(pnode->child[1]!=NULL)
		GExpCode(pnode->child[1],1);



        pnode->type = pnode->child[1]->type;
        //printf("in real, %d   %d\n",pnode->type,pnode->child[1]->type);
		switch(pnode->attr.op)
		{
		case TOKEN_PLUS:
			strcat(code, "fadd\n");
			break;
		case TOKEN_MINUS:
			strcat(code, "fsub\n");
			break;
		case TOKEN_MUL:
			strcat(code, "fmul\n");
			break;
		case TOKEN_DIV:
			strcat(code, "fdiv\n");
			break;
		case TOKEN_LT:
			strcat(code, "fcom\n");
			break;
		case TOKEN_LE:
			strcat(code, "fcom\n");
			break;
		case TOKEN_GT:
			strcat(code, "fcom\n");
			break;
		case TOKEN_GE:
			strcat(code, "fcom\n");
			break;
		case TOKEN_EQUAL:
			strcat(code, "fcom\n");
			break;
		case TOKEN_UNEQUAL:
			//
			break;
		case TOKEN_ASSIGN:
			getOffset(pnode->child[0]);
            if(isFatherParameter(pnode->child[0])){
                sprintf(tmp, "fstp dword ptr [esi+edi]\n");
            }
            else{
                sprintf(tmp, "fstp dword ptr [ebp+edi]\n");
            }
			strcat(code, tmp);
			break;
		default:
			break;
		}
	//}
	CG_CODE(code);
	return;

}
void GExpOpCode(TreeNode* pnode)

{
	char code[1024], tmp[1024];
	if(pnode->child[0]!=NULL&&pnode->child[0]->kind.exp==EXP_CONST&&pnode->child[1]!=NULL&&pnode->child[1]->kind.exp==EXP_CONST&&pnode->attr.op!=TOKEN_ASSIGN){
		int nn; 
	
		switch(pnode->attr.op){
			case TOKEN_PLUS:
				nn = pnode->child[0]->attr.val+pnode->child[1]->attr.val;
				break;
			case TOKEN_MINUS:
				nn = pnode->child[0]->attr.val-pnode->child[1]->attr.val;
				break;
			case TOKEN_MUL:
				nn = pnode->child[0]->attr.val*pnode->child[1]->attr.val;
				break;
			case TOKEN_DIV:
				nn = pnode->child[0]->attr.val/pnode->child[1]->attr.val;
				break;
			case TOKEN_LT:
				nn = pnode->child[0]->attr.val<pnode->child[1]->attr.val;
				break;
			case TOKEN_LE:
				nn = pnode->child[0]->attr.val<=pnode->child[1]->attr.val;
				break;
			case TOKEN_GT:
				nn = pnode->child[0]->attr.val>pnode->child[1]->attr.val;
				break;
			case TOKEN_GE:
				nn = pnode->child[0]->attr.val>=pnode->child[1]->attr.val;
				break;
			case TOKEN_EQUAL:
				nn = (pnode->child[0]->attr.val == pnode->child[1]->attr.val);
				break;
			case TOKEN_UNEQUAL:
				nn = (pnode->child[0]->attr.val!=pnode->child[1]->attr.val);
				break;
			default:
				break;
		}
		pnode->kind.exp = EXP_CONST;
		pnode->attr.val = nn;
		pnode->type = pnode->child[1]->type;
        if (nn != 0)
            sprintf(tmp,"mov eax, %d\n",nn);
        else
            sprintf(tmp, "xor eax, eax\n");
		CG_CODE(tmp);
		return;
	}
	
	if(pnode->child[0]!=NULL)
		GExpCode(pnode->child[0],0);
	CG_CODE("push eax\n");
	if(pnode->child[1]!=NULL)
		GExpCode(pnode->child[1],1);
	CG_CODE("mov ebx, eax\n");
	CG_CODE("pop eax\n");
	strcpy(code, "");

		switch(pnode->attr.op)
		{
		case TOKEN_PLUS:
			strcat(code, "add eax, ebx\n");
			break;
		case TOKEN_MINUS:
			strcat(code, "sub eax, ebx\n");
			break;
		case TOKEN_MUL:
                if (pnode->child[1]->kind.exp == EXP_CONST) {
                    int val = pnode->child[1]->attr.val;
                    //pow 2
                    if ((val & (val - 1)) == 0) {
                        int count = 0;
                        while (val >> count != 0)
                            ++count;
                        --count;
                        char shift[30];
                        sprintf(shift, "shl eax, %d\n", count);
                        strcat(code, shift);
                    }
                    else
                        strcat(code, "xor edx, edx\nmul ebx\n");
                }
                else
                    strcat(code, "xor edx, edx\nmul ebx\n");
			break;
		case TOKEN_DIV:
                if (pnode->child[1]->kind.exp == EXP_CONST) {
                    int val = pnode->child[1]->attr.val;
                    //pow 2
                    if ((val & (val - 1)) == 0) {
                        int count = 0;
                        while (val >> count != 0)
                            ++count;
                        --count;
                        char shift[30];
                        sprintf(shift, "shl eax, %d\n", count);
                        strcat(code, shift);
                    }
                    else
                        strcat(code, "xor edx, edx\ndiv ebx\n");
                }
                else
                    strcat(code, "xor edx, edx\ndiv ebx\n");
			break;
		case TOKEN_MOD:
                if (pnode->child[1]->kind.exp == EXP_CONST) {
                    int val = pnode->child[1]->attr.val;
                    //pow 2
                    if ((val & (val - 1)) == 0) {
                        int count = 0;
                        while (val >> count != 0)
                            ++count;
                        --count;
                        
                        int i, offset = 0;
                        for (i = 0; i < count; i++) {
                            offset = (offset << 1) | 0x01;
                        }
                        char shift[30];
                        sprintf(shift, "and eax, %d\n", offset);
                        strcat(code, shift);
                    }
                    else
                        strcat(code, "xor edx, edx\ndiv ebx\nmov eax, edx\n");
                }
                else
                    strcat(code, "xor edx, edx\ndiv ebx\nmov eax, edx\n");
			break;
		case TOKEN_AND:
			strcat(code, "and eax, ebx\n");
			break;
		case TOKEN_OR:
			strcat(code, "or eax, ebx\n");
			break;
		case TOKEN_NOT:
			strcat(code, "not eax\n");
			break;
		case TOKEN_LT:
			strcat(code, "cmp eax, ebx\n");
			strcat(code, "xor eax, eax\n");
			strcat(code, "setl al\n");
			break;
		case TOKEN_LE:
			strcat(code, "cmp eax, ebx\n");
			strcat(code, "xor eax, eax\n");
			strcat(code, "setng al\n");
			break;
		case TOKEN_GT:
			strcat(code, "cmp eax, ebx\n");
			strcat(code, "xor eax, eax\n");
			strcat(code, "setg al\n");
			break;
		case TOKEN_GE:
			strcat(code, "cmp eax, ebx\n");
			strcat(code, "xor eax, eax\n");
			strcat(code, "setnl eax\n");
			break;
		case TOKEN_EQUAL:
			strcat(code, "cmp eax, ebx\n");
			strcat(code, "xor eax, eax\n");
			strcat(code, "sete al\n");
			break;
		case TOKEN_UNEQUAL:
			strcat(code, "cmp eax, ebx\n");
			strcat(code, "xor eax, eax\n");
			strcat(code, "setne al\n");
			break;
		case TOKEN_ASSIGN:
			strcat(code, "mov eax, ebx\n");
			getOffset(pnode->child[0]);//st_execute(pnode->child[0], pnode->child[0]->lineno).offset);
            if(isFatherParameter(pnode->child[0])){
                sprintf(tmp, "mov ss:[esi+edi], eax\n");
            }
            else{
                sprintf(tmp, "mov ss:[ebp+edi], eax\n");
            }
			strcat(code, tmp);
			break;
		default:
			break;
		}

	CG_CODE(code);
	return;
}

void GExpCode(TreeNode *pnode, int isrightvalue)
{
	char tmp[1024];
	ConstValueItem item;

	switch (pnode->kind.exp)
	{
	case EXP_FUNC:
        CG_CODE(";call function\n");
		GExpCallCode(pnode);
		break;
	case EXP_OP:
        if(st_execute(pnode->child[1],pnode->lineno).type==EXPTYPE_REAL||
		   st_execute(pnode->child[0],pnode->lineno).type==EXPTYPE_REAL||
		   st_execute(pnode->child[1],pnode->lineno).childtype==EXPTYPE_REAL||
		   st_execute(pnode->child[0],pnode->lineno).childtype==EXPTYPE_REAL||
			pnode->child[1]->type==EXPTYPE_REAL||
			pnode->child[0]->type==EXPTYPE_REAL){
				GExpOpCode_real(pnode);
        }
        else{
            GExpOpCode(pnode);
        }
		break;
	case EXP_CONST:
		GExpConstCode(pnode);
		break;
	case EXP_ID:	
		//if the ID is a const
		item = CT_lookup(pnode->attr.name);
		if(item!=NULL){
            if (item->val.int_val != 0)
                sprintf(tmp, ";the ID is const\n mov eax, %d\n",item->val.int_val);
            else
                sprintf(tmp, ";the ID is const\n xor eax, eax\n");
            CG_CODE(tmp);
            pnode->type = item->type;
		}
		else if(item!=NULL&&isrightvalue){
            printf("error %d(%d): %s is a const value and cannot to be assigned.\n", ++err_cnt, pnode->lineno,pnode->attr.name);
		}
		//if the ID is a function ,first execute this function
        else if((st_execute(pnode, pnode->lineno).type==EXPTYPE_FUNC)&&(pnode->child[1]==NULL)&&(isrightvalue==1)){  //是函数变量
            sprintf(tmp, ";the ID is function\ncall %s\n", pnode->attr.name);
            CG_CODE(tmp);
            pnode->type = EXPTYPE_FUNC;
        }
        else if((pnode->type==EXPTYPE_REAL)||(pnode->type ==EXPTYPE_ARRAY&&st_execute(pnode,pnode->lineno).childtype==EXPTYPE_REAL)){
                getOffset(pnode);
                if(isFatherParameter(pnode)){
                    sprintf(tmp,"fld dword ptr [esi+edi]\n");
                }
                else{
                    sprintf(tmp,"fld dword ptr [ebp+edi]\n");
                }
                CG_CODE(tmp);
        }
        else{
			getOffset(pnode);
            if(isFatherParameter(pnode)){
                sprintf(tmp, "mov eax, ss:[esi+edi] \n");
            }
            else{
                sprintf(tmp, "mov eax, ss:[ebp+edi] \n");//st_execute(pnode, pnode->lineno).offset);
            }
            CG_CODE(tmp);
            pnode->type = st_execute(pnode, pnode->lineno).type;
        }
		break;
        default:
            break;
    }
	return;
}

void GDeclFuncCode(TreeNode* pnode)
{
	char tmp[1024];
	GenerateCode(pnode->child[0]); //calculate the type of function
	GenerateCode(pnode->child[1]); //push the parameter of function

	pnode->child[2]->attr.name=copyString(pnode->attr.name);
	GenerateCode(pnode->child[2]); // generate the code of function body
	sprintf(tmp, "add esp, %d\n", (varOffset));
	CG_CODE(tmp);
	varOffset = 0;
	CG_CODE("pop ebp\n");
	CG_CODE("ret\n");
	st_leave(pnode->child[3]);
	paramCnt = 0;
	#ifdef CG_DEBUG
	#endif
}

void GParamCode(TreeNode* pnode)
{
	paramCnt++;
	return;
}


void GDeclCode(TreeNode* pnode)
{
	int i;
	char tmp[200];
    int namenum =0;//the name number of var  x,y,z:=integer(namenum=3)
    int namesize = 0;//the size of var  x,y,z:=integer(namesize=4)
    TreeNode* tmptree;
	switch(pnode->kind.decl)
	{
		case DECL_ROUTINEHEAD:
			for(i=0;i<2;i++){ //insert the const and type 
				if(pnode->child[i]!=NULL){
					GenerateCode(pnode->child[i]);
                }
			}
			if(pnode->child[2]!=NULL){
               st_insertdecl_var_list(pnode->child[2]);//only insert the var into symtable
            }
			if(pnode->child[3]!=NULL){
                GenerateCode(pnode->child[3]); //generate the function(procedure) code

			}
			if(pnode->attr.name!=NULL){
                sprintf(tmp,"%s:\n",pnode->attr.name);
                CG_CODE(tmp);
                CG_CODE("push ebp\nmov ebp, esp\nmov esi, ss:[ebp+0]\n");
            }
			
			if(pnode->child[2]!=NULL){
                GDeclCode(pnode->child[2]); // use this function can void insert the var two times
            }

			break;
		case DECL_FUNCTION:
			return GDeclFuncCode(pnode);
			break;
		case DECL_PROCEDURE:
			return GDeclFuncCode(pnode);
			break;

		case DECL_CONST:
			//only do something in SymTable
			break;
		case DECL_TYPE:
			//only do something in SymTable
			break;
		case DECL_VAR:
            while(pnode!=NULL){
                namenum = 0;
                namesize = 0;
                tmptree = pnode->child[0];
                while(tmptree!=NULL){
                    namenum ++;
                    tmptree = tmptree->sibling;
                }
                tmptree = pnode->child[1];
                if(tmptree->type==EXPTYPE_ARRAY){

                    namesize = (tmptree->child[0]->child[1]->attr.val - tmptree->child[0]->child[0]->attr.val+1)*4;
                }
                else if(tmptree->type==EXPTYPE_REAL){
                    namesize = 4;
                }
                else {
                    namesize = 4;

                }
                sprintf(tmp,"sub esp, %d\t\t;Allocate Varable space\n",namenum*namesize);
                varOffset = varOffset + namenum*namesize;
                CG_CODE(tmp);
                pnode = pnode->sibling;
            }
            break;
		case DECL_VAL_PARA:
		case DECL_VAR_PARA:
			GParamCode(pnode);
			break;
		default:
			break;
	}
return;
}




char* InitialGenerater(char* o_name)
{
	CODEFILE = fopen(o_name, "w");
	return NULL;
}


int GenerateCode(TreeNode* pnode)
/**
 * Generate Assemble Code
 * Use Post Order Recursive to Generate Code
 * Use Prior Oder Recursive to Generate
**/
{
	if(pnode==NULL)
	{
		return err_cnt;
	}
	st_execute(pnode, pnode->lineno);
	switch (pnode->nodekind)
	{
		case NODE_STATEMENT:
			GStmtCode(pnode);
			break;
		case NODE_EXPRESSION:
			GExpCode(pnode,0);
			break;
		case NODE_DECLARE:
			GDeclCode(pnode);
			break;
		default:
			break;
	}
	CG_CODE("\n");
	if(pnode->sibling!=NULL){
		pnode->sibling->type = pnode->type;
		GenerateCode(pnode->sibling);
	}
	return err_cnt;
}
void GenerateCodeHead(char* pname)
{
	CG_CODEHEAD(".386\n");
	CG_CODEHEAD(".model flat,stdcall\n");
	CG_CODEHEAD("option casemap:none\n");
	CG_CODEHEAD("\n");
	CG_CODEHEAD("include    masm32\\include\\windows.inc\n");
	CG_CODEHEAD("include    masm32\\include\\kernel32.inc\n");
	CG_CODEHEAD("include    masm32\\include\\msvcrt.inc\n");
	CG_CODEHEAD("includelib masm32\\lib\\msvcrt.lib\n");
	CG_CODEHEAD("includelib masm32\\lib\\kernel32.lib\n");
	CG_CODEHEAD("include    masm32\\include\\user32.inc\n");
	CG_CODEHEAD("includelib masm32\\lib\\user32.lib\n");
	CG_CODEHEAD("includelib masm32\\lib\\kernel32.lib\n");
	CG_CODEHEAD("includelib masm32\\lib\\msvcrt.lib\n");
	CG_CODEHEAD("printf PROTO C :ptr sbyte, :vararg\n");
	CG_CODEHEAD("	.data\n");
	CG_CODEHEAD("szInput         db  '%d',  0\n");
	CG_CODEHEAD("szInput_real    db  '%f', 0\n");
	CG_CODEHEAD("szFormat        db  '%d',  0ah, 0dh , 0\n");
	CG_CODEHEAD("szFormat_real   db  '%lf', 0ah, 0dh , 0\n");
	CG_CODEHEAD("tmp			 db 0, 0, 0, 0, 0, 0, 0, 0\n");


	CG_CODE("    .const\n");
	CG_CODE("    .code \n");
	CG_CODE("start:  \n");
	CG_CODE("mov esi, ebp\n");
	CG_CODE("push ebp\n");
	CG_CODE("mov ebp, esp\n");
	CG_CODE("call ");
	CG_CODE(pname);
	CG_CODE("\npop ebp\n");
	CG_CODE("invoke    ExitProcess,NULL\n");
	CG_CODE("\n");
	CG_CODE("output:\n");
	CG_CODE("	push    ebp\n");
	CG_CODE("	mov     ebp, esp\n");
	CG_CODE("	push    eax\n");
	CG_CODE("	mov     ebx, offset szFormat\n");
	CG_CODE("	push    ebx\n");
	CG_CODE("	call    printf\n");
	CG_CODE("	pop		ebx\n");
	CG_CODE("	pop		ebx\n");
	CG_CODE("   pop     ebp\n");
	CG_CODE("   ret\n");
	CG_CODE("output_real:\n");
	CG_CODE("   sub esp, 8\n");
	CG_CODE("   fstp qword ptr [esp]\n");
	CG_CODE("   push offset szFormat_real\n");
	CG_CODE("   call printf\n");
	CG_CODE("   pop eax\n");
	CG_CODE("   add esp, 8\n");
	CG_CODE("   ret\n");
	CG_CODE("input:\n");
	CG_CODE("   invoke crt_scanf, addr szInput, addr tmp\n");
	CG_CODE("   mov eax, dword ptr tmp\n");
	CG_CODE("   ret\n");
	CG_CODE("input_real:\n");
	CG_CODE("   invoke crt_scanf, addr szInput_real, addr tmp\n");
	CG_CODE("   fld dword ptr tmp\n");
	CG_CODE("   ret\n");

}


void GenerateCodeTail()
{
	char tmp[200];
	sprintf(tmp, "add esp, %d\n", varOffset);
	CG_CODE(tmp);
	CG_CODE("pop ebp\n");
	CG_CODE("ret\n");
	CG_CODE("end    start\n");
}



int BuildCode(TreeNode* pnode)
{
	sprintf(CodeHeadBuffer,"");
	sprintf(CodeBuffer,"");

	GenerateCodeHead(pnode->attr.name);
	GenerateCode(pnode);
	GenerateCodeTail();
	
	fprintf(CODEFILE,"%s",CodeHeadBuffer);
	fprintf(CODEFILE,"%s",CodeBuffer);
	fclose(CODEFILE);

	return 0;
}
