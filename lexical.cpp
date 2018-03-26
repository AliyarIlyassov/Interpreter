#include "lexical.h"
#include <cmath>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

string Scanner::TW[] = {
	"\0", "float", "int", "print", "sqrt", "ln", "exp", "if", "fi", "true", "false", "and", "or",
	"equal", "notequal", "else", "until", "here", "\0"
};

string Scanner::TD[] = {
	"\0", "=", "+", "-", "*", "/", "$", "(", ")", "\n", "\0"
};

type_lex Scanner::TWords[] = {
	LEX_NULL, LEX_FNUM, LEX_INUM, LEX_PRINT, LEX_SQRT, LEX_LN, LEX_EXP, LEX_IF, LEX_FI, LEX_TRUE,
	LEX_FALSE, LEX_AND, LEX_OR, LEX_EQUAL, LEX_NEQUAL, LEX_ELSE, LEX_UNTIL, LEX_HERE, LEX_NULL
};

type_lex Scanner::TDlms[] = {
	LEX_NULL, LEX_ASSIGN, LEX_PLUS, LEX_MINUS, LEX_MULT, LEX_DIV, LEX_FIN, LEX_LBR, LEX_RBR,
	LEX_NLINE, LEX_NULL
};

extern tabl_ident TID;

bool blank( char c ) { return (c == ' ' || c == '\n' || c == '\r' || c == '\t'); }

Lex::Lex ( ) : t_lex(LEX_NULL), v_lex("") { };

Lex::Lex ( type_lex t, string v ) : t_lex(t), v_lex(v) { };

ostream & operator << ( ostream & s, Lex l ) {
	s << "( " << l.t_lex << " : " << l.v_lex << " )" << "\n";
		return s;
}

int find(string key) {
	for (int i = 0; i < TID.top; i++)
		if (TID.p[i].name == key)
			return i;
	throw "Indefinite identifier\n";
}

void tabl_ident::print() {
	cout << "Identifiers table :\n";
	for (int i = 0; i < top; i++)
		cout << p[i] << endl;
	cout << "End.\n";
}

Lex operator + (Lex a, Lex b) {
  if (a.t_lex != LEX_ID && b.t_lex != LEX_ID) {
    if (a.t_lex == b.t_lex) {
      if (a.t_lex == LEX_INT) {
      	int a_ival = atoi(a.v_lex.c_str());
      	int b_ival = atoi(b.v_lex.c_str());
        return Lex(LEX_INT, to_string(a_ival + b_ival));
      }
    }
    float a_fval = atof(a.v_lex.c_str());
    float b_fval = atof(b.v_lex.c_str());
    return Lex(LEX_FLOAT, to_string(a_fval + b_fval));
  } else {
    int j;
    if (a.t_lex == LEX_ID) {
      j = find(a.v_lex);
      if (b.t_lex == LEX_ID) {
        int i = find(b.v_lex);
        return Lex(TID.p[j].numb_type, TID.p[j].value) + Lex(TID.p[i].numb_type, TID.p[i].value);
      }
      return Lex(TID.p[j].numb_type, TID.p[j].value) + b;
    }
    j = find(b.v_lex);
    b.t_lex = a.t_lex;
    b.v_lex = a.v_lex;
    return Lex(TID.p[j].numb_type, TID.p[j].value) + b;
  }
}

Lex operator - (Lex a, Lex b) {
  if (a.t_lex != LEX_ID && b.t_lex != LEX_ID) {
    if (a.t_lex == b.t_lex) {
      if (a.t_lex == LEX_INT) {
      	int a_ival = atoi(a.v_lex.c_str());
      	int b_ival = atoi(b.v_lex.c_str());
        return Lex(LEX_INT, to_string(a_ival - b_ival));
      }
    }
    float a_fval = atof(a.v_lex.c_str());
    float b_fval = atof(b.v_lex.c_str());
    return Lex(LEX_FLOAT, to_string(a_fval - b_fval));
  } else {
    int j;
    if (a.t_lex == LEX_ID) {
      j = find(a.v_lex);
      if (b.t_lex == LEX_ID) {
        int i = find(b.v_lex);
        return Lex(TID.p[j].numb_type, TID.p[j].value) - Lex(TID.p[i].numb_type, TID.p[i].value);
      }
      return Lex(TID.p[j].numb_type, TID.p[j].value) - b;
    }
    j = find(b.v_lex);
    b.t_lex = a.t_lex;
    b.v_lex = a.v_lex;
    return b - Lex(TID.p[j].numb_type, TID.p[j].value);
  }
}

Lex operator * (Lex a, Lex b) {
  if (a.t_lex != LEX_ID && b.t_lex != LEX_ID) {
    if (a.t_lex == b.t_lex) {
      if (a.t_lex == LEX_INT) {
      	int a_ival = atoi(a.v_lex.c_str());
      	int b_ival = atoi(b.v_lex.c_str());
        return Lex(LEX_INT, to_string(a_ival * b_ival));
      }
    }
    float a_fval = atof(a.v_lex.c_str());
    float b_fval = atof(b.v_lex.c_str());
    return Lex(LEX_FLOAT, to_string(a_fval * b_fval));
  } else {
    int j;
    if (a.t_lex == LEX_ID) {
      j = find(a.v_lex);
      if (b.t_lex == LEX_ID) {
        int i = find(b.v_lex);
        return Lex(TID.p[j].numb_type, TID.p[j].value) * Lex(TID.p[i].numb_type, TID.p[i].value);
      }
      return Lex(TID.p[j].numb_type, TID.p[j].value) * b;
    }
    j = find(b.v_lex);
    b.t_lex = a.t_lex;
    b.v_lex = a.v_lex;
    return Lex(TID.p[j].numb_type, TID.p[j].value) * b;
  }
}

Lex operator / (Lex a, Lex b) {
	if (a.t_lex != LEX_ID && b.t_lex != LEX_ID) {
    if (a.t_lex == b.t_lex) {
      if (a.t_lex == LEX_INT) {
      	int a_ival = atoi(a.v_lex.c_str());
      	int b_ival = atoi(b.v_lex.c_str());
				if (!b_ival) {
					throw "POLIZ ERROR : Division by zero\n";
				}
        return Lex(LEX_INT, to_string(a_ival / b_ival));
      }
    }
    float a_fval = atof(a.v_lex.c_str());
    float b_fval = atof(b.v_lex.c_str());
		if (!b_fval) {
			throw "POLIZ ERROR : Division by zero\n";
		}
    return Lex(LEX_FLOAT, to_string(a_fval / b_fval));
  } else {
    int j;
    if (a.t_lex == LEX_ID) {
      j = find(a.v_lex);
      if (b.t_lex == LEX_ID) {
        int i = find(b.v_lex);
        return Lex(TID.p[j].numb_type, TID.p[j].value) / Lex(TID.p[i].numb_type, TID.p[i].value);
      }
      return Lex(TID.p[j].numb_type, TID.p[j].value) / b;
    }
    j = find(b.v_lex);
    b.t_lex = a.t_lex;
    b.v_lex = a.v_lex;
		return b / Lex(TID.p[j].numb_type, TID.p[j].value);
  }
}

Lex operator && (Lex a, Lex b) {
	if (a.t_lex == LEX_TRUE)
		return Lex(LEX_FLOAT, "1") && b;
	if (a.t_lex == LEX_FALSE)
		return Lex(LEX_FLOAT, "0") && b;
	if (b.t_lex == LEX_TRUE)
		return a && Lex(LEX_FLOAT, "1");
	if (a.t_lex == LEX_FALSE)
		return a && Lex(LEX_FLOAT, "0");
	if (a.t_lex == LEX_ID) {
		a.t_lex = LEX_FLOAT;
		int tmp_index = find(a.v_lex);
		a.v_lex = TID.p[tmp_index].value;
	}
	if (b.t_lex == LEX_ID) {
		b.t_lex = LEX_FLOAT;
		int tmp_index = find(b.v_lex);
		b.v_lex = TID.p[tmp_index].value;
	}
	if (atof(a.v_lex.c_str()) && atof(b.v_lex.c_str()))
		return Lex(LEX_TRUE, "true");
	else
		return Lex(LEX_FALSE, "false");
}

Lex operator || (Lex a, Lex b) {
	if (a.t_lex == LEX_TRUE)
		return Lex(LEX_FLOAT, "1") || b;
	if (a.t_lex == LEX_FALSE)
		return Lex(LEX_FLOAT, "0") || b;
	if (b.t_lex == LEX_TRUE)
		return a || Lex(LEX_FLOAT, "1");
	if (a.t_lex == LEX_FALSE)
		return a || Lex(LEX_FLOAT, "0");
	if (a.t_lex == LEX_ID) {
		a.t_lex = LEX_FLOAT;
		int tmp_index = find(a.v_lex);
		a.v_lex = TID.p[tmp_index].value;
	}
	if (b.t_lex == LEX_ID) {
		b.t_lex = LEX_FLOAT;
		int tmp_index = find(b.v_lex);
		b.v_lex = TID.p[tmp_index].value;
	}
	if (atof(a.v_lex.c_str()) || atof(b.v_lex.c_str()))
		return Lex(LEX_TRUE, "true");
	else
		return Lex(LEX_FALSE, "false");
}

Lex operator == (Lex a, Lex b) {
	if (a.t_lex == LEX_TRUE)
		return Lex(LEX_FLOAT, "1") == b;
	if (a.t_lex == LEX_FALSE)
		return Lex(LEX_FLOAT, "0") == b;
	if (b.t_lex == LEX_TRUE)
		return a == Lex(LEX_FLOAT, "1");
	if (a.t_lex == LEX_FALSE)
		return a == Lex(LEX_FLOAT, "0");
	if (a.t_lex == LEX_ID) {
		a.t_lex = LEX_FLOAT;
		int tmp_index = find(a.v_lex);
		a.v_lex = TID.p[tmp_index].value;
	}
	if (b.t_lex == LEX_ID) {
		b.t_lex = LEX_FLOAT;
		int tmp_index = find(b.v_lex);
		b.v_lex = TID.p[tmp_index].value;
	}
	if (atof(a.v_lex.c_str()) == atof(b.v_lex.c_str()))
		return Lex(LEX_TRUE, "true");
	else
		return Lex(LEX_FALSE, "false");
}

Lex operator != (Lex a, Lex b) {
	if (a.t_lex == LEX_TRUE)
		return Lex(LEX_FLOAT, "1") != b;
	if (a.t_lex == LEX_FALSE)
		return Lex(LEX_FLOAT, "0") != b;
	if (b.t_lex == LEX_TRUE)
		return a != Lex(LEX_FLOAT, "1");
	if (a.t_lex == LEX_FALSE)
		return a != Lex(LEX_FLOAT, "0");
	if (a.t_lex == LEX_ID) {
		a.t_lex = LEX_FLOAT;
		int tmp_index = find(a.v_lex);
		a.v_lex = TID.p[tmp_index].value;
	}
	if (b.t_lex == LEX_ID) {
		b.t_lex = LEX_FLOAT;
		int tmp_index = find(b.v_lex);
		b.v_lex = TID.p[tmp_index].value;
	}
	if (atof(a.v_lex.c_str()) != atof(b.v_lex.c_str()))
		return Lex(LEX_TRUE, "true");
	else
		return Lex(LEX_FALSE, "false");
}

Ident::Ident ( ) : name(""), declare(false), type(LEX_NULL), numb_type(LEX_NULL), assign(false), value("") {}

ostream & operator << ( ostream &s, Ident &I) {
	s << "Name : " << I.name << "\n";
	s << "Declare : " << I.declare << "\n";
	s << "Type of lex : " << I.type << "\n";
	s << "Number Type : " << I.numb_type << "\n";
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
	p[top++].name = buf;
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

bool delim (char c) { return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'); }

Lex Scanner::get_lex() {
	ST = H;
	string Number;
	bool dot = false;
	int ident_ind;
	while(c != '$') {
		switch (ST) {
			case H :
				clear();
				buf = c;
				if ( blank(c) ) {
					if (c == '\n') {
						gc();
						return Lex(LEX_NLINE, "\n");
					}
				} else if (isalpha(c)) {
					ST = IDENT;
				} else if ( isdigit(c) ) {
					ST = NUMB;
				} else if (c == '#') {
					ST = COM;
				} else if (c == '(') {
					gc();
					return Lex(LEX_LBR, "(");
				} else if (c == ')') {
					gc();
					return Lex(LEX_RBR, ")");
				} else
					ST = DELIM;
				break;
			case IDENT :
				if ( isalpha(c) || isdigit(c) )
					buf += c;
				else if ( blank(c) || delim(c)) {
					if (ident_ind = look(buf, TW))
						return Lex(TWords[ident_ind], buf);
					else {
						TID.put(buf);
						return Lex(LEX_ID, buf);
					}
				} else {
					throw "Lex Error : Identifier error\n";
				}
				break;
			case NUMB:
				if (c == '.')
					dot = true;
				if ( isdigit(c) || c == '.') {
					buf += c;
				} else if (blank(c) || c == ')' || delim(c)) {
					if (dot)
						return Lex(LEX_FLOAT, buf);
					else
						return Lex(LEX_INT, buf);
				} else
					throw "Lex Error : Number reading error\n";
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
