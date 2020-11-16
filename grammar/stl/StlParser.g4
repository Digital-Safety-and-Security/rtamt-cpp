parser grammar StlParser ;

options {
	tokenVocab = StlLexer ;
}

stlfile
	: stlSpecification EOF ;

stlSpecification
    : ( spec )? ( declaration | annotation )* assertion ;
	
spec
	: Specification Identifier #Specification ;

assertion 
	: Identifier EQUAL topExpression ;

declaration 
	: variableDeclaration                                         #declVariable 
	: constantDeclaration                                         #declConstant;

annotation
        : '@' annotation_type ;

annotation_type
        : ROS_Topic LPAREN Identifier COMMA Identifier RPAREN #rosTopic;

variableDeclaration
	: ioType? domainType Identifier assignment?  ;
	
constantDeclaration
	: Constant domainType Identifier EQUAL literal  ;

assignment
	: EQUAL literal 				#AsgnLiteral
	| EQUAL expression 				#AsgnExpr ;

domainType
	: DomainTypeFloat
	| DomainTypeInt
    | DomainTypeLong
    | DomainTypeComplex
    | Identifier ;

ioType
	: Input
	| Output ;

interval
	: LBRACK intervalTime COLON intervalTime RBRACK ;

intervalTime
	: literal ( unit )?      #intervalTimeLiteral ;

unit
    : SEC | MSEC | USEC | NSEC | PSEC ; 

topExpression
	:
    AlwaysOperator expression                                   #ExprUntimedAlwaysExpr
    | EventuallyOperator expression                             #ExprUntimedEvExpr
    | expression                                                #Expr
    ;

expression
	:
    real_expression                                             #ExprReal
    | expression comparisonOp expression                        #IdCompInt
	| LPAREN expression RPAREN                                  #ExprParen
	| NotOperator expression                                    #ExprNot

    | expression OrOperator expression                          #ExprOrExpr
    | expression AndOperator expression                         #ExprAndExpr
    | expression ImpliesOperator expression                     #ExprImpliesExpr
    | expression IffOperator expression                         #ExprIffExpr
    | expression XorOperator expression                         #ExprXorExpr

	| AlwaysOperator interval expression                        #ExprAlwaysExpr
    | EventuallyOperator interval expression                    #ExprEvExpr
    | expression UntilOperator interval expression              #ExprUntilExpr
    | HistoricallyOperator ( interval )? expression             #ExprHistExpr
    | OnceOperator ( interval )? expression                     #ExpreOnceExpr
    | expression SinceOperator ( interval )? expression         #ExprSinceExpr
    | RiseOperator LPAREN expression RPAREN                     #ExprRise
    | FallOperator LPAREN expression RPAREN                     #ExprFall
	;

real_expression:
    Identifier                                                  #ExprId
    | literal                                                   #ExprLiteral
    | real_expression PLUS real_expression                      #ExprAddition
	| real_expression MINUS real_expression                     #ExprSubtraction
	| real_expression TIMES real_expression                     #ExprMultiplication
	| real_expression DIVIDE real_expression                    #ExprDivision

	| ABS LPAREN real_expression RPAREN                         #ExprAbs
	;


comparisonOp
	: LesserOrEqualOperator                                     #CmpOpLs
	| GreaterOrEqualOperator 				                    #CmpOpGte
	| LesserOperator                                            #CmpOpLse
	| GreaterOperator                                           #CmpOpGt 
    | EqualOperator                                             #CmpOpEq
    | NotEqualOperator                                          #ComOpNeq
	;
	
literal
	: IntegerLiteral		
	| RealLiteral
	| MINUS literal
	;
