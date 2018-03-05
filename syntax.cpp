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

void Parser::gl () {   
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
		if (c_type == LEX_ID)
			gl();
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
		else
			gl();
	}
}

void Parser::Val() {
	gl();
//	check_id();
//	prog.put_lex(c_lex);
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

/*void Parser::dec(type_lex Type) {
	int i;
	while (!st_int.is_empty()) {
		i = st_int.pop();

		if (TID[i].declare)
			throw "Redeclaration";
		else {
			TID[i].declare = true;
			TID[i].type = Type;
		}
	}
	cout << "Declared : " << TID.p[i].name << endl;
}

void Parser::check_id() {
	int ind = fromString<int>(c_val);
	if (TID.p[ind].declare)
		st_lex.push(TID.p[ind].type);
	else
		throw "Not Declared";
}

void Parser::check_op() {
	type_lex t1, t2, op;

	t2 = st_lex.pop();
	op = st_lex.pop();
	t1 = st_lex.pop();

	cout << "( " << t1 << " " << op << " " << t2 << " )" << "\n";

	if (t1 != t2)
		st_lex.push(LEX_FLOAT);
	else if (t1 == t2)
		st_lex.push(t1);
	else
		throw "Wrong types in operation";
}

void Parser::eq_type() {
	if (st_lex.pop() != st_lex.pop())
		throw "Wrong types in assignment";
}*/

void Interpretator::interpretation()
{
	pars.analyze();
//	cout << "Start execute: " << endl;
//	E.execute(pars.prog);
}

