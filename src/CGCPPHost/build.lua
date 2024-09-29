-- Host application for running the code
mox_project("cgcpp")
mox_cpp("C++20")
mox_console()

links { 
    "libcgcpp",
}
