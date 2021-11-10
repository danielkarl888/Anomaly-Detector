cmake_minimum_required(VERSION 3.17)
project(Project_Karl_Landau5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_Karl_Landau5
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        MainTrain.cpp
        AnomalyDetector.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        timeseries.h
        timeseries.cpp
        )
