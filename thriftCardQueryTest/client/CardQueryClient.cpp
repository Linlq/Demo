/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/UvcDccServices.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace boost;

using namespace  ::UvcDccServices;

int main(int argc, char** argv) {
  shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  UvcDccServicesClient client(protocol);

  try {
    transport->open();
    CardQueryResponse response;
    CardQueryRequest request;

    request.RequestSource="RequestSource";
    request.RequestUser="RequestUser";
    request.RequestSerial="RequestSerial";
    request.VoucherId="VoucherId";
    request.ServiceFlowId="ServiceFlowId";

    printf("Send CardQuery Request:\n  %s\n  %s\n  %s\n  %s\n  %s\n\n",
    	    request.RequestSource.c_str(),
    	    request.RequestUser.c_str(),
    	    request.RequestSerial.c_str(),
    	    request.VoucherId.c_str(),
    	    request.ServiceFlowId.c_str());

    client.CardQuery(response, request);

    printf("Receive response:\n  ResponseSerial = %s\n  RequestSerial = %s\n  \
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
			response.CallingNumber.c_str(),response.RechargeTime.c_str(),response.DestAccount.c_str(),
			response.DestAttribute,
			response.VoucherId.c_str(),response.VoucherPublisher.c_str(),
			response.VoucherStatus,response.VoucherExpireTime,response.ProlongDays,response.VoucherValue,
			response.BatchNumber.c_str(),
			response.VoucherType,response.AccessType,
			response.ServiceFlowId.c_str(),
			response.CardAttribute,response.VoucherFlow);

    transport->close();
  } catch (TException &tx) {
    printf("ERROR: %s\n", tx.what());
  }

}
