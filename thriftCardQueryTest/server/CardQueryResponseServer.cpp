/*
 * CardQueryServer.cpp
 *
 *  Created on: 2015Äê1ÔÂ8ÈÕ
 *      Author: lostaway
 */



#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

#include "../gen-cpp/UvcDccServices.h"
using namespace  ::UvcDccServices;

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace boost;

class UvcDccServicesHandler : virtual public UvcDccServicesIf {
 public:
  UvcDccServicesHandler() {
    // Your initialization goes here
  }

  int32_t CardQueryResponse(const CardQueryRespInfo& response)
  {
	    printf("Receive CardQUery Response:\n  ResponseSerial = %s\n  RequestSerial = %s\n  \
ResultCode = %d\n  Result = %d\n  \
CallingNumber = %s\n  RechargeTime = %s\n  DestAccount = %s\n  \
DestAttribute = %d\n  \
VoucherId = %s\n  VoucherPublisher = %s\n  \
VoucherStatus = %d\n  VoucherExpireTime = %lld\n  ProlongDays = %d\n  VoucherValue = %d\n  \
BatchNumber = %s\n  \
VoucherType = %d\n  AccessType = %d\n  \
ServiceFlowId = %s\n  \
CardAttribute = %d\n  VoucherFlow = %lld\n",
				response.ResponseSerial.c_str(),response.RequestSerial.c_str(),
				response.ResultCode,response.Result,
				response.CallingNumber.c_str(),response.RechargeTime.c_str(),
				response.DestAccount.c_str(), response.DestAttribute,
				response.VoucherId.c_str(),response.VoucherPublisher.c_str(),
				response.VoucherStatus,response.VoucherExpireTime,response.ProlongDays,
				response.VoucherValue, response.BatchNumber.c_str(),
				response.VoucherType,response.AccessType,
				response.ServiceFlowId.c_str(),
				response.CardAttribute,response.VoucherFlow);

	    return (0);
  }

  int32_t CardQueryRequest(const CardQueryReqInfo& request)
  {
	  return (0);
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<UvcDccServicesHandler> handler(new UvcDccServicesHandler());
  shared_ptr<TProcessor> processor(new UvcDccServicesProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TJSONProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
