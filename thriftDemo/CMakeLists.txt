PROJECT(ThriftDemo)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)


INCLUDE_DIRECTORIES($ENV{THRIFT_ROOT}/include
                    $ENV{BOOST_ROOT}/include)

LINK_DIRECTORIES($ENV{THRIFT_ROOT}/lib
                 $ENV{BOOST_ROOT}/lib
                 ${PROJECT_SOURCE_DIR}/gen-cpp)

ADD_SUBDIRECTORY(gen-cpp)
ADD_SUBDIRECTORY(client)
ADD_SUBDIRECTORY(server)