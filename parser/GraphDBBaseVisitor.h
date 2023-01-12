
// Generated from GraphDB.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "GraphDBVisitor.h"


/**
 * This class provides an empty implementation of GraphDBVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  GraphDBBaseVisitor : public GraphDBVisitor {
public:

  virtual antlrcpp::Any visitStatement(GraphDBParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDmlStatement(GraphDBParser::DmlStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInsertStat(GraphDBParser::InsertStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRemoveStat(GraphDBParser::RemoveStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInsertGsetStat(GraphDBParser::InsertGsetStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInsertGStat(GraphDBParser::InsertGStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphNameItem(GraphDBParser::GraphNameItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphNameList(GraphDBParser::GraphNameListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRemoveGsetStat(GraphDBParser::RemoveGsetStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRemoveGStat(GraphDBParser::RemoveGStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdateStat(GraphDBParser::UpdateStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNameGraph(GraphDBParser::NameGraphContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraph(GraphDBParser::GraphContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphItem(GraphDBParser::GraphItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphList(GraphDBParser::GraphListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphset(GraphDBParser::GraphsetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVertexInfo(GraphDBParser::VertexInfoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeInfo(GraphDBParser::EdgeInfoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeList(GraphDBParser::EdgeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdge(GraphDBParser::EdgeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeInfo(GraphDBParser::AttributeInfoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNodeAttributeList(GraphDBParser::NodeAttributeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeAttributeList(GraphDBParser::EdgeAttributeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQueryStat(GraphDBParser::QueryStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMultipleOperator(GraphDBParser::MultipleOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProjectCondition(GraphDBParser::ProjectConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFromCondition(GraphDBParser::FromConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAlignConditionList(GraphDBParser::AlignConditionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAlignCondition(GraphDBParser::AlignConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFilenamelist(GraphDBParser::FilenamelistContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhereCondition(GraphDBParser::WhereConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMapCondition(GraphDBParser::MapConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReduceWord(GraphDBParser::ReduceWordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMaximalWord(GraphDBParser::MaximalWordContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOperationStatement(GraphDBParser::OperationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOperatorGSet(GraphDBParser::OperatorGSetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaNameItem(GraphDBParser::SchemaNameItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaNameList(GraphDBParser::SchemaNameListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProductStatement(GraphDBParser::ProductStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJoinStatement(GraphDBParser::JoinStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValue(GraphDBParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEntId(GraphDBParser::EntIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVidList(GraphDBParser::VidListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGidList(GraphDBParser::GidListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLidList(GraphDBParser::LidListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVidTuple(GraphDBParser::VidTupleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVidTupleList(GraphDBParser::VidTupleListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttrEqItem(GraphDBParser::AttrEqItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttrEqItemList(GraphDBParser::AttrEqItemListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeNameList(GraphDBParser::AttributeNameListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGT(GraphDBParser::GTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLT(GraphDBParser::LTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGTE(GraphDBParser::GTEContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLTE(GraphDBParser::LTEContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEQ(GraphDBParser::EQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNEQ(GraphDBParser::NEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCalculateOperator(GraphDBParser::CalculateOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicFlagBi(GraphDBParser::LogicFlagBiContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicFlagNot(GraphDBParser::LogicFlagNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFirstOrderStat(GraphDBParser::FirstOrderStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFirstOrderUnit(GraphDBParser::FirstOrderUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExistStat(GraphDBParser::ExistStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForeachStat(GraphDBParser::ForeachStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareStat(GraphDBParser::CompareStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareUnit(GraphDBParser::CompareUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompareValStat(GraphDBParser::CompareValStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncStat(GraphDBParser::FuncStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFuncName(GraphDBParser::FuncNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObject(GraphDBParser::ObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObjectList(GraphDBParser::ObjectListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarList(GraphDBParser::VarListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBracketLeft(GraphDBParser::BracketLeftContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBracketRight(GraphDBParser::BracketRightContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDdlStatement(GraphDBParser::DdlStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreateSchemaStat(GraphDBParser::CreateSchemaStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaStatement(GraphDBParser::SchemaStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaNodeList(GraphDBParser::SchemaNodeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaEdgeList(GraphDBParser::SchemaEdgeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaNode(GraphDBParser::SchemaNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaAttrList(GraphDBParser::SchemaAttrListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaEdge(GraphDBParser::SchemaEdgeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEdgeLinkageList(GraphDBParser::EdgeLinkageListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLabelName(GraphDBParser::LabelNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeName(GraphDBParser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaItem(GraphDBParser::SchemaItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreateGsetStat(GraphDBParser::CreateGsetStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreateGStat(GraphDBParser::CreateGStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreateGFileStat(GraphDBParser::CreateGFileStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreateGForStat(GraphDBParser::CreateGForStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoadGsetStat(GraphDBParser::LoadGsetStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoadGStat(GraphDBParser::LoadGStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDropStat(GraphDBParser::DropStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDropGsetStat(GraphDBParser::DropGsetStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDropGStat(GraphDBParser::DropGStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDropSchemaStat(GraphDBParser::DropSchemaStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaTypeList(GraphDBParser::SchemaTypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttrItem(GraphDBParser::AttrItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDataType(GraphDBParser::DataTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeName(GraphDBParser::AttributeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGsid(GraphDBParser::GsidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGid(GraphDBParser::GidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVid(GraphDBParser::VidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEid(GraphDBParser::EidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLid(GraphDBParser::LidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFilename(GraphDBParser::FilenameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSchemaid(GraphDBParser::SchemaidContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariableName(GraphDBParser::VariableNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIndexInt(GraphDBParser::IndexIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParaItem(GraphDBParser::ParaItemContext *ctx) override {
    return visitChildren(ctx);
  }


};

