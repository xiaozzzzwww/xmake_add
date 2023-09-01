add_rules("mode.debug", "mode.release")

add_includedirs("include")
--静态库项目

    
set_symbols("debug")
set_runtimes("MTd")
target("libntld")
    set_kind("static")
    add_includedirs("include")
    add_files("src/*.cpp")
    on_install("windows", function (package)
            os.cp("include/*", package:installdir("include"))
            os.cp("lib/*", package:installdir("lib"))
        end)

    -- set_symbols("release")
    -- -- set_runtimes("MD")
    -- -- target("ntl")
    -- --     set_kind("shared")
    -- --     add_files("src/*.cpp")
    -- set_runtimes("MT")
    -- target("libntld")
    --     set_kind("static")
    --     add_files("src/*.cpp")
        
        
    --     on_install(function (target)
    --         os.cp("include", target:installdir(""))
    --         --os.cp("lib", target:installdir(""))
    --         print("install ok!")
    --         print(packages:installdir())
    --     end)

