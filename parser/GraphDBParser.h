
// Generated from GraphDB.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  GraphDBParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, SPACES = 20, 
    K_where = 21, K_drop = 22, K_graphset = 23, K_graph = 24, K_schema = 25, 
    K_insert = 26, K_into = 27, K_as = 28, K_remove = 29, K_from = 30, K_update = 31, 
    K_at = 32, K_by = 33, K_set = 34, K_query = 35, K_difference = 36, K_proj = 37, 
    K_for = 38, K_product = 39, K_align = 40, K_to = 41, K_on = 42, K_reduce = 43, 
    K_select = 44, K_map = 45, K_union = 46, K_join = 47, K_intersect = 48, 
    K_maximal = 49, K_vertex = 50, K_edge = 51, K_and = 52, K_or = 53, K_arrow = 54, 
    K_not = 55, K_exist = 56, K_foreach = 57, K_equal = 58, K_complete = 59, 
    K_hasedge = 60, K_graphequal = 61, K_unique = 62, K_sizegeq = 63, K_graphinset = 64, 
    K_subgraph = 65, K_inducedsub = 66, K_connect = 67, K_clique = 68, K_tdensesub = 69, 
    K_track = 70, K_create = 71, K_int = 72, K_integer = 73, K_float = 74, 
    K_double = 75, K_char = 76, K_string = 77, K_true = 78, K_false = 79, 
    K_file = 80, K_load = 81, INTEGER_NUMBER = 82, NOT_INTEGER_NUMBER = 83, 
    NAME_STRING = 84, LETTER = 85, SYMBOL = 86, CHAR = 87, TEXT = 88
  };

  enum {
    RuleStatement = 0, RuleDmlStatement = 1, RuleInsertStat = 2, RuleRemoveStat = 3, 
    RuleInsertGsetStat = 4, RuleInsertGStat = 5, RuleGraphNameItem = 6, 
    RuleGraphNameList = 7, RuleRemoveGsetStat = 8, RuleRemoveGStat = 9, 
    RuleUpdateStat = 10, RuleNameGraph = 11, RuleGraph = 12, RuleGraphItem = 13, 
    RuleGraphList = 14, RuleGraphset = 15, RuleVertexInfo = 16, RuleEdgeInfo = 17, 
    RuleEdgeList = 18, RuleEdge = 19, RuleAttributeInfo = 20, RuleNodeAttributeInfo = 21, 
    RuleNodeAttributeList = 22, RuleNodeAttributeItem = 23, RuleEdgeAttributeInfo = 24, 
    RuleEdgeAttributeList = 25, RuleEdgeAttributeItem = 26, RuleQueryStat = 27, 
    RuleMultipleOperator = 28, RuleProjectCondition = 29, RuleFromCondition = 30, 
    RuleAlignConditionList = 31, RuleAlignCondition = 32, RuleFilenamelist = 33, 
    RuleWhereCondition = 34, RuleMapCondition = 35, RuleReduceWord = 36, 
    RuleMaximalWord = 37, RuleOperationStatement = 38, RuleOperatorGSet = 39, 
    RuleSchemaNameItem = 40, RuleSchemaNameList = 41, RuleProductStatement = 42, 
    RuleJoinStatement = 43, RuleValue = 44, RuleEntId = 45, RuleVidList = 46, 
    RuleGidList = 47, RuleLidList = 48, RuleVidTuple = 49, RuleVidTupleList = 50, 
    RuleAttrEqItem = 51, RuleAttrEqItemList = 52, RuleAttributeNameList = 53, 
    RuleAttrEqItemUncertain = 54, RuleAttrEqItemListUncertain = 55, RuleCompareOperator = 56, 
    RuleCalculateOperator = 57, RuleLogicFlagBi = 58, RuleLogicFlagNot = 59, 
    RuleFirstOrderStat = 60, RuleFirstOrderUnit = 61, RuleExistStat = 62, 
    RuleForeachStat = 63, RuleCompareStat = 64, RuleCompareUnit = 65, RuleCompareValStat = 66, 
    RuleFuncStat = 67, RuleFuncName = 68, RuleObject = 69, RuleObjectList = 70, 
    RuleVarList = 71, RuleBracketLeft = 72, RuleBracketRight = 73, RuleDdlStatement = 74, 
    RuleCreateSchemaStat = 75, RuleSchemaStatement = 76, RuleSchemaNodeList = 77, 
    RuleSchemaEdgeList = 78, RuleSchemaNode = 79, RuleSchemaAttrList = 80, 
    RuleSchemaEdge = 81, RuleEdgeLinkageList = 82, RuleLabelName = 83, RuleTypeName = 84, 
    RuleSchemaItem = 85, RuleCreateGsetStat = 86, RuleCreateGStat = 87, 
    RuleCreateGFileStat = 88, RuleCreateGForStat = 89, RuleLoadGsetStat = 90, 
    RuleLoadGStat = 91, RuleDropStat = 92, RuleDropGsetStat = 93, RuleDropGStat = 94, 
    RuleDropSchemaStat = 95, RuleSchemaTypeList = 96, RuleSchemaAttributeItem = 97, 
    RuleAttrItem = 98, RuleDataType = 99, RuleAttributeName = 100, RuleGsid = 101, 
    RuleGid = 102, RuleVid = 103, RuleEid = 104, RuleLid = 105, RuleFilename = 106, 
    RuleSchemaid = 107, RuleVariableName = 108, RuleIndexInt = 109, RuleParaItem = 110
  };

  GraphDBParser(antlr4::TokenStream *input);
  ~GraphDBParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class StatementContext;
  class DmlStatementContext;
  class InsertStatContext;
  class RemoveStatContext;
  class InsertGsetStatContext;
  class InsertGStatContext;
  class GraphNameItemContext;
  class GraphNameListContext;
  class RemoveGsetStatContext;
  class RemoveGStatContext;
  class UpdateStatContext;
  class NameGraphContext;
  class GraphContext;
  class GraphItemContext;
  class GraphListContext;
  class GraphsetContext;
  class VertexInfoContext;
  class EdgeInfoContext;
  class EdgeListContext;
  class EdgeContext;
  class AttributeInfoContext;
  class NodeAttributeInfoContext;
  class NodeAttributeListContext;
  class NodeAttributeItemContext;
  class EdgeAttributeInfoContext;
  class EdgeAttributeListContext;
  class EdgeAttributeItemContext;
  class QueryStatContext;
  class MultipleOperatorContext;
  class ProjectConditionContext;
  class FromConditionContext;
  class AlignConditionListContext;
  class AlignConditionContext;
  class FilenamelistContext;
  class WhereConditionContext;
  class MapConditionContext;
  class ReduceWordContext;
  class MaximalWordContext;
  class OperationStatementContext;
  class OperatorGSetContext;
  class SchemaNameItemContext;
  class SchemaNameListContext;
  class ProductStatementContext;
  class JoinStatementContext;
  class ValueContext;
  class EntIdContext;
  class VidListContext;
  class GidListContext;
  class LidListContext;
  class VidTupleContext;
  class VidTupleListContext;
  class AttrEqItemContext;
  class AttrEqItemListContext;
  class AttributeNameListContext;
  class AttrEqItemUncertainContext;
  class AttrEqItemListUncertainContext;
  class CompareOperatorContext;
  class CalculateOperatorContext;
  class LogicFlagBiContext;
  class LogicFlagNotContext;
  class FirstOrderStatContext;
  class FirstOrderUnitContext;
  class ExistStatContext;
  class ForeachStatContext;
  class CompareStatContext;
  class CompareUnitContext;
  class CompareValStatContext;
  class FuncStatContext;
  class FuncNameContext;
  class ObjectContext;
  class ObjectListContext;
  class VarListContext;
  class BracketLeftContext;
  class BracketRightContext;
  class DdlStatementContext;
  class CreateSchemaStatContext;
  class SchemaStatementContext;
  class SchemaNodeListContext;
  class SchemaEdgeListContext;
  class SchemaNodeContext;
  class SchemaAttrListContext;
  class SchemaEdgeContext;
  class EdgeLinkageListContext;
  class LabelNameContext;
  class TypeNameContext;
  class SchemaItemContext;
  class CreateGsetStatContext;
  class CreateGStatContext;
  class CreateGFileStatContext;
  class CreateGForStatContext;
  class LoadGsetStatContext;
  class LoadGStatContext;
  class DropStatContext;
  class DropGsetStatContext;
  class DropGStatContext;
  class DropSchemaStatContext;
  class SchemaTypeListContext;
  class SchemaAttributeItemContext;
  class AttrItemContext;
  class DataTypeContext;
  class AttributeNameContext;
  class GsidContext;
  class GidContext;
  class VidContext;
  class EidContext;
  class LidContext;
  class FilenameContext;
  class SchemaidContext;
  class VariableNameContext;
  class IndexIntContext;
  class ParaItemContext; 

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DmlStatementContext *dmlStatement();
    DdlStatementContext *ddlStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  DmlStatementContext : public antlr4::ParserRuleContext {
  public:
    DmlStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InsertStatContext *insertStat();
    RemoveStatContext *removeStat();
    UpdateStatContext *updateStat();
    QueryStatContext *queryStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DmlStatementContext* dmlStatement();

  class  InsertStatContext : public antlr4::ParserRuleContext {
  public:
    InsertStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    InsertGsetStatContext *insertGsetStat();
    InsertGStatContext *insertGStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertStatContext* insertStat();

  class  RemoveStatContext : public antlr4::ParserRuleContext {
  public:
    RemoveStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RemoveGsetStatContext *removeGsetStat();
    RemoveGStatContext *removeGStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RemoveStatContext* removeStat();

  class  InsertGsetStatContext : public antlr4::ParserRuleContext {
  public:
    InsertGsetStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_insert();
    antlr4::tree::TerminalNode *K_into();
    antlr4::tree::TerminalNode *K_graphset();
    GsidContext *gsid();
    GidListContext *gidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertGsetStatContext* insertGsetStat();

  class  InsertGStatContext : public antlr4::ParserRuleContext {
  public:
    InsertGStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_insert();
    GraphContext *graph();
    antlr4::tree::TerminalNode *K_into();
    std::vector<antlr4::tree::TerminalNode *> K_graph();
    antlr4::tree::TerminalNode* K_graph(size_t i);
    std::vector<GidContext *> gid();
    GidContext* gid(size_t i);
    antlr4::tree::TerminalNode *K_file();
    FilenamelistContext *filenamelist();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InsertGStatContext* insertGStat();

  class  GraphNameItemContext : public antlr4::ParserRuleContext {
  public:
    GraphNameItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphContext *graph();
    antlr4::tree::TerminalNode *K_as();
    GidContext *gid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GraphNameItemContext* graphNameItem();

  class  GraphNameListContext : public antlr4::ParserRuleContext {
  public:
    GraphNameListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphNameItemContext *graphNameItem();
    GraphNameListContext *graphNameList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GraphNameListContext* graphNameList();

  class  RemoveGsetStatContext : public antlr4::ParserRuleContext {
  public:
    RemoveGsetStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_remove();
    antlr4::tree::TerminalNode *K_from();
    antlr4::tree::TerminalNode *K_graphset();
    GsidContext *gsid();
    GidListContext *gidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RemoveGsetStatContext* removeGsetStat();

  class  RemoveGStatContext : public antlr4::ParserRuleContext {
  public:
    RemoveGStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_remove();
    VertexInfoContext *vertexInfo();
    EdgeInfoContext *edgeInfo();
    antlr4::tree::TerminalNode *K_from();
    antlr4::tree::TerminalNode *K_graph();
    std::vector<GidContext *> gid();
    GidContext* gid(size_t i);
    antlr4::tree::TerminalNode *K_file();
    FilenamelistContext *filenamelist();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RemoveGStatContext* removeGStat();

  class  UpdateStatContext : public antlr4::ParserRuleContext {
  public:
    UpdateStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_update();
    GsidContext *gsid();
    antlr4::tree::TerminalNode *K_at();
    GidContext *gid();
    antlr4::tree::TerminalNode *K_by();
    antlr4::tree::TerminalNode *K_set();
    AttributeNameContext *attributeName();
    ValueContext *value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UpdateStatContext* updateStat();

  class  NameGraphContext : public antlr4::ParserRuleContext {
  public:
    NameGraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_as();
    GsidContext *gsid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameGraphContext* nameGraph();

  class  GraphContext : public antlr4::ParserRuleContext {
  public:
    GraphContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VertexInfoContext *vertexInfo();
    EdgeInfoContext *edgeInfo();
    AttributeInfoContext *attributeInfo();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GraphContext* graph();

  class  GraphItemContext : public antlr4::ParserRuleContext {
  public:
    GraphItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphContext *graph();
    GidContext *gid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GraphItemContext* graphItem();

  class  GraphListContext : public antlr4::ParserRuleContext {
  public:
    GraphListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphItemContext *graphItem();
    GraphListContext *graphList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GraphListContext* graphList();

  class  GraphsetContext : public antlr4::ParserRuleContext {
  public:
    GraphsetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphListContext *graphList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GraphsetContext* graphset();

  class  VertexInfoContext : public antlr4::ParserRuleContext {
  public:
    VertexInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VidListContext *vidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VertexInfoContext* vertexInfo();

  class  EdgeInfoContext : public antlr4::ParserRuleContext {
  public:
    EdgeInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EdgeListContext *edgeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeInfoContext* edgeInfo();

  class  EdgeListContext : public antlr4::ParserRuleContext {
  public:
    EdgeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EdgeContext *edge();
    LidContext *lid();
    EidContext *eid();
    EdgeListContext *edgeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeListContext* edgeList();

  class  EdgeContext : public antlr4::ParserRuleContext {
  public:
    EdgeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VidTupleContext *vidTuple();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeContext* edge();

  class  AttributeInfoContext : public antlr4::ParserRuleContext {
  public:
    AttributeInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NodeAttributeInfoContext *nodeAttributeInfo();
    EdgeAttributeInfoContext *edgeAttributeInfo();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeInfoContext* attributeInfo();

  class  NodeAttributeInfoContext : public antlr4::ParserRuleContext {
  public:
    NodeAttributeInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NodeAttributeListContext *nodeAttributeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NodeAttributeInfoContext* nodeAttributeInfo();

  class  NodeAttributeListContext : public antlr4::ParserRuleContext {
  public:
    NodeAttributeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NodeAttributeItemContext *nodeAttributeItem();
    NodeAttributeListContext *nodeAttributeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NodeAttributeListContext* nodeAttributeList();

  class  NodeAttributeItemContext : public antlr4::ParserRuleContext {
  public:
    NodeAttributeItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VidContext *vid();
    AttrEqItemListContext *attrEqItemList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NodeAttributeItemContext* nodeAttributeItem();

  class  EdgeAttributeInfoContext : public antlr4::ParserRuleContext {
  public:
    EdgeAttributeInfoContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EdgeAttributeListContext *edgeAttributeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeAttributeInfoContext* edgeAttributeInfo();

  class  EdgeAttributeListContext : public antlr4::ParserRuleContext {
  public:
    EdgeAttributeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EdgeAttributeItemContext *edgeAttributeItem();
    EdgeAttributeListContext *edgeAttributeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeAttributeListContext* edgeAttributeList();

  class  EdgeAttributeItemContext : public antlr4::ParserRuleContext {
  public:
    EdgeAttributeItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EidContext *eid();
    EdgeContext *edge();
    AttrEqItemListContext *attrEqItemList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeAttributeItemContext* edgeAttributeItem();

  class  QueryStatContext : public antlr4::ParserRuleContext {
  public:
    QueryStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<QueryStatContext *> queryStat();
    QueryStatContext* queryStat(size_t i);
    antlr4::tree::TerminalNode *K_select();
    NameGraphContext *nameGraph();
    ReduceWordContext *reduceWord();
    MaximalWordContext *maximalWord();
    ProjectConditionContext *projectCondition();
    FromConditionContext *fromCondition();
    AlignConditionListContext *alignConditionList();
    WhereConditionContext *whereCondition();
    MapConditionContext *mapCondition();
    GsidContext *gsid();
    MultipleOperatorContext *multipleOperator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QueryStatContext* queryStat();
  QueryStatContext* queryStat(int precedence);
  class  MultipleOperatorContext : public antlr4::ParserRuleContext {
  public:
    MultipleOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_intersect();
    antlr4::tree::TerminalNode *K_union();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultipleOperatorContext* multipleOperator();

  class  ProjectConditionContext : public antlr4::ParserRuleContext {
  public:
    ProjectConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SchemaNameListContext *schemaNameList();
    antlr4::tree::TerminalNode *K_for();
    LidListContext *lidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProjectConditionContext* projectCondition();

  class  FromConditionContext : public antlr4::ParserRuleContext {
  public:
    FromConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_from();
    OperatorGSetContext *operatorGSet();
    OperationStatementContext *operationStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromConditionContext* fromCondition();

  class  AlignConditionListContext : public antlr4::ParserRuleContext {
  public:
    AlignConditionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AlignConditionContext *alignCondition();
    AlignConditionListContext *alignConditionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AlignConditionListContext* alignConditionList();

  class  AlignConditionContext : public antlr4::ParserRuleContext {
  public:
    AlignConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_align();
    std::vector<LidContext *> lid();
    LidContext* lid(size_t i);
    antlr4::tree::TerminalNode *K_on();
    AttrEqItemListUncertainContext *attrEqItemListUncertain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AlignConditionContext* alignCondition();

  class  FilenamelistContext : public antlr4::ParserRuleContext {
  public:
    FilenamelistContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FilenameContext *filename();
    FilenamelistContext *filenamelist();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilenamelistContext* filenamelist();

  class  WhereConditionContext : public antlr4::ParserRuleContext {
  public:
    WhereConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_where();
    FirstOrderStatContext *firstOrderStat();
    antlr4::tree::TerminalNode *K_file();
    FilenamelistContext *filenamelist();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereConditionContext* whereCondition();

  class  MapConditionContext : public antlr4::ParserRuleContext {
  public:
    MapConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_map();
    OperatorGSetContext *operatorGSet();
    antlr4::tree::TerminalNode *K_by();
    GsidContext *gsid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MapConditionContext* mapCondition();

  class  ReduceWordContext : public antlr4::ParserRuleContext {
  public:
    ReduceWordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_reduce();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReduceWordContext* reduceWord();

  class  MaximalWordContext : public antlr4::ParserRuleContext {
  public:
    MaximalWordContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_maximal();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MaximalWordContext* maximalWord();

  class  OperationStatementContext : public antlr4::ParserRuleContext {
  public:
    OperationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ProductStatementContext *productStatement();
    JoinStatementContext *joinStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperationStatementContext* operationStatement();

  class  OperatorGSetContext : public antlr4::ParserRuleContext {
  public:
    OperatorGSetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GsidContext *gsid();
    GraphsetContext *graphset();
    NameGraphContext *nameGraph();
    QueryStatContext *queryStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperatorGSetContext* operatorGSet();

  class  SchemaNameItemContext : public antlr4::ParserRuleContext {
  public:
    SchemaNameItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeNameListContext *attributeNameList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaNameItemContext* schemaNameItem();

  class  SchemaNameListContext : public antlr4::ParserRuleContext {
  public:
    SchemaNameListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SchemaNameItemContext *schemaNameItem();
    SchemaNameListContext *schemaNameList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaNameListContext* schemaNameList();

  class  ProductStatementContext : public antlr4::ParserRuleContext {
  public:
    ProductStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OperatorGSetContext *> operatorGSet();
    OperatorGSetContext* operatorGSet(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProductStatementContext* productStatement();

  class  JoinStatementContext : public antlr4::ParserRuleContext {
  public:
    JoinStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OperatorGSetContext *> operatorGSet();
    OperatorGSetContext* operatorGSet(size_t i);
    antlr4::tree::TerminalNode *K_join();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JoinStatementContext* joinStatement();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_NUMBER();
    antlr4::tree::TerminalNode *NOT_INTEGER_NUMBER();
    antlr4::tree::TerminalNode *TEXT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueContext* value();

  class  EntIdContext : public antlr4::ParserRuleContext {
  public:
    EntIdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VidContext *vid();
    EidContext *eid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EntIdContext* entId();

  class  VidListContext : public antlr4::ParserRuleContext {
  public:
    VidListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VidContext *vid();
    LidContext *lid();
    VidListContext *vidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VidListContext* vidList();

  class  GidListContext : public antlr4::ParserRuleContext {
  public:
    GidListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GidContext *gid();
    GidListContext *gidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GidListContext* gidList();

  class  LidListContext : public antlr4::ParserRuleContext {
  public:
    LidListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LidContext *lid();
    LidListContext *lidList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LidListContext* lidList();

  class  VidTupleContext : public antlr4::ParserRuleContext {
  public:
    VidTupleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VidContext *> vid();
    VidContext* vid(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VidTupleContext* vidTuple();

  class  VidTupleListContext : public antlr4::ParserRuleContext {
  public:
    VidTupleListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VidTupleContext *vidTuple();
    VidTupleListContext *vidTupleList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VidTupleListContext* vidTupleList();

  class  AttrEqItemContext : public antlr4::ParserRuleContext {
  public:
    AttrEqItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeNameContext *attributeName();
    ValueContext *value();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttrEqItemContext* attrEqItem();

  class  AttrEqItemListContext : public antlr4::ParserRuleContext {
  public:
    AttrEqItemListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttrEqItemContext *attrEqItem();
    AttrEqItemListContext *attrEqItemList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttrEqItemListContext* attrEqItemList();

  class  AttributeNameListContext : public antlr4::ParserRuleContext {
  public:
    AttributeNameListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeNameContext *attributeName();
    AttributeNameListContext *attributeNameList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeNameListContext* attributeNameList();

  class  AttrEqItemUncertainContext : public antlr4::ParserRuleContext {
  public:
    AttrEqItemUncertainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AttributeNameContext *> attributeName();
    AttributeNameContext* attributeName(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttrEqItemUncertainContext* attrEqItemUncertain();

  class  AttrEqItemListUncertainContext : public antlr4::ParserRuleContext {
  public:
    AttrEqItemListUncertainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttrEqItemUncertainContext *attrEqItemUncertain();
    AttrEqItemListUncertainContext *attrEqItemListUncertain();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttrEqItemListUncertainContext* attrEqItemListUncertain();

  class  CompareOperatorContext : public antlr4::ParserRuleContext {
  public:
    CompareOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    CompareOperatorContext() = default;
    void copyFrom(CompareOperatorContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LTContext : public CompareOperatorContext {
  public:
    LTContext(CompareOperatorContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GTEContext : public CompareOperatorContext {
  public:
    GTEContext(CompareOperatorContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NEQContext : public CompareOperatorContext {
  public:
    NEQContext(CompareOperatorContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LTEContext : public CompareOperatorContext {
  public:
    LTEContext(CompareOperatorContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EQContext : public CompareOperatorContext {
  public:
    EQContext(CompareOperatorContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GTContext : public CompareOperatorContext {
  public:
    GTContext(CompareOperatorContext *ctx);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  CompareOperatorContext* compareOperator();

  class  CalculateOperatorContext : public antlr4::ParserRuleContext {
  public:
    CalculateOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CalculateOperatorContext* calculateOperator();

  class  LogicFlagBiContext : public antlr4::ParserRuleContext {
  public:
    LogicFlagBiContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_and();
    antlr4::tree::TerminalNode *K_or();
    antlr4::tree::TerminalNode *K_arrow();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicFlagBiContext* logicFlagBi();

  class  LogicFlagNotContext : public antlr4::ParserRuleContext {
  public:
    LogicFlagNotContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_not();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicFlagNotContext* logicFlagNot();

  class  FirstOrderStatContext : public antlr4::ParserRuleContext {
  public:
    FirstOrderStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FirstOrderUnitContext *firstOrderUnit();
    BracketLeftContext *bracketLeft();
    std::vector<FirstOrderStatContext *> firstOrderStat();
    FirstOrderStatContext* firstOrderStat(size_t i);
    BracketRightContext *bracketRight();
    LogicFlagNotContext *logicFlagNot();
    antlr4::tree::TerminalNode *K_true();
    antlr4::tree::TerminalNode *K_false();
    LogicFlagBiContext *logicFlagBi();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FirstOrderStatContext* firstOrderStat();
  FirstOrderStatContext* firstOrderStat(int precedence);
  class  FirstOrderUnitContext : public antlr4::ParserRuleContext {
  public:
    FirstOrderUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncStatContext *funcStat();
    ExistStatContext *existStat();
    ForeachStatContext *foreachStat();
    CompareValStatContext *compareValStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FirstOrderUnitContext* firstOrderUnit();

  class  ExistStatContext : public antlr4::ParserRuleContext {
  public:
    ExistStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_exist();
    VarListContext *varList();
    FirstOrderStatContext *firstOrderStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExistStatContext* existStat();

  class  ForeachStatContext : public antlr4::ParserRuleContext {
  public:
    ForeachStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_foreach();
    VarListContext *varList();
    FirstOrderStatContext *firstOrderStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForeachStatContext* foreachStat();

  class  CompareStatContext : public antlr4::ParserRuleContext {
  public:
    CompareStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CompareUnitContext *compareUnit();
    BracketLeftContext *bracketLeft();
    std::vector<CompareStatContext *> compareStat();
    CompareStatContext* compareStat(size_t i);
    BracketRightContext *bracketRight();
    antlr4::tree::TerminalNode *K_true();
    antlr4::tree::TerminalNode *K_false();
    CalculateOperatorContext *calculateOperator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompareStatContext* compareStat();
  CompareStatContext* compareStat(int precedence);
  class  CompareUnitContext : public antlr4::ParserRuleContext {
  public:
    CompareUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ValueContext *value();
    AttributeNameContext *attributeName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompareUnitContext* compareUnit();

  class  CompareValStatContext : public antlr4::ParserRuleContext {
  public:
    CompareValStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CompareStatContext *> compareStat();
    CompareStatContext* compareStat(size_t i);
    CompareOperatorContext *compareOperator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompareValStatContext* compareValStat();

  class  FuncStatContext : public antlr4::ParserRuleContext {
  public:
    FuncStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncNameContext *funcName();
    ObjectListContext *objectList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncStatContext* funcStat();

  class  FuncNameContext : public antlr4::ParserRuleContext {
  public:
    FuncNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_equal();
    antlr4::tree::TerminalNode *K_vertex();
    antlr4::tree::TerminalNode *K_edge();
    antlr4::tree::TerminalNode *K_complete();
    antlr4::tree::TerminalNode *K_unique();
    antlr4::tree::TerminalNode *K_hasedge();
    antlr4::tree::TerminalNode *K_sizegeq();
    antlr4::tree::TerminalNode *K_graphequal();
    antlr4::tree::TerminalNode *K_graphinset();
    antlr4::tree::TerminalNode *K_subgraph();
    antlr4::tree::TerminalNode *K_inducedsub();
    antlr4::tree::TerminalNode *K_connect();
    antlr4::tree::TerminalNode *K_clique();
    antlr4::tree::TerminalNode *K_tdensesub();
    antlr4::tree::TerminalNode *K_track();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncNameContext* funcName();

  class  ObjectContext : public antlr4::ParserRuleContext {
  public:
    ObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParaItemContext *paraItem();
    IndexIntContext *indexInt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectContext* object();

  class  ObjectListContext : public antlr4::ParserRuleContext {
  public:
    ObjectListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ObjectContext *object();
    ObjectListContext *objectList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectListContext* objectList();

  class  VarListContext : public antlr4::ParserRuleContext {
  public:
    VarListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableNameContext *variableName();
    VarListContext *varList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarListContext* varList();

  class  BracketLeftContext : public antlr4::ParserRuleContext {
  public:
    BracketLeftContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BracketLeftContext* bracketLeft();

  class  BracketRightContext : public antlr4::ParserRuleContext {
  public:
    BracketRightContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BracketRightContext* bracketRight();

  class  DdlStatementContext : public antlr4::ParserRuleContext {
  public:
    DdlStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CreateSchemaStatContext *createSchemaStat();
    CreateGsetStatContext *createGsetStat();
    LoadGsetStatContext *loadGsetStat();
    CreateGStatContext *createGStat();
    LoadGStatContext *loadGStat();
    DropStatContext *dropStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DdlStatementContext* ddlStatement();

  class  CreateSchemaStatContext : public antlr4::ParserRuleContext {
  public:
    CreateSchemaStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_create();
    antlr4::tree::TerminalNode *K_schema();
    SchemaidContext *schemaid();
    SchemaStatementContext *schemaStatement();
    antlr4::tree::TerminalNode *K_file();
    FilenameContext *filename();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateSchemaStatContext* createSchemaStat();

  class  SchemaStatementContext : public antlr4::ParserRuleContext {
  public:
    SchemaStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SchemaNodeListContext *schemaNodeList();
    SchemaEdgeListContext *schemaEdgeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaStatementContext* schemaStatement();

  class  SchemaNodeListContext : public antlr4::ParserRuleContext {
  public:
    SchemaNodeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SchemaNodeContext *schemaNode();
    SchemaNodeListContext *schemaNodeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaNodeListContext* schemaNodeList();

  class  SchemaEdgeListContext : public antlr4::ParserRuleContext {
  public:
    SchemaEdgeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SchemaEdgeContext *schemaEdge();
    SchemaEdgeListContext *schemaEdgeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaEdgeListContext* schemaEdgeList();

  class  SchemaNodeContext : public antlr4::ParserRuleContext {
  public:
    SchemaNodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LabelNameContext *labelName();
    SchemaAttrListContext *schemaAttrList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaNodeContext* schemaNode();

  class  SchemaAttrListContext : public antlr4::ParserRuleContext {
  public:
    SchemaAttrListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LabelNameContext *labelName();
    TypeNameContext *typeName();
    SchemaAttrListContext *schemaAttrList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaAttrListContext* schemaAttrList();

  class  SchemaEdgeContext : public antlr4::ParserRuleContext {
  public:
    SchemaEdgeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LabelNameContext *labelName();
    EdgeLinkageListContext *edgeLinkageList();
    SchemaAttrListContext *schemaAttrList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaEdgeContext* schemaEdge();

  class  EdgeLinkageListContext : public antlr4::ParserRuleContext {
  public:
    EdgeLinkageListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LabelNameContext *> labelName();
    LabelNameContext* labelName(size_t i);
    EdgeLinkageListContext *edgeLinkageList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EdgeLinkageListContext* edgeLinkageList();

  class  LabelNameContext : public antlr4::ParserRuleContext {
  public:
    LabelNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LabelNameContext* labelName();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DataTypeContext *dataType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  SchemaItemContext : public antlr4::ParserRuleContext {
  public:
    SchemaItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SchemaTypeListContext *schemaTypeList();
    SchemaidContext *schemaid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaItemContext* schemaItem();

  class  CreateGsetStatContext : public antlr4::ParserRuleContext {
  public:
    CreateGsetStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_create();
    antlr4::tree::TerminalNode *K_graphset();
    GsidContext *gsid();
    GidListContext *gidList();
    SchemaItemContext *schemaItem();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateGsetStatContext* createGsetStat();

  class  CreateGStatContext : public antlr4::ParserRuleContext {
  public:
    CreateGStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_create();
    antlr4::tree::TerminalNode *K_graph();
    GidContext *gid();
    SchemaItemContext *schemaItem();
    CreateGFileStatContext *createGFileStat();
    CreateGForStatContext *createGForStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateGStatContext* createGStat();

  class  CreateGFileStatContext : public antlr4::ParserRuleContext {
  public:
    CreateGFileStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_from();
    antlr4::tree::TerminalNode *K_file();
    FilenamelistContext *filenamelist();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateGFileStatContext* createGFileStat();

  class  CreateGForStatContext : public antlr4::ParserRuleContext {
  public:
    CreateGForStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_for();
    GsidContext *gsid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CreateGForStatContext* createGForStat();

  class  LoadGsetStatContext : public antlr4::ParserRuleContext {
  public:
    LoadGsetStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_load();
    antlr4::tree::TerminalNode *K_graphset();
    GsidContext *gsid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LoadGsetStatContext* loadGsetStat();

  class  LoadGStatContext : public antlr4::ParserRuleContext {
  public:
    LoadGStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_load();
    antlr4::tree::TerminalNode *K_graph();
    GidContext *gid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LoadGStatContext* loadGStat();

  class  DropStatContext : public antlr4::ParserRuleContext {
  public:
    DropStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DropGsetStatContext *dropGsetStat();
    DropGStatContext *dropGStat();
    DropSchemaStatContext *dropSchemaStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropStatContext* dropStat();

  class  DropGsetStatContext : public antlr4::ParserRuleContext {
  public:
    DropGsetStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_drop();
    antlr4::tree::TerminalNode *K_graphset();
    GsidContext *gsid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropGsetStatContext* dropGsetStat();

  class  DropGStatContext : public antlr4::ParserRuleContext {
  public:
    DropGStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_drop();
    antlr4::tree::TerminalNode *K_graph();
    GidContext *gid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropGStatContext* dropGStat();

  class  DropSchemaStatContext : public antlr4::ParserRuleContext {
  public:
    DropSchemaStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_drop();
    antlr4::tree::TerminalNode *K_schema();
    SchemaidContext *schemaid();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropSchemaStatContext* dropSchemaStat();

  class  SchemaTypeListContext : public antlr4::ParserRuleContext {
  public:
    SchemaTypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LidContext *lid();
    SchemaAttributeItemContext *schemaAttributeItem();
    SchemaTypeListContext *schemaTypeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaTypeListContext* schemaTypeList();

  class  SchemaAttributeItemContext : public antlr4::ParserRuleContext {
  public:
    SchemaAttributeItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttrItemContext *attrItem();
    SchemaAttributeItemContext *schemaAttributeItem();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaAttributeItemContext* schemaAttributeItem();

  class  AttrItemContext : public antlr4::ParserRuleContext {
  public:
    AttrItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AttributeNameContext *attributeName();
    DataTypeContext *dataType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttrItemContext* attrItem();

  class  DataTypeContext : public antlr4::ParserRuleContext {
  public:
    DataTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *K_int();
    antlr4::tree::TerminalNode *K_integer();
    antlr4::tree::TerminalNode *K_float();
    antlr4::tree::TerminalNode *K_double();
    antlr4::tree::TerminalNode *K_char();
    antlr4::tree::TerminalNode *K_string();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DataTypeContext* dataType();

  class  AttributeNameContext : public antlr4::ParserRuleContext {
  public:
    AttributeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AttributeNameContext* attributeName();

  class  GsidContext : public antlr4::ParserRuleContext {
  public:
    GsidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GsidContext* gsid();

  class  GidContext : public antlr4::ParserRuleContext {
  public:
    GidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GidContext* gid();

  class  VidContext : public antlr4::ParserRuleContext {
  public:
    VidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VidContext* vid();

  class  EidContext : public antlr4::ParserRuleContext {
  public:
    EidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EidContext* eid();

  class  LidContext : public antlr4::ParserRuleContext {
  public:
    LidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LidContext* lid();

  class  FilenameContext : public antlr4::ParserRuleContext {
  public:
    FilenameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TEXT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilenameContext* filename();

  class  SchemaidContext : public antlr4::ParserRuleContext {
  public:
    SchemaidContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SchemaidContext* schemaid();

  class  VariableNameContext : public antlr4::ParserRuleContext {
  public:
    VariableNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableNameContext* variableName();

  class  IndexIntContext : public antlr4::ParserRuleContext {
  public:
    IndexIntContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_NUMBER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexIntContext* indexInt();

  class  ParaItemContext : public antlr4::ParserRuleContext {
  public:
    ParaItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_NUMBER();
    antlr4::tree::TerminalNode *NOT_INTEGER_NUMBER();
    antlr4::tree::TerminalNode *TEXT();
    antlr4::tree::TerminalNode *NAME_STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParaItemContext* paraItem();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool queryStatSempred(QueryStatContext *_localctx, size_t predicateIndex);
  bool firstOrderStatSempred(FirstOrderStatContext *_localctx, size_t predicateIndex);
  bool compareStatSempred(CompareStatContext *_localctx, size_t predicateIndex);

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

