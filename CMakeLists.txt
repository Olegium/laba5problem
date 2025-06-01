# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.10)

# Определение проекта
project(banking LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути для поиска заголовочных файлов
include_directories(${CMAKE_SOURCE_DIR}/include)

# Создание статической библиотеки banking
add_library(banking STATIC
    src/Account.cpp
    src/Transaction.cpp
)

# Указание, где искать заголовочные файлы для библиотеки
target_include_directories(banking PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Настройка тестов с использованием Google Test
# Скачиваем и собираем Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Создание тестового исполняемого файла
enable_testing()
add_executable(tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)
target_link_libraries(tests banking gtest_main)

# Регистрация тестов
include(GoogleTest)
gtest_discover_tests(tests)

# Установка цели для сборки тестов
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS tests
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")