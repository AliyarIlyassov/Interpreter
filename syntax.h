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

struct Poliz {
	Lex * p;
	int size;
	int free;

	Poliz ( int max_size );

	~Poliz() { delete []p; };

//	void put_lex(Lex l, int place) { p[place]=l; };
	void put_lex(Lex l) { p[free++] = l; };
	void blank() { ++free; };

	Lex& operator[] ( int index );

	void print();
};

struct Parser {
	Lex curr_lex; // текущая лексема
	type_lex c_type;
	string c_val;
	Scanner scan;

	Stack < string, 100 > st_str;
	Stack < Lex, 100 > st_lex;

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

	Poliz prog;

	Parser ( const char *program) : scan (program), c_type(LEX_NULL), prog(1000) {}
	
	void analyze();
};

#endif
