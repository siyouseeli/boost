

#include <iostream>
#include <exception>
#include <istream>

//--[1]包含库文件
#include <boost/program_options.hpp>
namespace opt = boost::program_options;

void output_config(opt::variables_map & vm, const opt::options_description& desc) {
	if (!vm.empty()) {
		opt::notify(vm);
		if (vm.count("help")) {
			std::cout << desc << "\n";
			return;
		}
		//--[4]遍历解析参数 -- 缺点--不能一次性遍历出,as<T>无法知道
		for (opt::variables_map::const_iterator iter = vm.begin(); iter != vm.end(); ++iter) {
			if (iter->first == "name")
				std::cout << iter->first << "-->" << iter->second.as<std::string>() << std::endl;
			else
				std::cout << iter->first << "-->" << iter->second.as<int>() << std::endl;
		}

	}
}


int main01(int argc, char*argv[]){
	
	//--[2]添加选项参数
	opt::options_description desc("ALL options");	//构造一个选项描述变量,并给一个文本描述
	desc.add_options()("apples,a", opt::value<int>()->default_value(250), "how many apples do you have?");
	desc.add_options()("organges, o", opt::value<int>()->default_value(123), "how many organes do you have?");
	desc.add_options()("name,n", opt::value<std::string>()->default_value("yl"), "you name");
	desc.add_options()("help", "produce help message");
	
	//--[3]解析选项参数
	opt::variables_map vm;				//保存命令行参数
	opt::variables_map file_vm;
	try
	{
		//从命令行解析 -- parse_command_line
		opt::store(opt::parse_command_line(argc, argv, desc), vm);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	output_config(vm, desc);

	try {
		// 从配置文件解析 -- parse_config_file
		opt::store(opt::parse_config_file<char>("F:\\09_boost学习\\boost_vs\\boost_Secret\\apple_organges.cfg", desc), file_vm);
	}
	catch (const opt::reading_file& e) {
		std::cout << "Failed to open file 'apple_organges.cfg'" << e.what();
	}
	output_config(file_vm, desc);
	

// 	std::cout << "----------从输入流中读取-------------" << std::endl;
// 	
// 	std::ostringstream out;
// 	opt::variables_map vm_stream;
// 	out << "apples" << 999 <<  "organges" << 888 << "name" << "XXXS";
// 	std::istringstream in;
// 	in << out;
// 	try {
// 		opt::store(opt::parse_config_file<char>(in, desc), vm_stream);
// 	}
// 	catch (const std::exception& e) {
// 		std::cout << "Failed to parse 'ostringstream'" << e.what();
// 	}
// 	output_config(vm_stream, desc);

	getchar();
	return 0;
}
