
// Generated from StlParser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "StlParser.h"


namespace grammar {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by StlParser.
 */
class  StlParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by StlParser.
   */
    virtual antlrcpp::Any visitStlfile(StlParser::StlfileContext *context) = 0;

    virtual antlrcpp::Any visitStlSpecification(StlParser::StlSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitSpecification(StlParser::SpecificationContext *context) = 0;

    virtual antlrcpp::Any visitAssertion(StlParser::AssertionContext *context) = 0;

    virtual antlrcpp::Any visitDeclVariable(StlParser::DeclVariableContext *context) = 0;

    virtual antlrcpp::Any visitDeclConstant(StlParser::DeclConstantContext *context) = 0;

    virtual antlrcpp::Any visitAnnotation(StlParser::AnnotationContext *context) = 0;

    virtual antlrcpp::Any visitRosTopic(StlParser::RosTopicContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(StlParser::VariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitConstantDeclaration(StlParser::ConstantDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitAsgnLiteral(StlParser::AsgnLiteralContext *context) = 0;

    virtual antlrcpp::Any visitAsgnExpr(StlParser::AsgnExprContext *context) = 0;

    virtual antlrcpp::Any visitDomainType(StlParser::DomainTypeContext *context) = 0;

    virtual antlrcpp::Any visitIoType(StlParser::IoTypeContext *context) = 0;

    virtual antlrcpp::Any visitInterval(StlParser::IntervalContext *context) = 0;

    virtual antlrcpp::Any visitIntervalTimeLiteral(StlParser::IntervalTimeLiteralContext *context) = 0;

    virtual antlrcpp::Any visitConstantTimeLiteral(StlParser::ConstantTimeLiteralContext *context) = 0;

    virtual antlrcpp::Any visitUnit(StlParser::UnitContext *context) = 0;

    virtual antlrcpp::Any visitExprUntimedAlwaysExpr(StlParser::ExprUntimedAlwaysExprContext *context) = 0;

    virtual antlrcpp::Any visitExprUntimedEvExpr(StlParser::ExprUntimedEvExprContext *context) = 0;

    virtual antlrcpp::Any visitExpr(StlParser::ExprContext *context) = 0;

    virtual antlrcpp::Any visitExprParen(StlParser::ExprParenContext *context) = 0;

    virtual antlrcpp::Any visitExprAndExpr(StlParser::ExprAndExprContext *context) = 0;

    virtual antlrcpp::Any visitExpreOnceExpr(StlParser::ExpreOnceExprContext *context) = 0;

    virtual antlrcpp::Any visitExprAlwaysExpr(StlParser::ExprAlwaysExprContext *context) = 0;

    virtual antlrcpp::Any visitExprImpliesExpr(StlParser::ExprImpliesExprContext *context) = 0;

    virtual antlrcpp::Any visitExprXorExpr(StlParser::ExprXorExprContext *context) = 0;

    virtual antlrcpp::Any visitExprSinceExpr(StlParser::ExprSinceExprContext *context) = 0;

    virtual antlrcpp::Any visitExprNot(StlParser::ExprNotContext *context) = 0;

    virtual antlrcpp::Any visitExprOrExpr(StlParser::ExprOrExprContext *context) = 0;

    virtual antlrcpp::Any visitExprIffExpr(StlParser::ExprIffExprContext *context) = 0;

    virtual antlrcpp::Any visitExprFall(StlParser::ExprFallContext *context) = 0;

    virtual antlrcpp::Any visitExprRise(StlParser::ExprRiseContext *context) = 0;

    virtual antlrcpp::Any visitExprHistExpr(StlParser::ExprHistExprContext *context) = 0;

    virtual antlrcpp::Any visitExprReal(StlParser::ExprRealContext *context) = 0;

    virtual antlrcpp::Any visitExprUntilExpr(StlParser::ExprUntilExprContext *context) = 0;

    virtual antlrcpp::Any visitExprEvExpr(StlParser::ExprEvExprContext *context) = 0;

    virtual antlrcpp::Any visitIdCompInt(StlParser::IdCompIntContext *context) = 0;

    virtual antlrcpp::Any visitExprSubtraction(StlParser::ExprSubtractionContext *context) = 0;

    virtual antlrcpp::Any visitExprDivision(StlParser::ExprDivisionContext *context) = 0;

    virtual antlrcpp::Any visitExprMultiplication(StlParser::ExprMultiplicationContext *context) = 0;

    virtual antlrcpp::Any visitExprLiteral(StlParser::ExprLiteralContext *context) = 0;

    virtual antlrcpp::Any visitExprId(StlParser::ExprIdContext *context) = 0;

    virtual antlrcpp::Any visitExprAbs(StlParser::ExprAbsContext *context) = 0;

    virtual antlrcpp::Any visitExprAddition(StlParser::ExprAdditionContext *context) = 0;

    virtual antlrcpp::Any visitCmpOpLs(StlParser::CmpOpLsContext *context) = 0;

    virtual antlrcpp::Any visitCmpOpGte(StlParser::CmpOpGteContext *context) = 0;

    virtual antlrcpp::Any visitCmpOpLse(StlParser::CmpOpLseContext *context) = 0;

    virtual antlrcpp::Any visitCmpOpGt(StlParser::CmpOpGtContext *context) = 0;

    virtual antlrcpp::Any visitCmpOpEq(StlParser::CmpOpEqContext *context) = 0;

    virtual antlrcpp::Any visitComOpNeq(StlParser::ComOpNeqContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(StlParser::LiteralContext *context) = 0;


};

}  // namespace grammar
