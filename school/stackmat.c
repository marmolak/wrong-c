#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define STACK_SIZE  5
static const char *symbols = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
static int computed_expressions [ 26 ] = { 0 }, N = 0;
static int stack [STACK_SIZE] = { 0 };
static FILE *symbols_fp = NULL, *expressions_fp = NULL, *output_fp = NULL;

static bool get_symbol_value (const char symbol, int* const ret) {
    if ( NULL == strchr (symbols, symbol) ) { return false; };
    *ret =  computed_expressions [ symbol - 'A' ]; return true;
}
static bool set_symbol_value (const char symbol, const int value) {
    if ( NULL == strchr (symbols, symbol) ) { return false; };
    computed_expressions [ symbol - 'A' ] = value; return true;
}
static bool pop (int* const item) {
    if ( N == 0 ) { return false; }
    *item = stack [--N]; return true;
}
static bool push (const int item) {
    if ( N == STACK_SIZE ) { return false; }
    stack [N++] = item; return true;
}
static inline void init_stack (void) { memset (stack, 0, STACK_SIZE); N = 0; } // clear stack
static inline void init_symbols (void) { memset (computed_expressions, 0,  26); } // clear symbols

static bool evaluate_expression (char* const expr) {
    char *p = strtok (expr, " ");
    while ( NULL != p ) {
        char *endptr = NULL;
        int r = 0, s = 0, item = (int) strtol (p, &endptr, 10);  // mozna cislo
        if ( ( '\0' == *endptr ) && ( '\0' != *p ) ) {
            if ( !push (item) ) { return false; } else { goto finish; }
        }
        if ( '\0' != *(p+1) ) { return false; } // mozna symbol
        if ( get_symbol_value (*p, &item) ) {
            if ( !push (item) ) { return false; } else { goto finish; }
        }   // mozna operand
        if ( !pop (&r) || !pop (&s) ) { return false; }
        switch ( *p ) {
            case '+': if ( !push (r + s) ) return false; break;
            case '*': if ( !push (r * s) ) return false; break;
            case '-': if ( !push (r - s) ) return false; break;
            default: return false; break;
        }
        finish: p = strtok (NULL, " "); // get next token
    } // end while
    return true;
}

static bool parse_symbol_file (void) {
    init_symbols ();
    char symbol = '\0', expression [257] = { '\0' };
    int value = 0, n = 0;
    while ( EOF != (n = fscanf (symbols_fp, "%c: %256[A-Z 0-9-+*]\n", &symbol, expression)) ) {
        init_stack ();
        expression [256] = '\0';
        if ( !( (2 == n) && evaluate_expression (expression) && pop (&value) && set_symbol_value (symbol, value)) )
            { return false; }
    }
    return true;
}

static bool parse_expressions_file (void) {
    char expression [257] = { '\0' }, tmp_expression[257] = { '\0' };
    int n = 0, value = 0;
    while ( EOF != (n = fscanf (expressions_fp, "%256[A-Z 0-9-+*]\n", expression)) ) {
        init_stack ();
        expression [256] = '\0';
        strncpy (tmp_expression, expression, 256);
        if ( !( (1 == n) && evaluate_expression (expression) && pop (&value)) ) { return false; }
        fprintf (output_fp, "%s = %d\n", tmp_expression, value);
    }
    return true;
}

int main (int argc, char *argv[]) {
    if ( argc < 3 ) { return 3; }

    symbols_fp = fopen (argv[1], "r");
    if ( NULL == symbols_fp ) { return 4; }
    expressions_fp = fopen (argv[2], "r");
    if ( NULL == expressions_fp ) { return 5; }
    output_fp = fopen (argv[3], "w");
    if ( NULL == output_fp ) { return 9; }

    if ( !parse_symbol_file () ) { return 6; } // evaluate symbols
    if ( !parse_expressions_file () ) { return 7; } // evaluate expressions
    fclose (symbols_fp);
    fclose (expressions_fp);
    fclose (output_fp);

    return 0;
}
