//
// Created by ssunah on 6/22/18.
//

#ifndef SUBGRAPHMATCHING_TYPES_H
#define SUBGRAPHMATCHING_TYPES_H

#include <cstdint>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

//typedef unsigned int ui;
typedef int ui;

//typedef uint32_t VertexID;
typedef int VertexID;
typedef ui LabelID;

enum MatchingIndexType {
    VertexCentric = 0,
    EdgeCentric = 1
};

class TreeNode {
public:
    VertexID id_;
    VertexID parent_;
    ui level_;
    ui under_level_count_;
    ui children_count_;
    ui bn_count_;
    ui fn_count_;
    VertexID* under_level_;
    VertexID* children_;
    VertexID* bn_;
    VertexID* fn_;
    size_t estimated_embeddings_num_;
public:
    TreeNode() {
        id_ = 0;
        under_level_ = NULL;
        bn_ = NULL;
        fn_ = NULL;
        children_ = NULL;
        parent_ = 0;
        level_ = 0;
        under_level_count_ = 0;
        children_count_ = 0;
        bn_count_ = 0;
        fn_count_ = 0;
        estimated_embeddings_num_ = 0;
    }

    ~TreeNode() {
        delete[] under_level_;
        delete[] bn_;
        delete[] fn_;
        delete[] children_;
    }

	void init() {
		parent_ = 0;
        level_ = 0;
        under_level_count_ = 0;
        children_count_ = 0;
        bn_count_ = 0;
        fn_count_ = 0;
        estimated_embeddings_num_ = 0;
	}

    void initialize(const ui size) {
        under_level_ = new VertexID[size];
        bn_ = new VertexID[size];
        fn_ = new VertexID[size];
        children_ = new VertexID[size];
    }
};

class Edges {
public:
    vector<ui> offset_;
    vector<ui> edge_;
	//ui* offset_;
	//ui* edge_;
    ui vertex_count_;
    ui edge_count_;
    ui max_degree_;
public:
    Edges() {
        //offset_ = NULL;
        //edge_ = NULL;
        vertex_count_ = 0;
        edge_count_ = 0;
        max_degree_ = 0;
    }

    ~Edges() {
		/*if (offset_ != NULL)
			delete[] offset_;
		if (edge_ != NULL)
			delete[] edge_;*/
    }
};

#endif //SUBGRAPHMATCHING_TYPES_H
