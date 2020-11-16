
// Generated from StlParser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "StlParserVisitor.h"


namespace grammar {

/**
 * This class provides an empty implementation of StlParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  StlParserBaseVisitor : public StlParserVisitor {
public:

  virtual antlrcpp::Any visitStlfile(StlParser::StlfileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStlSpecification(StlParser::StlSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSpecification(StlParser::SpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssertion(StlParser::AssertionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclVariable(StlParser::DeclVariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclConstant(StlParser::DeclConstantContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAnnotation(StlParser::AnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRosTopic(StlParser::RosTopicContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableDeclaration(StlParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantDeclaration(StlParser::ConstantDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAsgnLiteral(StlParser::AsgnLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAsgnExpr(StlParser::AsgnExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDomainType(StlParser::DomainTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIoType(StlParser::IoTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInterval(StlParser::IntervalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIntervalTimeLiteral(StlParser::IntervalTimeLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantTimeLiteral(StlParser::ConstantTimeLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnit(StlParser::UnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprUntimedAlwaysExpr(StlParser::ExprUntimedAlwaysExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprUntimedEvExpr(StlParser::ExprUntimedEvExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpr(StlParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprParen(StlParser::ExprParenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprAndExpr(StlParser::ExprAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpreOnceExpr(StlParser::ExpreOnceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprAlwaysExpr(StlParser::ExprAlwaysExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprImpliesExpr(StlParser::ExprImpliesExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprXorExpr(StlParser::ExprXorExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprSinceExpr(StlParser::ExprSinceExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprNot(StlParser::ExprNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprOrExpr(StlParser::ExprOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprIffExpr(StlParser::ExprIffExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprFall(StlParser::ExprFallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprRise(StlParser::ExprRiseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprHistExpr(StlParser::ExprHistExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprReal(StlParser::ExprRealContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprUntilExpr(StlParser::ExprUntilExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprEvExpr(StlParser::ExprEvExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdCompInt(StlParser::IdCompIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprSubtraction(StlParser::ExprSubtractionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprDivision(StlParser::ExprDivisionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprMultiplication(StlParser::ExprMultiplicationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprLiteral(StlParser::ExprLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprId(StlParser::ExprIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprAbs(StlParser::ExprAbsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExprAddition(StlParser::ExprAdditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpOpLs(StlParser::CmpOpLsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpOpGte(StlParser::CmpOpGteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpOpLse(StlParser::CmpOpLseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpOpGt(StlParser::CmpOpGtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCmpOpEq(StlParser::CmpOpEqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComOpNeq(StlParser::ComOpNeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral(StlParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace grammar
