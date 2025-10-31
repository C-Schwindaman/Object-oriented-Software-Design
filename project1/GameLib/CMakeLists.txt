project(GameLib)

set(SOURCE_FILES pch.h MainFrame.h MainFrame.cpp Sparty.cpp Sparty.h
        Player.cpp
        Player.h
        Game.cpp
        Game.h
        Item.cpp
        Item.h
        GameView.cpp
        GameView.h
        Chest.h
        Chest.cpp
        Container.h
        Container.cpp
        Letter.cpp
        Letter.h
        Given.cpp
        Given.h
        Visitor.cpp
        Visitor.h
        LevelLoader.cpp
        LevelLoader.h
        Tray.cpp
        Tray.h
        Scoreboard.cpp
        Scoreboard.h
        ItemVisitor.h
        DrawVisitor.cpp
        DrawVisitor.h
        UpdateVisitor.cpp
        UpdateVisitor.h
        HeadButtVisitor.cpp
        HeadButtVisitor.h
        PopUpWindow.cpp
        SolveVisitor.cpp
        SolveVisitor.h
        GameWord.cpp
        GameWord.h
        GameObj.h
        GameObj.cpp
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

