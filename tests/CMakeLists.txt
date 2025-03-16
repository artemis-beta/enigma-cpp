include( FetchContent )
find_package( Threads REQUIRED )
cmake_policy(SET CMP0135 NEW)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set( gtest_force_shared_crt ON CACHE BOOL "" FORCE )

FetchContent_MakeAvailable( googletest )

# assume built-in pthreads on MacOS
IF( APPLE )
    set( CMAKE_THREAD_LIBS_INIT "-lpthread")
    set( CMAKE_HAVE_THREADS_LIBRARY 1)
    set( CMAKE_USE_WIN32_THREADS_INIT 0)
    set( CMAKE_USE_PTHREADS_INIT 1)
    set( THREADS_PREFER_PTHREAD_FLAG ON)
ENDIF( APPLE )

enable_testing()

add_subdirectory( unit_tests )