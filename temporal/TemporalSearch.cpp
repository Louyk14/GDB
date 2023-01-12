#include "TemporalSearch.h"

using namespace std;

int TemporalSearch::mapID(int& n, unordered_map<int, int>& mapper, unordered_map<int, int>& rev_mapper, int index) {
    if (mapper.find(n) != mapper.end())
        n = mapper[n];
    else {
        mapper[n] = index;
        rev_mapper[index] = n;
        n = index;
        index += 1;
	}

    return index;
}

void TemporalSearch::loadGraph(TemporalGraph& g, string file_path, unordered_map<int, int>& rev_mapper, bool isdouble) {
	int tmax = -1;
    int tmin = -1;

    int nmax = -1;

    unordered_map<int, int> mapper;
    
    int index = 1;
	g.edge_num = 0;
	g.maxstamp = -1;
	g.minstamp = -1;

	int n1, n2, t;

	fstream f_pre(file_path, ios::in);
	while(f_pre >> n1 >> n2 >> t) {
        index = mapID(n1, mapper, rev_mapper, index);
        index = mapID(n2, mapper, rev_mapper, index);

		//cout << n1 << " " << n2 << " " << t << endl;
	}
	f_pre.close();
	
	g.init(index - 1);
	
	fstream f(file_path, ios::in);
	while(f >> n1 >> n2 >> t) {
		if (n1 == n2)
			continue;
		g.t_edge_num++;

        index = mapID(n1, mapper, rev_mapper, index);
        index = mapID(n2, mapper, rev_mapper, index);

        nmax = max(n1, nmax);
		nmax = max(n2, nmax);

		g.sum_t_vertex[n1].push_back(t);
		g.network[n1].insert(n2);
		g.record_edges.push_back(t);

		if (g.maxstamp == -1 || g.maxstamp < t) {
			g.maxstamp = t;
		}
		if (g.minstamp == -1 || g.minstamp > t) {
			g.minstamp = t;
		}

        if (tmax == -1 || t > tmax)
            tmax = t;
        if (tmin == -1 || t < tmin)
            tmin = t;

		if (g.graph[n1] != NULL) {
			if (g.graph[n1]->find(n2) == g.graph[n1]->end()) {
				g.edge_num++;
				(*g.graph[n1])[n2] = vector<int>();
			}
            (*g.graph[n1])[n2].push_back(t);
            g.degree[n1] += 1;
		}
        else {
            g.graph[n1] = new unordered_map<int, vector<int>>();
            (*g.graph[n1])[n2] = vector<int>(1, t);
            g.edge_num += 1;
            g.degree[n1] = 1;
		}

		if (!isdouble || n1 == n2)
			continue;

		g.t_edge_num++;

		int tmp = n1;
		n1 = n2;
		n2 = tmp;

		g.sum_t_vertex[n1].push_back(t);
		g.network[n1].insert(n2);

        if (tmax == -1 || t > tmax)
            tmax = t;
        if (tmin == -1 || t < tmin)
            tmin = t;

		if (g.graph[n1] != NULL) {
			if (g.graph[n1]->find(n2) == g.graph[n1]->end()) {
				g.edge_num++;
				(*g.graph[n1])[n2] = vector<int>();
			}
            (*g.graph[n1])[n2].push_back(t);
            g.degree[n1] += 1;
		}
        else {
            g.graph[n1] = new unordered_map<int, vector<int>>();
            (*g.graph[n1])[n2] = vector<int>(1, t);
            g.edge_num += 1;
            g.degree[n1] = 1;
		}
	}

	sort(g.record_edges.begin(), g.record_edges.end());
	for (int i = 1; i < g.sum_t_vertex.size(); ++i) {
		sort(g.sum_t_vertex[i].begin(), g.sum_t_vertex[i].end());
	}

    g.t_edge_num /= 2;
    g.edge_num /= 2;
    g.t_gap = tmax - tmin;
	g.nodenum = nmax;
	g.mapper = mapper;
	g.rev_mapper = rev_mapper;

	f.close();
}

void TemporalSearch::refineGraphTimestamps(TemporalGraph& g) {
	cout << g.minstamp << " MIN" << endl;
	int maxdeg = -1;
	int maxpos = -1;
	for (int i = 0; i < g.graph.size(); ++i) {
		if (g.graph[i] != NULL) {
			if ((int)g.graph[i]->size() > maxdeg){
				maxdeg = g.graph[i]->size();
				maxpos = i;
			}
			for (const auto& n2 : *g.graph[i]) {
				for (int j = 0; j < n2.second.size(); ++j) {
					(*g.graph[i])[n2.first][j] -= g.minstamp;
				}

				sort((*g.graph[i])[n2.first].begin(), (*g.graph[i])[n2.first].end());
			}
			
			for (int j = 0; j < g.sum_t_vertex[i].size(); j++) {
				g.sum_t_vertex[i][j] -= g.minstamp;
			}
		}
	}

	for (int i = 0; i < g.record_edges.size(); ++i) {
		g.record_edges[i] -= g.minstamp;
	}
	//cout << g.minstamp << endl;
	//system("pause");

	g.maxstamp -= g.minstamp;
	g.minstamp = 0;

	cout << maxpos << " "<< maxdeg << endl;
}

void TemporalSearch::loadCommunity(TemporalGraph& g, string file_path) {
	fstream f(file_path, ios::in);

	int n, c;
	while(f >> n >> c) {
		if (g.communities.find(c) != g.communities.end()) {
			g.communities[c].push_back(n);
		}
		else {
			g.communities[c] = vector<int>(1, n);
		}
	}

	for (const auto& comm : g.communities) {
		double comm_ex = 0;
		double comm_ex2 = 0;
		double comm_edge = 0;
		int c = comm.first;

		for (int i1 = 0; i1 < comm.second.size(); ++i1) {
			int n1 = comm.second[i1];
			for (int i2 = i1 + 1; i2 < comm.second.size(); ++i2) {
				int n2 = comm.second[i2];
				if (g.graph[n1] != NULL
					&& g.graph[n1]->find(n2) != g.graph[n1]->end()) {
					for (const auto& t : (*g.graph[n1])[n2]) {
						g.comm_Ex[c] += t;
						g.comm_Ex2[c] += t * t;
						g.comm_edge[c]++;
					}
				}
			}
		}
	}
}

void TemporalSearch::printCommunityFile(TemporalGraph& g, string filename) {
	fstream f(filename, ios::out);

	for (const auto& comm : g.communities) {
		for (int i = 0; i < comm.second.size(); ++i) {
			f << comm.second[i] << ' ';
		}
		f << endl;
	}
}

void TemporalSearch::writeRelated(TemporalGraph& g, vector<int>& nodes) {
	unordered_set<int> ns(nodes.begin(), nodes.end());
	fstream output("relnet.txt", ios::out);
	for (const auto& n : nodes) {
		if (g.graph[n] == NULL)
			continue;
		for (const auto& n2 : *g.graph[n]) {
			if (ns.find(n2.first) == ns.end() || n > n2.first)
				continue;
			for (const auto& t : (*g.graph[n])[n2.first]) {
				if ((t - g.minstamp) / 86400 + 1 > 30)
					continue;
				output << n << " " << n2.first << " " << t << endl;
				cout << n << " " << n2.first<< " " << t << endl;
			}
		}
	}
	
	output.close();
	system("pause");
}

void TemporalSearch::detectDiff() {
	ifstream o1("data.log");
	ifstream o2("data_true.log");

	double ts1, ts2;
	while (o1 >> ts1) {
		o2 >> ts2;

		if (ts1 != ts2) {
			cout << ts1 << " " << ts2 << endl;
			system("pause");
		}

	}
}

void TemporalSearch::loadIndex(GraphAnalyzer& ga, TemporalGraph& g, int t_s, int t_e) {
	g.components.clear();
	g.cc_map.clear();
	g.eindex.clear();
	g.cc_network.clear();

	cout << "Start Build Index" << endl;
	ga.connectedComponents(g, t_s, t_e, g.components, g.cc_map);
	
	cout << "Finish Build CC" << endl;

	ifstream efile("index.txt", ios::in);
	for (int index = 0; index < g.components.size(); ++index) {
		cout << index << " " << g.components.size() << endl;
		
		int eindex = -1;
		efile >> eindex;
		int edgenum = -1;
		int src, dst, max_time, min_time, num;
		efile >> edgenum;
		for (int i = 0; i < edgenum; ++i) {
			efile >> src >> dst >> max_time >> min_time >> num;
			g.eindex[eindex].push_back(TemporalEdgeInfo(num, src, dst, max_time, min_time));
		}
		if (eindex != index) {
			cout << eindex << " " << index << endl;
			system("pause");
		}		
		
		for (int i = 0; i < g.eindex[index].size(); ++i) {
			int n1 = g.eindex[index][i].src;
			int n2 = g.eindex[index][i].dst;
			g.cc_network[n1].push_back(i);
			g.cc_network[n2].push_back(i);
		}
	}
	cout << "Finish Build Index" << endl;
}


void TemporalSearch::comboSearching(TemporalGraph& g, string inputfile, string outputfile, int qv, int combonum, int t_s, int duration, int t_e, double phi) {
	cout << fixed;

	unordered_map<int, int> rev_mapper;
	loadGraph(g, inputfile, rev_mapper, true);

	GraphAnalyzer ga;
	/*ga.caseStudy(g, 125679);
	system("pause");
	return 0;*/

	refineGraphTimestamps(g);

	//cout << ga.tseval.computeScore(g, 42259.84) << endl;
	//system("pause");
	//system("pause");
	cout << g.mapper.size() << " " << g.graph.size() << endl;
	//system("pause");
	CommGraphUtil CGU;
	CGU.initCommunity(g);

	//loadCommunity(g, "dataset//email//community.txt");
	cout << "MIN: " << g.minstamp << " " << "MAX: " << g.maxstamp << endl;

	//int t_s = 0;
	//int duration = 86400 * 30;
	g.window_span = duration;

	//int tp = 13;//6741785;//6741785 - 86400 * 27;//6223385 - 23 * 86400;

	int maxedge = -1;

	//string filename = "result/1M/log_" + to_string(tp) + "_" + to_string(g.kcore) + "_" + to_string(g.th_topo_beta) + "_" + to_string(g.th_beta) + "_" + to_string(g.th_ev2) + "_" + to_string(g.th_io_half) + "_" + to_string(g.th_io_beta) + "_" + to_string(phi) + ".txt";
	//string outputfile = "ablation_test/parameter/email30d//log_" + to_string(t_p) + "_" + to_string(g.kcore) + "_" + to_string(g.th_topo_half) + "_" + to_string(g.th_topo_beta) + "_" + to_string(g.th_beta) + "_" + to_string(g.th_ev2) + "_" + to_string(g.th_io_half) + "_" + to_string(g.th_io_beta) + "_" + to_string(phi) + ".txt";
	ga.filename = outputfile;

	ga.buildIndex(g, t_s, t_s + duration);	
	ga.tsearch_dfs(g, qv, phi, combonum, t_s, t_s + duration);
	g.clear();

	system("pause");
}

void TemporalSearch::evolutionTracking(TemporalGraph& g, string inputfile, string outputfile, vector<int>& relnodes, int qv, int combonum, int t_s, int duration, int t_e) {
	unordered_map<int, int> rev_mapper;
	loadGraph(g, inputfile, rev_mapper, true);

	GraphAnalyzer ga;

	refineGraphTimestamps(g);

	//cout << ga.tseval.computeScore(g, 42259.84) << endl;
	//system("pause");
	//system("pause");
	cout << g.mapper.size() << " " << g.graph.size() << endl;
	//system("pause");
	CommGraphUtil CGU;
	CGU.initCommunity(g);

	//loadCommunity(g, "dataset//email//community.txt");
	cout << "MIN: " << g.minstamp << " " << "MAX: " << g.maxstamp << endl;

	//int t_s = 0;
	// int duration = 86400 * 30;
	g.window_span = duration;
	int ner = 0;

	vector<int> cur;
	// vector<int> relnodes;
	/*ifstream input("input.txt", ios::in);
	while (true) {
		int nid;
		input >> nid;
		if (nid == -1)
			break;
		relnodes.push_back(nid);
		//cout << nid << endl;
	}*/

	cout << "REL SIZE: " << relnodes.size() << endl;
	for (int i = 0; i < relnodes.size(); ++i) {
		cur.push_back(g.mapper[relnodes[i]]);
	}
	ga.timeSeries(g, cur, t_s, duration, t_e, outputfile);
	cout << "TSA over" << endl;
	system("pause");
}