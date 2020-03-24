int main_filesystem() {

	/*
	 *	filesystem 可移植的文件操作库 使用posix标准表示文件系统的路径
	 *
	 */


	/*
	 *	filesystem 核心类 path
	 *
	 *	提供通用的目录、路径表示，支持posix的符号连接概念
	 */
	path p1("./a_dir");
	path p2("/usr/local/lib");

	path p3("c:\\tmp\\test.text");
	path p4("d:/boost/boost/filesystem");

	path p5;
	assert(p5.empty());			//空路径as

	char str[] = "the path is (/root)";
	path p(str + 13, str + 14);

	assert(!p.empty());

	p /= "etc";										// /= 追加路径
	string filename = "xinedt.conf";
	p.append(filename.begin(), filename.end());
	cout << p << endl;

	p += "/etc";									// += 追加路径

	p.concat(filename.begin(), filename.end());		// concat 追加路径
				
	cout << system_complete(p) << endl;				//输出绝对路径


	/*
	 *	可移植的文件名
	 *
	 *	portable_posix_name       : 是否符合posix规范
	 *	windows_name              : 是否符合windows规范
	 *	portable_name()           : 是否符合posix和windows规范
	 *	portable_directory_name() : 是否符合posix和windows规范且不能出现点号
	 *  portable_file_name()	  : 是否符合posix和windows规范且最多要求出现一个点号
	 *	native()				  : 是否符合本地文件系统命名规则
	 */



	/*
	 *	路径处理
	 *
	 *	
	 */
	path p41("/usr/local/include/xxx.hpp");

	cout << p41.string() << endl;				// usr/local/include/xxx.hpp 返回的是std::string

	cout << p41.parent_path() << endl;			// /usr/local/include

	cout << p41.stem() << endl;					// xxx

	cout << p41.filename() << endl;				// xxx.hpp

	cout << p41.extension() << endl;			// .hpp

	assert(p.is_absolute());
	assert(system_complete(p).is_absolute());

	cout << p.root_name() << endl;
	cout << p.root_directory() << endl;
	cout << p.root_path() << endl;

	cout << p.remove_filename() << endl;
	cout << p.replace_extension("hxx") << endl;


	/*
	 *	异常处理
	 *
	 */
	try {

	}catch(filesystem_error &e){
		cout << e.path1() << endl;
		cout << e.what() << endl;
	}


   /*
	*	文件状态
	*
	*/


   /*
	*	文件属性
	*
	*/
	cout << initial_path() << endl;
	cout << current_path() << endl;
	path p("./test.txt");
	cout << file_size(p) << endl;

	time_t t = last_write_time(p);
	last_write_time(p, time(0));

   /*
	*	文件操作
	*
	*	创建目录、文件改名、文件删除、文件拷贝、创建符号链接
	*/
	path ptest = "./test";
	if(exists(ptest)){
		if(is_empty(ptest)){
			remove(ptest);
		}else{
			remove_all(ptest);
		}
	}

	assert(!exists(ptest));
	create_directory(ptest);
	copy_file("/usr/local/include/boost/version.hpp", ptest / "a.txt");
	assert(exists(ptest / "a.txt"));

	rename(ptest / "a.txt", ptest / "b.txt");

	create_directories(ptest / "sub_dir1" / "sub_dir2");


   /*
	*	迭代文件
	*
	*	
	*/
	directory_iterator pos, end;
	for (directory_iterator pos("/usr/local/lib/"); pos != end; ++pos) {
		cout << *pos << endl;
	}

	typedef recursive_directory_iterator rd_iterator;
	rd_iterator end1;
	for (rd_iterator pos("/usr/local/lib"); pos != end1; ++pos) {
		cout << "level" << pos.level()<< ":" << "*pos" << endl;

	}

	getchar();
	return 0;
}

