add_rules("mode.debug", "mode.release")

add_requires("ntl")
target("${TARGETNAME}")
    set_kind("binary")
	add_packages("ntl")
    add_files("src/*.cpp")

${FAQ}
