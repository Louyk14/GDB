#pragma once
#ifndef TEMPORALPARAMETERS_H
#define TEMPORALPARAMETERS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct TemporalParameters {
	TemporalParameters() {
		th_score = 0.5;
		th_ev2 = 0;
		th_beta = 0;
		th_io_half = 0;
		th_io_beta = 0;
		kcore = 0;
		th_topo_beta = 0;
		th_topo_half = 0;

		th_alpha = 0;
		th_topo_alpha = 0;
		th_io_alpha = 0;

		t_s = 0;
		t_e = 0;
		duration = t_e - t_s;
		combonum = 0;
		phi = 0.5;
	}
	TemporalParameters(string filename);
	TemporalParameters(double score, double ev2, double beta, double io_half, double io_beta, double coreno, double topo_half, double topo_beta, double phival) {
		th_score = score; // 0.5
		th_ev2 = ev2;
		th_beta = beta;
		th_io_half = io_half;
		th_io_beta = io_beta;
		kcore = coreno;
		th_topo_half = topo_half;
		th_topo_beta = topo_beta;

		th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
		th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
		th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);

		phi = phival;
	}
	void setPara(vector<double>& parameters);

	double th_score;
	double th_ev2;
	double th_beta;
	double th_io_half;
	double th_io_beta;
	int kcore;
	double th_topo_beta;
	double th_topo_half;

	double th_alpha;
	double th_topo_alpha;
	double th_io_alpha;

	int t_s;
	int t_e;
	int duration;
	int combonum;
	double phi;

	int window_width;
	int window_step;
};

#endif