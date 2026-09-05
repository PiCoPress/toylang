#include <stdlib.h>
#include <string.h>

#include "tokenizers/specials.h"

#define u8 (unsigned char)
#define strpaste(x, r) if(sizeof(x) - 1 == len && !strncmp(x, str, len)) return r;

const struct token_map TOKEN_MAPPER_SPC[256] = {
    ['+'] = {TOK_OPR_ADD, 0},
    ['-'] = {TOK_OPR_SUB, 0},
    ['*'] = {TOK_OPR_ASTERISK, 0},
    ['/'] = {TOK_OPR_SLASH, 0},
    ['%'] = {TOK_OPR_MOD, 0},
    ['&'] = {TOK_OPR_AMPERSAND, 0},
    ['|'] = {TOK_OPR_OR, 0},
    ['^'] = {TOK_OPR_XOR, 0},
    ['~'] = {TOK_OPR_BIT_NOT, 1},
    ['>'] = {TOK_LOGIC_GT, 0},
    ['<'] = {TOK_LOGIC_LT, 0},
    ['='] = {TOK_ASSIGN, 0},
    ['.'] = {TOK_CH_DOT, 0},
    ['!'] = {TOK_LOGIC_NOT, 0},
    ['('] = {TOK_CH_PAR_OPEN, 1},
    [')'] = {TOK_CH_PAR_CLOSE, 1},
    ['{'] = {TOK_CH_BLK_BEGIN, 1},
    ['}'] = {TOK_CH_BLK_END, 1},
    ['['] = {TOK_CH_BRAC_OPEN, 1},
    [']'] = {TOK_CH_BRAC_CLOSE, 1},
    [','] = {TOK_CH_COMMA, 1},
    ['?'] = {TOK_CH_QMARK, 1},
    [':'] = {TOK_CH_COLON, 1},
    ['\''] = {TOK_CH_QUOTE, 1},
    ['"'] = {TOK_CH_DQUOTE, 1},
    [';'] = {TOK_CH_SEMI, 1},

    ['@'] = {TOK_RESERVED, 1},
    ['#'] = {TOK_RESERVED, 1},
    ['$'] = {TOK_RESERVED, 1},
};

int is_valid_sp_char(char c)
{
    int ret = TOKEN_MAPPER_SPC[u8 c].type;
    return ret != TOK_UNDEF && ret != TOK_RESERVED;
}

int can_be_token(char *str, int len)
{
    strpaste("+", TOK_OPR_ADD) else
    strpaste("-", TOK_OPR_SUB) else
    strpaste("*", TOK_OPR_ASTERISK) else
    strpaste("/", TOK_OPR_SLASH) else
    strpaste("%", TOK_OPR_MOD) else
    strpaste("++", TOK_OPR_INC) else
    strpaste("--", TOK_OPR_DEC) else
    strpaste("<<", TOK_OPR_SHL) else
    strpaste(">>", TOK_OPR_SHR) else
    strpaste("&", TOK_OPR_AMPERSAND) else
    strpaste("|", TOK_OPR_OR) else
    strpaste("^", TOK_OPR_XOR) else
    strpaste("~", TOK_OPR_BIT_NOT) else
    strpaste(">", TOK_LOGIC_GT) else
    strpaste(">=", TOK_LOGIC_GE) else
    strpaste("<", TOK_LOGIC_LT) else
    strpaste("<=", TOK_LOGIC_LE) else
    strpaste("&&", TOK_LOGIC_AND) else
    strpaste("||", TOK_LOGIC_OR) else
    strpaste("!", TOK_LOGIC_NOT) else
    strpaste("==", TOK_LOGIC_EQ) else
    strpaste("!=", TOK_LOGIC_NE) else
    strpaste("=", TOK_ASSIGN) else
    strpaste("+=", TOK_ASSIGN_ADD) else
    strpaste("-=", TOK_ASSIGN_SUB) else
    strpaste("*=", TOK_ASSIGN_MUL) else
    strpaste("/=", TOK_ASSIGN_DIV) else
    strpaste("%=", TOK_ASSIGN_MOD) else
    strpaste("|=", TOK_ASSIGN_OR) else
    strpaste("&=", TOK_ASSIGN_AND) else
    strpaste("^=", TOK_ASSIGN_XOR) else
    strpaste("<<=", TOK_ASSIGN_SHL) else
    strpaste(">>=", TOK_ASSIGN_SHR) else
    strpaste(".", TOK_CH_DOT) else
    strpaste(",", TOK_CH_COMMA) else
    strpaste(":", TOK_CH_COLON) else
    strpaste(";", TOK_CH_SEMI) else
    strpaste("?", TOK_CH_QMARK) else
    strpaste("'", TOK_CH_QUOTE) else
    strpaste("\"", TOK_CH_DQUOTE) else
    strpaste("{", TOK_CH_BLK_BEGIN) else
    strpaste("}", TOK_CH_BLK_END) else
    strpaste("[", TOK_CH_BRAC_OPEN) else
    strpaste("]", TOK_CH_BRAC_CLOSE) else
    strpaste("(", TOK_CH_PAR_OPEN) else
    strpaste(")", TOK_CH_PAR_CLOSE) else
    return TOK_UNDEF;
}

/*
    TODO: implement skipping comments, and collecting strings with escapes
 */
int collect_special(struct string *str, char **cursor_ptr, char *const source_end)
{
    char *cursor = *cursor_ptr;
    char buf[8] = "";

    int should_break = 0;
    int avail_token = 0;
    int idx = 0;
    int tok = 0;

    while(1)
    {
        if(idx >= 8) return -13;
        if(cursor >= source_end) break;

        switch(get_char_type(*cursor))
        {
            case SPECIAL:
            {
                if(!is_valid_sp_char(*cursor)) return -12;

                buf[idx] = *cursor;
                ++ idx;
                ++ cursor;

                tok = can_be_token(buf, idx);
                if(!tok)
                {
                    should_break = 1;
                    tok = avail_token;
                    -- cursor;
                } else avail_token = tok;
                break;
            }

            default:
                should_break = 1;
                break;
        }
        if(should_break) break;
    }

    *cursor_ptr = cursor;
	if(tok == 0) return -40;
    return tok;
}
