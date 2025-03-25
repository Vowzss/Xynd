-- xmake.lua

-- Set project properties
set_project("xynd")
set_version("1.0.0")
set_languages("cxx20")

-- Define the shared source directories
add_includedirs("common")

add_requires("protobuf")
add_requires("spdlog")

-- adds debugging symbols to the compilation
set_symbols("debug")
add_rules("mode.debug", "mode.release")

set_default("xynd-test")

-- automatically update and generate compile_commandss.json for vscode
-- add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

-- Define the client library target
target("xynd-client")
    set_kind("static") -- This will produce an library
    add_includedirs("client/include") -- Header files
    add_files("client/src/*.cpp")  -- Source files
    add_packages("protobuf", "spdlog") -- Link dependencies

    if is_plat("windows") then
        add_links("Ws2_32")  -- Link to Ws2_32.lib library (winsock)
    end
target_end()

-- Define the server library target
target("xynd-server")
    set_kind("static") -- This will produce an library
    add_includedirs("server/include") -- Header files
    add_files("server/src/*.cpp")  -- Source files
    add_packages("protobuf", "spdlog") -- Link dependencies

    if is_plat("windows") then
        add_links("Ws2_32")  -- Link to Ws2_32.lib library (winsock)
    end
target_end()

-- Define the test executable target
target("xynd-test")
    set_kind("binary") -- This will produce an executable
    add_includedirs("server/include", "client/include") -- Header files
    add_files("tests/*.cpp")  -- Source files
    add_packages("spdlog") -- Link dependencies
target_end()

-- Clean up build files
task("clean")
    on_run(function ()
        os.rm("build")
    end)
