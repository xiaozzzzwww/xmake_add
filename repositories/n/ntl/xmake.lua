package("ntl")

    set_homepage("https://libntl.org/")
    set_description("NTL is a high-performance, portable C++ library providing data structures and algorithms for manipulating signed, arbitrary length integers, and for vectors, matrices, and polynomials over the integers and over finite fields.")
    set_license("LGPLv2.1+")
    if is_plat("windows") then
        add_urls("https://github.com/xiaozzzzwww/libntl/releases/download/libntl-11.5.1/libntl-11.5.1.zip")
		add_configs("shared",     {description = "Build shared library.", default = false, type = "boolean", readonly = true})
        add_configs("vs_runtime", {description = "Set vs compiler runtime.", default = "MT", readonly = true})
    end
    if is_plat("linux") then
        add_urls("https://libntl.org/ntl-11.5.1.tar.gz" )
    end
    add_versions("11.5.1","ffb27fd8a0173f2341837481c4f10ea1d84adeb907fd838cf2b97f0251fd69d1")
	
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
