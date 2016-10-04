
add_definitions(-DWIN32)

set(SRC
    Application.cpp
    BspCollision.cpp
    BspEntity.cpp
    BspFace.cpp
    BspGeometry.cpp
    BspLeaf.cpp
    BspLoader.cpp
    BspNode.cpp
    BspObject.cpp
    BspProp.cpp
    BspWorld.cpp
    Console.cpp
    FreeTypeFont.cpp
    HlBspData.cpp
    HlBspWorld.cpp
    main.cpp
    Q3BspData.cpp
    Q3BspWorld.cpp
    RenderMode.cpp
    RenderOptions.cpp
    SkyBox.cpp
    TextureLoader.cpp
)

set(SRC_COMMON
    common/boundingbox.cpp
    common/camera.cpp
    common/common.cpp
    common/data.cpp
    common/math3d.cpp
    common/plane.cpp
    common/thread.cpp
    common/tokenizer.cpp
    common/vector3.cpp
)

set(SRC_FS
    fs/File.cpp
    fs/FileSystem.cpp
    fs/FileSystemException.cpp
    fs/Package.cpp
    fs/Resource.cpp
    fs/WadPackage.cpp
    fs/ZipPackage.cpp
    fs/image/bitmap.cpp
#    fs/image/jpeg.cpp
    fs/image/miptex.cpp
#    fs/image/png.cpp
    fs/image/targa.cpp
    fs/image/texture.cpp
    fs/mesh/Mdl.cpp
    fs/mesh/Mesh.cpp
    fs/mesh/hlsdk/cmdlib.c
    fs/mesh/hlsdk/mathlib.c
    fs/mesh/hlsdk/studio_render.cpp
    fs/mesh/hlsdk/studio_utils.cpp
    fs/zip/ioapi.c
    fs/zip/mztools.c
    fs/zip/unzip.c
    fs/zip/zip.c
    )

find_library(FREETYPE_LIBRARY
    NAMES libfreetype.dll
    PATHS lib/freetype2/lib
    )
include_directories(lib/freetype2/include)

#Dependency check
find_package(zlib REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

add_executable(learnbsp 
    ${SRC}
    ${SRC_COMMON}
    ${SRC_FS}
    )

target_link_libraries(learnbsp 
    ${ZLIB_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLFW3_LIBRARY}
    ${FREETYPE_LIBRARY}
    )
