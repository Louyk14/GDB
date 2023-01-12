
// Generated from GraphDB.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "GraphDBParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by GraphDBParser.
 */
class  GraphDBVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by GraphDBParser.
   */
    virtual antlrcpp::Any visitStatement(GraphDBParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitDmlStatement(GraphDBParser::DmlStatementContext *context) = 0;

    virtual antlrcpp::Any visitInsertStat(GraphDBParser::InsertStatContext *context) = 0;

    virtual antlrcpp::Any visitRemoveStat(GraphDBParser::RemoveStatContext *context) = 0;

    virtual antlrcpp::Any visitInsertGsetStat(GraphDBParser::InsertGsetStatContext *context) = 0;

    virtual antlrcpp::Any visitInsertGStat(GraphDBParser::InsertGStatContext *context) = 0;

    virtual antlrcpp::Any visitGraphNameItem(GraphDBParser::GraphNameItemContext *context) = 0;

    virtual antlrcpp::Any visitGraphNameList(GraphDBParser::GraphNameListContext *context) = 0;

    virtual antlrcpp::Any visitRemoveGsetStat(GraphDBParser::RemoveGsetStatContext *context) = 0;

    virtual antlrcpp::Any visitRemoveGStat(GraphDBParser::RemoveGStatContext *context) = 0;

    virtual antlrcpp::Any visitUpdateStat(GraphDBParser::UpdateStatContext *context) = 0;

    virtual antlrcpp::Any visitNameGraph(GraphDBParser::NameGraphContext *context) = 0;

    virtual antlrcpp::Any visitGraph(GraphDBParser::GraphContext *context) = 0;

    virtual antlrcpp::Any visitGraphItem(GraphDBParser::GraphItemContext *context) = 0;

    virtual antlrcpp::Any visitGraphList(GraphDBParser::GraphListContext *context) = 0;

    virtual antlrcpp::Any visitGraphset(GraphDBParser::GraphsetContext *context) = 0;

    virtual antlrcpp::Any visitVertexInfo(GraphDBParser::VertexInfoContext *context) = 0;

    virtual antlrcpp::Any visitEdgeInfo(GraphDBParser::EdgeInfoContext *context) = 0;

    virtual antlrcpp::Any visitEdgeList(GraphDBParser::EdgeListContext *context) = 0;

    virtual antlrcpp::Any visitEdge(GraphDBParser::EdgeContext *context) = 0;

    virtual antlrcpp::Any visitAttributeInfo(GraphDBParser::AttributeInfoContext *context) = 0;

    virtual antlrcpp::Any visitNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext *context) = 0;

    virtual antlrcpp::Any visitNodeAttributeList(GraphDBParser::NodeAttributeListContext *context) = 0;

    virtual antlrcpp::Any visitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *context) = 0;

    virtual antlrcpp::Any visitEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext *context) = 0;

    virtual antlrcpp::Any visitEdgeAttributeList(GraphDBParser::EdgeAttributeListContext *context) = 0;

    virtual antlrcpp::Any visitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *context) = 0;

    virtual antlrcpp::Any visitQueryStat(GraphDBParser::QueryStatContext *context) = 0;

    virtual antlrcpp::Any visitMultipleOperator(GraphDBParser::MultipleOperatorContext *context) = 0;

    virtual antlrcpp::Any visitProjectCondition(GraphDBParser::ProjectConditionContext *context) = 0;

    virtual antlrcpp::Any visitFromCondition(GraphDBParser::FromConditionContext *context) = 0;

    virtual antlrcpp::Any visitAlignConditionList(GraphDBParser::AlignConditionListContext *context) = 0;

    virtual antlrcpp::Any visitAlignCondition(GraphDBParser::AlignConditionContext *context) = 0;

    virtual antlrcpp::Any visitFilenamelist(GraphDBParser::FilenamelistContext *context) = 0;

    virtual antlrcpp::Any visitWhereCondition(GraphDBParser::WhereConditionContext *context) = 0;

    virtual antlrcpp::Any visitMapCondition(GraphDBParser::MapConditionContext *context) = 0;

    virtual antlrcpp::Any visitReduceWord(GraphDBParser::ReduceWordContext *context) = 0;

    virtual antlrcpp::Any visitMaximalWord(GraphDBParser::MaximalWordContext *context) = 0;

    virtual antlrcpp::Any visitOperationStatement(GraphDBParser::OperationStatementContext *context) = 0;

    virtual antlrcpp::Any visitOperatorGSet(GraphDBParser::OperatorGSetContext *context) = 0;

    virtual antlrcpp::Any visitSchemaNameItem(GraphDBParser::SchemaNameItemContext *context) = 0;

    virtual antlrcpp::Any visitSchemaNameList(GraphDBParser::SchemaNameListContext *context) = 0;

    virtual antlrcpp::Any visitProductStatement(GraphDBParser::ProductStatementContext *context) = 0;

    virtual antlrcpp::Any visitJoinStatement(GraphDBParser::JoinStatementContext *context) = 0;

    virtual antlrcpp::Any visitValue(GraphDBParser::ValueContext *context) = 0;

    virtual antlrcpp::Any visitEntId(GraphDBParser::EntIdContext *context) = 0;

    virtual antlrcpp::Any visitVidList(GraphDBParser::VidListContext *context) = 0;

    virtual antlrcpp::Any visitGidList(GraphDBParser::GidListContext *context) = 0;

    virtual antlrcpp::Any visitLidList(GraphDBParser::LidListContext *context) = 0;

    virtual antlrcpp::Any visitVidTuple(GraphDBParser::VidTupleContext *context) = 0;

    virtual antlrcpp::Any visitVidTupleList(GraphDBParser::VidTupleListContext *context) = 0;

    virtual antlrcpp::Any visitAttrEqItem(GraphDBParser::AttrEqItemContext *context) = 0;

    virtual antlrcpp::Any visitAttrEqItemList(GraphDBParser::AttrEqItemListContext *context) = 0;

    virtual antlrcpp::Any visitAttributeNameList(GraphDBParser::AttributeNameListContext *context) = 0;

    virtual antlrcpp::Any visitAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext *context) = 0;

    virtual antlrcpp::Any visitAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext *context) = 0;

    virtual antlrcpp::Any visitGT(GraphDBParser::GTContext *context) = 0;

    virtual antlrcpp::Any visitLT(GraphDBParser::LTContext *context) = 0;

    virtual antlrcpp::Any visitGTE(GraphDBParser::GTEContext *context) = 0;

    virtual antlrcpp::Any visitLTE(GraphDBParser::LTEContext *context) = 0;

    virtual antlrcpp::Any visitEQ(GraphDBParser::EQContext *context) = 0;

    virtual antlrcpp::Any visitNEQ(GraphDBParser::NEQContext *context) = 0;

    virtual antlrcpp::Any visitCalculateOperator(GraphDBParser::CalculateOperatorContext *context) = 0;

    virtual antlrcpp::Any visitLogicFlagBi(GraphDBParser::LogicFlagBiContext *context) = 0;

    virtual antlrcpp::Any visitLogicFlagNot(GraphDBParser::LogicFlagNotContext *context) = 0;

    virtual antlrcpp::Any visitFirstOrderStat(GraphDBParser::FirstOrderStatContext *context) = 0;

    virtual antlrcpp::Any visitFirstOrderUnit(GraphDBParser::FirstOrderUnitContext *context) = 0;

    virtual antlrcpp::Any visitExistStat(GraphDBParser::ExistStatContext *context) = 0;

    virtual antlrcpp::Any visitForeachStat(GraphDBParser::ForeachStatContext *context) = 0;

    virtual antlrcpp::Any visitCompareStat(GraphDBParser::CompareStatContext *context) = 0;

    virtual antlrcpp::Any visitCompareUnit(GraphDBParser::CompareUnitContext *context) = 0;

    virtual antlrcpp::Any visitCompareValStat(GraphDBParser::CompareValStatContext *context) = 0;

    virtual antlrcpp::Any visitFuncStat(GraphDBParser::FuncStatContext *context) = 0;

    virtual antlrcpp::Any visitFuncName(GraphDBParser::FuncNameContext *context) = 0;

    virtual antlrcpp::Any visitObject(GraphDBParser::ObjectContext *context) = 0;

    virtual antlrcpp::Any visitObjectList(GraphDBParser::ObjectListContext *context) = 0;

    virtual antlrcpp::Any visitVarList(GraphDBParser::VarListContext *context) = 0;

    virtual antlrcpp::Any visitBracketLeft(GraphDBParser::BracketLeftContext *context) = 0;

    virtual antlrcpp::Any visitBracketRight(GraphDBParser::BracketRightContext *context) = 0;

    virtual antlrcpp::Any visitDdlStatement(GraphDBParser::DdlStatementContext *context) = 0;

    virtual antlrcpp::Any visitCreateSchemaStat(GraphDBParser::CreateSchemaStatContext *context) = 0;

    virtual antlrcpp::Any visitSchemaStatement(GraphDBParser::SchemaStatementContext *context) = 0;

    virtual antlrcpp::Any visitSchemaNodeList(GraphDBParser::SchemaNodeListContext *context) = 0;

    virtual antlrcpp::Any visitSchemaEdgeList(GraphDBParser::SchemaEdgeListContext *context) = 0;

    virtual antlrcpp::Any visitSchemaNode(GraphDBParser::SchemaNodeContext *context) = 0;

    virtual antlrcpp::Any visitSchemaAttrList(GraphDBParser::SchemaAttrListContext *context) = 0;

    virtual antlrcpp::Any visitSchemaEdge(GraphDBParser::SchemaEdgeContext *context) = 0;

    virtual antlrcpp::Any visitEdgeLinkageList(GraphDBParser::EdgeLinkageListContext *context) = 0;

    virtual antlrcpp::Any visitLabelName(GraphDBParser::LabelNameContext *context) = 0;

    virtual antlrcpp::Any visitTypeName(GraphDBParser::TypeNameContext *context) = 0;

    virtual antlrcpp::Any visitSchemaItem(GraphDBParser::SchemaItemContext *context) = 0;

    virtual antlrcpp::Any visitCreateGsetStat(GraphDBParser::CreateGsetStatContext *context) = 0;

    virtual antlrcpp::Any visitCreateGStat(GraphDBParser::CreateGStatContext *context) = 0;

    virtual antlrcpp::Any visitCreateGFileStat(GraphDBParser::CreateGFileStatContext *context) = 0;

    virtual antlrcpp::Any visitCreateGForStat(GraphDBParser::CreateGForStatContext *context) = 0;

    virtual antlrcpp::Any visitLoadGsetStat(GraphDBParser::LoadGsetStatContext *context) = 0;

    virtual antlrcpp::Any visitLoadGStat(GraphDBParser::LoadGStatContext *context) = 0;

    virtual antlrcpp::Any visitDropStat(GraphDBParser::DropStatContext *context) = 0;

    virtual antlrcpp::Any visitDropGsetStat(GraphDBParser::DropGsetStatContext *context) = 0;

    virtual antlrcpp::Any visitDropGStat(GraphDBParser::DropGStatContext *context) = 0;

    virtual antlrcpp::Any visitDropSchemaStat(GraphDBParser::DropSchemaStatContext *context) = 0;

    virtual antlrcpp::Any visitSchemaTypeList(GraphDBParser::SchemaTypeListContext *context) = 0;

    virtual antlrcpp::Any visitSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext *context) = 0;

    virtual antlrcpp::Any visitAttrItem(GraphDBParser::AttrItemContext *context) = 0;

    virtual antlrcpp::Any visitDataType(GraphDBParser::DataTypeContext *context) = 0;

    virtual antlrcpp::Any visitAttributeName(GraphDBParser::AttributeNameContext *context) = 0;

    virtual antlrcpp::Any visitGsid(GraphDBParser::GsidContext *context) = 0;

    virtual antlrcpp::Any visitGid(GraphDBParser::GidContext *context) = 0;

    virtual antlrcpp::Any visitVid(GraphDBParser::VidContext *context) = 0;

    virtual antlrcpp::Any visitEid(GraphDBParser::EidContext *context) = 0;

    virtual antlrcpp::Any visitLid(GraphDBParser::LidContext *context) = 0;

    virtual antlrcpp::Any visitFilename(GraphDBParser::FilenameContext *context) = 0;

    virtual antlrcpp::Any visitSchemaid(GraphDBParser::SchemaidContext *context) = 0;

    virtual antlrcpp::Any visitVariableName(GraphDBParser::VariableNameContext *context) = 0;

    virtual antlrcpp::Any visitIndexInt(GraphDBParser::IndexIntContext *context) = 0;

    virtual antlrcpp::Any visitParaItem(GraphDBParser::ParaItemContext *context) = 0;


};

