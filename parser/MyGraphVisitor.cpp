//
// Created by Henry Fox on 2019-12-13.
//

#include "MyGraphVisitor.h"

#include <iostream>


antlrcpp::Any MyGraphVisitor::visitVidTupleList(GraphDBParser::VidTupleListContext *context) {
	VIDTupleList ans;
	ans.push_back(visit(context->vidTuple()).as<VIDTuple>());
	if (context->vidTupleList()) {
		VIDTupleList temp(visit(context->vidTupleList()).as<VIDTupleList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}

/*antlrcpp::Any MyGraphVisitor::visitEidList(GraphDBParser::EidListContext *context) {
	EIDList ans;
	ans.push_back(visit(context->eid()).as<EID>());
	if (context->eidList()) {
		EIDList temp(visit(context->eidList()).as<EIDList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}*/

antlrcpp::Any MyGraphVisitor::visitLidList(GraphDBParser::LidListContext *context) {
	LIDList ans;
	ans.push_back(visit(context->lid()).as<LID>());
	if (context->lidList()) {
		LIDList temp(visit(context->lidList()).as<LIDList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}


int toInt(const string &data) {
	stringstream ss;
	ss << data;
	int ans;
	ss >> ans;
	return ans;
}

double toDouble(const string &data) {
	stringstream ss;
	ss << data;
	double ans;
	ss >> ans;
	return ans;
}

Value getValue(const string &data) {
	if (data[0] == '"' || data[0] == '\'') {
		return Value(data.substr(1, data.size() - 2));
	}
	else {
		if (int(data.find('.')) < 0) {
			return Value(toInt(data));
		}
		return Value(toDouble(data));
	}
}

/*antlrcpp::Any MyGraphVisitor::visitAttributeConsItem(GraphDBParser::AttributeConsItemContext *context) {
	return antlrcpp::Any(AttributeConsItem(
		visit(context->attributeName()).as<AttributeName>(),
		getValue(context->VALUE()->getText())));
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeConsItemList(GraphDBParser::AttributeConsItemListContext *context) {
	AttributeConsItemList ans;
	ans.push_back(visit(context->attributeConsItem()).as<AttributeConsItem>());
	if (context->attributeConsItemList()) {
		AttributeConsItemList temp(visit(context->attributeConsItemList()).as<AttributeConsItemList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}*/

antlrcpp::Any MyGraphVisitor::visitAttributeNameList(GraphDBParser::AttributeNameListContext *context) {
	AttributeNameList ans;
	ans.push_back(visit(context->attributeName()).as<AttributeName>());
	if (context->attributeNameList()) {
		AttributeNameList temp(visit(context->attributeNameList()).as<AttributeNameList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}

/*antlrcpp::Any MyGraphVisitor::visitAttributeNameWithEnt(GraphDBParser::AttributeNameWithEntContext *context) {
	if (context->gid()) {
		return antlrcpp::Any(AttributeNameWithEnt(visit(context->gid()).as<GID>(),
			visit(context->entId()).as<EntID>(),
			visit(context->attributeName()).as<AttributeName>()));
	}
	return antlrcpp::Any(AttributeNameWithEnt(visit(context->entId()).as<EntID>(),
		visit(context->attributeName()).as<AttributeName>()));
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeConsCertain(GraphDBParser::AttributeConsCertainContext *context) {
	return antlrcpp::Any(AttributeConsCertain(visit(context->attributeNameWithEnt()).as<AttributeNameWithEnt>(),
		getValue(context->VALUE()->getText())));
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeConsUncertain(GraphDBParser::AttributeConsUncertainContext *context) {
	return antlrcpp::Any(AttributeConsUncertain(visit(context->attributeNameWithEnt(0)).as<AttributeNameWithEnt>(),
		visit(context->attributeNameWithEnt(1)).as<AttributeNameWithEnt>()));
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeConsItemWithEnt(GraphDBParser::AttributeConsItemWithEntContext *context) {
	if (context->attributeConsCertain()) {
		return antlrcpp::Any(
			AttributeConsItemWithEnt(visit(context->attributeConsCertain()).as<AttributeConsCertain>()));
	}
	return antlrcpp::Any(
		AttributeConsItemWithEnt(visit(context->attributeConsUncertain()).as<AttributeConsUncertain>()));

}*/

antlrcpp::Any MyGraphVisitor::visitGT(GraphDBParser::GTContext *) {
	return antlrcpp::Any(GT);
}

antlrcpp::Any MyGraphVisitor::visitLT(GraphDBParser::LTContext *) {
	return antlrcpp::Any(LT);
};

antlrcpp::Any MyGraphVisitor::visitGTE(GraphDBParser::GTEContext *) {
	return antlrcpp::Any(GTE);
};

antlrcpp::Any MyGraphVisitor::visitLTE(GraphDBParser::LTEContext *) {
	return antlrcpp::Any(LTE);
};

antlrcpp::Any MyGraphVisitor::visitEQ(GraphDBParser::EQContext *) {
	return antlrcpp::Any(EQ);
};

antlrcpp::Any MyGraphVisitor::visitNEQ(GraphDBParser::NEQContext *) {
	return antlrcpp::Any(NEQ);
};

/*antlrcpp::Any MyGraphVisitor::visitAND(GraphDBParser::ANDContext *) {
	return antlrcpp::Any(AND);
};

antlrcpp::Any MyGraphVisitor::visitOR(GraphDBParser::ORContext *) {
	return antlrcpp::Any(OR);
};

antlrcpp::Any MyGraphVisitor::visitGraph(GraphDBParser::GraphContext *context) {
	if (context->easyGraph()) {
		return visit(context->easyGraph());
	}
	return antlrcpp::Any(Graph(visit(context->vertexInfo()).as<VIDList>(), visit(context->edgeInfo()).as<EdgeInfo>(),
		visit(context->attributeInfo()).as<AttributeInfo>()));
}*/


/*antlrcpp::Any MyGraphVisitor::visitEdgeItem(GraphDBParser::EdgeItemContext *context) {
	return antlrcpp::Any(
		Edge(visit(context->vertexInfo()).as<VIDList>(), visit(context->edgeLabel()).as<VIDTupleList>(),
			visit(context->edgeAttributeInfo()).as<EdgeAttributeList>()));
}
*/
/*antlrcpp::Any MyGraphVisitor::visitEdgeList(GraphDBParser::EdgeListContext *context) {
	EdgeInfo ans;
	ans.push_back(visit(context->edgeItem()).as<Edge>());
	if (context->edgeList()) {
		EdgeInfo temp(visit(context->edgeList()).as<EdgeInfo>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}*/


/*antlrcpp::Any MyGraphVisitor::visitEdgeLabel(GraphDBParser::EdgeLabelContext *context) {
	if (context->vidTupleList()) {
		return visit(context->vidTupleList());
	}
	return antlrcpp::Any(VIDTupleList());
}*/



/*antlrcpp::Any MyGraphVisitor::visitNodeAttributeItem(GraphDBParser::NodeAttributeItemContext *context) {
	if (context->attributeConsItemList()) {
		return antlrcpp::Any(NodeAttribute(visit(context->vid()).as<VID>(),
			visit(context->attributeConsItemList()).as<AttributeConsItemList>()));
	}
	return antlrcpp::Any(NodeAttribute(visit(context->vid()).as<VID>(), AttributeConsItemList()));
}*/




/*antlrcpp::Any MyGraphVisitor::visitEdgeAttributeItem(GraphDBParser::EdgeAttributeItemContext *context) {
	if (context->attributeConsItemList()) {
		return antlrcpp::Any(EdgeAttribute(visit(context->eid()).as<EID>(),
			visit(context->attributeConsItemList()).as<AttributeConsItemList>()));
	}
	return antlrcpp::Any(EdgeAttribute(visit(context->eid()).as<EID>(), AttributeConsItemList()));
}*/


/*antlrcpp::Any MyGraphVisitor::visitStructureConstraintInfo(GraphDBParser::StructureConstraintInfoContext *context) {
	if (context->vidTupleList()) {
		return visit(context->vidTupleList());
	}
	return antlrcpp::Any(VIDTupleList());
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeConstraintItem(GraphDBParser::AttributeConstraintItemContext *context) {
	if (context->attributeConsItemWithEnt()) {
		return antlrcpp::Any(
			AttributeConstraintItem(visit(context->attributeConsItemWithEnt()).as<AttributeConsItemWithEnt>()));
	}
	else if (context->K_iscircle()) {
		return antlrcpp::Any(AttributeConstraintItem(IS_CIRCLE_TYPE));
	}
	else if (context->K_ispath()) {
		return antlrcpp::Any(AttributeConstraintItem(IS_PATH_TYPE));
	}
	else if (context->K_iscc()) {
		return antlrcpp::Any(AttributeConstraintItem(IS_CC_TYPE));
	}
	DegInOrOut degInOrOut = context->K_degin() ? DEG_IN : DEG_OUT;
	return antlrcpp::Any(AttributeConstraintItem(DegConstraint(
		degInOrOut, visit(context->vid()).as<VID>(), visit(context->compareOperator()).as<CompareOperator>(),
		getValue(context->VALUE()->getText())
		)));
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeConstraintList(GraphDBParser::AttributeConstraintListContext *context) {
	AttributeConstraintList ans;
	ans.push_back(visit(context->attributeConstraintItem()).as<AttributeConstraintItem>());
	if (context->attributeConstraintList()) {
		AttributeConstraintList temp(visit(context->attributeConstraintList()).as<AttributeConstraintList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}

antlrcpp::Any MyGraphVisitor::visitAttributeConstraintInfo(GraphDBParser::AttributeConstraintInfoContext *context) {
	if (context->attributeConstraintList()) {
		return visit(context->attributeConstraintList());
	}
	return antlrcpp::Any(AttributeConstraintList());
}

antlrcpp::Any MyGraphVisitor::visitConstraintGraph(GraphDBParser::ConstraintGraphContext *context) {
	return antlrcpp::Any(ConstraintGraph(visit(context->structureConstraintInfo()).as<VIDTupleList>(),
		visit(context->attributeConstraintInfo()).as<AttributeConstraintList>()));
}

antlrcpp::Any MyGraphVisitor::visitOperationStatement(GraphDBParser::OperationStatementContext *context) {
	if (context->unionStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->unionStatement()).as<UnionStatement>()));
	}
	else if (context->minusStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->minusStatement()).as<MinusStatement>()));
	}
	else if (context->attrProjStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->attrProjStatement()).as<AttrProjStatement>()));
	}
	else if (context->powerSetStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->powerSetStatement()).as<PowerSetStatement>()));
	}
	else if (context->one2oneJoinStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->one2oneJoinStatement()).as<One2oneJoinStatement>()));
	}
	else if (context->monoSelectionStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->monoSelectionStatement()).as<MonoSelectionStatement>()));
	}
	else if (context->filterStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->filterStatement()).as<FilterStatement>()));
	}
	else if (context->reduceStatement()) {
		return antlrcpp::Any(OperationStatement(visit(context->reduceStatement()).as<ReduceStatement>()));
	}
	else {
		return antlrcpp::Any(OperationStatement(visit(context->maximizeStatement()).as<MaximizeStatement>()));
	}
}*/

/*antlrcpp::Any MyGraphVisitor::visitOperationUnit(GraphDBParser::OperationUnitContext *context) {
	if (context->gid()) {
		return antlrcpp::Any(OperationUnit(visit(context->gid()).as<GID>()));
	}
	else {
		GraphAlias nameGraph(visit(context->nameGraph()).as<GraphAlias>());
		if (context->graph()) {
			return antlrcpp::Any(OperationUnit(visit(context->graph()).as<Graph>(), nameGraph));
		}
		else if (context->operationStatement()) {
			return antlrcpp::Any(
				OperationUnit(visit(context->operationStatement()).as<OperationStatement>(), nameGraph));
		}
		else {
			return antlrcpp::Any(OperationUnit(visit(context->queryStatement()).as<QueryStatement>(), nameGraph));
		}
	}
}

antlrcpp::Any MyGraphVisitor::visitUnionStatement(GraphDBParser::UnionStatementContext *context) {
	return antlrcpp::Any(UnionStatement(visit(context->operationUnit(0)).as<OperationUnit>(),
		visit(context->operationUnit(1)).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitMinusStatement(GraphDBParser::MinusStatementContext *context) {
	return antlrcpp::Any(MinusStatement(visit(context->operationUnit(0)).as<OperationUnit>(),
		visit(context->operationUnit(1)).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitSchemeItem(GraphDBParser::SchemeItemContext *context) {
	if (context->attributeNameList()) {
		return antlrcpp::Any(visit(context->attributeNameList()).as<AttributeNameList>());
	}
	else {
		return antlrcpp::Any(AttributeNameList());
	}
}

antlrcpp::Any MyGraphVisitor::visitSchemeList(GraphDBParser::SchemeListContext *context) {
	SchemeList ans;
	ans.push_back(visit(context->schemeItem()).as<AttributeNameList>());
	if (context->schemeList()) {
		SchemeList temp(visit(context->schemeList()).as<SchemeList>());
		ans.insert(ans.end(), temp.begin(), temp.end());
	}
	return antlrcpp::Any(ans);
}

antlrcpp::Any MyGraphVisitor::visitAttrProjStatement(GraphDBParser::AttrProjStatementContext *context) {
	return antlrcpp::Any(
		AttrProjStatement(visit(context->schemeList()).as<SchemeList>(), visit(context->lidList()).as<LIDList>()));
}

antlrcpp::Any MyGraphVisitor::visitPowerSetStatement(GraphDBParser::PowerSetStatementContext *context) {
	return antlrcpp::Any(PowerSetStatement(visit(context->operationUnit()).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitJoinConditionList(GraphDBParser::JoinConditionListContext *context) {
	if (context->logicOperator()) {
		return antlrcpp::Any(JoinConditionList(
			visit(context->attributeConsUncertain()).as<AttributeConsUncertain>(),
			visit(context->logicOperator()).as<LogicOperator>(),
			visit(context->joinConditionList()).as<JoinConditionList>()));
	}
	return antlrcpp::Any(JoinConditionList(visit(context->attributeConsUncertain()).as<AttributeConsUncertain>()));
}

antlrcpp::Any MyGraphVisitor::visitOne2oneJoinStatement(GraphDBParser::One2oneJoinStatementContext *context) {
	if (context->joinConditionList()) {
		return antlrcpp::Any(One2oneJoinStatement(
			visit(context->operationUnit(0)).as<OperationUnit>(),
			visit(context->operationUnit(1)).as<OperationUnit>(),
			visit(context->joinConditionList()).as<JoinConditionList>()));
	}
	return antlrcpp::Any(One2oneJoinStatement(
		visit(context->operationUnit(0)).as<OperationUnit>(),
		visit(context->operationUnit(1)).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitMonoSelectionStatement(GraphDBParser::MonoSelectionStatementContext *context) {
	return antlrcpp::Any(MonoSelectionStatement(
		visit(context->operationUnit(0)).as<OperationUnit>(),
		visit(context->operationUnit(1)).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitFilterStatement(GraphDBParser::FilterStatementContext *context) {
	return antlrcpp::Any(FilterStatement(visit(context->constraintGraph()).as<ConstraintGraph>(),
		visit(context->operationUnit()).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitReduceStatement(GraphDBParser::ReduceStatementContext *context) {
	return antlrcpp::Any(ReduceStatement(visit(context->operationUnit()).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitMaximizeStatement(GraphDBParser::MaximizeStatementContext *context) {
	return antlrcpp::Any(MaximizeStatement(visit(context->operationUnit()).as<OperationUnit>()));
}

antlrcpp::Any MyGraphVisitor::visitSourceGraph(GraphDBParser::SourceGraphContext *context) {
	if (context->gid()) {
		return antlrcpp::Any(SourceGraph(visit(context->gid()).as<GID>()));
	}
	else if (context->graph()) {
		return antlrcpp::Any(SourceGraph(visit(context->graph()).as<Graph>()));
	}
	else if (context->operationStatement()) {
		return antlrcpp::Any(
			SourceGraph(visit(context->operationStatement()).as<OperationStatement>()));
	}
	else {
		return antlrcpp::Any(SourceGraph(visit(context->queryStatement()).as<QueryStatement>()));
	}
}

antlrcpp::Any MyGraphVisitor::visitExactCondition(GraphDBParser::ExactConditionContext *context) {
	if (context->K_exact()) {
		return antlrcpp::Any(EXACT_CONDITION);
	}
	else if (context->K_mono()) {
		return antlrcpp::Any(MONO_CONDITION);
	}
	else {
		return antlrcpp::Any(NONE_CONDITION);
	}
}*/

/*antlrcpp::Any MyGraphVisitor::visitNameGraph(GraphDBParser::NameGraphContext *context) {
	if (context->gid()) {
		return antlrcpp::Any(GraphAlias(visit(context->gid()).as<GID>()));
	}
	return antlrcpp::Any(GraphAlias());
}

antlrcpp::Any MyGraphVisitor::visitQueryStatement(GraphDBParser::QueryStatementContext *context) {
	return antlrcpp::Any(QueryStatement(
		visit(context->exactCondition()).as<ExactCondition>(),
		context->graph() ? visit(context->graph()).as<Graph>() : Graph(),
		visit(context->nameGraph()).as<GraphAlias>(),
		visit(context->sourceGraph()).as<SourceGraph>()));
}*/

/*antlrcpp::Any MyGraphVisitor::visitAttributeName(GraphDBParser::AttributeNameContext *context) {
	return antlrcpp::Any(AttributeName(context->ANY_NAME()->getText()));
}

antlrcpp::Any MyGraphVisitor::visitGid(GraphDBParser::GidContext *context) {
	return antlrcpp::Any(GID(context->ANY_NAME()->getText()));
}

antlrcpp::Any MyGraphVisitor::visitVid(GraphDBParser::VidContext *context) {
	return antlrcpp::Any(VID(context->ANY_NAME()->getText()));
}

antlrcpp::Any MyGraphVisitor::visitEid(GraphDBParser::EidContext *context) {
	return antlrcpp::Any(EID(context->ANY_NAME()->getText()));
}

antlrcpp::Any MyGraphVisitor::visitLid(GraphDBParser::LidContext *context) {
	return antlrcpp::Any(LID(context->ANY_NAME()->getText()));
}*/

antlrcpp::Any MyGraphVisitor::visitEntId(GraphDBParser::EntIdContext *context) {
	if (context->vid()) {
		return antlrcpp::Any(EntID(visit(context->vid()).as<VID>()));
	}
	else {
		return antlrcpp::Any(EntID(visit(context->eid()).as<EID>()));
	}
}

/*antlrcpp::Any MyGraphVisitor::visitEasyVertex(GraphDBParser::EasyVertexContext *context) {
	return visit(context->vid());
}*/

/*antlrcpp::Any MyGraphVisitor::visitEasyEdge(GraphDBParser::EasyEdgeContext *context) {
	Edge ans;
	ans.edgeLable = visit(context->easyEdgeInfo()).as<VIDTupleList>();
	if (context->eid()) {
		ans.edgeAttributeInfo.push_back(EdgeAttribute(visit(context->eid()).as<EID>(), AttributeConsItemList()));
	}
	for (auto e = ans.edgeLable.begin(); e != ans.edgeLable.end(); e++) {
		VID a = get<0>(*e);
		if (find(ans.vertexInfo.begin(), ans.vertexInfo.end(), a) == ans.vertexInfo.end()) {
			ans.vertexInfo.push_back(a);
		}
		a = get<1>(*e);
		if (find(ans.vertexInfo.begin(), ans.vertexInfo.end(), a) == ans.vertexInfo.end()) {
			ans.vertexInfo.push_back(a);
		}
	}
	return antlrcpp::Any(ans);
}*/

/*antlrcpp::Any MyGraphVisitor::visitEasyEdgeItem(GraphDBParser::EasyEdgeItemContext *context) {
	VID v1 = visit(context->easyVertex(0)).as<VID>(), v2 = visit(context->easyVertex(1)).as<VID>();
	return antlrcpp::Any(VIDTuple(v1, v2));
}*/

/*antlrcpp::Any MyGraphVisitor::visitEasyEdgeInfo(GraphDBParser::EasyEdgeInfoContext *context) {
	VIDTupleList ans;
	if (context->easyEdgeInfo()) {
		ans = visit(context->easyEdgeInfo()).as<VIDTupleList>();
	}
	VIDTuple tuple = visit(context->easyEdgeItem()).as<VIDTuple>();
	ans.push_back(tuple);
	return antlrcpp::Any(ans);
}*/

/*antlrcpp::Any MyGraphVisitor::visitEasyGraphPartList(GraphDBParser::EasyGraphPartListContext *context) {
	Graph ans;
	if (context->easyGraphPartList()) {
		ans = visit(context->easyGraphPartList()).as<Graph>();
	}
	if (context->easyVertex()) {
		VID v = visit(context->easyVertex()).as<VID>();
		// TODO Check code structure, shouldn't parse here
		if (find(ans.vertexInfo.begin(), ans.vertexInfo.end(), v) == ans.vertexInfo.end()) {
			ans.vertexInfo.push_back(v);
		}
		else {
			// Just ignore the case of:
			// 1. duplicate single vertexes
			// 2. single vertex in other edges
		}
	}
	else {
		Edge e = visit(context->easyEdge()).as<Edge>();
		for (auto v = e.vertexInfo.begin(); v != e.vertexInfo.end(); v++) {
			if (find(ans.vertexInfo.begin(), ans.vertexInfo.end(), *v) == ans.vertexInfo.end()) {
				ans.vertexInfo.push_back(*v);
			}
		}
		ans.edgeInfo.push_back(e);
	}
	return antlrcpp::Any(ans);
}

antlrcpp::Any MyGraphVisitor::visitEasyGraph(GraphDBParser::EasyGraphContext *context) {
	if (context->easyGraphPartList()) {
		return visit(context->easyGraphPartList());
	}
	return antlrcpp::Any(Graph());
}*/