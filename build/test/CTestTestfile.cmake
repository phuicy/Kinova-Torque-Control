# CMake generated Testfile for 
# Source directory: /home/phuicy/workspace/kinova-unilateral/test
# Build directory: /home/phuicy/workspace/kinova-unilateral/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(KinovaTest "/home/phuicy/workspace/kinova-unilateral/build/bin/KinovaTest")
set_tests_properties(KinovaTest PROPERTIES  _BACKTRACE_TRIPLES "/home/phuicy/workspace/kinova-unilateral/test/CMakeLists.txt;12;add_test;/home/phuicy/workspace/kinova-unilateral/test/CMakeLists.txt;0;")
add_test(PDTest "/home/phuicy/workspace/kinova-unilateral/build/bin/PDTest")
set_tests_properties(PDTest PROPERTIES  _BACKTRACE_TRIPLES "/home/phuicy/workspace/kinova-unilateral/test/CMakeLists.txt;16;add_test;/home/phuicy/workspace/kinova-unilateral/test/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
