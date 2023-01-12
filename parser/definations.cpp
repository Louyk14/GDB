//
// Created by Henry Fox on 2019-12-13.
//

#include "definations.h"


//OperationStatement::OperationStatement(const SelectStatement &d) : type(SELECT_TYPE) {
//    selectStatement = new SelectStatement(m);
//}

/*
OperationStatement::OperationStatement(const ProjectStatement &a) : type(PROJECT_TYPE) {
    projectStatement = new ProjectStatement(a);
}


OperationStatement::OperationStatement(const CartesianProductStatement &a) : type(CARTESIAN_PRODUCT_TYPE) {
    cartesianProductStatement = new CartesianProductStatement(a);
}


OperationStatement::OperationStatement(const AlignStatement &u) : type(ALIGN_TYPE) {
    alignStatement = new AlignStatement(u);
}


OperationStatement::OperationStatement(const SelectStatement &o) : type(SELECT_TYPE) {
    selectStatement = new SelectStatement(o);
}


OperationStatement::OperationStatement(const ReduceStatement &f) : type(REDUCE_TYPE) {
    reduceStatement = new ReduceStatement(f);
}


OperationStatement::OperationStatement(const MapStatement &w) : type(MAP_TYPE) {
    mapStatement = new MapStatement(w);
}


OperationStatement::OperationStatement(const JoinStatement &r) : type(JOIN_TYPE) {
    joinStatement = new JoinStatement(r);
}

OperationStatement::OperationStatement(const IntersectionStatement &r) : type(INTERSECTION_TYPE) {
    intersectionStatement = new IntersectionStatement(r);
}

OperationStatement::OperationStatement(const MaximalStatement &m) : type(MAXIMAL_TYPE) {
    maximalStatement = new MaximalStatement(m);
}


OperationStatement::OperationStatement(const UnionStatement &u) : type(UNION_TYPE) {
    unionStatement = new UnionStatement(u);
}
*/

/*
OperationStatement::OperationStatement(const OperationStatement &o) : type(o.type) {
    switch (type) {
        case SELECT_TYPE:
            selectStatement = new SelectStatement(*o.selectStatement);
            break;
        /*case PROJECT_TYPE:
            projectStatement = new ProjectStatement(*o.projectStatement);
            break;
        case CARTESIAN_PRODUCT_TYPE:
            cartesianProductStatement = new CartesianProductStatement(*o.cartesianProductStatement);
            break;
        case ALIGN_TYPE:
            alignStatement = new AlignStatement(*o.alignStatement);
            break;
        case SELECT_TYPE:
            selectStatement = new SelectStatement(*o.selectStatement);
            break;
        case REDUCE_TYPE:
            reduceStatement = new ReduceStatement(*o.reduceStatement);
            break;
        case MAP_TYPE:
            mapStatement = new MapStatement(*o.mapStatement);
            break;
        case JOIN_TYPE:
            joinStatement = new JoinStatement(*o.joinStatement);
            break;
        case INTERSECTION_TYPE:
            intersectionStatement = new IntersectionStatement(*o.intersectionStatement);
            break;
        case MAXIMAL_TYPE:
            maximalStatement = new MaximalStatement(*o.maximalStatement);
            break;
        case UNION_TYPE:
            unionStatement = new UnionStatement(*o.unionStatement);
            break;   */ 
   /* }
}
*/

/*OperationStatement::~OperationStatement() {
    switch (type) {
        case SELECT_TYPE:
            delete selectStatement;
            break;
        /*case PROJECT_TYPE:
            delete projectStatement;
            break;
        case CARTESIAN_PRODUCT_TYPE:
            delete cartesianProductStatement;
            break;
        case ALIGN_TYPE:
            delete alignStatement;
            break;
        case SELECT_TYPE:
            delete selectStatement;
            break;
        case REDUCE_TYPE:
            delete reduceStatement;
            break;
        case MAP_TYPE:
            delete mapStatement;
            break;
        case JOIN_TYPE:
            delete joinStatement;
            break;
        case INTERSECTION_TYPE:
            delete intersectionStatement;
            break;
        case MAXIMAL_TYPE:
            delete maximalStatement;
            break;
        case UNION_TYPE:
            delete unionStatement;
            break; */
 /*   }
}*/

/*OperationUnit::OperationUnit(const QueryStatement &q, const GraphAlias &a) : alias(a), type(QUERY_STATEMENT_TYPE) {
    //query = new QueryStatement(q);
}

SourceGraph::SourceGraph(const QueryStatement &q) : type(QUERY_STATEMENT_TYPE) {
   // query = new QueryStatement(q);
}

OperationUnit::OperationUnit(const OperationUnit &o) : alias(o.alias), type(o.type) {
    if (type == GRAPH_DEFINITION_TYPE) {
        graph = new GDBGraph(*o.graph);
    } 
    else if (type == QUERY_STATEMENT_TYPE) {
        query = new QueryStatement(*o.query);
    } else {
        gid = new GID(*o.gid);
    }
}

SourceGraph::SourceGraph(const SourceGraph &o) : type(o.type) {
    if (type == GRAPH_DEFINITION_TYPE) {
        graph = new GDBGraph(*o.graph);
    } else if (type == QUERY_STATEMENT_TYPE) {
        query = new QueryStatement(*o.query);
    } else {
        gid = new GID(*o.gid);
    }
}

OperationUnit::~OperationUnit() {
    if (type == GRAPH_DEFINITION_TYPE) {
        delete graph;
    } 
    else if (type == QUERY_STATEMENT_TYPE) {
        delete query;
    } else {
        delete gid;
    }
}

SourceGraph::~SourceGraph() {
    if (type == GRAPH_DEFINITION_TYPE) {
        delete graph;
    } else if (type == QUERY_STATEMENT_TYPE) {
        delete query;
    } else {
        delete gid;
    }
}*/


OperatorGSet::OperatorGSet(QueryStatement& qs) : type(GSET_QUERY_TYPE) {
	queryStatement = new QueryStatement(qs);
}

OperatorGSet::OperatorGSet(OperatorGSet& operatorGSet) {
	type = operatorGSet.type;
	if (type == GSET_GSID_TYPE)
		gsid = new GID(*operatorGSet.gsid);
	else
		queryStatement = new QueryStatement(*operatorGSet.queryStatement);
}


ExistStat::ExistStat(ExistStat& es) {
	varList = vector<string>(es.varList);
	fos = new FirstOrderStat(*es.fos);
}

ExistStat::ExistStat(vector<string>& list, FirstOrderStat& fostat) {
	varList = vector<string>(list);
	fos = new FirstOrderStat(fostat);
}
