
// Generated from GraphDB.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "GraphDBParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by GraphDBParser.
 */
class  GraphDBListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterStatement(GraphDBParser::StatementContext *ctx) = 0;
  virtual void exitStatement(GraphDBParser::StatementContext *ctx) = 0;

  virtual void enterDmlStatement(GraphDBParser::DmlStatementContext *ctx) = 0;
  virtual void exitDmlStatement(GraphDBParser::DmlStatementContext *ctx) = 0;

  virtual void enterInsertStat(GraphDBParser::InsertStatContext *ctx) = 0;
  virtual void exitInsertStat(GraphDBParser::InsertStatContext *ctx) = 0;

  virtual void enterRemoveStat(GraphDBParser::RemoveStatContext *ctx) = 0;
  virtual void exitRemoveStat(GraphDBParser::RemoveStatContext *ctx) = 0;

  virtual void enterInsertGsetStat(GraphDBParser::InsertGsetStatContext *ctx) = 0;
  virtual void exitInsertGsetStat(GraphDBParser::InsertGsetStatContext *ctx) = 0;

  virtual void enterInsertGStat(GraphDBParser::InsertGStatContext *ctx) = 0;
  virtual void exitInsertGStat(GraphDBParser::InsertGStatContext *ctx) = 0;

  virtual void enterGraphNameItem(GraphDBParser::GraphNameItemContext *ctx) = 0;
  virtual void exitGraphNameItem(GraphDBParser::GraphNameItemContext *ctx) = 0;

  virtual void enterGraphNameList(GraphDBParser::GraphNameListContext *ctx) = 0;
  virtual void exitGraphNameList(GraphDBParser::GraphNameListContext *ctx) = 0;

  virtual void enterRemoveGsetStat(GraphDBParser::RemoveGsetStatContext *ctx) = 0;
  virtual void exitRemoveGsetStat(GraphDBParser::RemoveGsetStatContext *ctx) = 0;

  virtual void enterRemoveGStat(GraphDBParser::RemoveGStatContext *ctx) = 0;
  virtual void exitRemoveGStat(GraphDBParser::RemoveGStatContext *ctx) = 0;

  virtual void enterUpdateStat(GraphDBParser::UpdateStatContext *ctx) = 0;
  virtual void exitUpdateStat(GraphDBParser::UpdateStatContext *ctx) = 0;

  virtual void enterNameGraph(GraphDBParser::NameGraphContext *ctx) = 0;
  virtual void exitNameGraph(GraphDBParser::NameGraphContext *ctx) = 0;

  virtual void enterGraph(GraphDBParser::GraphContext *ctx) = 0;
  virtual void exitGraph(GraphDBParser::GraphContext *ctx) = 0;

  virtual void enterGraphItem(GraphDBParser::GraphItemContext *ctx) = 0;
  virtual void exitGraphItem(GraphDBParser::GraphItemContext *ctx) = 0;

  virtual void enterGraphList(GraphDBParser::GraphListContext *ctx) = 0;
  virtual void exitGraphList(GraphDBParser::GraphListContext *ctx) = 0;

  virtual void enterGraphset(GraphDBParser::GraphsetContext *ctx) = 0;
  virtual void exitGraphset(GraphDBParser::GraphsetContext *ctx) = 0;

  virtual void enterVertexInfo(GraphDBParser::VertexInfoContext *ctx) = 0;
  virtual void exitVertexInfo(GraphDBParser::VertexInfoContext *ctx) = 0;

  virtual void enterEdgeInfo(GraphDBParser::EdgeInfoContext *ctx) = 0;
  virtual void exitEdgeInfo(GraphDBParser::EdgeInfoContext *ctx) = 0;

  virtual void enterEdgeList(GraphDBParser::EdgeListContext *ctx) = 0;
  virtual void exitEdgeList(GraphDBParser::EdgeListContext *ctx) = 0;

  virtual void enterEdge(GraphDBParser::EdgeContext *ctx) = 0;
  virtual void exitEdge(GraphDBParser::EdgeContext *ctx) = 0;

  virtual void enterAttributeInfo(GraphDBParser::AttributeInfoContext *ctx) = 0;
  virtual void exitAttributeInfo(GraphDBParser::AttributeInfoContext *ctx) = 0;

  virtual void enterNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext *ctx) = 0;
  virtual void exitNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext *ctx) = 0;

  virtual void enterNodeAttributeList(GraphDBParser::NodeAttributeListContext *ctx) = 0;
  virtual void exitNodeAttributeList(GraphDBParser::NodeAttributeListContext *ctx) = 0;

  virtual void enterNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *ctx) = 0;
  virtual void exitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *ctx) = 0;

  virtual void enterEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext *ctx) = 0;
  virtual void exitEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext *ctx) = 0;

  virtual void enterEdgeAttributeList(GraphDBParser::EdgeAttributeListContext *ctx) = 0;
  virtual void exitEdgeAttributeList(GraphDBParser::EdgeAttributeListContext *ctx) = 0;

  virtual void enterEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *ctx) = 0;
  virtual void exitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *ctx) = 0;

  virtual void enterQueryStat(GraphDBParser::QueryStatContext *ctx) = 0;
  virtual void exitQueryStat(GraphDBParser::QueryStatContext *ctx) = 0;

  virtual void enterMultipleOperator(GraphDBParser::MultipleOperatorContext *ctx) = 0;
  virtual void exitMultipleOperator(GraphDBParser::MultipleOperatorContext *ctx) = 0;

  virtual void enterProjectCondition(GraphDBParser::ProjectConditionContext *ctx) = 0;
  virtual void exitProjectCondition(GraphDBParser::ProjectConditionContext *ctx) = 0;

  virtual void enterFromCondition(GraphDBParser::FromConditionContext *ctx) = 0;
  virtual void exitFromCondition(GraphDBParser::FromConditionContext *ctx) = 0;

  virtual void enterAlignConditionList(GraphDBParser::AlignConditionListContext *ctx) = 0;
  virtual void exitAlignConditionList(GraphDBParser::AlignConditionListContext *ctx) = 0;

  virtual void enterAlignCondition(GraphDBParser::AlignConditionContext *ctx) = 0;
  virtual void exitAlignCondition(GraphDBParser::AlignConditionContext *ctx) = 0;

  virtual void enterFilenamelist(GraphDBParser::FilenamelistContext *ctx) = 0;
  virtual void exitFilenamelist(GraphDBParser::FilenamelistContext *ctx) = 0;

  virtual void enterWhereCondition(GraphDBParser::WhereConditionContext *ctx) = 0;
  virtual void exitWhereCondition(GraphDBParser::WhereConditionContext *ctx) = 0;

  virtual void enterMapCondition(GraphDBParser::MapConditionContext *ctx) = 0;
  virtual void exitMapCondition(GraphDBParser::MapConditionContext *ctx) = 0;

  virtual void enterReduceWord(GraphDBParser::ReduceWordContext *ctx) = 0;
  virtual void exitReduceWord(GraphDBParser::ReduceWordContext *ctx) = 0;

  virtual void enterMaximalWord(GraphDBParser::MaximalWordContext *ctx) = 0;
  virtual void exitMaximalWord(GraphDBParser::MaximalWordContext *ctx) = 0;

  virtual void enterOperationStatement(GraphDBParser::OperationStatementContext *ctx) = 0;
  virtual void exitOperationStatement(GraphDBParser::OperationStatementContext *ctx) = 0;

  virtual void enterOperatorGSet(GraphDBParser::OperatorGSetContext *ctx) = 0;
  virtual void exitOperatorGSet(GraphDBParser::OperatorGSetContext *ctx) = 0;

  virtual void enterSchemaNameItem(GraphDBParser::SchemaNameItemContext *ctx) = 0;
  virtual void exitSchemaNameItem(GraphDBParser::SchemaNameItemContext *ctx) = 0;

  virtual void enterSchemaNameList(GraphDBParser::SchemaNameListContext *ctx) = 0;
  virtual void exitSchemaNameList(GraphDBParser::SchemaNameListContext *ctx) = 0;

  virtual void enterProductStatement(GraphDBParser::ProductStatementContext *ctx) = 0;
  virtual void exitProductStatement(GraphDBParser::ProductStatementContext *ctx) = 0;

  virtual void enterJoinStatement(GraphDBParser::JoinStatementContext *ctx) = 0;
  virtual void exitJoinStatement(GraphDBParser::JoinStatementContext *ctx) = 0;

  virtual void enterValue(GraphDBParser::ValueContext *ctx) = 0;
  virtual void exitValue(GraphDBParser::ValueContext *ctx) = 0;

  virtual void enterEntId(GraphDBParser::EntIdContext *ctx) = 0;
  virtual void exitEntId(GraphDBParser::EntIdContext *ctx) = 0;

  virtual void enterVidList(GraphDBParser::VidListContext *ctx) = 0;
  virtual void exitVidList(GraphDBParser::VidListContext *ctx) = 0;

  virtual void enterGidList(GraphDBParser::GidListContext *ctx) = 0;
  virtual void exitGidList(GraphDBParser::GidListContext *ctx) = 0;

  virtual void enterLidList(GraphDBParser::LidListContext *ctx) = 0;
  virtual void exitLidList(GraphDBParser::LidListContext *ctx) = 0;

  virtual void enterVidTuple(GraphDBParser::VidTupleContext *ctx) = 0;
  virtual void exitVidTuple(GraphDBParser::VidTupleContext *ctx) = 0;

  virtual void enterVidTupleList(GraphDBParser::VidTupleListContext *ctx) = 0;
  virtual void exitVidTupleList(GraphDBParser::VidTupleListContext *ctx) = 0;

  virtual void enterAttrEqItem(GraphDBParser::AttrEqItemContext *ctx) = 0;
  virtual void exitAttrEqItem(GraphDBParser::AttrEqItemContext *ctx) = 0;

  virtual void enterAttrEqItemList(GraphDBParser::AttrEqItemListContext *ctx) = 0;
  virtual void exitAttrEqItemList(GraphDBParser::AttrEqItemListContext *ctx) = 0;

  virtual void enterAttributeNameList(GraphDBParser::AttributeNameListContext *ctx) = 0;
  virtual void exitAttributeNameList(GraphDBParser::AttributeNameListContext *ctx) = 0;

  virtual void enterAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext *ctx) = 0;
  virtual void exitAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext *ctx) = 0;

  virtual void enterAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext *ctx) = 0;
  virtual void exitAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext *ctx) = 0;

  virtual void enterGT(GraphDBParser::GTContext *ctx) = 0;
  virtual void exitGT(GraphDBParser::GTContext *ctx) = 0;

  virtual void enterLT(GraphDBParser::LTContext *ctx) = 0;
  virtual void exitLT(GraphDBParser::LTContext *ctx) = 0;

  virtual void enterGTE(GraphDBParser::GTEContext *ctx) = 0;
  virtual void exitGTE(GraphDBParser::GTEContext *ctx) = 0;

  virtual void enterLTE(GraphDBParser::LTEContext *ctx) = 0;
  virtual void exitLTE(GraphDBParser::LTEContext *ctx) = 0;

  virtual void enterEQ(GraphDBParser::EQContext *ctx) = 0;
  virtual void exitEQ(GraphDBParser::EQContext *ctx) = 0;

  virtual void enterNEQ(GraphDBParser::NEQContext *ctx) = 0;
  virtual void exitNEQ(GraphDBParser::NEQContext *ctx) = 0;

  virtual void enterCalculateOperator(GraphDBParser::CalculateOperatorContext *ctx) = 0;
  virtual void exitCalculateOperator(GraphDBParser::CalculateOperatorContext *ctx) = 0;

  virtual void enterLogicFlagBi(GraphDBParser::LogicFlagBiContext *ctx) = 0;
  virtual void exitLogicFlagBi(GraphDBParser::LogicFlagBiContext *ctx) = 0;

  virtual void enterLogicFlagNot(GraphDBParser::LogicFlagNotContext *ctx) = 0;
  virtual void exitLogicFlagNot(GraphDBParser::LogicFlagNotContext *ctx) = 0;

  virtual void enterFirstOrderStat(GraphDBParser::FirstOrderStatContext *ctx) = 0;
  virtual void exitFirstOrderStat(GraphDBParser::FirstOrderStatContext *ctx) = 0;

  virtual void enterFirstOrderUnit(GraphDBParser::FirstOrderUnitContext *ctx) = 0;
  virtual void exitFirstOrderUnit(GraphDBParser::FirstOrderUnitContext *ctx) = 0;

  virtual void enterExistStat(GraphDBParser::ExistStatContext *ctx) = 0;
  virtual void exitExistStat(GraphDBParser::ExistStatContext *ctx) = 0;

  virtual void enterForeachStat(GraphDBParser::ForeachStatContext *ctx) = 0;
  virtual void exitForeachStat(GraphDBParser::ForeachStatContext *ctx) = 0;

  virtual void enterCompareStat(GraphDBParser::CompareStatContext *ctx) = 0;
  virtual void exitCompareStat(GraphDBParser::CompareStatContext *ctx) = 0;

  virtual void enterCompareUnit(GraphDBParser::CompareUnitContext *ctx) = 0;
  virtual void exitCompareUnit(GraphDBParser::CompareUnitContext *ctx) = 0;

  virtual void enterCompareValStat(GraphDBParser::CompareValStatContext *ctx) = 0;
  virtual void exitCompareValStat(GraphDBParser::CompareValStatContext *ctx) = 0;

  virtual void enterFuncStat(GraphDBParser::FuncStatContext *ctx) = 0;
  virtual void exitFuncStat(GraphDBParser::FuncStatContext *ctx) = 0;

  virtual void enterFuncName(GraphDBParser::FuncNameContext *ctx) = 0;
  virtual void exitFuncName(GraphDBParser::FuncNameContext *ctx) = 0;

  virtual void enterObject(GraphDBParser::ObjectContext *ctx) = 0;
  virtual void exitObject(GraphDBParser::ObjectContext *ctx) = 0;

  virtual void enterObjectList(GraphDBParser::ObjectListContext *ctx) = 0;
  virtual void exitObjectList(GraphDBParser::ObjectListContext *ctx) = 0;

  virtual void enterVarList(GraphDBParser::VarListContext *ctx) = 0;
  virtual void exitVarList(GraphDBParser::VarListContext *ctx) = 0;

  virtual void enterBracketLeft(GraphDBParser::BracketLeftContext *ctx) = 0;
  virtual void exitBracketLeft(GraphDBParser::BracketLeftContext *ctx) = 0;

  virtual void enterBracketRight(GraphDBParser::BracketRightContext *ctx) = 0;
  virtual void exitBracketRight(GraphDBParser::BracketRightContext *ctx) = 0;

  virtual void enterDdlStatement(GraphDBParser::DdlStatementContext *ctx) = 0;
  virtual void exitDdlStatement(GraphDBParser::DdlStatementContext *ctx) = 0;

  virtual void enterCreateSchemaStat(GraphDBParser::CreateSchemaStatContext *ctx) = 0;
  virtual void exitCreateSchemaStat(GraphDBParser::CreateSchemaStatContext *ctx) = 0;

  virtual void enterSchemaStatement(GraphDBParser::SchemaStatementContext *ctx) = 0;
  virtual void exitSchemaStatement(GraphDBParser::SchemaStatementContext *ctx) = 0;

  virtual void enterSchemaNodeList(GraphDBParser::SchemaNodeListContext *ctx) = 0;
  virtual void exitSchemaNodeList(GraphDBParser::SchemaNodeListContext *ctx) = 0;

  virtual void enterSchemaEdgeList(GraphDBParser::SchemaEdgeListContext *ctx) = 0;
  virtual void exitSchemaEdgeList(GraphDBParser::SchemaEdgeListContext *ctx) = 0;

  virtual void enterSchemaNode(GraphDBParser::SchemaNodeContext *ctx) = 0;
  virtual void exitSchemaNode(GraphDBParser::SchemaNodeContext *ctx) = 0;

  virtual void enterSchemaAttrList(GraphDBParser::SchemaAttrListContext *ctx) = 0;
  virtual void exitSchemaAttrList(GraphDBParser::SchemaAttrListContext *ctx) = 0;

  virtual void enterSchemaEdge(GraphDBParser::SchemaEdgeContext *ctx) = 0;
  virtual void exitSchemaEdge(GraphDBParser::SchemaEdgeContext *ctx) = 0;

  virtual void enterEdgeLinkageList(GraphDBParser::EdgeLinkageListContext *ctx) = 0;
  virtual void exitEdgeLinkageList(GraphDBParser::EdgeLinkageListContext *ctx) = 0;

  virtual void enterLabelName(GraphDBParser::LabelNameContext *ctx) = 0;
  virtual void exitLabelName(GraphDBParser::LabelNameContext *ctx) = 0;

  virtual void enterTypeName(GraphDBParser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(GraphDBParser::TypeNameContext *ctx) = 0;

  virtual void enterSchemaItem(GraphDBParser::SchemaItemContext *ctx) = 0;
  virtual void exitSchemaItem(GraphDBParser::SchemaItemContext *ctx) = 0;

  virtual void enterCreateGsetStat(GraphDBParser::CreateGsetStatContext *ctx) = 0;
  virtual void exitCreateGsetStat(GraphDBParser::CreateGsetStatContext *ctx) = 0;

  virtual void enterCreateGStat(GraphDBParser::CreateGStatContext *ctx) = 0;
  virtual void exitCreateGStat(GraphDBParser::CreateGStatContext *ctx) = 0;

  virtual void enterCreateGFileStat(GraphDBParser::CreateGFileStatContext *ctx) = 0;
  virtual void exitCreateGFileStat(GraphDBParser::CreateGFileStatContext *ctx) = 0;

  virtual void enterCreateGForStat(GraphDBParser::CreateGForStatContext *ctx) = 0;
  virtual void exitCreateGForStat(GraphDBParser::CreateGForStatContext *ctx) = 0;

  virtual void enterLoadGsetStat(GraphDBParser::LoadGsetStatContext *ctx) = 0;
  virtual void exitLoadGsetStat(GraphDBParser::LoadGsetStatContext *ctx) = 0;

  virtual void enterLoadGStat(GraphDBParser::LoadGStatContext *ctx) = 0;
  virtual void exitLoadGStat(GraphDBParser::LoadGStatContext *ctx) = 0;

  virtual void enterDropStat(GraphDBParser::DropStatContext *ctx) = 0;
  virtual void exitDropStat(GraphDBParser::DropStatContext *ctx) = 0;

  virtual void enterDropGsetStat(GraphDBParser::DropGsetStatContext *ctx) = 0;
  virtual void exitDropGsetStat(GraphDBParser::DropGsetStatContext *ctx) = 0;

  virtual void enterDropGStat(GraphDBParser::DropGStatContext *ctx) = 0;
  virtual void exitDropGStat(GraphDBParser::DropGStatContext *ctx) = 0;

  virtual void enterDropSchemaStat(GraphDBParser::DropSchemaStatContext *ctx) = 0;
  virtual void exitDropSchemaStat(GraphDBParser::DropSchemaStatContext *ctx) = 0;

  virtual void enterSchemaTypeList(GraphDBParser::SchemaTypeListContext *ctx) = 0;
  virtual void exitSchemaTypeList(GraphDBParser::SchemaTypeListContext *ctx) = 0;

  virtual void enterSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext *ctx) = 0;
  virtual void exitSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext *ctx) = 0;

  virtual void enterAttrItem(GraphDBParser::AttrItemContext *ctx) = 0;
  virtual void exitAttrItem(GraphDBParser::AttrItemContext *ctx) = 0;

  virtual void enterDataType(GraphDBParser::DataTypeContext *ctx) = 0;
  virtual void exitDataType(GraphDBParser::DataTypeContext *ctx) = 0;

  virtual void enterAttributeName(GraphDBParser::AttributeNameContext *ctx) = 0;
  virtual void exitAttributeName(GraphDBParser::AttributeNameContext *ctx) = 0;

  virtual void enterGsid(GraphDBParser::GsidContext *ctx) = 0;
  virtual void exitGsid(GraphDBParser::GsidContext *ctx) = 0;

  virtual void enterGid(GraphDBParser::GidContext *ctx) = 0;
  virtual void exitGid(GraphDBParser::GidContext *ctx) = 0;

  virtual void enterVid(GraphDBParser::VidContext *ctx) = 0;
  virtual void exitVid(GraphDBParser::VidContext *ctx) = 0;

  virtual void enterEid(GraphDBParser::EidContext *ctx) = 0;
  virtual void exitEid(GraphDBParser::EidContext *ctx) = 0;

  virtual void enterLid(GraphDBParser::LidContext *ctx) = 0;
  virtual void exitLid(GraphDBParser::LidContext *ctx) = 0;

  virtual void enterFilename(GraphDBParser::FilenameContext *ctx) = 0;
  virtual void exitFilename(GraphDBParser::FilenameContext *ctx) = 0;

  virtual void enterSchemaid(GraphDBParser::SchemaidContext *ctx) = 0;
  virtual void exitSchemaid(GraphDBParser::SchemaidContext *ctx) = 0;

  virtual void enterVariableName(GraphDBParser::VariableNameContext *ctx) = 0;
  virtual void exitVariableName(GraphDBParser::VariableNameContext *ctx) = 0;

  virtual void enterIndexInt(GraphDBParser::IndexIntContext *ctx) = 0;
  virtual void exitIndexInt(GraphDBParser::IndexIntContext *ctx) = 0;

  virtual void enterParaItem(GraphDBParser::ParaItemContext *ctx) = 0;
  virtual void exitParaItem(GraphDBParser::ParaItemContext *ctx) = 0;


};

