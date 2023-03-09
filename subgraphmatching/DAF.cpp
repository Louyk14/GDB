#include "DAF.h"

#define INVALID_VERTEX_ID 100000000
#define ENABLE_FAILING_SET

static bool cmpD(const DegreePos& a, const DegreePos& b)
{
    return a.degree < b.degree;
}

DAF::DAF(MemoryGraph* data_graph, MemoryGraph* query_graph, MemoryGraph* d) {
    g = data_graph;
    q = query_graph;
    data = d;

    itercount = 0;

    candidates = NULL;
    candidates_count = NULL;
    dpiso_tree = NULL;
    dpiso_order = NULL;
    matching_order = NULL;
    pivots = NULL;

    nodeArea = NULL;
    vans = vector<vector<int>*>(4);
    recdaf = NULL;
    bounddaf = NULL;
    
    //edge_matrix = vector<vector<Edges*>>(q->nodenum + 1, vector<Edges*>(q->nodenum + 1, NULL));
    edge_matrix = new Edges **[q->nodeNum + 1];
    weight_array = new ui *[q->nodeNum + 1];
    for (ui i = 0; i < q->nodeNum + 1; ++i) {
        edge_matrix[i] = new Edges* [q->nodeNum + 1];
        for (int j = 0; j < q->nodeNum + 1; ++j)
            edge_matrix[i][j] = NULL;
        //memset(edge_matrix[i], NULL, (q->nodenum + 1) * sizeof(Edges*));
        //fill(edge_matrix[i], edge_matrix[i] + q->nodenum + 1, NULL);

        weight_array[i] = new ui[g->nodeNum + 1];
        memset(weight_array[i], std::numeric_limits<ui>::max(), (g->nodeNum + 1) * sizeof(ui));
    }
    
    //weight_array = vector<vector<ui>>(q->nodenum + 1, vector<ui>(g->nodenum + 1, std::numeric_limits<ui>::max()));
}

DAF::DAF() {
    candidates = NULL;
    candidates_count = NULL;
    dpiso_tree = NULL;
    dpiso_order = NULL;
    matching_order = NULL;
    pivots = NULL;

    nodeArea = NULL;
    vans = vector<vector<int>*>(4);
    recdaf = NULL;
    bounddaf = NULL;
}

DAF::~DAF() {
    delete[] candidates_count;
    delete[] dpiso_order;
    delete[] dpiso_tree;
    delete[] matching_order;
    delete[] pivots;
    //for (ui i = 0; i <= q->nodenum; ++i) {
    //    delete[] candidates[i];
    //}
    //delete[] candidates;

    //if (recdaf != NULL)
    //  delete recdaf;
    //if (bounddaf != NULL)
    //  delete bounddaf;

    /*if (edge_matrix != NULL) {
        for (ui i = 1; i <= q->nodenum; ++i) {
            for (ui j = 0; j <= q->nodenum; ++j) {
                if (edge_matrix[i][j] != NULL)
                    delete edge_matrix[i][j];
            }
            delete[] edge_matrix[i];
        }
        delete[] edge_matrix;
    }
    if (weight_array != NULL) {
        for (ui i = 0; i <= q->nodenum; ++i) {
            delete[] weight_array[i];
        }
        delete[] weight_array;
    }*/
}

void DAF::allocateBuffer(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates,
                                    ui *&candidates_count) {
    ui query_vertex_num = q->nodeNum ;
    ui candidates_max_num = g->nodeNum;

    candidates_count = new ui[query_vertex_num + 1];
    memset(candidates_count, 0, sizeof(ui) * (query_vertex_num + 1));

    candidates = new ui*[query_vertex_num + 1];

    for (ui i = 0; i <= query_vertex_num; ++i) {
        candidates[i] = new ui[candidates_max_num];
    }
}

void DAF::allocateBuffer_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates,
                                    ui *&candidates_count) {
    ui query_vertex_num = q->nodeNum ;
    ui candidates_max_num = g->nodeNum;

    //candidates_count = new ui[query_vertex_num + 1];
    memset(candidates_count, 0, sizeof(ui) * (query_vertex_num + 1));

    /*candidates = new ui*[query_vertex_num + 1];

    for (ui i = 0; i <= query_vertex_num; ++i) {
        candidates[i] = new ui[candidates_max_num];
    }*/
}

void DAF::eva_allocateBuffer(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui *candidates_count, ui *&idx,
                              ui *&idx_count, ui *&embedding, ui *&idx_embedding, ui *&temp_buffer,
                              ui **&valid_candidate_idx, bool *&visited_vertices) {
    ui query_vertices_num = query_graph->nodeNum;
    ui data_vertices_num = data_graph->nodeNum;
    ui max_candidates_num = candidates_count[1];

    for (ui i = 2; i <= query_vertices_num; ++i) {
        VertexID cur_vertex = i;
        ui cur_candidate_num = candidates_count[cur_vertex];

        if (cur_candidate_num > max_candidates_num) {
            max_candidates_num = cur_candidate_num;
        }
    }

    idx = new ui[query_vertices_num + 1];
    idx_count = new ui[query_vertices_num + 1];
    embedding = new ui[query_vertices_num + 1];
    fill(embedding, embedding + query_vertices_num + 1, -1);
    idx_embedding = new ui[query_vertices_num + 1];
    visited_vertices = new bool[data_vertices_num + 1];
    temp_buffer = new ui[max_candidates_num + 1];
    valid_candidate_idx = new ui *[query_vertices_num + 1];
    for (ui i = 0; i <= query_vertices_num; ++i) {
        valid_candidate_idx[i] = new ui[max_candidates_num];
    }

    std::fill(visited_vertices, visited_vertices + data_vertices_num + 1, false);
}

void DAF::eva_allocateBuffer_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui *candidates_count, ui *&idx,
                              ui *&idx_count, ui *&embedding, ui *&idx_embedding, ui *&temp_buffer,
                              ui **&valid_candidate_idx) {
    //ui query_vertices_num = query_graph->nodenum;
    //ui data_vertices_num = data_graph->nodenum;
    //ui max_candidates_num = candidates_count[1];

    /*for (ui i = 2; i <= query_vertices_num; ++i) {
        VertexID cur_vertex = i;
        ui cur_candidate_num = candidates_count[cur_vertex];

        if (cur_candidate_num > max_candidates_num) {
            max_candidates_num = cur_candidate_num;
        }
    }

    idx = new ui[query_vertices_num + 1];
    idx_count = new ui[query_vertices_num + 1];
    embedding = new ui[query_vertices_num + 1];
    idx_embedding = new ui[query_vertices_num + 1];
    visited_vertices = new bool[data_vertices_num + 1];
    temp_buffer = new ui[max_candidates_num + 1];
    valid_candidate_idx = new ui *[query_vertices_num + 1];
    for (ui i = 0; i <= query_vertices_num; ++i) {
        valid_candidate_idx[i] = new ui[max_candidates_num];
    }*/

    //std::fill(visited_vertices.begin(), visited_vertices.end(), false);
    //memset(this->visited_vertices.begin(), false, this->visited_vertices.size() * sizeof(bool));
}

void DAF::eva_releaseBuffer(ui query_vertices_num, ui *idx, ui *idx_count, ui *embedding, ui *idx_embedding,
                                  ui *temp_buffer, ui **valid_candidate_idx, bool *visited_vertices, ui **bn,
                                  ui *bn_count) {
    delete[] idx;
    delete[] idx_count;
    delete[] embedding;
    delete[] idx_embedding;
    delete[] visited_vertices;
    delete[] bn_count;
    delete[] temp_buffer;
    for (ui i = 0; i <= query_vertices_num; ++i) {
        delete[] valid_candidate_idx[i];
        delete[] bn[i];
    }

    delete[] valid_candidate_idx;
    delete[] bn;
}

void DAF::eva_releaseBuffer_comm(ui query_vertices_num, ui *idx, ui *idx_count, ui *embedding, ui *idx_embedding,
                                  ui *temp_buffer, ui **valid_candidate_idx, ui **bn,
                                  ui *bn_count) {
    /*delete[] idx;
    delete[] idx_count;
    delete[] embedding;
    delete[] idx_embedding;
    delete[] visited_vertices;
    delete[] bn_count;
    delete[] temp_buffer;
    for (ui i = 0; i <= query_vertices_num; ++i) {
        delete[] valid_candidate_idx[i];
        delete[] bn[i];
    }

    delete[] valid_candidate_idx;
    delete[] bn;*/
}


bool DAF::LDFFilter(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count) {
    allocateBuffer(data_graph, query_graph, candidates, candidates_count);

    for (ui i = 1; i <= q->nodeNum; ++i) {
        LabelID label = 0;
        ui degree = q->degrees[i];

        //ui data_vertex_num;
        //const ui* data_vertices = g->getVerticesByLabel(label, data_vertex_num);

        //for (ui j = 0; j < data_vertex_num; ++j) {
        //    ui data_vertex = data_vertices[j];
        //    if (g->getVertexDegree(data_vertex) >= degree) {
        //        candidates[i][candidates_count[i]++] = data_vertex;
        //    }
        //}
        for (ui j = 0; j < g->nodeNum; ++j) {
            ui data_vertex = g->nodes[j];
            if (g->degrees[data_vertex] >= degree) {
				candmap[i][data_vertex] = candidates_count[i];
                candidates[i][candidates_count[i]++] = data_vertex;
            }
        }

        if (candidates_count[i] == 0) {
            return false;
        }
    }

    return true;
}

void DAF::computeCandidateWithLDF(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                             ui &count, ui *buffer) {
    LabelID label = 0;
    ui degree = query_graph->degrees[query_vertex];
    count = 0;
    //ui data_vertex_num;
    //const ui* data_vertices = data_graph->getVerticesByLabel(label, data_vertex_num);

    if (buffer == NULL) {
        for (ui i = 0; i < data_graph->nodeNum; ++i) {
            VertexID v = data_graph->nodes[i];
            if (data_graph->degrees[v] >= degree) {
                count += 1;
            }
        }
    }
    else {
        for (ui i = 0; i < data_graph->nodeNum; ++i) {
            VertexID v = data_graph->nodes[i];
            if (data_graph->degrees[v] >= degree) {
                buffer[count++] = v;
            }
        }
    }
}

VertexID DAF::selectDPisoStartVertex(const MemoryGraph *data_graph, const MemoryGraph *query_graph) {
    double min_score = data_graph->nodeNum;
    VertexID start_vertex = 1;

    for (ui i = 1; i <= query_graph->nodeNum; ++i) {
        ui degree = query_graph->degrees[i];
        if (degree <= 1)
            continue;

        ui count = 0;
        computeCandidateWithLDF(data_graph, query_graph, i, count);
        double cur_score = count / (double)degree;
        if (cur_score < min_score) {
            min_score = cur_score;
            start_vertex = i;
        }
    }

    return start_vertex;
}

VertexID DAF::selectDPisoStartVertexBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph) {
    double min_score = data_graph->nodeNum;
    VertexID start_vertex = 1;

    for (ui i = 1; i <= query_graph->nodeNum; ++i) {
        ui degree = query_graph->degrees[i];
        if (degree <= 1)
            continue;

        ui count = 0;

        VertexID query_vertex = i;
        //ui data_vertex_num;
        //const ui* data_vertices = data_graph->getVerticesByLabel(label, data_vertex_num);

        if (nodeArea[i] == NULL)
        {
            // do not use (*communityGraphs)[distributeplan[i]]->nodes because their ids are mapped to 1, 2, 3, ...
            /*auto c = &data->communityNodes[distributeplan[i]];
            for (ui j = 0; j < c->size(); ++j) {
                ui data_vertex = (*c)[j];
                if (g->degrees[data_vertex] >= degree) {
                    count++;
                }
            }*/
            count = data->communityNodes[distributeplan[i]].size();
        }
        else
        {
            count = nodeArea_count[i];
            //for (ui j = 0; j < (*nodeArea)[i]->size(); ++j) {
            //  ui data_vertex = (*(*nodeArea)[i])[j];
            //  count++;
            //}
        }

        double cur_score = count / (double)degree;
        if (cur_score < min_score) {
            min_score = cur_score;
            start_vertex = i;
        }
    }

    return start_vertex;
}

void DAF::bfsTraversal(const MemoryGraph *graph, VertexID root_vertex, TreeNode *&tree, VertexID *&bfs_order) {
    ui vertex_num = graph->nodeNum;

    std::queue<VertexID> bfs_queue;
    std::vector<bool> visited(vertex_num + 1, false);

    tree = new TreeNode[vertex_num + 1];
    for (ui i = 1; i <= vertex_num; ++i) {
        tree[i].initialize(vertex_num);
    }
    bfs_order = new VertexID[vertex_num + 1];

    ui visited_vertex_count = 0;
    bfs_queue.push(root_vertex);
    visited[root_vertex] = true;
    tree[root_vertex].level_ = 0;
    tree[root_vertex].id_ = root_vertex;

    while(!bfs_queue.empty()) {
        const VertexID u = bfs_queue.front();
        bfs_queue.pop();
        bfs_order[visited_vertex_count++] = u;

        ui u_nbrs_count;
        //const VertexID* u_nbrs = graph->getVertexNeighbors(u, u_nbrs_count);
        for (const auto& u_nbr : graph->outvecp[u]) {
        //for (ui i = 0; i < u_nbrs_count; ++i) {
            //VertexID u_nbr = u_nbrs[i];
            if (!visited[u_nbr]) {
                bfs_queue.push(u_nbr);
                visited[u_nbr] = true;
                tree[u_nbr].id_ = u_nbr;
                tree[u_nbr].parent_ = u;
                tree[u_nbr].level_ = tree[u] .level_ + 1;
                tree[u].children_[tree[u].children_count_++] = u_nbr;
            }
        }
    }
}

void DAF::bfsTraversalBound(const MemoryGraph *graph, VertexID root_vertex, TreeNode *&tree, VertexID *&bfs_order) {
    ui vertex_num = graph->nodeNum;

    std::queue<VertexID> bfs_queue;
    std::vector<bool> visited(vertex_num + 1, false);

    //tree = new TreeNode[vertex_num + 1];
    //for (ui i = 1; i <= vertex_num; ++i) {
    //    tree[i].initialize(vertex_num);
    //}
    //bfs_order = new VertexID[vertex_num + 1];

    ui visited_vertex_count = 0;
    bfs_queue.push(root_vertex);
    visited[root_vertex] = true;
    tree[root_vertex].init();
    tree[root_vertex].level_ = 0;
    tree[root_vertex].id_ = root_vertex;

    while(!bfs_queue.empty()) {
        const VertexID u = bfs_queue.front();
        bfs_queue.pop();
        bfs_order[visited_vertex_count++] = u;

        ui u_nbrs_count;
        //const VertexID* u_nbrs = graph->getVertexNeighbors(u, u_nbrs_count);
        for (const auto& u_nbr : graph->outvecp[u]) {
        //for (ui i = 0; i < u_nbrs_count; ++i) {
            //VertexID u_nbr = u_nbrs[i];
            if (!visited[u_nbr]) {
                bfs_queue.push(u_nbr);
                visited[u_nbr] = true;
                tree[u_nbr].init();
                tree[u_nbr].id_ = u_nbr;
                tree[u_nbr].parent_ = u;
                tree[u_nbr].level_ = tree[u].level_ + 1;
                tree[u].children_[tree[u].children_count_++] = u_nbr;
            }
        }
    }
}

void DAF::generateDPisoFilterPlan(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *&tree,
                                                    VertexID *&order) {
    VertexID start_vertex = selectDPisoStartVertex(data_graph, query_graph);
    bfsTraversal(query_graph, start_vertex, dpiso_tree, dpiso_order);

    ui query_vertices_num = query_graph->nodeNum;
    std::vector<ui> order_index(query_vertices_num + 1);
    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID query_vertex = dpiso_order[i];
        order_index[query_vertex] = i;
    }

    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID u = dpiso_order[i];
        dpiso_tree[u].under_level_count_ = 0;
        dpiso_tree[u].bn_count_ = 0;
        dpiso_tree[u].fn_count_ = 0;

        ui u_nbrs_count;
        //const VertexID* u_nbrs = q->getVertexNeighbors(u, u_nbrs_count);
        //for (ui j = 0; j < u_nbrs_count; ++j) {
        for (const auto& u_nbr : query_graph->outvecp[u]) {
            //VertexID u_nbr = u_nbrs[j];
            if (order_index[u_nbr] < order_index[u]) {
                dpiso_tree[u].bn_[dpiso_tree[u].bn_count_++] = u_nbr;
            }
            else {
                dpiso_tree[u].fn_[dpiso_tree[u].fn_count_++] = u_nbr;
            }
        }
    }
}

void DAF::generateDPisoFilterPlan_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *&tree,
                                                    VertexID *&order) {
    VertexID start_vertex = selectDPisoStartVertexBound(data_graph, query_graph);
    
    bfsTraversalBound(query_graph, start_vertex, dpiso_tree, dpiso_order);

    ui query_vertices_num = query_graph->nodeNum;
    std::vector<ui> order_index(query_vertices_num + 1);
    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID query_vertex = dpiso_order[i];
        order_index[query_vertex] = i;
    }

    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID u = dpiso_order[i];
        dpiso_tree[u].under_level_count_ = 0;
        dpiso_tree[u].bn_count_ = 0;
        dpiso_tree[u].fn_count_ = 0;

        ui u_nbrs_count;
        //const VertexID* u_nbrs = q->getVertexNeighbors(u, u_nbrs_count);
        //for (ui j = 0; j < u_nbrs_count; ++j) {
        for (const auto& u_nbr : query_graph->outvecp[u]) {
            //VertexID u_nbr = u_nbrs[j];
            if (order_index[u_nbr] < order_index[u]) {
                dpiso_tree[u].bn_[dpiso_tree[u].bn_count_++] = u_nbr;
            }
            else {
                dpiso_tree[u].fn_[dpiso_tree[u].fn_count_++] = u_nbr;
            }
        }
    }
}

void DAF::generateDSPisoQueryPlan(const MemoryGraph *query_graph, ui *&order, ui *&pivot,
                                                TreeNode *tree, ui *bfs_order, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    order = new ui[query_vertices_num];
    pivot = new ui[query_vertices_num];

    for (ui i = 0; i < query_vertices_num; ++i) {
        order[i] = bfs_order[i];
    }

    for (ui i = 1; i < query_vertices_num; ++i) {
        pivot[i] = tree[order[i]].parent_;
    }

    // Compute weight array.
    //for (int i = 1; i < weight_array.size(); ++i)
    //  std::fill(weight_array[i].begin(), weight_array[i].begin() + candidates_count[i], std::numeric_limits<ui>::max());

    for (int i = query_vertices_num - 1; i >= 0; --i) {
        VertexID vertex = order[i];
        TreeNode& node = tree[vertex];
        bool set_to_one = true;

        for (ui j = 0; j < node.fn_count_; ++j) {
            VertexID child = node.fn_[j];
            TreeNode& child_node = tree[child];

            if (child_node.bn_count_ == 1) {
                set_to_one = false;
                Edges* cur_edge = edge_matrix[vertex][child];
                for (ui k = 0; k < candidates_count[vertex]; ++k) {
                    ui cur_candidates_count = cur_edge->offset_[k + 1] - cur_edge->offset_[k];
                    //ui* cur_candidates = cur_edge->edge_ + cur_edge->offset_[k];
                    int off = cur_edge->offset_[k];

                    ui weight = 0;

                    for (ui l = 0; l < cur_candidates_count; ++l) {
                        ui candidates = cur_edge->edge_[off + l];
                        weight += weight_array[child][candidates];
                    }

                    if (weight < weight_array[vertex][k])
                        weight_array[vertex][k] = weight;
                }
            }
        }

        if (set_to_one) {
            std::fill(weight_array[vertex], weight_array[vertex] + candidates_count[vertex], 1);
        }
    }
}

void DAF::generateDSPisoQueryPlan_comm(const MemoryGraph *query_graph, ui *&order, ui *&pivot,
                                                TreeNode *tree, ui *bfs_order, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;

    // Compute weight array.
    //for (int i = 1; i <= q->nodenum; ++i)
    //  std::fill(weight_array[i], weight_array[i] + candidates_count[i], std::numeric_limits<ui>::max());

    for (int i = query_vertices_num - 1; i >= 0; --i) {
        VertexID vertex = order[i];
        TreeNode& node = tree[vertex];
        bool set_to_one = true;

        for (ui j = 0; j < node.fn_count_; ++j) {
            VertexID child = node.fn_[j];
            TreeNode& child_node = tree[child];

            if (child_node.bn_count_ == 1) {
                set_to_one = false;
                Edges* cur_edge = edge_matrix[vertex][child];
                for (ui k = 0; k < candidates_count[vertex]; ++k) {
                    ui cur_candidates_count = cur_edge->offset_[k + 1] - cur_edge->offset_[k];
                    //ui* cur_candidates = cur_edge->edge_ + cur_edge->offset_[k];
                    int off = cur_edge->offset_[k];

                    ui weight = 0;

                    for (ui l = 0; l < cur_candidates_count; ++l) {
                        ui candidates = cur_edge->edge_[off + l];
                        weight += weight_array[child][candidates];
                    }

                    if (weight < weight_array[vertex][k])
                        weight_array[vertex][k] = weight;
                }
            }
        }

        if (set_to_one) {
            std::fill(weight_array[vertex], weight_array[vertex] + candidates_count[vertex], 1);
        }
    }
}

void DAF::pruneCandidates(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    //LabelID query_vertex_label = 0;//query_graph->getVertexLabel(query_vertex);
    //ui query_vertex_degree = query_graph->degrees[query_vertex];//getVertexDegree(query_vertex);

    ui count = 0;
    ui updated_flag_count = 0;
    for (ui i = 0; i < pivot_vertices_count; ++i) {
        VertexID pivot_vertex = pivot_vertices[i];

        for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
            VertexID v = candidates[pivot_vertex][j];

            if (v == INVALID_VERTEX_ID)
                continue;
            //ui v_nbrs_count;
            //const VertexID* v_nbrs = data_graph->getVertexNeighbors(v, v_nbrs_count);

            //for (ui k = 0; k < v_nbrs_count; ++k) {
            //auto& vec = (*data_graph->outvec);
            for (const auto& v_nbr : data_graph->outvecp[v]) {
                // VertexID v_nbr = v_nbrs[k];
                LabelID v_nbr_label = 0; //data_graph->getVertexLabel(v_nbr);
                //ui v_nbr_degree = data_graph->degrees[v_nbr]; //data_graph->getVertexDegree(v_nbr);

                if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                    flag[v_nbr] += 1;

                    if (count == 0) {
                        updated_flag[updated_flag_count++] = v_nbr;
                    }
                }
            }
        }

        count += 1;
    }
    //return;
    int off = 0;
    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        ui v = candidates[query_vertex][i];
        if (v == INVALID_VERTEX_ID)
            continue;

        if (flag[v] != count) {
            off++;
            //candidates[query_vertex][i] = INVALID_VERTEX_ID;
        }
        else if (off != 0)
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
    }
    candidates_count[query_vertex] -= off;
    
    for (ui i = 0; i < updated_flag_count; ++i) {
        ui v = updated_flag[i];
        flag[v] = 0;
    }
}

void DAF::pruneCandidatesUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    int off = 0;

    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        VertexID v = candidates[query_vertex][i];
			
        bool canfind = true;
        int checked = 0;
        for (ui j = 0; j < pivot_vertices_count; ++j) {
            VertexID pivot_vertex = pivot_vertices[j];          
             {
				if (false) {//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }

            if (checked != j + 1) {
                canfind = false;
                break;
            }
        }
        if (!canfind) {
            off++;
			candmap[query_vertex][v] = -1;
        }
        else {
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
			candmap[query_vertex][v] -= off;
        }
    }

    candidates_count[query_vertex] -= off;

	for (int i = 0; i < pivot_vertices_count; ++i) {
		pivot_pos[pivot_vertices[i]] = 0;
	}
}


void DAF::pruneCandidatesBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    for (ui i = 0; i < pivot_vertices_count; ++i) {
        VertexID pivot_vertex = pivot_vertices[i];

        if (paIETreeL[query_vertex][pivot_vertex]) {
            for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
                VertexID v = candidates[pivot_vertex][j];

                if (v == INVALID_VERTEX_ID)
                    continue;

                //int pos = upper_bound(data_graph->outvecp[v].begin(), data_graph->outvecp[v].end(), v) - data_graph->outvecp[v].begin();
                int pos = data_graph->largerbound[v];
				for (int k = pos; k < data_graph->outvecp[v].size(); ++k) {
                    VertexID v_nbr = data_graph->outvecp[v][k];
                    if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                        flag[v_nbr] += 1;

                        if (count == 0) {
                            updated_flag[updated_flag_count++] = v_nbr;
                        }
                    }
                }
            }

            count += 1;
        }
        else if (paIETreeL[pivot_vertex][query_vertex]) {
            for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
                VertexID v = candidates[pivot_vertex][j];
                
				if (v == INVALID_VERTEX_ID || data_graph->largerbound[v] == 0)
                    continue;

                for (const auto& v_nbr : data_graph->outvecp[v]) {
                    if (v_nbr >= v)
                        break;
                    if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                        flag[v_nbr] += 1;

                        if (count == 0) {
                            updated_flag[updated_flag_count++] = v_nbr;
                        }
                    }
                }
            }

            count += 1;
        }
        else {
            for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
                VertexID v = candidates[pivot_vertex][j];

                if (v == INVALID_VERTEX_ID)
                    continue;

                for (const auto& v_nbr : data_graph->outvecp[v]) {            
                    if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                        flag[v_nbr] += 1;

                        if (count == 0) {
                            updated_flag[updated_flag_count++] = v_nbr;
                        }
                    }
                }
            }

            count += 1;
        }
    }
    //return;
    int off = 0;
    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        ui v = candidates[query_vertex][i];
        if (v == INVALID_VERTEX_ID)
            continue;

        if (flag[v] != count) {
            off++;
            //candidates[query_vertex][i] = INVALID_VERTEX_ID;
        }
        else if (off != 0)
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
    }
    candidates_count[query_vertex] -= off;
    
    for (ui i = 0; i < updated_flag_count; ++i) {
        ui v = updated_flag[i];
        flag[v] = 0;
    }
}



void DAF::pruneCandidatesBoundUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    int off = 0;

	bool over = false;
    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        VertexID v = candidates[query_vertex][i];

        bool canfind = true;
        int checked = 0;
        for (ui j = 0; j < pivot_vertices_count; ++j) {
            VertexID pivot_vertex = pivot_vertices[j];
            
            if (paIETreeL[pivot_vertex][query_vertex]) {
				if (false){//candidates_count[pivot_vertex] - pivot_pos[pivot_vertex] <= data_graph->outvecp[v].size() - data_graph->largerbound[v]) {
					pivot_pos[pivot_vertex] = upper_bound(candidates[pivot_vertex] + pivot_pos[pivot_vertex], candidates[pivot_vertex] + candidates_count[pivot_vertex], v) - candidates[pivot_vertex];
					if (pivot_pos[pivot_vertex] == candidates_count[pivot_vertex]) {
						over = true;
						break;
					}
					for (int q = pivot_pos[pivot_vertex]; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					vector<int>& temp = data_graph->outvecp[v];
					//int pos = upper_bound(temp.begin(), temp.end(), v) - temp.begin();
					int pos = data_graph->largerbound[v];
					for (int k = pos; k < temp.size(); ++k) {
						VertexID v_nbr = temp[k];
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }
            else if (paIETreeL[query_vertex][pivot_vertex]) {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						if (v_nbr >= v)
							break;
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (v_nbr >= v)
							break;
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }
            else {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }

            if (checked != j + 1) {
                canfind = false;
                break;
            }
        }
		if (over) {
			for (ui j = i; j < candidates_count[query_vertex]; ++j) {
				v = candidates[query_vertex][j];
				candmap[query_vertex][v] = -1;
			}
			candidates_count[query_vertex] = i - off;

			for (int i = 0; i < pivot_vertices_count; ++i) {
				pivot_pos[pivot_vertices[i]] = 0;
			}
			return;
		}
        if (!canfind) {
            off++;
			candmap[query_vertex][v] = -1;
        }
        else {
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
			candmap[query_vertex][v] -= off;
        }
    }

    candidates_count[query_vertex] -= off;

	for (int i = 0; i < pivot_vertices_count; ++i) {
		pivot_pos[pivot_vertices[i]] = 0;
	}
}


void DAF::pruneCandidatesBoundImp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    int off = 0;
	int degree = query_graph->degrees[query_vertex];
	candidates_count[query_vertex] = 0;

	bool over = false;
	if (nodeArea[query_vertex] != NULL) {
		for (ui i = 0; i < nodeArea_count[query_vertex]; ++i) {
			VertexID v = nodeArea[query_vertex][i];
			if (g->degrees[v] < degree)
				continue;                    
			
			bool canfind = true;
			int checked = 0;
			for (ui j = 0; j < pivot_vertices_count; ++j) {
				VertexID pivot_vertex = pivot_vertices[j];
            
				if (paIETreeL[pivot_vertex][query_vertex]) {
					if (false){//candidates_count[pivot_vertex] - pivot_pos[pivot_vertex] <= data_graph->outvecp[v].size() - data_graph->largerbound[v]) {
						pivot_pos[pivot_vertex] = upper_bound(candidates[pivot_vertex] + pivot_pos[pivot_vertex], candidates[pivot_vertex] + candidates_count[pivot_vertex], v) - candidates[pivot_vertex];
						if (pivot_pos[pivot_vertex] == candidates_count[pivot_vertex]) {
							over = true;
							break;
						}
						for (int q = pivot_pos[pivot_vertex]; q < candidates_count[pivot_vertex]; ++q) {
							VertexID v_nbr = candidates[pivot_vertex][q];
							//if (data_graph->edgemap[v][v_nbr]) {
							//	checked++;
							//	break;
							//}
						}
					}
					else {
						vector<int>& temp = data_graph->outvecp[v];
						//int pos = upper_bound(temp.begin(), temp.end(), v) - temp.begin();
						int pos = data_graph->largerbound[v];
						for (int k = pos; k < temp.size(); ++k) {
							VertexID v_nbr = temp[k];
							if (candmap[pivot_vertex][v_nbr] != -1) {
								checked++;
								break;
							}
						}
					}
				}
				else if (paIETreeL[query_vertex][pivot_vertex]) {
					if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
						for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
							VertexID v_nbr = candidates[pivot_vertex][q];
							if (v_nbr >= v)
								break;
							//if (data_graph->edgemap[v][v_nbr]) {
							//	checked++;
							//	break;
							//}
						}
					}
					else {
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (v_nbr >= v)
								break;
							if (candmap[pivot_vertex][v_nbr] != -1) {
								checked++;
								break;
							}
						}
					}
				}
				else {
					if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
						for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
							VertexID v_nbr = candidates[pivot_vertex][q];
							//if (data_graph->edgemap[v][v_nbr]) {
							//	checked++;
							//	break;
							//}
						}
					}
					else {
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (candmap[pivot_vertex][v_nbr] != -1) {
								checked++;
								break;
							}
						}
					}
				}

				if (checked != j + 1) {
					canfind = false;
					break;
				}
			}
			if (over) {					
				for (int i = 0; i < pivot_vertices_count; ++i) {
					pivot_pos[pivot_vertices[i]] = 0;
				}
				return;
			}
			if (!canfind) {
				off++;
			}
			else {
				candmap[query_vertex][v] = candidates_count[query_vertex];
                candidates[query_vertex][candidates_count[query_vertex]++] = v;						
			}
		}

		for (int i = 0; i < pivot_vertices_count; ++i) {
			pivot_pos[pivot_vertices[i]] = 0;
		}
	}
	else {
		auto c = &data->communityNodes[distributeplan[query_vertex]];
		for (ui i = 0; i < c->size(); ++i) {
			VertexID v = (*c)[i];
			if (g->degrees[v] < degree)
				continue;                    
			
			bool canfind = true;
			int checked = 0;
			for (ui j = 0; j < pivot_vertices_count; ++j) {
				VertexID pivot_vertex = pivot_vertices[j];
            
				if (paIETreeL[pivot_vertex][query_vertex]) {
					if (false){//candidates_count[pivot_vertex] - pivot_pos[pivot_vertex] <= data_graph->outvecp[v].size()) {
						pivot_pos[pivot_vertex] = upper_bound(candidates[pivot_vertex] + pivot_pos[pivot_vertex], candidates[pivot_vertex] + candidates_count[pivot_vertex], v) - candidates[pivot_vertex];
						if (pivot_pos[pivot_vertex] == candidates_count[pivot_vertex]) {
							over = true;
							break;
						}
						for (int q = pivot_pos[pivot_vertex]; q < candidates_count[pivot_vertex]; ++q) {
							VertexID v_nbr = candidates[pivot_vertex][q];
							//if (data_graph->edgemap[v][v_nbr]) {
							//	checked++;
							//	break;
							//}
						}
					}
					else {
						vector<int>& temp = data_graph->outvecp[v];
						//int pos = upper_bound(temp.begin(), temp.end(), v) - temp.begin();
						int pos = data_graph->largerbound[v];
						for (int k = pos; k < temp.size(); ++k) {
							VertexID v_nbr = temp[k];
							if (candmap[pivot_vertex][v_nbr] != -1) {
								checked++;
								break;
							}
						}
					}
				}
				else if (paIETreeL[query_vertex][pivot_vertex]) {
					if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
						for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
							VertexID v_nbr = candidates[pivot_vertex][q];
							if (v_nbr >= v)
								break;
							//if (data_graph->edgemap[v][v_nbr]) {
							//	checked++;
							//	break;
							//}
						}
					}
					else {
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (v_nbr >= v)
								break;
							if (candmap[pivot_vertex][v_nbr] != -1) {
								checked++;
								break;
							}
						}
					}
				}
				else {
					if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
						for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
							VertexID v_nbr = candidates[pivot_vertex][q];
							//if (data_graph->edgemap[v][v_nbr]) {
							//	checked++;
							//	break;
							//}
						}
					}
					else {
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (candmap[pivot_vertex][v_nbr] != -1) {
								checked++;
								break;
							}
						}
					}
				}

				if (checked != j + 1) {
					canfind = false;
					break;
				}
			}
			if (over) {					
				for (int i = 0; i < pivot_vertices_count; ++i) {
					pivot_pos[pivot_vertices[i]] = 0;
				}
				return;
			}
			if (!canfind) {
				off++;
			}
			else {
				candmap[query_vertex][v] = candidates_count[query_vertex];
                candidates[query_vertex][candidates_count[query_vertex]++] = v;							
			}
		}

		for (int i = 0; i < pivot_vertices_count; ++i) {
			pivot_pos[pivot_vertices[i]] = 0;
		}
	}
}

void DAF::pruneCandidatesDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    for (ui i = 0; i < pivot_vertices_count; ++i) {
        VertexID pivot_vertex = pivot_vertices[i];

        if (aIETreeL[query_vertex][pivot_vertex]) {
            for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
                VertexID v = candidates[pivot_vertex][j];

                if (v == INVALID_VERTEX_ID)
                    continue;

                //int pos = upper_bound(data_graph->outvecp[v].begin(), data_graph->outvecp[v].end(), v) - data_graph->outvecp[v].begin();
				int pos = data_graph->largerbound[v];
                for (int k = pos; k < data_graph->outvecp[v].size(); ++k) {
                    VertexID v_nbr = data_graph->outvecp[v][k];
                    if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                        flag[v_nbr] += 1;

                        if (count == 0) {
                            updated_flag[updated_flag_count++] = v_nbr;
                        }
                    }
                }
            }

            count += 1;
        }
        else if (aIETreeL[pivot_vertex][query_vertex]) {
            for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
                VertexID v = candidates[pivot_vertex][j];
                
				if (v == INVALID_VERTEX_ID || data_graph->largerbound[v] == 0)
                    continue;

                for (const auto& v_nbr : data_graph->outvecp[v]) {
                    if (v_nbr >= v)
                        break;
                    if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                        flag[v_nbr] += 1;

                        if (count == 0) {
                            updated_flag[updated_flag_count++] = v_nbr;
                        }
                    }
                }
            }

            count += 1;
        }
        else {
            for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
                VertexID v = candidates[pivot_vertex][j];

                if (v == INVALID_VERTEX_ID)
                    continue;

                for (const auto& v_nbr : data_graph->outvecp[v]) {            
                    if (flag[v_nbr] == count) { // && v_nbr_label == query_vertex_label && v_nbr_degree >= query_vertex_degree) {
                        flag[v_nbr] += 1;

                        if (count == 0) {
                            updated_flag[updated_flag_count++] = v_nbr;
                        }
                    }
                }
            }

            count += 1;
        }
    }
    //return;
	
    int off = 0;
    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        ui v = candidates[query_vertex][i];
        if (v == INVALID_VERTEX_ID)
            continue;

        if (flag[v] != count) {
            off++;
            //candidates[query_vertex][i] = INVALID_VERTEX_ID;
        }
        else if (off != 0)
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
    }
    candidates_count[query_vertex] -= off;
    
    for (ui i = 0; i < updated_flag_count; ++i) {
        ui v = updated_flag[i];
        flag[v] = 0;
    }
}

void DAF::pruneCandidatesDenseUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    int off = 0;

	bool over = false;
    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        VertexID v = candidates[query_vertex][i];
			
        bool canfind = true;
        int checked = 0;
        for (ui j = 0; j < pivot_vertices_count; ++j) {
            VertexID pivot_vertex = pivot_vertices[j];
            
            if (aIETreeL[pivot_vertex][query_vertex]) {
				if (false){//candidates_count[pivot_vertex] - pivot_pos[pivot_vertex] <= data_graph->outvecp[v].size() - data_graph->largerbound[v]) {
					pivot_pos[pivot_vertex] = upper_bound(candidates[pivot_vertex] + pivot_pos[pivot_vertex], candidates[pivot_vertex] + candidates_count[pivot_vertex], v) - candidates[pivot_vertex];
					if (pivot_pos[pivot_vertex] == candidates_count[pivot_vertex]) {
						over = true;
						break;
					}
					for (int q = pivot_pos[pivot_vertex]; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					vector<int>& temp = data_graph->outvecp[v];
					//int pos = upper_bound(temp.begin(), temp.end(), v) - temp.begin();
					int pos = data_graph->largerbound[v];
					for (int k = pos; k < temp.size(); ++k) {
						VertexID v_nbr = temp[k];
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }
            else if (aIETreeL[query_vertex][pivot_vertex]) {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						if (v_nbr >= v)
							break;
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (v_nbr >= v)
							break;
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }
            else {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }

            if (checked != j + 1) {
                canfind = false;
                break;
            }
        }
		if (over) {
			for (ui j = i; j < candidates_count[query_vertex]; ++j) {
				v = candidates[query_vertex][j];
				candmap[query_vertex][v] = -1;
			}
			candidates_count[query_vertex] = i - off;

			for (int i = 0; i < pivot_vertices_count; ++i) {
				pivot_pos[pivot_vertices[i]] = 0;
			}
			return;
		}
        if (!canfind) {
            off++;
			candmap[query_vertex][v] = -1;
        }
        else {
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
			candmap[query_vertex][v] -= off;
        }
    }

    candidates_count[query_vertex] -= off;

	for (int i = 0; i < pivot_vertices_count; ++i) {
		pivot_pos[pivot_vertices[i]] = 0;
	}
}

bool DAF::DPisoFilter(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree) {
    if (!LDFFilter(data_graph, query_graph, candidates, candidates_count))
        return false;

    generateDPisoFilterPlan(data_graph, query_graph, tree, order);

    ui query_vertices_num = query_graph->nodeNum;
    ui* updated_flag = new ui[data_graph->nodeNum + 1];
    ui* flag = new ui[data_graph->nodeNum + 1];
    std::fill(flag, flag + data_graph->nodeNum + 1, 0);

    // The number of refinement is k. According to the original paper, we set k as 3.
    for (ui k = 0; k < 3; ++k) {
        if (k % 2 == 0) {
            for (int i = 1; i < query_vertices_num; ++i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesUp(data_graph, query_graph, query_vertex, node.bn_, node.bn_count_, candidates, candidates_count, flag, updated_flag);
            }
        }
        else {
            for (int i = query_vertices_num - 2; i >= 0; --i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesUp(data_graph, query_graph, query_vertex, node.fn_, node.fn_count_, candidates, candidates_count, flag, updated_flag);
            }
        }
    }

    //compactCandidates(candidates, candidates_count, query_graph->nodenum);

    delete[] updated_flag;
    delete[] flag;
    return isCandidateSetValid(candidates, candidates_count, query_graph->nodeNum);
}

void DAF::compactCandidates(ui **&candidates, ui *&candidates_count, ui query_vertex_num) {
    for (ui i = 1; i <= query_vertex_num; ++i) {
        VertexID query_vertex = i;
        ui next_position = 0;
        //vector<VertexID> cands(candidates[query_vertex], candidates[query_vertex] + candidates_count[query_vertex]);
        //sort(cands.begin(), cands.end());
        for (ui j = 0; j < candidates_count[query_vertex]; ++j) {
            VertexID data_vertex = candidates[query_vertex][j];

            if (data_vertex != INVALID_VERTEX_ID) {
                candidates[query_vertex][next_position++] = data_vertex;
            }
        }

        candidates_count[query_vertex] = next_position;
    }
}

bool DAF::compactCandidatesBound(ui **&candidates, ui *&candidates_count, ui query_vertex_num) {
    for (ui i = 1; i <= query_vertex_num; ++i) {
        VertexID query_vertex = i;
        ui next_position = 0;
        //vector<VertexID> cands(candidates[query_vertex], candidates[query_vertex] + candidates_count[query_vertex]);
        //sort(cands.begin(), cands.end());
        for (ui j = 0; j < candidates_count[query_vertex]; ++j) {
            VertexID data_vertex = candidates[query_vertex][j];

            if (data_vertex != INVALID_VERTEX_ID) {
                candidates[query_vertex][next_position++] = data_vertex;
            }
        }

        candidates_count[query_vertex] = next_position;
        if (next_position == 0)
            return false;
    }
    return true;
}

bool DAF::isCandidateSetValid(ui **&candidates, ui *&candidates_count, ui query_vertex_num) {
    for (ui i = 1; i <= query_vertex_num; ++i) {
        if (candidates_count[i] == 0)
            return false;
    }
    return true;
}

void DAF::sortCandidates(ui **candidates, ui *candidates_count, ui num) {
    for (ui i = 0; i < num; ++i) {
        std::sort(candidates[i], candidates[i] + candidates_count[i]);
    }
}

size_t DAF::startMatch() {
    DPisoFilter(g, q, candidates, candidates_count, dpiso_order, dpiso_tree);

    buildTablesUp(g, q, candidates, candidates_count);

    //if (dpiso_tree == NULL) {
    //    generateDPisoFilterPlan(g, q, dpiso_tree, dpiso_order);
    //}

    generateDSPisoQueryPlan(q, matching_order, pivots, dpiso_tree, dpiso_order,
                                                    candidates_count);

    size_t ansnum = exploreDPisoStyle(g, q, dpiso_tree, candidates, candidates_count, dpiso_order);

	for (int i = 1; i <= q->nodeNum; ++i) {
        for (int j = 0; j < candidates_count[i]; ++j) {
            candmap[i][candidates[i][j]] = -1;
        }
    }

    return ansnum;
}

void DAF::buildTables(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    ui* flag = new ui[data_graph->nodeNum + 1];
    ui* updated_flag = new ui[data_graph->nodeNum + 1];
    std::fill(flag, flag + data_graph->nodeNum + 1, 0);

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    vector<int> buildorder(q->nodeNum + 1, -1);
    for (int i = 0; i < build_table_order.size(); ++i) {
        buildorder[build_table_order[i]] = i;
    }

    //std::vector<ui> temp_edges(data_graph->edgenum * 2);

    for (auto u : build_table_order) {
        ui u_nbrs_count;
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        ui updated_flag_count = 0;

        //for (ui i = 0; i < u_nbrs_count; ++i) {
        for (const auto& u_nbr : query_graph->outvecp[u]) {
            //VertexID u_nbr = u_nbrs[i];

            //if (edge_matrix[u][u_nbr] != NULL)
            //    continue;
            if (buildorder[u] > buildorder[u_nbr])
                continue;

            if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }

            edge_matrix[u_nbr][u] = new Edges;
            //edge_matrix[u_nbr][u]->vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u]->offset_.resize(candidates_count[u_nbr] + 1);

            edge_matrix[u][u_nbr] = new Edges;
            //edge_matrix[u][u_nbr]->vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr]->offset_.resize(candidates_count[u] + 1);
            fill(edge_matrix[u][u_nbr]->offset_.begin(), edge_matrix[u][u_nbr]->offset_.end(), 0);

            ui local_edge_count = 0;
            ui local_max_degree = 0;

            edge_matrix[u_nbr][u]->edge_.clear();

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u]->offset_[j] = local_edge_count;

                ui v_nbrs_count;
                //const VertexID* v_nbrs = data_graph->getVertexNeighbors(v, v_nbrs_count);

                ui local_degree = 0;

                int spos = local_edge_count;
                //for (ui k = 0; k < v_nbrs_count; ++k) {
                //    VertexID v_nbr = v_nbrs[k];
                for (const auto& v_nbr : data_graph->outvecp[v]) {
                    if (flag[v_nbr] != 0) {
                        ui position = flag[v_nbr] - 1;
                        //temp_edges[local_edge_count++] = position;
                        edge_matrix[u_nbr][u]->edge_.push_back(position);
                        local_edge_count++;
                        edge_matrix[u][u_nbr]->offset_[position + 1] += 1;
                        //local_degree += 1;
                    }
                }
                int epos = local_edge_count;
                sort(edge_matrix[u_nbr][u]->edge_.begin() + spos, edge_matrix[u_nbr][u]->edge_.begin() + epos);

                //if (local_degree > local_max_degree) {
                //    local_max_degree = local_degree;
                //}
            }

            edge_matrix[u_nbr][u]->offset_[candidates_count[u_nbr]] = local_edge_count;
            //edge_matrix[u_nbr][u].max_degree_ = local_max_degree;
            //edge_matrix[u_nbr][u]->edge_count_ = local_edge_count;
            //edge_matrix[u_nbr][u].edge_ = vector<ui>(local_edge_count);
            //std::copy(temp_edges.begin(), temp_edges.begin() + local_edge_count, edge_matrix[u_nbr][u].edge_.begin());

            //edge_matrix[u][u_nbr]->edge_count_ = local_edge_count;
            edge_matrix[u][u_nbr]->edge_.resize(local_edge_count);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                //if (edge_matrix[u][u_nbr].offset_[j] > local_max_degree) {
                //    local_max_degree = edge_matrix[u][u_nbr].offset_[j];
                //}
                edge_matrix[u][u_nbr]->offset_[j] += edge_matrix[u][u_nbr]->offset_[j - 1];
            }

            //edge_matrix[u][u_nbr].max_degree_ = local_max_degree;

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u]->offset_[begin]; k < edge_matrix[u_nbr][u]->offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u]->edge_[k];

                    edge_matrix[u][u_nbr]->edge_[edge_matrix[u][u_nbr]->offset_[end]++] = begin;
                }
            }

            for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr]->offset_[j] = edge_matrix[u][u_nbr]->offset_[j - 1];
            }
            edge_matrix[u][u_nbr]->offset_[0] = 0;
        }

        for (ui i = 0; i < updated_flag_count; ++i) {
            VertexID v = updated_flag[i];
            flag[v] = 0;
        }
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}

void DAF::buildTablesUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    //for (auto ptr : rubbishbin) {
    //  delete ptr;
    //  ptr = NULL;
    //}
    //rubbishbin.clear();

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    vector<int> buildorder(q->nodeNum + 1, -1);
    for (int i = 0; i < build_table_order.size(); ++i) {
        buildorder[build_table_order[i]] = i;
    }
    //std::vector<ui> temp_edges(data_graph->edgenum * 2);

	bool swapped = false;
    for (auto u : build_table_order) {
        ui u_nbrs_count;
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        ui updated_flag_count = 0;

        //for (ui i = 0; i < u_nbrs_count; ++i) {
        for (auto u_nbr : query_graph->outvecp[u]) {
            if (buildorder[u] > buildorder[u_nbr])
                continue;

			if (candidates_count[u] < candidates_count[u_nbr]) {
                std:swap(u, u_nbr);
                swapped = true;
            }
            /*if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }*/

            edge_matrix[u_nbr][u] = new Edges;
            //edge_matrix[u_nbr][u] = save_edge_matrix[u_nbr][u];
            //edge_matrix[u_nbr][u]->vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u]->offset_.resize(candidates_count[u_nbr] + 2);
            //rubbishbin.insert(edge_matrix[u_nbr][u]);

            edge_matrix[u][u_nbr] = new Edges;
            //edge_matrix[u][u_nbr] = save_edge_matrix[u][u_nbr];
            //edge_matrix[u][u_nbr]->vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr]->offset_.resize(candidates_count[u] + 2);
            std::fill(edge_matrix[u][u_nbr]->offset_.begin(), edge_matrix[u][u_nbr]->offset_.end(), 0);
            //rubbishbin.insert(edge_matrix[u][u_nbr]);

            ui local_edge_count = 0;
            ui local_max_degree = 0;
            ui edge_size = 0;

            edge_matrix[u_nbr][u]->edge_.clear();

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u]->offset_[j] = edge_size;

                ui local_degree = 0;

                int spos = edge_size;
                {
					if (false){//candidates_count[u] <= data_graph->outvecp[v].size()) {
						for (ui q = 0; q < candidates_count[u]; ++q) {
							VertexID v_nbr = candidates[u][q];
							//if (data_graph->edgemap[v][v_nbr]) {
								//ui position = q;
							//	edge_matrix[u_nbr][u]->edge_.push_back(q);
								//local_edge_count++;
							//	edge_matrix[u][u_nbr]->offset_[q + 2] += 1;
							//}
						}
					}
					else {
						/*if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}*/
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (candmap[u][v_nbr] != -1) {
                                ui position = candmap[u][v_nbr];//flag[v_nbr] - 1;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
							}
						}
					}
                }
                //int epos = local_edge_count;
                edge_size = edge_matrix[u_nbr][u]->edge_.size();
                sort(edge_matrix[u_nbr][u]->edge_.begin() + spos, edge_matrix[u_nbr][u]->edge_.end());
            }

            edge_matrix[u_nbr][u]->offset_[candidates_count[u_nbr]] = edge_size;
            //edge_matrix[u_nbr][u]->edge_count_ = edge_size;

            //edge_matrix[u][u_nbr]->edge_count_ = edge_size;
            edge_matrix[u][u_nbr]->edge_.resize(edge_size);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                edge_matrix[u][u_nbr]->offset_[j + 1] += edge_matrix[u][u_nbr]->offset_[j];
            }

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u]->offset_[begin]; k < edge_matrix[u_nbr][u]->offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u]->edge_[k];

                    edge_matrix[u][u_nbr]->edge_[edge_matrix[u][u_nbr]->offset_[end + 1]++] = begin;
                }
            }

            /*for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr]->offset_[j] = edge_matrix[u][u_nbr]->offset_[j - 1];
            }
            edge_matrix[u][u_nbr]->offset_[0] = 0;*/

			if (swapped) {
                swap(u, u_nbr);
                swapped = false;
            }
        }

        /*for (ui i = 0; i < updated_flag_count; ++i) {
            VertexID v = updated_flag[i];
            flag[v] = 0;
        }*/
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}



void DAF::buildTablesSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    //for (auto ptr : rubbishbin) {
    //  delete ptr;
    //  ptr = NULL;
    //}
    //rubbishbin.clear();

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    vector<int> buildorder(q->nodeNum + 1, -1);
    for (int i = 0; i < build_table_order.size(); ++i) {
        buildorder[build_table_order[i]] = i;
    }
    //std::vector<ui> temp_edges(data_graph->edgenum * 2);

	ui updated_flag_count = 0;
	ui lastupdate = -1;
	bool swapped = false;
    for (auto u : build_table_order) {
        ui u_nbrs_count;
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        //for (ui i = 0; i < u_nbrs_count; ++i) {
        for (auto u_nbr : query_graph->outvecp[u]) {
            if (buildorder[u] > buildorder[u_nbr])
                continue;

			if (candidates_count[u] < candidates_count[u_nbr]) {
                std:swap(u, u_nbr);
                swapped = true;
            }
            /*if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }*/

            edge_matrix[u_nbr][u] = new Edges;
            //edge_matrix[u_nbr][u] = save_edge_matrix[u_nbr][u];
            //edge_matrix[u_nbr][u]->vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u]->offset_.resize(candidates_count[u_nbr] + 2);
            //rubbishbin.insert(edge_matrix[u_nbr][u]);

            edge_matrix[u][u_nbr] = new Edges;
            //edge_matrix[u][u_nbr] = save_edge_matrix[u][u_nbr];
            //edge_matrix[u][u_nbr]->vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr]->offset_.resize(candidates_count[u] + 2);
            std::fill(edge_matrix[u][u_nbr]->offset_.begin(), edge_matrix[u][u_nbr]->offset_.end(), 0);
            //rubbishbin.insert(edge_matrix[u][u_nbr]);

            ui local_edge_count = 0;
            ui local_max_degree = 0;
            ui edge_size = 0;

            edge_matrix[u_nbr][u]->edge_.clear();

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u]->offset_[j] = edge_size;

                ui local_degree = 0;

                int spos = edge_size;
                if (aIETreeL[u][u_nbr]) {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						vector<int>& temp = data_graph->outvecp[v];
						//int pos = lower_bound(temp.begin(), temp.end(), v) - temp.begin();
						int pos = data_graph->largerbound[v];
						for (int k = pos; k < temp.size(); ++k) {
							VertexID v_nbr = temp[k];
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                else if (aIETreeL[u_nbr][u]) {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (v_nbr > v)
								break;
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                else {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                //int epos = local_edge_count;
                edge_size = edge_matrix[u_nbr][u]->edge_.size();
                sort(edge_matrix[u_nbr][u]->edge_.begin() + spos, edge_matrix[u_nbr][u]->edge_.end());
            }

            edge_matrix[u_nbr][u]->offset_[candidates_count[u_nbr]] = edge_size;
            //edge_matrix[u_nbr][u]->edge_count_ = edge_size;

            //edge_matrix[u][u_nbr]->edge_count_ = edge_size;
            edge_matrix[u][u_nbr]->edge_.resize(edge_size);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                edge_matrix[u][u_nbr]->offset_[j + 1] += edge_matrix[u][u_nbr]->offset_[j];
            }

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u]->offset_[begin]; k < edge_matrix[u_nbr][u]->offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u]->edge_[k];

                    edge_matrix[u][u_nbr]->edge_[edge_matrix[u][u_nbr]->offset_[end + 1]++] = begin;
                }
            }

            /*for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr]->offset_[j] = edge_matrix[u][u_nbr]->offset_[j - 1];
            }
            edge_matrix[u][u_nbr]->offset_[0] = 0;*/

			if (swapped) {
                swap(u, u_nbr);
                swapped = false;
            }
        }
    }

	for (ui i = 0; i < updated_flag_count; ++i) {
        VertexID v = updated_flag[i];
        flag[v] = 0;
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}

void DAF::buildTables_comm(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    //std::vector<ui> temp_edges(data_graph->edgenum * 2);

    for (auto u : build_table_order) {
        ui u_nbrs_count;
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        ui updated_flag_count = 0;

        //for (ui i = 0; i < u_nbrs_count; ++i) {
        for (const auto& u_nbr : query_graph->outvecp[u]) {
            if (u > u_nbr)
                continue;

            if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }

            edge_matrix[u_nbr][u] = new Edges;
            //edge_matrix[u_nbr][u]->vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u]->offset_.resize(candidates_count[u_nbr] + 1);

            edge_matrix[u][u_nbr] = new Edges;
            //edge_matrix[u][u_nbr]->vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr]->offset_.resize(candidates_count[u] + 1);
            fill(edge_matrix[u][u_nbr]->offset_.begin(), edge_matrix[u][u_nbr]->offset_.end(), 0);

            ui local_edge_count = 0;
            ui local_max_degree = 0;

            edge_matrix[u_nbr][u]->edge_.clear();

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u]->offset_[j] = local_edge_count;

                ui local_degree = 0;

                int spos = local_edge_count;
                for (const auto& v_nbr : data_graph->outvecp[v]) {
                    if (flag[v_nbr] != 0) {
                        ui position = flag[v_nbr] - 1;
                        edge_matrix[u_nbr][u]->edge_.push_back(position);
                        local_edge_count++;
                        edge_matrix[u][u_nbr]->offset_[position + 1] += 1;
                    }
                }
                int epos = local_edge_count;
                sort(edge_matrix[u_nbr][u]->edge_.begin() + spos, edge_matrix[u_nbr][u]->edge_.begin() + epos);
            }

            edge_matrix[u_nbr][u]->offset_[candidates_count[u_nbr]] = local_edge_count;
            //edge_matrix[u_nbr][u]->edge_count_ = local_edge_count;

            //edge_matrix[u][u_nbr]->edge_count_ = local_edge_count;
            edge_matrix[u][u_nbr]->edge_.resize(local_edge_count);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                edge_matrix[u][u_nbr]->offset_[j] += edge_matrix[u][u_nbr]->offset_[j - 1];
            }

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u]->offset_[begin]; k < edge_matrix[u_nbr][u]->offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u]->edge_[k];

                    edge_matrix[u][u_nbr]->edge_[edge_matrix[u][u_nbr]->offset_[end]++] = begin;
                }
            }

            for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr]->offset_[j] = edge_matrix[u][u_nbr]->offset_[j - 1];
            }
            edge_matrix[u][u_nbr]->offset_[0] = 0;
        }

        for (ui i = 0; i < updated_flag_count; ++i) {
            VertexID v = updated_flag[i];
            flag[v] = 0;
        }
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}

void DAF::buildTablesDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    //for (auto ptr : rubbishbin) {
    //  delete ptr;
    //  ptr = NULL;
    //}
    //rubbishbin.clear();

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    vector<int> buildorder(q->nodeNum + 1, -1);
    for (int i = 0; i < build_table_order.size(); ++i) {
        buildorder[build_table_order[i]] = i;
    }
    //std::vector<ui> temp_edges(data_graph->edgenum * 2);

	bool swapped = false;
	ui lastupdate = -1;
	ui updated_flag_count = 0;
    for (auto u : build_table_order) {
        ui u_nbrs_count;
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        //for (ui i = 0; i < u_nbrs_count; ++i) {
        for (auto u_nbr : query_graph->outvecp[u]) {
            if (buildorder[u] > buildorder[u_nbr])
                continue;

			if (candidates_count[u] < candidates_count[u_nbr]) {
                std:swap(u, u_nbr);
                swapped = true;
            }
            /*if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }*/

            //edge_matrix[u_nbr][u] = new Edges;
            edge_matrix[u_nbr][u] = save_edge_matrix[u_nbr][u];
            //edge_matrix[u_nbr][u]->vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u]->offset_.resize(candidates_count[u_nbr] + 2);
            //rubbishbin.insert(edge_matrix[u_nbr][u]);

            //edge_matrix[u][u_nbr] = new Edges;
            edge_matrix[u][u_nbr] = save_edge_matrix[u][u_nbr];
            //edge_matrix[u][u_nbr]->vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr]->offset_.resize(candidates_count[u] + 2);
            std::fill(edge_matrix[u][u_nbr]->offset_.begin(), edge_matrix[u][u_nbr]->offset_.end(), 0);
            //rubbishbin.insert(edge_matrix[u][u_nbr]);

            ui local_edge_count = 0;
            ui local_max_degree = 0;
            ui edge_size = 0;

            edge_matrix[u_nbr][u]->edge_.clear();

			int pos = 0;
            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u]->offset_[j] = edge_size;

                ui local_degree = 0;

                int spos = edge_size;
                if (aIETreeL[u][u_nbr]) {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						vector<int>& temp = data_graph->outvecp[v];
						//int pos = upper_bound(temp.begin(), temp.end(), v) - temp.begin();
						int pos = data_graph->largerbound[v];
						for (int k = pos; k < temp.size(); ++k) {
							VertexID v_nbr = temp[k];
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                else if (aIETreeL[u_nbr][u]) {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (v_nbr >= v)
								break;
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                else {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                //int epos = local_edge_count;
                edge_size = edge_matrix[u_nbr][u]->edge_.size();
                sort(edge_matrix[u_nbr][u]->edge_.begin() + spos, edge_matrix[u_nbr][u]->edge_.end());
            }

            edge_matrix[u_nbr][u]->offset_[candidates_count[u_nbr]] = edge_size;
            //edge_matrix[u_nbr][u]->edge_count_ = edge_size;

            //edge_matrix[u][u_nbr]->edge_count_ = edge_size;
            edge_matrix[u][u_nbr]->edge_.resize(edge_size);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                edge_matrix[u][u_nbr]->offset_[j + 1] += edge_matrix[u][u_nbr]->offset_[j];
            }

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u]->offset_[begin]; k < edge_matrix[u_nbr][u]->offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u]->edge_[k];

                    edge_matrix[u][u_nbr]->edge_[edge_matrix[u][u_nbr]->offset_[end + 1]++] = begin;
                }
            }

            /*for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr]->offset_[j] = edge_matrix[u][u_nbr]->offset_[j - 1];
            }
            edge_matrix[u][u_nbr]->offset_[0] = 0;*/

			if (swapped) {
                swap(u, u_nbr);
                swapped = false;
            }
        }

        
    }
	
	for (ui i = 0; i < updated_flag_count; ++i) {
        VertexID v = updated_flag[i];
        flag[v] = 0;
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}

void DAF::buildTablesBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodeNum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    //for (auto ptr : rubbishbin) {
    //  delete ptr;
    //  ptr = NULL;
    //}
    //rubbishbin.clear();

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    vector<int> buildorder(q->nodeNum + 1, -1);
    for (int i = 0; i < build_table_order.size(); ++i) {
        buildorder[build_table_order[i]] = i;
    }

    //std::vector<ui> temp_edges(data_graph->edgenum * 2);
    //cout << esetno[1] << " " << esetno[2] << " " << esetno[3] << endl;
    //for (int i = 0; i < candidates_count[1]; ++i) {
    //  cout << candidates[1][i] << " ";
    //}
    //cout << endl;
    //for (int i = 0; i < candidates_count[2]; ++i) {
    //  cout << candidates[2][i] << " ";
    //}
    //cout << endl;
    
    ui updated_flag_count = 0;
    for (auto u : build_table_order) {
        ui u_nbrs_count = query_graph->outvecp[u].size();
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        bool swapped = false;
        int lastupdate = -1;
        for (ui m = 0; m < u_nbrs_count; ++m) {
            ui u_nbr = query_graph->outvecp[u][m];
        //for (auto u_nbr : query_graph->outvecp[u]) {
            if (buildorder[u] < buildorder[u_nbr])
                continue;
            //if (u > u_nbr)
            //  continue;

            /*bool find = false;
            for (int p = 0; p < buildorder[u]; ++p) {
                int indexer = build_table_order[p];
                if (esetno[indexer] == esetno[u] && q->edgemap[u_nbr][indexer] == 1
                    && paIETreeL[u][u_nbr] == paIETreeL[indexer][u_nbr] && paIETreeL[u_nbr][u] == paIETreeL[u_nbr][indexer]) {
                    edge_matrix[u][u_nbr] = edge_matrix[indexer][u_nbr];
                    edge_matrix[u_nbr][u] = edge_matrix[u_nbr][indexer];
                    find = true;
                    break;
                }
            }
            if (find)
                continue;

            for (const auto& u_nbr_pre : query_graph->outvecp[u]) {
                if (u_nbr_pre == u_nbr)
                    break;
                if (esetno[u_nbr_pre] == esetno[u_nbr] && paIETreeL[u][u_nbr] == paIETreeL[u][u_nbr_pre]
                && paIETreeL[u_nbr][u] == paIETreeL[u_nbr_pre][u]) {
                    edge_matrix[u][u_nbr] = edge_matrix[u][u_nbr_pre];
                    edge_matrix[u_nbr][u] = edge_matrix[u_nbr_pre][u];
                    find = true;
                    break;
                }
            }
            if (find)
                continue;*/

            if (candidates_count[u] < candidates_count[u_nbr]) {
                std:swap(u, u_nbr);
                swapped = true;
            }

            /*if (u != lastupdate) {
                for (ui i = 0; i < updated_flag_count; ++i) {
                    VertexID v = updated_flag[i];
                    flag[v] = 0;
                }

                updated_flag_count = 0;
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
                lastupdate = u;
            }*/

            /*if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }*/

            //edge_matrix[u_nbr][u] = new Edges;
            edge_matrix[u_nbr][u] = save_edge_matrix[u_nbr][u];
            //edge_matrix[u_nbr][u]->vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u]->offset_.resize(candidates_count[u_nbr] + 2);
            //rubbishbin.insert(edge_matrix[u_nbr][u]);

            //edge_matrix[u][u_nbr] = new Edges;
            edge_matrix[u][u_nbr] = save_edge_matrix[u][u_nbr];
            //edge_matrix[u][u_nbr]->vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr]->offset_.resize(candidates_count[u] + 2);
            std::fill(edge_matrix[u][u_nbr]->offset_.begin(), edge_matrix[u][u_nbr]->offset_.end(), 0);
            //rubbishbin.insert(edge_matrix[u][u_nbr]);

            ui local_edge_count = 0;
            ui local_max_degree = 0;

            edge_matrix[u_nbr][u]->edge_.clear();
            ui edge_size = 0;

			int pos = 0;
            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u]->offset_[j] = edge_size;

                ui local_degree = 0;

                int spos = edge_size;
                if (paIETreeL[u][u_nbr]) {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						vector<int>& temp = data_graph->outvecp[v];
						//int pos = upper_bound(temp.begin(), temp.end(), v) - temp.begin();
						int pos = data_graph->largerbound[v];
						for (int k = pos; k < temp.size(); ++k) {
							VertexID v_nbr = temp[k];
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                else if (paIETreeL[u_nbr][u]) {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (v_nbr >= v)
								break;
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }
                else {
					{
						if (u != lastupdate) {
							for (ui i = 0; i < updated_flag_count; ++i) {
								VertexID v = updated_flag[i];
								flag[v] = 0;
							}

							updated_flag_count = 0;
							for (ui j = 0; j < candidates_count[u]; ++j) {
								VertexID v = candidates[u][j];
								flag[v] = j + 1;
								updated_flag[updated_flag_count++] = v;
							}
							lastupdate = u;
						}
						for (const auto& v_nbr : data_graph->outvecp[v]) {
							if (flag[v_nbr] != 0) {
								ui position = flag[v_nbr] - 1;
								//temp_edges[local_edge_count++] = position;
								edge_matrix[u_nbr][u]->edge_.push_back(position);
								//local_edge_count++;
								edge_matrix[u][u_nbr]->offset_[position + 2] += 1;
								//local_degree += 1;
							}
						}
					}
                }           
                //int epos = local_edge_count;
                edge_size = edge_matrix[u_nbr][u]->edge_.size();
                sort(edge_matrix[u_nbr][u]->edge_.begin() + spos, edge_matrix[u_nbr][u]->edge_.end());
            }

            edge_matrix[u_nbr][u]->offset_[candidates_count[u_nbr]] = edge_size;
            //edge_matrix[u_nbr][u]->edge_count_ = edge_size;

            //edge_matrix[u][u_nbr]->edge_count_ = edge_size;
            edge_matrix[u][u_nbr]->edge_.resize(edge_size);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                edge_matrix[u][u_nbr]->offset_[j + 1] += edge_matrix[u][u_nbr]->offset_[j];
            }

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u]->offset_[begin]; k < edge_matrix[u_nbr][u]->offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u]->edge_[k];

                    edge_matrix[u][u_nbr]->edge_[edge_matrix[u][u_nbr]->offset_[end + 1]++] = begin;
                }
            }

            /*for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr]->offset_[j] = edge_matrix[u][u_nbr]->offset_[j - 1];
            }
            edge_matrix[u][u_nbr]->offset_[0] = 0;*/

            if (swapped) {
                swap(u, u_nbr);
                swapped = false;
            }
        }  
    }

    for (ui i = 0; i < updated_flag_count; ++i) {
        VertexID v = updated_flag[i];
        flag[v] = 0;
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}

size_t DAF::exploreDPisoStyle(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order) {
    int max_depth = query_graph->nodeNum;
    ui *extendable = new ui[max_depth + 1];
    for (ui i = 1; i <= max_depth; ++i) {
        extendable[i] = tree[i].bn_count_;
    }

    // Generate backward neighbors.
    ui **bn;
    ui *bn_count;
    generateBN(query_graph, order, bn, bn_count);

    // Allocate the memory buffer.
    ui *idx;
    ui *idx_count;
    ui *embedding;
    ui *idx_embedding;
    ui *temp_buffer;
    ui **valid_candidate_idx;
    bool *visited_vertices;
    eva_allocateBuffer(data_graph, query_graph, candidates_count, idx, idx_count, embedding, idx_embedding,
                   temp_buffer, valid_candidate_idx, visited_vertices);

    // Evaluate the query.
    size_t embedding_cnt = 0;
    int cur_depth = 0;

#ifdef ENABLE_FAILING_SET
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> ancestors;
    computeAncestor(query_graph, tree, order);
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> vec_failing_set(max_depth);
    std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>* vec_failing_set = new std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>[max_depth];
    reverse_embedding = new VertexID[data->nodeNum + 1];
    memset(reverse_embedding, 0, (data->nodeNum + 1) * sizeof(VertexID));
    //std::unordered_map<VertexID, VertexID> reverse_embedding;
    //reverse_embedding.reserve(MAXIMUM_QUERY_GRAPH_SIZE * 2);
#endif

    VertexID start_vertex = order[0];
    
    std::vector<dpiso_min_pq> vec_rank_queue;

    for (ui i = 0; i < candidates_count[start_vertex]; ++i) {
        VertexID v = candidates[start_vertex][i];
        embedding[start_vertex] = v;
        idx_embedding[start_vertex] = i;
        visited_vertices[v] = true;

#ifdef ENABLE_FAILING_SET
        reverse_embedding[v] = start_vertex;
#endif
        vec_rank_queue.emplace_back(dpiso_min_pq(extendable_vertex_compare));
        updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer, 
                               tree, start_vertex, extendable,
                               vec_rank_queue, query_graph);

        VertexID u = vec_rank_queue.back().top().first.first;
        vec_rank_queue.back().pop();

#ifdef ENABLE_FAILING_SET
        if (idx_count[u] == 0) {
            vec_failing_set[cur_depth] = ancestors[u];
        } else {
            vec_failing_set[cur_depth].reset();
        }
#endif

        cur_depth += 1;
        order[cur_depth] = u;
        idx[u] = 0;
        while (cur_depth > 0) {
            while (idx[u] < idx_count[u]) {
                ui valid_idx = valid_candidate_idx[u][idx[u]];
                v = candidates[u][valid_idx];

                if (visited_vertices[v]) {
                    idx[u] += 1;
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    continue;
                }
                embedding[u] = v;
                idx_embedding[u] = valid_idx;
                visited_vertices[v] = true;
                idx[u] += 1;

#ifdef ENABLE_FAILING_SET
                reverse_embedding[v] = u;
#endif

                if (cur_depth == max_depth - 1) {
                    gm->ansnum++;
                    //embedding_cnt += 1;
                    visited_vertices[v] = false;
#ifdef ENABLE_FAILING_SET
                    reverse_embedding[embedding[u]] = 0;
                    vec_failing_set[cur_depth].set();
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];

#endif
                    //if (embedding_cnt >= output_limit_num) {
                    //    goto EXIT;
                    //}
                } else {
                    cur_depth += 1;
                    int vecsize = vec_rank_queue.size();
                    vec_rank_queue.push_back(vec_rank_queue[vecsize - 1]);
                    //vec_rank_queue.emplace_back(vec_rank_queue.back());

                    updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                                           tree, u, extendable,
                                           vec_rank_queue, query_graph);

                    if (!vec_rank_queue.back().empty()) {
                        u = vec_rank_queue.back().top().first.first;
                        vec_rank_queue.back().pop();
                        idx[u] = 0;
                        order[cur_depth] = u;
                    }
                    else
                        cout << "Error!" << endl;

#ifdef ENABLE_FAILING_SET
                    if (idx_count[u] == 0) {
                        vec_failing_set[cur_depth - 1] = ancestors[u];
                    } else {
                        vec_failing_set[cur_depth - 1].reset();
                    }
#endif
                }
            }

            cur_depth -= 1;
            vec_rank_queue.pop_back();
            u = order[cur_depth];
            visited_vertices[embedding[u]] = false;
            restoreExtendableVertex(tree, u, extendable);
#ifdef ENABLE_FAILING_SET
            reverse_embedding[embedding[u]] = 0;
            if (cur_depth != 0) {
                if (!vec_failing_set[cur_depth].test(u)) {
                    vec_failing_set[cur_depth - 1] = vec_failing_set[cur_depth];
                    idx[u] = idx_count[u];
                } else {
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
                }
            }
#endif
        }
    }

    // Release the buffer.
    EXIT:
    eva_releaseBuffer(max_depth, idx, idx_count, embedding, idx_embedding, temp_buffer, valid_candidate_idx,
                  visited_vertices,
                  bn, bn_count);

    return embedding_cnt;
}

void DAF::generateBN(const MemoryGraph *query_graph, ui *order, ui **&bn, ui *&bn_count) {
    ui query_vertices_num = query_graph->nodeNum;
    bn_count = new ui[query_vertices_num];
    std::fill(bn_count, bn_count + query_vertices_num, 0);
    bn = new ui *[query_vertices_num + 1];
    for (ui i = 0; i <= query_vertices_num; ++i) {
        bn[i] = new ui[query_vertices_num];
    }

    std::vector<bool> visited_vertices(query_vertices_num + 1, false);
    visited_vertices[order[0]] = true;
    for (ui i = 1; i < query_vertices_num; ++i) {
        VertexID vertex = order[i];

        ui nbrs_cnt;
        //const ui *nbrs = query_graph->getVertexNeighbors(vertex, nbrs_cnt);
        //for (ui j = 0; j < nbrs_cnt; ++j) {
        //    VertexID nbr = nbrs[j];
        for (const auto& nbr : query_graph->outvecp[vertex]) {
            if (visited_vertices[nbr]) {
                bn[i][bn_count[i]++] = nbr;
            }
        }

        visited_vertices[vertex] = true;
    }
}

void DAF::generateBNBound(const MemoryGraph *query_graph, ui *order, ui **&bn, ui *&bn_count) {
    ui query_vertices_num = query_graph->nodeNum;
    std::fill(bn_count, bn_count + query_vertices_num, 0);

    std::vector<bool> visited_vertices(query_vertices_num + 1, false);
    visited_vertices[order[0]] = true;
    for (ui i = 1; i < query_vertices_num; ++i) {
        VertexID vertex = order[i];

        ui nbrs_cnt;
        //const ui *nbrs = query_graph->getVertexNeighbors(vertex, nbrs_cnt);
        //for (ui j = 0; j < nbrs_cnt; ++j) {
        //    VertexID nbr = nbrs[j];
        for (const auto& nbr : query_graph->outvecp[vertex]) {
            if (visited_vertices[nbr]) {
                bn[i][bn_count[i]++] = nbr;
            }
        }

        visited_vertices[vertex] = true;
    }
}

void DAF::updateExtendableVertex(ui *idx_embedding, ui *idx_count, ui **valid_candidate_index,
                                           ui *&temp_buffer,
                                           TreeNode *tree, VertexID mapped_vertex, ui *extendable,
                                           std::vector<dpiso_min_pq> &vec_rank_queue, const MemoryGraph *query_graph) {
    TreeNode &node = tree[mapped_vertex];
    for (ui i = 0; i < node.fn_count_; ++i) {
        VertexID u = node.fn_[i];
        extendable[u] -= 1;
        if (extendable[u] == 0) {
            generateValidCandidateIndex(u, idx_embedding, idx_count, valid_candidate_index[u], tree[u].bn_,
                                        tree[u].bn_count_, temp_buffer);

            ui weight = 0;
            for (ui j = 0; j < idx_count[u]; ++j) {
                ui idx = valid_candidate_index[u][j];
                weight += weight_array[u][idx];
            }
            vec_rank_queue.back().emplace(std::make_pair(std::make_pair(u, query_graph->degrees[u]), weight));
        }
    }
}

void DAF::restoreExtendableVertex(TreeNode *tree, VertexID unmapped_vertex, ui *extendable) {
    TreeNode &node = tree[unmapped_vertex];
    for (ui i = 0; i < node.fn_count_; ++i) {
        VertexID u = node.fn_[i];
        extendable[u] += 1;
    }
}

void DAF::generateValidCandidateIndex(VertexID u, ui *idx_embedding, ui *idx_count, ui *&valid_candidate_index,
                                           ui *bn, ui bn_cnt, ui *&temp_buffer) {
    VertexID previous_bn = bn[0];
    Edges* previous_edge = edge_matrix[previous_bn][u];
    ui previous_index_id = idx_embedding[previous_bn];

    ui previous_candidates_count =
            previous_edge->offset_[previous_index_id + 1] - previous_edge->offset_[previous_index_id];
    //ui *previous_candidates = previous_edge->edge_ + previous_edge->offset_[previous_index_id];
    int preoff = previous_edge->offset_[previous_index_id];
    int endoff = previous_edge->offset_[previous_index_id] + previous_candidates_count;

    //vector<int> valid(previous_edge->edge_.begin() + off, previous_edge->edge_.begin() + off + previous_candidates_count);
    ui valid_candidates_count = 0;
    //for (ui i = 0; i < previous_candidates_count; ++i) {
    //    valid_candidate_index[valid_candidates_count++] = previous_edge->edge_[off + i];
    //} 

    ui temp_count;
    if (bn_cnt <= 1) {
        int endcc = previous_candidates_count + preoff;
        for (ui i = preoff; i < endcc; ++i) {
            valid_candidate_index[valid_candidates_count++] = previous_edge->edge_[i];
        }   
    }
    else {
        for (ui i = 1; i < bn_cnt; ++i) {
            VertexID current_bn = bn[i];
            Edges* current_edge = edge_matrix[current_bn][u];
            ui current_index_id = idx_embedding[current_bn];

            //ui current_candidates_count =
            //      current_edge->offset_[current_index_id + 1] - current_edge->offset_[current_index_id];
            //ui *current_candidates = current_edge->edge_ + current_edge->offset_[current_index_id];
            int off = current_edge->offset_[current_index_id];

            //vector<int> C(current_edge->edge_.begin() + off, current_edge->edge_.begin() + off + current_candidates_count);
            //vector<int> valid(valid_candidate_index, valid_candidate_index + valid_candidates_count);
            //sort(C.begin(), C.end());
            //sort(valid.begin(), valid.end());
            //vector<int>::iterator it = set_intersection(C.begin(), C.end(), valid.begin(), valid.end(), valid.begin());
            //valid.resize(it - valid.begin());

            int startc = current_edge->offset_[current_index_id];
            int endc = current_edge->offset_[current_index_id + 1];
            int j = 0;
            int k = startc;
            int voff = 0;

            if (i == 1) {
                j = preoff;
                while (j < endoff && k < endc) {
                    if (previous_edge->edge_[j] < current_edge->edge_[k]) {
                        j++;
                    }
                    else if(previous_edge->edge_[j] > current_edge->edge_[k]) {
                        k++;
                    }
                    else {
                        valid_candidate_index[valid_candidates_count++] = previous_edge->edge_[j];
                        j++;
                        k++;
                    }
                }
                continue;
            }

            while (j < valid_candidates_count && k < endc) {
                if (valid_candidate_index[j] < current_edge->edge_[k]) {
                    j++;
                }
                else if(valid_candidate_index[j] > current_edge->edge_[k]) {
                    k++;
                }
                else {
                    valid_candidate_index[voff++] = valid_candidate_index[j];
                    j++;
                    k++;
                }
            }
            valid_candidates_count = voff;
            //ComputeSetIntersection::ComputeCandidates(current_candidates, current_candidates_count, valid_candidate_index,
            //                                          valid_candidates_count,
            //                                          temp_buffer, temp_count);



            //std::swap(temp_buffer, valid_candidate_index);
            //for (int ci = 0; ci < C.size(); ++ci)
            //  *(valid_candidate_index + ci) = C[ci];
            //valid_candidates_count = C.size();
            //valid_candidates_count = temp_count;
        }
    }
    //std::copy(valid.begin(), valid.end(), valid_candidate_index);
    //for (int ci = 0; ci < valid.size(); ++ci)
    //  *(valid_candidate_index + ci) = valid[ci];
    //valid_candidates_count = valid.size();

    idx_count[u] = valid_candidates_count;
}


// comm daf
size_t DAF::startMatch_comm() {
    DPisoFilterSuper(g, q, candidates, candidates_count, dpiso_order, dpiso_tree);
	
    buildTablesSuper(g, q, candidates, candidates_count);
    
    //if (dpiso_tree == NULL) {
    //    generateDPisoFilterPlan(g, q, dpiso_tree, dpiso_order);
    //}

    generateDSPisoQueryPlan(q, matching_order, pivots, dpiso_tree, dpiso_order, candidates_count);

    size_t ansnum = exploreDPisoStyleSuper(g, q, dpiso_tree, candidates, candidates_count, dpiso_order);

    return ansnum;
}

bool DAF::DPisoFilterSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree) {
    if (!LDFFilterSuper(data_graph, query_graph, candidates, candidates_count))
        return false;
	
    generateDPisoFilterPlanSuper(data_graph, query_graph, tree, order);

    ui query_vertices_num = query_graph->nodeNum;
    ui* updated_flag = new ui[data_graph->nodeNum + 1];
    ui* flag = new ui[data_graph->nodeNum + 1];
    std::fill(flag, flag + data_graph->nodeNum + 1, 0);

    // The number of refinement is k. According to the original paper, we set k as 3.
    for (ui k = 0; k < 3; ++k) {
        if (k % 2 == 0) {
            for (int i = 1; i < query_vertices_num; ++i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesSuper(data_graph, query_graph, query_vertex, node.bn_, node.bn_count_, candidates, candidates_count, flag, updated_flag);
            }
        }
        else {
            for (int i = query_vertices_num - 2; i >= 0; --i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesSuper(data_graph, query_graph, query_vertex, node.fn_, node.fn_count_, candidates, candidates_count, flag, updated_flag);
            }
        }
    }

    //compactCandidates(candidates, candidates_count, query_graph->nodenum);

    delete[] updated_flag;
    delete[] flag;
    return isCandidateSetValid(candidates, candidates_count, query_graph->nodeNum);
}

bool DAF::LDFFilterSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count) {
    allocateBuffer(data_graph, query_graph, candidates, candidates_count);

    for (ui i = 1; i <= q->nodeNum; ++i) {
        LabelID label = 0;
        ui degree = q->degrees[i];

        //ui data_vertex_num;
        //const ui* data_vertices = g->getVerticesByLabel(label, data_vertex_num);

        //for (ui j = 0; j < data_vertex_num; ++j) {
        //    ui data_vertex = data_vertices[j];
        //    if (g->getVertexDegree(data_vertex) >= degree) {
        //        candidates[i][candidates_count[i]++] = data_vertex;
        //    }
        //}
        for (ui j = 0; j < g->nodeNum; ++j) {
            ui data_vertex = g->nodes[j];
            if (g->degrees[data_vertex] == 0 && degree != 0) {
                
            }
            else {
				//candmap[i][data_vertex] = candidates_count[i];
                candidates[i][candidates_count[i]++] = data_vertex;
			}
        }

        if (candidates_count[i] == 0) {
            return false;
        }
    }

    return true;
}

void DAF::generateDPisoFilterPlanSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *&tree,
                                                    VertexID *&order) {
    VertexID start_vertex = selectDPisoStartVertexSuper(g, q);
    bfsTraversal(q, start_vertex, dpiso_tree, dpiso_order);

    ui query_vertices_num = q->nodeNum;
    std::vector<ui> order_index(query_vertices_num + 1);
    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID query_vertex = dpiso_order[i];
        order_index[query_vertex] = i;
    }

    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID u = dpiso_order[i];
        dpiso_tree[u].under_level_count_ = 0;
        dpiso_tree[u].bn_count_ = 0;
        dpiso_tree[u].fn_count_ = 0;

        ui u_nbrs_count;
        //const VertexID* u_nbrs = q->getVertexNeighbors(u, u_nbrs_count);
        //for (ui j = 0; j < u_nbrs_count; ++j) {
        for (const auto& u_nbr : q->outvecp[u]) {
            //VertexID u_nbr = u_nbrs[j];
            if (order_index[u_nbr] < order_index[u]) {
                dpiso_tree[u].bn_[dpiso_tree[u].bn_count_++] = u_nbr;
            }
            else {
                dpiso_tree[u].fn_[dpiso_tree[u].fn_count_++] = u_nbr;
            }
        }
    }
}

VertexID DAF::selectDPisoStartVertexSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph) {
    double min_score = data_graph->nodeNum;
    VertexID start_vertex = 1;

    for (ui i = 1; i <= query_graph->nodeNum; ++i) {
        ui degree = query_graph->degrees[i];//(*query_graph->outedges)[i].size();
        if (degree <= 1)
            continue;

        ui count = 0;
        computeCandidateWithLDFSuper(data_graph, query_graph, i, count);
        double cur_score = count / (double)degree;
        if (cur_score < min_score) {
            min_score = cur_score;
            start_vertex = i;
        }
    }

    return start_vertex;
}

void DAF::computeCandidateWithLDFSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                             ui &count, ui *buffer) {
    LabelID label = 0;
    ui degree = query_graph->degrees[query_vertex];//(*query_graph->outedges)[query_vertex].size();
    count = 0;
    //ui data_vertex_num;
    //const ui* data_vertices = data_graph->getVerticesByLabel(label, data_vertex_num);

    if (buffer == NULL) {
        for (ui i = 0; i < data_graph->nodeNum; ++i) {
            VertexID v = data_graph->nodes[i];
            if (data_graph->degrees[v] == 0 && degree != 0) {
                
            }
            else
                count++;
        }
    }
    else {
        for (ui i = 0; i < data_graph->nodeNum; ++i) {
            VertexID v = data_graph->nodes[i];
            if (data_graph->degrees[v] >= degree) {
                buffer[count++] = v;
            }
        }
    }
}

void DAF::pruneCandidatesSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    LabelID query_vertex_label = 0;//query_graph->getVertexLabel(query_vertex);
    ui query_vertex_degree = query_graph->degrees[query_vertex];//getVertexDegree(query_vertex);

    ui count = 0;
    ui updated_flag_count = 0;
    for (ui i = 0; i < pivot_vertices_count; ++i) {
        VertexID pivot_vertex = pivot_vertices[i];

        for (ui j = 0; j < candidates_count[pivot_vertex]; ++j) {
            VertexID v = candidates[pivot_vertex][j];

            if (v == INVALID_VERTEX_ID)
                continue;
            ui v_nbrs_count;
            //const VertexID* v_nbrs = data_graph->getVertexNeighbors(v, v_nbrs_count);

            //for (ui k = 0; k < v_nbrs_count; ++k) {
            for (const auto& v_nbr : data_graph->outvecp[v]) {
                // VertexID v_nbr = v_nbrs[k];
                LabelID v_nbr_label = 0; //data_graph->getVertexLabel(v_nbr);
                ui v_nbr_degree = data_graph->degrees[v_nbr]; //data_graph->getVertexDegree(v_nbr);

                if (flag[v_nbr] == count && v_nbr_label == query_vertex_label && !(v_nbr_degree == 0 && query_vertex_degree != 0)) {
                    flag[v_nbr] += 1;

                    if (count == 0) {
                        updated_flag[updated_flag_count++] = v_nbr;
                    }
                }
            }
        }

        count += 1;
    }

    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        ui v = candidates[query_vertex][i];
        if (v == INVALID_VERTEX_ID)
            continue;
		
        if (flag[v] != count) {
            candidates[query_vertex][i] = INVALID_VERTEX_ID;
        }
    }

    for (ui i = 0; i < updated_flag_count; ++i) {
        ui v = updated_flag[i];
        flag[v] = 0;
    }
}

void DAF::pruneCandidatesSuperUp(const MemoryGraph *data_graph, const MemoryGraph *query_graph, VertexID query_vertex,
                                    VertexID *pivot_vertices, ui pivot_vertices_count, VertexID **candidates,
                                    ui *candidates_count, ui *flag, ui *updated_flag) {
    ui count = 0;
    ui updated_flag_count = 0;
    int off = 0;

	bool over =false;
    for (ui i = 0; i < candidates_count[query_vertex]; ++i) {
        VertexID v = candidates[query_vertex][i];
			
        bool canfind = true;
        int checked = 0;
        for (ui j = 0; j < pivot_vertices_count; ++j) {
            VertexID pivot_vertex = pivot_vertices[j];
            
            if (aIETreeL[pivot_vertex][query_vertex]) {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					pivot_pos[pivot_vertex] = lower_bound(candidates[pivot_vertex] + pivot_pos[pivot_vertex], candidates[pivot_vertex] + candidates_count[pivot_vertex], v) - candidates[pivot_vertex];
					if (pivot_pos[pivot_vertex] == candidates_count[pivot_vertex]) {
						over = true;
						break;
					}
					for (int q = pivot_pos[pivot_vertex]; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					vector<int>& temp = data_graph->outvecp[v];
					//int pos = lower_bound(temp.begin(), temp.end(), v) - temp.begin();
					int pos = data_graph->largerbound[v];
					for (int k = pos; k < temp.size(); ++k) {
						VertexID v_nbr = temp[k];
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }
            else if (aIETreeL[query_vertex][pivot_vertex]) {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						if (v_nbr > v)
							break;
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (v_nbr > v)
							break;
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }
            else {
				if (false){//candidates_count[pivot_vertex] <= data_graph->outvecp[v].size()) {
					for (int q = 0; q < candidates_count[pivot_vertex]; ++q) {
						VertexID v_nbr = candidates[pivot_vertex][q];
						//if (data_graph->edgemap[v][v_nbr]) {
						//	checked++;
						//	break;
						//}
					}
				}
				else {
					for (const auto& v_nbr : data_graph->outvecp[v]) {
						if (candmap[pivot_vertex][v_nbr] != -1) {
                            checked++;
							break;
						}
					}
				}
            }

            if (checked != j + 1) {
                canfind = false;
                break;
            }
        }
		if (over) {
			for (ui j = i; j < candidates_count[query_vertex]; ++j) {
				v = candidates[query_vertex][j];
				candmap[query_vertex][v] = -1;
			}
			candidates_count[query_vertex] = i - off;

			for (int i = 0; i < pivot_vertices_count; ++i) {
				pivot_pos[pivot_vertices[i]] = 0;
			}
			return;
		}
        if (!canfind) {
            off++;
			candmap[query_vertex][v] = -1;
        }
        else {
            candidates[query_vertex][i - off] = candidates[query_vertex][i];
			candmap[query_vertex][v] -= off;
        }
    }

    candidates_count[query_vertex] -= off;

	for (int i = 0; i < pivot_vertices_count; ++i) {
		pivot_pos[pivot_vertices[i]] = 0;
	}
}

size_t DAF::exploreDPisoStyleSuper(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order) {
    int max_depth = query_graph->nodeNum;
    ui *extendable = new ui[max_depth + 1];
    for (ui i = 1; i <= max_depth; ++i) {
        extendable[i] = tree[i].bn_count_;
    }

    // Generate backward neighbors.
    ui **bn;
    ui *bn_count;
    generateBN(query_graph, order, bn, bn_count);

    // Allocate the memory buffer.
    ui *idx;
    ui *idx_count;
    int *embedding;
    ui *idx_embedding;
    ui *temp_buffer;
    ui **valid_candidate_idx;
    bool *visited_vertices;
    eva_allocateBuffer(data_graph, query_graph, candidates_count, idx, idx_count, embedding, idx_embedding,
                   temp_buffer, valid_candidate_idx, visited_vertices);

    // Evaluate the query.
    size_t embedding_cnt = 0;
    int cur_depth = 0;

    //for (int i = 1; i <= q->nodenum; ++i)
    //  embedding[i] = -1;

#ifdef ENABLE_FAILING_SET
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> ancestors;
    computeAncestor(query_graph, tree, order);
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> vec_failing_set(max_depth);
    std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>* vec_failing_set = new std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>[max_depth];
    reverse_embedding = new VertexID[data->nodeNum + 1];
    memset(reverse_embedding, 0, (data->nodeNum + 1) * sizeof(VertexID));
    //std::unordered_map<VertexID, VertexID> reverse_embedding;
    //reverse_embedding.reserve(MAXIMUM_QUERY_GRAPH_SIZE * 2);
#endif

    VertexID start_vertex = order[0];
    
    std::vector<dpiso_min_pq> vec_rank_queue;
    vector<int> lastmatch(q->nodeNum + 1, -1);

    //for (int i = 1; i <= q->nodenum; ++i)
    //  lastmatch[i] = -1;

    for (ui i = 0; i < candidates_count[start_vertex]; ++i) {
        VertexID v = candidates[start_vertex][i];
        embedding[start_vertex] = v;
        idx_embedding[start_vertex] = i;
        //visited_vertices[v] = true;

#ifdef ENABLE_FAILING_SET
        reverse_embedding[v] = start_vertex;
#endif
        vec_rank_queue.emplace_back(dpiso_min_pq(extendable_vertex_compare));
        updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                               tree, start_vertex, extendable,
                               vec_rank_queue, query_graph);

        VertexID u = vec_rank_queue.back().top().first.first;
        vec_rank_queue.back().pop();

#ifdef ENABLE_FAILING_SET
        if (idx_count[u] == 0) {
            vec_failing_set[cur_depth] = ancestors[u];
        } else {
            vec_failing_set[cur_depth].reset();
        }
#endif

        cur_depth += 1;
        order[cur_depth] = u;
        idx[u] = 0;
        bool succeed = false;
        while (cur_depth > 0) {
            succeed = true;
            while (idx[u] < idx_count[u]) {
                ui valid_idx = valid_candidate_idx[u][idx[u]];
                v = candidates[u][valid_idx];

                if (visited_vertices[v]) {
                    //idx[u] += 1;
#ifdef ENABLE_FAILING_SET
                    //vec_failing_set[cur_depth] = ancestors[u];
                    //vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    //vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    //continue;
                }
                succeed = false;
                //embedding[u] = v;

                int curr_n1 = u;
                int prev_n2 = v;
                bool takeover = true;
                for (const auto& uv : IETreeS[curr_n1])
                {
                    if (embedding[uv] != -1 && embedding[uv] < prev_n2)
                    {
                        takeover = false;
                        break;
                    }
                }
                if (!takeover)
                {
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    idx[u] = idx_count[u];
                    continue;
                }

                //if (updated)
                //  break;

                int maxlevel = -1;
                for (const auto& uv : IETreeL[curr_n1])
                {
                    if (embedding[uv] != -1 && embedding[uv] > prev_n2)
                    {
                        takeover = false;
                        maxlevel = max(maxlevel, embedding[uv]);
                        //break;
                    }
                }
                if (!takeover)
                {   
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    succeed = false;
                    //updated = true;
                    //vector<int>* b = &(*g2->invec)[pred_pair];
                    //last_candidate_index = lower_bound(b->begin() + last_candidate_index, b->end(), maxlevel) - b->begin();
                    int last_cand = lower_bound(candidates[u], candidates[u] + candidates_count[u], maxlevel) - candidates[u];
                    int last_idx = lower_bound(valid_candidate_idx[u], valid_candidate_idx[u] + idx_count[u], last_cand) - valid_candidate_idx[u];
                    //idx[u]++;
                    idx[u] = last_idx;
                    continue;
                }

                for (const auto& neigh : q->outvecp[u])
                {
                    int commNeigh = embedding[neigh];
                    if (commNeigh != -1)
                    {
                        n2cNum[u][commNeigh]++;
                        n2cNum[neigh][prev_n2]++;
                        if (n2cNum[u][commNeigh] > data->commMaxNumTag[prev_n2][commNeigh]
                        || n2cNum[neigh][prev_n2] > data->commMaxNumTag[commNeigh][prev_n2])
                        {
                            for (const auto& n : q->outvecp[u])
                            {
                                int commN = embedding[n];
                                if (commN != -1)
                                {
                                    n2cNum[u][commN]--;
                                    n2cNum[n][prev_n2]--;
                                }

                                if (n == neigh)
                                    break;
                            }
                            takeover = false;
                            break;
                        }
                    }
                }
                if (!takeover)
                {
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    //n2cNum = recn2c;
                    idx[u]++;
                    continue;
                }

                embedding[u] = prev_n2;
                //vector<int> mys;
                unordered_set<int> myrecord;
                for (int i = 0; i < q->degrees[u]; ++i)
                {
                    int neigh = q->outvecp[u][i];
                    if (embedding[neigh] != -1)
                    {
                        int nval = embedding[neigh];

                        if (!gm->share1NeighbourPairs[prev_n2][nval])
                        {
                            takeover = false;
                            break;
                        }

                        bool added = true;
                        for (int j = 0; j < penv[neigh].size(); ++j)
                        {
                            int c2 = penv[neigh][j];
                            if (prev_n2 == c2)
                            {
                                added = false;
                                gm->addpos = j;
                            }
                            //else
                            {
                                if (!gm->share2NeighbourPairs[nval][prev_n2][c2])
                                {
                                    takeover = false;
                                    break;
                                }
                            }

                            for (int k = 0; k < penv[u].size(); ++k)
                            {
                                //if (penv[cur][k] == nval)
                                //  continue;
                                if (penv[u][k] != c2)
                                    continue;
                                bool catchv = false;
                                for (const auto& p1 : penv_en[u][k])
                                {
                                    for (const auto& p2 : penv_en[neigh][j])
                                    {
                                        if (p1 == p2)
                                        {
                                            catchv = true;
                                            break;
                                        }
                                    }
                                    if (catchv)
                                        break;
                                }
                                //if ((catchv && !data->triangleLimitation[penv[cur][k]][prev_n2][nval][c2]) 
                                //  || (!catchv && !data->len4Limitation[penv[cur][k]][prev_n2][nval][c2]))
                                if (catchv && !data->triangleLimitation[penv[u][k]][prev_n2][nval])
                                {
                                    takeover = false;
                                    break;
                                }
                            }
                            if (!takeover)
                                break;
                        }
                        if (!takeover)
                            break;

                        if (myrecord.find(nval) == myrecord.end())
                        {
                            penv[u].push_back(nval);
                            penv_en[u].push_back(vector<int>(1, neigh));
                            myrecord.insert(nval);
                        }
                        else
                        {
                            for (int index =  penv_en[u].size() - 1; index >= 0; --index)
                            {
                                if (penv[u][index] == nval)
                                {
                                    penv_en[u][index].push_back(neigh);
                                    break;
                                }
                            }
                        }
                        //mys.push_back(nval);

                        
                        if (!takeover)
                            break;

                        if (added)
                        {
                            toadd[u].push_back(neigh);
                        }
                        else
                        {
                            existaddpos[u].push_back(make_pair(neigh, gm->addpos));
                        }
                    }
                }
                if (!takeover)
                {
                    penv[u].clear();
                    penv_en[u].clear();
                    toadd[u].clear();
                    existaddpos[u].clear();
                    //n2cNum = recn2c;
                    for (const auto& n : q->outvecp[u])
                    {
                        int commN = embedding[n];
                        if (commN != -1)
                        {
                            n2cNum[u][commN]--;
                            n2cNum[n][prev_n2]--;
                        }
                    }
                    embedding[u] = -1;
                    idx[u]++;
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    continue;
                }

                succeed = true;
                for (const auto& neigh : toadd[u])
                {
                    penv[neigh].push_back(prev_n2);
                    penv_en[neigh].push_back(vector<int>(1, u));
                }
                for (const auto& neigh_pair : existaddpos[u])
                {
                    penv_en[neigh_pair.first][neigh_pair.second].push_back(u);
                }

                lastmatch[u] = v;

                idx_embedding[u] = valid_idx;
                visited_vertices[v] = true;
                idx[u] += 1;

#ifdef ENABLE_FAILING_SET
                reverse_embedding[v] = u;
#endif

                if (cur_depth == max_depth - 1) {
                    embedding_cnt += 1;
                    visited_vertices[v] = false;
#ifdef ENABLE_FAILING_SET
                    reverse_embedding[embedding[u]];
                    vec_failing_set[cur_depth].set();
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];

#endif
                    /*unordered_map<int, vector<int>> supermatch;
                    int i, j;
                    for (i = 1, j = 1; i <= q->nodenum; i++)
                    {
                        if (embedding[i] != -1)
                        {
                            //supermatch[core_1[i]].push_back(i);
                            gm->logger << i << " " << embedding[i] << endl;
                        }
                    }
                    gm->logger << endl;*/

                    //supert.clear();
                    //supermapper.clear();
                    superc2cMap.clear();
                    int index = 0;
                    fill(supertcount, supertcount + q->nodeNum, 0);

                    for (int i = 1; i <= q->nodeNum; ++i)
                    {
                        //if (m.second != -1)
                        if (embedding[i] != -1)
                        {
                            if (superc2cMap.find(embedding[i]) == superc2cMap.end())
                            {
                                int j = index;
                                supermapper[index] = embedding[i];
                                superc2cMap[embedding[i]] = index++;
                                //supermapper.push_back(embedding[i]);
                                supert[j][supertcount[j]++] = i;
                                //supert.push_back(vector<int>(1, i));
                                newM[i] = j;
                            }
                            else
                            {
                                int j = superc2cMap[embedding[i]];
                                supert[j][supertcount[j]++] = i;
                                //supert[j].push_back(i);
                                newM[i] = j;
                            }
                        }
                    }                    
                    commnum = index;
                    rematch_DAF(supert, supermapper, newM, embedding, *communityGraphs, *q);
                    
                    int prev_n2 = lastmatch[u];
                    for (const auto& neigh : q->outvecp[u])
                    {
                        int commNeigh = embedding[neigh];
                        if (commNeigh != -1)
                        {
                            n2cNum[u][commNeigh] = 0;
                            n2cNum[neigh][prev_n2]--;
                        }
                    }

                    for (const auto& neigh : toadd[u])
                    {
                        penv[neigh].pop_back();
                        penv_en[neigh].pop_back();
                    }
                    for (const auto& neigh_pair : existaddpos[u])
                    {
                        penv_en[neigh_pair.first][neigh_pair.second].pop_back();
                    }
                    toadd[u].clear();
                    existaddpos[u].clear();
                    penv[u].clear();
                    penv_en[u].clear();
                    //if (embedding_cnt >= output_limit_num) {
                    //    goto EXIT;
                    //}
                } else {
                    cur_depth += 1;
                    int vecsize = vec_rank_queue.size();
                    vec_rank_queue.push_back(vec_rank_queue[vecsize - 1]);
                    //vec_rank_queue.emplace_back(vec_rank_queue.back());

                    updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                                           tree, u, extendable,
                                           vec_rank_queue, query_graph);

                    u = vec_rank_queue.back().top().first.first;
                    vec_rank_queue.back().pop();
                    idx[u] = 0;
                    order[cur_depth] = u;

#ifdef ENABLE_FAILING_SET
                    if (idx_count[u] == 0) {
                        vec_failing_set[cur_depth - 1] = ancestors[u];
                    } else {
                        vec_failing_set[cur_depth - 1].reset();
                    }
#endif
                }
            }

            embedding[u] = -1;
            cur_depth -= 1;
            vec_rank_queue.pop_back();
            u = order[cur_depth];
            visited_vertices[embedding[u]] = false;
            restoreExtendableVertex(tree, u, extendable);   

            int prev_n2 = lastmatch[u];
            for (const auto& neigh : q->outvecp[u])
            {
                int commNeigh = embedding[neigh];
                if (commNeigh != -1)
                {
                    n2cNum[u][commNeigh] = 0;
                    n2cNum[neigh][prev_n2]--;
                }
            }

            for (const auto& neigh : toadd[u])
            {
                penv[neigh].pop_back();
                penv_en[neigh].pop_back();
            }
            for (const auto& neigh_pair : existaddpos[u])
            {
                penv_en[neigh_pair.first][neigh_pair.second].pop_back();
            }
            toadd[u].clear();
            existaddpos[u].clear();
            penv[u].clear();
            penv_en[u].clear();
#ifdef ENABLE_FAILING_SET
            reverse_embedding[embedding[u]] = 0;
            if (cur_depth != 0) {
                if (!vec_failing_set[cur_depth].test(u)) {
                    vec_failing_set[cur_depth - 1] = vec_failing_set[cur_depth];
                    idx[u] = idx_count[u];
                } else {
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
                }
            }
#endif
        }
    }

    embedding[start_vertex] = -1;
    // Release the buffer.
    EXIT:
    eva_releaseBuffer(max_depth, idx, idx_count, embedding, idx_embedding, temp_buffer, valid_candidate_idx,
                  visited_vertices,
                  bn, bn_count);

    return embedding_cnt;
}

void DAF::init() {
    equalq_ptr = new bool*[q->nodeNum + 1];
    for (int i = 1; i <= q->nodeNum; ++i) {
        equalq_ptr[i] = new bool[q->nodeNum + 1];
        fill(equalq_ptr[i], equalq_ptr[i] + q->nodeNum + 1, false);
        for (int j = 1; j <= q->nodeNum; ++j) {
            if ((*equalq)[i][j])
                equalq_ptr[i][j] = true;
        }
    }
    schemenum = gm->schemes.size();
    schemes = new int*[gm->schemes.size()];
    for (int i = 0; i < gm->schemes.size(); ++i) {
        schemes[i] = new int[gm->schemes[i].size()];
        for (int j = 0; j < gm->schemes[i].size(); ++j) {
            schemes[i][j] = gm->schemes[i][j];
        }
    }
    initIETree();
    flag_comm = new int[data->nodeNum + 1];
    memset(flag_comm, 0, (data->nodeNum + 1) * sizeof(int));
    updated_flag = new ui[data->nodeNum + 1];
	flag = new ui[data->communityNum + 1];
	memset(flag, 0, (data->communityNum + 1) * sizeof(int));
    gm->hittimes = 0;
    supermapper = new int[data->communityNum + 1];
    supertcount = new int[data->communityNum + 1];
    supert = new int*[data->communityNum + 1];
    for (int i = 0; i <= data->communityNum; ++i) {
        supert[i] = new int[q->nodeNum + 1];
    }
    //n2cNum = vector<vector<int>>(q->nodenum + 1, vector<int>(g->nodenum + 1, 0));
    n2cNum = new int* [q->nodeNum + 1];
    for (int i = 0; i < q->nodeNum + 1; ++i) {
        n2cNum[i] = new int[g->nodeNum + 1];
        memset(n2cNum[i], 0, (g->nodeNum + 1) * sizeof(int));
    }
    toadd = new vector<int>[q->nodeNum + 1];
    existaddpos = new vector<pair<int, int>>[q->nodeNum + 1];
    penv = new vector<int>[q->nodeNum + 1];
    penv_en = new vector<vector<int>>[q->nodeNum + 1];
    newM = new int[q->nodeNum + 1];
    boundary = new int*[q->nodeNum + 1];
    memset(boundary, NULL, (q->nodeNum + 1) * sizeof(int*));
    boundary_count = new int[q->nodeNum + 1];
    save_boundary = new int*[q->nodeNum + 1];
    for (int i = 0; i < q->nodeNum + 1; ++i) {
        save_boundary[i] = new int[data->maxCommSize + 1];
    }

	/*candmap = new int*[q->nodenum + 1];
    for (int i = 1; i <= q->nodenum; ++i) {
		candmap[i] = new int[data->communityNum + 1];
        fill(candmap[i], candmap[i] + data->communityNum + 1, -1);
    }
	pivot_pos = new int[q->nodenum + 1];
	fill(pivot_pos, pivot_pos + q->nodenum + 1, 0);*/

    recdaf = new DAF();
    recdaf->data = data;
    recdaf->gm = this->gm;
    recdaf->q = this->q;
    recdaf->schemes = schemes;
    recdaf->schemenum = schemenum;
    recdaf->initIETree();
    //recdaf->g = communityGraphs[cid];

    recdaf->edge_matrix = new Edges **[recdaf->q->nodeNum + 1];
    recdaf->save_edge_matrix = new Edges **[recdaf->q->nodeNum + 1];
    recdaf->weight_array = new ui *[recdaf->q->nodeNum + 1];
    for (ui i = 0; i < q->nodeNum + 1; ++i) {
        recdaf->edge_matrix[i] = new Edges* [recdaf->q->nodeNum + 1];
        recdaf->save_edge_matrix[i] = new Edges *[recdaf->q->nodeNum + 1];
        for (int j = 0; j < q->nodeNum + 1; ++j) {
            recdaf->save_edge_matrix[i][j] = new Edges;
            recdaf->edge_matrix[i][j] = NULL;
        }
        //fill(recdaf->edge_matrix[i], recdaf->edge_matrix[i] + recdaf->q->nodenum + 1, NULL);
        //memset(recdaf->edge_matrix[i], NULL, (recdaf->q->nodenum + 1) * sizeof(Edges*));
        //fill(recdaf->edge_matrix[i], recdaf->edge_matrix[i] + recdaf->q->nodenummem + 1, NULL);

        recdaf->weight_array[i] = new ui[data->maxCommSize + 1];
        //memset(recdaf->weight_array[i], std::numeric_limits<ui>::max(), (recdaf->g->nodenum + 1) * sizeof(ui));
    }

    //recdaf->generateDPisoFilterPlan(recdaf->g, recdaf->q, recdaf->dpiso_tree, recdaf->dpiso_order);
            //recdaf->edge_matrix = vector<vector<Edges*>>(q->nodenum + 1, vector<Edges*>(q->nodenum + 1, NULL));
            //recdaf->weight_array = vector<vector<ui>>(q->nodenum + 1, vector<ui>(g->nodenum + 1, std::numeric_limits<ui>::max()));

    recdaf->candidates_count = new ui[recdaf->q->nodeNum + 1];
    recdaf->candidates = new ui*[recdaf->q->nodeNum + 1];

    for (ui i = 0; i <= recdaf->q->nodeNum; ++i) {
        recdaf->candidates[i] = new ui[data->maxCommSize];
    }

    recdaf->updated_flag = new ui[data->maxCommSize + 1];
    recdaf->flag = new ui[data->maxCommSize + 1];
    memset(recdaf->flag, 0, (data->maxCommSize + 1) * sizeof(ui));

    recdaf->matching_order = new ui[recdaf->q->nodeNum];
    recdaf->pivots = new ui[recdaf->q->nodeNum];

    int max_depth = recdaf->q->nodeNum;
    recdaf->extendable = new ui[max_depth + 1];

    ui query_vertices_num = recdaf->q->nodeNum;
    ui data_vertices_num = data->maxCommSize;
    ui max_candidates_num = data->maxCommSize;

    recdaf->idx = new ui[query_vertices_num + 1];
    recdaf->idx_count = new ui[query_vertices_num + 1];
    recdaf->embedding = new ui[query_vertices_num + 1];
    fill(recdaf->embedding, recdaf->embedding + query_vertices_num + 1, -1);
    recdaf->idx_embedding = new ui[query_vertices_num + 1];
    recdaf->temp_buffer = new ui[max_candidates_num + 1];
    recdaf->valid_candidate_idx = new ui *[query_vertices_num + 1];
    for (ui i = 0; i <= query_vertices_num; ++i) {
        recdaf->valid_candidate_idx[i] = new ui[max_candidates_num];
    }
    recdaf->visited_vertices = new bool[data_vertices_num + 1];
    memset(recdaf->visited_vertices, false, (data_vertices_num + 1) * sizeof(bool));
    recdaf->reverse_embedding = new VertexID[data->nodeNum + 1];
    memset(recdaf->reverse_embedding, 0, (data->nodeNum + 1) * sizeof(VertexID));
    recdaf->vec_failing_set = new bitset<MAXIMUM_QUERY_GRAPH_SIZE>[q->nodeNum];
	recdaf->endmax = new bool[query_vertices_num + 1];
	fill(recdaf->endmax, recdaf->endmax + query_vertices_num + 1, false);

	/*recdaf->candmap = new int*[q->nodenum + 1];
    for (int i = 1; i <= q->nodenum; ++i) {
        recdaf->candmap[i] = new int[data->nodeNum + 1];
        fill(recdaf->candmap[i], recdaf->candmap[i] + data->nodeNum + 1, -1);
    }
	recdaf->pivot_pos = new int[q->nodenum + 1];
	fill(recdaf->pivot_pos, recdaf->pivot_pos + q->nodenum + 1, 0);*/

    bounddaf = new DAF();
    bounddaf->data = data;
    bounddaf->gm = this->gm;
    bounddaf->communityGraphs = this->communityGraphs;
    bounddaf->q = q;

    bounddaf->edge_matrix = new Edges **[bounddaf->q->nodeNum + 1];
    bounddaf->overall_edge_matrix = new Edges *[bounddaf->q->nodeNum + 1];
    bounddaf->save_edge_matrix = new Edges **[bounddaf->q->nodeNum + 1];
    bounddaf->weight_array = new ui *[q->nodeNum + 1];
    bounddaf->cand_idx_mapper = new ui* [q->nodeNum + 1];
    //bounddaf->cand_idx_mapper_rev = new ui* [q->nodenum + 1];
    for (ui i = 0; i < q->nodeNum + 1; ++i) {
        bounddaf->edge_matrix[i] = new Edges* [bounddaf->q->nodeNum + 1];
        bounddaf->overall_edge_matrix[i] = new Edges [bounddaf->q->nodeNum + 1];
        bounddaf->save_edge_matrix[i] = new Edges *[bounddaf->q->nodeNum + 1];
        //memset(bounddaf->edge_matrix[i], NULL, (bounddaf->q->nodenum + 1) * sizeof(Edges*));
        for (int j = 0; j <= q->nodeNum; ++j) {
            bounddaf->save_edge_matrix[i][j] = new Edges;
            bounddaf->edge_matrix[i][j] = NULL;
        }
        //fill(bounddaf->edge_matrix[i], bounddaf->edge_matrix[i] + bounddaf->q->nodenum + 1, NULL);

        bounddaf->weight_array[i] = new ui[data->nodeNum + 1];
        bounddaf->cand_idx_mapper[i] = new ui[data->nodeNum + 1];
        //bounddaf->cand_idx_mapper_rev[i] = new ui[data->nodeNum + 1];
        fill(bounddaf->weight_array[i], bounddaf->weight_array[i] + data->nodeNum + 1, 1);
    }

    bounddaf->candidates_count = new ui[bounddaf->q->nodeNum + 1];
    bounddaf->candidates = new ui*[bounddaf->q->nodeNum + 1];

    for (ui i = 0; i <= bounddaf->q->nodeNum; ++i) {
        bounddaf->candidates[i] = new ui[data->maxCommSize];
    }

    bounddaf->esetno = new int[bounddaf->q->nodeNum + 1];
    bounddaf->updated_flag = new ui[data->nodeNum + 1];
    bounddaf->flag = new ui[data->nodeNum + 1];
    memset(bounddaf->flag, 0, (data->nodeNum + 1) * sizeof(ui));

    bounddaf->matching_order = new ui[bounddaf->q->nodeNum];
    bounddaf->pivots = new ui[bounddaf->q->nodeNum];

    max_depth = bounddaf->q->nodeNum;
    bounddaf->extendable = new ui[max_depth + 1];

    query_vertices_num = bounddaf->q->nodeNum;
    max_candidates_num = data->maxCommSize;

    bounddaf->dpiso_tree = new TreeNode[bounddaf->q->nodeNum + 1];
    for (ui i = 1; i <= bounddaf->q->nodeNum; ++i) {
       bounddaf->dpiso_tree[i].initialize(bounddaf->q->nodeNum);
    }
    bounddaf->dpiso_order = new VertexID[bounddaf->q->nodeNum + 1];

    bounddaf->idx = new ui[query_vertices_num + 1];
    bounddaf->idx_count = new ui[query_vertices_num + 1];
    bounddaf->embedding = new ui[query_vertices_num + 1];
    fill(bounddaf->embedding, bounddaf->embedding + query_vertices_num + 1, -1);
    bounddaf->idx_embedding = new ui[query_vertices_num + 1];
    bounddaf->temp_buffer = new ui[max_candidates_num + 1];
    bounddaf->valid_candidate_idx = new ui *[query_vertices_num + 1];
    for (ui i = 0; i <= query_vertices_num; ++i) {
        bounddaf->valid_candidate_idx[i] = new ui[max_candidates_num];
    }
    bounddaf->visited_vertices = new bool[data->nodeNum + 1];
    memset(bounddaf->visited_vertices, false, (data->nodeNum + 1) * sizeof(bool));
    bounddaf->reverse_embedding = new VertexID[data->nodeNum + 1];
    memset(bounddaf->reverse_embedding, 0, (data->nodeNum + 1) * sizeof(VertexID));
    bounddaf->vec_failing_set = new bitset<MAXIMUM_QUERY_GRAPH_SIZE>[q->nodeNum];
	bounddaf->endmax = new bool[query_vertices_num + 1];
	fill(bounddaf->endmax, bounddaf->endmax + query_vertices_num + 1, false);

    bounddaf->pIETreeL = NULL;
    bounddaf->pIETreeS = NULL;

    bounddaf->bn_count = new ui[query_vertices_num];
    bounddaf->bn = new ui *[query_vertices_num + 1];
    for (ui i = 0; i <= query_vertices_num; ++i) {
        bounddaf->bn[i] = new ui[query_vertices_num];
    }
    bounddaf->ancestors = new std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>[query_vertices_num + 1];
    bounddaf->schemes = schemes;
    bounddaf->schemenum = schemenum;

	/*bounddaf->candmap = new int*[q->nodenum + 1];
    for (int i = 1; i <= q->nodenum; ++i) {
        bounddaf->candmap[i] = new int[data->nodeNum + 1];
        fill(bounddaf->candmap[i], bounddaf->candmap[i] + data->nodeNum + 1, -1);
    }

	bounddaf->pivot_pos = new int[q->nodenum + 1];
	fill(bounddaf->pivot_pos, bounddaf->pivot_pos + q->nodenum + 1, 0);*/

    boundfirst = true;
    recfirst = true;
}

void DAF::rematch_DAF(int** supermatch, int* c2cmapper, int* supermatchmap, int* supermatchmapori
        , vector<MemoryGraph*>& communityGraphs, MemoryGraph& patternGraph) {
    //int hittime turboisosuper= 0;
    //int totaltime = 0;
    //bool isCheck = false;
    //int supercount = 0;
    //cout << "supermatch: " << supermatch.size() << endl;

    /*map<int, vector<int>> m;
    m[1].push_back(1);
    m[12].push_back(2);
    m[12].push_back(3);
    m[12].push_back(4);
    //m[21].push_back(3);
    //supermatch = m;

    /*if (find(supermatch.begin(), supermatch.end(), m) != supermatch.end())
    {
    cout << "find it !!!!!" << endl;
    }
    else
    {
    cout << "not find" << endl;
    }*/

    //set<map<int, vector<int>>> supermatchrecord;
    //double testtime = 0;
    //int usedmatch = 0;
    //int usefulmatch = 0;

    //supercount++;
    //map<int, vector<int>> s;
    //cout << i++ << endl;
    //s.clear();
    //s[11].push_back(1);
    //s[9].push_back(2);
    //s[12].push_back(3);
    //s[11].push_back(4);
    //s[5].push_back(5);
    //supermatch = s;
    //for (auto& s : supermatch)
    //for (int i = 0; i < supermatch.size(); i++)
    //{
    //supermatch = m;
    bool cut1 = false;
    bool cut2 = true;//true;
    bool cut3 = true;//true;
    //cout << "info" << endl;
    bool isgo = true;

    /*for (int i = 0; i < supermatch.size(); ++i)
    {
    if (supermatch[i].size() > data->communityNodes[c2cmapper[i]].size())
    {
    isgo = false;
    break;
    }

    //sort(n.second.begin(), n.second.end());
    }*/

    //if (!isgo)
    //{
    //  return; //continue;
    //}

    if (commnum == 1)
    {
        //if (c2cmapper[0] != 13)
        //  return;
        //cout << supermatch.begin()->first << endl;
        int cid = c2cmapper[0];
        if (recfirst)
        {
            recdaf->g = communityGraphs[cid];

            recdaf->generateDPisoFilterPlan(recdaf->g, recdaf->q, recdaf->dpiso_tree, recdaf->dpiso_order);
            //recdaf->edge_matrix = vector<vector<Edges*>>(q->nodenum + 1, vector<Edges*>(q->nodenum + 1, NULL));
            //recdaf->weight_array = vector<vector<ui>>(q->nodenum + 1, vector<ui>(g->nodenum + 1, std::numeric_limits<ui>::max()));

            for (ui i = 0; i < recdaf->q->nodeNum; ++i) {
                recdaf->matching_order[i] = recdaf->dpiso_order[i];
            }

            for (ui i = 1; i < recdaf->q->nodeNum; ++i) {
                recdaf->pivots[i] = recdaf->dpiso_tree[recdaf->matching_order[i]].parent_;
            }

            int max_depth = recdaf->q->nodeNum;
            for (ui i = 1; i <= max_depth; ++i) {
                recdaf->extendable[i] = recdaf->dpiso_tree[i].bn_count_;
            }

            recdaf->generateBN(recdaf->q, recdaf->dpiso_order, recdaf->bn, recdaf->bn_count);

            ui query_vertices_num = recdaf->q->nodeNum;
            ui data_vertices_num = data->maxCommSize;
            ui max_candidates_num = data->maxCommSize;

#ifdef ENABLE_FAILING_SET  
            recdaf->computeAncestor(recdaf->q, recdaf->dpiso_tree, recdaf->dpiso_order);
            recfirst = false;
#endif
        }
        else {      
            recdaf->g = communityGraphs[cid];
            //for (ui i = 1; i <= q->nodenum; ++i) {
            //  /*for (ui j = 1; j <= q->nodenum; ++j) {
            //      if (recdaf->edge_matrix[i][j] != NULL) {
            //          delete recdaf->edge_matrix[i][j];
            //      }
            //      recdaf->edge_matrix[i][j] = NULL;
            //  }*/
            //  memset(recdaf->weight_array[i], std::numeric_limits<ui>::max(), (recdaf->g->nodenum + 1) * sizeof(ui));
            //}
        }
        //int cid = c2cmapper[0];
        //recdaf->g = communityGraphs[cid];
        //recdaf->weight_array = vector<vector<ui>>(q->nodenum + 1, vector<ui>(recdaf->g->nodenum + 1, std::numeric_limits<ui>::max()));
        //cout << cid << " " << rectm->g->nodenum << endl;
        bool candup = false;

        //rectm->vvans = &tans[0];
        //rectm->comm_id = cid;
        int count = recdaf->startMatchDense();
        //cout << "count: " << count << endl;
        //gm->internum++;
        //#pragma omp critical
        {
            gm->ansnum += count;
        }
        return;//continue;
    }
	
    //int id = omp_get_thread_num();
    //vector<map<int, int>> newallmaps;
    bool smallestPattern = false;

    //supermatch = s;

    bool canMatch = true;

    bool canfind = true;

    //if (supermatchmapori[1] == 2 && supermatchmapori[2] == 2 && supermatchmapori[3] == 2 && supermatchmapori[4] == 12)
    //  int ksp = 0;
	
    //pointers.clear();
    //gm->uselessUntrivial++;
    if (cut2)
    {
        memset(boundary + 1, NULL, sizeof(int*) * q->nodeNum);
        //for (int i = 1; i < patternGraph.nodenum + 1; ++i)
        //{
        //  boundary[i] = NULL;
        //}

        //for (int i = 0; i < q->nodenum + 1; ++i)
        //{
        //outcomm[i].clear();
        //  for (int j = 0; j < supermatch.size(); ++j)
        //  {
        //      outds[i][j].clear();
        //  }
        //}

        for (int comm = 0; comm < commnum; ++comm)
        {
            int actualcomm = c2cmapper[comm];
            for (int i = 0; i < supertcount[comm]; ++i)
            {
                int n = supermatch[comm][i];
                bool rep = false;
                for (int p = 0; p < i; p++)
                {
                    int vertex = supermatch[comm][p];
                    if (equalq_ptr[vertex][n])
                    {
                        rep = true;
                        if (boundary[vertex] != NULL)
                        {
                            boundary[n] = boundary[vertex];
                            boundary_count[n] = boundary_count[vertex];
                            //outds[n] = outds[vertex];
                        }
                        break;
                    }
                }
                if (rep)
                {
                    continue;
                }

                //int* narea = NULL;// = *((*communityGraphs[comm.first]).nodes);
                                          //sort(narea.begin(), narea.end());
                int nareacount = 0;

                int index = 0;
                int count = -1;
                int updated_flag_count = 0;
                for (int c = 0; c < commnum; ++c)
                {
                    if (c != comm)
                    {
                        int actualc = c2cmapper[c];                     

                        //if (hasout)
                        if (n2cNum[n][actualc] != 0)
                        {
                            //for (const auto& l : outds)
                            {
                                count++;

                                int label = this->q->nodeLabels[n];// l.first;
                                p.degree = n2cNum[n][actualc];//l.second;
                                p.pos = -1;

								if (label == 0) {
									bool getit = false;
									for (int tlabel = 0; tlabel < data->degreePosOut[actualcomm][actualc].size(); ++tlabel) {
										vector<DegreePos>* dpSaver = &data->degreePosOut[actualcomm][actualc][tlabel];
										if (dpSaver->empty())
										{
											continue;
										}

										vector<DegreePos>::iterator sit = lower_bound(dpSaver->begin(), dpSaver->end(), p, cmpD);
										if (sit == dpSaver->end())
										{
											continue;
										}
										else
										{
											bool test = true;
											vector<int>& cobSaver = data->commOutBoundary[actualcomm][actualc][tlabel];
											for (ui x = sit->pos; x < cobSaver.size(); ++x) {
												VertexID v = cobSaver[x];
												if (flag_comm[v] == count) {
													if (flag_comm[v] == 0)
														updated_flag[updated_flag_count++] = v;
													flag_comm[v]++;
													test = false;
													getit = true;
												}
											}
											if (test) {
												continue;
											}
										}
									}
									if (!getit) {
										canfind = false;
										break;
									}
								}
								else {
									vector<DegreePos>* dpSaver = &data->degreePosOut[actualcomm][actualc][label];
									if (dpSaver->empty())
									{
										canfind = false;
										break;
									}

									vector<DegreePos>::iterator sit = lower_bound(dpSaver->begin(), dpSaver->end(), p, cmpD);
									if (sit == dpSaver->end())
									{
										canfind = false;
										break;
									}
									else
									{
										bool test = true;
										vector<int>& cobSaver = data->commOutBoundary[actualcomm][actualc][label];
										for (ui x = sit->pos; x < cobSaver.size(); ++x) {
											VertexID v = cobSaver[x];
											if (flag_comm[v] == count) {
												if (flag_comm[v] == 0)
													updated_flag[updated_flag_count++] = v;
												flag_comm[v]++;
												test = false;
											}
										}
										if (test) {
											canfind = false;
											break;
										}
										/*if (narea == NULL)
										{

											//narea = new vector<int>(cobSaver->begin() + sit->pos, cobSaver->end());
											//sort(narea->begin(), narea->end());
											//pointers.push_back(narea);
										}
										else
										{
											//vector<int> t;
											vector<int> tempvector(cobSaver->begin() + sit->pos, cobSaver->end());
											sort(tempvector.begin(), tempvector.end());
											vector<int>::iterator it = set_intersection(narea->begin(), narea->end(), tempvector.begin(), tempvector.end(), narea->begin());
											narea->resize(it - narea->begin());
											if (narea->empty())
											{
												//if (index <= 2)
												canfind = false;
												break;
											}
											//*narea = t;
										}*/
									}
								}
                            }
                        }
                    }
                }
                if (updated_flag_count != 0 && canfind) {
                    count++;
                    boundary[n] = save_boundary[n];
                    //narea = new int[updated_flag_count + 1];
                    for (ui i = 0; i < updated_flag_count; ++i) {
                        VertexID v = updated_flag[i];
                        if (flag_comm[v] == count) {
                            boundary[n][nareacount++] = v;
                            //narea[nareacount++] = v;
                        }
                        flag_comm[v] = 0;
                    }
                    sort(boundary[n], boundary[n] + nareacount);
                    boundary_count[n] = nareacount;
                    //sort(narea, narea + nareacount);
                    //pointers.push_back(narea);
                }
                else {
                    for (ui i = 0; i < updated_flag_count; ++i) {
                        VertexID v = updated_flag[i];
                        flag_comm[v] = 0;
                    }
                }
                //outds.clear();
                if (!canfind)
                {
                    return;//break;
                }
                /*if (narea != NULL && nareacount != 0)
                {
                    boundary[n] = narea;
                    boundary_count[n] = nareacount;
                    //takeEffet.push_back(n);
                    //narea.clear();
                }*/
            }
            /*if (!canfind)
            {
                break;
            }*/
        }

        //if (!canfind)
        //{
            /*for (auto& p : pointers)
            {
                delete p;
            }*/
        //  return;// continue;
        //}
    }
    else
    {
        //for (int i = 1; i < patternGraph.nodenum + 1; ++i)
        //{
        //  boundary[i] = &data->communityNodes[supermatchmapori[i]];
        //}
    }

    //gm->uselessCut2++;

    vector<int> allmaps;
    if (cut3)
    {
        /*for (const auto& n : supermatchmap)
        {
        mystr += n.second;
        }*/

        //vector<map<int, int>> allmaps;
        //unordered_set<string> record;

        if (!getCompleteMatch(supermatchmapori, allmaps))//!(gm->getAllInPatternCompleteMatch(supermatch, supermatchmap, mystr, supermatch.begin(), newallmaps, cMap, usednodes)))
        {
            /*for (auto& p : pointers)
            {
                delete p;
            }*/
            //gm->uselessDouble++;
            //cout << "catch!" << endl;
            //for (auto& n : supermatchmap)
            //{
            //  gm->logger << n.first << " " << n.second << endl;
            //}
            //gm->logger << endl;
            return;// continue;
        }
    }
    //gm->usefulCS++;

    //unordered_map<int, unordered_map<int, unordered_map<int, int>>> oomessage;//, oimessage, iomessage;
    //storage->tools->getTwoHopPatternPairs(&patternGraph, supermatchmap, oomessage, oomessage, oomessage);//oimessage, iomessage);

    //TempMatchGraph t(*q->nodes, &nodeAttributes, &edgeAttributes, *q->outedges, *q->outedges);
    bool candup = false;
    
    bounddaf->g = originalgraph;
    
    if (true) {//boundfirst) {
        if (cut2)
        {
            bounddaf->nodeArea = boundary;
            bounddaf->nodeArea_count = boundary_count;
            bounddaf->initpIETree(supermatchmap);
        }
        else
        {
            //boundtm->nodeArea = NULL;
            bounddaf->nodeArea = boundary;
            bounddaf->nodeArea_count = boundary_count;
            bounddaf->initpIETree(supermatchmap);
        }

        int querynum = bounddaf->q->nodeNum;
        bounddaf->distributeplan = supermatchmapori;

        //for (ui i = 0; i < querynum + 1; ++i) {
        //  memset(bounddaf->weight_array[i], std::numeric_limits<ui>::max(), (bounddaf->g->nodenum + 1) * sizeof(ui));
        //}
        
        bounddaf->generateDPisoFilterPlan_comm(bounddaf->g, bounddaf->q, bounddaf->dpiso_tree, bounddaf->dpiso_order);

        /*if (boundfirst) {
            bounddaf->LDFFilter(bounddaf->g, q, bounddaf->overall_candidates, bounddaf->overall_candidates_count);  
            for (ui k = 0; k < 5; ++k) {
                if (k % 2 == 0) {
                    for (int i = 1; i < querynum; ++i) {
                        VertexID query_vertex = bounddaf->dpiso_order[i];
                        TreeNode& node = bounddaf->dpiso_tree[query_vertex];
                        bounddaf->pruneCandidates(bounddaf->g, bounddaf->q, query_vertex, node.bn_, node.bn_count_, bounddaf->overall_candidates, bounddaf->overall_candidates_count, bounddaf->flag, bounddaf->updated_flag);
                    }
                }
                else {
                    for (int i = querynum - 2; i >= 0; --i) {
                        VertexID query_vertex = bounddaf->dpiso_order[i];
                        TreeNode& node = bounddaf->dpiso_tree[query_vertex];
                        bounddaf->pruneCandidates(bounddaf->g, bounddaf->q, query_vertex, node.bn_, node.bn_count_, bounddaf->overall_candidates, bounddaf->overall_candidates_count, bounddaf->flag, bounddaf->updated_flag);
                    }
                }
            }
            bounddaf->buildTables_comm_overall(bounddaf->g, q, bounddaf->overall_candidates, bounddaf->overall_candidates_count, bounddaf->overall_edge_matrix);
        }*/

        for (ui i = 0; i < querynum; ++i) {
            bounddaf->matching_order[i] = bounddaf->dpiso_order[i];
        }

        for (ui i = 1; i < querynum; ++i) {
            bounddaf->pivots[i] = bounddaf->dpiso_tree[bounddaf->matching_order[i]].parent_;
        }

        int max_depth = querynum;
        for (ui i = 1; i <= max_depth; ++i) {
            bounddaf->extendable[i] = bounddaf->dpiso_tree[i].bn_count_;
        }

        bounddaf->generateBNBound(bounddaf->q, bounddaf->dpiso_order, bounddaf->bn, bounddaf->bn_count);

#ifdef ENABLE_FAILING_SET  
        bounddaf->computeAncestorBound(bounddaf->q, bounddaf->dpiso_tree, bounddaf->dpiso_order);
#endif
        boundfirst = false;
    }
    else {
        if (cut2)
        {
            bounddaf->nodeArea = boundary;
            bounddaf->nodeArea_count = boundary_count;
            bounddaf->initpIETree(supermatchmap);
        }
        else
        {
            //boundtm->nodeArea = NULL;
            bounddaf->nodeArea = boundary;
            bounddaf->nodeArea_count = boundary_count;
            bounddaf->initpIETree(supermatchmap);
        }

        bounddaf->distributeplan = supermatchmapori;

        //memset(bounddaf->weight_array[1], std::numeric_limits<ui>::max(), (q->nodenum) * (bounddaf->g->nodenum + 1) * sizeof(ui));
        //for (ui i = 1; i <= q->nodenum; ++i) {
            /*for (ui j = 1; j <= q->nodenum; ++j) {
                if (recdaf->edge_matrix[i][j] != NULL) {
                    delete recdaf->edge_matrix[i][j];
                }
                recdaf->edge_matrix[i][j] = NULL;
            }*/
            //memset(bounddaf->weight_array[i], std::numeric_limits<ui>::max(), (bounddaf->g->nodenum + 1) * sizeof(ui));
        //}
    }
    
    //TurboMatch tm(-1, &boundary, NULL, NULL, NULL, storage, &patternGraph, originalgraph);
    //tm.storeType = 0;
    //tm.communityGraphs = this->communityGraphs;

    //vector<vector<int>> finds;
    //bounddaf->vvans = &finds;
    //boundtm->newallmaps = &newallmaps;
    
    //cout << supermatchmap[1] << " "<< supermatchmap[2] << " " <<supermatchmap[3] << " " << supermatchmap[4] <<endl;
    
    int count = bounddaf->startMatchBound();
    //gm->internum++;
    //cout << count << endl;
    //if (count == 0)
    {
        //gm->uselessCS++;
        /*for (int n = 1; n <= patternGraph.nodenum; ++n)
        {
        gm->logger << n << " " << supermatchmapori[n] << endl;
        }
        gm->logger << endl;*/
    }
    //else
    {
        //gm->usefulCS++;
    }

    /*for (auto& p : pointers)
    {
        delete p;
    }*/

    if (cut3)
    {
        //#pragma omp critical
        {
			//cout << count * allmaps.size() << " ";
            gm->ansnum += count * allmaps.size();
        }
        /*for (int f = 0; f < finds.size(); f++)
        {
            for (int i = 0; i < allmaps.size(); ++i)
            {
                vector<int> newmap(finds[f].size(), -1);
                for (int j = 1; j < gm->schemes[allmaps[i]].size(); ++j)
                {
                    newmap[j - 1] = finds[f][gm->schemes[allmaps[i]][j] - 1];
                }
                for (int k = 0; k < newmap.size(); k++)
                {
                    gm->logger << k + 1 << " " << newmap[k] << endl;
                }
                gm->logger << endl;
            }
        }
        /*vector<map<int, int>>::iterator sit = newallmaps.begin();
        while (sit != newallmaps.end())
        {
        map<int, int> m = *sit;
        vector<int> newmap(finds[f].size(), -1);
        for (int i = 0; i < finds[f].size(); i++)
        {
        if (finds[f][i] != -1)
        {
        newmap[m[i + 1] - 1] = finds[f][i];
        }
        }
        //int id = 0;
        //tans[id].push_back(newmap);
        for (int k = 0; k < newmap.size(); k++)
        {
        gm->logger << k + 1 << " " << newmap[k] << endl;
        }
        gm->logger << endl;

        sit++;
        }*/
        //}
    }
    else
    {
        //#pragma omp critical
        //{
        gm->ansnum += count;
        //}
        //for (int f = 0; f < finds.size(); f++)
        //{
        //tans[0].push_back(finds[f]);
        //}
    }

    //for (const auto& m : dels)
    //{
    //  delete maps[m];
    //}
    //maps.clear();
    //currentMap.clear();
    //commvec.clear();
    //}
}



void DAF::initIETree()
{
    IETreeL = new vector<int>[q->nodeNum + 1];
    IETreeS = new vector<int>[q->nodeNum + 1];
    aIETreeL = new bool* [q->nodeNum + 1];
    for (int i = 1; i < q->nodeNum + 1; ++i) {
        aIETreeL[i] = new bool[q->nodeNum + 1];
        memset(aIETreeL[i], false, (q->nodeNum + 1) * sizeof(bool));
    }
    vector<unordered_set<int>> check(q->nodeNum + 1);
    int index = 0;
    for (int i = 0; i < schemenum; ++i)
    {
        for (int j = 1; j <= q->nodeNum; ++j)
        {
            if (schemes[i][j] != j)
            {
                if (check[j].find(schemes[i][j]) == check[j].end())
                {
                    IETreeS[j].push_back(schemes[i][j]);
                    IETreeL[schemes[i][j]].push_back(j);
                    aIETreeL[schemes[i][j]][j] = true;
                    check[j].insert(schemes[i][j]);
                    check[schemes[i][j]].insert(j);
                }
                break;
            }
        }
    }
}

void DAF::initpIETree(int* supermatchmap)
{
    if (pIETreeL == NULL)
    {
        //pIETreeL = new vector<int>[q->nodenum + 1];
        //pIETreeS = new vector<int>[q->nodenum + 1];
        paIETreeL = new bool*[q->nodeNum + 1];
        for (int i = 1; i <= q->nodeNum; ++i) {
            paIETreeL[i] = new bool[q->nodeNum + 1];
            memset(paIETreeL[i], false, (q->nodeNum + 1) * sizeof(bool));
        }
    }
    else
    {
        for (int i = 1; i <= q->nodeNum; ++i)
        {
            //pIETreeL[i].clear();
            //pIETreeS[i].clear();
            memset(paIETreeL[i], false, (q->nodeNum + 1) * sizeof(bool));
        }
    }

    //vector<unordered_set<int>> check(q->nodenum + 1);
    pschemes.clear();
    int index = 0;
    for (int i = 0; i < schemenum; ++i)
    {
        bool flag = true;
        for (int j = 1; j <= q->nodeNum; ++j)
        {
            int s1 = schemes[i][j];
            if (s1 != j && supermatchmap[s1] != supermatchmap[j])
            {
                flag = false;
                break;
            }
        }
        if (flag) {
            for (int j = 1; j <= q->nodeNum; ++j)
            {
                int posj = schemes[i][j];
                if (posj != j) // && !paIETreeL[posj][j]) //check[j].find(posj) == check[j].end())
                {
                    //pIETreeS[j].push_back(posj);
                    //pIETreeL[posj].push_back(j);
                    paIETreeL[posj][j] = true;
                    //check[j].insert(posj);
                    //check[posj].insert(j);
                    break;
                }
            }
            pschemes.push_back(schemes[i]);
        }       
    }

    /*for (int i = 0; i < pschemes.size(); ++i)
    {
        for (int j = 1; j <= q->nodenum; ++j)
        {
            int posj = (*pschemes[i])[j];
            if (posj != j)
            {
                pIETreeS[j].push_back(posj);
                pIETreeL[posj].push_back(j);
                break;
            }
        }
    }*/
}

size_t DAF::startMatchDense() {
    if(!DPisoFilterDense(g, q, candidates, candidates_count, dpiso_order, dpiso_tree)) {
		return 0;
	}
	
    buildTablesDense(g, q, candidates, candidates_count);
    //if (dpiso_tree == NULL) {
    //    generateDPisoFilterPlan(g, q, dpiso_tree, dpiso_order);
    //}
	
    generateDSPisoQueryPlan_comm(q, matching_order, pivots, dpiso_tree, dpiso_order,
                                                    candidates_count);
    
    size_t ansnum = exploreDPisoStyleDense(g, q, dpiso_tree, candidates, candidates_count, dpiso_order);

    return ansnum;
}

bool DAF::DPisoFilterDense(MemoryGraph *data_graph, MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree) {
    if (!LDFFilterDense(data_graph, query_graph, candidates, candidates_count))
        return false;
    
    //generateDPisoFilterPlan(data_graph, query_graph, tree, order);
    ui query_vertices_num = query_graph->nodeNum;
    
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    // The number of refinement is k. According to the original paper, we set k as 3.
    for (ui k = 0; k < 3; ++k) {
        if (k % 2 == 0) {
            for (int i = 1; i < query_vertices_num; ++i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesDense(data_graph, query_graph, query_vertex, node.bn_, node.bn_count_, candidates, candidates_count, flag, updated_flag);
                if (candidates_count[query_vertex] == 0)
                    return false;
            }
        }
        else {
            for (int i = query_vertices_num - 2; i >= 0; --i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesDense(data_graph, query_graph, query_vertex, node.fn_, node.fn_count_, candidates, candidates_count, flag, updated_flag);
                if (candidates_count[query_vertex] == 0)
                    return false;
            }
        }
    }

    return true;
    //return compactCandidatesBound(candidates, candidates_count, query_graph->nodenum);
    //return isCandidateSetValid(candidates, candidates_count, query_graph->nodenum);
}

bool DAF::LDFFilterDense(MemoryGraph *data_graph, MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count) {
    //allocateBuffer_comm(data_graph, query_graph, candidates, candidates_count);

    for (ui i = 1; i <= query_graph->nodeNum; ++i) {
        LabelID label = 0;
        ui degree = query_graph->degrees[i];
        candidates_count[i] = 0;

        //ui data_vertex_num;
        //const ui* data_vertices = g->getVerticesByLabel(label, data_vertex_num);

        //for (ui j = 0; j < data_vertex_num; ++j) {
        //    ui data_vertex = data_vertices[j];
        //    if (g->getVertexDegree(data_vertex) >= degree) {
        //        candidates[i][candidates_count[i]++] = data_vertex;
        //    }
        //}
        for (ui j = 0; j < data_graph->nodeNum; ++j) {
            ui data_vertex = data_graph->nodes[j];
            if (data_graph->degrees[data_vertex] >= degree) {
				if (query_graph->nodeAttributes[i].size() > data_graph->nodeAttributes[data_vertex].size())
					continue;
				if (query_graph->nodeLabels[i] != 0 && query_graph->nodeLabels[i] != data_graph->nodeLabels[data_vertex])
					continue;
				for (const auto& attrpair : query_graph->nodeAttributes[i]) {
					if (data_graph->nodeAttributes[data_vertex].find(attrpair.first) == data_graph->nodeAttributes[data_vertex].end()
						|| attrpair.second != data_graph->nodeAttributes[data_vertex][attrpair.first])
						continue;
				}
				//candmap[i][data_vertex] = candidates_count[i];
                candidates[i][candidates_count[i]++] = data_vertex;
            }
            else {
                //cout << "HIT" << endl;
            }
        }
		
        if (candidates_count[i] == 0) {
            return false;
        }
    }

    return true;
}


size_t DAF::exploreDPisoStyleDense(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order) {
    int max_depth = query_graph->nodeNum;
    /*ui *extendable = new ui[max_depth + 1];
    for (ui i = 0; i <= max_depth; ++i) {
        extendable[i] = tree[i].bn_count_;
    }

    // Generate backward neighbors.
    ui **bn;
    ui *bn_count;
    generateBN(query_graph, order, bn, bn_count);

    // Allocate the memory buffer.
    ui *idx;
    ui *idx_count;
    ui *embedding;
    ui *idx_embedding;
    ui *temp_buffer;
    ui **valid_candidate_idx;*/
    //bool *visited_vertices;
    //eva_allocateBuffer_comm(data_graph, query_graph, candidates_count, idx, idx_count, embedding, idx_embedding,
    //               temp_buffer, valid_candidate_idx);
    //std::fill(visited_vertices.begin(), visited_vertices.end(), false);

    // Evaluate the query.
    size_t embedding_cnt = 0;
    int cur_depth = 0;

    //for (int i = 1; i <= q->nodenum; ++i)
    //  embedding[i] = -1;

#ifdef ENABLE_FAILING_SET
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> vec_failing_set(max_depth);
    //std::unordered_map<VertexID, VertexID> reverse_embedding;
    //reverse_embedding.reserve(MAXIMUM_QUERY_GRAPH_SIZE * 2);
#endif

    VertexID start_vertex = order[0];
    
    //std::vector<dpiso_min_pq> vec_rank_queue;

    for (ui i = 0; i < candidates_count[start_vertex]; ++i) {
        VertexID v = candidates[start_vertex][i];
        embedding[start_vertex] = v;
        idx_embedding[start_vertex] = i;
        visited_vertices[v] = true;

#ifdef ENABLE_FAILING_SET
        reverse_embedding[v] = start_vertex;
#endif
        vec_rank_queue.emplace_back(dpiso_min_pq(extendable_vertex_compare));
        updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                               tree, start_vertex, extendable,
                               vec_rank_queue, query_graph);

        VertexID u = vec_rank_queue.back().top().first.first;
        vec_rank_queue.back().pop();

#ifdef ENABLE_FAILING_SET
        if (idx_count[u] == 0) {
            vec_failing_set[cur_depth] = ancestors[u];
        } else {
            vec_failing_set[cur_depth].reset();
        }
#endif

        cur_depth += 1;
        order[cur_depth] = u;
        idx[u] = 0;
        while (cur_depth > 0) {
			
            while (idx[u] < idx_count[u]) {
                ui valid_idx = valid_candidate_idx[u][idx[u]];
                v = candidates[u][valid_idx];

                if (visited_vertices[v]) {
                    idx[u] += 1;
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    continue;
                }
                embedding[u] = v;

                bool takeover = true;
                //ncMap[cur] = val;
                for (const auto& uv : IETreeS[u])
                {
                    if (embedding[uv] != -1 && ((embedding[uv] < v)))
                    {
                        takeover = false;
                        break;
                    }
                }
                if (!takeover)
                {
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    idx[u] = idx_count[u];
                    //idx[u] += 1;
                    continue;
                }

				if (!endmax[u]) {
					int maxlevel = -1;
					for (const auto& uv : IETreeL[u])
					{
						if (embedding[uv] != -1 && ((embedding[uv] > v)))
						{
							takeover = false;
							maxlevel = max(maxlevel, embedding[uv]);
							//break;
						}
					}
					if (!takeover)
					{
						//vector<int>* b = &(*g2->invec)[pred_pair];
						//last_candidate_index = upper_bound(b->begin() + last_candidate_index, b->end(), maxlevel) - b->begin();
						//idx[u] = upper_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
	#ifdef ENABLE_FAILING_SET
						vec_failing_set[cur_depth] = ancestors[u];
						vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
						vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
	#endif
						int last_cand = upper_bound(candidates[u] + valid_idx, candidates[u] + candidates_count[u], maxlevel) - candidates[u];
						int last_idx = lower_bound(valid_candidate_idx[u] + idx[u], valid_candidate_idx[u] + idx_count[u], last_cand) - valid_candidate_idx[u];
						//idx[u]++;
						idx[u] = last_idx;
						endmax[u] = true;
						continue;
					}
				}

                idx_embedding[u] = valid_idx;
                visited_vertices[v] = true;
                idx[u] += 1;

#ifdef ENABLE_FAILING_SET
                reverse_embedding[v] = u;
#endif

                if (cur_depth == max_depth - 1) {
                    embedding_cnt += schemenum;
                    
                    visited_vertices[v] = false;
#ifdef ENABLE_FAILING_SET
                    //reverse_embedding.erase(embedding[u]);
                    reverse_embedding[embedding[u]] = 0;
                    vec_failing_set[cur_depth].set();
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];

#endif
                    //if (embedding_cnt >= output_limit_num) {
                    //    goto EXIT;
                    //}
                } else {
                    cur_depth += 1;
                    int vecsize = vec_rank_queue.size();
                    vec_rank_queue.push_back(vec_rank_queue[vecsize - 1]);
                    //vec_rank_queue.emplace_back(vec_rank_queue.back());

                    updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                                           tree, u, extendable,
                                           vec_rank_queue, query_graph);

                    u = vec_rank_queue.back().top().first.first;
                    vec_rank_queue.back().pop();
                    idx[u] = 0;
                    order[cur_depth] = u;

#ifdef ENABLE_FAILING_SET
                    if (idx_count[u] == 0) {
                        vec_failing_set[cur_depth - 1] = ancestors[u];
                    } else {
                        vec_failing_set[cur_depth - 1].reset();
                    }
#endif
                }
            }

			endmax[u] = false;
            embedding[u] = -1;
            cur_depth -= 1;
            vec_rank_queue.pop_back();
            u = order[cur_depth];
            visited_vertices[embedding[u]] = false;
            restoreExtendableVertex(tree, u, extendable);
			
#ifdef ENABLE_FAILING_SET
            //reverse_embedding.erase(embedding[u]);
            reverse_embedding[embedding[u]] = 0;
            if (cur_depth != 0) {
                if (!vec_failing_set[cur_depth].test(u)) {
                    vec_failing_set[cur_depth - 1] = vec_failing_set[cur_depth];
                    idx[u] = idx_count[u];
                } else {
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
                }
            }
#endif
        }
    }

    embedding[start_vertex] = -1;
    // Release the buffer.
    //EXIT:
    //eva_releaseBuffer_comm(max_depth, idx, idx_count, embedding, idx_embedding, temp_buffer, valid_candidate_idx,
     //             bn, bn_count);

    return embedding_cnt;
}


size_t DAF::startMatchBound() {
    if(!DPisoFilterBound(g, q, candidates, candidates_count, dpiso_order, dpiso_tree)) {
		return 0;
	}
    
    //refineTables(g, q, candidates, candidates_count);
    buildTablesBound(g, q, candidates, candidates_count);
    
    //if (dpiso_tree == NULL) {
    //    generateDPisoFilterPlan(g, q, dpiso_tree, dpiso_order);
    //}
    //return 0;
    generateDSPisoQueryPlan_comm(q, matching_order, pivots, dpiso_tree, dpiso_order,
                                                    candidates_count);

    size_t ansnum = exploreDPisoStyleBound(g, q, dpiso_tree, candidates, candidates_count, dpiso_order);

    return ansnum;
}

bool DAF::LDFFilterBound(MemoryGraph *data_graph, MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count) {
    //allocateBuffer_comm(data_graph, query_graph, candidates, candidates_count);

    //eset.clear();
    for (ui i = 1; i <= q->nodeNum; ++i) {
        LabelID label = 0;
        ui degree = q->degrees[i];
        candidates_count[i] = 0;

        //ui data_vertex_num;
        //const ui* data_vertices = g->getVerticesByLabel(label, data_vertex_num);      

        //for (ui j = 0; j < data_vertex_num; ++j) {
        //    ui data_vertex = data_vertices[j];
        //    if (g->getVertexDegree(data_vertex) >= degree) {
        //        candidates[i][candidates_count[i]++] = data_vertex;
        //    }
        //}
        //for (ui j = 0; j < g->nodenum; ++j) {
        //  ui data_vertex = (*g->nodes)[j];
        //  if ((*g->outedges)[data_vertex].size() >= degree) {
        //        candidates[i][candidates_count[i]++] = data_vertex;
        //    }
        //}
        if (nodeArea[i] == NULL)
        {
            /*int eindex = 0;
            unordered_set<int> leftset;
            for (int j = 0; j < eset.size(); ++j)
                leftset.insert(eset[j]);*/

            auto c = &data->communityNodes[distributeplan[i]];
            for (ui j = 0; j < c->size(); ++j) {
                ui data_vertex = (*c)[j];
                if (g->degrees[data_vertex] >= degree) {
                    //int ccount = candidates_count[i];
					//candmap[i][data_vertex] = candidates_count[i];
					if (query_graph->nodeAttributes[i].size() > data_graph->nodeAttributes[data_vertex].size())
						continue;
					if (query_graph->nodeLabels[i] != 0 && query_graph->nodeLabels[i] != data_graph->nodeLabels[data_vertex])
						continue;
					for (const auto& attrpair : query_graph->nodeAttributes[i]) {
						if (data_graph->nodeAttributes[data_vertex].find(attrpair.first) == data_graph->nodeAttributes[data_vertex].end()
							|| attrpair.second != data_graph->nodeAttributes[data_vertex][attrpair.first])
							continue;
					}
                    candidates[i][candidates_count[i]++] = data_vertex;
                    /*for (unordered_set<int>::iterator setinter = leftset.begin(); setinter != leftset.end();) {
                        int index = *setinter;
                        if (candidates_count[index] > ccount && candidates[index][ccount] == data_vertex) {
                            setinter++;
                        }
                        else {
                            leftset.erase(setinter++);
                        }
                    }*/
                }
            }
            /*if (!leftset.empty()) {
                int number = *leftset.begin();
                esetno[i] = number;
            }
            else {
                esetno[i] = i;
                eset.push_back(i);
            }*/
            //auto c = &data->communityNodes[distributeplan[i]];
            //std::copy((*nodeArea)[i]->begin(), (*nodeArea)[i]->end(), candidates[i]);
            //candidates_count[i] = (*nodeArea)[i]->size();
            // do not use (*communityGraphs)[distributeplan[i]]->nodes because their ids are mapped to 1, 2, 3, ...
            /*int kx = 0;
            auto c = &data->communityNodes[distributeplan[i]];
            ui* ocd = overall_candidates[i];
            for (ui j = 0; j < c->size(); ++j) {
                ui data_vertex = (*c)[j];
                if (g->degrees[data_vertex] >= degree) {
                    kx = lower_bound(ocd + kx, ocd + overall_candidates_count[i], data_vertex) - ocd;
                    ui overall_vertex = ocd[kx];
                    if (overall_vertex == data_vertex) {
                        int ci = candidates_count[i];
                        candidates[i][candidates_count[i]++] = data_vertex;
                        cand_idx_mapper[i][ci] = kx;
                        //cand_idx_mapper_rev[i][kx] = ci;
                    }
                }
            }*/
        }
        else
        {
            //std::copy(nodeArea[i]->begin(), nodeArea[i]->end(), candidates[i]);
            //candidates_count[i] = nodeArea[i]->size();
            /*int eindex = 0;
            unordered_set<int> leftset;
            for (int j = 0; j < eset.size(); ++j)
                leftset.insert(eset[j]);*/

            auto c = nodeArea[i];
            for (ui j = 0; j < nodeArea_count[i]; ++j) {
                ui data_vertex = c[j];
                if (g->degrees[data_vertex] >= degree) {
                    //int ccount = candidates_count[i];
					//candmap[i][data_vertex] = candidates_count[i];
					if (query_graph->nodeAttributes[i].size() > data_graph->nodeAttributes[data_vertex].size())
						continue;
					if (query_graph->nodeLabels[i] != 0 && query_graph->nodeLabels[i] != data_graph->nodeLabels[data_vertex])
						continue;
					for (const auto& attrpair : query_graph->nodeAttributes[i]) {
						if (data_graph->nodeAttributes[data_vertex].find(attrpair.first) == data_graph->nodeAttributes[data_vertex].end()
							|| attrpair.second != data_graph->nodeAttributes[data_vertex][attrpair.first])
							continue;
					}
                    candidates[i][candidates_count[i]++] = data_vertex;
                    /*for (unordered_set<int>::iterator setinter = leftset.begin(); setinter != leftset.end();) {
                        int index = *setinter;
                        if (candidates_count[index] > ccount && candidates[index][ccount] == data_vertex) {
                            setinter++;
                        }
                        else {
                            leftset.erase(setinter++);
                        }
                    }*/
                }
            }
            /*if (!leftset.empty()) {
                int number = *leftset.begin();
                esetno[i] = number;
            }
            else {
                esetno[i] = i;
                eset.push_back(i);
            }*/
            /*int kx = 0;
            ui* ocd = overall_candidates[i];
            for (ui j = 0; j < nodeArea[i]->size(); ++j) {
                ui data_vertex = (*nodeArea[i])[j];
                //if ((*g->outedges)[data_vertex].size() >= degree) {
                kx = lower_bound(ocd + kx, ocd + overall_candidates_count[i], data_vertex) - ocd;
                ui overall_vertex = ocd[kx];
                if (overall_vertex == data_vertex) {
                    int ci = candidates_count[i];
                    candidates[i][candidates_count[i]++] = data_vertex;
                    cand_idx_mapper[i][ci] = kx;
                    //cand_idx_mapper_rev[i][kx] = ci;
                }
            }*/
        }

        if (candidates_count[i] == 0) {
            return false;
        }
    }

    return true;
}

bool DAF::DPisoFilterBound(MemoryGraph *data_graph, MemoryGraph *query_graph, ui **&candidates, ui *&candidates_count,
                            ui *&order, TreeNode *&tree) {
    if (!LDFFilterBound(data_graph, query_graph, candidates, candidates_count))
        return false;
    
    //generateDPisoFilterPlan(data_graph, query_graph, tree, order);
	
    ui query_vertices_num = query_graph->nodeNum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);
    
    // The number of refinement is k. According to the original paper, we set k as 3.
    for (ui k = 0; k < 3; ++k) {
        if (k % 2 == 0) {
			for (int i = 1; i < query_vertices_num; ++i) {
				VertexID query_vertex = order[i];
				TreeNode& node = tree[query_vertex];
				pruneCandidatesBound(data_graph, query_graph, query_vertex, node.bn_, node.bn_count_, candidates, candidates_count, flag, updated_flag);
				if (candidates_count[query_vertex] == 0)
					return false;
			}
        }
        else {
            for (int i = query_vertices_num - 2; i >= 0; --i) {
                VertexID query_vertex = order[i];
                TreeNode& node = tree[query_vertex];
                pruneCandidatesBound(data_graph, query_graph, query_vertex, node.fn_, node.fn_count_, candidates, candidates_count, flag, updated_flag);
                if (candidates_count[query_vertex] == 0)
                    return false;
            }
        }
    }
    
    return true;
    //return compactCandidatesBound(candidates, candidates_count, query_graph->nodenum);
    //return isCandidateSetValid(candidates, candidates_count, query_graph->nodenum);
}

size_t DAF::exploreDPisoStyleBound(const MemoryGraph *data_graph, const MemoryGraph *query_graph, TreeNode *tree,
                                        ui **candidates, ui *candidates_count, ui *order) {
    int max_depth = query_graph->nodeNum;
    /*ui *extendable = new ui[max_depth + 1];
    for (ui i = 0; i <= max_depth; ++i) {
        extendable[i] = tree[i].bn_count_;
    }

    // Generate backward neighbors.
    ui **bn;
    ui *bn_count;
    generateBN(query_graph, order, bn, bn_count);

    // Allocate the memory buffer.
    ui *idx;
    ui *idx_count;
    ui *embedding;
    ui *idx_embedding;
    ui *temp_buffer;
    ui **valid_candidate_idx;*/
    //bool *visited_vertices;
    //eva_allocateBuffer_comm(data_graph, query_graph, candidates_count, idx, idx_count, embedding, idx_embedding,
    //               temp_buffer, valid_candidate_idx);
    //std::fill(visited_vertices.begin(), visited_vertices.end(), false);

    // Evaluate the query.
    size_t embedding_cnt = 0;
    int cur_depth = 0;

    //for (int i = 1; i <= q->nodenum; ++i)
    //  embedding[i] = -1;

#ifdef ENABLE_FAILING_SET
    //std::vector<std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>> vec_failing_set(max_depth);
    //std::unordered_map<VertexID, VertexID> reverse_embedding;
    //reverse_embedding.reserve(MAXIMUM_QUERY_GRAPH_SIZE * 2);
#endif

    VertexID start_vertex = order[0];
    
    //std::vector<dpiso_min_pq> vec_rank_queue;

    for (ui i = 0; i < candidates_count[start_vertex]; ++i) {
        VertexID v = candidates[start_vertex][i];
        embedding[start_vertex] = v;
        idx_embedding[start_vertex] = i;
        visited_vertices[v] = true;

#ifdef ENABLE_FAILING_SET
        reverse_embedding[v] = start_vertex;
#endif
        vec_rank_queue.emplace_back(dpiso_min_pq(extendable_vertex_compare));
        updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                               tree, start_vertex, extendable,
                               vec_rank_queue, query_graph);

        VertexID u = vec_rank_queue.back().top().first.first;
        vec_rank_queue.back().pop();

#ifdef ENABLE_FAILING_SET
        if (idx_count[u] == 0) {
            vec_failing_set[cur_depth] = ancestors[u];
        } else {
            vec_failing_set[cur_depth].reset();
        }
#endif

        cur_depth += 1;
        order[cur_depth] = u;
        idx[u] = 0;
        while (cur_depth > 0) {
            while (idx[u] < idx_count[u]) {
                ui valid_idx = valid_candidate_idx[u][idx[u]];
                v = candidates[u][valid_idx];

                if (visited_vertices[v]) {
                    idx[u] += 1;
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    continue;
                }

                bool takeover = true;
                int prev_n2 = v;
                for (int x = 0; x < cur_depth; ++x) {
                    int vx = order[x];
                    if (paIETreeL[vx][u] && embedding[vx] < prev_n2) {
                        takeover = false;
                        break;
                    }
                }
                /*for (const auto& uv : pIETreeS[u])
                {
                    if (embedding[uv] != -1 && ((embedding[uv] < prev_n2)))
                    {
                        takeover = false;
                        break;
                    }
                }*/

                if (!takeover)
                {
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    idx[u] = idx_count[u];
                    //idx[u]++;
                    continue;
                }
                int maxlevel = -1;
                for (int x = 0; x < cur_depth; ++x) {
                    int vx = order[x];
                    if (paIETreeL[u][vx] && embedding[vx] > prev_n2) {
                        takeover = false;
                        maxlevel = max(maxlevel, embedding[vx]);
                        //break;
                    }
                }
                /*for (const auto& uv : pIETreeL[u])
                {
                    if (embedding[uv] != -1 && ((embedding[uv] > prev_n2)))
                    {
                        takeover = false;
                        maxlevel = max(maxlevel, embedding[uv]);
                        //break;
                    }
                }*/
                if (!takeover)
                {
#ifdef ENABLE_FAILING_SET
                    vec_failing_set[cur_depth] = ancestors[u];
                    vec_failing_set[cur_depth] |= ancestors[reverse_embedding[v]];
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
#endif
                    int last_cand = upper_bound(candidates[u], candidates[u] + candidates_count[u], maxlevel) - candidates[u];
                    int last_idx = lower_bound(valid_candidate_idx[u], valid_candidate_idx[u] + idx_count[u], last_cand) - valid_candidate_idx[u];
                    //idx[u]++;
                    idx[u] = last_idx;
					endmax[u] = false;
                    //vector<int>* b = (*nodeArea)[curr_n1];
                    //last_candidate_index = upper_bound(b->begin() + last_candidate_index, b->end(), maxlevel) - b->begin();
                    //last_candidate_index = upper_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
                    continue;
                }

                embedding[u] = v;
                idx_embedding[u] = valid_idx;
                visited_vertices[v] = true;
                idx[u] += 1;

#ifdef ENABLE_FAILING_SET
                reverse_embedding[v] = u;
#endif
                
                if (cur_depth == max_depth - 1) {
                    embedding_cnt += pschemes.size();
                    visited_vertices[v] = false;

                    /*for (int j = 0; j < pschemes.size(); ++j)
                    {
                        vector<int> t;
                        for (int i = 1; i <= (*q->nodes).size(); ++i)
                        {
                            t.push_back(embedding[(*pschemes[j])[i]]);
                            //gm->logger << i << " " <<  ncMap[(*pschemes[j])[i]] << endl;
                        }
                        //gm->logger << endl;
                        vvans->push_back(t);
                    }*/
#ifdef ENABLE_FAILING_SET
                    //reverse_embedding.erase(embedding[u]);
                    reverse_embedding[embedding[u]] = 0;
                    vec_failing_set[cur_depth].set();
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];

#endif
                    //if (embedding_cnt >= output_limit_num) {
                    //    goto EXIT;
                    //}
                } else {
                    cur_depth += 1;
                    int vecsize = vec_rank_queue.size();
                    vec_rank_queue.push_back(vec_rank_queue[vecsize - 1]);
                    //vec_rank_queue.emplace_back(vec_rank_queue.back());

                    updateExtendableVertex(idx_embedding, idx_count, valid_candidate_idx, temp_buffer,
                                           tree, u, extendable,
                                           vec_rank_queue, query_graph);

                    u = vec_rank_queue.back().top().first.first;
                    vec_rank_queue.back().pop();
                    idx[u] = 0;
                    order[cur_depth] = u;

#ifdef ENABLE_FAILING_SET
                    if (idx_count[u] == 0) {
                        vec_failing_set[cur_depth - 1] = ancestors[u];
                    } else {
                        vec_failing_set[cur_depth - 1].reset();
                    }
#endif
                }
            }

			endmax[u] = false;
            embedding[u] = -1;
            cur_depth -= 1;
            vec_rank_queue.pop_back();
            u = order[cur_depth];
            visited_vertices[embedding[u]] = false;
            restoreExtendableVertex(tree, u, extendable);
            
#ifdef ENABLE_FAILING_SET
            reverse_embedding[embedding[u]] = 0;
            //reverse_embedding.erase(embedding[u]);
            if (cur_depth != 0) {
                if (!vec_failing_set[cur_depth].test(u)) {
                    vec_failing_set[cur_depth - 1] = vec_failing_set[cur_depth];
                    idx[u] = idx_count[u];
                } else {
                    vec_failing_set[cur_depth - 1] |= vec_failing_set[cur_depth];
                }
            }
#endif
        }
    }

    embedding[start_vertex] = -1;
    // Release the buffer.
    //EXIT:
    //eva_releaseBuffer_comm(max_depth, idx, idx_count, embedding, idx_embedding, temp_buffer, valid_candidate_idx,
    //              bn, bn_count);

    return embedding_cnt;
}

void DAF::computeAncestor(const MemoryGraph *query_graph, TreeNode *tree, VertexID *order) {
    ui query_vertices_num = query_graph->nodeNum;
    //ancestors.resize(query_vertices_num + 1);
    ancestors = new std::bitset<MAXIMUM_QUERY_GRAPH_SIZE>[query_vertices_num + 1];

    // Compute the ancestor in the top-down order.
    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID u = order[i];
        TreeNode &u_node = tree[u];
        ancestors[u].set(u);
        for (ui j = 0; j < u_node.bn_count_; ++j) {
            VertexID u_bn = u_node.bn_[j];
            ancestors[u] |= ancestors[u_bn];
        }
    }
}

void DAF::computeAncestorBound(const MemoryGraph *query_graph, TreeNode *tree, VertexID *order) {
    ui query_vertices_num = query_graph->nodeNum;
    //ancestors.resize(query_vertices_num + 1);
    

    // Compute the ancestor in the top-down order.
    for (ui i = 0; i < query_vertices_num; ++i) {
        VertexID u = order[i];
        TreeNode &u_node = tree[u];
        ancestors[u].set(u);
        for (ui j = 0; j < u_node.bn_count_; ++j) {
            VertexID u_bn = u_node.bn_[j];
            ancestors[u] |= ancestors[u_bn];
        }
    }
}

/*
void DAF::buildTables_comm_overall(const TempMatchGraph *data_graph, const TempMatchGraph *query_graph, ui **candidates, ui *candidates_count, Edges** edge_matrix) {
    ui query_vertices_num = query_graph->nodenum;
    //std::fill(flag, flag + data_graph->nodenum + 1, 0);

    std::vector<VertexID> build_table_order(query_vertices_num);
    for (ui i = 0; i < query_vertices_num; ++i) {
        build_table_order[i] = i + 1;
    }

    std::sort(build_table_order.begin(), build_table_order.end(), [query_graph](VertexID l, VertexID r) {
        int dl = query_graph->degrees[l];
        int dr = query_graph->degrees[r];
        if (dl == dr) {
            return l < r;
        }
        return dl > dr;
    });

    //std::vector<ui> temp_edges(data_graph->edgenum * 2);

    for (auto u : build_table_order) {
        ui u_nbrs_count;
        //const VertexID* u_nbrs = query_graph->getVertexNeighbors(u, u_nbrs_count);

        ui updated_flag_count = 0;

        //for (ui i = 0; i < u_nbrs_count; ++i) {
        for (const auto& u_nbr : query_graph->outvecp[u]) {
            if (u > u_nbr)
                continue;

            if (updated_flag_count == 0) {
                for (ui j = 0; j < candidates_count[u]; ++j) {
                    VertexID v = candidates[u][j];
                    flag[v] = j + 1;
                    updated_flag[updated_flag_count++] = v;
                }
            }

            //edge_matrix[u_nbr][u] = new Edges;
            edge_matrix[u_nbr][u].vertex_count_ = candidates_count[u_nbr];
            edge_matrix[u_nbr][u].offset_.resize(candidates_count[u_nbr] + 1);

            //edge_matrix[u][u_nbr] = new Edges;
            edge_matrix[u][u_nbr].vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr].offset_.resize(candidates_count[u] + 1);
            fill(edge_matrix[u][u_nbr].offset_.begin(), edge_matrix[u][u_nbr].offset_.end(), 0);

            ui local_edge_count = 0;
            ui local_max_degree = 0;

            edge_matrix[u_nbr][u].edge_.clear();

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                VertexID v = candidates[u_nbr][j];
                edge_matrix[u_nbr][u].offset_[j] = local_edge_count;

                ui local_degree = 0;

                int spos = local_edge_count;
                for (const auto& v_nbr : data_graph->outvecp[v]) {
                    if (flag[v_nbr] != 0) {
                        ui position = flag[v_nbr] - 1;
                        edge_matrix[u_nbr][u].edge_.push_back(position);
                        local_edge_count++;
                        edge_matrix[u][u_nbr].offset_[position + 1] += 1;
                    }
                }
                int epos = local_edge_count;
                sort(edge_matrix[u_nbr][u].edge_.begin() + spos, edge_matrix[u_nbr][u].edge_.begin() + epos);
            }

            edge_matrix[u_nbr][u].offset_[candidates_count[u_nbr]] = local_edge_count;
            edge_matrix[u_nbr][u].edge_count_ = local_edge_count;

            edge_matrix[u][u_nbr].edge_count_ = local_edge_count;
            edge_matrix[u][u_nbr].edge_.resize(local_edge_count);

            //local_max_degree = 0;
            for (ui j = 1; j <= candidates_count[u]; ++j) {
                edge_matrix[u][u_nbr].offset_[j] += edge_matrix[u][u_nbr].offset_[j - 1];
            }

            for (ui j = 0; j < candidates_count[u_nbr]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u_nbr][u].offset_[begin]; k < edge_matrix[u_nbr][u].offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u_nbr][u].edge_[k];

                    edge_matrix[u][u_nbr].edge_[edge_matrix[u][u_nbr].offset_[end]++] = begin;
                }
            }

            for (ui j = candidates_count[u]; j >= 1; --j) {
                edge_matrix[u][u_nbr].offset_[j] = edge_matrix[u][u_nbr].offset_[j - 1];
            }
            edge_matrix[u][u_nbr].offset_[0] = 0;
        }

        for (ui i = 0; i < updated_flag_count; ++i) {
            VertexID v = updated_flag[i];
            flag[v] = 0;
        }
    }

#if ENABLE_QFLITER == 1
    qfliter_bsr_graph_ = new BSRGraph**[query_vertices_num];
    for (ui i = 0; i < query_vertices_num; ++i) {
        qfliter_bsr_graph_[i] = new BSRGraph*[query_vertices_num];
        for (ui j = 0; j < query_vertices_num; ++j) {

            qfliter_bsr_graph_[i][j] = new BSRGraph[query_vertices_num];

            if (edge_matrix[i][j] != NULL) {
                qfliter_bsr_graph_[i][j]->load(edge_matrix[i][j]->vertex_count_,
                                               edge_matrix[i][j]->offset_, edge_matrix[i][j]->offset_,
                                               edge_matrix[i][j]->edge_);
            }
        }
    }
#endif
}
*/

/*
void DAF::refineTables(const TempMatchGraph *data_graph, const TempMatchGraph *query_graph, ui **candidates, ui *candidates_count) {
    ui query_vertices_num = query_graph->nodenum;
    for (int i = 1; i <= query_vertices_num; ++i) {
        VertexID u = i;
        for (const auto& u_nbr : query_graph->outvecp[u]) {
            if (u_nbr > u)
                continue;
            //Edges* cur_edge = &edge_matrix[u][u_nbr];
            edge_matrix[u][u_nbr].vertex_count_ = candidates_count[u];
            edge_matrix[u][u_nbr].offset_.resize(candidates_count[u] + 1);
            edge_matrix[u][u_nbr].edge_.clear();

            //Edges* cur_rev = &edge_matrix[u_nbr][u];
            edge_matrix[u_nbr][u].offset_.resize(candidates_count[u_nbr] + 1);
            fill(edge_matrix[u_nbr][u].offset_.begin(), edge_matrix[u_nbr][u].offset_.end(), 0);

            int savepos = 0;
            edge_matrix[u][u_nbr].offset_[0] = 0;
            for (int j = 0; j < candidates_count[u]; ++j) {
                VertexID uc = candidates[u][j];
                savepos = lower_bound(overall_candidates[u] + savepos, overall_candidates[u] + overall_candidates_count[u], uc) - overall_candidates[u];
                //if (overall_candidates[u][savepos] != uc) {
                //  continue;
                //}

                Edges* overall_cur = &overall_edge_matrix[u][u_nbr];
                int start = overall_cur->offset_[savepos];
                int end = overall_cur->offset_[savepos + 1];
                
                int upos = start;
                int edgenum = 0;
                for (int k = 0; k < candidates_count[u_nbr]; ++k) {
                    int over_k = cand_idx_mapper[u_nbr][k];
                    upos = lower_bound(overall_cur->edge_.begin() + upos, overall_cur->edge_.begin() + end, over_k) - overall_cur->edge_.begin();
                    if (upos < end) {
                        if (overall_cur->edge_[upos] != over_k)
                            continue;
                            //cout << over_k << " " << "ERROR 2" << endl;
                        edge_matrix[u][u_nbr].edge_.push_back(k);
                        edge_matrix[u_nbr][u].offset_[k + 1]++;
                        edgenum++;
                    }
                    else
                        break;
                }
                edge_matrix[u][u_nbr].offset_[j + 1] = edge_matrix[u][u_nbr].offset_[j] + edgenum;
            }
        
            edge_matrix[u_nbr][u].vertex_count_ = candidates_count[u_nbr];         
            edge_matrix[u_nbr][u].edge_.resize(edge_matrix[u][u_nbr].edge_.size());
            edge_matrix[u_nbr][u].offset_[0] = 0;
            for (int p = 1; p <= candidates_count[u_nbr]; ++p) {
                edge_matrix[u_nbr][u].offset_[p] += edge_matrix[u_nbr][u].offset_[p - 1];
            }

            for (ui j = 0; j < candidates_count[u]; ++j) {
                ui begin = j;
                for (ui k = edge_matrix[u][u_nbr].offset_[begin]; k < edge_matrix[u][u_nbr].offset_[begin + 1]; ++k) {
                    ui end = edge_matrix[u][u_nbr].edge_[k];

                    edge_matrix[u_nbr][u].edge_[edge_matrix[u_nbr][u].offset_[end]++] = begin;
                }
            }

            for (ui j = candidates_count[u_nbr]; j >= 1; --j) {
                edge_matrix[u_nbr][u].offset_[j] = edge_matrix[u_nbr][u].offset_[j - 1];
            }
            edge_matrix[u_nbr][u].offset_[0] = 0;
        }
    }
}
*/

bool DAF::getCompleteMatch(int* supermatchmap, vector<int>& allmaps)
{
    for(int i = 0; i < schemenum; ++i)
    {		
		for (int j = 1; j <= q->nodeNum; ++j) {
			int snode = schemes[i][j];
			if (supermatchmap[snode] < supermatchmap[j])
				return false;
			else if (supermatchmap[snode] > supermatchmap[j])
				break;
		}
        bool check = true;
        for (int j = 0; j < i; ++j) {
            bool istrue = false;
            for (int k = 1; k <= q->nodeNum; ++k) {
                int vi = schemes[i][k];
                int vj = schemes[j][k];
                if (vi != vj && supermatchmap[vi] != supermatchmap[vj]) {
                    istrue = true;
                    break;
                }
            }
            if (!istrue) {
                check = false;
                break;
            }
        }
        if (!check)
            continue;

        allmaps.push_back(i);
        //bool smaller = false;
        //string thisstr = "";
        /*for (int j = 1; j < q->nodenum; ++j)
        {
            int snode = schemes[i][j];
            if (!smaller)
            {
                if (supermatchmap[snode] < supermatchmap[j])
                    return false;
                else if (supermatchmap[snode] > supermatchmap[j])
                {
                    smaller = true;
                }
            }
            //string str = to_string(supermatchmap[schemes[i][j]]);
            //thisstr += to_string(supermatchmap[snode]);
            //thisstr += " ";
        }*/

        //if (record.find(thisstr) == record.end())
        //{
            //allmaps.push_back(i);
            //record.insert(thisstr);
        //}
    }

    return true;
}