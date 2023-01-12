#include "tools.h"

void getnext(string tgt, vector<int>& next) {
	int k = -1;
	int j = 0;
	next[0] = -1;

	while (j < tgt.size()) {
		if (k == -1 || tgt[k] == tgt[j]) {
			if (tgt[++k] == tgt[++j]) {
				next[j] = next[k];
			}
			else {
				next[j] = k;
			}
		}
		else {
			k = next[k];
		}
	}
}

void replacekmp(string& str, string& src, string& tgt) {
	vector<int> next(src.size() + 1, 0);
	getnext(src, next);

	int i = 0;
	int j = 0;
	while (i < str.size()) {
		if (j == -1) {
			j = 0;
			i++;
		}
		else {
			if (str[i] == src[j]) {
				++i;
				++j;
				if (j == src.size()) {
					str = str.substr(0, i - src.size()) + tgt + str.substr(i);
					return;
				}
			}
			else {
				j = next[j];
			}
		}
	}
}
