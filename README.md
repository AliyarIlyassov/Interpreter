# Interpreter
#
# Interpreter of a simple language

	Prog       -> Dcls Stmts $
	Dcls       -> Dcl Dcls | Eps
	Dcl        -> "float" id | "int" id
	Stmts      -> Stm Stmts | Eps
	Stmt       -> id assign Equation | "print" id
	Equation   -> Equation2 { (+|-) Equation2 }
	Equation2  -> Expr { (* | / ) Expr }
	Expr       -> id | inum | fnum | "sqrt" Expr | "ln" Expr | "exp" Expr
	id         -> char id | Eps
	char       -> 'a' | 'b' | 'c' | ... | 'x' | 'y' | 'z'
	assign     -> '='
	plus       -> '+'
	minus      -> '-'
	inum       -> 0 inum | 1 inum | ... | 9 inum | Eps
	fnum       -> 0 fnum '.' numb | 1 fnum '.' numb | ... | 9 fnum '.' numb
	numb       -> 0 inum | 1 inum | ... | 9 inum
	Eps        -> ''

	1) Each identifier should be declared in the start of a program and declared once
	2) In assign operator operands must be of the same type
	3) In any place of a program, except identifiers, reserved words and numbers, there can be an arbitrary number of indents, tabs and spaces
