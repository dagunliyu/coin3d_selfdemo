


# # 添加每个sdk子目录
# foreach(sdk ${SDK_SUBDIRS})
#     if(IS_DIRECTORY "${SDK_DIR}/${sdk}")
#         add_subdirectory("${SDK_DIR}/${sdk}")
#     endif()
# endforeach()


# 查找sdk目录下所有子目录
# file(GLOB SDK_SUBDIRS RELATIVE ${SDK_DIR} ${SDK_DIR}/*)
