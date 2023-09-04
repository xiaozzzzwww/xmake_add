package("ntl")

    set_homepage("https://libntl.org/")
    set_description("NTL is a high-performance, portable C++ library providing data structures and algorithms for manipulating signed, arbitrary length integers, and for vectors, matrices, and polynomials over the integers and over finite fields.")
    set_license("LGPLv2.1+")
    if is_plat("windows") then
        add_urls("https://libntl.org/WinNTL-${version}.zip")
        add_versions("11_5_1","0f95b126764e41845c39929e1677c77ad9b743411d4e233ccfe4a6f8a35ed6a8")
        add_versions("11_5_0","092677e6e876ca75ddf9ead8bd71a4b44ea07b09bc39bdd7f9d655282ec71fb4")
        add_versions("11_4_4","29efb96669a295eebdd9b2966ed561120c8e149cbaa6dd506f14b63b226f1522")
        add_configs("vs_runtime", {description = "Set vs compiler runtime.", default = "MT", readonly = true})
    end
    if is_plat("linux") then
        add_urls("https://libntl.org/ntl-${version}.tar.gz" )
        add_versions("11.5.1","210d06c31306cbc6eaf6814453c56c776d9d8e8df36d74eb306f6a523d1c6a8a")
        add_versions("11.5.0","4f89c417699a3be541eb919f7af2d7c030ea17bc51146052d724ef66288f0078")
        add_versions("11.4.4","9d7f6e82e11a409f151c0de2deb08c0d763baf9834fddfd432bf3d218f8021db")
add_configs("shared",     {description = "Build shared library.", default = false, type = "boolean", readonly = true})
        add_deps("gmp","autoconf","automake")
    end
add_includedirs("include")
add_linkdirs("lib")
add_links("libntl")

    on_install("windows","linux", function (package)
        if is_plat("windows") then
            io.writefile("xmake.lua", [[
            add_rules("mode.debug", "mode.release")
            set_languages("c++11")
            if is_mode("debug") then
                add_defines("_DEBUG")
                target("libntld")
                    set_kind("static")
                    add_includedirs("include")
                    add_files("src/*.cpp")
            else
                add_defines("NDEBUG")
                target("libntl")
                    set_kind("static")
                    add_includedirs("include")
                    add_files("src/*.cpp")
            end
            ]])
      local configs = {}
   table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
            import("package.tools.xmake").install(package, configs)
        elseif is_plat("linux") then
       os.cd("src")
local install_dir=package:installdir()
os.vrun("./configure PREFIX="..install_dir)
os.vrun("make -j4")
os.vrun("make install")
        end 
    end)
 
