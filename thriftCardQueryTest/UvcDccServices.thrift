namespace cpp UvcDccServices
namespace java UvcDccServices

struct CardQueryRequest {
  1: optional string RequestSource,
  2: optional string RequestUser,
  3: optional string RequestSerial,
  4: optional string VoucherId,
  5: optional string ServiceFlowId
}

struct CardQueryResponse {
  1: optional string ResponseSerial,
  2: optional string RequestSerial,
  3: i32 ResultCode,
  4: i32 Result,
  5: optional string CallingNumber,
  6: optional string RechargeTime,
  7: optional string DestAccount,
  8: optional i32 DestAttribute,
  9: optional string VoucherId,
  10: optional string VoucherPublisher,
  11: i32 VoucherStatus,
  12: i64 VoucherExpireTime,
  13: i32 ProlongDays,
  14: i32 VoucherValue,
  15: optional string BatchNumber,
  16: i32 VoucherType,
  17: i32 AccessType,
  18: optional string ServiceFlowId,
  19: i32 CardAttribute,
  20: i64 VoucherFlow
}

service UvcDccServices {
  CardQueryResponse CardQuery(1:CardQueryRequest request)
}

