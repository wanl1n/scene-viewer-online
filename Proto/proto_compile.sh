#!/bin/bash
# directory of protoc: X:/GithubProjects/vcpkg/packages/protobuf_x64-windows/tools/protobuf

#where protobuf.exe and grpc_cpp_plugin.exe are
PROTOC_DIR="C:/Users/asus/Coding/vcpkg/installed/x64-windows/tools/protobuf"
GRPC_CPP_EXE="C:/Users/asus/Coding/vcpkg/installed/x64-windows/tools/grpc/grpc_cpp_plugin.exe"

#where your .proto files are
SRC_DIR="C:/Users/asus/Coding/GDPARCM/scene-viewer-online/Proto/"
DST_DIR="C:/Users/asus/Coding/GDPARCM/scene-viewer-online/Proto/"

echo "Src Directory: $SRC_DIR"
echo "Dst Directory: $DST_DIR"

$PROTOC_DIR/protoc --proto_path=$SRC_DIR --cpp_out=$DST_DIR --grpc_out=$DST_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_EXE $SRC_DIR/model.proto
$PROTOC_DIR/protoc --proto_path=$SRC_DIR --cpp_out=$DST_DIR --grpc_out=$DST_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_EXE $SRC_DIR/scene.proto
$PROTOC_DIR/protoc --proto_path=$SRC_DIR --cpp_out=$DST_DIR --grpc_out=$DST_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_EXE $SRC_DIR/transformtex.proto

$SHELL