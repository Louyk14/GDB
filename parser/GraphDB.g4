grammar GraphDB;

statement: dmlStatement ';' | ddlStatement ';';
dmlStatement: insertStat | removeStat | updateStat | queryStat;
insertStat: insertGsetStat | insertGStat;
removeStat: removeGsetStat | removeGStat;
insertGsetStat: K_insert K_into K_graphset gsid '(' gidList ')';
insertGStat: K_insert graph K_into K_graph gid | K_insert K_file filenamelist K_into K_graph gid | K_insert K_graph gid K_into K_graph gid;
graphNameItem: graph K_as gid | gid;
graphNameList: graphNameItem | graphNameItem ',' graphNameList;
removeGsetStat: K_remove K_from K_graphset gsid '(' gidList ')';
removeGStat: K_remove '(' vertexInfo ',' edgeInfo ')' K_from K_graph gid | K_remove K_file filenamelist K_from K_graph gid | K_remove gid K_from K_graph gid;
updateStat: K_update gsid K_at gid K_by K_set attributeName '=' value;

//queryStat: K_query nameGraph K_by operationStatement;
nameGraph: K_as gsid | ;
graph: '(' vertexInfo ',' edgeInfo ',' attributeInfo ')' | '(' vertexInfo ',' edgeInfo ')';
graphItem: graph | gid;
graphList: graphItem | graphItem ',' graphList;
graphset: '{' graphList '}';
vertexInfo: '{' '}' | '{' vidList '}';
edgeInfo: '{' '}' | '{' edgeList '}';
edgeList: edge '[' lid ']' | eid '=' edge '[' lid ']' | edge '[' lid ']' ',' edgeList | eid '=' edge '[' lid ']' ',' edgeList;
edge: vidTuple;
attributeInfo: '(' nodeAttributeInfo ',' edgeAttributeInfo ')' | '(' nodeAttributeInfo ')';
nodeAttributeInfo: '{' '}' | '{' nodeAttributeList '}';
nodeAttributeList: nodeAttributeItem | nodeAttributeItem ',' nodeAttributeList;
nodeAttributeItem: vid '<' '>' | vid '<' attrEqItemList '>';
edgeAttributeInfo: '{' '}' | '{' edgeAttributeList '}';
edgeAttributeList: edgeAttributeItem | edgeAttributeItem ',' edgeAttributeList;
edgeAttributeItem: eid '<' '>' | edge '<' '>' | eid '<' attrEqItemList '>' | edge '<' attrEqItemList '>';

queryStat: queryStat multipleOperator queryStat
    | '(' queryStat ')'
    | K_select nameGraph reduceWord maximalWord projectCondition fromCondition alignConditionList whereCondition mapCondition
    | gsid;

multipleOperator: '-' | K_intersect | K_union;

projectCondition: schemaNameList K_for lidList | '*';
fromCondition: K_from operatorGSet | K_from operationStatement;
alignConditionList: alignCondition alignConditionList | ;
alignCondition: K_align lid ',' lid ',' lid K_on attrEqItemListUncertain;
filenamelist: filename ',' filenamelist | filename ;
whereCondition: K_where firstOrderStat | K_where K_file filenamelist;
mapCondition: K_map '[' operatorGSet ']' K_by gsid |;
reduceWord: K_reduce |;
maximalWord: K_maximal |;

operationStatement: productStatement | joinStatement;

operatorGSet: gsid | graphset nameGraph | '(' graphset nameGraph ')' | queryStat;

schemaNameItem: '{' '}' | '{' attributeNameList '}' | '*';
schemaNameList: schemaNameItem | schemaNameItem ',' schemaNameList;
productStatement: operatorGSet ',' operatorGSet;
//alignStatement: K_align operatorGSet K_at lid ',' lid ',' lid K_on attrEqItemListUncertain;
//diffStatement: operatorGSet '-' operatorGSet;
joinStatement: operatorGSet K_join operatorGSet;
//intersectionStatement: operatorGSet K_intersect operatorGSet;
//unionStatement: operatorGSet K_union operatorGSet;

value: INTEGER_NUMBER | NOT_INTEGER_NUMBER | TEXT;

entId: vid | eid;
vidList: vid '[' lid ']' | vid '[' lid ']' ',' vidList;
gidList: gid | gid ',' gidList;
lidList: lid | lid ',' lidList;
vidTuple: '(' vid ',' vid ')';
vidTupleList: vidTuple | vidTuple ',' vidTupleList;
attrEqItem: attributeName '=' value;
attrEqItemList: attrEqItem | attrEqItem ',' attrEqItemList;
attributeNameList: attributeName | attributeName ',' attributeNameList;
attrEqItemUncertain: attributeName '=' attributeName;
attrEqItemListUncertain: attrEqItemUncertain | attrEqItemUncertain ',' attrEqItemListUncertain;
compareOperator : '>'    # GT
                | '<'    # LT
                | '>='   # GTE
                | '<='   # LTE
                | '='    # EQ
                | '!='   # NEQ
                ;
calculateOperator : '+' | '-' | '*' | '/';

logicFlagBi: K_and | K_or | K_arrow;
logicFlagNot: K_not;
firstOrderStat: firstOrderUnit | bracketLeft firstOrderStat bracketRight | firstOrderStat logicFlagBi firstOrderStat | logicFlagNot firstOrderStat | K_true | K_false;
firstOrderUnit: funcStat | existStat | foreachStat | compareValStat;
existStat: K_exist varList '(' firstOrderStat ')';
foreachStat: K_foreach varList '(' firstOrderStat ')';
compareStat: compareUnit | compareStat calculateOperator compareStat | bracketLeft compareStat bracketRight | K_true | K_false;
compareUnit: value | attributeName;
compareValStat: compareStat compareOperator compareStat;
funcStat: funcName '(' objectList ')' | funcName '(' ')';
funcName: K_equal | K_vertex | K_edge | K_complete | K_unique | K_hasedge | K_sizegeq | K_graphequal | K_graphinset | K_subgraph | K_inducedsub | K_connect | K_clique | K_tdensesub;
object: paraItem | paraItem '[' indexInt ']';
objectList: object ',' objectList | object;
varList: variableName | variableName ',' varList;
bracketLeft: '(';
bracketRight: ')';


ddlStatement: createSchemaStat | createGsetStat | loadGsetStat | createGStat | loadGStat | dropStat;
createSchemaStat: K_create K_schema schemaid schemaStatement | K_create K_schema K_file filename;
schemaStatement: '{' schemaNodeList ',' schemaEdgeList '}';
schemaNodeList: schemaNode | schemaNode ',' schemaNodeList;
schemaEdgeList: schemaEdge | schemaEdge ',' schemaEdgeList;
schemaNode: labelName '(' schemaAttrList ')';
schemaAttrList: labelName typeName | labelName typeName ',' schemaAttrList;
schemaEdge: labelName  '[' edgeLinkageList ']' '(' schemaAttrList ')';
edgeLinkageList: labelName '-' labelName | labelName '-' labelName ',' edgeLinkageList;
labelName: NAME_STRING;
typeName: dataType;
schemaItem: '{' schemaTypeList '}' | schemaid;
createGsetStat: K_create K_graphset gsid '(' gidList ')' schemaItem;
createGStat: K_create K_graph gid schemaItem createGFileStat createGForStat;
createGFileStat: K_from K_file filenamelist |;
createGForStat: K_for gsid |;
loadGsetStat: K_load K_graphset gsid;
loadGStat: K_load K_graph gid;
dropStat: dropGsetStat | dropGStat | dropSchemaStat;
dropGsetStat: K_drop K_graphset gsid;
dropGStat: K_drop K_graph gid;
dropSchemaStat: K_drop K_schema schemaid;
schemaTypeList: lid '<' schemaAttributeItem '>' | lid '<' schemaAttributeItem '>' ',' schemaTypeList;
schemaAttributeItem: attrItem | attrItem ',' schemaAttributeItem;
attrItem: attributeName ':' dataType;

SPACES
 : [ \u000B\t\r\n] -> channel(HIDDEN)
 ;

dataType: K_int | K_integer | K_float | K_double | K_char | K_string;

attributeName : NAME_STRING;
gsid : NAME_STRING;
gid : NAME_STRING;
vid : NAME_STRING;
eid : NAME_STRING;
lid : NAME_STRING;
filename : TEXT;
schemaid : NAME_STRING;
variableName: NAME_STRING;
indexInt: INTEGER_NUMBER;
paraItem : INTEGER_NUMBER | NOT_INTEGER_NUMBER | TEXT | NAME_STRING;

K_where : W H E R E;
K_drop : D R O P;
K_graphset: G R A P H S E T;
K_graph: G R A P H;
K_schema: S C H E M A;
K_insert: I N S E R T;
K_into: I N T O;
K_as: A S;
K_remove: R E M O V E;
K_from: F R O M;
K_update: U P D A T E;
K_at: A T;
K_by: B Y;
K_set: S E T;
K_query : Q U E R Y;
K_difference: D I F F E R E N C E;
K_proj: P R O J;
K_for: F O R;
K_product: P R O D U C T;
K_align: A L I G N;
K_to: T O;
K_on: O N;
K_reduce: R E D U C E;
K_select: S E L E C T;
K_map: M A P;
K_union: U N I O N;
K_join: J O I N;
K_intersect: I N T E R S E C T;
K_maximal: M A X I M A L;
K_vertex: V E R T E X;
K_edge: E D G E;
K_and: A N D;
K_or: O R;
K_arrow: '->';
K_not: N O T;
K_exist: E X I S T;
K_foreach: F O R E A C H;
K_equal: E Q U A L;
K_complete: C O M P L E T E;
K_hasedge: H A S E D G E;
K_graphequal: G R A P H E Q U A L;
K_unique: U N I Q U E;
K_sizegeq: S I Z E G E Q;
K_graphinset: G R A P H I N S E T;
K_subgraph: S U B G R A P H;
K_inducedsub: I N D U C E D S U B;
K_connect: C O N N E C T;
K_clique: C L I Q U E;
K_tdensesub: T D E N S E S U B;
K_create: C R E A T E;
K_int: I N T;
K_integer: I N T E G E R;
K_float: F L O A T;
K_double: D O U B L E;
K_char: C H A R;
K_string: S T R I N G;
K_true: T R U E;
K_false: F A L S E;
K_file: F I L E;
K_load: L O A D;

//VALUE : [+-]?([0]|([1-9][0-9]*))([.][0-9]+)? |  '"' [a-zA-Z0-9_]+ '"' | '\'' [a-zA-Z0-9_]+ '\'';
//Value := any value

INTEGER_NUMBER: [0-9] | [1-9][0-9]+;
NOT_INTEGER_NUMBER: '-' INTEGER_NUMBER '.' INTEGER_NUMBER | '-' INTEGER_NUMBER | INTEGER_NUMBER '.' INTEGER_NUMBER;
NAME_STRING : (LETTER)(LETTER | DIGIT | '\\' | '/' | '_' )*('\'')*('.' ((LETTER)(LETTER | DIGIT | '\\' | '/' | '_' )*)+('\'')*)*;
LETTER: [a-zA-Z];
SYMBOL: '|' | '!' | '#' | '$' | '%' | '&' | '(' | ')' | '*' | '+' | ',' | '-' | '.' | '/' | ':' | ';' | '>' | '=' | '<' | '?' | '@' | '[' | '\\' | ']' | '^' | '_' | '{' | '}' | '~';
CHAR: LETTER | DIGIT | SYMBOL;
TEXT: '\'' (CHAR | ' ')+ '\'';


//identifier: letter | identifier letter | identifier digit | identifier '_';
//integer: DIGIT | DIGIT integer;

fragment DIGIT : [0-9];
fragment A : [aA];
fragment B : [bB];
fragment C : [cC];
fragment D : [dD];
fragment E : [eE];
fragment F : [fF];
fragment G : [gG];
fragment H : [hH];
fragment I : [iI];
fragment J : [jJ];
fragment K : [kK];
fragment L : [lL];
fragment M : [mM];
fragment N : [nN];
fragment O : [oO];
fragment P : [pP];
fragment Q : [qQ];
fragment R : [rR];
fragment S : [sS];
fragment T : [tT];
fragment U : [uU];
fragment V : [vV];
fragment W : [wW];
fragment X : [xX];
fragment Y : [yY];
fragment Z : [zZ];
