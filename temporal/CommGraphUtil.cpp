#include "CommGraphUtil.h"

void CommGraphUtil::initCommunity(TemporalGraph& g) {
    for (int i = 1; i <= g.nodenum; ++i) {
        g.comm_map[i] = i;
        g.communities[i] = vector<int>(1, i);
	}
}

void CommGraphUtil::buildCommGraph(TemporalGraph& g, TemporalGraph& c_graph) {
    int tmax = -1;
    int tmin = -1;

	int index = 1;
	for (const auto& comm : g.communities) {
		if (comm.second.size() != 0) {
			int comm_id = comm.first;
			index = c_graph.mapID(comm_id, index);
		}
	}

	c_graph.init(index - 1);
	for (const auto& comm : g.communities) {
		if (comm.second.size() != 0) {
			int comm_id = comm.first;
			int final_comm_id = c_graph.mapper[comm_id];
            c_graph.comm_map[final_comm_id] = final_comm_id;
			c_graph.communities[final_comm_id] = vector<int>(1, final_comm_id);
		}
	}

    for (int n1 = 1; n1 <= g.nodenum; ++n1){
		int comm_n1 = c_graph.mapper[g.comm_map[n1]];
        for (const auto& np : *g.graph[n1]) {
			int n2 = np.first;
			int comm_n2 = c_graph.mapper[g.comm_map[n2]];
            if (comm_n1 == comm_n2) {
                for (const auto& t : (*g.graph[n1])[n2]) {
                    if (n1 < n2) {
                        c_graph.t_edge_num += 1;
						c_graph.sum_t_vertex[comm_n1].push_back(t);
						
						c_graph.inedge[comm_n1]++;	
						c_graph.indegree[comm_n1]++;
						c_graph.instamp[comm_n1].insert(t);
					}

                    if (tmax == -1 || t > tmax)
                        tmax = t;
                    if (tmin == -1 || t < tmin)
                        tmin = t;

                    if (n1 < n2) {
						if (c_graph.graph[comm_n1] != NULL) {
							if (c_graph.graph[comm_n1]->find(comm_n2) == c_graph.graph[comm_n1]->end()) {
                                (*c_graph.graph[comm_n1])[comm_n2] = vector<int>();                           
							}
							(*c_graph.graph[comm_n1])[comm_n2].push_back(t);
                            c_graph.degree[comm_n1] += 1;
						}
                        else {
							c_graph.graph[comm_n1] = new unordered_map<int, vector<int>>();
							(*c_graph.graph[comm_n1])[comm_n2] = vector<int>(1, t);
                            c_graph.degree[comm_n1] = 1;
						}
					}
				}
			}
			else if (comm_n1 != comm_n2) {
                for (const auto& t : (*g.graph[n1])[n2]) {
                    if (n1 < n2)
                        c_graph.t_edge_num += 1;

					c_graph.sum_t_vertex[comm_n1].push_back(t);

                    if (tmax == -1 || t > tmax)
                        tmax = t;
                    if (tmin == -1 || t < tmin)
                        tmin = t;

					if (c_graph.graph[comm_n1] != NULL) { 
						if (c_graph.graph[comm_n1]->find(comm_n2) == c_graph.graph[comm_n1]->end())
                            (*c_graph.graph[comm_n1])[comm_n2] = vector<int>();
						(*c_graph.graph[comm_n1])[comm_n2].push_back(t);
                        c_graph.degree[comm_n1] += 1;
					}
                    else {
						c_graph.graph[comm_n1] = new unordered_map<int, vector<int>>();
						(*c_graph.graph[comm_n1])[comm_n2] = vector<int>(1, t);
                        c_graph.degree[comm_n1] = 1;
					}
				}
			}
		}
	}

    c_graph.t_gap = tmax - tmin;
	for (int i = 1; i < g.sum_t_vertex.size(); ++i) {
		sort(g.sum_t_vertex[i].begin(), g.sum_t_vertex[i].end());
	}
}

void CommGraphUtil::convertCommGraph(TemporalGraph& g, TemporalGraph& c_graph) {
	unordered_map<int, vector<int>> copy_communities;

    for (const auto& c_comm : c_graph.communities) {
		for (const auto& comm : c_graph.communities[c_comm.first]) {
			int ori_comm = c_graph.rev_mapper[comm];
			if (copy_communities.find(c_comm.first) != copy_communities.end())
				copy_communities[c_comm.first].insert(copy_communities[c_comm.first].end(), g.communities[ori_comm].begin(), g.communities[ori_comm].end());
            else
                copy_communities[c_comm.first] = g.communities[ori_comm];

            for (const auto& n : g.communities[ori_comm])
				g.comm_map[n] = c_comm.first;
		}
	}

	g.communities = copy_communities;
	g.instamp = c_graph.instamp;
	g.comm_Ex = c_graph.comm_Ex;
	g.comm_Ex2 = c_graph.comm_Ex2;
	g.comm_edge = c_graph.comm_edge;
}
