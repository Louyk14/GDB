#pragma once
#ifndef GRAPHPARSER_H
#define GRAPHPARSER_H

#include "eval.h"
#include "definations.h"
#include "graphException.h"
#include "MyGraphVisitor.h"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class GraphParser {
public:
	GraphParser();

	Statement parse(string query);
	void run();

	string history;
};

#endif