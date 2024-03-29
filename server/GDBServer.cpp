#include "GDBServer.h"

GDBServer::GDBServer(string ip, string p) {
	address = ip + ":" + p;
	cout << address << endl;
}

GDBServer::GDBServer(string p) {
	address = p;
}

GDBServer::~GDBServer() {
	if (gdb)
		delete gdb;
}

void GDBServer::StartDatabase() {
	gdb = new GraphDatabase();
	//gdb->run();
}

void GDBServer::StopDatabase() {
	gdb->close();
}

void GDBServer::RunGreeterServer() {
	std::string server_address(address);
	GreeterServiceImpl service(gdb);

	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	ServerBuilder builder;
	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	// Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

	// Wait for the server to shutdown. Note that some other thread must be
	// responsible for shutting down the server for this call to ever return.
	server->Wait();
}