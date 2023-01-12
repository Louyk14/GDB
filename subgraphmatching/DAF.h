#ifndef DAF_H
#define DAF_H

#include "../MemoryGraph.h"
// #include "MatchGraph.h"
#include "Match.h"
#include "daftypes.h"
#include "ComputeSetIntersection.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <assert.h>
#include <vector>
#include <bitset>

using namespace std;

// Min priority queue.
static auto extendable_vertex_compare = [](std::pair<std::pair<VertexID, ui>, ui> l, std::pair<std::pair<VertexID, ui>, ui> r) {
    if (l.first.second == 1 && r.first.second != 1) {
        return true;
    }
    else if (l.first.second != 1 && r.first.second == 1) {
        return false;
    }
    else
    {
        return l.second > r.second;
    }
};

typedef std::priority_queue<std::pair<std::pair<VertexID, ui>, ui>, std::vector<std::pair<std::pair<VertexID, ui>, ui>>,
        decltype(extendable_vertex_compare)> dpiso_min_pq;

class DAF
{
public:
    DAF(MemoryGraph* data_graph, MemoryGraph* query_graph);
    DAF();
    ~DAF();

	MemoryGraph *q;
	MemoryGraph *g;

    Match* gm;
	MemoryGraph* data;

    //vector<vector<Edges*>> edge_matrix;
    //vector<vector<ui>> weight_array;
    int itercount;

    ui* dpiso_order;
    TreeNode* dpiso_tree;
    ui** candidates;
	ui** saver_candidates;
	void init();
	bool boundfirst;
	bool recfirst;
	bool candupdated;
	std::vector<dpiso_min_pq> vec_rank_queue;

    ui* candidates_count;
    Edges ***edge_matrix;
	Edges ***save_edge_matrix;
    ui* matching_order;
    ui* pivots;
    ui** weight_array;
    ui* updated_flag;
    ui* flag;
    ui *extendable;
    ui **bn;
    ui *bn_count;
    ui *idx;
    ui *idx_count;
    ui *embedding;
    ui *idx_embedding;
    ui *temp_buffer;
    ui **valid_candidate_idx;
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> ancestors;
	std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>* ancestors; 
	bool* visited_vertices;
	VertexID* reverse_embedding;
	bitset<MAXIMUM_QUERY_GRAPH_SIZE>* vec_failing_set;
	unordered_set<Edges*> rubbishbin;
	int* flag_comm;
	bool* endmax;

    vector<vector<int>>* vvans;
    vector<vector<int>*> vans;
    vector<map<int, vector<int>>>* superans;
    vector<vector<vector<int>>>* tans;
    vector<MemoryGraph*>* communityGraphs;
    int** n2cNum;
    vector<vector<int>> recn2c;
	MemoryGraph* originalgraph;
    map<vector<int>, string>* isomap;
    int* distributeplan;
    //unordered_map<int, int>* distributeplan;
    vector<map<int, int>>* newallmaps;
    int** nodeArea;
	int* nodeArea_count;
	int** schemes;
	int schemenum;

    int** boundary;
	int* boundary_count;
	int** save_boundary;
    //vector<int*> pointers;

    vector<vector<int>>* equalq;
	bool** equalq_ptr;
    vector<int>* pIETreeL;
    vector<int>* pIETreeS;
	bool** paIETreeL;
	bool** aIETreeL;
	int** candmap;
	int** saver_candmap;
	int* pivot_pos;
	int* neigh_start;
	bool* neigh_find;

	int* esetno;
	vector<int> eset;
	vector<int> esetcand;

	vector<int>* IETreeL;
	vector<int>* IETreeS;
    vector<int*> pschemes;
	vector<int>* penv;
	vector<vector<int>>* penv_en;
	//vector<vector<int>> toadd;
	vector<int>* toadd;
	vector<pair<int, int>>* existaddpos;
	unordered_set<int>* hascand;

    DAF* recdaf;
    DAF* bounddaf;
    DegreePos p;
	ui** overall_candidates;
	ui* overall_candidates_count;
	Edges **overall_edge_matrix;
	ui** cand_idx_mapper;
	ui** cand_idx_mapper_rev;

    int* newM;
    //vector<vector<int>> supert;
	int** supert;
	int* supertcount;
	int commnum;
    //vector<int> supermapper;
	int* supermapper;
    unordered_map<int, int> superc2cMap;

    void allocateBuffer(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates,
                                    ui *&candidates_count);
    void allocateBuffer_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates,
                                    ui *&candidates_count);
    void eva_allocateBuffer(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui *candidates_count, ui *&idx,
                              ui *&idx_count, ui *&embedding, ui *&idx_embedding, ui *&temp_buffer,
                              ui **&valid_candidate_idx, bool *&visited_vertices);
    void eva_allocateBuffer_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui *candidates_count, ui *&idx,
                              ui *&idx_count, ui *&embedding, ui *&idx_embedding, ui *&temp_buffer,
                              ui **&valid_candidate_idx);
    void eva_releaseBuffer(ui query_vertices_num, ui *idx, ui *idx_count, ui *embedding, ui *idx_embedding,
                                  ui *temp_buffer, ui **valid_candidate_idx, bool *visited_vertices, ui **bn,
                                  ui *bn_count);
    void eva_releaseBuffer_comm(ui query_vertices_num, ui *idx, ui *idx_count, ui *embedding, ui *idx_embedding,
                                  ui *temp_buffer, ui **valid_candidate_idx, ui **bn,
                                  ui *bn_count);
    void generateDPisoFilterPlan(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *&tree,
                                                    VertexID *&order);

	void generateDPisoFilterPlan_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *&tree,
                                                    VertexID *&order);

    void generateDSPisoQueryPlan(const MemoryGraph *query_graph, ui *&order, ui *&pivot,
                                                TreeNode *tree, ui *bfs_order, ui *candidates_count);
    void generateDSPisoQueryPlan_comm(const MemoryGraph *query_graph, ui *&order, ui *&pivot,
                                                TreeNode *tree, ui *bfs_order, ui *candidates_count);
	void generateDSPisoQueryPlanBound(const MemoryGraph *query_graph, ui *&order, ui *&pivot,
                                                TreeNode *tree, ui *bfs_order, ui *candidates_count);
    VertexID selectDPisoStartVertex(const MemoryGraph *data_graph, const MemoryGraph *query_graph);
	VertexID selectDPisoStartVertexBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph);
    void computeCandidateWithLDF(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                             ui &count, ui *buffer = NULL);
    void bfsTraversal(const MemoryGraph *graph, VertexID root_vertex, TreeNode *&tree, VertexID *&bfs_order);
	void bfsTraversalBound(const MemoryGraph *graph, VertexID root_vertex, TreeNode *&tree, VertexID *&bfs_order);
    void pruneCandidates(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesImp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesBoundUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesBoundNew(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesBoundImp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesDenseUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesDenseImp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
    bool LDFFilter(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count);
    bool DPisoFilter(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree);

    void compactCandidates(ui **&candidates, ui *&candidates_count, ui query_vertex_num);
	bool compactCandidatesBound(ui **&candidates, ui *&candidates_count, ui query_vertex_num);
    bool isCandidateSetValid(ui **&candidates, ui *&candidates_count, ui query_vertex_num);
    void sortCandidates(ui **candidates, ui *candidates_count, ui num);

    size_t startMatch();

    void buildTables(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);
	void buildTablesUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);
	void buildTablesSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);
	void buildTablesDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);
    void buildTables_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);
	void refineTables(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);
	void buildTablesBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count);

    size_t exploreDPisoStyle(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order);
    void generateBN(const MemoryGraph *query_graph, ui *order, ui **&bn, ui *&bn_count);
	void generateBNBound(const MemoryGraph *query_graph, ui *order, ui **&bn, ui *&bn_count);
    void restoreExtendableVertex(TreeNode *tree, VertexID unmapped_vertex, ui *extendable);
    void updateExtendableVertex(ui *idx_embedding, ui *idx_count, ui **valid_candidate_index,
                                           ui *&temp_buffer,
                                           TreeNode *tree, VertexID mapped_vertex, ui *extendable,
                                           std::vector<dpiso_min_pq> &vec_rank_queue, const MemoryGraph *query_graph);
    void generateValidCandidateIndex(VertexID u, ui *idx_embedding, ui *idx_count, ui *&valid_candidate_index,
                                           ui *bn, ui bn_cnt, ui *&temp_buffer);
	void generateValidCandidateIndex_comm(VertexID u, ui *idx_embedding, ui *idx_count, ui *&valid_candidate_index,
                                           ui *bn, ui bn_cnt, ui *&temp_buffer);
	void updateExtendableVertexBound(ui *idx_embedding, ui *idx_count, ui **valid_candidate_index,
                                           ui *&temp_buffer,
                                           TreeNode *tree, VertexID mapped_vertex, ui *extendable,
                                           std::vector<dpiso_min_pq> &vec_rank_queue, const MemoryGraph *query_graph);
    void generateValidCandidateIndexBound(VertexID u, ui *idx_embedding, ui *idx_count, ui *&valid_candidate_index,
                                           ui *bn, ui bn_cnt, ui *&temp_buffer);

    // comm dafs
    //super
    size_t startMatch_comm();
    bool LDFFilterSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count);
    bool DPisoFilterSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree);
    void generateDPisoFilterPlanSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *&tree,
                                                    VertexID *&order);
    VertexID selectDPisoStartVertexSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph);
    void computeCandidateWithLDFSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                             ui &count, ui *buffer = NULL);
    void pruneCandidatesSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
	void pruneCandidatesSuperUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag);
    size_t exploreDPisoStyleSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order);

    void rematch_DAF(int** supermatch, int* c2cmapper, int* supermatchmap, int* supermatchmapori
        , vector<MemoryGraph*>& communityGraphs, MemoryGraph& patternGraph);

    void initIETree();
    void initpIETree(int* supermatchmap);

    //dense
    size_t startMatchDense();
    bool DPisoFilterDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree);
    bool LDFFilterDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count);
    size_t exploreDPisoStyleDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order);

    //bound
    size_t startMatchBound();
    size_t exploreDPisoStyleBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order);
    bool LDFFilterBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count);
    bool DPisoFilterBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree);
	//void buildTables_comm_overall(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count, Edges** edge_matrix);

    // failing set
    void computeAncestor(const MemoryGraph *query_graph, TreeNode *tree, VertexID *order);
	void computeAncestorBound(const MemoryGraph *query_graph, TreeNode *tree, VertexID *order);

	bool getCompleteMatch(int* supermatchmap, vector<int>& allmaps);

	void refineCandidates(int pivot, int cur);
};

#endif