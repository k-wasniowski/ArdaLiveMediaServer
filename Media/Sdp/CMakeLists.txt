# Copyright 2023 The Arda Project Authors. All rights reserved.
#
# Copying, utilizing or revealing any part or entirety of this file
# and its contents without proper authorization is not allowed.

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Details DETAILS_SOURCES)
aux_source_directory(src/Details/abnf ABNF_SOURCES)
aux_source_directory(src/Details/builders BUILDERS_SOURCES)

add_library(Sdp
        STATIC
    ${SOURCES}
    ${DETAILS_SOURCES}
    ${ABNF_SOURCES}
    ${BUILDERS_SOURCES}
)

target_include_directories(Sdp
        PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Media/Sdp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Details
)

add_library(Media::Sdp ALIAS Sdp)