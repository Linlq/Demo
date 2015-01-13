ADD_EXECUTABLE(Client CardQueryClient.cpp)
TARGET_LINK_LIBRARIES(Client tutorialgencpp
                             thrift thriftnb
                             boost_thread-mt
                             event)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/client)