#include "Match.h"

int subgraph_matching_main()
{	
	/*string filename = "log_base.dat";
	set<map<int, int>> hasModel;
	fstream infile(filename);

	string dupfile = "dup.dat";
	ofstream outdup(dupfile);

	int dup = 0;
	while (true)
	{
	map<int, int> rt;

	for (int i = 0; i < 3; i++)
	{
	int pnode, node;
	infile >> pnode >> node;
	//cout << pnode << " " << node << endl;
	//system("pause");
	if (pnode == -1)
	{
	break;
	}
	rt[pnode] = node;
	}

	if (!rt.empty())
	{
	if (hasModel.find(rt) != hasModel.end())
	{
	for (const auto& n : rt)
	{
	outdup << n.first << " " << n.second << endl;
	}
	outdup << endl;
	//cout << rt.size() << endl;
	//if (rt.size() != 5)
	//{
	//	system("pause");
	//}
	dup++;
	}
	hasModel.insert(rt);
	}
	else
	{
	break;
	}
	}

	cout << "duplicate: " << dup << endl;
	cout << hasModel.size() << endl;
	infile.close();
	outdup.close();

	cout << "wf" << endl;
	
	filename = "log_super.dat";
	infile.open(filename);

	filename = "diff.dat";
	ofstream outfile(filename);

	int k = 0;

	while (true)
	{
		k++;
		map<int, int> rt;

		for (int i = 0; i < 3; i++)
		{
			int pnode, node;
			infile >> pnode >> node;
			//cout << pnode << " " << node << endl;
			if (pnode == -1)
			{
				break;
			}
			rt[pnode] = node;
		}

		if (!rt.empty())
		{
			if (hasModel.find(rt) == hasModel.end())
			{
				//cout << "not found" << endl;
				for (const auto& a : rt)
				{
					outfile << a.first << " " << a.second << endl;
				}

				outfile << endl;
			}
		}
		else
		{
			break;
		}
	}

	outdup.close();
	infile.close();
	outfile.close();

	system("pause");
	return 0;
	/**/
	string dataset = "brightkit///";
	string networkfile = dataset + "network.dat";
	string communityfile = dataset + "community.dat";
	string patternfile = "p3.dat";
	Match match(networkfile, communityfile, patternfile);

	match.logger << dataset + " " + patternfile + " ";
	vector<vector<int>> ans;
	//match.GoMatch_DAF();
	//match.GoMatch_DAF_comm();
	//match.GoMatch_vf3();
	//match.GoMatch_vf3_comm();
	//match.GoMatch_Turbo();
	match.GoMatch_Turbo_comm();
	cout << "finish " << endl;
	system("pause");
	return 0;
}