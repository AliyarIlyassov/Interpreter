#ifndef __SYNTAX_H__
#define __SYNTAX_H__
#include <stack>
#include "lexical.h"

extern tabl_ident TID;

template <typename T, int max_size > struct Stack {
	T s[max_size];
	int top;
	Stack() : top(0) { }
	void reset() { top = 0; }
	void push(T i);
	T pop();
	bool is_empty() { return top == 0;}
	bool is_full() { return top == max_size; }
};

struct Parser {
	Lex curr_lex; // текущая лексема
	type_lex c_type;
	string c_val;
	Scanner scan;

	Stack < string, 100 > st_str;
	Stack < type_lex, 100 > st_lex;

	void Prog();
	void Dcls();
	void Stmts();
	void Stmt();
	void Expr();
	void Val();	
	void Dcl();

	void gl ();

	void dec();	//Checks if there was redeclaration
	void check_id();

/*
	void dec ( type_lex Type);
	void check_op ();
	void eq_type ();
	
	Poliz prog;
*/
	Parser ( const char *program) : scan (program), c_type(LEX_NULL) {}
	
	void analyze();
};

struct Interpretator {
	Parser pars;
//	Executer E;	
	Interpretator (const char *program) : pars(program) { }
	void interpretation();
};

#endif
