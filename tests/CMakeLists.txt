include( FetchContent )
find_package( Threads REQUIRED )

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
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