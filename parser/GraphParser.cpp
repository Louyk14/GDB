#include "GraphParser.h"

GraphParser::GraphParser() {
	history = "";
}

Statement GraphParser::parse(string query) {
    ANTLRInputStream inputStream(query);
    GraphDBLexer lexer(&inputStream);
    CommonTokenStream tokens(&lexer);
    GraphDBParser parser(&tokens);
    MyGraphVisitor visitor;
	
	GraphDBParser::StatementContext *a = parser.statement();
    antlrcpp::Any ans = visitor.visit(a);
    Statement d = ans.as<Statement>();
	return d;
	//history = query + '\n' + history;
	//GraphSet graphset;
    //evalToGraphSet(d, graphset);
    //ofstream outfile("/Users/henryfox/Documents/github/GraphDBWeb/static/graph.json");
    //outfile << getJson();
    //outfile.close();
    //return graphset;
}

void GraphParser::run() {
	//string query = "select * from " + data + " where file " + community + ", " + pattern + ";";
	//string query = "select * from " + tempdata + " where tdensesub(3, 30, 518400, 86400, 604800, 0.5, 0.5, 86400, 43200, 0.4, 0.9, 2, 1);";
	//string query = "select * from " + tempdata + " where (not Exist x,y((1 + 2) * (3 + 4) = 5 and HasEdge(x, y))) and (a = b);";
	string query = "";

	//clock_t start, end;
	auto start = std::chrono::high_resolution_clock::now();
	//Graphset ans = parse(query);
	auto end = std::chrono::high_resolution_clock::now();
	//end = clock();
	//std::fstream fout("message.log", std::ios::app);
	//fout << (double)(end - start) / CLOCKS_PER_SEC << endl;
	double secs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	printf("%.4lf\n", secs / 1000000000);
	//cout << "TOTAL:"<<end<<"|"<<start<<"|"<< secs/(double)1000000000 <<"|"<<CLOCKS_PER_SEC<< endl;

	//return 0;

	while (true) {
		try {
			//        parse("query * as Graph1 from {v1, e1<v2->v3>, e2<{v3->v4}>, {v4->v2, v1->v4}}");
			//        parse("query * as Graph2 from {v1, e1<v2->v3>, {v1->v4}}");
			//        Graph ans = parse("Query * from Graph1 minus Graph2");
			string query;
			//cout << RED << "Please input your query: " BLACK;
			getline(cin, query);
			if (query == "quit") {
				break;
			}
			//GraphSet ans = parse(query);
			//cout << ans.toString() << endl;
		}
		catch (const GraphException &msg) {
			cerr << msg.what() << endl;
		}
		catch (...) {
			cerr << "Parse error, please try again" << endl;
		}
	}
}