#include "syntax.h"
#include <stack>
#include <iostream>

using namespace std;

extern tabl_ident TID;

template <typename T, int max_size >
void Stack <T, max_size >::push(T i) {
	if ( !is_full() ) {
		s[top] = i;
		++top;
	} else
		throw "Stack is full";
}

template <class T, int max_size >
T Stack <T, max_size >::pop() {
	if ( !is_empty() ) {
		--top;
		return s[top];
	} else
		throw "Stack is empty";
}

void Parser::dec() {
	string id_name = st_str.pop();
	for (int i = 0; i < TID.top; i++) {
		if (id_name == TID.p[i].name) {
			if (TID.p[i].declare)
				throw "Redeclaration";
			else {
				TID.p[i].declare = true;
				return;
			}
		}
	}
	TID.put(id_name);
}

void Parser::check_id() {
	string id_name = st_str.pop();
	for (int i = 0; i < TID.top; i++) {
		if (id_name == TID.p[i].name) {
			cout << "Match " << id_name << "\n";
			return;
		}
	}
	throw id_name + " not declared";
}

void Parser::gl() {   
	curr_lex = scan.get_lex();
	c_type = curr_lex.t_lex;
	c_val = curr_lex.v_lex;
	cout << "( " << c_type << " : " << c_val << " )\n";
}


void Parser::analyze () {
	cout << "Analyze started : \n";
	Prog();
//	prog.print();
	cout << endl << "Success\n" << endl;
}

void Parser::Prog() {
	cout << "Prog\n";
	Dcls();
	Stmts();
	if (c_type != LEX_FIN)
		throw curr_lex;
}

void Parser::Dcls() {
	cout << "Dcls\n";
	Dcl();
	if (c_type == LEX_INT || c_type == LEX_FLOAT)
		Dcls();
}

void Parser::Dcl() {
	if (c_type == LEX_NULL)
		gl();
	cout << "Dcl\n";
	if (c_type == LEX_INT || c_type == LEX_FLOAT) {
		gl();
		if (c_type == LEX_ID) {
			st_str.push(c_val);
			dec();
			gl();
		}
		else
			throw curr_lex;
	}
}

void Parser::Stmts() {
	cout << "Stmts\n";
	Stmt();
	if (c_type == LEX_ID || c_type == LEX_PRINT)
		Stmts();
}

void Parser::Stmt() {
	cout << "Stmt\n";
	if (c_type == LEX_ID) {
		st_str.push(c_val);
		check_id();
		gl();
		if (c_type == LEX_ASSIGN) {
			Val();
			Expr();
		} else
			throw curr_lex;
	} else if (c_type == LEX_PRINT) {
		gl();
		if (c_type != LEX_ID)
			throw curr_lex;
		else {
			st_str.push(c_val);
			check_id();
			gl();
		}
	}
}

void Parser::Val() {
	gl();
	cout << "Val\n";
	if(c_type != LEX_ID && c_type != LEX_INUM && c_type != LEX_FNUM)
		throw curr_lex;
}

void Parser::Expr() {
	gl();
//	st_lex.push(c_type);
	cout << "Expr\n";
	if (c_type == LEX_PLUS || c_type == LEX_MINUS) {
		Val();
		Expr();
	}
//	check_op();
}

void Interpretator::interpretation()
{
	pars.analyze();
//	cout << "Start execute: " << endl;
//	E.execute(pars.prog);
}

