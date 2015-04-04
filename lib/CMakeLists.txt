# Ooura FFT
enable_language(C)
set(Ooura_fft_SOURCES ooura/fft4g.c)

add_library(Ooura_fft ${Ooura_fft_SOURCES})

set(Kiss_fft_SOURCES kiss_fft/kiss_fft.c kiss_fft/kissfft.hh) 

add_library(Kiss_fft ${Kiss_fft_SOURCES})

include_directories(kiss_fft)


# UnitTest++
if(Aquila_BUILD_TESTS)
    add_subdirectory(unittestpp)
endif()
