include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable (KinovaTest kinova_test.cpp )
target_link_libraries (KinovaTest  ${CONAN_LIBS} pthread gtest_main kinova utils)
add_test (NAME KinovaTest COMMAND KinovaTest)

add_executable (PDTest PD_test.cpp )
target_link_libraries (PDTest  ${CONAN_LIBS} pthread gtest_main utils)
add_test (NAME PDTest COMMAND PDTest)
