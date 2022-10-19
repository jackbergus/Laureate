cmake_minimum_required(VERSION 3.22)
project(VideoGameDebugging)

set(CMAKE_CXX_STANDARD 20)

include_directories(Common)
include_directories(CSC8599Common)
include_directories(CSC8503/CSC8503Common)
add_library(common CSC8599Common/AbstractComponent.cpp
                   CSC8599Common/AbstractStateMachine.cpp
                   CSC8599Common/AdaptiveDebugSystem.cpp
        CSC8599Common/Character.cpp
        CSC8599Common/DebugStateMachine.cpp
        CSC8599Common/Dragon.cpp
        CSC8599Common/EventSystem.cpp
        CSC8599Common/Monster.cpp
        CSC8599Common/Pet.cpp
        CSC8599Common/PlalyerAIController.cpp
        CSC8599Common/Player.cpp
        CSC8599Common/State.cpp
        CSC8599Common/StateMachine.cpp
        CSC8599Common/StateMachinePlus.cpp
        CSC8599Common/StateTransition.cpp
        CSC8503/CSC8503Common/GameWorld.cpp
        Common/GameTimer.cpp)