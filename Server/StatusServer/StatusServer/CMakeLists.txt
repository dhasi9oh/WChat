# CMakeList.txt: StatusServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
file(GLOB_RECURSE ICD_FILES "./*.h")
file(GLOB_RECURSE SRC_FILES "./*.cpp" "./*.cc")

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/con"
    "${CMAKE_CURRENT_SOURCE_DIR}/dao"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils"
    "${CMAKE_CURRENT_SOURCE_DIR}/service"
    "${CMAKE_CURRENT_SOURCE_DIR}/session"
)

add_executable(StatusServer ${ICD_FILES}  ${SRC_FILES})

# 将配置文件复制到输出目录。
configure_file(
    config.ini
    ${CMAKE_BINARY_DIR}/config.ini
    COPYONLY)

# 设置项目的依赖项。
target_link_libraries (StatusServer PUBLIC
    fmt
    spdlog
    jsoncpp
    protobuf
    hiredis
    grpc
    grpc++
    upb
    z
    ssl
    mysqlcppconn
    boost_filesystem
    boost_system
    crypto
    absl_bad_optional_access
    absl_bad_variant_access
    absl_base
    absl_city
    absl_civil_time
    absl_cord
    absl_debugging_internal
    absl_demangle_internal
    absl_exponential_biased
    absl_graphcycles_internal
    absl_hash
    absl_hashtablez_sampler
    absl_int128
    absl_log_severity
    absl_malloc_internal
    absl_raw_hash_set
    absl_raw_logging_internal
    absl_spinlock_wait
    absl_stacktrace
    absl_status
    absl_strings
    absl_strings_internal
    absl_str_format_internal
    absl_symbolize
    absl_synchronization
    absl_throw_delegate
    absl_time
    absl_time_zone
    re2
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET StatusServer PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
