cmake_minimum_required(VERSION 3.17)
project(Project_Karl_Landau5)

set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(Project_Karl_Landau5
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        AnomalyDetector.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        timeseries.cpp
        timeseries.h
        MinCircle.h
        MinCircle.cpp
        MainTrain.cpp
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        CLI.h
        CLI.cpp
        commands.h
        Server.h
        Server.cpp)
