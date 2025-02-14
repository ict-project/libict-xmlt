################################################################
cmake_minimum_required(VERSION 3.25)
################################################################
set(LIBRARY_NAME "xmlt")
set(LIBRARY_DESC "Handy XML template library based on C++20 templates.")

project(libict-${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 20)
find_package(Threads)

include(../libict-dev-tools/libs-include.cmake)
include(../libict-dev-tools/info-include.cmake)
include(../libict-dev-tools/test-include.cmake)
include(../libict-dev-tools/git-include.cmake)

file(GLOB CMAKE_HEADER_LIST . *.hpp)

set(CMAKE_SOURCE_FILES 
  info.cpp
  literal.cpp
  param.cpp
  xml-data.cpp
  xml-interface.cpp
  xml-nil.cpp
  xml-text.cpp
  xml-cdata.cpp
  xml-comment.cpp
  xml-attribute.cpp
  xml-element.cpp
  xml-instruction.cpp
  xml-doctype.cpp
  xml-set.cpp
  xml-array.cpp
  xml-pick.cpp
  xml-name.cpp
)

add_library(ict-static-${LIBRARY_NAME} STATIC ${CMAKE_SOURCE_FILES})
target_link_libraries(ict-static-${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ict-static-${LIBRARY_NAME}  PROPERTIES OUTPUT_NAME ict-${LIBRARY_NAME})

add_library(ict-shared-${LIBRARY_NAME} SHARED ${CMAKE_SOURCE_FILES})
target_link_libraries(ict-shared-${LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(ict-shared-${LIBRARY_NAME}  PROPERTIES OUTPUT_NAME ict-${LIBRARY_NAME})

add_executable(${PROJECT_NAME}-test ${CMAKE_HEADER_LIST} test.cpp)
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME}-test ict-static-${LIBRARY_NAME})
target_link_libraries(${PROJECT_NAME}-test ${CMAKE_LINK_LIBS})
target_compile_definitions(${PROJECT_NAME}-test PUBLIC -DENABLE_TESTING)

################################################################
install(TARGETS ict-static-${LIBRARY_NAME} ict-shared-${LIBRARY_NAME} DESTINATION lib COMPONENT libraries)
install(
  FILES ${HEADER_LIST}
  DESTINATION include/libict/${LIBRARY_NAME} COMPONENT headers
)
################################################################
enable_testing()

add_test(NAME ict-literal-tc1 COMMAND ${PROJECT_NAME}-test ict literal tc1)
add_test(NAME ict-literal-tc2 COMMAND ${PROJECT_NAME}-test ict literal tc2)
add_test(NAME ict-literal-tc3 COMMAND ${PROJECT_NAME}-test ict literal tc3)
add_test(NAME ict-literal-tc4 COMMAND ${PROJECT_NAME}-test ict literal tc4)
add_test(NAME ict-literal-tc5 COMMAND ${PROJECT_NAME}-test ict literal tc5)
add_test(NAME ict-literal-tc6 COMMAND ${PROJECT_NAME}-test ict literal tc6)
add_test(NAME ict-literal-tc7 COMMAND ${PROJECT_NAME}-test ict literal tc7)
add_test(NAME ict-literal-tc8 COMMAND ${PROJECT_NAME}-test ict literal tc8)
add_test(NAME ict-literal-tc9 COMMAND ${PROJECT_NAME}-test ict literal tc9)
add_test(NAME ict-literal-tc10 COMMAND ${PROJECT_NAME}-test ict literal tc10)
add_test(NAME ict-literal-tc11 COMMAND ${PROJECT_NAME}-test ict literal tc11)
add_test(NAME ict-param-tc1 COMMAND ${PROJECT_NAME}-test ict param tc1)
add_test(NAME ict-param-tc2 COMMAND ${PROJECT_NAME}-test ict param tc2)
add_test(NAME ict-param-tc3 COMMAND ${PROJECT_NAME}-test ict param tc3)
add_test(NAME ict-param-tc4 COMMAND ${PROJECT_NAME}-test ict param tc4)
add_test(NAME ict-param-tc5 COMMAND ${PROJECT_NAME}-test ict param tc5)
add_test(NAME ict-param-tc6 COMMAND ${PROJECT_NAME}-test ict param tc6)
add_test(NAME ict-param-tc7 COMMAND ${PROJECT_NAME}-test ict param tc7)
add_test(NAME ict-param-tc8 COMMAND ${PROJECT_NAME}-test ict param tc8)
add_test(NAME ict-param-tc9 COMMAND ${PROJECT_NAME}-test ict param tc9)
add_test(NAME ict-param-tc10 COMMAND ${PROJECT_NAME}-test ict param tc10)
add_test(NAME ict-param-tc11 COMMAND ${PROJECT_NAME}-test ict param tc11)
add_test(NAME ict-param-tc12 COMMAND ${PROJECT_NAME}-test ict param tc12)
add_test(NAME ict-param-tc13 COMMAND ${PROJECT_NAME}-test ict param tc13)
add_test(NAME ict-param-tc14 COMMAND ${PROJECT_NAME}-test ict param tc14)
add_test(NAME ict-param-tc15 COMMAND ${PROJECT_NAME}-test ict param tc15)
add_test(NAME ict-param-tc16 COMMAND ${PROJECT_NAME}-test ict param tc16)
add_test(NAME ict-param-tc17 COMMAND ${PROJECT_NAME}-test ict param tc17)
add_test(NAME ict-param-tc18 COMMAND ${PROJECT_NAME}-test ict param tc18)
add_test(NAME ict-param-tc19 COMMAND ${PROJECT_NAME}-test ict param tc19)
add_test(NAME ict-param-tc20 COMMAND ${PROJECT_NAME}-test ict param tc20)
add_test(NAME ict-param-tc21 COMMAND ${PROJECT_NAME}-test ict param tc21)
add_test(NAME ict-param-tc22 COMMAND ${PROJECT_NAME}-test ict param tc22)
add_test(NAME ict-param-tc23 COMMAND ${PROJECT_NAME}-test ict param tc23)
add_test(NAME ict-param-tc24 COMMAND ${PROJECT_NAME}-test ict param tc24)
add_test(NAME ict-xml_html-tc1 COMMAND ${PROJECT_NAME}-test ict xml_html tc1)
add_test(NAME ict-xml_html-tc2 COMMAND ${PROJECT_NAME}-test ict xml_html tc2)
add_test(NAME ict-xml_nil-tc1 COMMAND ${PROJECT_NAME}-test ict xml_nil tc1)
add_test(NAME ict-xml_text-tc1 COMMAND ${PROJECT_NAME}-test ict xml_text tc1)
add_test(NAME ict-xml_text-tc2 COMMAND ${PROJECT_NAME}-test ict xml_text tc2)
add_test(NAME ict-xml_text-tc3 COMMAND ${PROJECT_NAME}-test ict xml_text tc3)
add_test(NAME ict-xml_text-tc4 COMMAND ${PROJECT_NAME}-test ict xml_text tc4)
add_test(NAME ict-xml_cdata-tc1 COMMAND ${PROJECT_NAME}-test ict xml_cdata tc1)
add_test(NAME ict-xml_cdata-tc2 COMMAND ${PROJECT_NAME}-test ict xml_cdata tc2)
add_test(NAME ict-xml_cdata-tc3 COMMAND ${PROJECT_NAME}-test ict xml_cdata tc3)
add_test(NAME ict-xml_cdata-tc4 COMMAND ${PROJECT_NAME}-test ict xml_cdata tc4)
add_test(NAME ict-xml_comment-tc1 COMMAND ${PROJECT_NAME}-test ict xml_comment tc1)
add_test(NAME ict-xml_comment-tc2 COMMAND ${PROJECT_NAME}-test ict xml_comment tc2)
add_test(NAME ict-xml_comment-tc3 COMMAND ${PROJECT_NAME}-test ict xml_comment tc3)
add_test(NAME ict-xml_comment-tc4 COMMAND ${PROJECT_NAME}-test ict xml_comment tc4)
add_test(NAME ict-xml_attribute-tc1 COMMAND ${PROJECT_NAME}-test ict xml_attribute tc1)
add_test(NAME ict-xml_attribute-tc2 COMMAND ${PROJECT_NAME}-test ict xml_attribute tc2)
add_test(NAME ict-xml_attribute-tc3 COMMAND ${PROJECT_NAME}-test ict xml_attribute tc3)
add_test(NAME ict-xml_attribute-tc4 COMMAND ${PROJECT_NAME}-test ict xml_attribute tc4)
add_test(NAME ict-xml_element-tc1 COMMAND ${PROJECT_NAME}-test ict xml_element tc1)
add_test(NAME ict-xml_element-tc2 COMMAND ${PROJECT_NAME}-test ict xml_element tc2)
add_test(NAME ict-xml_element-tc3 COMMAND ${PROJECT_NAME}-test ict xml_element tc3)
add_test(NAME ict-xml_instruction-tc1 COMMAND ${PROJECT_NAME}-test ict xml_instruction tc1)
add_test(NAME ict-xml_instruction-tc2 COMMAND ${PROJECT_NAME}-test ict xml_instruction tc2)
add_test(NAME ict-xml_doctype-tc1 COMMAND ${PROJECT_NAME}-test ict xml_doctype tc1)
add_test(NAME ict-xml_set-tc1 COMMAND ${PROJECT_NAME}-test ict xml_set tc1)
add_test(NAME ict-xml_set-tc2 COMMAND ${PROJECT_NAME}-test ict xml_set tc2)
add_test(NAME ict-xml_set-tc3 COMMAND ${PROJECT_NAME}-test ict xml_set tc3)
add_test(NAME ict-xml_set-tc4 COMMAND ${PROJECT_NAME}-test ict xml_set tc4)
add_test(NAME ict-xml_array-tc1 COMMAND ${PROJECT_NAME}-test ict xml_array tc1)
add_test(NAME ict-xml_array-tc2 COMMAND ${PROJECT_NAME}-test ict xml_array tc2)
add_test(NAME ict-xml_array-tc3 COMMAND ${PROJECT_NAME}-test ict xml_array tc3)
add_test(NAME ict-xml_array-tc4 COMMAND ${PROJECT_NAME}-test ict xml_array tc4)
add_test(NAME ict-xml_array-tc5 COMMAND ${PROJECT_NAME}-test ict xml_array tc5)
add_test(NAME ict-xml_pick-tc1 COMMAND ${PROJECT_NAME}-test ict xml_pick tc1)
add_test(NAME ict-xml_pick-tc2 COMMAND ${PROJECT_NAME}-test ict xml_pick tc2)
add_test(NAME ict-xml_pick-tc3 COMMAND ${PROJECT_NAME}-test ict xml_pick tc3)
add_test(NAME ict-xml_pick-tc4 COMMAND ${PROJECT_NAME}-test ict xml_pick tc4)
add_test(NAME ict-xml_name-tc1 COMMAND ${PROJECT_NAME}-test ict xml_name tc1)
add_test(NAME ict-xml_name-tc2 COMMAND ${PROJECT_NAME}-test ict xml_name tc2)
add_test(NAME ict-xml_name-tc3 COMMAND ${PROJECT_NAME}-test ict xml_name tc3)

################################################################
include(../libict-dev-tools/cpack-include.cmake)
################################################################
