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

#include "../gen-cpp/Aggr.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::async;

using namespace boost;


void my_ping_pong(AggrCobClient* client)
{
	string  _return;
	client->recv_pingpong(_return);
	printf("[%d] receive: %s\n", (int)time(NULL),_return.c_str());
}

int main(int argc, char** argv) {
try {
  //async
	event_base* evbase = event_base_new();
    boost::shared_ptr<TAsyncChannel> channel(new TEvhttpClientChannel("localhost", "/", "localhost", 9090, evbase));
    AggrCobClient client(channel, new TBinaryProtocolFactory());

    tcxx::function<void(AggrCobClient* client)> cob = bind(&my_ping_pong,_1);

    client.pingpong(cob, "ping");
    printf("[%d] send ping\n", (int)time(NULL));

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
