
// Generated from StlParser.g4 by ANTLR 4.8


#include "StlParserVisitor.h"

#include "StlParser.h"


using namespace antlrcpp;
using namespace grammar;
using namespace antlr4;

StlParser::StlParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

StlParser::~StlParser() {
  delete _interpreter;
}

std::string StlParser::getGrammarFileName() const {
  return "StlParser.g4";
}

const std::vector<std::string>& StlParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& StlParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StlfileContext ------------------------------------------------------------------

StlParser::StlfileContext::StlfileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StlParser::StlSpecificationContext* StlParser::StlfileContext::stlSpecification() {
  return getRuleContext<StlParser::StlSpecificationContext>(0);
}

tree::TerminalNode* StlParser::StlfileContext::EOF() {
  return getToken(StlParser::EOF, 0);
}


size_t StlParser::StlfileContext::getRuleIndex() const {
  return StlParser::RuleStlfile;
}


antlrcpp::Any StlParser::StlfileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitStlfile(this);
  else
    return visitor->visitChildren(this);
}

StlParser::StlfileContext* StlParser::stlfile() {
  StlfileContext *_localctx = _tracker.createInstance<StlfileContext>(_ctx, getState());
  enterRule(_localctx, 0, StlParser::RuleStlfile);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    stlSpecification();
    setState(41);
    match(StlParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StlSpecificationContext ------------------------------------------------------------------

StlParser::StlSpecificationContext::StlSpecificationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StlParser::AssertionContext* StlParser::StlSpecificationContext::assertion() {
  return getRuleContext<StlParser::AssertionContext>(0);
}

StlParser::SpecContext* StlParser::StlSpecificationContext::spec() {
  return getRuleContext<StlParser::SpecContext>(0);
}

std::vector<StlParser::DeclarationContext *> StlParser::StlSpecificationContext::declaration() {
  return getRuleContexts<StlParser::DeclarationContext>();
}

StlParser::DeclarationContext* StlParser::StlSpecificationContext::declaration(size_t i) {
  return getRuleContext<StlParser::DeclarationContext>(i);
}

std::vector<StlParser::AnnotationContext *> StlParser::StlSpecificationContext::annotation() {
  return getRuleContexts<StlParser::AnnotationContext>();
}

StlParser::AnnotationContext* StlParser::StlSpecificationContext::annotation(size_t i) {
  return getRuleContext<StlParser::AnnotationContext>(i);
}


size_t StlParser::StlSpecificationContext::getRuleIndex() const {
  return StlParser::RuleStlSpecification;
}


antlrcpp::Any StlParser::StlSpecificationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitStlSpecification(this);
  else
    return visitor->visitChildren(this);
}

StlParser::StlSpecificationContext* StlParser::stlSpecification() {
  StlSpecificationContext *_localctx = _tracker.createInstance<StlSpecificationContext>(_ctx, getState());
  enterRule(_localctx, 2, StlParser::RuleStlSpecification);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StlParser::Specification) {
      setState(43);
      spec();
    }
    setState(50);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(48);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case StlParser::Input:
          case StlParser::Output:
          case StlParser::Constant:
          case StlParser::DomainTypeFloat:
          case StlParser::DomainTypeLong:
          case StlParser::DomainTypeComplex:
          case StlParser::DomainTypeInt:
          case StlParser::Identifier: {
            setState(46);
            declaration();
            break;
          }

          case StlParser::AT: {
            setState(47);
            annotation();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(52);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(53);
    assertion();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecContext ------------------------------------------------------------------

StlParser::SpecContext::SpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::SpecContext::getRuleIndex() const {
  return StlParser::RuleSpec;
}

void StlParser::SpecContext::copyFrom(SpecContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SpecificationContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::SpecificationContext::Specification() {
  return getToken(StlParser::Specification, 0);
}

tree::TerminalNode* StlParser::SpecificationContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}

StlParser::SpecificationContext::SpecificationContext(SpecContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::SpecificationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitSpecification(this);
  else
    return visitor->visitChildren(this);
}
StlParser::SpecContext* StlParser::spec() {
  SpecContext *_localctx = _tracker.createInstance<SpecContext>(_ctx, getState());
  enterRule(_localctx, 4, StlParser::RuleSpec);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<SpecContext *>(_tracker.createInstance<StlParser::SpecificationContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(55);
    match(StlParser::Specification);
    setState(56);
    match(StlParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssertionContext ------------------------------------------------------------------

StlParser::AssertionContext::AssertionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::AssertionContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}

tree::TerminalNode* StlParser::AssertionContext::EQUAL() {
  return getToken(StlParser::EQUAL, 0);
}

StlParser::TopExpressionContext* StlParser::AssertionContext::topExpression() {
  return getRuleContext<StlParser::TopExpressionContext>(0);
}


size_t StlParser::AssertionContext::getRuleIndex() const {
  return StlParser::RuleAssertion;
}


antlrcpp::Any StlParser::AssertionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitAssertion(this);
  else
    return visitor->visitChildren(this);
}

StlParser::AssertionContext* StlParser::assertion() {
  AssertionContext *_localctx = _tracker.createInstance<AssertionContext>(_ctx, getState());
  enterRule(_localctx, 6, StlParser::RuleAssertion);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(StlParser::Identifier);
    setState(59);
    match(StlParser::EQUAL);
    setState(60);
    topExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

StlParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::DeclarationContext::getRuleIndex() const {
  return StlParser::RuleDeclaration;
}

void StlParser::DeclarationContext::copyFrom(DeclarationContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DeclVariableContext ------------------------------------------------------------------

StlParser::VariableDeclarationContext* StlParser::DeclVariableContext::variableDeclaration() {
  return getRuleContext<StlParser::VariableDeclarationContext>(0);
}

StlParser::DeclVariableContext::DeclVariableContext(DeclarationContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::DeclVariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitDeclVariable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeclConstantContext ------------------------------------------------------------------

StlParser::ConstantDeclarationContext* StlParser::DeclConstantContext::constantDeclaration() {
  return getRuleContext<StlParser::ConstantDeclarationContext>(0);
}

StlParser::DeclConstantContext::DeclConstantContext(DeclarationContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::DeclConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitDeclConstant(this);
  else
    return visitor->visitChildren(this);
}
StlParser::DeclarationContext* StlParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 8, StlParser::RuleDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(64);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StlParser::Input:
      case StlParser::Output:
      case StlParser::DomainTypeFloat:
      case StlParser::DomainTypeLong:
      case StlParser::DomainTypeComplex:
      case StlParser::DomainTypeInt:
      case StlParser::Identifier: {
        _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<StlParser::DeclVariableContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(62);
        variableDeclaration();
        break;
      }

      case StlParser::Constant: {
        _localctx = dynamic_cast<DeclarationContext *>(_tracker.createInstance<StlParser::DeclConstantContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(63);
        constantDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnnotationContext ------------------------------------------------------------------

StlParser::AnnotationContext::AnnotationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::AnnotationContext::AT() {
  return getToken(StlParser::AT, 0);
}

StlParser::Annotation_typeContext* StlParser::AnnotationContext::annotation_type() {
  return getRuleContext<StlParser::Annotation_typeContext>(0);
}


size_t StlParser::AnnotationContext::getRuleIndex() const {
  return StlParser::RuleAnnotation;
}


antlrcpp::Any StlParser::AnnotationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitAnnotation(this);
  else
    return visitor->visitChildren(this);
}

StlParser::AnnotationContext* StlParser::annotation() {
  AnnotationContext *_localctx = _tracker.createInstance<AnnotationContext>(_ctx, getState());
  enterRule(_localctx, 10, StlParser::RuleAnnotation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(StlParser::AT);
    setState(67);
    annotation_type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Annotation_typeContext ------------------------------------------------------------------

StlParser::Annotation_typeContext::Annotation_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::Annotation_typeContext::getRuleIndex() const {
  return StlParser::RuleAnnotation_type;
}

void StlParser::Annotation_typeContext::copyFrom(Annotation_typeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RosTopicContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::RosTopicContext::ROS_Topic() {
  return getToken(StlParser::ROS_Topic, 0);
}

tree::TerminalNode* StlParser::RosTopicContext::LPAREN() {
  return getToken(StlParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> StlParser::RosTopicContext::Identifier() {
  return getTokens(StlParser::Identifier);
}

tree::TerminalNode* StlParser::RosTopicContext::Identifier(size_t i) {
  return getToken(StlParser::Identifier, i);
}

tree::TerminalNode* StlParser::RosTopicContext::COMMA() {
  return getToken(StlParser::COMMA, 0);
}

tree::TerminalNode* StlParser::RosTopicContext::RPAREN() {
  return getToken(StlParser::RPAREN, 0);
}

StlParser::RosTopicContext::RosTopicContext(Annotation_typeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::RosTopicContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitRosTopic(this);
  else
    return visitor->visitChildren(this);
}
StlParser::Annotation_typeContext* StlParser::annotation_type() {
  Annotation_typeContext *_localctx = _tracker.createInstance<Annotation_typeContext>(_ctx, getState());
  enterRule(_localctx, 12, StlParser::RuleAnnotation_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    _localctx = dynamic_cast<Annotation_typeContext *>(_tracker.createInstance<StlParser::RosTopicContext>(_localctx));
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(StlParser::ROS_Topic);
    setState(70);
    match(StlParser::LPAREN);
    setState(71);
    match(StlParser::Identifier);
    setState(72);
    match(StlParser::COMMA);
    setState(73);
    match(StlParser::Identifier);
    setState(74);
    match(StlParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

StlParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StlParser::DomainTypeContext* StlParser::VariableDeclarationContext::domainType() {
  return getRuleContext<StlParser::DomainTypeContext>(0);
}

tree::TerminalNode* StlParser::VariableDeclarationContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}

StlParser::IoTypeContext* StlParser::VariableDeclarationContext::ioType() {
  return getRuleContext<StlParser::IoTypeContext>(0);
}

StlParser::AssignmentContext* StlParser::VariableDeclarationContext::assignment() {
  return getRuleContext<StlParser::AssignmentContext>(0);
}


size_t StlParser::VariableDeclarationContext::getRuleIndex() const {
  return StlParser::RuleVariableDeclaration;
}


antlrcpp::Any StlParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

StlParser::VariableDeclarationContext* StlParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, StlParser::RuleVariableDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StlParser::Input

    || _la == StlParser::Output) {
      setState(76);
      ioType();
    }
    setState(79);
    domainType();
    setState(80);
    match(StlParser::Identifier);
    setState(82);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StlParser::EQUAL) {
      setState(81);
      assignment();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantDeclarationContext ------------------------------------------------------------------

StlParser::ConstantDeclarationContext::ConstantDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::ConstantDeclarationContext::Constant() {
  return getToken(StlParser::Constant, 0);
}

StlParser::DomainTypeContext* StlParser::ConstantDeclarationContext::domainType() {
  return getRuleContext<StlParser::DomainTypeContext>(0);
}

tree::TerminalNode* StlParser::ConstantDeclarationContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}

tree::TerminalNode* StlParser::ConstantDeclarationContext::EQUAL() {
  return getToken(StlParser::EQUAL, 0);
}

StlParser::LiteralContext* StlParser::ConstantDeclarationContext::literal() {
  return getRuleContext<StlParser::LiteralContext>(0);
}


size_t StlParser::ConstantDeclarationContext::getRuleIndex() const {
  return StlParser::RuleConstantDeclaration;
}


antlrcpp::Any StlParser::ConstantDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitConstantDeclaration(this);
  else
    return visitor->visitChildren(this);
}

StlParser::ConstantDeclarationContext* StlParser::constantDeclaration() {
  ConstantDeclarationContext *_localctx = _tracker.createInstance<ConstantDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 16, StlParser::RuleConstantDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(StlParser::Constant);
    setState(85);
    domainType();
    setState(86);
    match(StlParser::Identifier);
    setState(87);
    match(StlParser::EQUAL);
    setState(88);
    literal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

StlParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::AssignmentContext::getRuleIndex() const {
  return StlParser::RuleAssignment;
}

void StlParser::AssignmentContext::copyFrom(AssignmentContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AsgnExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::AsgnExprContext::EQUAL() {
  return getToken(StlParser::EQUAL, 0);
}

StlParser::ExpressionContext* StlParser::AsgnExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::AsgnExprContext::AsgnExprContext(AssignmentContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::AsgnExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitAsgnExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AsgnLiteralContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::AsgnLiteralContext::EQUAL() {
  return getToken(StlParser::EQUAL, 0);
}

StlParser::LiteralContext* StlParser::AsgnLiteralContext::literal() {
  return getRuleContext<StlParser::LiteralContext>(0);
}

StlParser::AsgnLiteralContext::AsgnLiteralContext(AssignmentContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::AsgnLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitAsgnLiteral(this);
  else
    return visitor->visitChildren(this);
}
StlParser::AssignmentContext* StlParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 18, StlParser::RuleAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<AssignmentContext *>(_tracker.createInstance<StlParser::AsgnLiteralContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(90);
      match(StlParser::EQUAL);
      setState(91);
      literal();
      break;
    }

    case 2: {
      _localctx = dynamic_cast<AssignmentContext *>(_tracker.createInstance<StlParser::AsgnExprContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(92);
      match(StlParser::EQUAL);
      setState(93);
      expression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DomainTypeContext ------------------------------------------------------------------

StlParser::DomainTypeContext::DomainTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::DomainTypeContext::DomainTypeFloat() {
  return getToken(StlParser::DomainTypeFloat, 0);
}

tree::TerminalNode* StlParser::DomainTypeContext::DomainTypeInt() {
  return getToken(StlParser::DomainTypeInt, 0);
}

tree::TerminalNode* StlParser::DomainTypeContext::DomainTypeLong() {
  return getToken(StlParser::DomainTypeLong, 0);
}

tree::TerminalNode* StlParser::DomainTypeContext::DomainTypeComplex() {
  return getToken(StlParser::DomainTypeComplex, 0);
}

tree::TerminalNode* StlParser::DomainTypeContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}


size_t StlParser::DomainTypeContext::getRuleIndex() const {
  return StlParser::RuleDomainType;
}


antlrcpp::Any StlParser::DomainTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitDomainType(this);
  else
    return visitor->visitChildren(this);
}

StlParser::DomainTypeContext* StlParser::domainType() {
  DomainTypeContext *_localctx = _tracker.createInstance<DomainTypeContext>(_ctx, getState());
  enterRule(_localctx, 20, StlParser::RuleDomainType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    _la = _input->LA(1);
    if (!(((((_la - 29) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 29)) & ((1ULL << (StlParser::DomainTypeFloat - 29))
      | (1ULL << (StlParser::DomainTypeLong - 29))
      | (1ULL << (StlParser::DomainTypeComplex - 29))
      | (1ULL << (StlParser::DomainTypeInt - 29))
      | (1ULL << (StlParser::Identifier - 29)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IoTypeContext ------------------------------------------------------------------

StlParser::IoTypeContext::IoTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::IoTypeContext::Input() {
  return getToken(StlParser::Input, 0);
}

tree::TerminalNode* StlParser::IoTypeContext::Output() {
  return getToken(StlParser::Output, 0);
}


size_t StlParser::IoTypeContext::getRuleIndex() const {
  return StlParser::RuleIoType;
}


antlrcpp::Any StlParser::IoTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitIoType(this);
  else
    return visitor->visitChildren(this);
}

StlParser::IoTypeContext* StlParser::ioType() {
  IoTypeContext *_localctx = _tracker.createInstance<IoTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, StlParser::RuleIoType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    _la = _input->LA(1);
    if (!(_la == StlParser::Input

    || _la == StlParser::Output)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalContext ------------------------------------------------------------------

StlParser::IntervalContext::IntervalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::IntervalContext::LBRACK() {
  return getToken(StlParser::LBRACK, 0);
}

std::vector<StlParser::IntervalTimeContext *> StlParser::IntervalContext::intervalTime() {
  return getRuleContexts<StlParser::IntervalTimeContext>();
}

StlParser::IntervalTimeContext* StlParser::IntervalContext::intervalTime(size_t i) {
  return getRuleContext<StlParser::IntervalTimeContext>(i);
}

tree::TerminalNode* StlParser::IntervalContext::COLON() {
  return getToken(StlParser::COLON, 0);
}

tree::TerminalNode* StlParser::IntervalContext::RBRACK() {
  return getToken(StlParser::RBRACK, 0);
}


size_t StlParser::IntervalContext::getRuleIndex() const {
  return StlParser::RuleInterval;
}


antlrcpp::Any StlParser::IntervalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitInterval(this);
  else
    return visitor->visitChildren(this);
}

StlParser::IntervalContext* StlParser::interval() {
  IntervalContext *_localctx = _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 24, StlParser::RuleInterval);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(StlParser::LBRACK);
    setState(101);
    intervalTime();
    setState(102);
    match(StlParser::COLON);
    setState(103);
    intervalTime();
    setState(104);
    match(StlParser::RBRACK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalTimeContext ------------------------------------------------------------------

StlParser::IntervalTimeContext::IntervalTimeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::IntervalTimeContext::getRuleIndex() const {
  return StlParser::RuleIntervalTime;
}

void StlParser::IntervalTimeContext::copyFrom(IntervalTimeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntervalTimeLiteralContext ------------------------------------------------------------------

StlParser::LiteralContext* StlParser::IntervalTimeLiteralContext::literal() {
  return getRuleContext<StlParser::LiteralContext>(0);
}

StlParser::UnitContext* StlParser::IntervalTimeLiteralContext::unit() {
  return getRuleContext<StlParser::UnitContext>(0);
}

StlParser::IntervalTimeLiteralContext::IntervalTimeLiteralContext(IntervalTimeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::IntervalTimeLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitIntervalTimeLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstantTimeLiteralContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ConstantTimeLiteralContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}

StlParser::UnitContext* StlParser::ConstantTimeLiteralContext::unit() {
  return getRuleContext<StlParser::UnitContext>(0);
}

StlParser::ConstantTimeLiteralContext::ConstantTimeLiteralContext(IntervalTimeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ConstantTimeLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitConstantTimeLiteral(this);
  else
    return visitor->visitChildren(this);
}
StlParser::IntervalTimeContext* StlParser::intervalTime() {
  IntervalTimeContext *_localctx = _tracker.createInstance<IntervalTimeContext>(_ctx, getState());
  enterRule(_localctx, 26, StlParser::RuleIntervalTime);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(114);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StlParser::MINUS:
      case StlParser::IntegerLiteral:
      case StlParser::RealLiteral: {
        _localctx = dynamic_cast<IntervalTimeContext *>(_tracker.createInstance<StlParser::IntervalTimeLiteralContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(106);
        literal();
        setState(108);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << StlParser::SEC)
          | (1ULL << StlParser::MSEC)
          | (1ULL << StlParser::USEC)
          | (1ULL << StlParser::NSEC)
          | (1ULL << StlParser::PSEC))) != 0)) {
          setState(107);
          unit();
        }
        break;
      }

      case StlParser::Identifier: {
        _localctx = dynamic_cast<IntervalTimeContext *>(_tracker.createInstance<StlParser::ConstantTimeLiteralContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(110);
        match(StlParser::Identifier);
        setState(112);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << StlParser::SEC)
          | (1ULL << StlParser::MSEC)
          | (1ULL << StlParser::USEC)
          | (1ULL << StlParser::NSEC)
          | (1ULL << StlParser::PSEC))) != 0)) {
          setState(111);
          unit();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitContext ------------------------------------------------------------------

StlParser::UnitContext::UnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::UnitContext::SEC() {
  return getToken(StlParser::SEC, 0);
}

tree::TerminalNode* StlParser::UnitContext::MSEC() {
  return getToken(StlParser::MSEC, 0);
}

tree::TerminalNode* StlParser::UnitContext::USEC() {
  return getToken(StlParser::USEC, 0);
}

tree::TerminalNode* StlParser::UnitContext::NSEC() {
  return getToken(StlParser::NSEC, 0);
}

tree::TerminalNode* StlParser::UnitContext::PSEC() {
  return getToken(StlParser::PSEC, 0);
}


size_t StlParser::UnitContext::getRuleIndex() const {
  return StlParser::RuleUnit;
}


antlrcpp::Any StlParser::UnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitUnit(this);
  else
    return visitor->visitChildren(this);
}

StlParser::UnitContext* StlParser::unit() {
  UnitContext *_localctx = _tracker.createInstance<UnitContext>(_ctx, getState());
  enterRule(_localctx, 28, StlParser::RuleUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << StlParser::SEC)
      | (1ULL << StlParser::MSEC)
      | (1ULL << StlParser::USEC)
      | (1ULL << StlParser::NSEC)
      | (1ULL << StlParser::PSEC))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TopExpressionContext ------------------------------------------------------------------

StlParser::TopExpressionContext::TopExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::TopExpressionContext::getRuleIndex() const {
  return StlParser::RuleTopExpression;
}

void StlParser::TopExpressionContext::copyFrom(TopExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprContext ------------------------------------------------------------------

StlParser::ExpressionContext* StlParser::ExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::ExprContext::ExprContext(TopExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprUntimedEvExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprUntimedEvExprContext::EventuallyOperator() {
  return getToken(StlParser::EventuallyOperator, 0);
}

StlParser::ExpressionContext* StlParser::ExprUntimedEvExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::ExprUntimedEvExprContext::ExprUntimedEvExprContext(TopExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprUntimedEvExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprUntimedEvExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprUntimedAlwaysExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprUntimedAlwaysExprContext::AlwaysOperator() {
  return getToken(StlParser::AlwaysOperator, 0);
}

StlParser::ExpressionContext* StlParser::ExprUntimedAlwaysExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::ExprUntimedAlwaysExprContext::ExprUntimedAlwaysExprContext(TopExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprUntimedAlwaysExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprUntimedAlwaysExpr(this);
  else
    return visitor->visitChildren(this);
}
StlParser::TopExpressionContext* StlParser::topExpression() {
  TopExpressionContext *_localctx = _tracker.createInstance<TopExpressionContext>(_ctx, getState());
  enterRule(_localctx, 30, StlParser::RuleTopExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(123);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<TopExpressionContext *>(_tracker.createInstance<StlParser::ExprUntimedAlwaysExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(118);
      match(StlParser::AlwaysOperator);
      setState(119);
      expression(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<TopExpressionContext *>(_tracker.createInstance<StlParser::ExprUntimedEvExprContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(120);
      match(StlParser::EventuallyOperator);
      setState(121);
      expression(0);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<TopExpressionContext *>(_tracker.createInstance<StlParser::ExprContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(122);
      expression(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

StlParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::ExpressionContext::getRuleIndex() const {
  return StlParser::RuleExpression;
}

void StlParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprParenContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprParenContext::LPAREN() {
  return getToken(StlParser::LPAREN, 0);
}

StlParser::ExpressionContext* StlParser::ExprParenContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

tree::TerminalNode* StlParser::ExprParenContext::RPAREN() {
  return getToken(StlParser::RPAREN, 0);
}

StlParser::ExprParenContext::ExprParenContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAndExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprAndExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprAndExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprAndExprContext::AndOperator() {
  return getToken(StlParser::AndOperator, 0);
}

StlParser::ExprAndExprContext::ExprAndExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprAndExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpreOnceExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExpreOnceExprContext::OnceOperator() {
  return getToken(StlParser::OnceOperator, 0);
}

StlParser::ExpressionContext* StlParser::ExpreOnceExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::IntervalContext* StlParser::ExpreOnceExprContext::interval() {
  return getRuleContext<StlParser::IntervalContext>(0);
}

StlParser::ExpreOnceExprContext::ExpreOnceExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExpreOnceExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExpreOnceExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAlwaysExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprAlwaysExprContext::AlwaysOperator() {
  return getToken(StlParser::AlwaysOperator, 0);
}

StlParser::IntervalContext* StlParser::ExprAlwaysExprContext::interval() {
  return getRuleContext<StlParser::IntervalContext>(0);
}

StlParser::ExpressionContext* StlParser::ExprAlwaysExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::ExprAlwaysExprContext::ExprAlwaysExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprAlwaysExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprAlwaysExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprImpliesExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprImpliesExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprImpliesExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprImpliesExprContext::ImpliesOperator() {
  return getToken(StlParser::ImpliesOperator, 0);
}

StlParser::ExprImpliesExprContext::ExprImpliesExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprImpliesExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprImpliesExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprXorExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprXorExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprXorExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprXorExprContext::XorOperator() {
  return getToken(StlParser::XorOperator, 0);
}

StlParser::ExprXorExprContext::ExprXorExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprXorExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprXorExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprSinceExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprSinceExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprSinceExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprSinceExprContext::SinceOperator() {
  return getToken(StlParser::SinceOperator, 0);
}

StlParser::IntervalContext* StlParser::ExprSinceExprContext::interval() {
  return getRuleContext<StlParser::IntervalContext>(0);
}

StlParser::ExprSinceExprContext::ExprSinceExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprSinceExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprSinceExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprNotContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprNotContext::NotOperator() {
  return getToken(StlParser::NotOperator, 0);
}

StlParser::ExpressionContext* StlParser::ExprNotContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::ExprNotContext::ExprNotContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprOrExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprOrExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprOrExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprOrExprContext::OrOperator() {
  return getToken(StlParser::OrOperator, 0);
}

StlParser::ExprOrExprContext::ExprOrExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprIffExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprIffExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprIffExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprIffExprContext::IffOperator() {
  return getToken(StlParser::IffOperator, 0);
}

StlParser::ExprIffExprContext::ExprIffExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprIffExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprIffExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFallContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprFallContext::FallOperator() {
  return getToken(StlParser::FallOperator, 0);
}

tree::TerminalNode* StlParser::ExprFallContext::LPAREN() {
  return getToken(StlParser::LPAREN, 0);
}

StlParser::ExpressionContext* StlParser::ExprFallContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

tree::TerminalNode* StlParser::ExprFallContext::RPAREN() {
  return getToken(StlParser::RPAREN, 0);
}

StlParser::ExprFallContext::ExprFallContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprFallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprFall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprRiseContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprRiseContext::RiseOperator() {
  return getToken(StlParser::RiseOperator, 0);
}

tree::TerminalNode* StlParser::ExprRiseContext::LPAREN() {
  return getToken(StlParser::LPAREN, 0);
}

StlParser::ExpressionContext* StlParser::ExprRiseContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

tree::TerminalNode* StlParser::ExprRiseContext::RPAREN() {
  return getToken(StlParser::RPAREN, 0);
}

StlParser::ExprRiseContext::ExprRiseContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprRiseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprRise(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprHistExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprHistExprContext::HistoricallyOperator() {
  return getToken(StlParser::HistoricallyOperator, 0);
}

StlParser::ExpressionContext* StlParser::ExprHistExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::IntervalContext* StlParser::ExprHistExprContext::interval() {
  return getRuleContext<StlParser::IntervalContext>(0);
}

StlParser::ExprHistExprContext::ExprHistExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprHistExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprHistExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprRealContext ------------------------------------------------------------------

StlParser::Real_expressionContext* StlParser::ExprRealContext::real_expression() {
  return getRuleContext<StlParser::Real_expressionContext>(0);
}

StlParser::ExprRealContext::ExprRealContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprRealContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprReal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprUntilExprContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::ExprUntilExprContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::ExprUntilExprContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

tree::TerminalNode* StlParser::ExprUntilExprContext::UntilOperator() {
  return getToken(StlParser::UntilOperator, 0);
}

StlParser::IntervalContext* StlParser::ExprUntilExprContext::interval() {
  return getRuleContext<StlParser::IntervalContext>(0);
}

StlParser::ExprUntilExprContext::ExprUntilExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprUntilExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprUntilExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprEvExprContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprEvExprContext::EventuallyOperator() {
  return getToken(StlParser::EventuallyOperator, 0);
}

StlParser::IntervalContext* StlParser::ExprEvExprContext::interval() {
  return getRuleContext<StlParser::IntervalContext>(0);
}

StlParser::ExpressionContext* StlParser::ExprEvExprContext::expression() {
  return getRuleContext<StlParser::ExpressionContext>(0);
}

StlParser::ExprEvExprContext::ExprEvExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprEvExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprEvExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdCompIntContext ------------------------------------------------------------------

std::vector<StlParser::ExpressionContext *> StlParser::IdCompIntContext::expression() {
  return getRuleContexts<StlParser::ExpressionContext>();
}

StlParser::ExpressionContext* StlParser::IdCompIntContext::expression(size_t i) {
  return getRuleContext<StlParser::ExpressionContext>(i);
}

StlParser::ComparisonOpContext* StlParser::IdCompIntContext::comparisonOp() {
  return getRuleContext<StlParser::ComparisonOpContext>(0);
}

StlParser::IdCompIntContext::IdCompIntContext(ExpressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::IdCompIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitIdCompInt(this);
  else
    return visitor->visitChildren(this);
}

StlParser::ExpressionContext* StlParser::expression() {
   return expression(0);
}

StlParser::ExpressionContext* StlParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  StlParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  StlParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, StlParser::RuleExpression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(161);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StlParser::MINUS:
      case StlParser::ABS:
      case StlParser::IntegerLiteral:
      case StlParser::RealLiteral:
      case StlParser::Identifier: {
        _localctx = _tracker.createInstance<ExprRealContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(126);
        real_expression(0);
        break;
      }

      case StlParser::LPAREN: {
        _localctx = _tracker.createInstance<ExprParenContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(127);
        match(StlParser::LPAREN);
        setState(128);
        expression(0);
        setState(129);
        match(StlParser::RPAREN);
        break;
      }

      case StlParser::NotOperator: {
        _localctx = _tracker.createInstance<ExprNotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(131);
        match(StlParser::NotOperator);
        setState(132);
        expression(14);
        break;
      }

      case StlParser::AlwaysOperator: {
        _localctx = _tracker.createInstance<ExprAlwaysExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(133);
        match(StlParser::AlwaysOperator);
        setState(134);
        interval();
        setState(135);
        expression(8);
        break;
      }

      case StlParser::EventuallyOperator: {
        _localctx = _tracker.createInstance<ExprEvExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(137);
        match(StlParser::EventuallyOperator);
        setState(138);
        interval();
        setState(139);
        expression(7);
        break;
      }

      case StlParser::HistoricallyOperator: {
        _localctx = _tracker.createInstance<ExprHistExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(141);
        match(StlParser::HistoricallyOperator);
        setState(143);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == StlParser::LBRACK) {
          setState(142);
          interval();
        }
        setState(145);
        expression(5);
        break;
      }

      case StlParser::OnceOperator: {
        _localctx = _tracker.createInstance<ExpreOnceExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(146);
        match(StlParser::OnceOperator);
        setState(148);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == StlParser::LBRACK) {
          setState(147);
          interval();
        }
        setState(150);
        expression(4);
        break;
      }

      case StlParser::RiseOperator: {
        _localctx = _tracker.createInstance<ExprRiseContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(151);
        match(StlParser::RiseOperator);
        setState(152);
        match(StlParser::LPAREN);
        setState(153);
        expression(0);
        setState(154);
        match(StlParser::RPAREN);
        break;
      }

      case StlParser::FallOperator: {
        _localctx = _tracker.createInstance<ExprFallContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(156);
        match(StlParser::FallOperator);
        setState(157);
        match(StlParser::LPAREN);
        setState(158);
        expression(0);
        setState(159);
        match(StlParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(195);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(193);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<IdCompIntContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(163);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(164);
          comparisonOp();
          setState(165);
          expression(17);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ExprOrExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(167);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(168);
          match(StlParser::OrOperator);
          setState(169);
          expression(14);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ExprAndExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(170);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(171);
          match(StlParser::AndOperator);
          setState(172);
          expression(13);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ExprImpliesExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(173);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(174);
          match(StlParser::ImpliesOperator);
          setState(175);
          expression(12);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<ExprIffExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(176);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(177);
          match(StlParser::IffOperator);
          setState(178);
          expression(11);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<ExprXorExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(179);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(180);
          match(StlParser::XorOperator);
          setState(181);
          expression(10);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<ExprUntilExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(182);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(183);
          match(StlParser::UntilOperator);
          setState(184);
          interval();
          setState(185);
          expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ExprSinceExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(187);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(188);
          match(StlParser::SinceOperator);
          setState(190);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == StlParser::LBRACK) {
            setState(189);
            interval();
          }
          setState(192);
          expression(4);
          break;
        }

        } 
      }
      setState(197);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Real_expressionContext ------------------------------------------------------------------

StlParser::Real_expressionContext::Real_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::Real_expressionContext::getRuleIndex() const {
  return StlParser::RuleReal_expression;
}

void StlParser::Real_expressionContext::copyFrom(Real_expressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprSubtractionContext ------------------------------------------------------------------

std::vector<StlParser::Real_expressionContext *> StlParser::ExprSubtractionContext::real_expression() {
  return getRuleContexts<StlParser::Real_expressionContext>();
}

StlParser::Real_expressionContext* StlParser::ExprSubtractionContext::real_expression(size_t i) {
  return getRuleContext<StlParser::Real_expressionContext>(i);
}

tree::TerminalNode* StlParser::ExprSubtractionContext::MINUS() {
  return getToken(StlParser::MINUS, 0);
}

StlParser::ExprSubtractionContext::ExprSubtractionContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprSubtractionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprSubtraction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprDivisionContext ------------------------------------------------------------------

std::vector<StlParser::Real_expressionContext *> StlParser::ExprDivisionContext::real_expression() {
  return getRuleContexts<StlParser::Real_expressionContext>();
}

StlParser::Real_expressionContext* StlParser::ExprDivisionContext::real_expression(size_t i) {
  return getRuleContext<StlParser::Real_expressionContext>(i);
}

tree::TerminalNode* StlParser::ExprDivisionContext::DIVIDE() {
  return getToken(StlParser::DIVIDE, 0);
}

StlParser::ExprDivisionContext::ExprDivisionContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprDivisionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprDivision(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprMultiplicationContext ------------------------------------------------------------------

std::vector<StlParser::Real_expressionContext *> StlParser::ExprMultiplicationContext::real_expression() {
  return getRuleContexts<StlParser::Real_expressionContext>();
}

StlParser::Real_expressionContext* StlParser::ExprMultiplicationContext::real_expression(size_t i) {
  return getRuleContext<StlParser::Real_expressionContext>(i);
}

tree::TerminalNode* StlParser::ExprMultiplicationContext::TIMES() {
  return getToken(StlParser::TIMES, 0);
}

StlParser::ExprMultiplicationContext::ExprMultiplicationContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprMultiplicationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprMultiplication(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprLiteralContext ------------------------------------------------------------------

StlParser::LiteralContext* StlParser::ExprLiteralContext::literal() {
  return getRuleContext<StlParser::LiteralContext>(0);
}

StlParser::ExprLiteralContext::ExprLiteralContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprIdContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprIdContext::Identifier() {
  return getToken(StlParser::Identifier, 0);
}

StlParser::ExprIdContext::ExprIdContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprId(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAbsContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ExprAbsContext::ABS() {
  return getToken(StlParser::ABS, 0);
}

tree::TerminalNode* StlParser::ExprAbsContext::LPAREN() {
  return getToken(StlParser::LPAREN, 0);
}

StlParser::Real_expressionContext* StlParser::ExprAbsContext::real_expression() {
  return getRuleContext<StlParser::Real_expressionContext>(0);
}

tree::TerminalNode* StlParser::ExprAbsContext::RPAREN() {
  return getToken(StlParser::RPAREN, 0);
}

StlParser::ExprAbsContext::ExprAbsContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprAbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprAbs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAdditionContext ------------------------------------------------------------------

std::vector<StlParser::Real_expressionContext *> StlParser::ExprAdditionContext::real_expression() {
  return getRuleContexts<StlParser::Real_expressionContext>();
}

StlParser::Real_expressionContext* StlParser::ExprAdditionContext::real_expression(size_t i) {
  return getRuleContext<StlParser::Real_expressionContext>(i);
}

tree::TerminalNode* StlParser::ExprAdditionContext::PLUS() {
  return getToken(StlParser::PLUS, 0);
}

StlParser::ExprAdditionContext::ExprAdditionContext(Real_expressionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ExprAdditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitExprAddition(this);
  else
    return visitor->visitChildren(this);
}

StlParser::Real_expressionContext* StlParser::real_expression() {
   return real_expression(0);
}

StlParser::Real_expressionContext* StlParser::real_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  StlParser::Real_expressionContext *_localctx = _tracker.createInstance<Real_expressionContext>(_ctx, parentState);
  StlParser::Real_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, StlParser::RuleReal_expression, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(206);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StlParser::Identifier: {
        _localctx = _tracker.createInstance<ExprIdContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(199);
        match(StlParser::Identifier);
        break;
      }

      case StlParser::MINUS:
      case StlParser::IntegerLiteral:
      case StlParser::RealLiteral: {
        _localctx = _tracker.createInstance<ExprLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(200);
        literal();
        break;
      }

      case StlParser::ABS: {
        _localctx = _tracker.createInstance<ExprAbsContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(201);
        match(StlParser::ABS);
        setState(202);
        match(StlParser::LPAREN);
        setState(203);
        real_expression(0);
        setState(204);
        match(StlParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(222);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(220);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ExprAdditionContext>(_tracker.createInstance<Real_expressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleReal_expression);
          setState(208);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(209);
          match(StlParser::PLUS);
          setState(210);
          real_expression(6);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ExprSubtractionContext>(_tracker.createInstance<Real_expressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleReal_expression);
          setState(211);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(212);
          match(StlParser::MINUS);
          setState(213);
          real_expression(5);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ExprMultiplicationContext>(_tracker.createInstance<Real_expressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleReal_expression);
          setState(214);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(215);
          match(StlParser::TIMES);
          setState(216);
          real_expression(4);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ExprDivisionContext>(_tracker.createInstance<Real_expressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleReal_expression);
          setState(217);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(218);
          match(StlParser::DIVIDE);
          setState(219);
          real_expression(3);
          break;
        }

        } 
      }
      setState(224);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ComparisonOpContext ------------------------------------------------------------------

StlParser::ComparisonOpContext::ComparisonOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t StlParser::ComparisonOpContext::getRuleIndex() const {
  return StlParser::RuleComparisonOp;
}

void StlParser::ComparisonOpContext::copyFrom(ComparisonOpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CmpOpEqContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::CmpOpEqContext::EqualOperator() {
  return getToken(StlParser::EqualOperator, 0);
}

StlParser::CmpOpEqContext::CmpOpEqContext(ComparisonOpContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::CmpOpEqContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitCmpOpEq(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpOpGteContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::CmpOpGteContext::GreaterOrEqualOperator() {
  return getToken(StlParser::GreaterOrEqualOperator, 0);
}

StlParser::CmpOpGteContext::CmpOpGteContext(ComparisonOpContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::CmpOpGteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitCmpOpGte(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpOpLseContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::CmpOpLseContext::LesserOperator() {
  return getToken(StlParser::LesserOperator, 0);
}

StlParser::CmpOpLseContext::CmpOpLseContext(ComparisonOpContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::CmpOpLseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitCmpOpLse(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpOpGtContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::CmpOpGtContext::GreaterOperator() {
  return getToken(StlParser::GreaterOperator, 0);
}

StlParser::CmpOpGtContext::CmpOpGtContext(ComparisonOpContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::CmpOpGtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitCmpOpGt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComOpNeqContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::ComOpNeqContext::NotEqualOperator() {
  return getToken(StlParser::NotEqualOperator, 0);
}

StlParser::ComOpNeqContext::ComOpNeqContext(ComparisonOpContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::ComOpNeqContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitComOpNeq(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpOpLsContext ------------------------------------------------------------------

tree::TerminalNode* StlParser::CmpOpLsContext::LesserOrEqualOperator() {
  return getToken(StlParser::LesserOrEqualOperator, 0);
}

StlParser::CmpOpLsContext::CmpOpLsContext(ComparisonOpContext *ctx) { copyFrom(ctx); }


antlrcpp::Any StlParser::CmpOpLsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitCmpOpLs(this);
  else
    return visitor->visitChildren(this);
}
StlParser::ComparisonOpContext* StlParser::comparisonOp() {
  ComparisonOpContext *_localctx = _tracker.createInstance<ComparisonOpContext>(_ctx, getState());
  enterRule(_localctx, 36, StlParser::RuleComparisonOp);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(231);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StlParser::LesserOrEqualOperator: {
        _localctx = dynamic_cast<ComparisonOpContext *>(_tracker.createInstance<StlParser::CmpOpLsContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(225);
        match(StlParser::LesserOrEqualOperator);
        break;
      }

      case StlParser::GreaterOrEqualOperator: {
        _localctx = dynamic_cast<ComparisonOpContext *>(_tracker.createInstance<StlParser::CmpOpGteContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(226);
        match(StlParser::GreaterOrEqualOperator);
        break;
      }

      case StlParser::LesserOperator: {
        _localctx = dynamic_cast<ComparisonOpContext *>(_tracker.createInstance<StlParser::CmpOpLseContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(227);
        match(StlParser::LesserOperator);
        break;
      }

      case StlParser::GreaterOperator: {
        _localctx = dynamic_cast<ComparisonOpContext *>(_tracker.createInstance<StlParser::CmpOpGtContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(228);
        match(StlParser::GreaterOperator);
        break;
      }

      case StlParser::EqualOperator: {
        _localctx = dynamic_cast<ComparisonOpContext *>(_tracker.createInstance<StlParser::CmpOpEqContext>(_localctx));
        enterOuterAlt(_localctx, 5);
        setState(229);
        match(StlParser::EqualOperator);
        break;
      }

      case StlParser::NotEqualOperator: {
        _localctx = dynamic_cast<ComparisonOpContext *>(_tracker.createInstance<StlParser::ComOpNeqContext>(_localctx));
        enterOuterAlt(_localctx, 6);
        setState(230);
        match(StlParser::NotEqualOperator);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

StlParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StlParser::LiteralContext::IntegerLiteral() {
  return getToken(StlParser::IntegerLiteral, 0);
}

tree::TerminalNode* StlParser::LiteralContext::RealLiteral() {
  return getToken(StlParser::RealLiteral, 0);
}

tree::TerminalNode* StlParser::LiteralContext::MINUS() {
  return getToken(StlParser::MINUS, 0);
}

StlParser::LiteralContext* StlParser::LiteralContext::literal() {
  return getRuleContext<StlParser::LiteralContext>(0);
}


size_t StlParser::LiteralContext::getRuleIndex() const {
  return StlParser::RuleLiteral;
}


antlrcpp::Any StlParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StlParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

StlParser::LiteralContext* StlParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 38, StlParser::RuleLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StlParser::IntegerLiteral: {
        enterOuterAlt(_localctx, 1);
        setState(233);
        match(StlParser::IntegerLiteral);
        break;
      }

      case StlParser::RealLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(234);
        match(StlParser::RealLiteral);
        break;
      }

      case StlParser::MINUS: {
        enterOuterAlt(_localctx, 3);
        setState(235);
        match(StlParser::MINUS);
        setState(236);
        literal();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool StlParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 16: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);
    case 17: return real_expressionSempred(dynamic_cast<Real_expressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool StlParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 16);
    case 1: return precpred(_ctx, 13);
    case 2: return precpred(_ctx, 12);
    case 3: return precpred(_ctx, 11);
    case 4: return precpred(_ctx, 10);
    case 5: return precpred(_ctx, 9);
    case 6: return precpred(_ctx, 6);
    case 7: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool StlParser::real_expressionSempred(Real_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 8: return precpred(_ctx, 5);
    case 9: return precpred(_ctx, 4);
    case 10: return precpred(_ctx, 3);
    case 11: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> StlParser::_decisionToDFA;
atn::PredictionContextCache StlParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN StlParser::_atn;
std::vector<uint16_t> StlParser::_serializedATN;

std::vector<std::string> StlParser::_ruleNames = {
  "stlfile", "stlSpecification", "spec", "assertion", "declaration", "annotation", 
  "annotation_type", "variableDeclaration", "constantDeclaration", "assignment", 
  "domainType", "ioType", "interval", "intervalTime", "unit", "topExpression", 
  "expression", "real_expression", "comparisonOp", "literal"
};

std::vector<std::string> StlParser::_literalNames = {
  "", "'-'", "'+'", "'*'", "'/'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
  "';'", "':'", "','", "'.'", "'@'", "'abs'", "'s'", "'ms'", "'us'", "'ns'", 
  "'ps'", "'topic'", "'import'", "'input'", "'output'", "'internal'", "'const'", 
  "'real'", "'float'", "'long'", "'complex'", "'int'", "'bool'", "'assertion'", 
  "'specification'", "'from'", "'not'", "'or'", "'and'", "", "", "'xor'", 
  "'rise'", "'fall'", "'always'", "'eventually'", "'until'", "'historically'", 
  "'once'", "'since'", "'next'", "'oracle'", "'prev'", "'=='", "'!=='", 
  "'>='", "'<='", "'>'", "'<'", "'='"
};

std::vector<std::string> StlParser::_symbolicNames = {
  "", "MINUS", "PLUS", "TIMES", "DIVIDE", "LPAREN", "RPAREN", "LBRACE", 
  "RBRACE", "LBRACK", "RBRACK", "SEMICOLON", "COLON", "COMMA", "DOT", "AT", 
  "ABS", "SEC", "MSEC", "USEC", "NSEC", "PSEC", "ROS_Topic", "Import", "Input", 
  "Output", "Internal", "Constant", "DomainTypeReal", "DomainTypeFloat", 
  "DomainTypeLong", "DomainTypeComplex", "DomainTypeInt", "DomainTypeBool", 
  "Assertion", "Specification", "From", "NotOperator", "OrOperator", "AndOperator", 
  "IffOperator", "ImpliesOperator", "XorOperator", "RiseOperator", "FallOperator", 
  "AlwaysOperator", "EventuallyOperator", "UntilOperator", "HistoricallyOperator", 
  "OnceOperator", "SinceOperator", "NextOperator", "OracleOperator", "PreviousOperator", 
  "EqualOperator", "NotEqualOperator", "GreaterOrEqualOperator", "LesserOrEqualOperator", 
  "GreaterOperator", "LesserOperator", "EQUAL", "BooleanLiteral", "TRUE", 
  "FALSE", "IntegerLiteral", "RealLiteral", "Identifier", "LINE_TERMINATOR", 
  "WHITESPACE", "COMMENT", "LINE_COMMENT"
};

dfa::Vocabulary StlParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> StlParser::_tokenNames;

StlParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x48, 0xf2, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x5, 0x3, 0x2f, 0xa, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x33, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x36, 
    0xb, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x43, 0xa, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x5, 0x9, 0x50, 0xa, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x55, 0xa, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x5, 0xb, 0x61, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x6f, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 
    0xf, 0x73, 0xa, 0xf, 0x5, 0xf, 0x75, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x7e, 
    0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 
    0x12, 0x92, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x97, 
    0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 
    0xa4, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xc1, 0xa, 0x12, 0x3, 0x12, 0x7, 
    0x12, 0xc4, 0xa, 0x12, 0xc, 0x12, 0xe, 0x12, 0xc7, 0xb, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x5, 0x13, 0xd1, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xdf, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 
    0xe2, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0xea, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x5, 0x15, 0xf0, 0xa, 0x15, 0x3, 0x15, 0x2, 0x4, 0x22, 0x24, 
    0x16, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2, 0x5, 0x4, 0x2, 
    0x1f, 0x22, 0x44, 0x44, 0x3, 0x2, 0x1a, 0x1b, 0x3, 0x2, 0x13, 0x17, 
    0x2, 0x109, 0x2, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x4, 0x2e, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0x39, 0x3, 0x2, 0x2, 0x2, 0x8, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0x42, 0x3, 0x2, 0x2, 0x2, 0xc, 0x44, 0x3, 0x2, 0x2, 0x2, 0xe, 0x47, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x12, 0x56, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x60, 0x3, 0x2, 0x2, 0x2, 0x16, 0x62, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x64, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x66, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x74, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x76, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x22, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0xd0, 0x3, 0x2, 0x2, 0x2, 0x26, 0xe9, 0x3, 0x2, 0x2, 0x2, 0x28, 0xef, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 0x4, 0x3, 0x2, 0x2b, 0x2c, 0x7, 
    0x2, 0x2, 0x3, 0x2c, 0x3, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2f, 0x5, 0x6, 
    0x4, 0x2, 0x2e, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 
    0x2, 0x2f, 0x34, 0x3, 0x2, 0x2, 0x2, 0x30, 0x33, 0x5, 0xa, 0x6, 0x2, 
    0x31, 0x33, 0x5, 0xc, 0x7, 0x2, 0x32, 0x30, 0x3, 0x2, 0x2, 0x2, 0x32, 
    0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 0x2, 0x2, 0x34, 0x32, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 0x37, 0x3, 
    0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x5, 0x8, 
    0x5, 0x2, 0x38, 0x5, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x25, 0x2, 
    0x2, 0x3a, 0x3b, 0x7, 0x44, 0x2, 0x2, 0x3b, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x3d, 0x7, 0x44, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x3e, 0x2, 0x2, 0x3e, 
    0x3f, 0x5, 0x20, 0x11, 0x2, 0x3f, 0x9, 0x3, 0x2, 0x2, 0x2, 0x40, 0x43, 
    0x5, 0x10, 0x9, 0x2, 0x41, 0x43, 0x5, 0x12, 0xa, 0x2, 0x42, 0x40, 0x3, 
    0x2, 0x2, 0x2, 0x42, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0xb, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x45, 0x7, 0x11, 0x2, 0x2, 0x45, 0x46, 0x5, 0xe, 0x8, 
    0x2, 0x46, 0xd, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x7, 0x18, 0x2, 0x2, 
    0x48, 0x49, 0x7, 0x7, 0x2, 0x2, 0x49, 0x4a, 0x7, 0x44, 0x2, 0x2, 0x4a, 
    0x4b, 0x7, 0xf, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0x44, 0x2, 0x2, 0x4c, 0x4d, 
    0x7, 0x8, 0x2, 0x2, 0x4d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x50, 0x5, 
    0x18, 0xd, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0x3, 0x2, 
    0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x5, 0x16, 0xc, 
    0x2, 0x52, 0x54, 0x7, 0x44, 0x2, 0x2, 0x53, 0x55, 0x5, 0x14, 0xb, 0x2, 
    0x54, 0x53, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x3, 0x2, 0x2, 0x2, 0x55, 
    0x11, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x7, 0x1d, 0x2, 0x2, 0x57, 0x58, 
    0x5, 0x16, 0xc, 0x2, 0x58, 0x59, 0x7, 0x44, 0x2, 0x2, 0x59, 0x5a, 0x7, 
    0x3e, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0x28, 0x15, 0x2, 0x5b, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x5c, 0x5d, 0x7, 0x3e, 0x2, 0x2, 0x5d, 0x61, 0x5, 0x28, 0x15, 
    0x2, 0x5e, 0x5f, 0x7, 0x3e, 0x2, 0x2, 0x5f, 0x61, 0x5, 0x22, 0x12, 0x2, 
    0x60, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x61, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x9, 0x2, 0x2, 0x2, 0x63, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x9, 0x3, 0x2, 0x2, 0x65, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 0xb, 0x2, 0x2, 0x67, 0x68, 0x5, 0x1c, 
    0xf, 0x2, 0x68, 0x69, 0x7, 0xe, 0x2, 0x2, 0x69, 0x6a, 0x5, 0x1c, 0xf, 
    0x2, 0x6a, 0x6b, 0x7, 0xc, 0x2, 0x2, 0x6b, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x6e, 0x5, 0x28, 0x15, 0x2, 0x6d, 0x6f, 0x5, 0x1e, 0x10, 0x2, 
    0x6e, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0x75, 0x3, 0x2, 0x2, 0x2, 0x70, 0x72, 0x7, 0x44, 0x2, 0x2, 0x71, 0x73, 
    0x5, 0x1e, 0x10, 0x2, 0x72, 0x71, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 
    0x2, 0x2, 0x2, 0x73, 0x75, 0x3, 0x2, 0x2, 0x2, 0x74, 0x6c, 0x3, 0x2, 
    0x2, 0x2, 0x74, 0x70, 0x3, 0x2, 0x2, 0x2, 0x75, 0x1d, 0x3, 0x2, 0x2, 
    0x2, 0x76, 0x77, 0x9, 0x4, 0x2, 0x2, 0x77, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x78, 0x79, 0x7, 0x2f, 0x2, 0x2, 0x79, 0x7e, 0x5, 0x22, 0x12, 0x2, 0x7a, 
    0x7b, 0x7, 0x30, 0x2, 0x2, 0x7b, 0x7e, 0x5, 0x22, 0x12, 0x2, 0x7c, 0x7e, 
    0x5, 0x22, 0x12, 0x2, 0x7d, 0x78, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7a, 0x3, 
    0x2, 0x2, 0x2, 0x7d, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x7f, 0x80, 0x8, 0x12, 0x1, 0x2, 0x80, 0xa4, 0x5, 0x24, 0x13, 
    0x2, 0x81, 0x82, 0x7, 0x7, 0x2, 0x2, 0x82, 0x83, 0x5, 0x22, 0x12, 0x2, 
    0x83, 0x84, 0x7, 0x8, 0x2, 0x2, 0x84, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x85, 
    0x86, 0x7, 0x27, 0x2, 0x2, 0x86, 0xa4, 0x5, 0x22, 0x12, 0x10, 0x87, 
    0x88, 0x7, 0x2f, 0x2, 0x2, 0x88, 0x89, 0x5, 0x1a, 0xe, 0x2, 0x89, 0x8a, 
    0x5, 0x22, 0x12, 0xa, 0x8a, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x7, 
    0x30, 0x2, 0x2, 0x8c, 0x8d, 0x5, 0x1a, 0xe, 0x2, 0x8d, 0x8e, 0x5, 0x22, 
    0x12, 0x9, 0x8e, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x8f, 0x91, 0x7, 0x32, 0x2, 
    0x2, 0x90, 0x92, 0x5, 0x1a, 0xe, 0x2, 0x91, 0x90, 0x3, 0x2, 0x2, 0x2, 
    0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 
    0xa4, 0x5, 0x22, 0x12, 0x7, 0x94, 0x96, 0x7, 0x33, 0x2, 0x2, 0x95, 0x97, 
    0x5, 0x1a, 0xe, 0x2, 0x96, 0x95, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 0x3, 
    0x2, 0x2, 0x2, 0x97, 0x98, 0x3, 0x2, 0x2, 0x2, 0x98, 0xa4, 0x5, 0x22, 
    0x12, 0x6, 0x99, 0x9a, 0x7, 0x2d, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x7, 0x2, 
    0x2, 0x9b, 0x9c, 0x5, 0x22, 0x12, 0x2, 0x9c, 0x9d, 0x7, 0x8, 0x2, 0x2, 
    0x9d, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x2e, 0x2, 0x2, 0x9f, 
    0xa0, 0x7, 0x7, 0x2, 0x2, 0xa0, 0xa1, 0x5, 0x22, 0x12, 0x2, 0xa1, 0xa2, 
    0x7, 0x8, 0x2, 0x2, 0xa2, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa3, 0x7f, 0x3, 
    0x2, 0x2, 0x2, 0xa3, 0x81, 0x3, 0x2, 0x2, 0x2, 0xa3, 0x85, 0x3, 0x2, 
    0x2, 0x2, 0xa3, 0x87, 0x3, 0x2, 0x2, 0x2, 0xa3, 0x8b, 0x3, 0x2, 0x2, 
    0x2, 0xa3, 0x8f, 0x3, 0x2, 0x2, 0x2, 0xa3, 0x94, 0x3, 0x2, 0x2, 0x2, 
    0xa3, 0x99, 0x3, 0x2, 0x2, 0x2, 0xa3, 0x9e, 0x3, 0x2, 0x2, 0x2, 0xa4, 
    0xc5, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0xc, 0x12, 0x2, 0x2, 0xa6, 0xa7, 
    0x5, 0x26, 0x14, 0x2, 0xa7, 0xa8, 0x5, 0x22, 0x12, 0x13, 0xa8, 0xc4, 
    0x3, 0x2, 0x2, 0x2, 0xa9, 0xaa, 0xc, 0xf, 0x2, 0x2, 0xaa, 0xab, 0x7, 
    0x28, 0x2, 0x2, 0xab, 0xc4, 0x5, 0x22, 0x12, 0x10, 0xac, 0xad, 0xc, 
    0xe, 0x2, 0x2, 0xad, 0xae, 0x7, 0x29, 0x2, 0x2, 0xae, 0xc4, 0x5, 0x22, 
    0x12, 0xf, 0xaf, 0xb0, 0xc, 0xd, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x2b, 0x2, 
    0x2, 0xb1, 0xc4, 0x5, 0x22, 0x12, 0xe, 0xb2, 0xb3, 0xc, 0xc, 0x2, 0x2, 
    0xb3, 0xb4, 0x7, 0x2a, 0x2, 0x2, 0xb4, 0xc4, 0x5, 0x22, 0x12, 0xd, 0xb5, 
    0xb6, 0xc, 0xb, 0x2, 0x2, 0xb6, 0xb7, 0x7, 0x2c, 0x2, 0x2, 0xb7, 0xc4, 
    0x5, 0x22, 0x12, 0xc, 0xb8, 0xb9, 0xc, 0x8, 0x2, 0x2, 0xb9, 0xba, 0x7, 
    0x31, 0x2, 0x2, 0xba, 0xbb, 0x5, 0x1a, 0xe, 0x2, 0xbb, 0xbc, 0x5, 0x22, 
    0x12, 0x9, 0xbc, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0xc, 0x5, 0x2, 
    0x2, 0xbe, 0xc0, 0x7, 0x34, 0x2, 0x2, 0xbf, 0xc1, 0x5, 0x1a, 0xe, 0x2, 
    0xc0, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc1, 
    0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc4, 0x5, 0x22, 0x12, 0x6, 0xc3, 0xa5, 
    0x3, 0x2, 0x2, 0x2, 0xc3, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xac, 0x3, 
    0x2, 0x2, 0x2, 0xc3, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xb2, 0x3, 0x2, 
    0x2, 0x2, 0xc3, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xb8, 0x3, 0x2, 0x2, 
    0x2, 0xc3, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc7, 0x3, 0x2, 0x2, 0x2, 
    0xc5, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 
    0x23, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc5, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xc9, 
    0x8, 0x13, 0x1, 0x2, 0xc9, 0xd1, 0x7, 0x44, 0x2, 0x2, 0xca, 0xd1, 0x5, 
    0x28, 0x15, 0x2, 0xcb, 0xcc, 0x7, 0x12, 0x2, 0x2, 0xcc, 0xcd, 0x7, 0x7, 
    0x2, 0x2, 0xcd, 0xce, 0x5, 0x24, 0x13, 0x2, 0xce, 0xcf, 0x7, 0x8, 0x2, 
    0x2, 0xcf, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xc8, 0x3, 0x2, 0x2, 0x2, 
    0xd0, 0xca, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xd1, 
    0xe0, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0xc, 0x7, 0x2, 0x2, 0xd3, 0xd4, 
    0x7, 0x4, 0x2, 0x2, 0xd4, 0xdf, 0x5, 0x24, 0x13, 0x8, 0xd5, 0xd6, 0xc, 
    0x6, 0x2, 0x2, 0xd6, 0xd7, 0x7, 0x3, 0x2, 0x2, 0xd7, 0xdf, 0x5, 0x24, 
    0x13, 0x7, 0xd8, 0xd9, 0xc, 0x5, 0x2, 0x2, 0xd9, 0xda, 0x7, 0x5, 0x2, 
    0x2, 0xda, 0xdf, 0x5, 0x24, 0x13, 0x6, 0xdb, 0xdc, 0xc, 0x4, 0x2, 0x2, 
    0xdc, 0xdd, 0x7, 0x6, 0x2, 0x2, 0xdd, 0xdf, 0x5, 0x24, 0x13, 0x5, 0xde, 
    0xd2, 0x3, 0x2, 0x2, 0x2, 0xde, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xde, 0xd8, 
    0x3, 0x2, 0x2, 0x2, 0xde, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe2, 0x3, 
    0x2, 0x2, 0x2, 0xe0, 0xde, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0x3, 0x2, 
    0x2, 0x2, 0xe1, 0x25, 0x3, 0x2, 0x2, 0x2, 0xe2, 0xe0, 0x3, 0x2, 0x2, 
    0x2, 0xe3, 0xea, 0x7, 0x3b, 0x2, 0x2, 0xe4, 0xea, 0x7, 0x3a, 0x2, 0x2, 
    0xe5, 0xea, 0x7, 0x3d, 0x2, 0x2, 0xe6, 0xea, 0x7, 0x3c, 0x2, 0x2, 0xe7, 
    0xea, 0x7, 0x38, 0x2, 0x2, 0xe8, 0xea, 0x7, 0x39, 0x2, 0x2, 0xe9, 0xe3, 
    0x3, 0x2, 0x2, 0x2, 0xe9, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xe5, 0x3, 
    0x2, 0x2, 0x2, 0xe9, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xe7, 0x3, 0x2, 
    0x2, 0x2, 0xe9, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xea, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0xeb, 0xf0, 0x7, 0x42, 0x2, 0x2, 0xec, 0xf0, 0x7, 0x43, 0x2, 0x2, 
    0xed, 0xee, 0x7, 0x3, 0x2, 0x2, 0xee, 0xf0, 0x5, 0x28, 0x15, 0x2, 0xef, 
    0xeb, 0x3, 0x2, 0x2, 0x2, 0xef, 0xec, 0x3, 0x2, 0x2, 0x2, 0xef, 0xed, 
    0x3, 0x2, 0x2, 0x2, 0xf0, 0x29, 0x3, 0x2, 0x2, 0x2, 0x18, 0x2e, 0x32, 
    0x34, 0x42, 0x4f, 0x54, 0x60, 0x6e, 0x72, 0x74, 0x7d, 0x91, 0x96, 0xa3, 
    0xc0, 0xc3, 0xc5, 0xd0, 0xde, 0xe0, 0xe9, 0xef, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

StlParser::Initializer StlParser::_init;
