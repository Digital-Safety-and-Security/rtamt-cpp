
// Generated from StlParser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace grammar {


class  StlParser : public antlr4::Parser {
public:
  enum {
    MINUS = 1, PLUS = 2, TIMES = 3, DIVIDE = 4, LPAREN = 5, RPAREN = 6, 
    LBRACE = 7, RBRACE = 8, LBRACK = 9, RBRACK = 10, SEMICOLON = 11, COLON = 12, 
    COMMA = 13, DOT = 14, AT = 15, ABS = 16, SEC = 17, MSEC = 18, USEC = 19, 
    NSEC = 20, PSEC = 21, ROS_Topic = 22, Import = 23, Input = 24, Output = 25, 
    Internal = 26, Constant = 27, DomainTypeReal = 28, DomainTypeFloat = 29, 
    DomainTypeLong = 30, DomainTypeComplex = 31, DomainTypeInt = 32, DomainTypeBool = 33, 
    Assertion = 34, Specification = 35, From = 36, NotOperator = 37, OrOperator = 38, 
    AndOperator = 39, IffOperator = 40, ImpliesOperator = 41, XorOperator = 42, 
    RiseOperator = 43, FallOperator = 44, AlwaysOperator = 45, EventuallyOperator = 46, 
    UntilOperator = 47, HistoricallyOperator = 48, OnceOperator = 49, SinceOperator = 50, 
    NextOperator = 51, OracleOperator = 52, PreviousOperator = 53, EqualOperator = 54, 
    NotEqualOperator = 55, GreaterOrEqualOperator = 56, LesserOrEqualOperator = 57, 
    GreaterOperator = 58, LesserOperator = 59, EQUAL = 60, BooleanLiteral = 61, 
    TRUE = 62, FALSE = 63, IntegerLiteral = 64, RealLiteral = 65, Identifier = 66, 
    LINE_TERMINATOR = 67, WHITESPACE = 68, COMMENT = 69, LINE_COMMENT = 70
  };

  enum {
    RuleStlfile = 0, RuleStlSpecification = 1, RuleSpec = 2, RuleAssertion = 3, 
    RuleDeclaration = 4, RuleAnnotation = 5, RuleAnnotation_type = 6, RuleVariableDeclaration = 7, 
    RuleAssignment = 8, RuleDomainType = 9, RuleIoType = 10, RuleInterval = 11, 
    RuleIntervalTime = 12, RuleUnit = 13, RuleTopExpression = 14, RuleExpression = 15, 
    RuleReal_expression = 16, RuleComparisonOp = 17, RuleLiteral = 18
  };

  StlParser(antlr4::TokenStream *input);
  ~StlParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class StlfileContext;
  class StlSpecificationContext;
  class SpecContext;
  class AssertionContext;
  class DeclarationContext;
  class AnnotationContext;
  class Annotation_typeContext;
  class VariableDeclarationContext;
  class AssignmentContext;
  class DomainTypeContext;
  class IoTypeContext;
  class IntervalContext;
  class IntervalTimeContext;
  class UnitContext;
  class TopExpressionContext;
  class ExpressionContext;
  class Real_expressionContext;
  class ComparisonOpContext;
  class LiteralContext; 

  class  StlfileContext : public antlr4::ParserRuleContext {
  public:
    StlfileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StlSpecificationContext *stlSpecification();
    antlr4::tree::TerminalNode *EOF();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StlfileContext* stlfile();

  class  StlSpecificationContext : public antlr4::ParserRuleContext {
  public:
    StlSpecificationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssertionContext *assertion();
    SpecContext *spec();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<AnnotationContext *> annotation();
    AnnotationContext* annotation(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StlSpecificationContext* stlSpecification();

  class  SpecContext : public antlr4::ParserRuleContext {
  public:
    SpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    SpecContext() = default;
    void copyFrom(SpecContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SpecificationContext : public SpecContext {
  public:
    SpecificationContext(SpecContext *ctx);

    antlr4::tree::TerminalNode *Specification();
    antlr4::tree::TerminalNode *Identifier();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  SpecContext* spec();

  class  AssertionContext : public antlr4::ParserRuleContext {
  public:
    AssertionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *EQUAL();
    TopExpressionContext *topExpression();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssertionContext* assertion();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    DeclarationContext() = default;
    void copyFrom(DeclarationContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DeclVariableContext : public DeclarationContext {
  public:
    DeclVariableContext(DeclarationContext *ctx);

    VariableDeclarationContext *variableDeclaration();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  DeclarationContext* declaration();

  class  AnnotationContext : public antlr4::ParserRuleContext {
  public:
    AnnotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT();
    Annotation_typeContext *annotation_type();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationContext* annotation();

  class  Annotation_typeContext : public antlr4::ParserRuleContext {
  public:
    Annotation_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Annotation_typeContext() = default;
    void copyFrom(Annotation_typeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RosTopicContext : public Annotation_typeContext {
  public:
    RosTopicContext(Annotation_typeContext *ctx);

    antlr4::tree::TerminalNode *ROS_Topic();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> Identifier();
    antlr4::tree::TerminalNode* Identifier(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Annotation_typeContext* annotation_type();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DomainTypeContext *domainType();
    antlr4::tree::TerminalNode *Identifier();
    antlr4::tree::TerminalNode *Constant();
    IoTypeContext *ioType();
    AssignmentContext *assignment();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AssignmentContext() = default;
    void copyFrom(AssignmentContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AsgnExprContext : public AssignmentContext {
  public:
    AsgnExprContext(AssignmentContext *ctx);

    antlr4::tree::TerminalNode *EQUAL();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AsgnLiteralContext : public AssignmentContext {
  public:
    AsgnLiteralContext(AssignmentContext *ctx);

    antlr4::tree::TerminalNode *EQUAL();
    LiteralContext *literal();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AssignmentContext* assignment();

  class  DomainTypeContext : public antlr4::ParserRuleContext {
  public:
    DomainTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DomainTypeFloat();
    antlr4::tree::TerminalNode *DomainTypeInt();
    antlr4::tree::TerminalNode *DomainTypeLong();
    antlr4::tree::TerminalNode *DomainTypeComplex();
    antlr4::tree::TerminalNode *Identifier();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DomainTypeContext* domainType();

  class  IoTypeContext : public antlr4::ParserRuleContext {
  public:
    IoTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Input();
    antlr4::tree::TerminalNode *Output();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IoTypeContext* ioType();

  class  IntervalContext : public antlr4::ParserRuleContext {
  public:
    IntervalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    std::vector<IntervalTimeContext *> intervalTime();
    IntervalTimeContext* intervalTime(size_t i);
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *RBRACK();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntervalContext* interval();

  class  IntervalTimeContext : public antlr4::ParserRuleContext {
  public:
    IntervalTimeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    IntervalTimeContext() = default;
    void copyFrom(IntervalTimeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntervalTimeLiteralContext : public IntervalTimeContext {
  public:
    IntervalTimeLiteralContext(IntervalTimeContext *ctx);

    LiteralContext *literal();
    UnitContext *unit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  IntervalTimeContext* intervalTime();

  class  UnitContext : public antlr4::ParserRuleContext {
  public:
    UnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEC();
    antlr4::tree::TerminalNode *MSEC();
    antlr4::tree::TerminalNode *USEC();
    antlr4::tree::TerminalNode *NSEC();
    antlr4::tree::TerminalNode *PSEC();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnitContext* unit();

  class  TopExpressionContext : public antlr4::ParserRuleContext {
  public:
    TopExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TopExpressionContext() = default;
    void copyFrom(TopExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExprContext : public TopExpressionContext {
  public:
    ExprContext(TopExpressionContext *ctx);

    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprUntimedEvExprContext : public TopExpressionContext {
  public:
    ExprUntimedEvExprContext(TopExpressionContext *ctx);

    antlr4::tree::TerminalNode *EventuallyOperator();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprUntimedAlwaysExprContext : public TopExpressionContext {
  public:
    ExprUntimedAlwaysExprContext(TopExpressionContext *ctx);

    antlr4::tree::TerminalNode *AlwaysOperator();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TopExpressionContext* topExpression();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExprParenContext : public ExpressionContext {
  public:
    ExprParenContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAndExprContext : public ExpressionContext {
  public:
    ExprAndExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *AndOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpreOnceExprContext : public ExpressionContext {
  public:
    ExpreOnceExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *OnceOperator();
    ExpressionContext *expression();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAlwaysExprContext : public ExpressionContext {
  public:
    ExprAlwaysExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *AlwaysOperator();
    IntervalContext *interval();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprImpliesExprContext : public ExpressionContext {
  public:
    ExprImpliesExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *ImpliesOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprXorExprContext : public ExpressionContext {
  public:
    ExprXorExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *XorOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprSinceExprContext : public ExpressionContext {
  public:
    ExprSinceExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *SinceOperator();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprNotContext : public ExpressionContext {
  public:
    ExprNotContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *NotOperator();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprOrExprContext : public ExpressionContext {
  public:
    ExprOrExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *OrOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprIffExprContext : public ExpressionContext {
  public:
    ExprIffExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *IffOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprFallContext : public ExpressionContext {
  public:
    ExprFallContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *FallOperator();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprRiseContext : public ExpressionContext {
  public:
    ExprRiseContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *RiseOperator();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprHistExprContext : public ExpressionContext {
  public:
    ExprHistExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *HistoricallyOperator();
    ExpressionContext *expression();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprRealContext : public ExpressionContext {
  public:
    ExprRealContext(ExpressionContext *ctx);

    Real_expressionContext *real_expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprUntilExprContext : public ExpressionContext {
  public:
    ExprUntilExprContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *UntilOperator();
    IntervalContext *interval();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprEvExprContext : public ExpressionContext {
  public:
    ExprEvExprContext(ExpressionContext *ctx);

    antlr4::tree::TerminalNode *EventuallyOperator();
    IntervalContext *interval();
    ExpressionContext *expression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdCompIntContext : public ExpressionContext {
  public:
    IdCompIntContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    ComparisonOpContext *comparisonOp();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  Real_expressionContext : public antlr4::ParserRuleContext {
  public:
    Real_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Real_expressionContext() = default;
    void copyFrom(Real_expressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExprSubtractionContext : public Real_expressionContext {
  public:
    ExprSubtractionContext(Real_expressionContext *ctx);

    std::vector<Real_expressionContext *> real_expression();
    Real_expressionContext* real_expression(size_t i);
    antlr4::tree::TerminalNode *MINUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprDivisionContext : public Real_expressionContext {
  public:
    ExprDivisionContext(Real_expressionContext *ctx);

    std::vector<Real_expressionContext *> real_expression();
    Real_expressionContext* real_expression(size_t i);
    antlr4::tree::TerminalNode *DIVIDE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprMultiplicationContext : public Real_expressionContext {
  public:
    ExprMultiplicationContext(Real_expressionContext *ctx);

    std::vector<Real_expressionContext *> real_expression();
    Real_expressionContext* real_expression(size_t i);
    antlr4::tree::TerminalNode *TIMES();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprLiteralContext : public Real_expressionContext {
  public:
    ExprLiteralContext(Real_expressionContext *ctx);

    LiteralContext *literal();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprIdContext : public Real_expressionContext {
  public:
    ExprIdContext(Real_expressionContext *ctx);

    antlr4::tree::TerminalNode *Identifier();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAbsContext : public Real_expressionContext {
  public:
    ExprAbsContext(Real_expressionContext *ctx);

    antlr4::tree::TerminalNode *ABS();
    antlr4::tree::TerminalNode *LPAREN();
    Real_expressionContext *real_expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAdditionContext : public Real_expressionContext {
  public:
    ExprAdditionContext(Real_expressionContext *ctx);

    std::vector<Real_expressionContext *> real_expression();
    Real_expressionContext* real_expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  Real_expressionContext* real_expression();
  Real_expressionContext* real_expression(int precedence);
  class  ComparisonOpContext : public antlr4::ParserRuleContext {
  public:
    ComparisonOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ComparisonOpContext() = default;
    void copyFrom(ComparisonOpContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  CmpOpEqContext : public ComparisonOpContext {
  public:
    CmpOpEqContext(ComparisonOpContext *ctx);

    antlr4::tree::TerminalNode *EqualOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CmpOpGteContext : public ComparisonOpContext {
  public:
    CmpOpGteContext(ComparisonOpContext *ctx);

    antlr4::tree::TerminalNode *GreaterOrEqualOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CmpOpLseContext : public ComparisonOpContext {
  public:
    CmpOpLseContext(ComparisonOpContext *ctx);

    antlr4::tree::TerminalNode *LesserOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CmpOpGtContext : public ComparisonOpContext {
  public:
    CmpOpGtContext(ComparisonOpContext *ctx);

    antlr4::tree::TerminalNode *GreaterOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ComOpNeqContext : public ComparisonOpContext {
  public:
    ComOpNeqContext(ComparisonOpContext *ctx);

    antlr4::tree::TerminalNode *NotEqualOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CmpOpLsContext : public ComparisonOpContext {
  public:
    CmpOpLsContext(ComparisonOpContext *ctx);

    antlr4::tree::TerminalNode *LesserOrEqualOperator();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ComparisonOpContext* comparisonOp();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *RealLiteral();
    antlr4::tree::TerminalNode *MINUS();
    LiteralContext *literal();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);
  bool real_expressionSempred(Real_expressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace grammar
