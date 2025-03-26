-- Set project properties
set_project("xynd")
set_version("1.0.0")
set_languages("cxx20")

-- Set default project
set_default("xynd-demo")

-- Adds debugging symbols to the compilation
set_symbols("debug")
add_rules("mode.debug", "mode.release")

-- Add required dependancies
add_requires("fmt") 
add_requires("spdlog") 
add_requires("protobuf")

add_includedirs("shared")

-- Define the shared library target
target("xynd-shared")
    set_kind("headeronly")
    add_includedirs("shared")
target_end()

-- Define the client library target
target("xynd-client")
    set_kind("static") -- This will produce a library
    
    add_includedirs("shared/", "client/include") -- Header files
    add_files("client/src/*.cpp")  -- Source files
    
    add_deps("xynd-shared") -- Link dependencies
    add_packages("protobuf", "spdlog") -- Link libraries
        
    set_pcxxheader("client/pch.h")
    
    if is_plat("windows") then
        add_links("Ws2_32")
    end
target_end()

-- Define the server library target
target("xynd-server")
    set_kind("static") -- This will produce a library
    
    add_includedirs("shared/", "server/include") -- Header files
    add_files("server/src/*.cpp")  -- Source files
    
    add_deps("xynd-shared") -- Link dependencies
    add_packages("protobuf", "spdlog") -- Link libraries
    
    set_pcxxheader("server/pch.h")
    
    if is_plat("windows") then
        add_links("Ws2_32")
    end
target_end()

-- Define the executable target
target("xynd-demo")
    set_kind("binary") -- This will produce an executable
    
    add_includedirs("server/include", "client/include") -- Header files
    add_files("demo/*.cpp")  -- Source files
    
    add_deps("xynd-server", "xynd-client") -- Link dependencies
    add_packages("protobuf", "spdlog") -- Link libraries
target_end()

-- Clean up build files
task("clean")
    on_run(function ()
        os.rm("build")
    end)
