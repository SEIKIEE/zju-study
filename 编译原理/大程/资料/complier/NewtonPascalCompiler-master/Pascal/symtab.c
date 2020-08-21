#include "symtab.h"

static int indent = 0;
static int ConstValueNum = 0;
static int TypeItemNum = 0;
#define INDENT indent+=2
#define UNINDENT indent-=2
static int initial = 0;

HashList topHashTable[HASHSIZE];

HashList currentSymTab;

ConstValueItem ConstValueTable[ConstValueSize];
TypeItem TypeTable[TypeTableSize];

static int hash(char * key)
{
	int temp = 0;
	int i = 0;
	while (key[i]!='\0')
	{
		temp = ((temp << SHIFT) + key[i]) % HASHSIZE;
		i++;
	}
	return temp;
}


static void printBucketList(BucketList l)
{
	int i;
	BucketList bl = l;
	while(bl!=NULL)
	{
		for(i=0; i<indent; i++)
			fprintf(listing, " ");
		fprintf(listing, "%-14s  %-8d  ", bl->name, bl->memloc);
		fprintf(listing, "\n");
		bl = bl->next;
	}
}

static void printHashList(HashList hl)
{
	int i;
	while(hl!=NULL)
	{

		fprintf(listing, "Function Name:%-14s\n", hl->declName);
		for(i=0; i<HASHSIZE; i++)
		{
			printBucketList(hl->bucketList[i]);
		}
		INDENT;
		printHashList(hl->child);
		UNINDENT;
		hl = hl->next;
	}
}


static void st_create(HashList parent, char * name, int memBase)
{
	HashList hl = (HashList) malloc (sizeof(struct HashListRec));
	hl->parent = parent;

	if(parent!=NULL && (strcmp(parent->declName,GLOBAL_HASHLIST_NAME)!=0))
	/*when it has a parent and the parent is not the virtual global hashlist, set its child to the newly create hashlist*/
	{

		parent->child = hl;
	}
	hl->declName = name;
	hl->child = NULL;
	hl->paranum = 0;
	hl->memBase = memBase;
	memset(hl->bucketList, 0, HASHSIZE);
	hl->next = NULL;
	hl->offset = 0;
	currentSymTab = hl;
}

static void st_attatch()
{

	char * name = currentSymTab->declName;
	int key = hash(name);
	HashList hl = topHashTable[key];
	if( hl!=NULL && strcmp(hl->declName, name)!=0)
		hl=hl->next;
	if(hl==NULL)
	{
		currentSymTab->next = topHashTable[key];
		topHashTable[key] = currentSymTab;
	}
}

st_varInfo st_local_lookup(HashList hl, char * name)
{
	st_varInfo ml;
	int h = hash(name);
	if(hl==NULL)
	{
		ml.offset = -1;
		ml.type = EXPTYPE_UNKNOW;
	}
	else
	{
		BucketList bl = hl->bucketList[h];
		while(bl!=NULL)
		{
			if(strcmp(bl->name, name)==0)
				break;
			else
				bl = bl->next;
		}
		if(bl==NULL)/*can't find at this level*/
		{
			ml.offset = -1;
			ml.type = EXPTYPE_UNKNOW;
		}
		else/*find at this level*/
		{
			ml.offset = bl->memloc;
			ml.type = bl->type;
			ml.childtype=bl->childtype;
			ml.paramCnt= hl->paranum;
            ml.num1 = bl->num1;
            ml.num2 = bl->num2;
		}
	}
    ml.isfathervar=0;
	return ml;
}

st_varInfo st_lookup(HashList hl, char * name)
{
	st_varInfo ml = st_local_lookup(hl, name);
	if(ml.offset==-1)
	{
		if(hl->parent!=NULL)
			ml = st_lookup(hl->parent, name);
			ml.isfathervar = 1;
	}
	return ml;
}

void st_insert(TreeNode * node, int lineno, int ispara,int isfuncname)
{
    st_varInfo ml;
	if(ispara==1){
        currentSymTab->paranum++;
    }
	int memloc = currentSymTab->memBase + currentSymTab->offset;
	
	int h = hash(node->attr.name);
	BucketList bl = currentSymTab->bucketList[h];
	while((bl!=NULL) && strcmp(bl->name, node->attr.name))
		bl = bl->next;
	if(bl==NULL)/*means this char is not in the table*/
	{
		bl = (BucketList) malloc(sizeof(struct BucketListRec));
		bl->name = node->attr.name;
		if(isfuncname==1){
                bl->type = EXPTYPE_FUNC;
        }
        else if(node->type == EXPTYPE_ARRAY){
            bl->type = node->type;
            bl->childtype = node->child[1]->type;
            bl->num1 = node->child[0]->child[0]->attr.val;
            bl->num2 = node->child[0]->child[1]->attr.val;
        }
        else if(node->type == EXPTYPE_LIMIT){
            bl->type = node->type;
            bl->num1 = node->child[0]->attr.val;
            bl->num2 = node->child[1]->attr.val;
        }
        else{
            bl->type = node->type;
        }
		bl->memloc = memloc;
		bl->next = currentSymTab->bucketList[h];
		currentSymTab->bucketList[h] = bl;/*circular*/
	}
	ml.offset = memloc;
	switch(node->type)
	{
        case EXPTYPE_CHAR:
		case EXPTYPE_INT:
		case EXPTYPE_REAL:
		case EXPTYPE_BOOL:
		case EXPTYPE_POINTER:	currentSymTab->offset += 4;
				break;
		case EXPTYPE_ARRAY:	currentSymTab->offset += (bl->num2 - bl->num1+1)*4;
				break;
		case EXPTYPE_VOID:
		default:	break;
	}

	return;
}

void st_leave(TreeNode * node)
{
	if(currentSymTab->parent!=NULL)
	{

		printHashList(currentSymTab);
		currentSymTab = currentSymTab->parent;

	}
}

void st_insertdecl_var_list(TreeNode* node)
{
        node ->child[0]->type = node->child[1]->type;
        TreeNode* tmp;
    
        if(node->child[1]->type==EXPTYPE_INT||node->child[1]->type==EXPTYPE_REAL){
            tmp = node->child[0];
            while(tmp!=NULL){
                if(st_local_lookup(currentSymTab, tmp->attr.name).offset!=-1)
                    fprintf(listing, "Redefine identifier %s in line %d\n", tmp->attr.name, tmp->lineno);
                st_insert(tmp, lineno,0,0);
                if(tmp->sibling!=NULL){
                    tmp->sibling->type = tmp->type;
                }
                tmp = tmp->sibling;
            }
        }
        else if(node->child[1]->type==EXPTYPE_ARRAY) { //如果是数组，用类型节点插入
            tmp = node->child[0];
            while(tmp!=NULL){
                if(st_local_lookup(currentSymTab, tmp->attr.name).offset!=-1)
                    fprintf(listing, "Redefine identifier %s in line %d\n", tmp->attr.name, tmp->lineno);
                node->child[1]->attr.name = tmp->attr.name;
                st_insert(node->child[1], lineno,0,0);
                tmp = tmp->sibling;
            }

        }
		else if(node->child[1]->nodekind==NODE_TYPE&&node->child[1]->kind.type ==TYPE_SIMPLE_ID){
			TypeItem tt = TT_lookup(node->child[1]->attr.name);
			tmp = node->child[0];
			while(tmp!=NULL){
                if(st_local_lookup(currentSymTab, tmp->attr.name).offset!=-1)
                    fprintf(listing, "Redefine identifier %s in line %d\n", tmp->attr.name, tmp->lineno);
                tt->node->attr.name = tmp->attr.name;
                st_insert(tt->node, lineno,0,0);
                tmp = tmp->sibling;
            }
		}
        if(node->sibling!=NULL){
            st_insertdecl_var_list(node->sibling);
        }
        return;
}

st_varInfo st_execute(TreeNode * node, int lineno)
{

	st_varInfo ml;
	switch(node->nodekind)
	{
		case NODE_EXPRESSION: {
			switch(node->kind.exp)
			{
				case EXP_FUNC:	/*return the call function addr*/
						ml = st_lookup(currentSymTab, node->attr.name);
						if(ml.offset==-1)
							fprintf(listing, "Undefine identifier %s in line %d\n", node->attr.name, lineno);
						return ml;
						break;
				case EXP_ID:
                        ml = st_lookup(currentSymTab, node->attr.name);
                        node->type = ml.type;
                        if(ml.offset==-1)
                            fprintf(listing, "Undefine identifier %s in line %d\n", node->attr.name, lineno);

                        if(node->type == EXPTYPE_ARRAY){
                            if(node->child[0]->attr.val > ml.num2||node->child[0]->attr.val < ml.num1){
                                fprintf(listing, "The index of array %s over in line %d!\n", node->attr.name, lineno);
                            }
    
                        }
                        return ml;
                        break;
				default:
					break;
			}
		}break;
		case NODE_DECLARE:
		{
			switch(node->kind.decl)
			{
				case DECL_ROUTINEHEAD: //only create the st when the first time
                    if(initial==0){
                        st_create(currentSymTab,node->attr.name,0);
                        st_attatch();
                        initial = 1;
                    }
					break;
				case DECL_FUNCTION:
				 
					node->type = node->child[0]->type;
					if(st_local_lookup(currentSymTab, node->attr.name).offset!=-1)
							fprintf(listing, "Redefine identifier %s in line %d\n", node->attr.name, lineno);
					st_insert(node, lineno,0,1);

					st_create(currentSymTab, node->attr.name, 0);
					st_attatch();
					break;
				case DECL_PROCEDURE:
					node->type = EXPTYPE_VOID;
					if(st_local_lookup(currentSymTab, node->attr.name).offset!=-1)
							fprintf(listing, "Redefine identifier %s in line %d\n", node->attr.name, lineno);
					st_insert(node, lineno,0,1);
					st_create(currentSymTab, node->attr.name, 0);
					st_attatch();
					break;
				case DECL_CONST:
                    while(node!=NULL){
                            ConstValueItem tmp =(ConstValueItem)malloc(sizeof(ConstValueItem));
                            tmp->name = node->attr.name;
                            tmp->type = node->type;
                            if(tmp->type==EXPTYPE_INT||tmp->type==EXPTYPE_BOOL){
                                tmp->val.int_val = node->child[0]->attr.val;
                            }
                            else if(tmp->type==EXPTYPE_REAL){
                                tmp->val.real_val = node->child[0]->attr.real_val;
                            }
                            else if(tmp->type==EXPTYPE_CHAR){
                                tmp->val.char_val = node->child[0]->attr.char_val;
                            }
                            printf("IN DECL_CONST %d\n",node->child[0]->attr.val);
                            CT_insert(tmp);
                            node = node->sibling;
                    }
					break;
				case DECL_TYPE:
					while(node!=NULL){
                            TypeItem tmp =(TypeItem)malloc(sizeof(TypeItem));
							tmp ->name = node->child[0]->attr.name;
							tmp->node = node->child[1];
							TT_insert(tmp);
                            node = node->sibling;
                    }
					break;
				case DECL_VAL_PARA:		//所有变量用相同的方法处理
				case DECL_VAR_PARA:
                    st_execute(node->child[1],node->child[1]->lineno);//计算pnode的类型
					node ->child[0]->type = node->child[1]->type;
					//把多个变量插入符号表
					node = node->child[0];
					while(1){
						if(st_local_lookup(currentSymTab, node->attr.name).offset!=-1)
							fprintf(listing, "Redefine identifier %s in line %d\n", node->attr.name, node->lineno);
						st_insert(node, lineno,1,0);
						if(node->sibling!=NULL){
							node->sibling->type = node->type;
							node = node->sibling;
						}
						else{break;}
					}
					break;

				case DECL_VAR:
					st_execute(node->child[1],node->child[1]->lineno);//计算pnode的类型
					node ->child[0]->type = node->child[1]->type;
					
					node = node->child[0];
					while(1){
						if(st_local_lookup(currentSymTab, node->attr.name).offset!=-1)
							fprintf(listing, "Redefine identifier %s in line %d\n", node->attr.name, node->lineno);
						st_insert(node, lineno,0,0);
						if(node->sibling!=NULL){
							node->sibling->type = node->type;
							node = node->sibling;
						}
						else{break;}
					}
					break;

				default :
                        fprintf(listing, "unknown declaration node.\n");
						break;
			}
		}break;
		case NODE_TYPE:
		{
			switch(node->kind.type)
			{
			case TYPE_SIMPLE_SYS:
			   
				break;
			case TYPE_SIMPLE_ID:
				ml = st_lookup(currentSymTab,node->attr.name);
				if(ml.type ==EXPTYPE_UNKNOW)
					fprintf(listing, "Undefine identifier %s\n", node->attr.name);
				node->type = ml.type;
				break;
			case TYPE_SIMPLE_ENUM:
				node ->type = EXPTYPE_ENUM;
				
				break;
			case TYPE_SIMPLE_LIMIT:
				
				node ->type = EXPTYPE_LIMIT;
			case TYPE_ARRAY:
				node->type = EXPTYPE_ARRAY;
				//
				break;
			case TYPE_RECORD:
				node ->type = EXPTYPE_RECORD;
				//
				break;
			default:
				node ->type = EXPTYPE_UNKNOW;
				break;
			}
		}
		default:	fprintf(listing, "unknown node kind.\n");
				break;
	}
	ml.isfathervar=0;
	ml.offset=-1;
	return ml;
}


void printSymTab()
{
	int i;
	fprintf(listing, "Variable Name 	Location 	Line Number\n");
	fprintf(listing, "--------------	---------	--------------\n");
	for(i = 0; i<HASHSIZE; i++)
	{
		printHashList( topHashTable[i] );
	}
}

void CT_insert(ConstValueItem item){
    ConstValueTable[ConstValueNum++] = item;
}

ConstValueItem CT_lookup(char* name){
    int i;
    for(i=0;i<ConstValueNum;i++){
        if(strcmp(name,ConstValueTable[i]->name)==0){
            return ConstValueTable[i];
        }
    }
    return NULL;
}

void TT_insert(TypeItem item){
    TypeTable[TypeItemNum++] = item;

}
TypeItem TT_lookup(char* name){
    int i;
    for(i=0;i<TypeItemNum;i++){
        if(strcmp(name,TypeTable[i]->name)==0){
            return TypeTable[i];
        }
    }
    return NULL;
}





