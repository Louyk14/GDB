#pragma once
#ifndef GDBSERVER_H
#define GDBSERVER_H

#include "../GraphDatabase.h"

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
using namespace std;

class GDBServer {
public:
	GDBServer(string ip, string p);
	GDBServer(string add = "0.0.0.0:9092");
	~GDBServer();
	void StartDatabase();
	void StopDatabase();
	void RunGreeterServer();

	GraphDatabase* gdb;
	string address;
};

class GreeterServiceImpl final : public Greeter::Service {
public:
	GreeterServiceImpl(GraphDatabase* db) {
		gdb = db;
	}

	GraphDatabase* gdb;

	Status SayHello(ServerContext* context, const HelloRequest* request,
		HelloReply* reply) override {

		GraphManager* gm = NULL;

		if (!gdb->getGraph("g100", gm)) {
			return Status::CANCELLED;
		}
		string str;
		gm->printMemoryGraphFromDisk(str);

		std::string prefix("Hello ");
		reply->set_message(str + request->name());
		std::cout << "Hello " << std::endl;
		return Status::OK;
	}
};

#endif