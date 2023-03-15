// Code adapt from https://blog.csdn.net/zt1091574181/article/details/126288077
#include <iostream>
#include <fstream>
#include "onnx.pb.h"


void print_dim(const ::onnx::TensorShapeProto_Dimension &dim)
{
	switch (dim.value_case())
	{
	case onnx::TensorShapeProto_Dimension::ValueCase::kDimParam:
		std::cout << dim.dim_param();
		break;
	case onnx::TensorShapeProto_Dimension::ValueCase::kDimValue:
		std::cout << dim.dim_value();
		break;
	default:
		assert(false && "should never happen");
	}
}
void print_io_info(const ::google::protobuf::RepeatedPtrField<::onnx::ValueInfoProto> &info)
{
	for (auto input_data : info)
	{
		auto shape = input_data.type().tensor_type().shape();
		std::cout << "  " << input_data.name() << ":";
		std::cout << "[";
		if (shape.dim_size() != 0)
		{
			int size = shape.dim_size();
			for (int i = 0; i < size - 1; ++i)
			{
				print_dim(shape.dim(i));
				std::cout << ",";
			}
			print_dim(shape.dim(size - 1));
		}
		std::cout << "]\n";
	}
}
 
float from_le_bytes(const unsigned char* bytes)
{
	
	return bytes[0];
}
void print_initializer_info(const ::google::protobuf::RepeatedPtrField<::onnx::TensorProto>& info)
{
	for (auto input_data : info)
	{
		auto data_type = input_data.data_type();
		auto dims = input_data.dims();
		std::cout << "shapes: ";
		for (auto dim : dims)
			std::cout << dim<< " ";
		std::cout << std::endl;
		auto raw_data = input_data.raw_data(); // weight
		float *data_r = (float*)raw_data.c_str(); // raw_data 读取
		int k = raw_data.size() / 4; //float 是4个字节
		int i = 0;
		std::vector<int> weight;
		while (i < k)
		{
			std::cout << *data_r << " "; //print weight
		    data_r++;
			i++;
		}
		
		/* auto tile = input_data.xb_number(0); */
		/* //float *y = reinterpret_cast<char*>(&raw_data)(4); */
		/* std::cout << raw_data.size() << std::endl; */
		/* //auto shape = input_data.type().tensor_type().shape(); */
		/* std::cout << "  " << input_data.name() << "\n tile: " << tile << ":"; */
		/* std::cout << "["; */
 
		/* std::cout << "]\n"; */
	}
}
 
void print_node_info(const ::google::protobuf::RepeatedPtrField<::onnx::NodeProto>& info)
{
	for (auto input_data : info)
	{
		auto op_type = input_data.op_type();
		// AttributeProto
		auto shape = input_data.attribute();
		std::cout << op_type <<" " << input_data.name() << ":";
		std::cout << std::endl << "Inputs:";
		for (auto inp : input_data.input())
			std::cout << inp << " ";
		std::cout << std::endl << "Outputs:";
		for (auto outp : input_data.output())
			std::cout << outp << " ";
		std::cout << std::endl << "[";
		// Print Attribute
		for (auto y : shape)
		{
			std::cout << y.name()<<": ";
			for (auto t : y.ints())
				std::cout << t << " ";
		}
		std::cout << "]\n";
	}
}
int main(int argc, char *argv[])
{
	//消息解析
	onnx::ModelProto out_msg;
	/* { */
	/* 	std::fstream input("person.onnx", std::ios::in | std::ios::binary); */
	/* 	if (!out_msg.ParseFromIstream(&input)) { */
	/* 	  std::cerr << "failed to parse" << std::endl; */
	/* 	  return -1; */
	/* 	} */
	/* 	std::cout << 1 << std::endl; */
	/* 	std::cout << out_msg.graph().node_size() << std::endl; */
	/* } */
	onnx::ModelProto model;
	std::ifstream input("./resnet18.onnx", std::ios::ate | std::ios::binary);
	// get current position in file
	std::streamsize size = input.tellg();
	// move to start of file
	input.seekg(0, std::ios::beg);
	// read raw data
	std::vector<char> buffer(size);
	input.read(buffer.data(), size); 
	model.ParseFromArray(buffer.data(), size); // parse protobuf
	auto graph = model.graph();
	std::cout << graph.initializer_size() << std::endl;
	std::cout << "graph inputs:\n";
	print_io_info(graph.input());
	std::cout << "graph outputs:\n";
	print_io_info(graph.output());
	std::cout << "graph initializer:\n";
	print_initializer_info(graph.initializer());
	std::cout << "graph node:\n";
	print_node_info(graph.node());
	
	return 0;
}
