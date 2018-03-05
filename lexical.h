#ifndef __LEXICAL_H__
#define __LEXICAL_H__
#include <string>
#include <sstream>

using namespace std;

bool blank(char c);

template <typename T>
T toString (T v) {
	ostringstream oss;
	oss << v;
	return oss.str();
}

template <typename T>
T fromString (const string & s) {
	istringstream iss(s);
	T res;
	iss >> res;
	return res;
}

enum type_lex {
	LEX_NULL, LEX_ASSIGN, LEX_FIN, LEX_FLOAT,
	LEX_FNUM, LEX_ID, LEX_INT, LEX_INUM,
	LEX_MINUS, LEX_PLUS, LEX_PRINT, POLIZ_ADDRESS, POLIZ_LABEL,
	POLIZ_GO, POLIZ_FGO, LEX_EOF
};

struct Lex {
	type_lex t_lex;
	string v_lex;

	Lex (  );
	Lex ( type_lex t, string v );
	friend ostream & operator << ( ostream & s, Lex l );
	friend bool operator != (Lex a, Lex b);
};

struct Ident {
	string name;
	bool declare;
	type_lex type;
	bool assign;
	string value;

	Ident ( );
//	Ident ( string Name, bool Declare, type_lex Type, bool Assign, string Value);
	friend ostream & operator << ( ostream &s, Ident &I);
};

struct tabl_ident {
	Ident * p;
	int size;
	int top;
	
	tabl_ident (int max_size);	
	~tabl_ident ( );
	Ident & operator[] (int k);
	void put ( string buf);
};

struct Scanner {
	enum state { H, IDENT, NUMB, COM, DELIM };
	state ST;
	FILE * fp;
	char c;
	string buf;
	int buf_top;
	
	static type_lex TWords[];
	static type_lex TDlms[];
	static string TW[];
	static string TD[];

	Lex get_lex();
	void clear();
	void gc();
	int look ( string buf, string * list );
	Scanner ( const char * filename );
};

#endif
