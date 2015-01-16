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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <pthread.h>
#include <signal.h>

#include <thrift/protocol/TJSONProtocol.h>
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

using namespace boost::gregorian;

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


void getCurrentTime(char *CurrentTime_)
{
	printf("in getCurrentTime.\n");
	struct timeval tv;
	gettimeofday(&tv,NULL);
	long long llCurrentTime = ((long long)tv.tv_sec)*1000 + ((long long)tv.tv_usec)/1000;
	sprintf(CurrentTime_, "%lld", llCurrentTime);
	printf("%s\n",CurrentTime_);
	return;
}


void* work_thread(void* arg)
{
	struct event_base* evbase = (event_base*) arg;
//for(int i=0;i<1;i++)
{
    boost::shared_ptr<TAsyncChannel> channel(new TEvhttpClientChannel("localhost", "/", "localhost", 9091, evbase));
    UvcDccServicesCobClient client(channel, new TJSONProtocolFactory());
	tcxx::function<void(UvcDccServicesCobClient* client)> cob = bind(&my_ping_pong,_1);

	CardQueryRequest request;
	char CurrentTime[20];
	memset((void*)CurrentTime, 0, sizeof(CurrentTime));
	getCurrentTime(CurrentTime);

	request.RequestSource="RequestSource";
	request.RequestUser="RequestUser";
	request.RequestSerial=CurrentTime;
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
}
	return NULL;
}

void signal_cb(int fd, short event, void *argc)
{
	struct event_base* base = (event_base*) argc;
	struct timeval delay = {2 ,0 };
	printf("receive signal,exiting in two seconds ...\n");
	event_base_loopexit( base, &delay);
}

int main(int argc, char** argv) {
	try {
		//async
		struct event_base* evbase = event_base_new();

		struct event* signal_event = evsignal_new(evbase, SIGINT, signal_cb, evbase);
		event_add(signal_event, NULL);

		printf("create thread for work_thread.\n");
		pthread_t pid;
		pthread_attr_t congestionThreadAttr;
		pthread_attr_init(&congestionThreadAttr);
		pthread_attr_setdetachstate(&congestionThreadAttr, PTHREAD_CREATE_DETACHED);
		int ret = pthread_create(&pid,
				&congestionThreadAttr,
				work_thread,
				evbase);
		if(ret != 0)
		{
			printf("thread for work_thread create failed.\n");
			return -1;
		}
		printf("[%lld]thread for work_thread create success.\n",pid);

		event_base_dispatch(evbase);

		event_free(signal_event);
		event_base_free(evbase);
	} catch (TException &tx) {
		printf("ERROR: %s\n", tx.what());
	}
}
