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

