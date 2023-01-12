
// Generated from GraphDB.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "GraphDBListener.h"


/**
 * This class provides an empty implementation of GraphDBListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  GraphDBBaseListener : public GraphDBListener {
public:

  virtual void enterStatement(GraphDBParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(GraphDBParser::StatementContext * /*ctx*/) override { }

  virtual void enterDmlStatement(GraphDBParser::DmlStatementContext * /*ctx*/) override { }
  virtual void exitDmlStatement(GraphDBParser::DmlStatementContext * /*ctx*/) override { }

  virtual void enterInsertStat(GraphDBParser::InsertStatContext * /*ctx*/) override { }
  virtual void exitInsertStat(GraphDBParser::InsertStatContext * /*ctx*/) override { }

  virtual void enterRemoveStat(GraphDBParser::RemoveStatContext * /*ctx*/) override { }
  virtual void exitRemoveStat(GraphDBParser::RemoveStatContext * /*ctx*/) override { }

  virtual void enterInsertGsetStat(GraphDBParser::InsertGsetStatContext * /*ctx*/) override { }
  virtual void exitInsertGsetStat(GraphDBParser::InsertGsetStatContext * /*ctx*/) override { }

  virtual void enterInsertGStat(GraphDBParser::InsertGStatContext * /*ctx*/) override { }
  virtual void exitInsertGStat(GraphDBParser::InsertGStatContext * /*ctx*/) override { }

  virtual void enterGraphNameItem(GraphDBParser::GraphNameItemContext * /*ctx*/) override { }
  virtual void exitGraphNameItem(GraphDBParser::GraphNameItemContext * /*ctx*/) override { }

  virtual void enterGraphNameList(GraphDBParser::GraphNameListContext * /*ctx*/) override { }
  virtual void exitGraphNameList(GraphDBParser::GraphNameListContext * /*ctx*/) override { }

  virtual void enterRemoveGsetStat(GraphDBParser::RemoveGsetStatContext * /*ctx*/) override { }
  virtual void exitRemoveGsetStat(GraphDBParser::RemoveGsetStatContext * /*ctx*/) override { }

  virtual void enterRemoveGStat(GraphDBParser::RemoveGStatContext * /*ctx*/) override { }
  virtual void exitRemoveGStat(GraphDBParser::RemoveGStatContext * /*ctx*/) override { }

  virtual void enterUpdateStat(GraphDBParser::UpdateStatContext * /*ctx*/) override { }
  virtual void exitUpdateStat(GraphDBParser::UpdateStatContext * /*ctx*/) override { }

  virtual void enterNameGraph(GraphDBParser::NameGraphContext * /*ctx*/) override { }
  virtual void exitNameGraph(GraphDBParser::NameGraphContext * /*ctx*/) override { }

  virtual void enterGraph(GraphDBParser::GraphContext * /*ctx*/) override { }
  virtual void exitGraph(GraphDBParser::GraphContext * /*ctx*/) override { }

  virtual void enterGraphItem(GraphDBParser::GraphItemContext * /*ctx*/) override { }
  virtual void exitGraphItem(GraphDBParser::GraphItemContext * /*ctx*/) override { }

  virtual void enterGraphList(GraphDBParser::GraphListContext * /*ctx*/) override { }
  virtual void exitGraphList(GraphDBParser::GraphListContext * /*ctx*/) override { }

  virtual void enterGraphset(GraphDBParser::GraphsetContext * /*ctx*/) override { }
  virtual void exitGraphset(GraphDBParser::GraphsetContext * /*ctx*/) override { }

  virtual void enterVertexInfo(GraphDBParser::VertexInfoContext * /*ctx*/) override { }
  virtual void exitVertexInfo(GraphDBParser::VertexInfoContext * /*ctx*/) override { }

  virtual void enterEdgeInfo(GraphDBParser::EdgeInfoContext * /*ctx*/) override { }
  virtual void exitEdgeInfo(GraphDBParser::EdgeInfoContext * /*ctx*/) override { }

  virtual void enterEdgeList(GraphDBParser::EdgeListContext * /*ctx*/) override { }
  virtual void exitEdgeList(GraphDBParser::EdgeListContext * /*ctx*/) override { }

  virtual void enterEdge(GraphDBParser::EdgeContext * /*ctx*/) override { }
  virtual void exitEdge(GraphDBParser::EdgeContext * /*ctx*/) override { }

  virtual void enterAttributeInfo(GraphDBParser::AttributeInfoContext * /*ctx*/) override { }
  virtual void exitAttributeInfo(GraphDBParser::AttributeInfoContext * /*ctx*/) override { }

  virtual void enterNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext * /*ctx*/) override { }
  virtual void exitNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext * /*ctx*/) override { }

  virtual void enterNodeAttributeList(GraphDBParser::NodeAttributeListContext * /*ctx*/) override { }
  virtual void exitNodeAttributeList(GraphDBParser::NodeAttributeListContext * /*ctx*/) override { }

  virtual void enterNodeAttributeItem(GraphDBParser::NodeAttributeItemContext * /*ctx*/) override { }
  virtual void exitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext * /*ctx*/) override { }

  virtual void enterEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext * /*ctx*/) override { }
  virtual void exitEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext * /*ctx*/) override { }

  virtual void enterEdgeAttributeList(GraphDBParser::EdgeAttributeListContext * /*ctx*/) override { }
  virtual void exitEdgeAttributeList(GraphDBParser::EdgeAttributeListContext * /*ctx*/) override { }

  virtual void enterEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext * /*ctx*/) override { }
  virtual void exitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext * /*ctx*/) override { }

  virtual void enterQueryStat(GraphDBParser::QueryStatContext * /*ctx*/) override { }
  virtual void exitQueryStat(GraphDBParser::QueryStatContext * /*ctx*/) override { }

  virtual void enterMultipleOperator(GraphDBParser::MultipleOperatorContext * /*ctx*/) override { }
  virtual void exitMultipleOperator(GraphDBParser::MultipleOperatorContext * /*ctx*/) override { }

  virtual void enterProjectCondition(GraphDBParser::ProjectConditionContext * /*ctx*/) override { }
  virtual void exitProjectCondition(GraphDBParser::ProjectConditionContext * /*ctx*/) override { }

  virtual void enterFromCondition(GraphDBParser::FromConditionContext * /*ctx*/) override { }
  virtual void exitFromCondition(GraphDBParser::FromConditionContext * /*ctx*/) override { }

  virtual void enterAlignConditionList(GraphDBParser::AlignConditionListContext * /*ctx*/) override { }
  virtual void exitAlignConditionList(GraphDBParser::AlignConditionListContext * /*ctx*/) override { }

  virtual void enterAlignCondition(GraphDBParser::AlignConditionContext * /*ctx*/) override { }
  virtual void exitAlignCondition(GraphDBParser::AlignConditionContext * /*ctx*/) override { }

  virtual void enterFilenamelist(GraphDBParser::FilenamelistContext * /*ctx*/) override { }
  virtual void exitFilenamelist(GraphDBParser::FilenamelistContext * /*ctx*/) override { }

  virtual void enterWhereCondition(GraphDBParser::WhereConditionContext * /*ctx*/) override { }
  virtual void exitWhereCondition(GraphDBParser::WhereConditionContext * /*ctx*/) override { }

  virtual void enterMapCondition(GraphDBParser::MapConditionContext * /*ctx*/) override { }
  virtual void exitMapCondition(GraphDBParser::MapConditionContext * /*ctx*/) override { }

  virtual void enterReduceWord(GraphDBParser::ReduceWordContext * /*ctx*/) override { }
  virtual void exitReduceWord(GraphDBParser::ReduceWordContext * /*ctx*/) override { }

  virtual void enterMaximalWord(GraphDBParser::MaximalWordContext * /*ctx*/) override { }
  virtual void exitMaximalWord(GraphDBParser::MaximalWordContext * /*ctx*/) override { }

  virtual void enterOperationStatement(GraphDBParser::OperationStatementContext * /*ctx*/) override { }
  virtual void exitOperationStatement(GraphDBParser::OperationStatementContext * /*ctx*/) override { }

  virtual void enterOperatorGSet(GraphDBParser::OperatorGSetContext * /*ctx*/) override { }
  virtual void exitOperatorGSet(GraphDBParser::OperatorGSetContext * /*ctx*/) override { }

  virtual void enterSchemaNameItem(GraphDBParser::SchemaNameItemContext * /*ctx*/) override { }
  virtual void exitSchemaNameItem(GraphDBParser::SchemaNameItemContext * /*ctx*/) override { }

  virtual void enterSchemaNameList(GraphDBParser::SchemaNameListContext * /*ctx*/) override { }
  virtual void exitSchemaNameList(GraphDBParser::SchemaNameListContext * /*ctx*/) override { }

  virtual void enterProductStatement(GraphDBParser::ProductStatementContext * /*ctx*/) override { }
  virtual void exitProductStatement(GraphDBParser::ProductStatementContext * /*ctx*/) override { }

  virtual void enterJoinStatement(GraphDBParser::JoinStatementContext * /*ctx*/) override { }
  virtual void exitJoinStatement(GraphDBParser::JoinStatementContext * /*ctx*/) override { }

  virtual void enterValue(GraphDBParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(GraphDBParser::ValueContext * /*ctx*/) override { }

  virtual void enterEntId(GraphDBParser::EntIdContext * /*ctx*/) override { }
  virtual void exitEntId(GraphDBParser::EntIdContext * /*ctx*/) override { }

  virtual void enterVidList(GraphDBParser::VidListContext * /*ctx*/) override { }
  virtual void exitVidList(GraphDBParser::VidListContext * /*ctx*/) override { }

  virtual void enterGidList(GraphDBParser::GidListContext * /*ctx*/) override { }
  virtual void exitGidList(GraphDBParser::GidListContext * /*ctx*/) override { }

  virtual void enterLidList(GraphDBParser::LidListContext * /*ctx*/) override { }
  virtual void exitLidList(GraphDBParser::LidListContext * /*ctx*/) override { }

  virtual void enterVidTuple(GraphDBParser::VidTupleContext * /*ctx*/) override { }
  virtual void exitVidTuple(GraphDBParser::VidTupleContext * /*ctx*/) override { }

  virtual void enterVidTupleList(GraphDBParser::VidTupleListContext * /*ctx*/) override { }
  virtual void exitVidTupleList(GraphDBParser::VidTupleListContext * /*ctx*/) override { }

  virtual void enterAttrEqItem(GraphDBParser::AttrEqItemContext * /*ctx*/) override { }
  virtual void exitAttrEqItem(GraphDBParser::AttrEqItemContext * /*ctx*/) override { }

  virtual void enterAttrEqItemList(GraphDBParser::AttrEqItemListContext * /*ctx*/) override { }
  virtual void exitAttrEqItemList(GraphDBParser::AttrEqItemListContext * /*ctx*/) override { }

  virtual void enterAttributeNameList(GraphDBParser::AttributeNameListContext * /*ctx*/) override { }
  virtual void exitAttributeNameList(GraphDBParser::AttributeNameListContext * /*ctx*/) override { }

  virtual void enterAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext * /*ctx*/) override { }
  virtual void exitAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext * /*ctx*/) override { }

  virtual void enterAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext * /*ctx*/) override { }
  virtual void exitAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext * /*ctx*/) override { }

  virtual void enterGT(GraphDBParser::GTContext * /*ctx*/) override { }
  virtual void exitGT(GraphDBParser::GTContext * /*ctx*/) override { }

  virtual void enterLT(GraphDBParser::LTContext * /*ctx*/) override { }
  virtual void exitLT(GraphDBParser::LTContext * /*ctx*/) override { }

  virtual void enterGTE(GraphDBParser::GTEContext * /*ctx*/) override { }
  virtual void exitGTE(GraphDBParser::GTEContext * /*ctx*/) override { }

  virtual void enterLTE(GraphDBParser::LTEContext * /*ctx*/) override { }
  virtual void exitLTE(GraphDBParser::LTEContext * /*ctx*/) override { }

  virtual void enterEQ(GraphDBParser::EQContext * /*ctx*/) override { }
  virtual void exitEQ(GraphDBParser::EQContext * /*ctx*/) override { }

  virtual void enterNEQ(GraphDBParser::NEQContext * /*ctx*/) override { }
  virtual void exitNEQ(GraphDBParser::NEQContext * /*ctx*/) override { }

  virtual void enterCalculateOperator(GraphDBParser::CalculateOperatorContext * /*ctx*/) override { }
  virtual void exitCalculateOperator(GraphDBParser::CalculateOperatorContext * /*ctx*/) override { }

  virtual void enterLogicFlagBi(GraphDBParser::LogicFlagBiContext * /*ctx*/) override { }
  virtual void exitLogicFlagBi(GraphDBParser::LogicFlagBiContext * /*ctx*/) override { }

  virtual void enterLogicFlagNot(GraphDBParser::LogicFlagNotContext * /*ctx*/) override { }
  virtual void exitLogicFlagNot(GraphDBParser::LogicFlagNotContext * /*ctx*/) override { }

  virtual void enterFirstOrderStat(GraphDBParser::FirstOrderStatContext * /*ctx*/) override { }
  virtual void exitFirstOrderStat(GraphDBParser::FirstOrderStatContext * /*ctx*/) override { }

  virtual void enterFirstOrderUnit(GraphDBParser::FirstOrderUnitContext * /*ctx*/) override { }
  virtual void exitFirstOrderUnit(GraphDBParser::FirstOrderUnitContext * /*ctx*/) override { }

  virtual void enterExistStat(GraphDBParser::ExistStatContext * /*ctx*/) override { }
  virtual void exitExistStat(GraphDBParser::ExistStatContext * /*ctx*/) override { }

  virtual void enterForeachStat(GraphDBParser::ForeachStatContext * /*ctx*/) override { }
  virtual void exitForeachStat(GraphDBParser::ForeachStatContext * /*ctx*/) override { }

  virtual void enterCompareStat(GraphDBParser::CompareStatContext * /*ctx*/) override { }
  virtual void exitCompareStat(GraphDBParser::CompareStatContext * /*ctx*/) override { }

  virtual void enterCompareUnit(GraphDBParser::CompareUnitContext * /*ctx*/) override { }
  virtual void exitCompareUnit(GraphDBParser::CompareUnitContext * /*ctx*/) override { }

  virtual void enterCompareValStat(GraphDBParser::CompareValStatContext * /*ctx*/) override { }
  virtual void exitCompareValStat(GraphDBParser::CompareValStatContext * /*ctx*/) override { }

  virtual void enterFuncStat(GraphDBParser::FuncStatContext * /*ctx*/) override { }
  virtual void exitFuncStat(GraphDBParser::FuncStatContext * /*ctx*/) override { }

  virtual void enterFuncName(GraphDBParser::FuncNameContext * /*ctx*/) override { }
  virtual void exitFuncName(GraphDBParser::FuncNameContext * /*ctx*/) override { }

  virtual void enterObject(GraphDBParser::ObjectContext * /*ctx*/) override { }
  virtual void exitObject(GraphDBParser::ObjectContext * /*ctx*/) override { }

  virtual void enterObjectList(GraphDBParser::ObjectListContext * /*ctx*/) override { }
  virtual void exitObjectList(GraphDBParser::ObjectListContext * /*ctx*/) override { }

  virtual void enterVarList(GraphDBParser::VarListContext * /*ctx*/) override { }
  virtual void exitVarList(GraphDBParser::VarListContext * /*ctx*/) override { }

  virtual void enterBracketLeft(GraphDBParser::BracketLeftContext * /*ctx*/) override { }
  virtual void exitBracketLeft(GraphDBParser::BracketLeftContext * /*ctx*/) override { }

  virtual void enterBracketRight(GraphDBParser::BracketRightContext * /*ctx*/) override { }
  virtual void exitBracketRight(GraphDBParser::BracketRightContext * /*ctx*/) override { }

  virtual void enterDdlStatement(GraphDBParser::DdlStatementContext * /*ctx*/) override { }
  virtual void exitDdlStatement(GraphDBParser::DdlStatementContext * /*ctx*/) override { }

  virtual void enterCreateSchemaStat(GraphDBParser::CreateSchemaStatContext * /*ctx*/) override { }
  virtual void exitCreateSchemaStat(GraphDBParser::CreateSchemaStatContext * /*ctx*/) override { }

  virtual void enterSchemaStatement(GraphDBParser::SchemaStatementContext * /*ctx*/) override { }
  virtual void exitSchemaStatement(GraphDBParser::SchemaStatementContext * /*ctx*/) override { }

  virtual void enterSchemaNodeList(GraphDBParser::SchemaNodeListContext * /*ctx*/) override { }
  virtual void exitSchemaNodeList(GraphDBParser::SchemaNodeListContext * /*ctx*/) override { }

  virtual void enterSchemaEdgeList(GraphDBParser::SchemaEdgeListContext * /*ctx*/) override { }
  virtual void exitSchemaEdgeList(GraphDBParser::SchemaEdgeListContext * /*ctx*/) override { }

  virtual void enterSchemaNode(GraphDBParser::SchemaNodeContext * /*ctx*/) override { }
  virtual void exitSchemaNode(GraphDBParser::SchemaNodeContext * /*ctx*/) override { }

  virtual void enterSchemaAttrList(GraphDBParser::SchemaAttrListContext * /*ctx*/) override { }
  virtual void exitSchemaAttrList(GraphDBParser::SchemaAttrListContext * /*ctx*/) override { }

  virtual void enterSchemaEdge(GraphDBParser::SchemaEdgeContext * /*ctx*/) override { }
  virtual void exitSchemaEdge(GraphDBParser::SchemaEdgeContext * /*ctx*/) override { }

  virtual void enterEdgeLinkageList(GraphDBParser::EdgeLinkageListContext * /*ctx*/) override { }
  virtual void exitEdgeLinkageList(GraphDBParser::EdgeLinkageListContext * /*ctx*/) override { }

  virtual void enterLabelName(GraphDBParser::LabelNameContext * /*ctx*/) override { }
  virtual void exitLabelName(GraphDBParser::LabelNameContext * /*ctx*/) override { }

  virtual void enterTypeName(GraphDBParser::TypeNameContext * /*ctx*/) override { }
  virtual void exitTypeName(GraphDBParser::TypeNameContext * /*ctx*/) override { }

  virtual void enterSchemaItem(GraphDBParser::SchemaItemContext * /*ctx*/) override { }
  virtual void exitSchemaItem(GraphDBParser::SchemaItemContext * /*ctx*/) override { }

  virtual void enterCreateGsetStat(GraphDBParser::CreateGsetStatContext * /*ctx*/) override { }
  virtual void exitCreateGsetStat(GraphDBParser::CreateGsetStatContext * /*ctx*/) override { }

  virtual void enterCreateGStat(GraphDBParser::CreateGStatContext * /*ctx*/) override { }
  virtual void exitCreateGStat(GraphDBParser::CreateGStatContext * /*ctx*/) override { }

  virtual void enterCreateGFileStat(GraphDBParser::CreateGFileStatContext * /*ctx*/) override { }
  virtual void exitCreateGFileStat(GraphDBParser::CreateGFileStatContext * /*ctx*/) override { }

  virtual void enterCreateGForStat(GraphDBParser::CreateGForStatContext * /*ctx*/) override { }
  virtual void exitCreateGForStat(GraphDBParser::CreateGForStatContext * /*ctx*/) override { }

  virtual void enterLoadGsetStat(GraphDBParser::LoadGsetStatContext * /*ctx*/) override { }
  virtual void exitLoadGsetStat(GraphDBParser::LoadGsetStatContext * /*ctx*/) override { }

  virtual void enterLoadGStat(GraphDBParser::LoadGStatContext * /*ctx*/) override { }
  virtual void exitLoadGStat(GraphDBParser::LoadGStatContext * /*ctx*/) override { }

  virtual void enterDropStat(GraphDBParser::DropStatContext * /*ctx*/) override { }
  virtual void exitDropStat(GraphDBParser::DropStatContext * /*ctx*/) override { }

  virtual void enterDropGsetStat(GraphDBParser::DropGsetStatContext * /*ctx*/) override { }
  virtual void exitDropGsetStat(GraphDBParser::DropGsetStatContext * /*ctx*/) override { }

  virtual void enterDropGStat(GraphDBParser::DropGStatContext * /*ctx*/) override { }
  virtual void exitDropGStat(GraphDBParser::DropGStatContext * /*ctx*/) override { }

  virtual void enterDropSchemaStat(GraphDBParser::DropSchemaStatContext * /*ctx*/) override { }
  virtual void exitDropSchemaStat(GraphDBParser::DropSchemaStatContext * /*ctx*/) override { }

  virtual void enterSchemaTypeList(GraphDBParser::SchemaTypeListContext * /*ctx*/) override { }
  virtual void exitSchemaTypeList(GraphDBParser::SchemaTypeListContext * /*ctx*/) override { }

  virtual void enterSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext * /*ctx*/) override { }
  virtual void exitSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext * /*ctx*/) override { }

  virtual void enterAttrItem(GraphDBParser::AttrItemContext * /*ctx*/) override { }
  virtual void exitAttrItem(GraphDBParser::AttrItemContext * /*ctx*/) override { }

  virtual void enterDataType(GraphDBParser::DataTypeContext * /*ctx*/) override { }
  virtual void exitDataType(GraphDBParser::DataTypeContext * /*ctx*/) override { }

  virtual void enterAttributeName(GraphDBParser::AttributeNameContext * /*ctx*/) override { }
  virtual void exitAttributeName(GraphDBParser::AttributeNameContext * /*ctx*/) override { }

  virtual void enterGsid(GraphDBParser::GsidContext * /*ctx*/) override { }
  virtual void exitGsid(GraphDBParser::GsidContext * /*ctx*/) override { }

  virtual void enterGid(GraphDBParser::GidContext * /*ctx*/) override { }
  virtual void exitGid(GraphDBParser::GidContext * /*ctx*/) override { }

  virtual void enterVid(GraphDBParser::VidContext * /*ctx*/) override { }
  virtual void exitVid(GraphDBParser::VidContext * /*ctx*/) override { }

  virtual void enterEid(GraphDBParser::EidContext * /*ctx*/) override { }
  virtual void exitEid(GraphDBParser::EidContext * /*ctx*/) override { }

  virtual void enterLid(GraphDBParser::LidContext * /*ctx*/) override { }
  virtual void exitLid(GraphDBParser::LidContext * /*ctx*/) override { }

  virtual void enterFilename(GraphDBParser::FilenameContext * /*ctx*/) override { }
  virtual void exitFilename(GraphDBParser::FilenameContext * /*ctx*/) override { }

  virtual void enterSchemaid(GraphDBParser::SchemaidContext * /*ctx*/) override { }
  virtual void exitSchemaid(GraphDBParser::SchemaidContext * /*ctx*/) override { }

  virtual void enterVariableName(GraphDBParser::VariableNameContext * /*ctx*/) override { }
  virtual void exitVariableName(GraphDBParser::VariableNameContext * /*ctx*/) override { }

  virtual void enterIndexInt(GraphDBParser::IndexIntContext * /*ctx*/) override { }
  virtual void exitIndexInt(GraphDBParser::IndexIntContext * /*ctx*/) override { }

  virtual void enterParaItem(GraphDBParser::ParaItemContext * /*ctx*/) override { }
  virtual void exitParaItem(GraphDBParser::ParaItemContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

