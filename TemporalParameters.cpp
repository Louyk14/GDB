#include "TemporalParameters.h"

TemporalParameters::TemporalParameters(string filename) {
	th_score = 0;
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

	ifstream input(filename, ios::in);

	string item;
	double dval;
	int ival;
	while (input >> item) {
		if (item == "T1") {
			input >> dval;
			th_beta = dval;
		}
		else if (item == "T5") {
			input >> dval;
			th_ev2 = dval;
		}
		else if (item == "R1") {
			input >> dval;
			th_io_beta = dval;
		}
		else if (item == "R5") {
			input >> dval;
			th_io_half = dval;
		}
		else if (item == "D1") {
			input >> dval;
			th_topo_beta = dval;
		}
		else if (item == "D5") {
			input >> dval;
			th_topo_half = dval;
		}
		else if (item == "K") {
			input >> ival;
			kcore = ival;
		}
		else if (item == "SCORE") {
			input >> dval;
			th_score = dval;
		}
		else if (item == "TS") {
			input >> ival;
			t_s = ival;
		}
		else if (item == "TE") {
			input >> ival;
			t_e = ival;
		}
		else if (item == "DUR") {
			input >> ival;
			duration = ival;
		}
		else if (item == "NUM") {
			input >> ival;
			combonum = ival;
		}
		else if (item == "PHI") {
			input >> dval;
			phi = dval;
		}
		else if (item == "WWIDTH") {
			input >> ival;
			window_width = ival;
		}
		else if (item == "WSTEP") {
			input >> ival;
			window_step = ival;
		}
	}

	input.close();
}

void TemporalParameters::setPara(vector<double>& parameters) {
	if (parameters.empty())
		return;

	th_score = parameters[0];
	th_ev2 = parameters[1];
	th_beta = parameters[2];
	th_io_half = parameters[3];
	th_io_beta = parameters[4];
	kcore = parameters[5];
	th_topo_beta = parameters[6];
	th_topo_half = 1 - 1.0 / kcore;

	th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
	th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
	th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);
}