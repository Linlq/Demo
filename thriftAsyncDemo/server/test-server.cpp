#include <tr1/functional>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/async/TAsyncProtocolProcessor.h>
#include <thrift/async/TEvhttpServer.h>
#include <thrift/async/TEvhttpClientChannel.h>

#include "../gen-cpp/Aggr.h"

using std::tr1::bind;
using std::tr1::placeholders::_1;

using apache::thrift::TException;
using apache::thrift::protocol::TBinaryProtocolFactory;
using apache::thrift::protocol::TProtocolFactory;
using apache::thrift::async::TEvhttpServer;
using apache::thrift::async::TAsyncProcessor;
using apache::thrift::async::TAsyncBufferProcessor;
using apache::thrift::async::TAsyncProtocolProcessor;
using apache::thrift::async::TAsyncChannel;
using apache::thrift::async::TEvhttpClientChannel;


class AggrHandler : virtual public AggrIf {
 public:
	AggrHandler() { }

  void pingpong(std::string& _return, const std::string& data)
  {
      printf("[%d] receive %s\n", (int)time(NULL),data.c_str());
	  _return = "pong";
	  printf("[%d] send pong\n", (int)time(NULL));
  }
};


class AggrAsyncHandler : public AggrCobSvIf {
 public:
  AggrAsyncHandler() {
    syncHandler_ = std::auto_ptr<AggrHandler>(new AggrHandler);
    // Your initialization goes here
  }
//  virtual ~AggrAsyncHandler();

  void pingpong(tcxx::function<void(std::string const& _return)> cob, const std::string& data) {
    std::string _return;
    syncHandler_->pingpong(_return, data);
    return cob(_return);
  }

 protected:
  std::auto_ptr<AggrHandler> syncHandler_;
};


int main() {
  boost::shared_ptr<AggrAsyncHandler> handler(new AggrAsyncHandler());
  boost::shared_ptr<TAsyncProcessor> proc(new AggrAsyncProcessor(handler));
  boost::shared_ptr<TProtocolFactory> pfact(new TBinaryProtocolFactory());
  boost::shared_ptr<TAsyncBufferProcessor> bufproc(new TAsyncProtocolProcessor(proc, pfact));
  boost::shared_ptr<TEvhttpServer> server(new TEvhttpServer(bufproc, 9090));
//  handler->setEventBase(server->getEventBase());
  server->serve();
}
