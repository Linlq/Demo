SET(LIBGENCPP_SRC UvcDccServices_constants.cpp /
				  UvcDccServices_types.cpp /
				  UvcDccServices.cpp)

ADD_LIBRARY(tutorialgencpp STATIC ${LIBGENCPP_SRC})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/gen-cpp)