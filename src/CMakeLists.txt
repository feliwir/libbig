set(HEADER_DIR ${LIBBIG_ROOT}/include/libbig)
set(PUBLIC_HEADERS  ${HEADER_DIR}/big.hpp
                    ${HEADER_DIR}/manager.hpp)

file(GLOB_RECURSE SRC_FILES
	"*.c"
	"*.h"
    "*.hpp"
    "*.cpp"
)

add_library(libbig STATIC   ${SRC_FILES}
							${PUBLIC_HEADERS})

set_property(TARGET libbig PROPERTY CXX_STANDARD 14)
set_property(TARGET libbig PROPERTY PREFIX "")
target_include_directories(libbig PUBLIC ${LIBBIG_ROOT}/include)