# 在xmake的本地库中添加自定义包/xrepo中没有的包

## xmake的本地包管理，可以让我们直接在本地快速添加一个本地包，而不需要从网络下载，这样我们就可以在本地快速测试一些
当用xmake下载包时可能出现网速等问题时，我们可以通过查找该包在repositories中对应位置的xmake.lua中的链接手动下载之后放在本地指定路径下，
    
假设以ntl为例：那么就在 
    
    windwos: 
    /home/username/AppData/Local/.xmake/repositories/xmake-repo/packages/n/ntl
    linux:  
    /home/username/.xmake/repositories/xmake-repo/packages/n/ntl
    
下的xmake.lua中找到应的下载链接，然后下载到本地指定路径下，

然后通过 

    xmake g --pkg_searchdirs =/path/to/local/packages 
    
指定本地包的查找路径，之后就可以下载网上的包了
    
# 添加一个本地包

以ntl包为例。
在此文件夹路径n/ntl下有一个xmake.lua文件，其中代码是:

    -- 添加一个本地包
    add_rules("mode.debug", "mode.release")

    --静态项目
    set_symbols("debug")
    set_runtimes("MTd")                         -- 设置运行时环境
    target("libntld")                           -- 设置目标名
        set_kind("static")                      -- 设置为静态库
        add_includedirs("include")              -- 添加头文件路径
        add_files("src/*.cpp")                  -- 添加源文件
        on_install("windows", function (package)
                os.cp("include/*", package:installdir("include"))
                os.cp("lib/*", package:installdir("lib"))
            end)
    
在n/ntl路径下执行 
    
    xmake 

将会生成静态库文件，之后执行

    xmake p 
    
将会将静态库打包，此时就可以在其他项目中通过
    
    add_repositories("local-repo /path/packages/n/ntl")   --此处的路径为上述ntl打包后的包路径
    add_requires("ntl")
    target("test")
        set_kind("binary")
        add_files("src/*.cpp")
        add_packages("ntl")

调用ntl库。

当然，也可以通过将ntl打包后的包文件复制到本地的xmake仓库
    
    repositories/xmake-repo/packages/n/ntl

文件夹下，然后通过

    add_requires("ntl")
    target("test")
        set_kind("binary")
        add_files("src/*.cpp")
        add_packages("ntl")

调用ntl库。

# 添加一个网络包(以cmake项目为例)
添加一个网络包，首先需要将包的源码下载下来放置 pkg_searchdirs 目录下（以 ntl 为例），然后通过在
    
    repositories/xmake-repo/packages/n/ntl

文件夹下添加一个xmake.lua文件，内容如下：

    -- 可能错误 需要自行更改

    package("ntl")

    set_homepage("https://libntl.org/")
    set_description("NTL is a high-performance, portable C++ library providing data structures and algorithms for manipulating signed, arbitrary length integers, and for vectors, matrices, and polynomials over the integers and over finite fields.")
    set_license("LGPLv2.1+")
    if is_plat("windows") then
        add_urls("https://github.com/xiaozzzzwww/libntl/archive/refs/heads/master.zip")
		add_configs("shared",     {description = "Build shared library.", default = false, type = "boolean", readonly = true})
        add_configs("vs_runtime", {description = "Set vs compiler runtime.", default = "MT", readonly = true})
    end
    if is_plat("linux") then
        add_urls("https://libntl.org/ntl-11.5.1.tar.gz" )
    end
    add_versions("11.5.1","9bf764b3faa81189af3fe82f296980a600091e5b9d1a9bbabc2ce39f88f7a0fb")
    add_deps("cmake")
	add_includedirs("include")
	add_linkdirs("lib")
	add_links("libntl")
	

    on_install("windows", function (package)
		local configs = {}
		table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        import("package.tools.cmake").install(package, configs)
		--os.cp("include/NTL", package:installdir("include"))
		--os.cp("lib/*",package:installdir("lib"))
    end)


添加好后就可以通过xmake下载安装包了
具体见xmake官网文档
链接：https://xmake.io/#/zh-cn/manual/package_dependencies?id=%e4%bb%93%e5%ba%93%e4%be%9d%e8%b5%96%e5%8c%85%e5%ae%9a%e4%b9%89%e6%8f%8f%e8%bf%b0
