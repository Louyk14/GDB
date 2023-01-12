//
// Created by Henry Fox on 2019-12-21.
//

#ifndef ANTLR_GRAPHDB_GRAPHEXCEPTION_H
#define ANTLR_GRAPHDB_GRAPHEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

class GraphException : public runtime_error {
public:
    explicit GraphException(const string &s = "Graph Error") : runtime_error(s) {}
};

#endif //ANTLR_GRAPHDB_GRAPHEXCEPTION_H
