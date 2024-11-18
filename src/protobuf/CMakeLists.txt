
set(SRC_FILES
        dist/test.pb.h
        dist/test.pb.cc
)

message("LIBS: ${protobuf_LIBRARIES}")
add_executable(testProto testProto.cpp ${SRC_FILES})
target_link_libraries(testProto ${protobuf_LIBRARIES})