#include "visual.h"

static int spacelength = 0;

void showSyntaxTree(SyntaxTree root)
{
    int i;
    spacelength += 2;
    while (root != NULL) {
        //print spaces;
        int k;
        for (k = 0; k < spacelength; k++) {
            fprintf(visualTree, " ");
        }

        if (root->nodeKind == StatementNode) {

            switch (root->kind.stmt) {
            case LabelStmt:
                fprintf(visualTree, "Label\n");
                break;
            case AssignStmt:
                fprintf(visualTree, "Assign\n");
                break;
            case GotoStmt:
                fprintf(visualTree, "Goto\n");
                break;
            case IfStmt:
                fprintf(visualTree, "If\n");
                break;
            case RepeatStmt:
                fprintf(visualTree, "Repeat\n");
                break;
            case WhileStmt:
                fprintf(visualTree, "While\n");
                break;
            case ForStmt:
                fprintf(visualTree, "For\n");
                break;
            case CaseStmt:
                fprintf(visualTree, "Case\n");
                break;
            case ProcIdStmt:
                fprintf(visualTree, "ProcId\n");
                break;
            case ProcSysStmt:
                fprintf(visualTree, "ProcSys\n");
                break;
            case FuncIdStmt:
                fprintf(visualTree, "FuncId\n");
                break;
            case FuncSysStmt:
                fprintf(visualTree, "FuncSys\n");
            default:
                break;
            }

        } else if (root->nodeKind == ExpressionNode) {

            switch (root->kind.exp) {
            case IdExp:
                fprintf(visualTree, "Id:%s\n", root->attr.name);
                break;
            case ConstExp:
                fprintf(visualTree, "Const");
                switch (root->type) {
                case IntExpType:
                    fprintf(visualTree, ":%d\n", root->attr.intValue);
                    break;
                case RealExpType:
                    fprintf(visualTree, ":%lf\n", root->attr.realValue);
                    break;
                case CharExpType:
                    fprintf(visualTree, ":%c\n", root->attr.charValue);
                    break;
                case StringExpType:
                    fprintf(visualTree, ":%s\n", root->attr.stringValue);
                    break;
                case BoolExpType:
                    fprintf(visualTree, ":%d\n", root->attr.intValue);
                    break;
                default:
                    fprintf(visualTree, "\n");
                    break;
                }
                break;
            case OpExp:
                fprintf(visualTree, "Oper:");
                switch(root->attr.op)
                {
                        
                    case GeOp:
                        fprintf(visualTree, ">=\n");
                        break;
                    case GtOp:
                        fprintf(visualTree, ">\n");
                        break;
                    case LeOp:
                        fprintf(visualTree, "<=\n");
                        break;
                    case LtOp:
                        fprintf(visualTree, "<\n");
                        break;
                    case EqualOp:
                        fprintf(visualTree, "=\n");
                        break;
                    case UnequalOp:
                        fprintf(visualTree, "<>\n");
                        break;
                    case PlusOp:
                        fprintf(visualTree, "+\n");
                        break;
                    case MinusOp:
                        fprintf(visualTree, "-\n");
                        break;
                    case OrOp:
                        fprintf(visualTree, "or\n");
                        break;
                    case MulOp:
                        fprintf(visualTree, "*\n");
                        break;
                    case DivOp:
                        fprintf(visualTree, "/\n");
                        break;
                    case ModOp:
                        fprintf(visualTree, "mod\n");
                        break;
                    case AndOp:
                        fprintf(visualTree, "and\n");
                        break;
                    case NotOp:
                        fprintf(visualTree, "not\n");
                        break;
                    case AbsOp:
                        fprintf(visualTree, "abs\n");
                        break;
                    case ChrOp:
                        fprintf(visualTree, "chr\n");
                        break;
                    case OddOp:
                        fprintf(visualTree, "odd\n");
                        break;
                    case OrdOp:
                        fprintf(visualTree, "ord\n");
                        break;
                    case PredOp:
                        fprintf(visualTree, "pred\n");
                        break;
                    case SqrOp:
                        fprintf(visualTree, "sqr\n");
                        break;
                    case SqrtOp:
                        fprintf(visualTree, "sqrt\n");
                        break;
                    case SuccOp:
                        fprintf(visualTree, "succ\n");
                        break;
                    case ReadOp:
                        fprintf(visualTree, "read\n");
                        break;
                    case WriteOp:
                        fprintf(visualTree, "write\n");
                        break;
                    case WritelnOp:
                        fprintf(visualTree, "writeln\n");
                        break;
                    case ToOp:
                        fprintf(visualTree, "to\n");
                        break;
                    case DowntoOp:
                        fprintf(visualTree, "downto\n");
                        break;
                }
                break;
            case CaseExp:
                fprintf(visualTree, "Case\n");
                break;
            default:
                break;
            }

        } else if (root->nodeKind == DeclareNode) {

            switch (root->kind.decl) {
            case ProgramDecl:
                fprintf(visualTree, "ProgramDecl:%s\n",root->attr.name);
                break;
            case ProgramheadDecl:
                fprintf(visualTree, "ProgramheadDecl\n");
                break;
            case RoutineheadDecl:
                fprintf(visualTree, "RoutineheadDecl\n");
                break;
            case FunctionDecl:
                fprintf(visualTree, "FunctionDecl:%s\n",root->attr.name);
                break;
            case FunctionheadDecl:
                fprintf(visualTree, "FunctionheadDecl\n");
                break;
            case ProcedureDecl:
                fprintf(visualTree, "ProcedureDecl\n");
                break;
            case ProcedureheadDecl:
                fprintf(visualTree, "ProcedureheadDecl\n");
                break;
            case ConstDecl:
                fprintf(visualTree, "ConstDecl\n");
                break;
            case VarDecl:
                fprintf(visualTree, "VarDecl\n");
                break;
            case VarParaDecl:
                fprintf(visualTree, "VarParaDecl\n");
                break;
            default:
                break;
            }

        } else if (root->nodeKind == TypeNode) {

            switch (root->kind.type) {
            case SimpleSysType:
                fprintf(visualTree, "SimpleSysType:");
                switch(root->type)
                {
                        
                    case UnknowExpType:
                        fprintf(visualTree, "UnknowExpType\n");
                        break;
                    case UserExpType:
                        fprintf(visualTree, "UserExpType\n");
                        break;
                    case VoidExpType:
                        fprintf(visualTree, "VoidExpType\n");
                        break;
                    case IntExpType:
                        fprintf(visualTree, "IntExpType\n");
                        break;
                    case RealExpType:
                        fprintf(visualTree, "RealExpType\n");
                        break;
                    case PointerExpType:
                        fprintf(visualTree, "PointerExpType\n");
                        break;
                    case CharExpType:
                        fprintf(visualTree, "CharExpType\n");
                        break;
                    case StringExpType:
                        fprintf(visualTree, "StringExpType\n");
                        break;
                    case BoolExpType:
                        fprintf(visualTree, "BoolExpType\n");
                        break;
                    case ArrayExpType:
                        fprintf(visualTree, "ArrayExpType\n");
                        break;
                    case RecordExpType:
                        fprintf(visualTree, "RecordExpType\n");
                        break;
                    case EnumExpType:
                        fprintf(visualTree, "EnumExpType\n");
                        break;
                    case LimitExpType:
                        fprintf(visualTree, "LimitExpType\n");
                        break;
                    case FuncExpType:
                        fprintf(visualTree, "FuncExpType\n");
                        break;
                }
                break;
            case SimpleIdType:
                fprintf(visualTree, "SimpleIdType\n");
                break;
            case SimpleEnumType:
                fprintf(visualTree, "SimpleEnumType\n");
                break;
            case simpleLimitType:
                fprintf(visualTree, "SimpleLimitType\n");
                break;
            case ArrayType:
                fprintf(visualTree, "ArrayType\n");
                break;
            case RecordType:
                fprintf(visualTree, "RecordType\n");
                break;
            default:
                break;
            }
        } else {
            fprintf(visualTree, "Unknown nodeKind\n");
        }

        for (i = 0; i < MAXCHILDREN; i++) {
            showSyntaxTree(root->child[i]);
        }

        root = root->sibling;
    }
    spacelength -= 2;
}
