add_rules("mode.debug", "mode.release")

add_requires("eigen")
target("${TARGETNAME}")
    set_kind("binary")
	add_packages("eigen")
    add_files("src/*.cpp")

${FAQ}
