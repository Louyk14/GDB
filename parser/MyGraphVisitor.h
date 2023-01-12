//
// Created by Henry Fox on 2019-12-13.
//

#ifndef ANTLR_GRAPHDB_MYGRAPHVISITOR_H
#define ANTLR_GRAPHDB_MYGRAPHVISITOR_H

#include <unordered_map>
#include <string>
#include "GraphDBVisitor.h"
#include "definations.h"

class MyGraphVisitor : public GraphDBVisitor {
	antlrcpp::Any visitVidList(GraphDBParser::VidListContext *ctx) override {
		VIDList ans;
		ans.push_back(make_pair(visit(ctx->vid()).as<VID>(), visit(ctx->lid()).as<LID>()));
		if (ctx->vidList()) {
			VIDList temp(visit(ctx->vidList()).as<VIDList>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitVidTuple(GraphDBParser::VidTupleContext *ctx) override {
		VID a = visit(ctx->vid(0)).as<VID>(), b = visit(ctx->vid(1)).as<VID>();
		return antlrcpp::Any(make_pair(a, b));
	}

	antlrcpp::Any visitVidTupleList(GraphDBParser::VidTupleListContext *context) final;

	//antlrcpp::Any visitEidList(GraphDBParser::EidListContext *context) final;

	antlrcpp::Any visitLidList(GraphDBParser::LidListContext *context) final;

	//antlrcpp::Any visitAttributeConsItem(GraphDBParser::AttributeConsItemContext *context) final;

	//antlrcpp::Any visitAttributeConsItemList(GraphDBParser::AttributeConsItemListContext *context) final;

	antlrcpp::Any visitAttributeNameList(GraphDBParser::AttributeNameListContext *context) final;

	//antlrcpp::Any visitAttributeNameWithEnt(GraphDBParser::AttributeNameWithEntContext *context) final;

	//antlrcpp::Any visitAttributeConsCertain(GraphDBParser::AttributeConsCertainContext *context) final;

	//antlrcpp::Any visitAttributeConsUncertain(GraphDBParser::AttributeConsUncertainContext *context) final;

	//antlrcpp::Any visitAttributeConsItemWithEnt(GraphDBParser::AttributeConsItemWithEntContext *context) final;

	antlrcpp::Any visitGT(GraphDBParser::GTContext *context) final;

	antlrcpp::Any visitLT(GraphDBParser::LTContext *context) final;

	antlrcpp::Any visitGTE(GraphDBParser::GTEContext *context) final;

	antlrcpp::Any visitLTE(GraphDBParser::LTEContext *context) final;

	antlrcpp::Any visitEQ(GraphDBParser::EQContext *context) final;

	antlrcpp::Any visitNEQ(GraphDBParser::NEQContext *context) final;

	//antlrcpp::Any visitAND(GraphDBParser::ANDContext *context) final;

	//antlrcpp::Any visitOR(GraphDBParser::ORContext *context) final;

	//antlrcpp::Any visitGraph(GraphDBParser::GraphContext *context) final;

	antlrcpp::Any visitVertexInfo(GraphDBParser::VertexInfoContext *ctx) override {
		if (ctx->vidList()) {
			return visit(ctx->vidList()).as<vector<pair<string, string>>>();
		}
		else {
			vector<pair<string, string>> temp;
			return temp;
		}
		return visitChildren(ctx);
	}

	//antlrcpp::Any visitEdgeItem(GraphDBParser::EdgeItemContext *context) final;

	antlrcpp::Any visitEdgeList(GraphDBParser::EdgeListContext *ctx) override {
		unordered_map<string, EdgeInfo*> ans;
		pair<string, string> tup(visit(ctx->edge()).as<pair<string, string>>());
		string label = visit(ctx->lid()).as<string>();
		EdgeInfo* edgeinfo = new EdgeInfo(tup.first, tup.second, label);
		
		string ealias = tup.first + " " + tup.second;
		if (ctx->eid()) {
			ealias = visit(ctx->eid()).as<string>();
		}

		ans[ealias] = edgeinfo;

		if (ctx->edgeList()) {
			unordered_map<string, EdgeInfo*> temp(visit(ctx->edgeList()).as<unordered_map<string, EdgeInfo*>>());
			ans.insert(temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitEdgeInfo(GraphDBParser::EdgeInfoContext *ctx) override {
		if (ctx->edgeList()) {
			return visit(ctx->edgeList()).as<unordered_map<string, EdgeInfo*>>();
		}
		else {
			auto temp = make_pair(vector<pair<pair<string, string>, string>>(), unordered_map<string, int>());
			return temp;
		}
	}

	//antlrcpp::Any visitEdgeLabel(GraphDBParser::EdgeLabelContext *context) final;

	antlrcpp::Any visitAttributeInfo(GraphDBParser::AttributeInfoContext *ctx) override {
		AttributeList nodeattr;
		AttributeList edgeattr;
		
		if (ctx->nodeAttributeInfo()) {
			nodeattr = visit(ctx->nodeAttributeInfo()).as<AttributeList>();
		}
		if (ctx->edgeAttributeInfo()) {
			edgeattr = visit(ctx->edgeAttributeInfo()).as<AttributeList>();
		}

		AttributeInfo attrinfo(nodeattr, edgeattr);
		return attrinfo;
	}

	//antlrcpp::Any visitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *context) final;

	antlrcpp::Any visitNodeAttributeList(GraphDBParser::NodeAttributeListContext *ctx) override {
		AttributeList ans;
		ans.push_back(visit(ctx->nodeAttributeItem()).as<AttributeListItem>());
		if (ctx->nodeAttributeList()) {
			AttributeList temp(visit(ctx->nodeAttributeList()).as<AttributeList>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitNodeAttributeInfo(GraphDBParser::NodeAttributeInfoContext *ctx) override {
		if (ctx->nodeAttributeList()) {
			return visit(ctx->nodeAttributeList()).as<AttributeList>();
		}
		return AttributeList();
	}

	//antlrcpp::Any visitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *context) final;

	antlrcpp::Any visitEdgeAttributeList(GraphDBParser::EdgeAttributeListContext *ctx) override {
		AttributeList ans;
		ans.push_back(visit(ctx->edgeAttributeItem()).as<AttributeListItem>());
		if (ctx->edgeAttributeList()) {
			AttributeList temp(visit(ctx->edgeAttributeList()).as<AttributeList>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitEdgeAttributeInfo(GraphDBParser::EdgeAttributeInfoContext *ctx) override {
		if (ctx->edgeAttributeList()) {
			return visit(ctx->edgeAttributeList()).as<AttributeList>();
		}
		return AttributeList();
	}

	//antlrcpp::Any visitStructureConstraintInfo(GraphDBParser::StructureConstraintInfoContext *context) final;

	//antlrcpp::Any visitAttributeConstraintItem(GraphDBParser::AttributeConstraintItemContext *context) final;

	//antlrcpp::Any visitAttributeConstraintList(GraphDBParser::AttributeConstraintListContext *context) final;

	//antlrcpp::Any visitAttributeConstraintInfo(GraphDBParser::AttributeConstraintInfoContext *context) final;

	//antlrcpp::Any visitConstraintGraph(GraphDBParser::ConstraintGraphContext *context) final;

	//antlrcpp::Any visitOperationStatement(GraphDBParser::OperationStatementContext *context) final;

	//antlrcpp::Any visitOperationUnit(GraphDBParser::OperationUnitContext *context) final;

	//antlrcpp::Any visitUnionStatement(GraphDBParser::UnionStatementContext *context) final;

	//antlrcpp::Any visitMinusStatement(GraphDBParser::MinusStatementContext *context) final;

	//antlrcpp::Any visitSchemeItem(GraphDBParser::SchemeItemContext *context) final;

	//antlrcpp::Any visitSchemeList(GraphDBParser::SchemeListContext *context) final;

	//antlrcpp::Any visitAttrProjStatement(GraphDBParser::AttrProjStatementContext *context) final;

	//antlrcpp::Any visitPowerSetStatement(GraphDBParser::PowerSetStatementContext *context) final;

	//antlrcpp::Any visitJoinConditionList(GraphDBParser::JoinConditionListContext *context) final;

	//antlrcpp::Any visitOne2oneJoinStatement(GraphDBParser::One2oneJoinStatementContext *context) final;

	//antlrcpp::Any visitMonoSelectionStatement(GraphDBParser::MonoSelectionStatementContext *context) final;

	//antlrcpp::Any visitFilterStatement(GraphDBParser::FilterStatementContext *context) final;

	//antlrcpp::Any visitReduceStatement(GraphDBParser::ReduceStatementContext *context) final;

	//antlrcpp::Any visitMaximizeStatement(GraphDBParser::MaximizeStatementContext *context) final;

	//antlrcpp::Any visitSourceGraph(GraphDBParser::SourceGraphContext *context) final;

	//antlrcpp::Any visitExactCondition(GraphDBParser::ExactConditionContext *context) final;

	//antlrcpp::Any visitNameGraph(GraphDBParser::NameGraphContext *context) final;

	//antlrcpp::Any visitQueryStatement(GraphDBParser::QueryStatementContext *context) final;

	//antlrcpp::Any visitAttributeName(GraphDBParser::AttributeNameContext *context) final;

	//antlrcpp::Any visitGid(GraphDBParser::GidContext *context) final;

	//antlrcpp::Any visitVid(GraphDBParser::VidContext *context) final;

	//antlrcpp::Any visitEid(GraphDBParser::EidContext *context) final;

	//antlrcpp::Any visitLid(GraphDBParser::LidContext *context) final;

	antlrcpp::Any visitEntId(GraphDBParser::EntIdContext *context) final;

	//antlrcpp::Any visitEasyVertex(GraphDBParser::EasyVertexContext *context) final;

	//antlrcpp::Any visitEasyEdge(GraphDBParser::EasyEdgeContext *context) final;

	//antlrcpp::Any visitEasyEdgeItem(GraphDBParser::EasyEdgeItemContext *context) final;

	//antlrcpp::Any visitEasyEdgeInfo(GraphDBParser::EasyEdgeInfoContext *context) final;

	//antlrcpp::Any visitEasyGraphPartList(GraphDBParser::EasyGraphPartListContext *context) final;

	//antlrcpp::Any visitEasyGraph(GraphDBParser::EasyGraphContext *context) final;

	antlrcpp::Any visitStatement(GraphDBParser::StatementContext *ctx) override {
		if (ctx->ddlStatement()) {
			return antlrcpp::Any(Statement(visit(ctx->ddlStatement()).as<DDLStatement>()));
		}
		else if (ctx->dmlStatement()) {
			return antlrcpp::Any(Statement(visit(ctx->dmlStatement()).as<DMLStatement>()));
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitDmlStatement(GraphDBParser::DmlStatementContext *ctx) override {
		if (ctx->queryStat()) {
			return antlrcpp::Any(DMLStatement(visit(ctx->queryStat()).as<QueryStatement>()));
		}
		else if (ctx->insertStat()) {
			return antlrcpp::Any(DMLStatement(visit(ctx->insertStat()).as<InsertStatement>()));
		}
		else if (ctx->removeStat()) {
			return antlrcpp::Any(DMLStatement(visit(ctx->removeStat()).as<RemoveStatement>()));
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitDropStat(GraphDBParser::DropStatContext *ctx) override {
		string ans = "";
		if (ctx->dropGsetStat()) {
			ans = visit(ctx->dropGsetStat()).as<string>();
			DropStatement ds(DropStatType::DROP_GSET_TYPE, ans);
			return ds;
		}
		else if (ctx->dropGStat()) {
			ans = visit(ctx->dropGStat()).as<string>();
			DropStatement ds(DropStatType::DROP_GRAPH_TYPE, ans);
			return ds;
		}
		else if (ctx->dropSchemaStat()) {
			ans = visit(ctx->dropSchemaStat()).as<string>();
			DropStatement ds(DropStatType::DROP_SCHEMA_TYPE, ans);
			return ds;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitInsertStat(GraphDBParser::InsertStatContext *ctx) override {
		if (ctx->insertGsetStat()) {
			InsertGSetStat igsstat(visit(ctx->insertGsetStat()).as<InsertGSetStat>());
			InsertStatement istat(igsstat);
			return istat;
		}
		else if (ctx->insertGStat()) {
			InsertGraphStat igs(visit(ctx->insertGStat()).as<InsertGraphStat>());
			InsertStatement istat(igs);
			return istat;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitRemoveStat(GraphDBParser::RemoveStatContext *ctx) override {
		if (ctx->removeGsetStat()) {
			RemoveGSetStat rgsstat(visit(ctx->removeGsetStat()).as<RemoveGSetStat>());
			RemoveStatement rstat(rgsstat);
			return rstat;
		}
		else if (ctx->removeGStat()) {
			RemoveGraphStat rgs(visit(ctx->removeGStat()).as<RemoveGraphStat>());
			RemoveStatement rstat(rgs);
			return rstat;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitDropGsetStat(GraphDBParser::DropGsetStatContext *ctx) override {
		string ans = visit(ctx->gsid()).as<string>();
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitDropGStat(GraphDBParser::DropGStatContext *ctx) override {
		string ans = visit(ctx->gid()).as<string>();
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitDropSchemaStat(GraphDBParser::DropSchemaStatContext *ctx) override {
		string ans = visit(ctx->schemaid()).as<string>();
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitInsertGsetStat(GraphDBParser::InsertGsetStatContext *ctx) override {
		string gsid = visit(ctx->gsid()).as<string>();
		vector<string> gidlist(visit(ctx->gidList()).as<vector<string>>());
		InsertGSetStat igsstat(gsid, gidlist);
		return igsstat;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitInsertGStat(GraphDBParser::InsertGStatContext *ctx) override {		
		if (ctx->graph()) {
			string aimid = visit(ctx->gid(0)).as<string>();
			GraphStat gstat(visit(ctx->graph()).as<GraphStat>());
			InsertGraphStat igs(gstat, aimid);
			return igs;
		}
		else if (ctx->K_file()) {

		}
		else {
			
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitGraphNameItem(GraphDBParser::GraphNameItemContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitGraphNameList(GraphDBParser::GraphNameListContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitRemoveGsetStat(GraphDBParser::RemoveGsetStatContext *ctx) override {
		string gsid = visit(ctx->gsid()).as<string>();
		vector<string> gidlist(visit(ctx->gidList()).as<vector<string>>());
		RemoveGSetStat rgsstat(gsid, gidlist);
		return rgsstat;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitRemoveGStat(GraphDBParser::RemoveGStatContext *ctx) override {
		if (ctx->vertexInfo()) {
			string aimid = visit(ctx->gid(0)).as<string>();
			vector<pair<string, string>> vid(visit(ctx->vertexInfo()).as<vector<pair<string, string>>>());
			unordered_map<string, EdgeInfo*> edge(visit(ctx->edgeInfo()).as<unordered_map<string, EdgeInfo*>>());

			GraphStat gstat(vid, edge);
			
			RemoveGraphStat rgs(gstat, aimid);
			return rgs;
		}
		else if (ctx->K_file()) {

		}
		else {

		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitUpdateStat(GraphDBParser::UpdateStatContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitGraph(GraphDBParser::GraphContext *ctx) override {
		vector<pair<string, string>> vid(visit(ctx->vertexInfo()).as<vector<pair<string, string>>>());
		unordered_map<string, EdgeInfo*> edge(visit(ctx->edgeInfo()).as<unordered_map<string, EdgeInfo*>>());

		AttributeInfo attrinfo;
		
		if (ctx->attributeInfo()) {
			attrinfo = visit(ctx->attributeInfo()).as<AttributeInfo>();
		}
		else {
			
		}

		GraphStat gstat(vid, edge, attrinfo.nodeAttr, attrinfo.edgeAttr);
		return gstat;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitGraphItem(GraphDBParser::GraphItemContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitGraphList(GraphDBParser::GraphListContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitGraphset(GraphDBParser::GraphsetContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitEdge(GraphDBParser::EdgeContext *ctx) override {
		return visit(ctx->vidTuple()).as<pair<string, string>>();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitNameGraph(GraphDBParser::NameGraphContext *ctx) override {
		if (ctx->K_as()) {
			string str = ctx->gsid()->getText();
			return antlrcpp::Any(GraphSetAlias(str));
		}
		else {
			return antlrcpp::Any(GraphSetAlias());
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitQueryStat(GraphDBParser::QueryStatContext *ctx) override {
		if (ctx->K_select()) {
			bool rword = visit(ctx->reduceWord()).as<bool>();
			bool mword = visit(ctx->maximalWord()).as<bool>();
			GraphSetAlias ng = visit(ctx->nameGraph()).as<GraphSetAlias>();
			FromCondition fcondition = visit(ctx->fromCondition()).as<FromCondition>();
			WhereCondition wcondition = visit(ctx->whereCondition()).as<WhereCondition>();
			SelectStatement select(rword, mword, ng, fcondition, wcondition);
			QueryStatement queryStat(select);
            return queryStat;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitMultipleOperator(GraphDBParser::MultipleOperatorContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitProjectCondition(GraphDBParser::ProjectConditionContext *ctx) override {
		if (ctx->getText() == "*") {
            ProjectCondition projectCond(true); 
			return projectCond;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitFromCondition(GraphDBParser::FromConditionContext *ctx) override {
		if (ctx->operatorGSet()) {
			FromCondition fromcond(visit(ctx->operatorGSet()).as<OperatorGSet>());
            return fromcond;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitAlignConditionList(GraphDBParser::AlignConditionListContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitAlignCondition(GraphDBParser::AlignConditionContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitWhereCondition(GraphDBParser::WhereConditionContext *ctx) override {
		if (ctx->K_file()) {
			vector<string> filenamelist(visit(ctx->filenamelist()).as<vector<string>>());
			if (filenamelist.size() == 1) {
				WhereCondition wherecond(filenamelist[0]);
				return wherecond;
			}
			else {
				WhereCondition wherecond(filenamelist);
				return wherecond;
			}
		}
		else {
			FirstOrderStat fos(visit(ctx->firstOrderStat()).as<FirstOrderStat>());
			WhereCondition wherecond(fos);
			return wherecond;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitMapCondition(GraphDBParser::MapConditionContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitReduceWord(GraphDBParser::ReduceWordContext *ctx) override {
		if (ctx->getText().empty())
			return false;
		else
			return true;
		return visitChildren(ctx);
	}

	antlrcpp::Any visitMaximalWord(GraphDBParser::MaximalWordContext *ctx) override {
		if (ctx->getText().empty())
			return false;
		else
			return true;
		return visitChildren(ctx);
	}

	antlrcpp::Any visitOperationStatement(GraphDBParser::OperationStatementContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitOperatorGSet(GraphDBParser::OperatorGSetContext *ctx) override {
		if (ctx->gsid()) {
			string str = ctx->gsid()->getText();
            OperatorGSet og(str);
			return og;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitSchemaNameItem(GraphDBParser::SchemaNameItemContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitSchemaNameList(GraphDBParser::SchemaNameListContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitProductStatement(GraphDBParser::ProductStatementContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitJoinStatement(GraphDBParser::JoinStatementContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitValue(GraphDBParser::ValueContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitAttrEqItem(GraphDBParser::AttrEqItemContext *ctx) override {
		return make_pair(visit(ctx->attributeName()).as<string>(), visit(ctx->value()).as<string>());
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitAttrEqItemList(GraphDBParser::AttrEqItemListContext *ctx) override {
		vector<pair<string, string>> ans;
		pair<string, string> attritem(visit(ctx->attrEqItem()).as<pair<string, string>>());
		ans.push_back(attritem);
		if (ctx->attrEqItemList()) {
			vector<pair<string, string>> temp(visit(ctx->attrEqItemList()).as<vector<pair<string, string>>>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitAttrEqItemUncertain(GraphDBParser::AttrEqItemUncertainContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitAttrEqItemListUncertain(GraphDBParser::AttrEqItemListUncertainContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitCalculateOperator(GraphDBParser::CalculateOperatorContext *ctx) override {
		string op = ctx->getText();
		if (op == "+") {
			return CALCULATE_OPERATOR_ADD;
		}
		else if (op == "-") {
			return CALCULATE_OPERATOR_MINUS;
		}
		else if (op == "*") {
			return CALCULATE_OPERATOR_MULTIPLE;
		}
		else if (op == "/") {
			return CALCULATE_OPERATOR_DIVIDE;
		}

		return visitChildren(ctx);
	}

	antlrcpp::Any visitLogicFlagBi(GraphDBParser::LogicFlagBiContext *ctx) override {
		if (ctx->K_and()) {
			return LogicFlagBiType::LOGIC_AND;
		}
		else if (ctx->K_or()) {
			return LogicFlagBiType::LOGIC_OR;
		}
		else if (ctx->K_arrow()) {
			return LogicFlagBiType::LOGIC_ARROW;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitLogicFlagNot(GraphDBParser::LogicFlagNotContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitFirstOrderStat(GraphDBParser::FirstOrderStatContext *ctx) override {
		if (ctx->firstOrderUnit()) {
			FirstOrderUnit fou(visit(ctx->firstOrderUnit()).as<FirstOrderUnit>());
			return FirstOrderStat(fou);
		}
		else if (ctx->bracketLeft()) {
			FirstOrderStat fos_in(visit(ctx->firstOrderStat(0)).as<FirstOrderStat>());
			FirstOrderStat fos(fos_in, FIRST_ORDER_STAT_BRAC);
			return fos;
		}
		else if (ctx->logicFlagNot()) {
			FirstOrderStat fos_in(visit(ctx->firstOrderStat(0)).as<FirstOrderStat>());
			FirstOrderStat fos(fos_in, FIRST_ORDER_STAT_NOT);
			return fos;
		}
		else if (ctx->logicFlagBi()) {
			FirstOrderStat fos_1eft(visit(ctx->firstOrderStat(0)).as<FirstOrderStat>());
			LogicFlagBiType logicbi(visit(ctx->logicFlagBi()).as<LogicFlagBiType>());
			FirstOrderStat fos_right(visit(ctx->firstOrderStat(1)).as<FirstOrderStat>());
			FirstOrderStat fos(fos_1eft, logicbi, fos_right);
			return fos;
		}
		else if (ctx->K_true()) {
			FirstOrderStat fos(FIRST_ORDER_STAT_TRUE);
			return fos;
		}
		else if (ctx->K_false()) {
			FirstOrderStat fos(FIRST_ORDER_STAT_FALSE);
			return fos;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitFirstOrderUnit(GraphDBParser::FirstOrderUnitContext *ctx) override {
		if (ctx->funcStat()) {
			FuncStat fs(visit(ctx->funcStat()).as<FuncStat>());
			return FirstOrderUnit(fs);
		}
		else if (ctx->existStat()) {
			ExistStat es(visit(ctx->existStat()).as<ExistStat>());
			return FirstOrderUnit(es);
		}
		else if (ctx->compareValStat()) {
			CompareValStat cvs(visit(ctx->compareValStat()).as<CompareValStat>());
			return FirstOrderUnit(cvs);
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitExistStat(GraphDBParser::ExistStatContext *ctx) override {
		vector<string> varlist(visit(ctx->varList()).as<vector<string>>());
		FirstOrderStat fos(visit(ctx->firstOrderStat()).as<FirstOrderStat>());
		ExistStat es(varlist, fos);
		return es;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitForeachStat(GraphDBParser::ForeachStatContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitCompareStat(GraphDBParser::CompareStatContext *ctx) override {
		if (ctx->compareUnit()) {
			CompareUnit cu(visit(ctx->compareUnit()).as<CompareUnit>());
			CompareStat cs(cu);
			return cs;
		}
		else if (ctx->calculateOperator()) {
			CompareStat cs_left(visit(ctx->compareStat(0)).as<CompareStat>());
			CalculateOperatorType cot(visit(ctx->calculateOperator()).as<CalculateOperatorType>());
			CompareStat cs_right(visit(ctx->compareStat(1)).as<CompareStat>());
			CompareStat cs(cs_left, cot, cs_right);
			return cs;
		}
		else if (ctx->bracketLeft()) {
			CompareStat cs_in(visit(ctx->compareStat(0)).as<CompareStat>());
			CompareStat cs(cs_in, COMPARE_STAT_BRAC);
			return cs;
		}
		else if (ctx->K_true()) {
			CompareStat cs(COMPARE_STAT_TRUE);
			return cs;
		}
		else if (ctx->K_false()) {
			CompareStat cs(COMPARE_STAT_FALSE);
			return cs;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitCompareUnit(GraphDBParser::CompareUnitContext *ctx) override {
		if (ctx->value()) {
			CompareUnitType cut(COMPARE_UNIT_VALUE);
			string unit(visit(ctx->value()).as<string>());
			CompareUnit cu(cut, unit);
			return cu;
		}
		else {
			CompareUnitType cut(COMPARE_UNIT_ATTRIBUTE_NAME);
			string unit(visit(ctx->attributeName()).as<string>());
			CompareUnit cu(cut, unit);
			return cu;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitCompareValStat(GraphDBParser::CompareValStatContext *ctx) override {
		CompareStat cs_left(visit(ctx->compareStat(0)).as<CompareStat>());
		
		CompareOperatorType cot;
		if (ctx->compareOperator()->getText() == ">") {
			cot = COMPARE_GT;
		}
		else if (ctx->compareOperator()->getText() == "<") {
			cot = COMPARE_LT;
		}
		else if (ctx->compareOperator()->getText() == ">=") {
			cot = COMPARE_GTE;
		}
		else if (ctx->compareOperator()->getText() == "<=") {
			cot = COMPARE_LTE;
		}
		else if (ctx->compareOperator()->getText() == "=") {
			cot = COMPARE_EQ;
		}
		else if (ctx->compareOperator()->getText() == "!=") {
			cot = COMPARE_NEQ;
		}
		
		CompareStat cs_right(visit(ctx->compareStat(1)).as<CompareStat>());
		CompareValStat cvs(cs_left, cot, cs_right);
		return cvs;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitFuncStat(GraphDBParser::FuncStatContext *ctx) override {
		if (ctx->objectList()) {
			vector<string> objlist(visit(ctx->objectList()).as<vector<string>>());
			string funcname = visit(ctx->funcName()).as<string>();
			FuncStat fs(funcname, objlist);
			return fs;
		}
		else {
			vector<string> objlist;
			string funcname = visit(ctx->funcName()).as<string>();
			FuncStat fs(funcname, objlist);
			return fs;
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitFuncName(GraphDBParser::FuncNameContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitObject(GraphDBParser::ObjectContext *ctx) override {
		string ans = visit(ctx->paraItem()).as<string>();
		if (ctx->indexInt()) {
			ans += '[';
			ans += std::to_string(visit(ctx->indexInt()).as<int>());
			ans += ']';
		}
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitObjectList(GraphDBParser::ObjectListContext *ctx) override {
		vector<string> ans;
		string cur = visit(ctx->object()).as<string>();
		ans.push_back(cur);
		
		if (ctx->objectList()) {
			vector<string> temp(visit(ctx->objectList()).as<vector<string>>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitVarList(GraphDBParser::VarListContext *ctx) override {
		vector<string> ans;
		string cur = visit(ctx->variableName()).as<string>();
		ans.push_back(cur);

		if (ctx->varList()) {
			vector<string> temp(visit(ctx->varList()).as<vector<string>>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return ans;
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitBracketLeft(GraphDBParser::BracketLeftContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitBracketRight(GraphDBParser::BracketRightContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitDdlStatement(GraphDBParser::DdlStatementContext *ctx) override {
		if (ctx->createGsetStat()) {
			return antlrcpp::Any(DDLStatement(visit(ctx->createGsetStat()).as<CreateGSetStatement>()));
		}
		else if (ctx->createGStat()) {
			return antlrcpp::Any(DDLStatement(visit(ctx->createGStat()).as<CreateGraphStatement>()));
		}
		else if (ctx->createSchemaStat()) {
			return antlrcpp::Any(DDLStatement(visit(ctx->createSchemaStat()).as<CreateSchemaStatement>()));
		}
		else if (ctx->loadGsetStat()) {
			return antlrcpp::Any(DDLStatement(visit(ctx->loadGsetStat()).as<LoadGSetStatement>()));
		}
		else if (ctx->loadGStat()) {
			return antlrcpp::Any(DDLStatement(visit(ctx->loadGStat()).as<LoadGraphStatement>()));
		}
		else if (ctx->dropStat()) {
			return antlrcpp::Any(DDLStatement(visit(ctx->dropStat()).as<DropStatement>()));
		}
		
		return visitChildren(ctx);
	}

	antlrcpp::Any visitCreateSchemaStat(GraphDBParser::CreateSchemaStatContext *ctx) override {
		if (ctx->K_file()) {
			string path = visit(ctx->filename()).as<string>();
			CreateSchemaStatement css(path);
			return antlrcpp::Any(css);
		}
		else {
			string schemaname = visit(ctx->schemaid()).as<string>();
			SchemaStatement ss(visit(ctx->schemaStatement()).as<SchemaStatement>());
			CreateSchemaStatement css(ss, schemaname);
			return antlrcpp::Any(css);
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitSchemaStatement(GraphDBParser::SchemaStatementContext *ctx) override {
		SchemaAttrMap nodeans = visit(ctx->schemaNodeList()).as<SchemaAttrMap>();
		pair<SchemaAttrMap, SchemaNetwork> edgeans = visit(ctx->schemaEdgeList()).as<pair<SchemaAttrMap, SchemaNetwork>>();
		SchemaStatement ss(nodeans, edgeans.first, edgeans.second);
		return antlrcpp::Any(ss);
	}

	antlrcpp::Any visitSchemaNodeList(GraphDBParser::SchemaNodeListContext *ctx) override {
		SchemaAttrMap ans = visit(ctx->schemaNode()).as<SchemaAttrMap>();

		if (ctx->schemaNodeList()) {
			SchemaAttrMap temp(visit(ctx->schemaNodeList()).as<SchemaAttrMap>());
			ans.insert(temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitSchemaEdgeList(GraphDBParser::SchemaEdgeListContext *ctx) override {
		pair<SchemaAttrMap, SchemaNetwork> ans = visit(ctx->schemaEdge()).as<pair<SchemaAttrMap, SchemaNetwork>>();

		if (ctx->schemaEdgeList()) {
			pair<SchemaAttrMap, SchemaNetwork> temp(visit(ctx->schemaEdgeList()).as<pair<SchemaAttrMap, SchemaNetwork>>());
			ans.first.insert(temp.first.begin(), temp.first.end());
			ans.second.insert(temp.second.begin(), temp.second.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitSchemaNode(GraphDBParser::SchemaNodeContext *ctx) override {
		string labelname(visit(ctx->labelName()).as<string>());
		SchemaAttrMap ans;
		ans[labelname] = visit(ctx->schemaAttrList()).as<SchemaAttrTypeList>();
		return ans;
	}

	antlrcpp::Any visitSchemaAttrList(GraphDBParser::SchemaAttrListContext *ctx) override {
		SchemaAttrTypeList ans;
		ans.push_back(make_pair(visit(ctx->labelName()).as<string>(), visit(ctx->typeName()).as<string>()));

		if (ctx->schemaAttrList()) {
			SchemaAttrTypeList temp(visit(ctx->schemaAttrList()).as<SchemaAttrTypeList>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitSchemaEdge(GraphDBParser::SchemaEdgeContext *ctx) override {
		string labelname(visit(ctx->labelName()).as<string>());
		SchemaAttrMap ansfirst;
		SchemaNetwork anssecond;
		ansfirst[labelname] = visit(ctx->schemaAttrList()).as<SchemaAttrTypeList>();
		anssecond[labelname] = visit(ctx->edgeLinkageList()).as<SchemaConnection>();

		pair<SchemaAttrMap, SchemaNetwork> ans = make_pair(ansfirst, anssecond);
		return ans;
	}

	antlrcpp::Any visitEdgeLinkageList(GraphDBParser::EdgeLinkageListContext *ctx) override {
		SchemaConnection ans;
		ans.push_back(make_pair(visit(ctx->labelName(0)).as<string>(), visit(ctx->labelName(1)).as<string>()));

		if (ctx->edgeLinkageList()) {
			SchemaConnection temp = visit(ctx->edgeLinkageList()).as<SchemaConnection>();
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitLabelName(GraphDBParser::LabelNameContext *ctx) override {
		return ctx->getText();
	}

	antlrcpp::Any visitTypeName(GraphDBParser::TypeNameContext *ctx) override {
		return ctx->getText();
	}

	antlrcpp::Any visitSchemaItem(GraphDBParser::SchemaItemContext *ctx) override {
		if (ctx->schemaid()) {
			string sid = visit(ctx->schemaid()).as<string>();
			SchemaItem sitem(sid);
			return antlrcpp::Any(sitem);
		}
		return visitChildren(ctx);
	}

	antlrcpp::Any visitCreateGForStat(GraphDBParser::CreateGForStatContext *ctx) override {
		string gsid;
		if (ctx->K_for()) {
			gsid = visit(ctx->gsid()).as<string>();
		}
		else {
			gsid = "";
		}
		return antlrcpp::Any(gsid);
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitCreateGFileStat(GraphDBParser::CreateGFileStatContext *ctx) override {
		vector<string> flist;
		if (ctx->K_file()) {
			flist = visit(ctx->filenamelist()).as<vector<string>>();
		}
		
		return antlrcpp::Any(flist);
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitCreateGsetStat(GraphDBParser::CreateGsetStatContext *ctx) override {
		string gsid = visit(ctx->gsid()).as<string>();
		vector<string> gidlist = visit(ctx->gidList()).as<vector<string>>();
		SchemaItem sitem = visit(ctx->schemaItem()).as<SchemaItem>();
		CreateGSetStatement cgss(gsid, gidlist, sitem);
		return antlrcpp::Any(cgss);
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitLoadGsetStat(GraphDBParser::LoadGsetStatContext *ctx) override {
		string gsid = visit(ctx->gsid()).as<string>();
		LoadGSetStatement lgss(gsid);
		return antlrcpp::Any(lgss);
		//return visitChildren(ctx);
	}

	antlrcpp::Any visitCreateGStat(GraphDBParser::CreateGStatContext *ctx) override {
		string gid = visit(ctx->gid()).as<string>();
		SchemaItem sitem = visit(ctx->schemaItem()).as<SchemaItem>();
		vector<string> flist = visit(ctx->createGFileStat()).as<vector<string>>();
		string gsid = visit(ctx->createGForStat()).as<string>();
		bool hasfor = false;
		if (gsid != "")
			hasfor = true;
		CreateGraphStatement cgs(gid, sitem, flist, hasfor, gsid);
		return antlrcpp::Any(cgs);
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitLoadGStat(GraphDBParser::LoadGStatContext *ctx) override {
		string gid = visit(ctx->gid()).as<string>();
		LoadGraphStatement lgs(gid);
		return antlrcpp::Any(lgs);
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitSchemaTypeList(GraphDBParser::SchemaTypeListContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *ctx) override {
		string vid = visit(ctx->vid()).as<string>();
		if (ctx->attrEqItemList()) {
			return make_pair(vid, visit(ctx->attrEqItemList()).as<vector<pair<string, string>>>());
		}
		else {
			return make_pair(vid, vector<pair<string, string>>());
		}
	}

	antlrcpp::Any visitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *ctx) override {
		if (ctx->eid()) {
			string eid = visit(ctx->eid()).as<string>();
			if (ctx->attrEqItemList()) {
				return make_pair(eid, visit(ctx->attrEqItemList()).as<vector<pair<string, string>>>());
			}
			else {
				return make_pair(eid, vector<pair<string, string>>());
			}
		}
		else if (ctx->edge()) {
			pair<string, string> edge(visit(ctx->edge()).as<pair<string, string>>());
			string edgesign = edge.first + " " + edge.second;
			if (ctx->attrEqItemList()) {
				return make_pair(edgesign, visit(ctx->attrEqItemList()).as<vector<pair<string, string>>>());
			}
			else {
				return make_pair(edgesign, vector<pair<string, string>>());
			}
		}
		
		return visitChildren(ctx);
	}

	antlrcpp::Any visitSchemaAttributeItem(GraphDBParser::SchemaAttributeItemContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitAttrItem(GraphDBParser::AttrItemContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitDataType(GraphDBParser::DataTypeContext *ctx) override {
		return visitChildren(ctx);
	}

	antlrcpp::Any visitGsid(GraphDBParser::GsidContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitGid(GraphDBParser::GidContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any MyGraphVisitor::visitGidList(GraphDBParser::GidListContext *ctx) override {
		GIDList ans;
		ans.push_back(visit(ctx->gid()).as<GID>());
		if (ctx->gidList()) {
			LIDList temp(visit(ctx->gidList()).as<GIDList>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitVid(GraphDBParser::VidContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitEid(GraphDBParser::EidContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitLid(GraphDBParser::LidContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitFilename(GraphDBParser::FilenameContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitFilenamelist(GraphDBParser::FilenamelistContext *ctx) override {
		vector<string> ans;
		ans.push_back(ctx->filename()->getText());

		if (ctx->filenamelist()) {
			vector<string> temp(visit(ctx->filenamelist()).as<vector<string>>());
			ans.insert(ans.end(), temp.begin(), temp.end());
		}
		return antlrcpp::Any(ans);
	}

	antlrcpp::Any visitSchemaid(GraphDBParser::SchemaidContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitAttributeName(GraphDBParser::AttributeNameContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitVariableName(GraphDBParser::VariableNameContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitIndexInt(GraphDBParser::IndexIntContext *ctx) override {
		return ctx->getText();
		// return visitChildren(ctx);
	}

	antlrcpp::Any visitParaItem(GraphDBParser::ParaItemContext *ctx) override {
		return ctx->getText();
	}
};


#endif //ANTLR_GRAPHDB_MYGRAPHVISITOR_H
