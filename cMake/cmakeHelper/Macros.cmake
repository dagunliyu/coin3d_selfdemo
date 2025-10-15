

macro(SET_BIN_DIR ProjectName OutputName)
    set_target_properties(${ProjectName} PROPERTIES OUTPUT_NAME ${OutputName})

    if(${ARGC} GREATER 2)
        # VS_IDE (and perhaps others) make Release and Debug subfolders.  This removes them.
        set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}${ARGV2})
        set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}${ARGV2})
        set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}${ARGV2})
        set_target_properties(${ProjectName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}${ARGV2})
        set_target_properties(${ProjectName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}${ARGV2})
        set_target_properties(${ProjectName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}${ARGV2})
    else(${ARGC} GREATER 2)
        set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY         ${BIN_DIR}) # ${CMAKE_BINARY_DIR}/bin)
        set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}) # ${CMAKE_BINARY_DIR}/bin)
        set_target_properties(${ProjectName} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${BIN_DIR}) # ${CMAKE_BINARY_DIR}/bin)
        set_target_properties(${ProjectName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY         ${BIN_DIR}/lib) # ${CMAKE_BINARY_DIR}/lib)
        set_target_properties(${ProjectName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR}/lib) # ${CMAKE_BINARY_DIR}/lib)
        set_target_properties(${ProjectName} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${BIN_DIR}/lib) # ${CMAKE_BINARY_DIR}/lib)
    endif(${ARGC} GREATER 2)

endmacro(SET_BIN_DIR)