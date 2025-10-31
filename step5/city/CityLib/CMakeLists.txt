project(CityLib)

set(SOURCE_FILES
        pch.h
        City.h City.cpp
        Tile.h Tile.cpp
        CityReport.h CityReport.cpp
        MemberReport.h MemberReport.cpp
        TileBuilding.h TileBuilding.cpp
        TileGarden.h TileGarden.cpp
        TileLandscape.h TileLandscape.cpp
        MainFrame.cpp MainFrame.h
        CityReport.cpp CityView.cpp CityView.h ids.h
        TileWater.cpp TileWater.h TileFirehouse.cpp
        TileFirehouse.h
        TileVisitor.h
        BuildingCounter.h
        BuildingVisitor.h
        BuildingCounter.cpp
        BuildingVisitor.cpp
        SlimedVisitor.cpp
        SlimedVisitor.h
        TrapVisitor.cpp
        TrapVisitor.h
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)