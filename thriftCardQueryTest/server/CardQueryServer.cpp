/*
 * CardQueryServer.cpp
 *
 *  Created on: 2015Äê1ÔÂ8ÈÕ
 *      Author: lostaway
 */



#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
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

  void CardQuery(CardQueryResponse& _return, const CardQueryRequest& request) {
    printf("Receive CardQuery Request:\n  %s\n  %s\n  %s\n  %s\n  %s\n\n",
    	    request.RequestSource.c_str(),
    	    request.RequestUser.c_str(),
    	    request.RequestSerial.c_str(),
    	    request.VoucherId.c_str(),
    	    request.ServiceFlowId.c_str());

    _return.ResponseSerial="ResponseSerial";
    _return.RequestSerial="RequestSerial";
    _return.ResultCode = 2001;
    _return.Result=0;
    _return.CallingNumber="CallingNumber";
    _return.RechargeTime="RechargeTime";
    _return.DestAccount="DestAccount";
    _return.DestAttribute=1111;
    _return.VoucherId="VoucherId";
    _return.VoucherPublisher="VoucherPublisher";
    _return.VoucherStatus=1;
    _return.VoucherExpireTime=20150108;
    _return.ProlongDays=2;
    _return.VoucherValue=3;
    _return.BatchNumber="BatchNumber";
    _return.VoucherType=4;
    _return.AccessType=5;
    _return.ServiceFlowId="ServiceFlowId";
    _return.CardAttribute=6;
    _return.VoucherFlow=7;

    printf("Send response:\n  ResponseSerial = %s\n  RequestSerial = %s\n  \
ResultCode = %d\n  Result = %d\n  \
CallingNumber = %s\n  RechargeTime = %s\n  DestAccount = %s\n  \
DestAttribute = %d\n  \
VoucherId = %s\n  VoucherPublisher = %s\n  \
VoucherStatus = %d\n  ProlongDays = %d\n  VoucherValue = %d\n  \
BatchNumber = %s\n  \
VoucherType = %d\n  AccessType = %d\n  \
ServiceFlowId = %s\n  \
CardAttribute = %d\n  VoucherFlow = %d\n",
			_return.ResponseSerial.c_str(),_return.RequestSerial.c_str(),
			_return.ResultCode,_return.Result,
			_return.CallingNumber.c_str(),_return.RechargeTime.c_str(),_return.DestAccount.c_str(),
			_return.DestAttribute,
			_return.VoucherId.c_str(),_return.VoucherPublisher.c_str(),
			_return.VoucherStatus,
			_return.ProlongDays,
			_return.VoucherValue,
			_return.BatchNumber.c_str(),
			_return.VoucherType,_return.AccessType,
			_return.ServiceFlowId.c_str(),
			_return.CardAttribute,_return.VoucherFlow);
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<UvcDccServicesHandler> handler(new UvcDccServicesHandler());
  shared_ptr<TProcessor> processor(new UvcDccServicesProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
