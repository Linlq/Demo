ADD_EXECUTABLE(RespServer CardQueryResponseServer.cpp)
TARGET_LINK_LIBRARIES(RespServer tutorialgencpp thrift)

ADD_EXECUTABLE(ReqServer CardQueryRequestServer.cpp)
TARGET_LINK_LIBRARIES(ReqServer tutorialgencpp thrift boost_thread-mt boost_system-mt)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/server)