#ifndef TURBOMATCH_H
#define TURBOMATCH_H

#include "../MemoryGraph.h"
//#include "MatchGraph.h"
#include "TurboGraph.h"
#include "Match.h"
#include <string>
#include <algorithm>

using namespace std;

class Match;

class TurboMatch
{
public:
	MemoryGraph* q;
	MemoryGraph* g;

	Match* gm;
	MemoryGraph* data;

	int** ranks;

	bool degree;
	vector<vector<int>*>* nodeArea;
	//unordered_map<int, unordered_set<int>>* nodeAreaSet;
	//unordered_map<int, unordered_set<int>> nodeCommunitySet;

	int memberNum;
	//bool isLeader;
	//vector<int>* leaderSC;

	int storeType;
	vector<vector<int>>* vvans;
	vector<vector<int>*> vans;
	vector<map<int, vector<int>>>* superans;
	vector<vector<vector<int>>>* tans;
	vector<MemoryGraph*>* communityGraphs;
	vector<vector<int>> n2cNum;
	vector<vector<int>> recn2c;
	MemoryGraph* originalgraph;
	map<vector<int>, string>* isomap;
	int* distributeplan;
	//unordered_map<int, int>* distributeplan;
	vector<map<int, int>>* newallmaps;

	string* featurestr;
	unordered_map<int, int>* subans;

	int firstpattern;
	int firstmatch;
	int comm_id;
	string filename;
	int core;// = 4;
	int news;
	DegreePos p;
	vector<DegreePos> dprec;

	// comm -> nodes
	
	int* ncMap;//unordered_map<int, int> ncMap;
	unordered_map<int, int> nodeOrder;
	int* level;

	TurboMatch* rectm;
	TurboMatch* boundtm;
	CRTree CR;
	NECTree q_prime;
	unordered_map<int, int> outds;
	vector<vector<int>> outcomm;
	vector<vector<int>*> boundary;
	vector<vector<int>*> pointers;
	int *u;
	int *candN;
	bool *flag;
	vector<LabelVList*> CPer;
	int* newM;
	int* M;
	bool *F;
	vector<vector<int>> supert;
	vector<int> supermapper;
	unordered_map<int, int> superc2cMap;
	vector<NECTree>* q_primes;
	vector<vector<int>> penv;
	vector<vector<vector<int>>> penv_en;
	vector<vector<int>> toadd;
	vector<vector<pair<int, int>>> existaddpos;
	int addpos;

	vector<vector<int>>* equalq;
	vector<vector<int>> pIETreeL;
	vector<vector<int>> pIETreeS;
	vector<vector<int>*> pschemes;

	unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oomessage;// = NULL;
	unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oimessage;// = NULL;
	unordered_map<int, unordered_map<int, unordered_map<int, int>>>* iomessage;// = NULL;

	~TurboMatch()
	{
		if (rectm != NULL)
			delete rectm;
		if (boundtm != NULL)
			delete boundtm;
	}
	TurboMatch();
	TurboMatch(int comm, vector<vector<int>*>* boundary, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oomessage,
		unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oimessage,
		unordered_map<int, unordered_map<int, unordered_map<int, int>>>* iomessage,
		MemoryGraph* g, MemoryGraph* query, MemoryGraph* graph);
	TurboMatch(string& f);
	void init(bool tough = false);
	//void createTempGraph(string nodefile, string edgefile, TempGraph* &t);
	//void createTempGraph(string filename, TempGraph* &t);
	void SetFile(string& f);
	int TurboISO(MemoryGraph* q, MemoryGraph* g, bool& candup, int comm_id);
	int TurboISODense(MemoryGraph* q, MemoryGraph* g, bool& candup, int comm_id);
	int TurboISOSuper(MemoryGraph* q, MemoryGraph* g, bool& candup);
	int TurboISOBound(MemoryGraph* q, MemoryGraph* g, bool& candup);
	//int TurboISO(TempGraph* q, TempGraph* g, NECTree& q_prime, bool& candup);

	int contain(int e, vector<LabelVList> *tmp);
	int contain(int e, vector<LabelVList*> *tmp);
	template<class T> int contain(T e, vector<T> *tmp);
	bool equals(vector<LabelVList> *v1, vector<LabelVList> *v2);
	int ChooseStartQVertex(MemoryGraph* q, MemoryGraph* g);
	void FindNEC(vector<vector<Vid>> *NECV, vector <Vid> *vertexList, MemoryGraph *q);
	void RewriteToNECTree(MemoryGraph *q, int U_s, NECTree *q_prime);
	void BuildNECTree(MemoryGraph *q, int U_s, NECTree *q_prime);
	void ClearCR(Vid uc_Dprime, Vid v_prime, CRTree *CR);
	bool ExploreCR(int u_prime, unordered_set<Vid> *VM, CRTree *CR, Vid v, NECTree *q_prime, MemoryGraph *g, MemoryGraph *q, bool* visited, bool& candup);
	bool ExploreCR(int u_prime, vector<Vid> *VM, CRTree *CR, Vid v, NECTree *q_prime, MemoryGraph *g, MemoryGraph *q, bool* visited, bool& candup);
	double C(int n, int m);
	double DetermineMatchingOrder(NECTree *q_prime, CRTree *CRTree, TurboElem *order, Vid v, int product, MemoryGraph *q);
	void UpdateState(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV);
	void UpdateState(int* M, vector <Vid> *qV, vector <Vid> *gV);
	void UpdateStateDense(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV);
	void NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, NECTree *q_prime, bool super=false);
	void NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, NECTree *q_prime, int& midvalpos, int& midval, int& bigpos, bool super=false);
	//void NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, NECTree *q_prime, unordered_map<int, int>& smallvalpos, unordered_map<int, int>& bigvalpos);
	void NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, int& u_prime, NECTree *q_primed);
	int GetComb(vector <Vid>& C, int Size, vector<int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos);
	int GetFirst(vector <Vid>& C, int Size, vector<int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos);
	int GetCombDense(vector <Vid>& C, int Size, vector<int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos);
	int GetFirstDense(vector <Vid>& C, int Size, vector<int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos);
	int GetFirstBound(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos);
	int GetCombBound(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos);
	bool IsJoinable(int* M, int qV, int gV);
	bool IsJoinableSuper(MemoryGraph *q, MemoryGraph *g, int* M, int qV, int gV);
	void output(int* M, int qVNum, int& count);
	bool NextPerm(int* M, vector <Vid> *qV, vector<Vid> *mV, int *rank, bool& candup);
	void GenPerm(int* M, NECTree *q_prime, int i, MemoryGraph* q, MemoryGraph* g, int& count, bool& candup);
	void RestoreState(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV);
	void RestoreState(int* M, vector <Vid> *qV, vector <Vid> *gV);
	void RestoreStateDense(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV);
	void SubgraphSearch(NECTree *q_prime, TurboElem *order, int dc, int* M, bool* F, CRTree *CR, int& count, bool& candup);
	void SubgraphSearchDense(MemoryGraph *q, NECTree *q_prime, MemoryGraph *g, TurboElem *order, int dc, int* M, CRTree *CR, int& count, bool& candup);
	void SubgraphSearchSuper(MemoryGraph *q, NECTree *q_prime, MemoryGraph *g, TurboElem *order, int dc, int* M, CRTree *CR, int& count, bool& candup);
	void SubgraphSearchBound(NECTree *q_prime, TurboElem *order, int dc, int* M, bool* F, CRTree *CR, int& count, bool& candup);

	void rematch_Turbo(vector<vector<int>>& supermatch, vector<int>& c2cmapper, int* supermatchmap, int* supermatchmapori
		, vector<MemoryGraph*>& communityGraphs, MemoryGraph& patternGraph);

	void initIETree();
	void initpIETree(int* supermatchmap);
};

#endif