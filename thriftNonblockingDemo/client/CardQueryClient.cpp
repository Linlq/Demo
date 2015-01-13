/*
 * CartQueryClient.cpp
 *
 *  Created on: 2015Äê1ÔÂ12ÈÕ
 *      Author: lostaway
 */



#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <event.h>
#include <boost/bind.hpp>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/async/TEvhttpClientChannel.h>

#include "../gen-cpp/UvcDccServices.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::async;

using namespace boost;

using namespace  ::UvcDccServices;

void my_ping_pong(UvcDccServicesCobClient* client)
{
    CardQueryResponse response;
    client->recv_CardQuery(response);
    printf("[%d] Receive response:\n  ResponseSerial = %s\n  RequestSerial = %s\n  \
  ResultCode = %d\n  Result = %d\n  \
  CallingNumber = %s\n  RechargeTime = %s\n  DestAccount = %s\n  \
  DestAttribute = %d\n  \
  VoucherId = %s\n  VoucherPublisher = %s\n  \
  VoucherStatus = %d\n  VoucherExpireTime = %lld\n  ProlongDays = %d\n  VoucherValue = %d\n  \
  BatchNumber = %s\n  \
  VoucherType = %d\n  AccessType = %d\n  \
  ServiceFlowId = %s\n  \
  CardAttribute = %d\n  VoucherFlow = %lld\n",
  	  	  	(int)time(NULL),
      		response.ResponseSerial.c_str(),response.RequestSerial.c_str(),
  			response.ResultCode,response.Result,
  			response.CallingNumber.c_str(),response.RechargeTime.c_str(),response.DestAccount.c_str(),
  			response.DestAttribute,
  			response.VoucherId.c_str(),response.VoucherPublisher.c_str(),
  			response.VoucherStatus,response.VoucherExpireTime,response.ProlongDays,response.VoucherValue,
  			response.BatchNumber.c_str(),
  			response.VoucherType,response.AccessType,
  			response.ServiceFlowId.c_str(),
  			response.CardAttribute,response.VoucherFlow);

}

int main(int argc, char** argv) {
try {
  //async
	event_base* evbase = event_base_new();
    boost::shared_ptr<TAsyncChannel> channel(new TEvhttpClientChannel("localhost", "/", "localhost", 9090, evbase));
    UvcDccServicesCobClient client(channel, new TBinaryProtocolFactory());

    tcxx::function<void(UvcDccServicesCobClient* client)> cob = bind(&my_ping_pong,_1);

    CardQueryRequest request;

        request.RequestSource="RequestSource";
        request.RequestUser="RequestUser";
        request.RequestSerial="RequestSerial";
        request.VoucherId="VoucherId";
        request.ServiceFlowId="ServiceFlowId";

    client.CardQuery(cob, request);


    printf("[%d] Send CardQuery Request:\n  %s\n  %s\n  %s\n  %s\n  %s\n\n",
    		(int)time(NULL),
			request.RequestSource.c_str(),
    	    request.RequestUser.c_str(),
    	    request.RequestSerial.c_str(),
    	    request.VoucherId.c_str(),
    	    request.ServiceFlowId.c_str());

    for(int i=0;i<5;i++)
    {
      printf("[%d] running...\n", (int)time(NULL));
      sleep(1);
    }

    event_base_dispatch(evbase);
    event_base_free(evbase);
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }

}
