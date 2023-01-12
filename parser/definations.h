//
// Created by Henry Fox on 2019-12-13.
//

#ifndef ANTLR_GRAPHDB_DEFINATIONS_H
#define ANTLR_GRAPHDB_DEFINATIONS_H

#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <unordered_map>
#include "GraphDBParser.h"
#include "GraphDBLexer.h"
#include <sstream>

using namespace antlr4;
using namespace antlr4::tree;
using std::vector;
using std::string;
using std::tuple;
using std::stringstream;
using std::get;
using std::pair;
using std::unordered_map;

typedef string VID;
typedef string EID;
typedef string LID;
typedef string GID;
typedef string GSID;
typedef string EntID;
typedef string FileName;
typedef string AttributeName;
typedef vector<pair<VID, LID>> VIDList;
typedef vector<EID, LID> EIDList;
typedef vector<LID> LIDList;
typedef vector<GID> GIDList;
typedef tuple<VID, VID> VIDTuple;
typedef vector<VIDTuple> VIDTupleList;
typedef vector<AttributeName> AttributeNameList;
typedef vector<pair<string, string>> SchemaAttrTypeList;
typedef vector<pair<string, string>> SchemaConnection;
typedef unordered_map<string, SchemaAttrTypeList> SchemaAttrMap;
typedef unordered_map<string, SchemaConnection> SchemaNetwork;
typedef pair<string, vector<pair<string, string>>> AttributeListItem;
typedef vector<pair<string, vector<pair<string, string>>>> AttributeList;

enum ValueType {
    STRING_TYPE, INT_TYPE, DOUBLE_TYPE
};

#define EDGE_ID_KEY "ID"

class FirstOrderStat;

class Value {
public:
    ValueType type;
    union {
        string *s_data;
        int i_data;
        double d_data;
    };

    ~Value() {
        if (type == STRING_TYPE) {
            delete s_data;
        }
    }

    explicit Value(const string &s) : type(STRING_TYPE) {
        s_data = new string(s);
    }

    Value(const Value &v) : type(v.type) {
        if (type == STRING_TYPE) {
            s_data = new string(*v.s_data);
        } else if (type == INT_TYPE) {
            i_data = v.i_data;
        } else {
            d_data = v.d_data;
        }
    }

    explicit Value(const int &i) : type(INT_TYPE), i_data(i) {}

    explicit Value(const double &d) : type(DOUBLE_TYPE), d_data(d) {}

    bool operator==(const Value &v) const {
        if (type != v.type) {
            return false;
        }
        if (type == STRING_TYPE) {
            return *s_data == *v.s_data;
        } else if (type == INT_TYPE) {
            return i_data == v.i_data;
        } else {
            return d_data == v.d_data;
        }
    }
};

class AttributeConsItem {
public:
    AttributeName attributeName;
    Value value;

    AttributeConsItem(const AttributeName &a, const Value &b) : attributeName(a), value(b) {}

    AttributeConsItem(const AttributeConsItem &a) : attributeName(a.attributeName), value(a.value) {}

    bool operator==(const AttributeConsItem &a) const {
        return (attributeName == a.attributeName) && (value == a.value);
    }
};

typedef vector<AttributeConsItem> AttributeConsItemList;

class EdgeAttribute {
public:
    EID eid;
    AttributeConsItemList attributeConsItemList;

    EdgeAttribute(const EID &e, const AttributeConsItemList &a) : eid(e), attributeConsItemList(a) {}

    bool operator==(const EdgeAttribute &e) const {
        if (e.eid != eid) {
            return false;
        }
        int len_a = attributeConsItemList.size();
        int len_b = e.attributeConsItemList.size();
        if (len_a != len_b) {
            return false;
        }
        for (int i = 0; i < len_a; i++) {
            if (!(attributeConsItemList[i] == e.attributeConsItemList[i])) {
                return false;
            }
        }
        return true;
    }
};

class NodeAttribute {
public:
    VID vid;
    AttributeConsItemList attributeConsItemList;

    NodeAttribute(const VID &v, const AttributeConsItemList &a) : vid(v), attributeConsItemList(a) {}

    bool operator==(const NodeAttribute &e) const {
        if (e.vid != vid) {
            return false;
        }
        int len_a = attributeConsItemList.size();
        int len_b = e.attributeConsItemList.size();
        if (len_a != len_b) {
            return false;
        }
        for (int i = 0; i < len_a; i++) {
            if (!(attributeConsItemList[i] == e.attributeConsItemList[i])) {
                return false;
            }
        }
        return true;
    }
};

typedef vector<EdgeAttribute> EdgeAttributeList;
typedef vector<NodeAttribute> NodeAttributeList;
// typedef tuple<NodeAttributeList, EdgeAttributeList> AttributeInfo;



class AttributeNameWithEnt {
public:
    bool specifiedGraphName;
    EntID ent;
    GID graph;
    AttributeName attributeName;

    AttributeNameWithEnt(const GID &g, const EntID &e,
                         const AttributeName &a) : specifiedGraphName(true), ent(e), graph(g), attributeName(a) {}

    AttributeNameWithEnt(const EntID &e, const AttributeName &a) : specifiedGraphName(false), ent(e), graph(""),
                                                                   attributeName(a) {}
};

class AttributeConsCertain {
public:
    AttributeNameWithEnt attributeNameWithEnt;
    Value value;

    AttributeConsCertain(const AttributeNameWithEnt &a, const Value &v) : attributeNameWithEnt(a), value(v) {}
};

class AttributeConsUncertain {
public:
    AttributeNameWithEnt target;
    AttributeNameWithEnt source;

    AttributeConsUncertain(const AttributeNameWithEnt &t, const AttributeNameWithEnt &s) : target(t), source(s) {}
};

enum ValueOrEntAttr {
    VALUE_CONS_TYPE, ENT_ATTR_CONS_TYPE
};

class AttributeConsItemWithEnt {
public:
    ValueOrEntAttr type;
    union {
        AttributeConsCertain *certain;
        AttributeConsUncertain *uncertain;
    };

    explicit AttributeConsItemWithEnt(const AttributeConsCertain &a) : type(VALUE_CONS_TYPE) {
        certain = new AttributeConsCertain(a);
    }

    explicit AttributeConsItemWithEnt(const AttributeConsUncertain &a) : type(ENT_ATTR_CONS_TYPE) {
        uncertain = new AttributeConsUncertain(a);
    }

    AttributeConsItemWithEnt(const AttributeConsItemWithEnt &a) : type(a.type) {
        if (type == VALUE_CONS_TYPE) {
            certain = new AttributeConsCertain(*a.certain);
        } else {
            uncertain = new AttributeConsUncertain(*a.uncertain);
        }
    }

    ~AttributeConsItemWithEnt() {
        if (type == VALUE_CONS_TYPE) {
            delete certain;
        } else {
            delete uncertain;
        }
    }
};

enum CompareOperator {
    GT, LT, GTE, LTE, EQ, NEQ
};

//enum LogicOperator {
//    AND, OR, SINGLE
//};

enum AttributeConstraintItemType {
    ATTR_CONSTRAINT_TYPE, IS_CIRCLE_TYPE, IS_PATH_TYPE, IS_CC_TYPE, DEG_CONSTRAINT_TYPE
};

enum DegInOrOut {
    DEG_IN, DEG_OUT
};

class DegConstraint {
public:
    DegInOrOut type;
    VID vid;
    CompareOperator op;
    Value value;

    DegConstraint(const DegInOrOut &t, const VID &v,
                  const CompareOperator &o, const Value &va) : type(t), vid(v), op(o), value(va) {}
};

class AttributeConstraintItem {
public:
    AttributeConstraintItemType type;
    union {
        AttributeConsItemWithEnt *attributeConsItemWithEnt;
        DegConstraint *degConstraint;
    };

    explicit AttributeConstraintItem(const AttributeConsItemWithEnt &a) : type(ATTR_CONSTRAINT_TYPE) {
        attributeConsItemWithEnt = new AttributeConsItemWithEnt(a);
    }

    explicit AttributeConstraintItem(const DegConstraint &d) : type(DEG_CONSTRAINT_TYPE) {
        degConstraint = new DegConstraint(d);
    }

    explicit AttributeConstraintItem(const AttributeConstraintItemType &a) : type(a),
                                                                             attributeConsItemWithEnt(nullptr) {}

    AttributeConstraintItem(const AttributeConstraintItem &a) : type(a.type) {
        if (type == ATTR_CONSTRAINT_TYPE) {
            attributeConsItemWithEnt = new AttributeConsItemWithEnt(*a.attributeConsItemWithEnt);
        } else if (type == DEG_CONSTRAINT_TYPE) {
            degConstraint = new DegConstraint(*a.degConstraint);
        } else {
            attributeConsItemWithEnt = nullptr;
        }
    }

    ~AttributeConstraintItem() {
        if (type == ATTR_CONSTRAINT_TYPE) {
            delete attributeConsItemWithEnt;
        } else if (type == DEG_CONSTRAINT_TYPE) {
            delete degConstraint;
        } else {
            delete attributeConsItemWithEnt;
        }
    }
};

typedef vector<AttributeConstraintItem> AttributeConstraintList;
typedef tuple<VIDTupleList, AttributeConstraintList> ConstraintGraph;

class GraphAlias {
public:
    bool haveAlias;
    GID gid;

    explicit GraphAlias(const GID &g) : haveAlias(true), gid(g) {}

    explicit GraphAlias() : haveAlias(false), gid(GID()) {}
};

class GraphSetAlias {
public:
	bool haveAlias;
	GSID gsid;

	explicit GraphSetAlias(const GSID &g) : haveAlias(true), gsid(g) {}

	explicit GraphSetAlias() : haveAlias(false), gsid(GSID()) {}
};

enum ExactCondition {
    NONE_CONDITION, EXACT_CONDITION, MONO_CONDITION
};

enum OperationUnitType {
    GRAPH_DEFINITION_TYPE, QUERY_STATEMENT_TYPE, GID_TYPE
};

enum StatementType {
	DML_STATEMENT_TYPE, DDL_STATEMENT_TYPE
};

enum DMLOperationType {
	QUERY_TYPE,
	INSERT_TYPE,
	REMOVE_TYPE,
	UPDATE_TYPE
};

//class SelectStatement;

//class OperationStatement {
//public:
 //   OperationStatementType type;
 //   union {
 //       SelectStatement *selectStatement;
        //MinusStatement *minusStatement;
        //AttrProjStatement *attrProjStatement;
        //PowerSetStatement *powerSetStatement;
        //One2oneJoinStatement *one2OneJoinStatement;
        //MonoSelectionStatement *monoSelectionStatement;
        //FilterStatement *filterStatement;
        //ReduceStatement *reduceStatement;
        //MaximizeStatement * maximizeStatement;
//    };

 //   explicit OperationStatement(const SelectStatement &u);

    //explicit OperationStatement(const MinusStatement &m);

    //explicit OperationStatement(const AttrProjStatement &a);

    //explicit OperationStatement(const PowerSetStatement &w);

    //explicit OperationStatement(const One2oneJoinStatement &o);

    //explicit OperationStatement(const MonoSelectionStatement &o);

    //explicit OperationStatement(const FilterStatement &f);

    //explicit OperationStatement(const ReduceStatement &r);

    //explicit OperationStatement(const MaximizeStatement &r);

 //   OperationStatement(const OperationStatement &o);

  //  ~OperationStatement();
//};

class QueryStatement;


/*class UnionStatement {
public:
    OperationUnit unit_a, unit_b;

    UnionStatement(const OperationUnit &a, const OperationUnit &b) : unit_a(a), unit_b(b) {}
};

class MinusStatement {
public:
    OperationUnit unit_a, unit_b;

    MinusStatement(const OperationUnit &a, const OperationUnit &b) : unit_a(a), unit_b(b) {}
};

typedef vector<AttributeNameList> SchemeList;

class AttrProjStatement {
public:
    SchemeList schemeList;
    LIDList lidList;

    AttrProjStatement(const SchemeList &s, const LIDList &l) : schemeList(s), lidList(l) {}
};

class PowerSetStatement {
public:
    OperationUnit operationUnit;

    PowerSetStatement(const OperationUnit &o) : operationUnit(o) {}
};

class JoinConditionList {
public:
    AttributeConsUncertain attributeConsUncertain;
    LogicOperator op;
    JoinConditionList *joinConditionList;

    explicit JoinConditionList(const AttributeConsUncertain &a) : attributeConsUncertain(a), op(SINGLE),
                                                                  joinConditionList(nullptr) {}

    JoinConditionList(const AttributeConsUncertain &a, const LogicOperator &o, const JoinConditionList &j)
            : attributeConsUncertain(a), op(o) {
        joinConditionList = new JoinConditionList(j);
    }

    JoinConditionList(const JoinConditionList &j) : attributeConsUncertain(j.attributeConsUncertain), op(j.op) {
        if (op != SINGLE) {
            joinConditionList = new JoinConditionList(*j.joinConditionList);
        } else {
            joinConditionList = nullptr;
        }
    }

    ~JoinConditionList() {
        if (op != SINGLE) {
            delete joinConditionList;
        }
    }
};

class One2oneJoinStatement {
public:
    OperationUnit unit_a, unit_b;
    JoinConditionList *joinConditionList;

    One2oneJoinStatement(const OperationUnit &a, const OperationUnit &b) : unit_a(a), unit_b(b),
                                                                           joinConditionList(nullptr) {}

    One2oneJoinStatement(const OperationUnit &a, const OperationUnit &b,
                         const JoinConditionList &j) : unit_a(a), unit_b(b) {
        joinConditionList = new JoinConditionList(j);
    }

    One2oneJoinStatement(const One2oneJoinStatement &o) : unit_a(o.unit_a), unit_b(o.unit_b) {
        if (o.joinConditionList) {
            joinConditionList = new JoinConditionList(*o.joinConditionList);
        } else {
            joinConditionList = nullptr;
        }
    }

    ~One2oneJoinStatement() {
        if (joinConditionList) {
            delete joinConditionList;
        }
    }
};

class MonoSelectionStatement {
public:
    OperationUnit sourceGraph, patternGraph;

    MonoSelectionStatement(const OperationUnit &a, const OperationUnit &b) : sourceGraph(a), patternGraph(b) {}
};

class FilterStatement {
public:
    ConstraintGraph constraintGraph;
    OperationUnit operationUnit;

    FilterStatement(const ConstraintGraph &c, const OperationUnit &o) : constraintGraph(c), operationUnit(o) {}
};

class ReduceStatement {
public:
    OperationUnit operationUnit;

    ReduceStatement(const OperationUnit &o) : operationUnit(o) {}
};

class MaximizeStatement {
public:
    OperationUnit operationUnit;

    MaximizeStatement(const OperationUnit &o) : operationUnit(o) {}
};*/


enum ProjectType {
	PROJECT_STAR_TYPE, PROJECT_LIST_TYPE
};

class ProjectCondition {
public:
	ProjectType type;
	union {
		bool isStar;
	};

	ProjectCondition(ProjectCondition& pc) : type(pc.type) {
		if (type == PROJECT_STAR_TYPE) {
			isStar = pc.isStar;
		}
	}

	ProjectCondition(bool star) : isStar(star) {
		if (isStar)
			type = PROJECT_STAR_TYPE;
	}

	ProjectCondition() : isStar(false) {
		type = PROJECT_LIST_TYPE;
	}
};

class AttributeInfo {
public:
	AttributeList nodeAttr;
	AttributeList edgeAttr;

	AttributeInfo() {

	}

	AttributeInfo(AttributeList& na, AttributeList& ea) {
		nodeAttr = na;
		edgeAttr = ea;
	}
};

class EdgeInfo {
public:
	string start;
	string end;
	string label;
	
	EdgeInfo(string& src, string& tgt, string l) {
		start = src;
		end = tgt;
		label = l;
	}
};

class GraphStat {
public:
	vector<pair<string, string>> vid;
	unordered_map<string, EdgeInfo*> eidmap; // alias name mapping
	AttributeList nodeattr;
	AttributeList edgeattr;

	GraphStat(vector<pair<string, string>>& vidt, unordered_map<string, EdgeInfo*>& eidmapt,
		AttributeList& nodeattrt,
		AttributeList& edgeattrt) {
		vid = vidt;
		eidmap = eidmapt;
		nodeattr = nodeattrt;
		edgeattr = edgeattrt;
	}

	GraphStat(vector<pair<string, string>>& vidt, unordered_map<string, EdgeInfo*>& eidmapt) {
		vid = vidt;
		eidmap = eidmapt;
	}

	GraphStat(GraphStat& gstat) {
		vid = gstat.vid;
		eidmap = gstat.eidmap;
		nodeattr = gstat.nodeattr;
		edgeattr = gstat.edgeattr;
	}
};

enum GSetType {
	GSET_GSID_TYPE, GSET_CONSTANT_GRAPHSET_TYPE, GSET_QUERY_TYPE
};

class OperatorGSet {
public:
	GSetType type;
	union {
		GSID* gsid;
		QueryStatement* queryStatement;
	};

	OperatorGSet(GSID& g) : type(GSET_GSID_TYPE) {
		gsid = new GSID(g);
	}

	OperatorGSet(QueryStatement& qs);

	OperatorGSet(OperatorGSet& operatorGSet);
};

class OperationStatement {
public:
	OperationStatement(OperationStatement& oS) {

	}
};

enum FromType {
	FROM_OPERATOR_GSET, FROM_OPERATION_STATEMENT
};

class FromCondition {
public:
	FromType type;
	union {
		OperatorGSet* operatorGSet;
		OperationStatement* operationStatement;
	};

	FromCondition(FromCondition& from) : type(from.type) {
		if (type == FROM_OPERATOR_GSET)
			operatorGSet = new OperatorGSet(*from.operatorGSet);
		else
			operationStatement = new OperationStatement(*from.operationStatement);
	}

	FromCondition(OperatorGSet& oGSet) : type(FROM_OPERATOR_GSET) {
		operatorGSet = new OperatorGSet(oGSet);
	}

	FromCondition(OperationStatement& oStatement) : type(FROM_OPERATION_STATEMENT) {
		operationStatement = new OperationStatement(oStatement);
	}
};

class FuncStat {
public:
	string funcName;
	vector<string> objList;

	FuncStat(FuncStat& fs) {
		funcName = fs.funcName;
		objList = vector<string>(fs.objList);
	}

	FuncStat(string& fn, vector<string>& objl) {
		funcName = fn;
		objList = vector<string>(objl);
	}
};



class ExistStat {
public:
	vector<string> varList;
	FirstOrderStat* fos;

	ExistStat(ExistStat& es);
	ExistStat(vector<string>& list, FirstOrderStat& fostat);
};

enum CompareUnitType {
	COMPARE_UNIT_VALUE, COMPARE_UNIT_ATTRIBUTE_NAME
};

class CompareUnit {
public:
	CompareUnitType type;
	string unit;

	CompareUnit(CompareUnit& cu) : type(cu.type) {
		unit = cu.unit;
	}

	CompareUnit(CompareUnitType t, string u) {
		type = t;
		unit = u;
	}
};

enum CompareStatType {
	COMPARE_STAT_UNIT_TYPE, COMPARE_STAT_CALCULATE_TYPE, COMPARE_STAT_BRAC, COMPARE_STAT_TRUE, COMPARE_STAT_FALSE
};

enum CalculateOperatorType {
	CALCULATE_OPERATOR_ADD, CALCULATE_OPERATOR_MINUS, CALCULATE_OPERATOR_MULTIPLE, CALCULATE_OPERATOR_DIVIDE
};

class CompareStat {
public:
	CompareStatType type;
	CompareUnit* compareUnit;
	CompareStat* compareStatLeft;
	CalculateOperatorType calculateOperatorType;
	CompareStat* compareStatRight;

	CompareStat(CompareStat& cs) : type(cs.type) {
		if (cs.type == COMPARE_STAT_UNIT_TYPE) {
			compareUnit = new CompareUnit(*cs.compareUnit);
		}
		else if (cs.type == COMPARE_STAT_CALCULATE_TYPE) {
			compareStatLeft = new CompareStat(*cs.compareStatLeft);
			calculateOperatorType = cs.calculateOperatorType;
			compareStatRight = new CompareStat(*cs.compareStatRight);
		}
		else if (cs.type == COMPARE_STAT_BRAC) {
			compareStatLeft = new CompareStat(*cs.compareStatLeft);
		}
		else if (cs.type == COMPARE_STAT_TRUE) {

		}
		else if (cs.type == COMPARE_STAT_FALSE) {

		}
	}

	CompareStat(CompareUnit& cu) : type(COMPARE_STAT_UNIT_TYPE) {
		compareUnit = new CompareUnit(cu);
	}

	CompareStat(CompareStat& cs_left, CalculateOperatorType cot, CompareStat& cs_right) : type(COMPARE_STAT_CALCULATE_TYPE) {
		compareStatLeft = new CompareStat(cs_left);
		calculateOperatorType = cot;
		compareStatRight = new CompareStat(cs_right);
	}

	CompareStat(CompareStat& cu, CompareStatType cst) : type(cst) {
		compareStatLeft = new CompareStat(cu);
	}

	CompareStat(CompareStatType cst) : type(cst) {

	}
};

enum CompareOperatorType {
	COMPARE_GT, COMPARE_LT, COMPARE_GTE, COMPARE_LTE, COMPARE_EQ, COMPARE_NEQ
};

class CompareValStat {
public:
	CompareStat* compareStatLeft;
	CompareOperatorType compareOperator;
	CompareStat* compareStatRight;

	CompareValStat(CompareValStat& cvs) {
		compareStatLeft = new CompareStat(*cvs.compareStatLeft);
		compareOperator = cvs.compareOperator;
		compareStatRight = new CompareStat(*cvs.compareStatRight);
	}

	CompareValStat(CompareStat& cs_left, CompareOperatorType cot, CompareStat& cs_right) {
		compareStatLeft = new CompareStat(cs_left);
		compareOperator = cot;
		compareStatRight = new CompareStat(cs_right);
	}
};

enum FirstOrderUnitType {
	EXIST_TYPE, FOREACH_TYPE, COMPARE_VAL_TYPE, FUNC_TYPE
};

class FirstOrderUnit {
public:
	FirstOrderUnitType type;
	union {
		FuncStat* funcstat;
		ExistStat* existstat;
		CompareValStat* comparevalstat;
	};

	FirstOrderUnit(FirstOrderUnit& fou) : type(fou.type) {
		if (type == FUNC_TYPE) {
			funcstat = new FuncStat(*fou.funcstat);
		}
		else if (type == EXIST_TYPE) {
			existstat = new ExistStat(*fou.existstat);
		}
		else if (type == COMPARE_VAL_TYPE) {
			comparevalstat = new CompareValStat(*fou.comparevalstat);
		}
	}

	FirstOrderUnit(FuncStat& fs) : type(FUNC_TYPE) {
		funcstat = new FuncStat(fs);
	}

	FirstOrderUnit(ExistStat& es) : type(EXIST_TYPE) {
		existstat = new ExistStat(es);
	}

	FirstOrderUnit(CompareValStat& cvs) : type(COMPARE_VAL_TYPE) {
		comparevalstat = new CompareValStat(cvs);
	}
};

enum FirstOrderStatType {
	FIRST_ORDER_STAT_UNIT_TYPE, FIRST_ORDER_STAT_LOGIC_TYPE, FIRST_ORDER_STAT_BRAC, FIRST_ORDER_STAT_NOT, FIRST_ORDER_STAT_TRUE, FIRST_ORDER_STAT_FALSE
};

enum LogicFlagBiType {
	LOGIC_AND, LOGIC_OR, LOGIC_ARROW
};

class FirstOrderStat {
public:
	FirstOrderStatType type;
	FirstOrderUnit* firstOrderUnit;
	FirstOrderStat* firstOrderStatLeft;
	FirstOrderStat* firstOrderStatRight;
	LogicFlagBiType logicFlagBi;

	FirstOrderStat(FirstOrderStat& fos) : type(fos.type) {
		if (type == FIRST_ORDER_STAT_UNIT_TYPE) {
			firstOrderUnit = new FirstOrderUnit(*fos.firstOrderUnit);
		}
		else if (type == FIRST_ORDER_STAT_LOGIC_TYPE) {
			firstOrderStatLeft = new FirstOrderStat(*fos.firstOrderStatLeft);
			firstOrderStatRight = new FirstOrderStat(*fos.firstOrderStatRight);
			logicFlagBi = fos.logicFlagBi;
		}
		else if (type == FIRST_ORDER_STAT_NOT) {
			firstOrderStatLeft = new FirstOrderStat(*fos.firstOrderStatLeft);
		}
		else if (type == FIRST_ORDER_STAT_BRAC) {
			firstOrderStatLeft = new FirstOrderStat(*fos.firstOrderStatLeft);
		}
		else if (type == FIRST_ORDER_STAT_TRUE) {

		}
		else if (type == FIRST_ORDER_STAT_FALSE) {

		}
	}

	FirstOrderStat(FirstOrderUnit& fou) : type(FIRST_ORDER_STAT_UNIT_TYPE) {
		firstOrderUnit = new FirstOrderUnit(fou);
	}

	// NOT and BRACKET
	FirstOrderStat(FirstOrderStat& fos, FirstOrderStatType fost) : type(fost) {
		firstOrderStatLeft = new FirstOrderStat(fos);
	}

	FirstOrderStat(FirstOrderStat& fos_left, LogicFlagBiType bitype, FirstOrderStat& fos_right) : type(FIRST_ORDER_STAT_LOGIC_TYPE) {
		firstOrderStatLeft = new FirstOrderStat(fos_left);
		logicFlagBi = bitype;
		firstOrderStatRight = new FirstOrderStat(fos_right);
	}

	FirstOrderStat(FirstOrderStatType fostype) : type(fostype) {
		
	}
};

enum WhereType {
	WHERE_NONE_TYPE, WHERE_FILENAME_TYPE, WHERE_FILENAMELIST_TYPE, WHERE_FIRSTORDER_TYPE
};

class WhereCondition {
public:
	WhereType type;
	bool hasWhere;
	union {
		FileName* filename;
		vector<FileName>* filenamelist;
		FirstOrderStat* firstOrderStat;
	};

	WhereCondition(WhereCondition& whereCondition) : type(whereCondition.type), hasWhere(whereCondition.hasWhere) {
		if (type == WHERE_FILENAME_TYPE) {
			filename = new FileName(*whereCondition.filename);
		}
		else if (type == WHERE_FILENAMELIST_TYPE) {
			filenamelist = new vector<FileName>(*whereCondition.filenamelist);
		}
		else if (type == WHERE_FIRSTORDER_TYPE) {
			firstOrderStat = new FirstOrderStat(*whereCondition.firstOrderStat);
		}
	}

	WhereCondition(FileName& file) : type(WHERE_FILENAME_TYPE) {
		filename = new FileName(file);
	}

	WhereCondition(vector<FileName>& file) : type(WHERE_FILENAMELIST_TYPE) {
		filenamelist = new vector<FileName>();
		for (int i = 0; i < file.size(); ++i) {
			filenamelist->push_back(FileName(file[i]));
		}
	}

	WhereCondition(FirstOrderStat& firstorderStat) : type(WHERE_FIRSTORDER_TYPE) {
		firstOrderStat = new FirstOrderStat(firstorderStat);
	}
};

class SelectStatement {
public:
	bool needReduce;
	bool needMaximal;
	GraphSetAlias alias;
	FromCondition* fromCondition;
	WhereCondition* whereCondition;

	SelectStatement(SelectStatement& select) : needReduce(select.needReduce), needMaximal(select.needMaximal), alias(select.alias), fromCondition(select.fromCondition), whereCondition(select.whereCondition) {

	}

	SelectStatement(bool nR, bool nM, GraphSetAlias& ga, FromCondition& fC, WhereCondition& wC) {
		needReduce = nR;
		needMaximal = nM;
		alias = ga;
		fromCondition = new FromCondition(fC);
		whereCondition = new WhereCondition(wC);

	}
};

enum QueryStatementType {
	MULTIPLE_OPERATOR_TYPE, SELECT_OPERATION_TYPE, CONSTANT_GRAPH_TYPE
};

class QueryStatement {
public:
	QueryStatementType type;
	union {
		SelectStatement* selectStatement;
	};
	
	QueryStatement() : type(SELECT_OPERATION_TYPE) {};

	QueryStatement(QueryStatement& qs) {
		type = qs.type;
		if (type == SELECT_OPERATION_TYPE) {
			selectStatement = new SelectStatement(*qs.selectStatement);
		}
	}

	QueryStatement(SelectStatement& select) : type(SELECT_OPERATION_TYPE) {
		selectStatement = new SelectStatement(select);
	}
};

class InsertGSetStat {
public:
	string gsid;
	vector<string> gidlist;

	InsertGSetStat(string& id, vector<string>& idlist) {
		gsid = id;
		gidlist = idlist;
	}

	InsertGSetStat(InsertGSetStat& igss) {
		gsid = igss.gsid;
		gidlist = igss.gidlist;
	}
};


enum InsertGraphStatType {
	INSERT_INTO_GRAPH_TUPLE_TYPE, INSERT_INTO_GRAPH_FILE_TYPE, INSERT_INTO_GRAPH_GRAPH_TYPE
};

class InsertGraphStat {
public:
	InsertGraphStatType type;
	string gid;
	union {
		GraphStat* gstat;
		vector<string>* filelist;
		string* sourcegid;
	};

	InsertGraphStat(GraphStat& gs, string id) : type(INSERT_INTO_GRAPH_TUPLE_TYPE) {
		gstat = new GraphStat(gs);
		gid = id;
	}

	InsertGraphStat(vector<string>& list, string id) : type(INSERT_INTO_GRAPH_FILE_TYPE) {
		filelist = new vector<string>(list);
		gid = id;
	}

	InsertGraphStat(string& sgid, string id) : type(INSERT_INTO_GRAPH_GRAPH_TYPE) {
		sourcegid = new string(sgid);
		gid = id;
	}
};

enum InsertStatementType {
	INSERT_INTO_GSET_TYPE, INSERT_INTO_GRAPH_TYPE, INSERT_INTO_SCHEMA_TYPE
};

class InsertStatement {
public:
	InsertStatementType type;
	union {
		InsertGSetStat* insertGSetStat;
		InsertGraphStat* insertGraphStat;
	};

	InsertStatement(InsertGSetStat& igss) : type(INSERT_INTO_GSET_TYPE) {
		insertGSetStat = new InsertGSetStat(igss);
	}

	InsertStatement(InsertGraphStat& igs) : type(INSERT_INTO_GRAPH_TYPE) {
		insertGraphStat = new InsertGraphStat(igs);
	}

	InsertStatement(InsertStatement& istat) : type(istat.type) {
		if (type == INSERT_INTO_GSET_TYPE) {
			insertGSetStat = new InsertGSetStat(*istat.insertGSetStat);
		}
		else if (type == INSERT_INTO_GRAPH_TYPE) {
			insertGraphStat = new InsertGraphStat(*istat.insertGraphStat);
		}
	}
};

class RemoveGSetStat {
public:
	string gsid;
	vector<string> gidlist;

	RemoveGSetStat(string& id, vector<string>& idlist) {
		gsid = id;
		gidlist = idlist;
	}

	RemoveGSetStat(RemoveGSetStat& rgss) {
		gsid = rgss.gsid;
		gidlist = rgss.gidlist;
	}
};

enum RemoveGraphStatType {
	REMOVE_FROM_GRAPH_TUPLE_TYPE, REMOVE_FROM_GRAPH_FILE_TYPE, REMOVE_FROM_GRAPH_GRAPH_TYPE
};

class RemoveGraphStat {
public:
	RemoveGraphStatType type;
	string gid;
	union {
		GraphStat* gstat;
		vector<string>* filelist;
		string* sourcegid;
	};

	RemoveGraphStat(GraphStat& gs, string id) : type(REMOVE_FROM_GRAPH_TUPLE_TYPE) {
		gstat = new GraphStat(gs);
		gid = id;
	}

	RemoveGraphStat(vector<string>& list, string id) : type(REMOVE_FROM_GRAPH_FILE_TYPE) {
		filelist = new vector<string>(list);
		gid = id;
	}

	RemoveGraphStat(string& sgid, string id) : type(REMOVE_FROM_GRAPH_GRAPH_TYPE) {
		sourcegid = new string(sgid);
		gid = id;
	}
};

enum RemoveStatementType {
	REMOVE_FROM_GSET_TYPE, REMOVE_FROM_GRAPH_TYPE
};

class RemoveStatement {
public:
	RemoveStatementType type;
	union {
		RemoveGSetStat* removeGSetStat;
		RemoveGraphStat* removeGraphStat;
	};

	RemoveStatement(RemoveGSetStat& rgss) : type(REMOVE_FROM_GSET_TYPE) {
		removeGSetStat = new RemoveGSetStat(rgss);
	}

	RemoveStatement(RemoveGraphStat& rgs) : type(REMOVE_FROM_GRAPH_TYPE) {
		removeGraphStat = new RemoveGraphStat(rgs);
	}

	RemoveStatement(RemoveStatement& rstat) : type(rstat.type) {
		if (type == REMOVE_FROM_GSET_TYPE) {
			removeGSetStat = new RemoveGSetStat(*rstat.removeGSetStat);
		}
		else if (type == REMOVE_FROM_GRAPH_TYPE) {
			removeGraphStat = new RemoveGraphStat(*rstat.removeGraphStat);
		}
	}
};

class DMLStatement {
public:
	DMLOperationType type;
	union {
		QueryStatement* queryStatement;
		InsertStatement* insertStatement;
		RemoveStatement* removeStatement;
	};

	DMLStatement(QueryStatement& query) : type(QUERY_TYPE) {
		queryStatement = new QueryStatement(query);
	}

	DMLStatement(InsertStatement& insert) : type(INSERT_TYPE) {
		insertStatement = new InsertStatement(insert);
	}

	DMLStatement(RemoveStatement& remove) : type(REMOVE_TYPE) {
		removeStatement = new RemoveStatement(remove);
	}

	DMLStatement(const DMLStatement& dml) : type(dml.type) {
		if (type == QUERY_TYPE) {
			queryStatement = new QueryStatement(*dml.queryStatement);
		}
		else if (type == INSERT_TYPE) {
			insertStatement = new InsertStatement(*dml.insertStatement);
		}
		else if (type == REMOVE_TYPE) {
			removeStatement = new RemoveStatement(*dml.removeStatement);
		}
	}
};


// ddl definitions

enum DDLOperationType {
	CREATE_SCHEMA_TYPE, CREATE_GSET_TYPE, CREATE_GRAPH_TYPE, LOAD_GSET_TYPE, LOAD_GRAPH_TYPE, DROP_TYPE
};

enum DropStatType {
	DROP_GSET_TYPE, DROP_GRAPH_TYPE, DROP_SCHEMA_TYPE
};

enum CreateSchemaStatementType {
	CREATE_SCHEMA_DESCRIBE_TYPE, CREATE_SCHEMA_FILE_TYPE
};

enum SchemaType {
	SCHEMA_LIST_TYPE, SCHEMA_ID_TYPE
};

class SchemaStatement {
public:
	SchemaAttrMap nodeattrlist;
	SchemaAttrMap edgeattrlist;
	SchemaNetwork edgelink;

	SchemaStatement(SchemaAttrMap& nalist, SchemaAttrMap& ealist, SchemaNetwork& elink) {
		nodeattrlist = nalist;
		edgeattrlist = ealist;
		edgelink = elink;
	}

	SchemaStatement(const SchemaStatement& sstat) {
		nodeattrlist = sstat.nodeattrlist;
		edgeattrlist = sstat.edgeattrlist;
		edgelink = sstat.edgelink;
	}
};

class CreateSchemaStatement {
public:
	CreateSchemaStatementType type;
	string schemaname;
	union {
		string* filepath;
		SchemaStatement* schemaStatement;
	};

	CreateSchemaStatement(string path) : type(CREATE_SCHEMA_FILE_TYPE) {
		filepath = new string(path);
	}

	CreateSchemaStatement(SchemaStatement& sstat, string& sname) : type(CREATE_SCHEMA_DESCRIBE_TYPE) {
		schemaStatement = new SchemaStatement(sstat);
		schemaname = sname;
	}

	CreateSchemaStatement(CreateSchemaStatement& css) : type(css.type) {
		if (type == CREATE_SCHEMA_FILE_TYPE) {
			filepath = css.filepath;
		}
		else if (type == CREATE_SCHEMA_DESCRIBE_TYPE) {
			schemaStatement = new SchemaStatement(*css.schemaStatement);
			schemaname = css.schemaname;
		}
	}
};

class SchemaItem {
public:
	SchemaType type;
	union {
		string* schemaid;
	};

	SchemaItem(string& sid) : type(SCHEMA_ID_TYPE) {
		schemaid = new string(sid);
	}

	SchemaItem(const SchemaItem& sitem) : type(sitem.type) {
		if (type == SCHEMA_LIST_TYPE) {
			
		}
		else {
			schemaid = sitem.schemaid;
		}
	}
};

class CreateGSetStatement {
public:
	string gsid;
	vector<string> gidlist;
	SchemaItem* sitem;

	CreateGSetStatement(string gs, vector<string>& glist, SchemaItem& si) {
		gsid = gs;
		gidlist = glist;
		sitem = new SchemaItem(si);
	}

	CreateGSetStatement(CreateGSetStatement& cgss) {
		gsid = cgss.gsid;
		gidlist = cgss.gidlist;
		sitem = new SchemaItem(*cgss.sitem);
	}
};

class CreateGraphStatement {
public:
	string gid;
	SchemaItem* sitem;
	vector<string> filelist;
	bool hasfor;
	string gsid;

	CreateGraphStatement(string g, SchemaItem& si, vector<string>& flist, bool& hasf, string& gs) {
		gid = g;
		sitem = new SchemaItem(si);
		filelist = flist;
		hasfor = hasf;
		gsid = gs;
	}

	CreateGraphStatement(CreateGraphStatement& cgs) {
		gid = cgs.gid;
		sitem = new SchemaItem(*cgs.sitem);
		filelist = cgs.filelist;
		hasfor = cgs.hasfor;
		gsid = cgs.gsid;
	}
};

class LoadGSetStatement {
public:
	string gsid;

	LoadGSetStatement(string id) {
		gsid = id;
	}

	LoadGSetStatement(LoadGSetStatement* lgss) {
		gsid = lgss->gsid;
	}
};

class LoadGraphStatement {
public:
	string gid;
	
	LoadGraphStatement(string id) {
		gid = id;
	}

	LoadGraphStatement(LoadGraphStatement& lgs) {
		gid = lgs.gid;
	}
};

class DropStatement {
public:
	DropStatType type;
	string itemid;

	DropStatement(DropStatType t, string id) : type(t) {
		itemid = id;
	}

	DropStatement(DropStatement& ds) : type(ds.type){
		itemid = ds.itemid;
	}
};

class DDLStatement {
public:
	DDLOperationType type;
	union {
		CreateGSetStatement* createGSet;
		CreateGraphStatement* createGraph;
		CreateSchemaStatement* createSchema;
		LoadGSetStatement* loadGSet;
		LoadGraphStatement* loadGraph;
		DropStatement* dropStat;
	};

	DDLStatement(CreateGSetStatement& cgss) : type(CREATE_GSET_TYPE) {
		createGSet = new CreateGSetStatement(cgss);
	}

	DDLStatement(CreateGraphStatement& cgs) : type(CREATE_GRAPH_TYPE) {
		createGraph = new CreateGraphStatement(cgs);
	}

	DDLStatement(CreateSchemaStatement& css) : type(CREATE_SCHEMA_TYPE) {
		createSchema = new CreateSchemaStatement(css);
	}

	DDLStatement(LoadGraphStatement& lgs) : type(LOAD_GRAPH_TYPE) {
		loadGraph = new LoadGraphStatement(lgs);
	}

	DDLStatement(LoadGSetStatement& lgss) : type(LOAD_GSET_TYPE) {
		loadGSet = new LoadGSetStatement(lgss);
	}

	DDLStatement(DropStatement& ds) : type(DROP_TYPE) {
		dropStat = new DropStatement(ds);
	}

	DDLStatement(const DDLStatement& ddl) : type(ddl.type) {
		if (type == CREATE_GSET_TYPE) {
			createGSet = new CreateGSetStatement(*ddl.createGSet);
		}
		else if (type == CREATE_GRAPH_TYPE) {
			createGraph = new CreateGraphStatement(*ddl.createGraph);
		}
		else if (type == CREATE_SCHEMA_TYPE) {
			createSchema = new CreateSchemaStatement(*ddl.createSchema);
		}
		else if (type == LOAD_GSET_TYPE) {
			loadGSet = new LoadGSetStatement(*ddl.loadGSet);
		}
		else if (type == LOAD_GRAPH_TYPE) {
			loadGraph = new LoadGraphStatement(*ddl.loadGraph);
		}
		else if (type == DROP_TYPE) {
			dropStat = new DropStatement(*ddl.dropStat);
		}
	}
};


// all statement

class Statement {
public:
	StatementType type;
	union {
		DMLStatement* dmlStatement;
		DDLStatement* ddlStatement;
	};

	Statement(const DMLStatement &dmls) : type(DML_STATEMENT_TYPE) {
		dmlStatement = new DMLStatement(dmls);
	}

	Statement(const DDLStatement &ddls) : type(DDL_STATEMENT_TYPE) {
		ddlStatement = new DDLStatement(ddls);
	}
};

#endif //ANTLR_GRAPHDB_DEFINATIONS_H
