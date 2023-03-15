# ONNX CPP Parser (Experimental)

Environment:
- MacOSX M2

## Step1. Prepare
> Since necessary files have been placed in the repo, this step can be skipped, just for record.
```bash
# Get an example onnx model and onnx protobuf definition
wget https://github.com/onnx/models/raw/main/vision/classification/resnet/model/resnet18-v2-7.onnx -O resnet18.onnx
wget https://raw.githubusercontent.com/onnx/onnx/main/onnx/onnx.proto

# Transfer onnx.proto to C++ code
brew install protobuf
protoc --cpp_out=./ onnx.proto
```
Then get
```
./onnx.pb.h
./onnx.pb.cc
```

## Step2. Build
```bash
cmake -B build
cmake --build build -j
```
> Two things in CMakeLists.txt to modify if not succeed: include directories for protobuf and find library for protobuf. (You need to know where're the header files and library files)

## Step3. Run
```bash
./build/main
```
