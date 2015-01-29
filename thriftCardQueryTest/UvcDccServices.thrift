namespace cpp UvcDccServices
namespace java UvcDccServices

struct CardQueryReqInfo {
  1: string RequestSource,
  2: string RequestUser,
  3: string RequestSerial,
  4: string VoucherId,
  5: string ServiceFlowId,
  6: string SessionId
}

struct CardQueryRespInfo {
  1: string ResponseSerial,
  2: string RequestSerial,
  3: i32 ResultCode,
  4: i32 Result,
  5: string CallingNumber,
  6: string RechargeTime,
  7: string DestAccount,
  8: i32 DestAttribute,
  9: string VoucherId,
  10: string VoucherPublisher,
  11: i32 VoucherStatus,
  12: i64 VoucherExpireTime,
  13: i32 ProlongDays,
  14: i32 VoucherValue,
  15: string BatchNumber,
  16: i32 VoucherType,
  17: i32 AccessType,
  18: string ServiceFlowId,
  19: i32 CardAttribute,
  20: i64 VoucherFlow,
  21: string SessionId
}

service UvcDccServices {
  i32 CardQueryRequest(1:CardQueryReqInfo request)
  i32 CardQueryResponse(1:CardQueryRespInfo response)
}

