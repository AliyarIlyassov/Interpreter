#include "lexical.h"
#include <cmath>
#include <iostream>
#include <cstring>

using namespace std;
 
string Scanner::TW[] = {
	"\0", "float", "int", "print", "\0"
};

string Scanner::TD[] = {
	"\0", "=", "+", "-", "$", "\0"
};

type_lex Scanner::TWords[] = {
	LEX_NULL, LEX_FLOAT, LEX_INT, LEX_PRINT, LEX_NULL
};

type_lex Scanner::TDlms[] = {
	LEX_NULL, LEX_ASSIGN, LEX_PLUS, LEX_MINUS, LEX_FIN, LEX_NULL
};

extern tabl_ident TID;

bool blank( char c ) { return (c == ' ' || c == '\n' || c == '\r' || c == '\t'); }

Lex::Lex ( ) : t_lex(LEX_NULL), v_lex("") { };

Lex::Lex ( type_lex t, string v ) : t_lex(t), v_lex(v) { };

ostream & operator << ( ostream & s, Lex l ) {
	s << "( " << l.t_lex << " , " << l.v_lex << " )" << "\n";
		return s;
}

bool operator != (Lex a, Lex b) {
	return (a.t_lex != b.t_lex);
}

Ident::Ident ( ) : name(""), declare(false), type(LEX_NULL), assign(false), value("") {}

ostream & operator << ( ostream &s, Ident &I) {
	s << "Name : " << I.name << "\n";
	s << "Declare : " << I.declare << "\n";
	s << "Type of lex : " << I.type << "\n";
	s << "Assign : " << I.assign << "\n";
	s << "Value : " << I.value << "\n\n";
	return s;
}

tabl_ident::tabl_ident (int max_size) {
	p = new Ident[size = max_size];
	top = 0;
}
	
tabl_ident::~tabl_ident ( ) { delete []p; }

Ident & tabl_ident::operator[] (int k) {
	if (k <= top)
		return p[k];
	else
		throw("Ident index out of range\n");
}

void tabl_ident::put ( string buf ) {
	for (int i = 0; i < top; i++)
		if (buf == (p[i].name) ) {
			return;
		}
	p[top].name = buf;
	p[top++].declare = true;
};

void Scanner::clear() { buf = ""; }
	
void Scanner::gc() { c = fgetc(fp); }

int Scanner::look ( string buf, string * list ) {
	int i = 1;
	while ( list[i].size() ) {
		if ( buf == (list[i]) )
			return i;
		++i;
	}
	return 0;
}
	
Scanner::Scanner ( const char * filename ) {
	fp = fopen(filename, "r");
	ST = H;
	gc();
}

Lex Scanner::get_lex() {
	ST = H;
	string Number;
	bool dot = false;
	int ident_ind;
	while(c != '$') {
		switch (ST) {
			case H :
				clear();
				if (c != '#')
					buf = c;
				else
					gc();
				if ( blank(c) );
				else if (isalpha(c)) {
					ST = IDENT;
				} else if ( isdigit(c) ) {
					ST = NUMB;
				} else if (c == '#') {
					ST = COM;
				} else
					ST = DELIM;
				break;
			case IDENT :
				if ( isalpha(c) || isdigit(c) )
					buf += c;
				else if ( blank(c) ) {
					if (ident_ind = look(buf, TW))
						return Lex(TWords[ident_ind], buf);
					else {
						TID.put(buf);
						return Lex(LEX_ID, buf);
					}
				} else
					throw "Lex Error : Identifier error\n";
				break;
			case NUMB:
				if (c == '.')
					dot = true;
				if ( isdigit(c) || c == '.') {
					buf += c;
				} else if (blank(c)) {
					if (dot)
						return Lex(LEX_FNUM, buf);
					else
						return Lex(LEX_INUM, buf);
				} else
					throw "Lex Error : Number reading error\n";
				break;
			case COM :
				if ( c == '\n' )
					ST = H;
				break;
			case DELIM :
				if ( ident_ind = look(buf, TD) )
					return Lex(TDlms[ident_ind], buf);
				else
					throw "Lex Error : Delimeter error\n";
				break;
		}// end switch
		gc();
	}
	return Lex(LEX_FIN, "$");
}
