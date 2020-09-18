
// Generated from StlLexer.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace grammar {


class  StlLexer : public antlr4::Lexer {
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

  StlLexer(antlr4::CharStream *input);
  ~StlLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace grammar
