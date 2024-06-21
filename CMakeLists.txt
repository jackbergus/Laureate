cmake_minimum_required(VERSION 3.22)
project(language)
include_directories(include)
set(CMAKE_CXX_STANDARD 23)

add_library(debugstatemachine OBJECT
        src/statemachineplus/AbstractComponent.cpp
        include/statemachineplus/AbstractComponent.h
        src/statemachineplus/AbstractStateMachine.cpp
        include/statemachineplus/AbstractStateMachine.h
        src/statemachineplus/AbstractStateMachine.cpp include/statemachineplus/AbstractStateMachine.h
        src/statemachineplus/State.cpp
        include/statemachineplus/State.h
        src/statemachineplus/AdaptiveDebugSystem.cpp
        include/statemachineplus/AdaptiveDebugSystem.h
        src/statemachineplus/StateMachine.cpp
        include/statemachineplus/StateMachine.h
        src/statemachineplus/EventSystem.cpp
        include/statemachineplus/EventSystem.h
        src/statemachineplus/StateTransition.cpp
        include/statemachineplus/StateTransition.h
        src/statemachineplus/StateMachinePlus.cpp
        include/statemachineplus/StateMachinePlus.h
        src/statemachineplus/DebugStateMachine.cpp
        include/statemachineplus/DebugStateMachine.h)

add_executable(language main.cpp)
target_link_libraries(language debugstatemachine)

