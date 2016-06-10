add_executable(hfrtc hfrtc.cpp)
target_link_libraries(hfrtc tinyutil pthread lua)

add_executable(admin admin.cpp)
target_link_libraries(admin tinyutil pthread lua)

add_executable(uas uas.cpp)
target_link_libraries(uas tinyutil pthread lua)