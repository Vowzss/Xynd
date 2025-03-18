-- xmake.lua

-- Set project properties
set_project("xynd")
set_version("1.0.0")
set_languages("cxx20")

-- Define the shared source directories
add_includedirs("common")

-- adds debugging symbols to the compilation
set_symbols("debug")

-- Define the client executable target
target("xynd-client")
    set_kind("binary") -- This will produce an executable
    add_files("client/*.cpp") -- Source files
    add_includedirs("client/include") -- Header files
    add_packages("protobuf") -- Link dependencies

    if is_plat("windows") then
        add_links("Ws2_32")  -- Link to Ws2_32.lib library (winsock)
    end
target_end()

-- Define the server executable target
target("xynd-server")
    set_kind("binary") -- This will produce an executable
    add_files("server/*.cpp") -- Source files
    add_includedirs("server/include") -- Header files
    add_packages("protobuf") -- Link dependencies

    if is_plat("windows") then
        add_links("Ws2_32")  -- Link to Ws2_32.lib library (winsock)
    end
target_end()

-- Clean up build files
task("clean")
    on_run(function ()
        os.rm("build")
    end)
