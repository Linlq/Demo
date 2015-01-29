ADD_EXECUTABLE(Client CardQueryRequestClient.cpp)
TARGET_LINK_LIBRARIES(Client tutorialgencpp thrift)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/client)