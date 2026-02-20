/* mcc89 - src/operator.c
 * made by matyz
 * licensed under MPL 2.0
 */

#include "operator.h"
#include "str.h"

enum operator operator_from_str(str_t slice) {
    switch (slice.len) {
        case 1:
            switch (slice.ptr[0]) {
                case '=': return OP_ASSIGN;
                case '<': return OP_LT;
                case '>': return OP_GT;
                case '^': return OP_XOR;
                case '+': return OP_ADD;
                case '-': return OP_SUB;
                case '%': return OP_MOD;
                case '/': return OP_DIV;
                case '*': return OP_MUL;
                case '&': return OP_AND;
                case '|': return OP_OR;
                case '.': return OP_DOT;
                case '?': return OP_QM;
                case '!': return OP_NEG;
                case ':': return OP_COLON;
                default: return OP_NONE;
            }
        case 2:
            switch (slice.ptr[0]) {
                case '=': return slice.ptr[1] == '=' ? OP_EQ : OP_NONE;
                case '<': 
                    return slice.ptr[1] == '=' ? OP_LTE : (slice.ptr[1] == '<' ? OP_LSH : OP_NONE);
                case '>': 
                    return slice.ptr[1] == '=' ? OP_GTE : (slice.ptr[1] == '>' ? OP_RSH : OP_NONE);
                case '^': return slice.ptr[1] == '=' ? OP_XORASSIGN : OP_NONE;
                case '+': return slice.ptr[1] == '=' ? OP_ADDASSIGN : OP_NONE;
                case '-': return slice.ptr[1] == '=' ? OP_SUBASSIGN : (slice.ptr[1] == '>' ? OP_ARROW : OP_NONE);
                case '*': return slice.ptr[1] == '=' ? OP_MULASSIGN : OP_NONE;
                case '%': return slice.ptr[1] == '=' ? OP_MODASSIGN : OP_NONE;
                case '/': return slice.ptr[1] == '=' ? OP_DIVASSIGN : OP_NONE;
                case '&': return slice.ptr[1] == '=' ? OP_ANDASSIGN : (slice.ptr[1] == '&' ? OP_CMP_AND : OP_NONE);
                case '!': return slice.ptr[1] == '=' ? OP_NEGASSIGN : OP_NONE;
                case '|': return slice.ptr[1] == '=' ? OP_ORASSIGN : (slice.ptr[1] == '|' ? OP_CMP_OR : OP_NONE);
            }
        case 3:
            switch (slice.ptr[0]) {
                case '<': return (slice.ptr[1] == '<' && slice.ptr[2] == '=') ? OP_LSHASSIGN : OP_NONE;
                case '>': return (slice.ptr[1] == '>' && slice.ptr[2] == '=') ? OP_RSHASSIGN : OP_NONE;
                default: return OP_NONE;
            }
        default: return OP_NONE;
    }
}

unsigned char operator_as_str_len(enum operator self) {
    switch (self) {
        case OP_NONE: return 0;
        case OP_XORASSIGN:
        case OP_ANDASSIGN:
        case OP_ORASSIGN:
        case OP_SUBASSIGN:
        case OP_ADDASSIGN:
        case OP_MULASSIGN:
        case OP_DIVASSIGN:
        case OP_NEGASSIGN:
        case OP_MODASSIGN:
        case OP_ARROW:
        case OP_LSH:
        case OP_RSH:
        case OP_EQ:
        case OP_LTE:
        case OP_GTE:
        case OP_CMP_AND:
        case OP_CMP_OR: return 2;
        case OP_LSHASSIGN:
        case OP_RSHASSIGN: return 3;
        
        case OP_MOD:
        case OP_QM:
        case OP_DOT:
        case OP_COLON:
        case OP_LT:
        case OP_GT:
        case OP_ASSIGN:
        case OP_XOR:
        case OP_AND:
        case OP_OR:
        case OP_SUB:
        case OP_ADD:
        case OP_MUL:
        case OP_DIV:
        case OP_NEG: return 1;
    }
    return 0;
}

void operator_print(enum operator* operator) {
    if (!operator) return;
    switch (*operator) {
        case OP_NONE: break;
        case OP_ARROW: printf("->"); break;
        case OP_ASSIGN: printf("="); break;
        case OP_ADD: printf("+"); break;
        case OP_SUB: printf("-"); break;
        case OP_MUL: printf("*"); break;
        case OP_DIV: printf("/"); break;
        case OP_MOD: printf("%%"); break;
        case OP_AND: printf("&"); break;
        case OP_OR : printf("|"); break;
        case OP_XOR: printf("^"); break;
        case OP_NEG: printf("!"); break;
        case OP_LSH: printf("<<"); break;
        case OP_RSH: printf(">>"); break;
        case OP_ADDASSIGN: printf("+="); break;
        case OP_SUBASSIGN: printf("-="); break;
        case OP_MULASSIGN: printf("*="); break;
        case OP_DIVASSIGN: printf("/="); break;
        case OP_MODASSIGN: printf("%%="); break;
        case OP_ANDASSIGN: printf("&="); break;
        case OP_ORASSIGN: printf("|="); break;
        case OP_XORASSIGN: printf("^="); break;
        case OP_LSHASSIGN: printf("<<="); break;
        case OP_RSHASSIGN: printf(">>="); break;
        
        case OP_LT: printf("<"); break;
        case OP_GT: printf(">"); break;
        case OP_EQ: printf("=="); break;
        case OP_NEGASSIGN: printf("!="); break;
        case OP_GTE: printf(">="); break;
        case OP_LTE: printf("<="); break;
        case OP_CMP_AND: printf("&&"); break;
        case OP_CMP_OR: printf("||"); break;
        case OP_DOT: printf("."); break;
        case OP_QM: printf("?"); break;
        case OP_COLON: printf(","); break;
    }
}
