#include "TS.h"

double TS::computeAvgV_ana(TemporalGraph& g, vector<TemporalEdge>& tstamps, int u, int v, int t_s, int t_e) {
	double sum1 = 0;
	double sum2 = 0;
	int commcount1 = 0;
	bool hassum1 = false;
	bool hassum2 = false;

	int comm = -1;

	//if ((*g.graph[u])[v].size() == 0)
	// 	return 0.5;

	vector<int> tstamps1;
	vector<int> tstamps2;
	vector<int> toremove;

	if (g.expect_index.find(u) != g.expect_index.end()) {
		sum1 = g.expect_index[u];
		hassum1 = true;
	}
	if (g.expect_index.find(v) != g.expect_index.end()) {
		sum2 = g.expect_index[v];
		hassum2 = true;
	}

	if (hassum1 && hassum2) {
		//cout << max(sum1, sum2) << endl;
		return max(sum1, sum2);
	}

	if(!hassum1) {
		g.save(comm);
	}

	for (const auto& e : tstamps) {
		if (!hassum1) {
			if (e.rel1 != u && e.rel2 != u) {
				tstamps1.push_back(e.t);
			}
			else {
				g.removeT_actual(comm, e.t);
			}
		}
	
		if (!hassum2) {
			if (e.rel1 != v && e.rel2 != v) {
				tstamps2.push_back(e.t);
			}
			else {
				toremove.push_back(e.t);
			}
		}
	}

	if (!hassum1) {
		int sz = tstamps1.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps1[i];
			sum1 += SVs(g, cur_t, comm);
			//tstamps1.erase(tstamps1.begin());
			//sum1 += SV(cur_t, tstamps1);
			commcount1++;
		}

		if (commcount1 >= 1) {
			sum1 = sum1 / (double)commcount1;
		}
		else
			sum1 = 1;

		g.expect_index[u] = sum1;
		g.load(comm);
	}

	//double sum2 = 0;
	int commcount2 = 0;

	if (!hassum2) {
		g.save(comm);

		for (const auto& t : toremove) {
			g.removeT_actual(comm, t);
		}

		int sz = tstamps2.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps2[i];
			sum2 += SVs(g, cur_t, comm);
			//tstamps2.erase(tstamps2.begin());
			//sum2 += SV(cur_t, tstamps2);
			commcount2++;
		}

		g.load(comm);

		if (commcount2 >= 1) {
			sum2 = sum2 / (double)commcount2;
		}
		else
			sum2 = 1;
	
		g.expect_index[v] = sum2;
	}

	//cout << max(sum1, sum2) << endl;
	return max(sum1, sum2);
}

double TS::computeAvgV_both(TemporalGraph& g, vector<int>& nodes, vector<TemporalEdge>& tstamps, int u, int v, int t_s, int t_e) {
	double sum1 = 0;
	double sum2 = 0;
	int commcount1 = 0;
	bool hassum1 = false;
	bool hassum2 = false;

	int comm = -1;

	vector<int> tmpnodes(nodes);
	sort(tmpnodes.begin(), tmpnodes.end());

	string sig1, sig2;
	double recsum1 = -1;
	double recsum2 = -1;

	for (int i = 0; i < tmpnodes.size(); ++i) {
		if (tmpnodes[i] != u) {
			sig1 += to_string(tmpnodes[i]) + " ";
		}
		if (tmpnodes[i] != v) {
			sig2 += to_string(tmpnodes[i]) + " ";
		}
	}

	if (g.sRecorder[g.scode].find(sig1) != g.sRecorder[g.scode].end()) {
		sum1 = g.sRecorder[g.scode][sig1];
		hassum1 = true;
		//cout << "hit" << endl;
	}
	if (g.sRecorder[g.scode].find(sig2) != g.sRecorder[g.scode].end()) {
		sum2 = g.sRecorder[g.scode][sig2];
		hassum2 = true;
		//cout << "hit" << endl;
	}

	//if ((*g.graph[u])[v].size() == 0)
	// 	return 0.5;

	vector<int> tstamps1;
	vector<int> tstamps2;
	vector<int> toremove;
	
	/*if (!hassum1 && g.expect_index.find(u) != g.expect_index.end()) {
		sum1 = g.expect_index[u];
		hassum1 = true;
	}
	if (!hassum2 && g.expect_index.find(v) != g.expect_index.end()) {
		sum2 = g.expect_index[v];
		hassum2 = true;
	}*/

	if (hassum1 && hassum2) {
		//if ((recsum1 != -1 && abs(sum1 - recsum1) > 0.00000000001) || (recsum2 != -1 && abs(sum2 - recsum2) > 0.00000000001))
		//	cout << "Wrong!!!!!!!!!" << endl;
		//cout << max(sum1, sum2) << endl;
		return max(sum1, sum2);
	}

	if(!hassum1) {
		g.save(comm);
	}

	for (const auto& e : tstamps) {
		if (!hassum1) {
			if (e.rel1 != u && e.rel2 != u) {
				tstamps1.push_back(e.t);
			}
			else {
				g.removeT_actual(comm, e.t);
			}
		}
	
		if (!hassum2) {
			if (e.rel1 != v && e.rel2 != v) {
				tstamps2.push_back(e.t);
			}
			else {
				toremove.push_back(e.t);
			}
		}
	}

	if (!hassum1) {
		int sz = tstamps1.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps1[i];
			sum1 += SVs(g, cur_t, comm);
			//tstamps1.erase(tstamps1.begin());
			//sum1 += SV(cur_t, tstamps1);
			commcount1++;
		}

		if (commcount1 >= 1) {
			sum1 = sum1 / (double)commcount1;
		}
		else
			sum1 = 1;

		g.expect_index[u] = sum1;
		g.sRecorder[g.scode][sig1] = sum1;
		g.load(comm);
	}

	//double sum2 = 0;
	int commcount2 = 0;

	if (!hassum2) {
		g.save(comm);

		for (const auto& t : toremove) {
			g.removeT_actual(comm, t);
		}

		int sz = tstamps2.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps2[i];
			sum2 += SVs(g, cur_t, comm);
			//tstamps2.erase(tstamps2.begin());
			//sum2 += SV(cur_t, tstamps2);
			commcount2++;
		}

		g.load(comm);

		if (commcount2 >= 1) {
			sum2 = sum2 / (double)commcount2;
		}
		else
			sum2 = 1;
	
		g.expect_index[v] = sum2;
		g.sRecorder[g.scode][sig2] = sum2;
	}

	//if ((recsum1 != -1 && abs(sum1 - recsum1) > 0.00000000001) || (recsum2 != -1 && abs(sum2 - recsum2) > 0.00000000001)) {
	//	cout << sum2 << " " << recsum2 <<  " " << sum2 - recsum2 << endl;
	//	cout << recsum1 << " " << recsum2 << " " << sum1 << " " << sum2 << " == " << sig1 << " == " << sig2 << endl;
	//	system("pause");
	//	cout << "Wrong!!!!!!!!!" << endl;
	//}
	//cout << max(sum1, sum2) << endl;
	return max(sum1, sum2);
}

double TS::computeAvgV_ab(TemporalGraph& g, vector<int>& nodes, vector<TemporalEdge>& tstamps, int u, int v, int t_s, int t_e) {
	double sum1 = 0;
	double sum2 = 0;
	int commcount1 = 0;
	bool hassum1 = false;
	bool hassum2 = false;

	int comm = -1;

	vector<int> tmpnodes(nodes);
	sort(tmpnodes.begin(), tmpnodes.end());

	string sig1, sig2;
	double recsum1 = -1;
	double recsum2 = -1;

	for (int i = 0; i < tmpnodes.size(); ++i) {
		if (tmpnodes[i] != u) {
			sig1 += to_string(tmpnodes[i]) + " ";
		}
		if (tmpnodes[i] != v) {
			sig2 += to_string(tmpnodes[i]) + " ";
		}
	}

	if (g.sRecorder[g.scode].find(sig1) != g.sRecorder[g.scode].end()) {
		sum1 = g.sRecorder[g.scode][sig1];
		hassum1 = true;
		//cout << "hit" << endl;
	}
	if (g.sRecorder[g.scode].find(sig2) != g.sRecorder[g.scode].end()) {
		sum2 = g.sRecorder[g.scode][sig2];
		hassum2 = true;
		//cout << "hit" << endl;
	}

	//if ((*g.graph[u])[v].size() == 0)
	// 	return 0.5;

	vector<int> tstamps1;
	vector<int> tstamps2;
	vector<int> toremove;
	
	/*if (!hassum1 && g.expect_index.find(u) != g.expect_index.end()) {
		sum1 = g.expect_index[u];
		hassum1 = true;
	}
	if (!hassum2 && g.expect_index.find(v) != g.expect_index.end()) {
		sum2 = g.expect_index[v];
		hassum2 = true;
	}*/

	if (hassum1 && hassum2) {
		//if ((recsum1 != -1 && abs(sum1 - recsum1) > 0.00000000001) || (recsum2 != -1 && abs(sum2 - recsum2) > 0.00000000001))
		//	cout << "Wrong!!!!!!!!!" << endl;
		//cout << max(sum1, sum2) << endl;
		return max(sum1, sum2);
	}

	if(!hassum1) {
		g.save(comm);
	}

	for (const auto& e : tstamps) {
		if (!hassum1) {
			if (e.rel1 != u && e.rel2 != u) {
				tstamps1.push_back(e.t);
			}
			else {
				g.removeT_actual(comm, e.t);
			}
		}
	
		if (!hassum2) {
			if (e.rel1 != v && e.rel2 != v) {
				tstamps2.push_back(e.t);
			}
			else {
				toremove.push_back(e.t);
			}
		}
	}

	if (!hassum1) {
		int sz = tstamps1.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps1[0];
			tstamps1.erase(tstamps1.begin());
			sum1 += SV(cur_t, tstamps1);
			//sum1 += SVs(g, cur_t, comm);
			//tstamps1.erase(tstamps1.begin());
			//sum1 += SV(cur_t, tstamps1);
			commcount1++;
		}

		if (commcount1 >= 1) {
			sum1 = sum1 / (double)commcount1;
		}
		else
			sum1 = 1;

		g.expect_index[u] = sum1;
		g.sRecorder[g.scode][sig1] = sum1;
		g.load(comm);
	}

	//double sum2 = 0;
	int commcount2 = 0;

	if (!hassum2) {
		g.save(comm);

		for (const auto& t : toremove) {
			g.removeT_actual(comm, t);
		}

		int sz = tstamps2.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps2[0];
			tstamps2.erase(tstamps2.begin());
			sum2 += SV(cur_t, tstamps2);
			//sum2 += SVs(g, cur_t, comm);
			//tstamps2.erase(tstamps2.begin());
			//sum2 += SV(cur_t, tstamps2);
			commcount2++;
		}

		g.load(comm);

		if (commcount2 >= 1) {
			sum2 = sum2 / (double)commcount2;
		}
		else
			sum2 = 1;
	
		g.expect_index[v] = sum2;
		g.sRecorder[g.scode][sig2] = sum2;
	}

	//if ((recsum1 != -1 && abs(sum1 - recsum1) > 0.00000000001) || (recsum2 != -1 && abs(sum2 - recsum2) > 0.00000000001)) {
	//	cout << sum2 << " " << recsum2 <<  " " << sum2 - recsum2 << endl;
	//	cout << recsum1 << " " << recsum2 << " " << sum1 << " " << sum2 << " == " << sig1 << " == " << sig2 << endl;
	//	system("pause");
	//	cout << "Wrong!!!!!!!!!" << endl;
	//}
	//cout << max(sum1, sum2) << endl;
	return max(sum1, sum2);
}

double TS::computeAvgV(TemporalGraph& g, int u, int v, int comm) {
	double sum1 = 0;
	int commcount1 = 0;

	//if ((*g.graph[u])[v].size() == 0)
	// 	return 0.5;

	vector<int> tstamps1;
	vector<int> tstamps2;
	vector<int> toremove;
	g.save(comm);

	for (TemporalEdge& e : g.in_edges[comm]) {
		if (e.rel1 != u && e.rel2 != u) {
			tstamps1.push_back(e.t);
		}
		else {
			g.removeT_actual(comm, e.t);
		}

		if (e.rel1 != v && e.rel2 != v) {
			tstamps2.push_back(e.t);
		}
		else {
			toremove.push_back(e.t);
		}
	}

	int sz = tstamps1.size();
	for (int i = 0; i < sz; ++i) {
		int cur_t = tstamps1[i];
		sum1 += SVs(g, cur_t, comm);
		//tstamps1.erase(tstamps1.begin());
		//sum1 += SV(cur_t, tstamps1);
		commcount1++;
	}

	if (commcount1 >= 1) {
		sum1 = sum1 / (double)commcount1;
	}
	else
		sum1 = 0.5;

	double sum2 = 0;
	int commcount2 = 0;

	g.load(comm);
	g.save(comm);
	for (const auto& t : toremove) {
		g.removeT_actual(comm, t);
	}

	sz = tstamps2.size();
	for (int i = 0; i < sz; ++i) {
		int cur_t = tstamps2[i];
		sum2 += SVs(g, cur_t, comm);
		//tstamps2.erase(tstamps2.begin());
		//sum2 += SV(cur_t, tstamps2);
		commcount2++;
	}

	g.load(comm);

	if (commcount2 >= 1) {
		sum2 = sum2 / (double)commcount2;
	}
	else
		sum2 = 0.5;
	
	return max(sum1, sum2);
}

double TS::computeAvgV(TemporalGraph& g, int u, int v, int comm, int node, bool add) {
	double sum1 = 0;
	double sum2 = 0;
	int commcount1 = 0;
	bool hassum1 = false;
	bool hassum2 = false;

	//if ((*g.graph[u])[v].size() == 0)
	// 	return 0.5;

	vector<int> tstamps1;
	vector<int> tstamps2;
	vector<int> toremove;

	if (g.expect_index.find(u) != g.expect_index.end()) {
		sum1 = g.expect_index[u];
		hassum1 = true;
	}
	if (g.expect_index.find(v) != g.expect_index.end()) {
		sum2 = g.expect_index[v];
		hassum2 = true;
	}

	if (hassum1 && hassum2) {
		//cout << max(sum1, sum2) << endl;
		return max(sum1, sum2);
	}

	if(!hassum1) {
		g.save(comm);
	}

	for (const auto& e : g.in_edges[comm]) {
		if (!add && (e.rel1 == node || e.rel2 == node))
			continue;

		if (!hassum1) {
			if (e.rel1 != u && e.rel2 != u) {
				tstamps1.push_back(e.t);
			}
			else {
				g.removeT_actual(comm, e.t);
			}
		}
	
		if (!hassum2) {
			if (e.rel1 != v && e.rel2 != v) {
				tstamps2.push_back(e.t);
			}
			else {
				toremove.push_back(e.t);
			}
		}
	}

	if (!hassum1) {
		int sz = tstamps1.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps1[i];
			sum1 += SVs(g, cur_t, comm);
			//tstamps1.erase(tstamps1.begin());
			//sum1 += SV(cur_t, tstamps1);
			commcount1++;
		}

		if (commcount1 >= 1) {
			sum1 = sum1 / (double)commcount1;
		}
		else
			sum1 = 0.5;

		g.expect_index[u] = sum1;
		g.load(comm);
	}

	//double sum2 = 0;
	int commcount2 = 0;

	if (!hassum2) {
		g.save(comm);

		for (const auto& t : toremove) {
			g.removeT_actual(comm, t);
		}

		int sz = tstamps2.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps2[i];
			sum2 += SVs(g, cur_t, comm);
			//tstamps2.erase(tstamps2.begin());
			//sum2 += SV(cur_t, tstamps2);
			commcount2++;
		}

		g.load(comm);

		if (commcount2 >= 1) {
			sum2 = sum2 / (double)commcount2;
		}
		else
			sum2 = 0.5;
	
		g.expect_index[v] = sum2;
	}

	//cout << max(sum1, sum2) << endl;
	return max(sum1, sum2);
}

/*
double TS::computeAvgExV(GraphInfo& g, int u, int v, int comm) {
	double sum = 0;
	int commcount = 0;
	if ((*g.graph[u])[v].size() == 0)
		return 1;
	for (const auto& c : g.communities) {
		if(c.second.size() != 0) {
			int community = c.first;
			multiset<int> tset(g.instamp[community]);

			if (community != comm) {
				bool connected = false;
				for (const auto& t : (*g.graph[u])[v]) {
					tset.insert(t);
				}

				for (const auto& n : c.second) {
					if (n == u || n == v) {
						connected = true;
						continue;
					}
					if (g.graph[n] != NULL
						&& g.graph[n]->find(u) != g.graph[n]->end()
						&& !(*g.graph[n])[u].empty()) {
						connected = true;
						for (const auto& t : (*g.graph[n])[u]) {
							tset.insert(t);
						}
					}
					if (g.graph[n] != NULL
						&& g.graph[n]->find(v) != g.graph[n]->end()
						&& !(*g.graph[n])[v].empty()) {
						connected = true;
						for (const auto& t : (*g.graph[n])[v]) {
							tset.insert(t);
						}
					}
				}
				
				if (!connected)
					continue;
			}		

			commcount++;

			for (const auto& t : (*g.graph[u])[v]) {
				sum += SV(t, tset);
			}
		}
	}

	// sum += 0.5 * (*g.graph[u])[v].size();
	// commcount++;

	if (commcount >= 1)
		sum = sum / ((double)commcount * (*g.graph[u])[v].size());
	else
		sum = 0;
	// cout << sum << endl;
	return sum;
}
*/

double TS::computeExpV(TemporalGraph& g, int c) {
	if (g.inedge[c] == 0 || g.inedge[c] == 1) {
		return 0;
	}

	int m = g.inedge[c];
	
	double ans = 0.0;
	vector<int>* comm = &g.communities[c];
	double partial = 0.0;

	for (int i1 = 0; i1 < comm->size(); ++i1) {
		int n1 = (*comm)[i1];
		for(const auto& t : g.sum_t_vertex[n1]) {
			partial += t * t;
		}
		ans = ans + partial * g.indegree[n1] / (double)g.sum_t_vertex[n1].size();
		partial = 0;
	}
	ans = (1.0 / (2.0 * m) - 1.0 / (4.0 * m * m)) * ans;

	partial = 0;
	for (int i1 = 0; i1 < comm->size(); ++i1) {
		int n1 = (*comm)[i1];
		int n1size = g.sum_t_vertex[n1].size();

		for (int j1 = 0; j1 < n1size; ++j1) {
			int t1 = g.sum_t_vertex[n1][j1];

			for (int j2 = j1 + 1; j2 < n1size; ++j2) {
				int t2 = g.sum_t_vertex[n1][j2];
		
				partial = partial + 2 * t1 * t2 * (double)(g.indegree[n1] * (g.indegree[n1] - 1)) / (n1size * (n1size - 1));
			}

			for(int i2 = i1 + 1; i2 < comm->size(); ++i2) {
				int n2 = (*comm)[i2];

				int n2size = g.sum_t_vertex[n2].size();
				for (int j2 = 0; j2 < n2size; ++j2) {
					int t2 = g.sum_t_vertex[n2][j2];

					partial = partial + 2 * t1 * t2 * (double)(g.indegree[n1] * g.indegree[n2]) / (n1size * n2size);
				}
			}
		}
	}

	ans = ans - (1.0 / (4.0 * m * m)) * partial;

	return ans;
}

double TS::computeExpVwoE(TemporalGraph& g, int c, int u, int v) {
	if (g.inedge[c] == 0 || g.inedge[c] == 1) {
		return 0;
	}

	g.inedge[c]--;
	g.indegree[u]--;

	if(u != v)
		g.indegree[v]--;
	
	int m = g.inedge[c];

	double ans = 0.0;
	vector<int>* comm = &g.communities[c];
	double partial = 0.0;

	for (int i1 = 0; i1 < comm->size(); ++i1) {
		int n1 = (*comm)[i1];
		for(const auto& t : g.sum_t_vertex[n1]) {
			partial += t * t;
		}
		ans = ans + partial * g.indegree[n1] / (double)g.sum_t_vertex[n1].size();
		partial = 0;
	}
	ans = (1.0 / (2.0 * m) - 1.0 / (4.0 * m * m)) * ans;

	partial = 0;
	for (int i1 = 0; i1 < comm->size(); ++i1) {
		int n1 = (*comm)[i1];
		int n1size = g.sum_t_vertex[n1].size();

		for (int j1 = 0; j1 < n1size; ++j1) {
			int t1 = g.sum_t_vertex[n1][j1];

			for (int j2 = j1 + 1; j2 < n1size; ++j2) {
				int t2 = g.sum_t_vertex[n1][j2];
		
				partial = partial + 2 * t1 * t2 * (double)(g.indegree[n1] * (g.indegree[n1] - 1)) / (n1size * (n1size - 1));
			}

			for(int i2 = i1 + 1; i2 < comm->size(); ++i2) {
				int n2 = (*comm)[i2];

				int n2size = g.sum_t_vertex[n2].size();
				for (int j2 = 0; j2 < n2size; ++j2) {
					int t2 = g.sum_t_vertex[n2][j2];

					partial = partial + 2 * t1 * t2 * (double)(g.indegree[n1] * g.indegree[n2]) / (n1size * n2size);
				}
			}
		}
	}

	ans = ans - (1.0 / (4.0 * m * m)) * partial;

	g.inedge[c]++;
	g.indegree[u]++;

	if(u != v)
		g.indegree[v]++;

	return ans;
}

double TS::SExpV(TemporalGraph& g, int comm, int u, int v) {
	double v1 = computeExpV(g, comm);
	double v2 = computeExpVwoE(g, comm, u, v);

	double delta = v1 - v2;
	// cout << "delta: " << delta << " " << u << " " << v << " " << comm << endl;
	if (delta > 0) {
		// cout << delta << " " << 1 - 1.0 / (2 + log(delta + 1)) << endl;
		// return 1 - 0.5 * exp(-delta);
		return 1 - 1.0 / (2 + log(delta + 1));
	}
	else {
		// cout << delta << " " << 1.0 / (2 + log(1 - delta)) << endl;
		// return 0.5 * exp(delta);
		return 1.0 / (2 + log(1 - delta));
	}
}

double TS::computeV(vector<int>& timestamp) {
	if (timestamp.size() <= 1) 
		return 0;

	double sum = 0;
	for (const auto& t : timestamp) {
		sum += t;
	}
	double mean = sum / (double)timestamp.size();

	double accum = 0.0;
	for (const auto& t : timestamp) {
		accum += (t - mean) * (t - mean);
	}

	double stdev = sqrt(accum / ((double)(timestamp.size())));

	return stdev;
}

double TS::SV(TemporalGraph& g, int t, int comm) {
	double ev1 = g.getStd(comm, t);
	double ev2 = g.addT(comm, t);
	double delta = ev2 - ev1;

	double metric = 1.0 / (double)(1 + log(0.05 * ev2 + 1));
	// cout << ev2 << " " << metric << endl;
	if (delta > 0) {
		// return 1 - 0.5 * exp(-delta);
		// cout << delta << " " << 1.0 / (1 + log(0.05 * delta + 1)) << endl;
		return metric * 1.0 / (2 + log(0.05 * delta + 1));
	}
	else if (delta <= 0){
		// return 0.5addn * exp(delta);
		// cout << delta << " "<<  (2 - 1.0 / (1 + log(1 - 0.05 * delta))) << endl;
		return metric * (1 - 1.0 / (2 + log(1 - 0.05 * delta)));
	}
}

double TS::computeScore(TemporalGraph& g, double ev2) {
	//both
	/*if (ev2 <= g.th_beta)
		return 1;
	else
		return (double) (g.th_ev2 - g.th_beta) / (ev2 + g.th_ev2 - 2 * g.th_beta);*/

	//t1only
	//return (double) 1.0 / (1 + max(0.0, ev2 - g.th_beta));

	// trivial
	//if (ev2 == 0)
	//	return 1;
	//return (double) 1.0 / (ev2 + 1);

	//return 1;
	//cout << "ALPHA_T: " << g.th_alpha << endl;
	if (ev2 <= g.th_beta)
		return 1;
	double metric = 1.0 / (double)(1 + log(g.th_alpha * (ev2 - g.th_beta) + 1));
	return metric;
}

double TS::computeTopoScore(TemporalGraph& g, double ev2) {
	//both
	/*if (ev2 <= g.th_topo_half)
		return (double) (0.5 * ev2) / g.th_topo_half;
	else if (ev2 >= g.th_topo_beta)
		return 1;
	else
		return (double) (0.5 * (ev2 - g.th_topo_half)) / (g.th_topo_beta - g.th_topo_half) + 0.5;*/

	//t1only
	//return min(1.0, (double)ev2 / g.th_topo_beta);

	//trivial
	//return ev2;
	
	//return 1;
	//cout << "ALPHA_TOPO: " << g.th_topo_alpha << endl;
	if (ev2 >= g.th_topo_beta)
		return 1;
	double metric = 1.0 / (double)(1 + log(g.th_topo_alpha * (g.th_topo_beta - ev2) + 1));
	
	return metric;
}

double TS::computeIOScore(TemporalGraph& g, double ev2) {
	/*if (ev2 <= g.th_io_half)
		return (double) (0.5 * ev2) / g.th_io_half;
	else if (ev2 >= g.th_io_beta)
		return 1;
	else
		return (double) (0.5 * (ev2 - g.th_io_half)) / (g.th_io_beta - g.th_io_half) + 0.5;*/

	//t1only
	//return min(1.0, (double)ev2 / g.th_io_beta);

	//trivial
	//return ev2;
	
	//return 1;
	//cout << "ALPHA_IO: " << g.th_io_alpha << endl;
	if (ev2 >= g.th_io_beta)
		return 1;
	double metric = 1.0 / (double)(1 + log(g.th_io_alpha * (g.th_io_beta - ev2) + 1));
	
	return metric;
}

double TS::SVs(TemporalGraph& g, vector<int>& timestamps) {
	double ev2 = computeV(timestamps);
	//double ev1 = g.removeT(comm, t);
	//double delta = ev2 - ev1;

	double alpha = g.th_alpha;
	double beta = 0.05;

	return computeScore(g, ev2);
	//if (ev2 <= g.th_beta)
	//	return 1;
	//double metric = 1.0 / (double)(1 + log(alpha * (ev2 - g.th_beta) + 1));
	//double metric = 1.0 / (double)(1 + log(alpha * ev2 + 1));
	//return metric;
	//return metric / (1 + log(1 + beta * abs(delta)));
	// cout << ev2 << " " << metric << endl;
	//if (delta > 0) {
		// return 1 - 0.5 * exp(-delta);
		// cout << delta << " " << 1.0 / (1 + log(0.05 * delta + 1)) << endl;
	//	return metric * 1.0 / (1 + log(beta * delta + 1));
	//}
	//else if (delta <= 0){
	//	return metric;
		// return 0.5addn * exp(delta);
		// cout << delta << " "<<  (2 - 1.0 / (1 + log(1 - 0.05 * delta))) << endl;
		//return metric * (1 - 1.0 / (2 + log(1 - 0.05 * delta)));
	//}
}

double TS::SVs(TemporalGraph& g, int t, int comm) {
	double ev2 = g.getStd(comm, t);
	//double ev1 = g.removeT(comm, t);
	//double delta = ev2 - ev1;

	double alpha = g.th_alpha;
	double beta = 0.05;

	double metric = 1.0 / (double)(1 + log(alpha * ev2 + 1));
	return metric;
	//return metric / (1 + log(1 + beta * abs(delta)));
	// cout << ev2 << " " << metric << endl;
	//if (delta > 0) {
		// return 1 - 0.5 * exp(-delta);
		// cout << delta << " " << 1.0 / (1 + log(0.05 * delta + 1)) << endl;
	//	return metric * 1.0 / (1 + log(beta * delta + 1));
	//}
	//else if (delta <= 0){
	//	return metric;
		// return 0.5addn * exp(delta);
		// cout << delta << " "<<  (2 - 1.0 / (1 + log(1 - 0.05 * delta))) << endl;
		//return metric * (1 - 1.0 / (2 + log(1 - 0.05 * delta)));
	//}
}


double TS::SV(int t, vector<int>& timestamp) {
	double ev1 = computeV(timestamp);
	timestamp.push_back(t);

	double ev2 = computeV(timestamp);

	double delta = ev2 - ev1;

	double metric = 1.0 / (double)(1 + log(0.05 * ev2 + 1));
	// cout << ev2 << " " << metric << endl;
	if (delta > 0) {
		// return 1 - 0.5 * exp(-delta);
		// cout << delta << " " << 1.0 / (1 + log(0.05 * delta + 1)) << endl;
		return metric * 1.0 / (1 + log(0.05 * delta + 1));
	}
	else if (delta <= 0){
		return metric;
		// return 0.5addn * exp(delta);
		// cout << delta << " "<<  (2 - 1.0 / (1 + log(1 - 0.05 * delta))) << endl;
		//return metric * (1 - 1.0 / (2 + log(1 - 0.05 * delta)));
	}

	/*if (delta < 0) {
		// return 1 - 0.5 * exp(-delta);
		return 1 - 1.0 / (2 + log(1 - delta));
	}
	else {
		// return 0.5 * exp(delta);
		return 1.0 / (2 + log(1 + delta));
	}*/
}

void TS::randomSelect(vector<int>& timestamp, int k) {
	srand(unsigned(time(NULL)));
	random_shuffle(timestamp.begin(), timestamp.end());
	timestamp.resize(k);
}

double TS::S(int t1, int t2, int t_max, int t_min,  double t_avg) {
	if (t_max != t_min) {
		//cout << t_max << " " << t_min << " " << t1 << " " << t2 << endl;
		return 1 - abs(t1 - t2) / (double)(t_max - t_min);
	}
	else
		return 1;
}

double TS::Ssin(int t1, int t2, int t_max, int t_min, double t_avg) {
	if (t_max != t_min) {
		double d = max(abs(t_avg - t_min), abs(t_max - t_avg));
		double ts = t_avg - d;
		double t_gap = t_max - t_min;
		double val1 = 2 * ((double)t1 - ts) / (double)(2 * d) - 1;
		double val2 = 2 * ((double)t2 - ts) / (double)(2 * d) - 1;
		double val = abs(0.5 * val1 * val1 * val1 - 0.5 * val2 * val2 * val2);
		// if (abs(val) > 1)
		//	cout << "S: " << " " << t1 << " " << t2 << " " << t_max << " " << t_min << " " << t_avg << " " << val1 << " " << val2 << endl;
		return 1 - abs(val);
	}
	else
		return 1;
}

double TS::computeTS(TemporalGraph& g) {
	double avg_factor = 2 * g.t_edge_num;

	double ts = 0.0;
	for (auto& comm : g.communities) {
		if (comm.second.empty()) {
			continue;
		}

		vector<int> tstamps;

		double avg_t = 0;
		int edgenum = 0;
		int maxtime = -1;
		int mintime = -1;

		for (const auto& e : g.in_edges[comm.first]) {
			tstamps.push_back(e.t);
		}

		if (g.in_edges[comm.first].empty()) {
			continue;
		}
		// avg_t = avg_t / (double)edgenum;
		sort(comm.second.begin(), comm.second.end());
		for (int i1 = 0; i1 < comm.second.size(); ++i1) {
			int n1 = comm.second[i1];
			for (int i2 = i1 + 1; i2 < comm.second.size(); ++i2) {
				int n2 = comm.second[i2];	
				ts -= g.degree[n1] * g.degree[n2] * computeAvgV(g, n1, n2, comm.first, -1, true) / avg_factor;
			}
		}

		for (const auto& n : comm.second) {
			if (g.graph[n] != NULL && g.graph[n]->find(n) != g.graph[n]->end()) {				
				ts -= g.degree[n] * g.degree[n] * computeAvgV(g, n, n, comm.first, -1, true) / avg_factor;
				// ts = ts - g.degree[n] * g.degree[n] * S((g.sum_t_vertex[n] + g.sum_t_vertex[n]) / (g.degree[n] + g.degree[n]), avg_t, maxtime, mintime, avg_t) / avg_factor;
			}
		}

		g.expect_index.clear();

		int sz = tstamps.size();
		for (int i = 0; i < sz; ++i) {
			int cur_t = tstamps[i];
			//int cur_t = tstamps[0];
			//tstamps.erase(tstamps.begin());
			
			//ts += SV(cur_t, tstamps);
			ts += SVs(g, cur_t, comm.first);
		}
	}

	ts = ts / (double)avg_factor;
	return ts;
}

double TS::addN2CTSFake(int node, int comm, int fromcomm, TemporalGraph& g) {
	double avg_factor = 2 * g.t_edge_num;

	double ts = 0.0;
	double avg_t = 0.0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;

	//list<int> tstamps;
	int ori_sz = g.in_edges[comm].size();

	//int record = g.indegree[node];
	//g.indegree[node] = 0;
	
	/*if (g.communities.find(comm) != g.communities.end()) {
		for (auto& e : g.in_edges[comm]) {
			tstamps.push_back(e.t);
		}
	}*/

	g.save(comm);
	for (const auto& n2 : g.communities[comm]) {
		if (g.graph[node]->find(n2) != g.graph[node]->end()) {
			for (const auto& t : (*g.graph[n2])[node]) {
				g.addT_actual(comm, t);
				g.in_edges[comm].push_back(TemporalEdge(node, n2, t));
			}
			//tstamps.insert(tstamps.end(), (*g.graph[node])[n2].begin(), (*g.graph[node])[n2].end());
		}
	}

	if (g.graph[node]->find(node) != g.graph[node]->end()) {
		for (const auto& t : (*g.graph[node])[node]) {
			g.addT_actual(comm, t);
			g.in_edges[comm].push_back(TemporalEdge(node, node, t));
		}
		//tstamps.insert(tstamps.end(), (*g.graph[node])[node].begin(), (*g.graph[node])[node].end());
	}
	//avg_t = avg_t / (double)edgenum;
	
	//int sz = tstamps.size();
	for (const auto& e : g.in_edges[comm]) {
		int cur_t = e.t;
		//int cur_t = tstamps[i];
		//tstamps.erase(tstamps.begin());
		//ts += SV(cur_t, tstamps);

		ts += SVs(g, cur_t, comm);
	}
	
	g.communities[comm].push_back(node);
	//auto it = std::find(g.communities[fromcomm].begin(), g.communities[fromcomm].end(), node);

	//if (it != g.communities[fromcomm].end())
	//	g.communities[fromcomm].erase(it);

	// cout << "ADD: " << g.communities[comm].size() << " " << g.in_edges[comm].size() << endl;
	for (int i1 = 0; i1 < g.communities[comm].size(); ++i1) {
		int n1 = g.communities[comm][i1];
		for (int i2 = i1 + 1; i2 < g.communities[comm].size(); ++i2) {
			int n2 = g.communities[comm][i2];
			ts -= g.degree[n1] * g.degree[n2] * computeAvgV(g, n1, n2, comm, node, true) / avg_factor;
		}
	}
	//cout << "STEP 1" << endl;
	for (const auto& n : g.communities[comm]) {
		if (g.graph[n] != NULL && g.graph[n]->find(n) != g.graph[n]->end()) {
			ts -= g.degree[n] * g.degree[n] * computeAvgV(g, n, n, comm, node, true) / avg_factor;
		}
	}

	g.expect_index.clear();

	g.in_edges[comm].resize(ori_sz);
	//cout << "STEP 2" << endl;
	g.load(comm);

	g.communities[comm].pop_back();
	//g.communities[fromcomm].push_back(node);
	ts = ts / (double)avg_factor;

	/*for (const auto& n2 : g.communities[comm]) {
		if (g.graph[node]->find(n2) != g.graph[node]->end()) {
			int s = (*g.graph[node])[n2].size();
			g.inedge[comm] -= s;
			g.indegree[n2] -= s;
		}
	}

	if (g.graph[node]->find(node) != g.graph[node]->end()) {
		int s = (*g.graph[node])[node].size();
		g.inedge[comm] -= s;
	}

	g.indegree[node] = record;*/

	return ts;
}

double TS::removeN2CTSFake(int node, int comm, int tocomm, TemporalGraph& g) {
	double avg_factor = 2 * g.t_edge_num;

	double ts = 0.0;
	double avg_t = 0;
	int maxtime = -1;
	int mintime = -1;

	vector<int> tstamps;

	g.save(comm);
	if (g.communities.find(comm) != g.communities.end()) {
		int edgenum = 0;
		for (const auto& e : g.in_edges[comm]) {
			if (e.rel1 == node || e.rel2 == node) {
				g.removeT_actual(comm, e.t);
			}
			else {
				tstamps.push_back(e.t);
			}
		}
		
		if (tstamps.empty()) {
			g.load(comm);
			return 0;
		}

		//avg_t = avg_t / (double)edgenum;
	}
	else {
		g.load(comm);
		return 0;
	}

	int sz = tstamps.size();
	for (int i = 0; i < sz; ++i) {
		int cur_t = tstamps[i];
		//tstamps.erase(tstamps.begin());
		//ts += SV(cur_t, tstamps);

		ts += SVs(g, cur_t, comm);
	}

	auto it = std::find(g.communities[comm].begin(), g.communities[comm].end(), node);

	if (it != g.communities[comm].end()) {
		g.communities[comm].erase(it);
	}

	//g.communities[tocomm].push_back(node);

	/*for (int i = 0; i < g.communities[comm].size(); ++i) {
		int n1 = g.communities[comm][i];
		if (g.graph[n1] != NULL
			&& g.graph[n1]->find(node) != g.graph[n1]->end()) {
			g.indegree[n1] -= (*g.graph[n1])[node].size();
			g.inedge[comm] -= (*g.graph[n1])[node].size();
		}
	}
	if(g.graph[node] != NULL
		&& g.graph[node]->find(node) != g.graph[node]->end()) {
		g.inedge[comm] -= (*g.graph[node])[node].size();
	}*/

	for (int i1 = 0; i1 < g.communities[comm].size(); ++i1) {
		int n1 = g.communities[comm][i1];
		if (n1 == node)
			continue;
		for (int i2 = i1 + 1; i2 < g.communities[comm].size(); ++i2) {
			int n2 = g.communities[comm][i2];
			if (n2 == node)
				continue;

			ts -= g.degree[n1] * g.degree[n2] * computeAvgV(g, n1, n2, comm, node, false) / avg_factor;
		}
	}

	for (const auto& n : g.communities[comm]) {
		if (n == node)
			continue;
		if (g.graph[n] != NULL && g.graph[n]->find(n) != g.graph[n]->end()) {
			ts -= g.degree[n] * g.degree[n] * computeAvgV(g, n, n, comm, node, false) / avg_factor;
		}
	}

	g.expect_index.clear();

	/*for (int i = 0; i < g.communities[comm].size(); ++i) {
		int n1 = g.communities[comm][i];
		if (g.graph[n1] != NULL
			&& g.graph[n1]->find(node) != g.graph[n1]->end()) {
			g.indegree[n1] += (*g.graph[n1])[node].size();
			g.inedge[comm] += (*g.graph[n1])[node].size();
		}
	}
	if(g.graph[node] != NULL
		&& g.graph[node]->find(node) != g.graph[node]->end()) {
		g.inedge[comm] += (*g.graph[node])[node].size();
	}*/

	g.load(comm);
	g.communities[comm].push_back(node);
	//g.communities[tocomm].pop_back();

	ts = ts / (double)avg_factor;
	return ts;
}

void TS::moveTS(int node, int comm, double rectsto, double rectsfrom, TemporalGraph& g) {
	int ori_comm = g.comm_map[node];
	g.comm_ts[comm] = rectsto;
	g.comm_ts[ori_comm] = rectsfrom;

	g.indegree[node] = 0;

	g.communities[comm].push_back(node);
	for (const auto& n2 : g.communities[comm]) {
		if (g.graph[node]->find(n2) != g.graph[node]->end()) {
			for (const auto& t : (*g.graph[node])[n2]) {
				g.addT_actual(comm, t);
				g.in_edges[comm].push_back(TemporalEdge(node, n2, t));
			}
		}
	}

	for (const auto& n2 : g.communities[ori_comm]) {
		if (g.graph[node]->find(n2) != g.graph[node]->end()) {
			for (const auto& t : (*g.graph[node])[n2]) {
				g.removeT_actual(ori_comm, t);
			}
		}
	}

	for(vector<TemporalEdge>::iterator it = g.in_edges[ori_comm].begin(); it != g.in_edges[ori_comm].end();) {
		if(it->rel1 == node || it->rel2 == node) {
            it = g.in_edges[ori_comm].erase(it);
		}
        else {
			++it;
		}
    }

	auto it = std::find(g.communities[ori_comm].begin(), g.communities[ori_comm].end(), node);

	if (it != g.communities[ori_comm].end()) {
		g.communities[ori_comm].erase(it);
		//if (g.communities[ori_comm].empty()) {
		//	g.communities.erase(ori_comm);
		//}
	}
	
	g.comm_map[node] = comm;

	cout << "NODE " << node << "is moved to COMMUNITY" << comm << endl;

	/*double sum = 0;
	for (const auto& comm : g.communities) {
		if (g.comm_ts.find(comm.first) != g.comm_ts.end()) {
			sum += g.comm_ts[comm.first];
		}
	}
	cout << "P: " << " |  " << computeTS(g) << " " << sum << endl;*/
}

double TS::computeCommTS(int comm, TemporalGraph& g) {
	double avg_factor = 2 * g.t_edge_num;

	double ts = 0.0;
	double avg_t = 0;
	int edgenum = 0;
	int maxtime = -1;
	int mintime = -1;

	vector<int> tstamps;

	if (g.communities.find(comm) == g.communities.end() 
		|| g.communities[comm].size() == 0)
		return 0;

	g.save(comm);
	for (const auto& e : g.in_edges[comm]) {
		tstamps.push_back(e.t);
	}
		
	if (tstamps.empty()) {
		g.load(comm);
		return 0;
	}

	// avg_t = avg_t / (double)edgenum;

	for (int i1 = 0; i1 < g.communities[comm].size(); ++i1) {
		int n1 = g.communities[comm][i1];
		for (int i2 = i1 + 1; i2 < g.communities[comm].size(); ++i2) {
			int n2 = g.communities[comm][i2];
			ts -= g.degree[n1] * g.degree[n2] * computeAvgV(g, n1, n2, comm, -1, true) / avg_factor;
		}
	}

	for (const auto& n : g.communities[comm]) {
		if (g.graph[n] != NULL && g.graph[n]->find(n) != g.graph[n]->end()) {
			ts -= g.degree[n] * g.degree[n] * computeAvgV(g, n, n, comm, -1, true) / avg_factor;
		}
	}

	g.expect_index.clear();

	int sz = tstamps.size();
	for (int i = 0; i < sz; ++i) {
		int cur_t = tstamps[i];
		//int cur_t = tstamps[0];
		//tstamps.erase(tstamps.begin());
			
		//ts += SV(cur_t, tstamps);
		ts += SVs(g, cur_t, comm);
	}

	ts = ts / (double)avg_factor;
	return ts;
}

bool TS::traverseTS(TemporalGraph& g) {
	bool once_updated = false;
    bool updated = true;

    int part_num = 0;

	g.communities[0] = vector<int>();
    while(updated) {
        updated = false;

        double sum = 0;
		for (const auto& comm : g.communities) {
			if (g.comm_ts.find(comm.first) != g.comm_ts.end()) {
				sum += g.comm_ts[comm.first];
			}
		}

        cout << "P: " << part_num << " |  " << computeTS(g) << " " << sum << endl;
        part_num += 1;

		//if (part_num > 1)
		//	g.debug = true;

		for (int v = 1; v <= g.nodenum; ++ v) {
            int ori_comm = g.comm_map[v];
            unordered_set<int> clist;

            if (g.comm_ts.find(ori_comm) == g.comm_ts.end())
                g.comm_ts[ori_comm] = 0;

            if (g.graph[v] != NULL){
                for (const auto& np : *g.graph[v]) {
					int n2 = np.first;
                    if (g.comm_map[n2] != ori_comm)
                        clist.insert(g.comm_map[n2]);
				}
			}

			if (g.communities[ori_comm].size() > 1) {
				for (const auto& c : g.communities) {
					if (c.second.size() == 0) {
						clist.insert(c.first);
						break;
					}
				}
			}

            double maxdelta = 0;
            double reccomm = -1;
            double rectsfrom = -1;
            double rectsto = -1;
			double tsfrom = -1;
			
			if (!clist.empty()) {
				if(g.debug)
					cout << "Before Removing" << endl;
				tsfrom = removeN2CTSFake(v, ori_comm, -1, g);
			}

            for (const auto& comm : clist) {
				/*unordered_map<int, multiset<int>> recordstamp(g.instamp);
				for (int i = 0; i < g.communities[comm].size(); ++i) {
					int n1 = g.communities[comm][i];
					if (g.graph[n1] != NULL
						&& g.graph[n1]->find(v) != g.graph[n1]->end()) {
						g.instamp[comm].insert((*g.graph[n1])[v].begin(), (*g.graph[n1])[v].end());
					}
				}
				if(g.graph[v] != NULL
					&& g.graph[v]->find(v) != g.graph[v]->end()) {
					g.instamp[comm].insert((*g.graph[v])[v].begin(), (*g.graph[v])[v].end());

					for (const auto& t : (*g.graph[v])[v]) {
						auto it = std::find(g.instamp[ori_comm].begin(), g.instamp[ori_comm].end(), t);

						if (it != g.instamp[ori_comm].end())
							g.instamp[ori_comm].erase(it);
					}
				}

				for (int i = 0; i < g.communities[ori_comm].size(); ++i) {
					int n1 = g.communities[ori_comm][i];
					if (g.graph[n1] != NULL
						&& g.graph[n1]->find(v) != g.graph[n1]->end()) {
						
						for (const auto& t : (*g.graph[n1])[v]) {
							auto it = std::find(g.instamp[ori_comm].begin(), g.instamp[ori_comm].end(), t);

							if (it != g.instamp[ori_comm].end())
								g.instamp[ori_comm].erase(it);
						}
					}
				}*/
				
				if(g.debug)
					cout << "Before Adding" << endl;
				double tsto = addN2CTSFake(v, comm, ori_comm, g);
				
				if(g.debug)
					cout << "Before Moving" << endl;

				if (g.comm_ts.find(comm) == g.comm_ts.end())
                    g.comm_ts[comm] = 0;

                double delta1 = tsto - g.comm_ts[comm];
                double delta2 = tsfrom - g.comm_ts[ori_comm];
                double delta = delta1 + delta2;
                if (delta > maxdelta) {
                    maxdelta = delta;
                    reccomm = comm;
                    rectsto = tsto;
                    rectsfrom = tsfrom;
				}

				// g.instamp = recordstamp;
			}

            if (maxdelta > 0) {
                updated = true;
                once_updated = true;
                moveTS(v, reccomm, rectsto, rectsfrom, g);
			}
		}
	}
	
	return once_updated;
}

void TS::detectTS(TemporalGraph& g) {
	int iter_num = 10;

    int count = 0;
	bool once_updated = true;
	double max_sum = 0;

    while (count < iter_num) {
        cout << "Iteration " << " "<< count << endl;
        count += 1;
        once_updated = traverseTS(g);

		double sum = 0;
		for (const auto& comm : g.communities) {
			if (g.comm_ts.find(comm.first) != g.comm_ts.end()) {
				sum += g.comm_ts[comm.first];
			}
		}
		if (sum > max_sum) {
			g.best_comm_map = g.comm_map;
			g.bestVal = sum;
			max_sum = sum;
		}

        if (!once_updated)
            break;

		TemporalGraph c_graph;
        CGU.buildCommGraph(g, c_graph);

		for (const auto& comm : c_graph.communities) {
			for (const auto& n : comm.second) {
				if (c_graph.graph[n] != NULL
					&& c_graph.graph[n]->find(n) != c_graph.graph[n]->end()) {
						for (const auto& t : (*c_graph.graph[n])[n]) {
							c_graph.addT_actual(comm.first, t);
							c_graph.in_edges[comm.first].push_back(TemporalEdge(n, n, t));
						}
				}
			}
			c_graph.comm_ts[comm.first] = computeCommTS(comm.first, c_graph);
		}

		// c_graph.debug = true;
        once_updated = traverseTS(c_graph);
        if (!once_updated) {
            break;
		}

		sum = 0;
        CGU.convertCommGraph(g, c_graph);
		g.in_edges.clear();
		for (const auto& comm : g.communities) {
			for (int i1 = 0; i1 < g.communities[comm.first].size(); ++i1) {
				int n1 = g.communities[comm.first][i1];
				for (int i2 = i1; i2 < g.communities[comm.first].size(); ++i2) {
					int n2 = g.communities[comm.first][i2];
					if (g.graph[n1] != NULL
						&& g.graph[n1]->find(n2) != g.graph[n1]->end()) {
						for (const auto& t : (*g.graph[n1])[n2]) {
							g.in_edges[comm.first].push_back(TemporalEdge(n1, n2, t));
						}
					}
				}
			}
		}

        for (const auto& comm : g.communities) {
			g.comm_ts[comm.first] = computeCommTS(comm.first, g);
			sum += g.comm_ts[comm.first];
		}

		if (sum > max_sum) {
			g.best_comm_map = g.comm_map;
			g.bestVal = sum;
			max_sum = sum;
		}
	}

    cout << once_updated << endl;
}

void TS::printTS(TemporalGraph& g) {
    cout << "TS: " << g.bestVal << endl;

    int nmax = -1;
    unordered_map<int, int> ori_comm_map;
	for(int n = 1; n <= g.nodenum; ++n) {
		ori_comm_map[g.rev_mapper[n]] = g.comm_map[n];
		nmax = max(nmax, g.rev_mapper[n]);
	}

    int index = 1;
    unordered_map<int, int> mapper;

    for (int i = 0; i < nmax + 1; ++i) {
		if (ori_comm_map.find(i) == ori_comm_map.end())
			continue;

        if (mapper.find(g.comm_map[i]) != mapper.end())
            cout << i <<  ' ' << mapper[g.comm_map[i]] << endl;
        else {
            cout << i << ' ' << index << endl;
            mapper[g.comm_map[i]] = index;
            index += 1;
		}
	}
}

void TS::writeTS(TemporalGraph& g, string filename) {
    // double ts_val = computeTS(g);
    cout << "TS: " << g.bestVal << endl;

    int nmax = -1;
    unordered_map<int, int> ori_comm_map;
	for(int n = 1; n <= g.nodenum; ++n) {
		ori_comm_map[g.rev_mapper[n]] = g.comm_map[n];
		nmax = max(nmax, g.rev_mapper[n]);
	}

	ofstream f(filename, ios::out);
	f << "TS: " << g.bestVal << endl;

    int index = 1;
    unordered_map<int, int> mapper;

    for (int i = 0; i < nmax + 1; ++i) {
		if (ori_comm_map.find(i) == ori_comm_map.end())
			continue;

        if (mapper.find(g.comm_map[i]) != mapper.end())
            f << i <<  ' ' << mapper[g.comm_map[i]] << endl;
        else {
            f << i << ' ' << index << endl;
            mapper[g.comm_map[i]] = index;
            index += 1;
		}
	}
}