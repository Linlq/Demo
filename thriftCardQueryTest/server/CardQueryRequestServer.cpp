/*
 * CardQueryServer.cpp
 *
 *  Created on: 2015��1��8��
 *      Author: lostaway
 */



#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "../gen-cpp/UvcDccServices.h"
using namespace  ::UvcDccServices;

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace boost;

shared_ptr<UvcDccServicesClient> g_spCli;

class UvcDccServicesHandler : virtual public UvcDccServicesIf {
 public:
  UvcDccServicesHandler() {
    // Your initialization goes here
  }

  int32_t CardQueryResponse(const CardQueryRespInfo& response)
  {
	    return (0);
  }

  int32_t CardQueryRequest(const CardQueryReqInfo& request)
  {
	  printf("Receive CardQuery Request:\n\
\tRequestSource: %s\n\
\tRequestUser: %s\n\
\tRequestSerial: %s\n\
\tVoucherId: %s\n\
\tServiceFlowId: %s\n\
\tSessionId: %s\n",
		request.RequestSource.c_str(), request.RequestUser.c_str(),
		request.RequestSerial.c_str(), request.VoucherId.c_str(),
	    request.ServiceFlowId.c_str(), request.SessionId.c_str());

	  CardQueryRespInfo resp;
	  resp.ResultCode = 2001;
	  resp.Result = 0;
	  resp.ServiceFlowId = request.ServiceFlowId;
	  resp.SessionId = request.SessionId;
	  int result = g_spCli->CardQueryResponse(resp);
	  printf("Send CardQuery Response: result = %d.\n", result);

	  return (0);
  }

};

int main(int argc, char **argv)
{
	// Server
	int port = 9090;
	shared_ptr<UvcDccServicesHandler> handler(new UvcDccServicesHandler());
	shared_ptr<TProcessor> processor(new UvcDccServicesProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	shared_ptr<TProtocolFactory> protocolFactory(new TJSONProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	boost::thread serverThread(boost::bind(&TSimpleServer::serve, server));


	// Client
	shared_ptr<TTransport> socket(new TSocket("localhost", 17972));
	shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	shared_ptr<TProtocol> protocol(new TJSONProtocol(transport));
	g_spCli.reset(new UvcDccServicesClient(protocol));
	while(!transport->isOpen())
	{
		try
		{
			transport->open();
			printf("Thrift client connect success.\n");
			break;
		}
		catch(const TException &te)
		{
			sleep(3);
			continue;
		}
	}

	serverThread.join();
	transport->close();
    return 0;
}