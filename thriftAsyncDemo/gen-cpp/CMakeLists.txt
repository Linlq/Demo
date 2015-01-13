SET(LIBGENCPP_SRC aggr_constants.cpp /
				  aggr_types.cpp /
				  Aggr.cpp)

ADD_LIBRARY(tutorialgencpp STATIC ${LIBGENCPP_SRC})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/gen-cpp)