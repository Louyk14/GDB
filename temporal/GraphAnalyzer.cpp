#include "GraphAnalyzer.h"

void GraphAnalyzer::computeMetric(TemporalGraph& g, vector<int>& nodes, int t_s, int t_e, double ts) {
	int maxtime = -1;
	int mintime = -1;
	vector<int> coh;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		if (g.graph[n1] != NULL) {
			for(int i2 = i1; i2 < nodes.size(); ++i2) {
				int n2 = nodes[i2];
				if (g.graph[n1]->find(n2) != g.graph[n1]->end()) {
					for (const auto& t : (*g.graph[n1])[n2]) {
						if (t >= t_s && t <= t_e) {
							coh.push_back(t);
							if (t > maxtime || maxtime == -1)
								maxtime = t;
							if (t < mintime || mintime == -1)
								mintime = t;
						}
					}
				}
			}
		}
	}
	g.tspan = g.tspan + (maxtime - mintime);//tseval.computeV(coh);

	int inside = 0;
	int outside = 0;
	unordered_set<int> nset(nodes.begin(), nodes.end());
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		if (g.graph[n1] != NULL) {
			for(const auto& n2p : *g.graph[n1]) {
				int n2 = n2p.first;
				if (g.graph[n1]->find(n2) != g.graph[n1]->end()) {
					for (const auto& t : (*g.graph[n1])[n2]) {
						if (t >= t_s && t <= t_e) {
							if (nset.find(n2) != nset.end()) {
								if (n1 <= n2) {
									inside++;
								}
							}
							else {
								outside++;
							}
						}
					}
				}
			}
		}
	}
	//cout << "IO:  " << inside << " "<< outside << endl;
	g.iorate = g.iorate + (double)inside / (inside + outside);
	
	unordered_map<int, int> corenum;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		
		for (int i2 = i1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
				bool once = false;
				for (const auto& t : (*g.graph[n1])[n2]) {
					if (t >= t_s && t <= t_e) {
						if (!once) {
							once = true;
							corenum[n1]++;
							corenum[n2]++;
						}
					}
					else if (t > t_e)
						break;
				}
			}
		}
	}

	double lose_core = 0;
	for (const auto& deg : corenum) {
		lose_core += min((int)g.kcore, deg.second);
	}
	double lose_rate = lose_core / (double)(g.kcore * nodes.size());

	g.corerate += lose_rate;

	g.avgts += ts;
	g.testnum++;
}

double GraphAnalyzer::analyze(TemporalGraph& g, vector<int>& nodes, int t_s, int t_e) {
	int t_edge_num = 0;
	double ts = 0.0;
	
	vector<int> tstamps;

	double avg_t = 0;
	int edgenum = 0;
	int e_num = 0;

	unordered_map<int, int> degree;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		int lowbound, upbound;
		vector<int>::iterator low = lower_bound(g.sum_t_vertex[n1].begin(), g.sum_t_vertex[n1].end(), t_s);
		if (low == g.sum_t_vertex[n1].end()) {
			lowbound = g.sum_t_vertex[n1].size();
		}
		else {
			lowbound = low - g.sum_t_vertex[n1].begin();
		}
		
		vector<int>::iterator upper = upper_bound(g.sum_t_vertex[n1].begin(), g.sum_t_vertex[n1].end(), t_e);
		if (upper == g.sum_t_vertex[n1].end()) {
			upbound = g.sum_t_vertex[n1].size();
		}
		else {
			upbound = upper - g.sum_t_vertex[n1].begin();
		}
		
		degree[n1] = upbound - lowbound;
		/*cout << upbound << " "<< lowbound << " " << t_s << " "<< t_e << endl;
		for (const auto& t : g.sum_t_vertex[n1]) {
			cout << t << " ";
		}
		cout << endl;
		system("pause");*/
	}

	t_edge_num = upper_bound(g.record_edges.begin(), g.record_edges.end(), t_e) - lower_bound(g.record_edges.begin(), g.record_edges.end(), t_s);
	//cout << t_edge_num << " " << degree[1] << " " << degree[2] << endl;

	int max_topo = -1;
	unordered_map<int, int> corenum;
	int intimes = 0;

	int multi_edge = 0;
	int sz = 0;

	int maxtime = -1;
	int mintime = -1;

	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		e_num += degree[n1];

		for (int i2 = i1 + 1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
				bool once = false;
				sort((*g.graph[n1])[n2].begin(), (*g.graph[n1])[n2].end());
				for (const auto& t : (*g.graph[n1])[n2]) {
					if (t >= t_s && t <= t_e) {
						if (!once) {
							once = true;
							corenum[n1]++;
							corenum[n2]++;
						}
						
						//if (t_s == 2006)
						//	slog << g.rev_mapper[n1] << " " << g.rev_mapper[n2] << t << endl;
						sz++;
						e_num--;
						if (maxtime == -1 || maxtime < t)
							maxtime = t;
						if (mintime == -1 || mintime > t)
							mintime = t;
					}
					else if (t > t_e)
						break;
				}
			}
		}
	}

	int lose_core = 0;
	for (const auto& deg : corenum) {
		lose_core += min((int)g.kcore, deg.second);
	}
	double lose_rate = lose_core / (double)(g.kcore * nodes.size());
	
	double avg_factor = 2 * e_num;//t_edge_num;

	if (e_num == 0) {
		//g.load(-1);
	//	return -2;
	}
	
	
	e_num -= (1 - g.multi_rate) * multi_edge;

	sz = sz - (1 - g.multi_rate) * multi_edge;

	//double zeta = tseval.computeScore(g, g.th_ev2);

	//if (sz == 1)
	//	zeta = 1;
	//zeta = 1;
	
	double zeta_topo = tseval.computeTopoScore(g, lose_rate);
	if (sz == 0)
		zeta_topo = 0;
	//cout << zeta_topo << endl;
	//system("pause");
	//cout << sz << " " << e_num - sz << " " << e_num << endl;
	
	double zeta_io = tseval.computeIOScore(g, (double)sz / e_num);
	if (sz == 0)
		zeta_io = 0;

	double tspan = maxtime - mintime;
	double tmp = tseval.computeScore(g, tspan); //tseval.SVs(g, tstamps);
	double stmp = 0;
	
	//logger << t_s - 1998 << " " << (double)tmp * zeta_io * zeta_topo << " " << tmp << " " << zeta_io << " " << zeta_topo << " " << zeta_io * zeta_topo << endl;
	cout << tspan << " " << (double)sz / e_num << " " << lose_rate << endl;
	//logger << t_s << " " << t_e << " " << tmp << " " << zeta_io << " " << zeta_topo << " " << (double)tmp * zeta_io * zeta_topo << endl;
	//system("pause");
	ts = (double)tmp * zeta_io * zeta_topo;

	return ts;
}

double GraphAnalyzer::analyzeCase(TemporalGraph& g, vector<int>& nodes) {
	int nodenum = nodes.size();
	//unordered_map<int, unordered_map<int, int>> dist;
	//for (const auto& n1 : nodes) {
	//	for (const auto& n2 : nodes) {
	//		dist[n1][n2] = -1;
	//	}
	//}
	//vector<vector<int>> dist(nodenum + 1, vector<int>(nodenum + 1, -1));

	int maxd = -1;
	int count = 0;
	unordered_set<int> nodeset(nodes.begin(), nodes.end());
	
	for (const auto& n : nodes) {
		unordered_map<int, int> dist;
		for (const auto& n2 : nodes) {
			dist[n2] = -1;
		}

		count++;
		if (count % 100 == 0)
			cout << count << "/" << nodes.size() << endl;
		unordered_set<int> Q;
		Q.insert(n);
		dist[n] = 0;
		int d = 1;
		while (!Q.empty()) {
			unordered_set<int> QR;
			for (const auto& n1 : Q) {
				for (const auto& neigh : g.network[n1]) {
					if (nodeset.find(neigh) != nodeset.end() && dist[neigh] == -1) {
						QR.insert(neigh);
						dist[neigh] = d;
						maxd = max(maxd, d);
					}
				}
			}
			Q.clear();
			Q = QR;
			d++;
		}
	}
	
	int diameter = maxd;
	/*for (int i = 0; i < nodes.size(); ++i) {
		for (int j = i + 1; j < nodes.size(); ++j) {
			diameter = max(diameter, dist[nodes[i]][nodes[j]]);
		}
	}*/
	cout << "DIAMETER DIST: " << diameter << endl;

	/*for (int i = 0; i < nodes.size(); ++i) {
		int node1 = nodes[i];
		for (int j = i + 1; j < nodes.size(); ++j) {
			int node2 = nodes[j];

			unordered_set<int> Q;
			Q.insert(node1);
			unordered_map<int, unordered_set<pair<int, int>>> record;
			
			while (!Q.empty()) {
				unordered_set<int> QR;
				for (const auto& n1 : Q) {
					for (const auto& neigh : g.network[n1]) {
						if (nodeset.find(neigh) != nodeset.end()) {
							unordered_set<int> tset((*g.graph[n1])[neigh].begin(), (*g.graph[n1])[neigh].end());
							for (const auto& t : tset) {
								for (const auto& p : record[n1]) {
									int newf = p.first;
									int news = p.second;
									if (newf == -1 || t < newf)
										newf = t;
									if (news == -1 || t > news)
										news = t;
									bool domin = false;
									for (const auto& pneigh : record[neigh]) {
										if (pneigh.first >= newf && pneigh.second <= news) {
											domin = true;
											break;
										}
									}
									if (!domin) {
										vector<pair<int, int>> toerase;
										for (const auto& rq : record[neigh]) {
											if (rq.first <= newf && rq.second >= news)
												toerase.push_back(rq);
										}
										for (const auto& rq : toerase) {
											record[neigh].erase(rq);
										}
										record[neigh].insert(make_pair(newf, news));
									}
								}
							}
						}
					}
				}
				Q.clear();
				Q = QR;
			}
		}
	}*/

	int maxtime = -1;
	int mintime = -1;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		for (int i2 = i1 + 1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
				bool once = false;
				sort((*g.graph[n1])[n2].begin(), (*g.graph[n1])[n2].end());
				for (const auto& t : (*g.graph[n1])[n2]) {				
					if (maxtime == -1 || maxtime < t)
						maxtime = t;
					if (mintime == -1 || mintime > t)
						mintime = t;
				}
			}
		}
	}

	cout << "DIAMETER TIME: " << maxtime - mintime << endl;

	int validedge = 0;
	int alledge = 0;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		for (const auto& n2 : g.network[n1]) {
			if (nodeset.find(n2) == nodeset.end()) {
				for (const auto& t : (*g.graph[n1])[n2]) {				
					if (t <= maxtime && t >= mintime) {
						validedge++;
					}
					alledge++;
				}
			}
		}
	}

	cout << "VALID EDGE: " << validedge << endl;

	cout << "ALL EDGE: " << alledge << endl;

	unordered_map<int, int> deg;
	for (const auto& n : nodes) {
		int degree = 0;
		for (const auto& neigh : g.network[n]) {
			if (nodeset.find(neigh) != nodeset.end())
				degree++;
		}
		deg[n] = degree;
	}

	int mindeg = -1;
	for (const auto& n : nodes) {
		if (mindeg == -1 || mindeg > deg[n])
			mindeg = deg[n];
	}
	cout << "MIN DEG: " << mindeg << endl;

	int degsum = 0;
	for (const auto& n : nodes) {
		degsum += deg[n];
	}
	cout << "AVG DEG: " << (double) degsum / (double) nodes.size() << endl;

	cout << "NODE NUM: " << nodes.size() << endl;

	int edgenum = 0;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		for (int i2 = i1 + 1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
				edgenum += (*g.graph[n1])[n2].size();
			}
		}
	}
	cout << "EDGE NUM: " << edgenum << endl;

	cout << "DENSITY: " << edgenum / (double) nodes.size() << endl;

	return 0;
}

void GraphAnalyzer::timeSeries(TemporalGraph& g, vector<int> nodes, int starttime, int dur, int endtime, string outputfile) {
	int t_s = starttime;
	int t_e = t_s + dur;
	fstream out(outputfile, ios::out);
	//cout << g.maxstamp << endl;
	int counter = 1;
	//cout << t_s << endl;
	bool start = false;
	//slog.open("series_log.log", ios::app);
	while (t_s <= endtime) {
		double ts = analyze(g, nodes, t_s, t_e);
		// analyzeCase(g, nodes);
		//computeMetric(g, nodes, t_s, t_e, ts);
		//if (ts != -2)
		//	start = true;
		//if (start)
		//	out << "[" << t_s << ", "<< t_e << "] " << ts << endl;
		//cout << t_s << " " << t_e << " " << ts << endl;
		//break;
		out << ts << " " << counter << endl;
		//t_s = t_e;
		t_s = t_s + 1;
		//t_s++;
		t_e = t_s + dur;
		counter++;
		
		g.tspan = 0;
		g.iorate = 0;
		g.corerate = 0;
		//if(counter >= 31)
		//	break;
	}
	slog.close();
}

bool GraphAnalyzer::isValidExtension(TemporalGraph& g, int qv, vector<int>& nodes, int v, vector<int>& distance) {
	int x = nodes[(int)nodes.size() - 2];
	if (distance[v] > distance[x])
		return true;
	return distance[v] == distance[x] && v > x;
}

void GraphAnalyzer::enumerateCIS(TemporalGraph& g, int qv, vector<int>& nodes, vector<int>& distance, unordered_set<int>& neighs, unordered_map<int, int>& degree,
								 double phi, double max_span, int t_s, int t_e, int& ansnum, int num, bool& enough) {
	for (const auto& n : neighs) {
		nodes.push_back(n);

		if (isValidExtension(g, qv, nodes, n, distance)) {	
			initNodes_dfs(g, n, degree, t_s, t_e);
			double zeta_tmp = 0;
			int in_enum = 0;
			int in_sz = 0;
			int in_core = 0;
			int maxt = -1;
			int mint = -1;
			double ts = analyzeIndex_enum(g, nodes, degree, t_s, t_e, zeta_tmp, in_sz, in_enum, in_core, maxt, mint);
			
			if (ts > 0.4) {
				cout << ts << " (" << ansnum << ") |     ";
				for (const auto& n : nodes) {
					cout << n << " ";
				}
				cout << endl;
			}
			//if (ts > 0.3)
			//	system("pause");

			if (ts >= phi) {
				computeMetric(g, nodes, t_s, t_e, ts);
				ansnum++;
					
				cout << ts << " " << ansnum << "/" << num << endl;
			
				//cout << ts << endl;
				//ans.push_back(cur);
				for (const auto& n : nodes) {
					cout << n << " ";
				}
				cout << endl;
					
				if (ansnum >= num) {
					//logger << g.rev_mapper[qv] << ',';
					enough = true;
					return;
				}
			}

			unordered_set<int> invalid_nodes;
			int sum_deg_max = 0;
			int invalid_edge = 0;
			
			for (const auto& node : nodes) {
				int valid_deg = 0;
				if (!g.temporal_graph[node].empty()) {
					for (const auto& n2 : g.temporal_graph[node]) {
						if (invalid_nodes.find(n2.first) != invalid_nodes.end())
							continue;

						bool valid = true;
						bool can = false;
						for (const auto& t : n2.second) {
							if (t >= t_s && t <= t_e) {
								can = true;
								if ((t < mint && maxt - t > max_span) || (t > maxt && t - mint > max_span)) {
									valid = false;
									break;
								}
							}
							else if (t > t_e)
								break;
						}
						if (!valid) {
							invalid_nodes.insert(n2.first);
						}
					}
				}
			}

			int ec = 0;
			int ccindex = g.cc_map[nodes[0]];

			double max_score = zeta_tmp;// * tseval.computeTopoScore(g, sum_deg_max / (g.kcore * (double)(p->nodes.size() + 1)));

			unordered_set<int> cc;
			int maxnode = 0;
			ec = getComponentEst(g, t_s, t_e, nodes, maxt, mint, max_span, invalid_nodes, cc, maxnode);

			//double zeta_io = tseval.computeIOScore(g, (double)ec / (ec + invalid_edge));
			//cout << ec << " " << ecs << " " << invalid_edge << " " << zeta_io << " " << cc.size() << " " << g.components[ccindex].size() << endl;
			//system("pause");
			double zeta_topo = getMaxTopo(g, t_s, t_e, nodes, maxt, mint, max_span, cc, invalid_nodes, in_core);

			//double zeta_topo = tseval.computeTopoScore(g, sum_deg_max / (g.kcore * (double)maxnode));
			
			invalid_edge = 0;
			for (const auto& niv : invalid_nodes) {
				for (const auto& node : nodes) {
					if (!g.temporal_graph[niv].empty() && g.temporal_graph[niv].find(node) != g.temporal_graph[niv].end()) {
						invalid_edge += g.temporal_graph[niv][node].size();
					}
				}
			}

			double zeta_io = getMaxIO(g, t_s, t_e, nodes, maxt, mint, max_span, cc, invalid_nodes, in_sz, in_enum, invalid_edge);
			max_score = max_score * zeta_io * zeta_topo;
			//cout << max_score << " " << zeta_tmp << " " << zeta_io << " " << zeta_topo << endl;
			//system("pause");

			if (max_score >= phi) {
				unordered_set<int> tmp(neighs);
				//vector<int> new_neighs;
				unordered_map<int, int> dist_rec;
			
				for (const auto& np : g.temporal_network[n]) {
					if (neighs.find(np) == neighs.end() && invalid_nodes.find(np) == invalid_nodes.end()) {
						tmp.insert(np);
						//new_neighs.push_back(np);
					}

					dist_rec[np] = distance[np];
					if (distance[np] == -1)
						distance[np] = distance[n] + 1;
					else
						distance[np] = min(distance[np], distance[n] + 1);
				}

				tmp.erase(n);
				
				enumerateCIS(g, qv, nodes, distance, tmp, degree, phi, max_span, t_s, t_e, ansnum, num, enough);

				if (enough)
					return;

				for (const auto& distp : dist_rec) {
					distance[distp.first] = distp.second;
				}
			}
			else {
				//cout << "cut" << endl;
			}
		}
		nodes.pop_back();
	}
}


void GraphAnalyzer::tsearch_enum(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e) {
	g.temporal_graph = vector<unordered_map<int, vector<int>>>(g.graph.size());
	g.temporal_network.clear();

	for (const auto& n1 : g.network) {
		for (const auto& n2 : g.network[n1.first]) {
			if (n1.first < n2) {
				for (const auto& t : (*g.graph[n1.first])[n2]) {
					if (t >= t_s && t <= t_e) {
						g.temporal_network[n1.first].insert(n2);
						g.temporal_network[n2].insert(n1.first);
						break;
					}
					else if (t > t_e)
						break;
				}
			}
		}
	}

	for (const auto& n1 : g.temporal_network) {
		for (const auto& n2 : g.temporal_network[n1.first]) {
			for (const auto& t : (*g.graph[n1.first])[n2]){
				if (t >= t_s && t <= t_e) {
					g.temporal_graph[n1.first][n2].push_back(t);
				}
				else if (t > t_e)
					break;
			}
		}
	}

	vector<int> distance(g.graph.size(), -1);
	distance[qv] = 0;
	vector<int> nodes(1, qv);
	unordered_set<int> neighs(g.temporal_network[qv].begin(), g.temporal_network[qv].end());
	
	for (const auto& n : neighs) {
		distance[n] = 1;
	}

	double max_span = 0;
	double min_io = 0;
	if (phi == 1) {
		max_span = g.th_beta;
		min_io = g.th_io_beta;
	}
	else {
		max_span = (double)(exp(1.0 / phi - 1) - 1.0) / g.th_alpha + g.th_beta;
		min_io = g.th_io_beta - (double)(exp(1.0 / phi - 1) - 1.0) / g.th_io_alpha;
	}
	cout << max_span << endl;
	//system("pause");
	unordered_set<string> recstr;
	unordered_map<int, int> degree;
	int ansnum = 0;
	bool enough = false;

	initNodes_dfs(g, nodes[0], degree, t_s, t_e);
	unordered_set<int> invalid_nodes;
	
	enumerateCIS(g, qv, nodes, distance, neighs, degree, phi, max_span, t_s, t_e, ansnum, num, enough);
}


void GraphAnalyzer::dfs(TemporalGraph& g, double phi, priority_queue<DNode*, vector<DNode*>, tscmp>& Q, int num, int t_s, int t_e, unordered_map<int, int>& degree, vector<int>& window_edges) {
	double max_span = 0;
	double min_io = 0;
	if (phi == 1) {
		max_span = g.th_beta;
		min_io = g.th_io_beta;
	}
	else {
		max_span = min((double)g.window_span, (double)(exp(1.0 / phi - 1) - 1.0) / g.th_alpha + g.th_beta);
		min_io = max(0.0, g.th_io_beta - (double)(exp(1.0 / phi - 1) - 1.0) / g.th_io_alpha);

		// (t + io + topo) / 3
		//max_span = min((double)g.window_span, (double)(exp(1.0 / (max(0.0, 3 * phi - 2)) - 1) - 1.0) / g.th_alpha + g.th_beta);
		//min_io = max(0.0, g.th_io_beta - (double)(exp(1.0 / (max(0.0, 3 * phi - 2)) - 1) - 1.0) / g.th_io_alpha);

		//trivial
		//max_span = 1 / phi - 1;
		//min_io = phi;

		//t1only
		//max_span = (double) 1.0 / phi - 1 + g.th_beta;
		//min_io = phi * g.th_io_beta;

		//both
		//max_span = g.th_ev2;
		//min_io = g.th_io_half;
	}
	//max_span = 86400 * 7;
	cout << max_span << " " << min_io << endl;
	//system("pause");
	unordered_set<string> recstr;
	//unordered_map<int, int> degree;
	int ansnum = 0;
	bool enough = false;

	int qv = Q.top()->nodes[0];
	initNodes_dfs(g, Q.top()->nodes[0], degree, t_s, t_e);

	unordered_set<string> number; 
	clock_t start = clock();
	int counter = 0;
	int samecount = 0;
	int qnum = 0;
	int cutsize = 0;
	while(!Q.empty() && !enough) {
		counter++;
		if ((double)(clock() - start) / CLOCKS_PER_SEC >= 1800)// && ansnum == 0)
			break;
		//if (counter % 1 == 0) {
			//cout << counter << "/" << endl;
			//clock_t end = clock();
			//cout << "TIME: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
			//cout << g.handlenum << endl;
			//start = clock();
		//}
		//if (counter == 1000001 && ansnum == 0)
		//	break;
		//if (counter == 101) {
		//	g.posnum = 1;
		//	break;
		//}
		DNode* p = Q.top();
		Q.pop();
		
		/*if (p->save == -1){
			cout << cutsize << endl;
			cutsize++;
			system("pause");
		}*/
		//qnum++;
		//for (const auto& n : p->nodes) {
		//	logger << n << " ";
		//}
		//logger << endl;

		unordered_map<int, pair<int, int>> neigh_info;
		//unordered_set<int> neighs;
		vector<int> neighs;
		unordered_set<int> visited(p->nodes.begin(), p->nodes.end());
		unordered_set<int> noneigh;
		unordered_map<int, int> distindex;
		unordered_map<int, int> distmap;

		for (const auto& n : p->nodes) {
			for (const auto& n2 : g.temporal_network[n]) {
				if (visited.find(n2) != visited.end()) 
					continue;
				
				visited.insert(n2);

				/*int x = p->nodes[(int)p->nodes.size() - 1];
				int distn2 = g.distance[n2];
				if (distmap.find(distn2) == distmap.end()) {
					distmap[n2] = distindex[distn2];
					distindex[distn2]++;
				}
				if (g.distance[n2] > g.distance[x] || (g.distance[n2] == g.distance[x] && distmap[n2] > distmap[x])) {
				
				}
				else {
					continue;
				}*/

				bool can = false;
				bool timecan = true;
				int maxt = p->max_time;
				int mint = p->min_time;

				for (const auto& np : p->nodes) {
					if (g.temporal_graph[np].find(n2) != g.temporal_graph[np].end() && !g.temporal_graph[np][n2].empty()) {
						int mit = g.temporal_graph[np][n2][0];
						int mat = g.temporal_graph[np][n2][(int)g.temporal_graph[np][n2].size() - 1];
						
						can = true;

						if (maxt == -1 || mat > maxt) {
							maxt = mat;
						}
						if (mint == -1 || mit < mint) {
							mint = mit;
						}

						if (maxt - mint > max_span) {
							timecan = false;
							break;
						}
					}
				}
				if (can && timecan) {
					neighs.push_back(n2);
					neigh_info[n2] = make_pair(maxt, mint);
				}
				else if(can && !timecan) {
					noneigh.insert(n2);
				}
			}
		}

		//cout << neighs.size() << endl;
		for (const auto& n : neighs) {
			//if (p->nodes.size() == 1 && (n == 63 || n == 51 || n == 70))
			//	continue;
			//if (n == g.mapper[999530])
			//	continue;
			p->nodes.push_back(n);
		
			vector<int> st(p->nodes);
			sort(st.begin(), st.end());
			string sig = "";
			
			for (const auto& n : st) {
				sig += to_string(n) + " ";
			}
			
			if (recstr.find(sig) != recstr.end()) {
				p->nodes.pop_back();
				//cout << "ERROR" << endl;
				continue;
			}
			else {
				recstr.insert(sig);
			}

			/*if (p->kball)
				g.negall++;
			if (p->kbnt)
				g.negt++;
			if (p->kbnio)
				g.negio++;
			if (p->kbntopo)
				g.negtopo++;*/

			unordered_map<int, int> ncore(p->ncore);
			int last_sz = p->last_sz;
			int last_enum = p->last_enum;

			initNodes_dfs(g, n, degree, t_s, t_e);
			double zeta_tmp = 0;
			int in_enum = 0;
			int in_sz = 0;
			int in_core = 0;

			/*int test_sz = 0;
			int test_enum = 0;
			int test_core = 0;
						
			cout << test_enum << " "<< test_sz << " " << test_core << " " << ts1 << endl;
			cout << in_enum << " " << in_sz << " " << in_core << " " << ts << endl;
			system("pause");*/
			
			g.handlenum++;

			g.refine = false;
			//double ts1 = analyzeIndex_dfs(g, p->nodes, degree, t_s, t_e, neigh_info[n].first - neigh_info[n].second, zeta_tmp, in_sz, in_enum, in_core);
			double ts = analyzeIndex_dfs_load(g, p->nodes, degree, t_s, t_e, neigh_info[n].first - neigh_info[n].second, zeta_tmp, in_sz, in_enum, in_core, ncore, last_sz, last_enum);
			
			/*if (ts >= 0.6) {
				cout << ts << " (" << ansnum << ") |     ";
				for (const auto& n : p->nodes) {
					cout << n << " ";
				}
				cout << endl;
				//system("pause");
			}*/
			//if (ts > 0.3)
			//	system("pause");

			if (ts >= phi && !g.refine) {
				computeMetric(g, p->nodes, t_s, t_e, ts);
				ansnum++;
				
				cout << ts << " " << ansnum << "/" << num << endl;

				cout << ts << endl;
				//ans.push_back(cur);
				for (const auto& n : p->nodes) {
					cout << n << " ";
				}
				cout << endl;
					
				if (ansnum >= num) {
					//logger << g.rev_mapper[qv] << ',';
					enough = true;
					break;
				}
			}

			unordered_set<int> invalid_nodes(noneigh);
			int sum_deg_max = 0;
			int invalid_edge = 0;
			int maxt = neigh_info[n].first;
			int mint = neigh_info[n].second;

			int min_change = -1;
			
			unordered_set<int> new_visited(p->nodes.begin(), p->nodes.end());
			for (const auto& n : p->nodes) {
				for (const auto& n2 : g.temporal_network[n]) {
					if (new_visited.find(n2) != new_visited.end() || invalid_nodes.find(n2) != invalid_nodes.end()) 
						continue;
				
					new_visited.insert(n2);

					bool can = false;
					bool timecan = true;
					int newmaxt = maxt;
					int newmint = mint;

					for (const auto& np : p->nodes) {
						if (g.temporal_graph[np].find(n2) != g.temporal_graph[np].end() && !g.temporal_graph[np][n2].empty()) {
							int mit = g.temporal_graph[np][n2][0];
							int mat = g.temporal_graph[np][n2][(int)g.temporal_graph[np][n2].size() - 1];
				
							can = true;

							if (newmaxt == -1 || mat > newmaxt) {
								newmaxt = mat;
							}
							if (mint == -1 || newmint == -1)
								cout << "ERROR" << endl;
							if (newmint == -1 || mit < newmint) {
								newmint = mit;
							}

							if (newmaxt - newmint > max_span) {
								timecan = false;
								break;
							}
						}
					}
					if (can && !timecan) {
						invalid_nodes.insert(n2);
					}
					else {
						if (min_change == -1 || min_change > newmaxt - newmint) {
							min_change = newmaxt - newmint;
						}
					}
				}
			}
			
			invalid_edge = 0;
			for (const auto& niv : invalid_nodes) {
				for (const auto& node : p->nodes) {
					if (!g.temporal_graph[niv].empty() && g.temporal_graph[niv].find(node) != g.temporal_graph[niv].end()) {
						invalid_edge += g.temporal_graph[niv][node].size();
					}
				}
			}

			int ec = 0;
			int ccindex = g.cc_map[p->nodes[0]];

			double max_score = zeta_tmp;// * tseval.computeTopoScore(g, sum_deg_max / (g.kcore * (double)(p->nodes.size() + 1)));
			//cout << "Start Estimating" << endl;
			unordered_set<int> cc;
			int maxnode = 0;
			ec = getComponentEst(g, t_s, t_e, p->nodes, maxt, mint, max_span, invalid_nodes, cc, maxnode);
			//cout << "Get Component" << endl;
			int ecs = 0;
			/*for (int ei = 0; ei < g.eindex[ccindex].size(); ++ei) {
				EdgeInfo* e = &g.eindex[ccindex][ei];
				if (e->max_time - mint > max_span)
					break;
				if (max(e->max_time, maxt) - min(e->min_time, mint) > max_span)
					continue;
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end())
					continue;
				ecs += e->num;
			}*/
			//cout << sum_deg_max << " " << g.components[ccindex].size() << " " << possible_n.size() << endl;
			//system("pause");
			//int ec = getEdgeNumInWindow(g, window_edges, maxt - max_span, mint + max_span);
			/*for (const auto& n1 : g.network) {
				for (const auto& n2 : g.network[n1.first]) {
					if (n1.first < n2) {
						bool valid = true;
						int ecount = 0;
						for (const auto& t : (*g.graph[n1.first])[n2]) {
							if (t >= t_s && t <= t_e) {
								ecount++;
								if ((t < mint && maxt - t > max_span) || (t > maxt && t - mint > max_span)) {
									valid = false;
									break;
								}
							}
							else if (t > t_e)
								break;
						}
						if (valid) {
							ec += ecount;
						}
					}
				}
			}*/

			//double zeta_io = tseval.computeIOScore(g, (double)ec / (ec + invalid_edge));
			//cout << ec << " " << ecs << " " << invalid_edge << " " << zeta_io << " " << cc.size() << " " << g.components[ccindex].size() << endl;
			//system("pause");
			
			//double zeta_topo = getMaxTopo(g, t_s, t_e, p->nodes, maxt, mint, max_span, cc, invalid_nodes, in_core);
			//cout << "Get TOPO" << endl;
			//double zeta_topo = tseval.computeTopoScore(g, sum_deg_max / (g.kcore * (double)maxnode));
			
			//double zeta_io = getMaxIO(g, t_s, t_e, p->nodes, maxt, mint, max_span, cc, invalid_nodes, in_sz, in_enum, invalid_edge);
			//cout << "Get IO" << endl;

			double zeta_topo, zeta_io;
			getMaxTT_new(g, t_s, t_e, p->nodes, maxt, mint, max_span, cc, invalid_nodes, in_sz, in_enum, invalid_edge, in_core, zeta_io, zeta_topo);
			
			max_score = zeta_tmp * zeta_io * zeta_topo;
			//max_score = (double)(zeta_tmp + zeta_io + zeta_topo) / 3.0;
			//cout << max_score << endl;
			//cout << "End Estimating" << endl;
			//cout << max_score << " " << zeta_tmp << " " << zeta_io << " " << zeta_topo << " " << Q.size() << endl;
			//system("pause");
			
			if (max_score >= phi) {
				int rnum = 0;
				/*unordered_map<int, int> pneighs;
				for (const auto& np : p->nodes) {
					if (g.graph[np] != NULL) {
						for (const auto& n2 : (*g.graph[np])) {
							for (const auto& t : n2.second) {
								if (t >= t_s && t <= t_e) {
									pneighs[n2.first]++;
									//break;
								}
								else if (t > t_e)
									break;
							}
						}
					}
				}

				int maxcount = 0;
				int maxn = -1;
				for(const auto& pn : pneighs) {
					if (pn.second > maxcount)
						maxn = pn.first;
					maxcount = max(pn.second, maxcount);
				}
				initNodes_dfs(g, maxn, degree, t_s, t_e);*/
				//double expect_zeta = zeta_tmp * tseval.computeIOScore(g, (double)(maxcount + in_sz) / (in_enum + degree[maxn] - maxcount));
				DNode* dnode = new DNode(ts, p->nodes, neigh_info[n].first, neigh_info[n].second);
				dnode->ncore = ncore;
				dnode->last_enum = last_enum;
				dnode->last_sz = last_sz;
				
				if (max_score < phi)
					dnode->save = -1;
				else
					dnode->save = 1;

				/*vector<int> st(p->nodes);
				sort(st.begin(), st.end());
				string sig = "";
			
				for (const auto& n : st) {
					sig += to_string(n) + " ";
				}
				
				if (number.find(sig) == number.end()) {
					number.insert(sig);*/
					if (zeta_io * zeta_topo < phi || p->kbnt) {					
						g.negt++;
						dnode->kbnt = true;
					}
					if (zeta_tmp * zeta_topo < phi || p->kbnio) {
						g.negio++;
						dnode->kbnio = true;
					}
					if (zeta_tmp * zeta_io < phi || p->kbntopo) {
						g.negtopo++;
						dnode->kbntopo = true;
					}
					if (zeta_tmp * zeta_io * zeta_topo < phi || p->kball) {
						g.negall++;
						dnode->kball = true;
					}

					//Q.push(dnode);
					//g.positivenum++;
				//}

				Q.push(dnode);
				g.positivenum++;
				
				/*if (zeta_io * zeta_topo < phi) {
					g.negt++;
				}
				if (zeta_tmp * zeta_topo < phi) {
					g.negio++;
				}
				if (zeta_tmp * zeta_io < phi) {
					g.negtopo++;
				}
				if (zeta_tmp * zeta_io * zeta_topo < phi) {
					g.negall++;
				}
				if (zeta_tmp < phi) {
					g.post++;
				}
				if (zeta_io < phi) {
					g.posio++;
				}
				if (zeta_topo < phi) {
					g.postopo++;
				}*/
			}
			else{
				//cutsize++;
				//cout << "cut" << endl;
				//cout << zeta_tmp << " " << sum_deg_max << " " << (double)ec / (ec + invalid_edge) << " " << zeta_io << " " << max_score << endl;
				//system("pause");s
				g.negtivenum++;
			}

			p->nodes.pop_back();
		}

		delete p;
	}
	cout << qv << " QNUM: " << qnum << " " << cutsize << " " << Q.size() << endl;
}

int GraphAnalyzer::getEdgeNumInWindow(TemporalGraph& g, vector<int>& window_edges, int t_s, int t_e) {
	int lowbound, upbound;

	vector<int>::iterator low = lower_bound(window_edges.begin(), window_edges.end(), t_s);
	if (low == window_edges.end()) {
		lowbound = window_edges.size();
	}
	else {
		lowbound = low - window_edges.begin();
	}
		
	vector<int>::iterator upper = upper_bound(window_edges.begin(), window_edges.end(), t_e);
	if (upper == window_edges.end()) {
		upbound = window_edges.size();
	}
	else {
		upbound = upper - window_edges.begin();
	}

	return upbound - lowbound;
}

void GraphAnalyzer::initNodes_dfs(TemporalGraph& g, int n, unordered_map<int, int>& degree, int t_s, int t_e) {
	if (degree.find(n) != degree.end())
		return;
	int lowbound, upbound;

	vector<int>::iterator low = lower_bound(g.sum_t_vertex[n].begin(), g.sum_t_vertex[n].end(), t_s);
	if (low == g.sum_t_vertex[n].end()) {
		lowbound = g.sum_t_vertex[n].size();
	}
	else {
		lowbound = low - g.sum_t_vertex[n].begin();
	}
		
	vector<int>::iterator upper = upper_bound(g.sum_t_vertex[n].begin(), g.sum_t_vertex[n].end(), t_e);
	if (upper == g.sum_t_vertex[n].end()) {
		upbound = g.sum_t_vertex[n].size();
	}
	else {
		upbound = upper - g.sum_t_vertex[n].begin();
	}
		
	degree[n] = upbound - lowbound;
}

double GraphAnalyzer::analyzeIndex_enum(TemporalGraph& g, vector<int>& nodes, unordered_map<int, int>& degree, int t_s, int t_e, double& zeta_tmp, int& in_sz, int& in_enum, int& in_core, int& maxt, int& mint) {
	int new_node = nodes[(int)nodes.size() - 1];
	double ts = 0.0;
	
	//vector<Edge> tstamps;

	double avg_t = 0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;
	int e_num = 0;
	int inside_edge = 0;
	//int edgnum = t_edge_num;

	//vector<int> tstamps;

	int max_topo = -1;
	unordered_map<int, int> corenum;
	int intimes = 0;

	int multi_edge = 0;
	int sz = 0;

	int max_time = -1;
	int min_time = -1;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		e_num += degree[n1];

		for (int i2 = i1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.temporal_graph[n1].find(n2) != g.temporal_graph[n1].end()) {
				bool once = false;
				for (const auto& t : g.temporal_graph[n1][n2]) {
					if (t >= t_s && t <= t_e) {
						sz++;
						//t_edge_num++;
						//tstamps.push_back(t);
						//g.addT_actual(-1, t);
						if (max_time == -1 || t > max_time)
							max_time = t;
						if (min_time == -1 || t < min_time)
							min_time = t;

						if (!once) {
							once = true;
							corenum[n1]++;
							corenum[n2]++;
							intimes++;
						}
						else {
							multi_edge++;
						}
						// degree[n1]++;
						// degree[n2]++;

						if (n1 != n2)
							e_num--;
					}
				}
			}
		}
	}

	int tspan = max_time - min_time;
	maxt = max_time;
	mint = min_time;

	int lose_core = 0;
	for (const auto& deg : corenum) {
		if (max_topo == -1)
			max_topo = deg.second;
		else
			max_topo = min(deg.second, max_topo);
		lose_core += max(0.0, g.kcore - deg.second);
	}
	double lose_rate = lose_core / (double)(g.kcore * nodes.size());
	in_core = lose_core;

	double avg_factor = 2 * e_num;//t_edge_num;

	if (e_num == 0 || sz == 0) {
		g.load(-1);
		return -2;
	}

	e_num -= (1 - g.multi_rate) * multi_edge;

	sz = sz - (1 - g.multi_rate) * multi_edge;

	double zeta = tseval.computeScore(g, g.th_ev2);

	if (sz == 1)
		zeta = 1;
	//zeta = 1;
	
	double zeta_topo = tseval.computeTopoScore(g, lose_rate);
	//cout << zeta_topo << endl;
	//system("pause");
	//cout << sz << " " << e_num - sz << " " << e_num << endl;
	
	double zeta_io = tseval.computeIOScore(g, (double)sz / e_num);
	in_enum = e_num;
	in_sz = sz;

	//double edgesum = e_num;
	//double res = (double)sz / e_num - pow((double)e_num / edgesum, 2.0);

	double tmp = tseval.computeScore(g, tspan); //tseval.SVs(g, tstamps);
	double stmp = 0;
	
	//cout << tmp << " " << zeta_topo << " " << zeta_io << endl;
	ts = (double)tmp * zeta_io * zeta_topo;
	zeta_tmp = tmp;
	//cout << ts << endl;
	//ts = tmp * zeta_topo * zeta_io;
	//g.sRecorder[1 - g.scode][signature] = stmp / (double)sz;

	//cout << ts << " " << zeta << " " << sz << " " << e_num << " " << expect_edge_num << endl;
	/*if (zeta != 1)
		ts = ts / (2.0 * (1 - zeta) * ((double)e_num - expect_edge_num));
	else
		ts = ts / (2 * e_num);*/
	//cout << ts << " " << avg_factor << endl;
	//ts = ts / avg_factor;
	//ts = ts / (2 * stmp);//avg_factor;
	// ts = ts / (double)avg_factor;
	return ts;
}



double GraphAnalyzer::analyzeIndex_dfs(TemporalGraph& g, vector<int>& nodes, unordered_map<int, int>& degree, int t_s, int t_e, int tspan, double& zeta_tmp, int& in_sz, int& in_enum, int& in_core) {
	int new_node = nodes[(int)nodes.size() - 1];
	double ts = 0.0;
	
	//vector<Edge> tstamps;

	double avg_t = 0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;
	int e_num = 0;
	int inside_edge = 0;
	//int edgnum = t_edge_num;

	//vector<int> tstamps;

	int max_topo = -1;
	unordered_map<int, int> corenum;
	int intimes = 0;

	int multi_edge = 0;
	int sz = 0;

	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		e_num += degree[n1];

		for (int i2 = i1 + 1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.temporal_graph[n1].find(n2) != g.temporal_graph[n1].end()) {
				bool once = false;
				sz += g.temporal_graph[n1][n2].size();
				e_num -= g.temporal_graph[n1][n2].size();
				if (!g.temporal_graph[n1][n2].empty()) {
					corenum[n1]++;
					corenum[n2]++;
				}
			}
		}
	}

	int lose_core = 0;
	for (const auto& deg : corenum) {
		/*if (max_topo == -1)
			max_topo = deg.second;
		else
			max_topo = min(deg.second, max_topo);*/
		lose_core += max(0.0, g.kcore - deg.second);
	}
	double lose_rate = lose_core / (double)(g.kcore * nodes.size());
	in_core = lose_core;

	double avg_factor = 2 * e_num;//t_edge_num;

	if (e_num == 0 || sz == 0) {
		//g.load(-1);
		return -2;
	}

	e_num -= (1 - g.multi_rate) * multi_edge;

	sz = sz - (1 - g.multi_rate) * multi_edge;

	//double zeta = tseval.computeScore(g, g.th_ev2);

	//if (sz == 1)
	//	zeta = 1;a
	//zeta = 1;
	
	double zeta_topo = tseval.computeTopoScore(g, lose_rate);
	//cout << zeta_topo << endl;
	//system("pause");
	//cout << sz << " " << e_num - sz << " " << e_num << endl;
	
	double zeta_io = tseval.computeIOScore(g, (double)sz / e_num);
	in_enum = e_num;
	in_sz = sz;

	//double edgesum = e_num;
	//double res = (double)sz / e_num - pow((double)e_num / edgesum, 2.0);

	double tmp = tseval.computeScore(g, tspan); //tseval.SVs(g, tstamps);
	double stmp = 0;
	
	//cout << tspan << " " << lose_core << " " << nodes.size() << " " << sz << " " << e_num << endl;
	ts = (double)tmp * zeta_io * zeta_topo;
	//cout << "ACTUAL: " << " " << ts << " " << tmp << " " << zeta_topo << " " << zeta_io << endl;
	//system("pause");
	zeta_tmp = tmp;
	//cout << ts << endl;
	//ts = tmp * zeta_topo * zeta_io;
	//g.sRecorder[1 - g.scode][signature] = stmp / (double)sz;

	//cout << ts << " " << zeta << " " << sz << " " << e_num << " " << expect_edge_num << endl;
	/*if (zeta != 1)
		ts = ts / (2.0 * (1 - zeta) * ((double)e_num - expect_edge_num));
	else
		ts = ts / (2 * e_num);*/
	//cout << ts << " " << avg_factor << endl;
	//ts = ts / avg_factor;
	//ts = ts / (2 * stmp);//avg_factor;
	// ts = ts / (double)avg_factor;
	return ts;
}


void GraphAnalyzer::tsearch_dfs(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e) {
	vector<int> window_edges;
	g.temporal_graph = vector<unordered_map<int, vector<int>>>(g.graph.size());
	g.temporal_network.clear();
	cout << "start: " << t_s << " " << t_e << endl;
	int tedge = 0;
	int nedge = 0;
	for (const auto& n1 : g.network) {
		for (const auto& n2 : g.network[n1.first]) {
			if (n1.first < n2) {
				for (const auto& t : (*g.graph[n1.first])[n2]) {
					if (t >= t_s && t <= t_e) {
						g.temporal_network[n1.first].insert(n2);
						g.temporal_network[n2].insert(n1.first);
						break;
					}
					else if (t > t_e)
						break;
				}
				if (g.temporal_network[n1.first].find(n2) != g.temporal_network[n1.first].end())
					nedge++;
			}
		}
	}

	for (const auto& n1 : g.temporal_network) {
		for (const auto& n2 : g.temporal_network[n1.first]) {
			for (const auto& t : (*g.graph[n1.first])[n2]){
				if (t >= t_s && t <= t_e) {
					g.temporal_graph[n1.first][n2].push_back(t);
					tedge++;
				}
				else if (t > t_e)
					break;
			}
		}
	}
	cout << "EDGE: " << nedge << " " << tedge << " " << g.nodenum << endl;
	//system("pause");c
	for (auto& n1 : g.temporal_graph) {
		for (auto& n2 : n1) {
			sort(n2.second.begin(), n2.second.end());
		}
	}

	//buildIndex(g, t_s, t_e);

	unordered_set<int> QR;
	QR.insert(qv);
	int hop = 1;
	g.distance = vector<int>(g.graph.size(), -1);
	g.distance[qv] = 0;
	unordered_set<int> rec;
	rec.insert(qv);

	while (!QR.empty()) {
		unordered_set<int> tmp;
		for (const auto& node : QR) {
			if (!g.temporal_graph[node].empty()) {
				for (const auto& n2 : g.temporal_graph[node]) {
					if (!g.temporal_graph[node][n2.first].empty() && rec.find(n2.first) == rec.end()) {
						g.distance[n2.first] = hop;
						rec.insert(n2.first);
						tmp.insert(n2.first);
					}
				}	
			}
		}
		QR = tmp;
		hop++;
	}

	sort(window_edges.begin(), window_edges.end());

	priority_queue<DNode*, vector<DNode*>, tscmp> Q;

	unordered_map<int, int> degree;
	initNodes_dfs(g, qv, degree, t_s, t_e);
	DNode* p = new DNode(0, vector<int>(1, qv), -1, -1);
	p->last_enum = degree[qv];
	p->last_sz = 0;
	p->save = 1;
	Q.push(p);

	//cout << g.eindex.size() << endl;
	//cout << g.components.size() << endl;
	dfs(g, phi, Q, num, t_s, t_e, degree, window_edges);

	ofstream logger(filename, ios::app);
	if (g.testnum >= 30) {
		logger << fixed<< setprecision(8) << qv << " " << g.tspan / (double)g.testnum << " " << g.iorate / (double)g.testnum << " " << g.corerate / (double)g.testnum << endl;
	}
	else
		logger << qv << " " << g.testnum << endl;

	/*ofstream logger_backup(filename_backup, ios::app);
	if (g.testnum >= 30) {
		logger_backup << fixed<< setprecision(8) << qv << " " << g.tspan / (double)g.testnum << " " << g.iorate / (double)g.testnum << " " << g.corerate / (double)g.testnum << endl;
	}
	else
		logger_backup << qv << " " << g.testnum << endl;*/

	clock_t sa = clock();
	while(!Q.empty()){
		DNode* q = Q.top();
		Q.pop();
		delete q;
	}
	clock_t se = clock();
	g.timesum += (double)(se - sa) / (CLOCKS_PER_SEC);
}


void GraphAnalyzer::tsearch_reduce(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e) {
	priority_queue<DNode*, vector<DNode*>, tscmp> Q;
	
	double max_span = 0;
	if (phi == 1) {
		max_span = g.th_beta;
	}
	else {
		max_span = (double)(exp(1.0 / phi - 1) - 1.0) / g.th_alpha + g.th_beta;
	}
}

void GraphAnalyzer::tsearch(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e) {
	//unordered_set<int> neighs;
	vector<vector<int>> ans;
	vector<int> cur;
	unordered_set<int> record;
	unordered_set<string> recstr;

	cur.push_back(qv);
	record.insert(qv);

	/*if (g.graph[qv] != NULL) {
		for (const auto& n : *g.graph[qv]) {
			neighs.insert(n.first);
		}
	}*/

	int t_edge_num = -1;
	unordered_map<int, int> degree;
	vector<TemporalEdge> tstamps;

	Lattice* root = new Lattice(vector<int>(1, qv));
	Lattice* cur_node = root;
	Lattice* start_node = root;
	bool enough = false;

	if (g.graph[qv] != NULL && g.graph[qv]->find(qv) != g.graph[qv]->end()) {
		for (const auto& t : (*g.graph[qv])[qv]) {
			if (t >= t_s && t <= t_e) {
				g.addT_actual(-1, t);
				tstamps.push_back(TemporalEdge(qv, qv, t));
			}
		}
	}

	initNodes(g, qv, degree, t_edge_num, t_s, t_e);
	
	while (ans.size() < num) {
		Lattice* last = NULL;
		Lattice* nextnode = NULL;
		while (true) {
			unordered_set<int> neighs;
			for (const auto& n : cur) {
				for (const auto& n2 : g.network[n]) {
					int sz = (*g.graph[n])[n2].size();
					if ((*g.graph[n])[n2][0] > t_e || (*g.graph[n])[n2][sz - 1] < t_s)
						continue;

					for (const auto& t : (*g.graph[n])[n2]) {
						if (t >= t_s && t <= t_e) {
							neighs.insert(n2);
							break;
						}
					}
				}
				// neighs.insert(g.network[n].begin(), g.network[n].end());
			}
			
			vector<TemporalEdge> tstamps;
			for (int i1 = 0; i1 < cur.size(); ++i1) {
				int n1 = cur[i1];
				for (int i2 = i1; i2 < cur.size(); ++i2) {
					int n2 = cur[i2];
					if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
						for (const auto& t : (*g.graph[n1])[n2]) {
							if (t >= t_s && t <= t_e) {
								tstamps.push_back(TemporalEdge(n1, n2, t));
							}
						}
					}
				}
			}
			int t_sz = tstamps.size();

			for (const auto& n : neighs) {
				if (record.find(n) != record.end())
					continue;

				cur.push_back(n);
				record.insert(n);

				vector<int> st(cur);
				sort(st.begin(), st.end());
				string sig = "";
				for (const auto& n : st) {
					sig += to_string(n) + " ";
				}
				if (recstr.find(sig) != recstr.end()) {
					cur.pop_back();
					record.erase(n);
					continue;
				}
				else {
					recstr.insert(sig);
				}

				Lattice* sub = new Lattice(cur);
				if (nextnode == NULL)
					nextnode = sub;

				cur_node->child.push_back(sub);

				initNodes(g, n, degree, t_edge_num, t_s, t_e);

				g.save(-1);
				
				if (cur.size() == 3 && cur[0] == 1 && cur[1] == 18 && cur[2] == 121)
					int kps = 0;

				double ts = analyzeIndex(g, cur, sig, tstamps, degree, t_edge_num, t_s, t_e);
				
				/*if (ts > 0.1) {
					cout << ts << " |     ";
					for (const auto& n : cur) {
						cout << n << " ";
					}
					cout << endl;
				}*/

				sub->set(g.comm_Ex[-1], g.comm_Ex2[-1], g.comm_edge[-1]);
				sub->parent = cur_node;
				g.load(-1);
				tstamps.resize(t_sz);

				if (cur.size() > 40) {
					//system("pause");
					enough = true;
					break;
				}

				if (ts >= phi) {
					g.tspan = 0;
					g.iorate = 0;
					computeMetric(g, cur, t_s, t_e, ts);
					
					cout << ts << " " << ans.size() + 1 << "/" << num << endl;
					//cout << g.tspan << " " << g.iorate << endl;
					
					//cout << ts << endl;
					ans.push_back(cur);
					for (const auto& n : cur) {
						cout << n << " ";
					}
					cout << endl;
					
					if (ans.size() >= num) {
						//logger << g.rev_mapper[qv] << ',';
						enough = true;
						break;
					}
				}

				if (last != NULL) {
					last->next = sub;
					last = sub;
				}
				else {
					last = sub;
				}

				cur.pop_back();
				record.erase(n);
			}
			if (enough)
				break;
		
			if (cur_node->next == NULL) {
				break;
			}
			else {
				cur_node = cur_node->next;
				record.clear();
				cur = cur_node->node;
				record = unordered_set<int>(cur.begin(), cur.end());
				g.comm_Ex[-1] = cur_node->commEx;
				g.comm_Ex2[-1] = cur_node->commEx2;
				g.comm_edge[-1] = cur_node->commEdge;
			}
		}
		if (enough)
			break;
		
		if (nextnode == NULL)
			break;
		cur_node = nextnode;
		cur = cur_node->node;
		record = unordered_set<int>(cur_node->node.begin(), cur_node->node.end());
		start_node = cur_node;
		g.comm_Ex[-1] = cur_node->commEx;
		g.comm_Ex2[-1] = cur_node->commEx2;
		g.comm_edge[-1] = cur_node->commEdge;
		g.sRecorder[g.scode].clear();
		g.scode = 1 - g.scode;
		cout << "Level " << cur.size() <<  " " << qv << endl;
	}

	deleteTree(root);
}

void GraphAnalyzer::initNodes(TemporalGraph& g, int n, unordered_map<int, int>& degree, int& t_edge_num, int t_s, int t_e) {
	if (degree.find(n) != degree.end())
		return;
	int lowbound, upbound;

	vector<int>::iterator low = lower_bound(g.sum_t_vertex[n].begin(), g.sum_t_vertex[n].end(), t_s);
	if (low == g.sum_t_vertex[n].end()) {
		lowbound = g.sum_t_vertex[n].size();
	}
	else {
		lowbound = low - g.sum_t_vertex[n].begin();
	}
		
	vector<int>::iterator upper = upper_bound(g.sum_t_vertex[n].begin(), g.sum_t_vertex[n].end(), t_e);
	if (upper == g.sum_t_vertex[n].end()) {
		upbound = g.sum_t_vertex[n].size();
	}
	else {
		upbound = upper - g.sum_t_vertex[n].begin();
	}
		
	degree[n] = upbound - lowbound;
	/*cout << upbound << " "<< lowbound << " " << t_s << " "<< t_e << endl;
	for (const auto& t : g.sum_t_vertex[n1]) {
		cout << t << " ";
	}
	cout << endl;
	system("pause");*/
	
	if (t_edge_num == -1)
		t_edge_num = upper_bound(g.record_edges.begin(), g.record_edges.end(), t_e) - lower_bound(g.record_edges.begin(), g.record_edges.end(), t_s);
	//cout << t_edge_num << " " << degree[1] << " " << degree[2] << endl;
}

double GraphAnalyzer::analyzeIndex(TemporalGraph& g, vector<int>& nodes, string& signature, vector<TemporalEdge>& tstamps, unordered_map<int, int>& degree, int t_edge_num, int t_s, int t_e) {
	int new_node = nodes[(int)nodes.size() - 1];
	double ts = 0.0;
	
	//vector<Edge> tstamps;

	double avg_t = 0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;
	int e_num = 0;
	//int edgnum = t_edge_num;

	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		e_num += degree[n1];

		if (g.graph[n1] != NULL && g.graph[n1]->find(new_node) != g.graph[n1]->end()) {
			for (const auto& t : (*g.graph[n1])[new_node]) {
				if (t >= t_s && t <= t_e) {
					g.addT_actual(-1, t);
					tstamps.push_back(TemporalEdge(n1, new_node, t));
				}
			}
		}
		for (int i2 = i1 + 1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
				for (const auto& t : (*g.graph[n1])[n2]) {
					if (t >= t_s && t <= t_e) {
						e_num--;
					}
				}
			}
		}
	}
	
	double avg_factor = 2 * e_num;//t_edge_num;

	if (t_edge_num == 0 || e_num == 0 || tstamps.empty()) {
		return -2;
	}

	double zeta = 1.0 / (double)(1 + log(g.th_alpha * g.th_ev2 + 1));

	if (tstamps.size() == 1)
		zeta = 1;
	//zeta = 1;

	double expect_edge_num = 0;
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		for (int i2 = i1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];	

			if (n1 != n2 || (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end())) {			
				//ts -= 2 * degree[n1] * degree[n2] * tseval.computeAvgV_both(g, nodes, tstamps, n1, n2, t_s, t_e) / avg_factor;
				ts -= 2 * degree[n1] * degree[n2] * zeta / avg_factor;
				expect_edge_num += (double)degree[n1] * degree[n2] / avg_factor;
			}
		}
	}

	g.expect_index.clear();

	double stmp = 0;
	int sz = tstamps.size();
	for (int i = 0; i < sz; ++i) {
		int cur_t = tstamps[i].t;
			
		double tmp = tseval.SVs(g, cur_t, -1);
		stmp += tmp;
		//ts += 2;
		ts += 2 * tmp;
	}

	ts /= 2;
	//g.sRecorder[1 - g.scode][signature] = stmp / (double)sz;

	//cout << ts << " " << zeta << " " << sz << " " << e_num << " " << expect_edge_num << endl;
	/*if (zeta != 1)
		ts = ts / (2.0 * (1 - zeta) * ((double)e_num - expect_edge_num));
	else
		ts = ts / (2 * e_num);*/
	//cout << ts << " " << avg_factor << endl;
	//ts = ts / avg_factor;
	//ts = ts / (2 * stmp);//avg_factor;
	// ts = ts / (double)avg_factor;
	return ts;
}

double GraphAnalyzer::analyzeIndex_ab(TemporalGraph& g, vector<int>& nodes, string& signature, vector<TemporalEdge>& tstamps, unordered_map<int, int>& degree, int t_edge_num, int t_s, int t_e) {
	int new_node = nodes[(int)nodes.size() - 1];
	double ts = 0.0;
	
	//vector<Edge> tstamps;

	double avg_t = 0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;
	int e_num = 0;
	//int edgnum = t_edge_num;

	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		e_num += degree[n1];

		if (g.graph[n1] != NULL && g.graph[n1]->find(new_node) != g.graph[n1]->end()) {
			for (const auto& t : (*g.graph[n1])[new_node]) {
				if (t >= t_s && t <= t_e) {
					g.addT_actual(-1, t);
					tstamps.push_back(TemporalEdge(n1, new_node, t));
				}
			}
		}
		for (int i2 = i1 + 1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];
			if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {
				for (const auto& t : (*g.graph[n1])[n2]) {
					if (t >= t_s && t <= t_e) {
						e_num--;
					}
				}
			}
		}
	}
	
	double avg_factor = 2 * e_num;//t_edge_num;

	if (t_edge_num == 0 || e_num == 0 || tstamps.empty()) {
		return -2;
	}
	
	for (int i1 = 0; i1 < nodes.size(); ++i1) {
		int n1 = nodes[i1];
		for (int i2 = i1; i2 < nodes.size(); ++i2) {
			int n2 = nodes[i2];	

			if (n1 != n2 || (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end())) {
				ts -= degree[n1] * degree[n2] * tseval.computeAvgV_ab(g, nodes, tstamps, n1, n2, t_s, t_e) / avg_factor;
			}
		}
	}

	g.expect_index.clear();

	vector<int> ttmp;
	for (int i = 0; i < tstamps.size(); ++i) {
		ttmp.push_back(tstamps[i].t);
	}
	
	double stmp = 0;
	int sz = ttmp.size();
	for (int i = 0; i < sz; ++i) {
		int cur_t = ttmp[0];
		
		ttmp.erase(ttmp.begin());
		double tmp = tseval.SV(cur_t, ttmp);
		stmp += tmp;
		ts += tmp;
	}

	g.sRecorder[1 - g.scode][signature] = stmp / (double)sz;

	//ts = ts / stmp;//avg_factor;
	// ts = ts / (double)avg_factor;
	return ts;
}

void GraphAnalyzer::deleteTree(Lattice* root) {
	for (int i = 0; i < root->child.size(); ++i) {
		deleteTree(root->child[i]);
	}

	delete root;
}

void GraphAnalyzer::caseStudy(TemporalGraph& g, int mid) {
	int nid = g.mapper[mid];
	cout << nid << endl;

	int t_s = g.minstamp;
	cout << t_s << endl;
	int duration = 0;
	int ner = 0;
	
	double phi = 0.2;
	double maxphi = 0.2;
	for (; phi <= maxphi; phi += 0.1) {
		time_t start = clock();
		t_s = 2015;
		
		//fstream output("log.txt", ios::app);
		int tp = 0;
		tsearch(g, nid, phi, 100, t_s + tp * duration, t_s + (tp + 1) * duration);
		g.clear();
		//output << s << endl;
		//output.close();
		ner++;

		cout << "Phi: " << phi << endl;

		cout << ner << endl;
		cout << g.tspan << " " << g.iorate << " " << g.testnum << endl;
		cout << g.tspan / (double)g.testnum << " " << g.iorate / (double)g.testnum << endl;
		cout << g.avgts / (double)g.testnum << endl;
	}
}

void GraphAnalyzer::buildIndex(TemporalGraph& g, int t_s, int t_e) {
	g.components.clear();
	g.cc_map.clear();
	g.eindex.clear();
	g.cc_network.clear();

	cout << "Start Build Index" << endl;
	connectedComponents(g, t_s, t_e, g.components, g.cc_map);
	
	cout << "Finish Build CC" << endl;

	ofstream efile("index.txt", ios::out);

	for (int index = 0; index < g.components.size(); ++index) {
		//cout << index << " " << g.components.size() << endl;
		for (int i = 0; i < g.components[index].size(); ++i) {
			//if (i % 1000 == 0)
			//	cout << i << " " << g.components[index].size() << endl;
			int n1 = g.components[index][i];
			for (int j = i + 1; j < g.components[index].size(); ++j) {
				int n2 = g.components[index][j];
				int e_num = 0;
				int maxt = -1;
				int mint = -1;

				if (g.graph[n1] != NULL && g.graph[n1]->find(n2) != g.graph[n1]->end()) {				
					for (const auto& t : (*g.graph[n1])[n2]) {
						if (t >= t_s && t <= t_e) {
							if (maxt == -1 || maxt < t)
								maxt = t;
							if (mint == -1 || mint > t)
								mint = t;
							e_num++;
						}
						else if (t > t_e) {
							break;
						}
					}
				}
				
				if (e_num > 0) {
					g.eindex[index].push_back(TemporalEdgeInfo(e_num, n1, n2, maxt, mint));
				}
			}
		}

		sort(g.eindex[index].begin(), g.eindex[index].end(), compareEdgeInfo);
		
		efile << index << endl;
		efile << g.eindex[index].size() << endl;
		for (int i = 0; i < g.eindex[index].size(); ++i) {
			efile << g.eindex[index][i].src << " " << g.eindex[index][i].dst << " " << g.eindex[index][i].max_time << " " << g.eindex[index][i].min_time << " " << g.eindex[index][i].num << endl;
		}
		/*for (const auto& es : g.eindex[index]) {
			cout << es.min_time << " " << es.max_time << endl;
			system("pause");
		}*/
		for (int i = 0; i < g.eindex[index].size(); ++i) {
			int n1 = g.eindex[index][i].src;
			int n2 = g.eindex[index][i].dst;
			g.cc_network[n1].push_back(i);
			g.cc_network[n2].push_back(i);
		}
	}
	efile.close();
	cout << "Finish Build Index" << endl;
}

void GraphAnalyzer::connectedComponents(TemporalGraph& g, int t_s, int t_e, vector<vector<int>>& components, unordered_map<int, int>& cc_map) {
	unordered_set<int> found;
	int index = 0;

	for (const auto& n : g.network) {
		if (found.find(n.first) != found.end())
			continue;

		int n1 = n.first;
		vector<int> cc;
		queue<int> Q;
		Q.push(n1);

		while (!Q.empty()) {
			int node = Q.front();
			Q.pop();
			cc.push_back(node);
			found.insert(node);
			cc_map[node] = index;

			if (g.graph[node] != NULL) {
				for (const auto& n2 : (*g.graph[node])) {
					for (const auto& t : n2.second) {
						if (t >= t_s && t <= t_e) {
							if (found.find(n2.first) == found.end()) {
								Q.push(n2.first);
								found.insert(n2.first);
							}
						}
						else if (t > t_e)
							break;
					}
				}
			}
		}

		components.push_back(cc);
		index++;
	}
}

int GraphAnalyzer::getComponentEst(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& invalid_nodes, unordered_set<int>& cc, int& maxnode) {
	int ccindex2 = g.cc_map[nodes[0]];
	cc = unordered_set<int>(g.components[ccindex2].begin(), g.components[ccindex2].end());
	return 0;
	queue<int> Q;
	unordered_set<int> RQ;
	unordered_set<int> related_edges;
	unordered_map<int, int> node_app;

	for (const auto& n : nodes) {
		Q.push(n);
		RQ.insert(n);
	}

	int mintmp = mint;
	int maxtmp = maxt;
	int ccindex = g.cc_map[nodes[0]];
	int e_num = 0;
	while (!Q.empty()) {
		int node = Q.front();
		Q.pop();
		cc.insert(node);
		
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (e->max_time - mint > max_span)
				break;
			if (max(e->max_time, maxt) - min(e->min_time, mint) > max_span)
				continue;
			if (invalid_nodes.find(e->src) != invalid_nodes.end()
				|| invalid_nodes.find(e->dst) != invalid_nodes.end())
				continue;
			if (e->src == node) {
				if (RQ.find(e->dst) == RQ.end()) {
					Q.push(e->dst);
					RQ.insert(e->dst);
				}
			}
			else {
				if (RQ.find(e->src) == RQ.end()) {
					Q.push(e->src);
					RQ.insert(e->src);
				}
			}
			if (mintmp == -1 || e->min_time < mintmp)
				mintmp = e->min_time;
			if (maxtmp == -1 || e->max_time > maxtmp)
				maxtmp = e->max_time;
			e_num += e->num;
			//related_edges.insert(index);
		}
	}

	return 0;
	
	vector<int> re(related_edges.begin(), related_edges.end());

	sort(re.begin(), re.end(), MinCmp(&g.eindex[ccindex]));
	vector<int> min_order = re;
	sort(re.begin(), re.end(), MaxCmp(&g.eindex[ccindex]));
	vector<int> max_order = re;

	int min_order_index = 0;
	int max_order_index = 0;
	int min_index = min_order[min_order_index];
	int max_th = g.eindex[ccindex][min_index].min_time + max_span;
	for (; max_order_index < max_order.size(); ++max_order_index) {
		int max_index = max_order[max_order_index];
		if (g.eindex[ccindex][max_index].max_time > max_th) {
			break;
		}
	}

	int maxcount = 0;
	maxnode = 0;
	for (int i = max_order_index - 1; i >= 0; --i) {
		int max_index = max_order[i];
		if (g.eindex[ccindex][max_index].min_time >= g.eindex[ccindex][min_index].min_time) {
			maxcount += g.eindex[ccindex][max_index].num;
			//node_app[g.eindex[ccindex][max_index].src]++;
			//node_app[g.eindex[ccindex][max_index].dst]++;
		}
		else if (g.eindex[ccindex][max_index].max_time < g.eindex[ccindex][min_index].min_time)
			break;
	}

	maxnode = cc.size();
	min_order_index++;
	int count = maxcount;
	int save = g.eindex[ccindex][min_order[0]].num;
	for (; min_order_index < min_order.size(); ++min_order_index) {
		int min_index = min_order[min_order_index];
		int last_min_index = min_order[min_order_index - 1];
		if (g.eindex[ccindex][min_index].min_time == g.eindex[ccindex][last_min_index].min_time) {
			save += g.eindex[ccindex][min_index].num;
			/*node_app[g.eindex[ccindex][last_min_index].src]--;
			node_app[g.eindex[ccindex][last_min_index].dst]--;

			if (node_app[g.eindex[ccindex][last_min_index].src] == 0)
				node_app.erase(g.eindex[ccindex][last_min_index].src);
			if (node_app[g.eindex[ccindex][last_min_index].dst] == 0)
				node_app.erase(g.eindex[ccindex][last_min_index].dst);*/
			continue;
		}

		count -= save;
		save = 0;
		max_th = g.eindex[ccindex][min_index].min_time + max_span;

		for (; max_order_index < max_order.size(); ++max_order_index) {
			int max_index = max_order[max_order_index];
			if (g.eindex[ccindex][max_index].max_time <= max_th && g.eindex[ccindex][max_index].min_time >= g.eindex[ccindex][min_index].min_time) {
				count += g.eindex[ccindex][max_index].num;
				//node_app[g.eindex[ccindex][max_index].src]++;
				//node_app[g.eindex[ccindex][max_index].dst]++;
			}
		}

		maxcount = max(maxcount, count);
		//maxnode = max(maxnode, (int)node_app.size());
	}

	//cout << mintmp << " " << maxtmp << " " << maxtmp - mintmp << " " << max_span << " " << e_num / 2 << " " << maxcount << endl;
	//cout << maxnode << " " << cc.size() << endl;
	//system("pause");
	return maxcount;
}

double GraphAnalyzer::getMaxIO(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edge) {
	int ccindex = g.cc_map[nodes[0]];
	double std = (double)in_sz / in_enum;
	double std_out = (double)invalid_edge / in_enum;

	//cout << mint << " " << maxt << " " << maxt - mint << " " << max_span << endl;
	double maxrate = 0;
	//unordered_map<double, int> in_map;
	//unordered_map<double, int> out_map;
	//vector<double> rate_list;

	double minrate = 0;
	int out_upper = invalid_edge;
	int out_lower = in_enum;

	int upper = in_sz;
	int lower = in_enum;

	unordered_set<int> nodeset(nodes.begin(), nodes.end());

	for (const auto& node : cc) {
		if (nodeset.find(node) != nodeset.end())
			continue;

		int inner = 0;
		int outer = 0;
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (max(maxt, e->max_time) - min(mint, e->min_time) > max_span)
				outer += e->num;
			else {
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end())
					outer += e->num;
				else
					inner += e->num;
			}
		}
		
		double rate = (double)inner / outer;
		double out_rate = (double)outer / (inner + outer);
		if (outer == 0) {
			rate = 1;
			out_rate = 0;
		}
		
		if (rate > std) {
			upper += inner;
			lower += outer;
			//rate_list.push_back(rate);
			//in_map[rate] += inner;
			//out_map[rate] += outer;
			//cout << rate << " " << inner << endl;
		}
		if (out_rate < std_out) {
			out_upper += outer;
			out_lower += inner + outer;
		}
	}
	
	/*sort(rate_list.begin(), rate_list.end());
	int upper = in_sz;
	int lower = in_enum;
	for (int i = 0; i < rate_list.size(); ++i) {
		double rate = rate_list[i];
		upper += in_map[rate];
		lower += out_map[rate];
		cout << rate << " " << in_map[rate] << endl;
	}
	if (upper < 0)
		system("pause");

	int upper_test = in_sz;
	int lower_test = in_enum;
	for (const auto& r : in_map) {
		upper_test += r.second;
	}
	for (const auto& r : out_map) {
		lower_test += r.second;
	}
	cout << upper << " " << lower << " " << upper_test << " " << lower_test << endl;*/
	
	//cout << "MAX: " << 1 - (double)out_upper / out_lower << " "<< (double)upper / lower << " " << tseval.computeIOScore(g, min(1 - (double)out_upper / out_lower, (double)upper / lower)) << endl;
	//system("pause");
	return tseval.computeIOScore(g, min(1 - (double)out_upper / out_lower, (double)upper / lower));
	//if (maxrate != 1) {
	//	cout << "MAX: " << (double)upper / lower << " " <<  << " " << min_io << endl;
	//	system("pause");
	//}
}

double GraphAnalyzer::getMaxTopo(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int lose_core) {
	int ccindex = g.cc_map[nodes[0]];
	double std = (double)lose_core / nodes.size();
	int n_num = nodes.size();

	//cout << mint << " " << maxt << " " << maxt - mint << " " << max_span << endl;
	int sum_core = lose_core;
	unordered_set<int> nodeset(nodes.begin(), nodes.end());

	for (const auto& node : cc) {
		if (nodeset.find(node) != nodeset.end())
			continue;
		int inner = 0;
		int outer = 0;
		int neighs = 0;
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (max(maxt, e->max_time) - min(mint, e->min_time) <= max_span) {
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end())
					continue;
				
				neighs++;

				if (neighs >= g.kcore)
					break;
			}
		}
		
		int new_core = max(0.0, g.kcore - neighs);
		if (new_core <= std) {
			sum_core += new_core;
			n_num++;
		}
	}
	
	return tseval.computeTopoScore(g, (double)sum_core / (g.kcore * n_num));
	//cout << "MAX: " << (double)sum_core / (g.kcore * cc.size()) << " " << tseval.computeTopoScore(g, (double)sum_core / (g.kcore * cc.size())) << endl;
	//system("pause");
}

void GraphAnalyzer::getMaxTT(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edge, int lose_core, double& io, double& topo) {
	int ccindex = g.cc_map[nodes[0]];
	double std = (double)in_sz / in_enum;
	double std_out = (double)invalid_edge / in_enum;

	//cout << mint << " " << maxt << " " << maxt - mint << " " << max_span << endl;
	double maxrate = 0;
	//unordered_map<double, int> in_map;
	//unordered_map<double, int> out_map;
	//vector<double> rate_list;

	double minrate = 0;
	int out_upper = invalid_edge;
	int out_lower = in_enum;

	int upper = in_sz;
	int lower = in_enum;

	unordered_set<int> nodeset(nodes.begin(), nodes.end());

	int n_num = 0;
	int sum_core = 0;
	for (const auto& node : nodeset) {
		int neighs = 0;
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (max(maxt, e->max_time) - min(mint, e->min_time) > max_span) {
			}
			else {
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end()) {
				}
				else {
					neighs++;
					if (neighs >= g.kcore)
						break;
				}
			}
		}
		int new_core = min((double)g.kcore, (double)neighs);
		sum_core += new_core;
		n_num++;
	}

	double stdcore = (double)sum_core / nodes.size();

	//cout << mint << " " << maxt << " " << maxt - mint << " " << max_span << endl;
	//int sum_core = lose_core;

	for (const auto& node : cc) {
		if (nodeset.find(node) != nodeset.end())
			continue;

		int inner = 0;
		int outer = 0;
		int neighs = 0;
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (max(maxt, e->max_time) - min(mint, e->min_time) > max_span)
				outer += e->num;
			else {
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end())
					outer += e->num;
				else {
					inner += e->num;
					neighs++;
				}
			}
		}
		
		double rate = (double)inner / outer;
		double out_rate = (double)outer / (inner + outer);
		if (outer == 0) {
			rate = 1;
			out_rate = 0;
		}
		
		if (rate > std) {
			upper += inner;
			lower += outer;
			//rate_list.push_back(rate);
			//in_map[rate] += inner;
			//out_map[rate] += outer;
			//cout << rate << " " << inner << endl;
		}
		if (out_rate < std_out) {
			out_upper += outer;
			out_lower += inner + outer;
		}

		int new_core = min((int)g.kcore, neighs);
		if (new_core >= stdcore) {
			sum_core += new_core;
			n_num++;
		}
	}
	
	topo = tseval.computeTopoScore(g, (double)sum_core / (g.kcore * n_num));
	io = tseval.computeIOScore(g, min(1.0, (double)upper / lower));
	//if (maxrate != 1) {
	//	cout << "MAX: " << (double)upper / lower << " " <<  << " " << min_io << endl;
	//	system("pause");
	//}
}


void GraphAnalyzer::getMaxTT_new(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edge, int lose_core, double& io, double& topo) {
	int ccindex = g.cc_map[nodes[0]];
	double std = (double)in_sz / in_enum;
	double std_out = (double)invalid_edge / in_enum;

	//cout << mint << " " << maxt << " " << maxt - mint << " " << max_span << endl;
	double maxrate = 0;
	//unordered_map<double, int> in_map;
	//unordered_map<double, int> out_map;
	//vector<double> rate_list;

	double minrate = 0;
	int out_upper = invalid_edge;
	int out_lower = in_enum;

	int upper = in_sz;
	int lower = in_enum;

	unordered_set<int> nodeset(nodes.begin(), nodes.end());

	int n_num = 0;
	int sum_core = 0;
	for (const auto& node : nodeset) {
		int neighs = 0;
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (max(maxt, e->max_time) - min(mint, e->min_time) > max_span) {
			}
			else {
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end()) {
				}
				else {
					neighs++;
					if (neighs >= g.kcore)
						break;
				}
			}
		}
		int new_core = min((double)g.kcore, (double)neighs);
		sum_core += new_core;
		n_num++;
	}

	double stdcore = (double)sum_core / nodes.size();

	//cout << mint << " " << maxt << " " << maxt - mint << " " << max_span << endl;
	//int sum_core = lose_core;

	vector<int> outers, inners, neighsvec;
	bool largerIO = false;
	bool largerTopo = false;

	for (const auto& node : cc) {
		if (nodeset.find(node) != nodeset.end())
			continue;

		int inner = 0;
		int outer = 0;
		int neighs = 0;
		for (int i = 0; i < g.cc_network[node].size(); ++i) {
			int index = g.cc_network[node][i];

			TemporalEdgeInfo* e = &g.eindex[ccindex][index];
			if (max(maxt, e->max_time) - min(mint, e->min_time) > max_span)
				outer += e->num;
			else {
				if (invalid_nodes.find(e->src) != invalid_nodes.end()
					|| invalid_nodes.find(e->dst) != invalid_nodes.end())
					outer += e->num;
				else {
					inner += e->num;
					neighs++;
				}
			}
		}

		if (inner == 0 && outer == 0)
			continue;
		
		double rate = (double)inner / outer;
		outers.push_back(outer);
		inners.push_back(inner);
			
		if (outer == 0)
			rate = 1;
		if (rate >= std) {
			largerIO = true;
		}

		int new_core = min((int)g.kcore, neighs);
		if (new_core >= stdcore) {
			largerTopo = true;
		}
		neighsvec.push_back(new_core);
	}

	vector<int> idx(outers.size());
	for (int i = 0; i < idx.size(); ++i)
		idx[i] = i;

	sort(idx.begin(), idx.end(), [&outers, &inners](int i1, int i2) {return (double)inners[i1]/max(0.000001, (double)outers[i1]) > (double)inners[i2]/(double)max(0.000001, (double)outers[i2]);});
	
	if (largerIO) {
		for (int i = 0; i < idx.size(); ++i) {
			int index = idx[i];
			double rate = (double)inners[index] / outers[index];
			if (outers[index] == 0)
				rate = 1;
			if ((double)upper / lower < rate) {
				upper += inners[index];
				lower += outers[index];
			}
			else {
				break;
			}
		}
		//if (upper < lower)
		//	cout << upper << " " << lower << endl;
		io = tseval.computeIOScore(g, min(1.0, (double)upper / lower));
	}
	else {
		double maxrate = -1;
		for (int i = 0; i < idx.size(); ++i) {
			int index = idx[i];
			if (lower + outers[index] == 0) {
				cout << "Error" << endl;
				maxrate = 1;
			}
			else
				maxrate = max(maxrate, (double)(upper + inners[index]) / (lower + outers[index]));
		}
		io = tseval.computeIOScore(g, maxrate);
	}

	sort(neighsvec.rbegin(), neighsvec.rend());

	if (largerTopo) {
		for (int i = 0; i < neighsvec.size(); ++i) {
			if (neighsvec[i] > sum_core / (double)n_num) {
				sum_core += neighsvec[i];
				n_num++;
			}
			else {
				break;
			}
		}
		topo = tseval.computeTopoScore(g, (double)sum_core / (g.kcore * n_num));
	}
	else {
		double maxrate = -1;
		for (int i = 0; i < neighsvec.size(); ++i) {
			maxrate = max(maxrate, (double)(sum_core + neighsvec[i]) / (n_num + 1));
		}
		topo = tseval.computeTopoScore(g, (double)maxrate / g.kcore);
	}
	
	
	//if (maxrate != 1) {
	//	cout << "MAX: " << (double)upper / lower << " " <<  << " " << min_io << endl;
	//	system("pause");
	//}
}



double GraphAnalyzer::analyzeIndex_dfs_load(TemporalGraph& g, vector<int>& nodes, unordered_map<int, int>& degree, int t_s, int t_e, int tspan, double& zeta_tmp, int& in_sz, int& in_enum, int& in_core
											, unordered_map<int, int>& ncore, int& last_sz, int& last_enum) {
	int new_node = nodes[(int)nodes.size() - 1];
	double ts = 0.0;
	
	//vector<Edge> tstamps;

	double avg_t = 0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;
	int e_num = 0;
	int inside_edge = 0;
	//int edgnum = t_edge_num;

	//vector<int> tstamps;

	int max_topo = -1;
	unordered_map<int, int> corenum;
	int intimes = 0;

	int multi_edge = 0;
	int sz = 0;

	last_enum += degree[new_node];
	for (int i1 = 0; i1 < (int)nodes.size() - 1; ++i1) {
		int n1 = nodes[i1];
		
		int n2 = new_node;
		if (g.temporal_graph[n1].find(n2) != g.temporal_graph[n1].end()) {
			bool once = false;
			last_sz += g.temporal_graph[n1][n2].size();
			last_enum -= g.temporal_graph[n1][n2].size();
			if (!g.temporal_graph[n1][n2].empty()) {
				ncore[n1]++;
				ncore[n2]++;
			}
		}
	}
	e_num = last_enum;
	sz = last_sz;
	int lose_core = 0;
	for (const auto& deg : ncore) {
		/*if (max_topo == -1)
			max_topo = deg.second;
		else
			max_topo = min(deg.second, max_topo);*/
		lose_core += min((double)g.kcore, (double)deg.second);
	}
	double lose_rate = lose_core / (double)(g.kcore * nodes.size());
	in_core = lose_core;

	double avg_factor = 2 * e_num;//t_edge_num;

	if (e_num == 0 || sz == 0) {
		//g.load(-1);
		return -2;
	}

	e_num -= (1 - g.multi_rate) * multi_edge;

	sz = sz - (1 - g.multi_rate) * multi_edge;

	//double zeta = tseval.computeScore(g, g.th_ev2);

	//if (sz == 1)
	//	zeta = 1;a
	//zeta = 1;
	
	double zeta_topo = tseval.computeTopoScore(g, lose_rate);
	//cout << zeta_topo << endl;
	//system("pause");
	//cout << sz << " " << e_num -b sz << " " << e_num << endl;
	
	double zeta_io = tseval.computeIOScore(g, (double)sz / e_num);
	in_enum = e_num;
	in_sz = sz;
	//cout << zeta_io << " " << (double)sz / e_num << " " << tseval.computeIOScore(g, 0.35) << " " << tseval.computeIOScore(g, 0.3) << endl;
	//double edgesum = e_num;
	//double res = (double)sz / e_num - pow((double)e_num / edgesanum, 2.0);

	double tmp = tseval.computeScore(g, tspan); //tseval.SVs(g, tstamps);
	double stmp = 0;
	
	//cout << tspan << " " << lose_core << " " << nodes.size() << " " << sz << " " << e_num << endl;
	ts = (double)tmp * zeta_io * zeta_topo;
	//ts = (double)(tmp + zeta_io + zeta_topo) / 3.0;
	/*if (zeta_io >= 0.5) {
		cout << "ACTUAL: " << " " << ts << " " << tmp << " " << zeta_topo << " " << zeta_io << endl;
		system("pause");
	}*/
	//cout << tspan << " " << lose_core << " " << nodes.size() << " " << sz << " " << e_num << endl;
	//cout << "ACTUAL: " << " " << ts << " " << tmp << " " << zeta_topo << " " << zeta_io << endl;
	//system("pause");
	zeta_tmp = tmp;

	//if ((double)sz / e_num <= 0.7)
	//	g.refine = true;
	//if (tspan <= 1000000)/* || (double)sz / e_num >= 0.5)// ||*/ //lose_rate <= 0.8)
	//	g.refine = true;

	return ts;
}
