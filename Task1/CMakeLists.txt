project(main)

option(float ON) 
option(double ON) 

if(float)
    add_definitions(-DFLOAT)
elseif(double)
    add_definitions(-DDOUBLE)
else()
    message("you didn't choose the type")
endif()
message( "float - " ${float})
message( "double - "${double})
add_executable(main main.cpp)





