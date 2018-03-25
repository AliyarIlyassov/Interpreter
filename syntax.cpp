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
	cout << "( " << c_type << " : " << c_val << " )\n";
}


void Parser::analyze () {
	cout << "Analyze\n";
	Prog();
//	cout << endl << "Analysis was successful\n" << endl;
}

void Parser::Prog() {
	cout << "Prog\n";
	Dcls();
//	TID.print();
	Stmts();
	if (c_type != LEX_FIN)
		throw curr_lex;
}

void Parser::Dcls() {
	cout << "Dcls\n";
	Dcl();
	if (c_type == LEX_NLINE) {
		Dcls();
	}
}

void Parser::Dcl() {
	gl();
	cout << "Dcl\n";
	Lex Tmp(c_type, c_val);
	if (c_type == LEX_INUM || c_type == LEX_FNUM) {
		gl();
		if (c_type == LEX_ID) {
			prog.put_lex(curr_lex);
			prog.put_lex(Tmp);
			st_str.push(c_val);
			dec();
			gl();
		} else
			throw curr_lex;
	}
}

void Parser::Stmts() {
	cout << "Stmts\n";
	Stmt();
	if (c_type == LEX_NLINE) {
		gl();
		if (c_type == LEX_ID || c_type == LEX_PRINT || c_type == LEX_IF)
			Stmts();
	}	else
		throw curr_lex;
}

void Parser::Stmt() {
	cout << "Stmt\n";
	cout << curr_lex << endl;
	if (c_type == LEX_ID) {
		st_str.push(c_val);
		check_id();
		prog.put_lex(Lex(POLIZ_ADDRESS, c_val));
		gl();
		if (c_type == LEX_ASSIGN) {
			Equation();
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
	} else if (c_type == LEX_IF) {
		BoolStmt();
		if (c_type == LEX_NLINE)
			gl();
		else
			throw curr_lex;
		prog.put_lex(Lex(LEX_IF, "if"));
		while (c_type != LEX_ENDIF && c_type != LEX_ELSE)
			Stmt();
		if (c_type == LEX_ELSE) {
			prog.put_lex(Lex(LEX_ELSE, "else"));
			gl();
			while(c_type != LEX_ENDIF)
				Stmt();
		}
		prog.put_lex(Lex(LEX_ENDIF, "endif"));
		gl();
	} else if (c_type == LEX_NLINE)
		gl();
}

void Parser::BoolStmt() {
	cout << "BoolStmt\n";
	Expr1();
//	if (c_type != LEX_NLINE)
//		BoolStmt();
	if(c_type == LEX_AND || c_type == LEX_OR || c_type == LEX_EQUAL || c_type == LEX_NEQUAL) {
		Lex TMP = curr_lex;
		if (c_type != LEX_NLINE)
			BoolStmt();
		prog.put_lex(TMP);
	}
}

void Parser::Expr1() {
	gl();
	cout << "Expr1\n";
	if (c_type == LEX_LBR) {
		BoolStmt();
		if (c_type != LEX_RBR)
			throw "Syntax Error : No Right bracket\n";
		else
			gl();
	} else if (c_type != LEX_ID && c_type != LEX_INT && c_type != LEX_FLOAT && c_type != LEX_SQRT &&
						 c_type != LEX_LN && c_type != LEX_EXP && c_type != LEX_TRUE && c_type != LEX_FALSE) {
		throw curr_lex;
	} else if (c_type == LEX_SQRT || c_type == LEX_LN || c_type == LEX_EXP) {
		Lex TMP(c_type, c_val);
		Expr1();
		prog.put_lex(TMP);
	} else {
		prog.put_lex(curr_lex);
		gl();
	}

}

void Parser::Equation() {
	cout << "Equation\n";
	Equation2();
	if(c_type == LEX_PLUS || c_type == LEX_MINUS) {
		Lex TMP = curr_lex;
		if (c_type != LEX_NLINE)
			Equation();
		prog.put_lex(TMP);
	}
}

void Parser::Equation2() {
	cout << "Equation2\n";
	Expr();
	if (c_type == LEX_MULT || c_type == LEX_DIV) {
		Lex TMP = curr_lex;
		if (c_type != LEX_NLINE)
			Equation2();
		prog.put_lex(TMP);
	}
}

void Parser::Expr() {
	cout << "Expr\n";
	gl();
	if (c_type == LEX_LBR) {
		Equation();
		if (c_type != LEX_RBR)
			throw "Syntax Error : No Right bracket\n";
		else
			gl();
	} else if (c_type != LEX_ID && c_type != LEX_INT && c_type != LEX_FLOAT &&
						 c_type != LEX_SQRT && c_type != LEX_LN && c_type != LEX_EXP) {
		throw curr_lex;
	} else if (c_type == LEX_SQRT || c_type == LEX_LN || c_type == LEX_EXP) {
		Lex TMP(c_type, c_val);
		Expr();
		prog.put_lex(TMP);
	} else {
		prog.put_lex(curr_lex);
		gl();
	}
}
