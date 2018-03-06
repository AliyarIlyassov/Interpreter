#include "lexical.h"
#include "syntax.h"
#include <stack>
#include <iostream>

using namespace std;

extern tabl_ident TID;

template <typename T, int max_size >
void Stack <T, max_size >::push(T i) {
	if ( !is_full() ) {
		s[top++] = i;
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

Poliz::Poliz ( int max_size ) {
	p = new Lex [size = max_size];
	free = 0;
}

Lex & Poliz::operator[] ( int index ) {
	if (index > size) 
		throw "POLIZ : Out of array";
	else if ( index > free )
		throw "POLIZ : Indefinite element of array";
	else
		return p[index];
}

void Poliz::print() {
	for ( int i = 0; i < free; ++i )
		cout << p[i];
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
//			cout << "Match " << id_name << "\n";
			return;
		}
	}
	throw id_name + " not declared";
}

void Parser::gl() {   
	curr_lex = scan.get_lex();
	c_type = curr_lex.t_lex;
	c_val = curr_lex.v_lex;
//	cout << "( " << c_type << " : " << c_val << " )\n";
}


void Parser::analyze () {
//	cout << "Analyze started : \n";
	Prog();
	cout << endl << "Analysis was successful\n" << endl;
}

void Parser::Prog() {
//	cout << "Prog\n";
	Dcls();
	Stmts();
	if (c_type != LEX_FIN)
		throw curr_lex;
}

void Parser::Dcls() {
//	cout << "Dcls\n";
	Dcl();
	if (c_type == LEX_INT || c_type == LEX_FLOAT)
		Dcls();
}

void Parser::Dcl() {
	if (c_type == LEX_NULL)
		gl();
//	cout << "Dcl\n";
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
//	cout << "Stmts\n";
	Stmt();
	if (c_type == LEX_ID || c_type == LEX_PRINT)
		Stmts();
}

void Parser::Stmt() {
//	cout << "Stmt\n";
	if (c_type == LEX_ID) {
		st_str.push(c_val);
		check_id();
		prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
		gl();
		if (c_type == LEX_ASSIGN) {
			Val();
			Expr();
			prog.put_lex(Lex(LEX_ASSIGN, "="));
		} else
			throw curr_lex;
	} else if (c_type == LEX_PRINT) {
		gl();
		if (c_type != LEX_ID)
			throw curr_lex;
		else {
			st_str.push(c_val);
			check_id();
			prog.put_lex(curr_lex);
			prog.put_lex(Lex(LEX_PRINT, "print"));
			gl();
		}
	}
}

void Parser::Val() {
	gl();
//	cout << "Val\n";
	if(c_type != LEX_ID && c_type != LEX_INUM && c_type != LEX_FNUM)
		throw curr_lex;
	else
		prog.put_lex(curr_lex);
}

void Parser::Expr() {
	gl();
//	cout << "Expr\n";
	if (c_type == LEX_PLUS) {
		Val();
		prog.put_lex(Lex(LEX_PLUS, "+"));
		Expr();
	} else if (c_type == LEX_MINUS) {
		Val();
		prog.put_lex(Lex(LEX_MINUS, "-"));
		Expr();
	}
}
