cmake_minimum_required(VERSION 3.0)
project(ex5_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex5_2 MainTrain.cpp
        anomaly_detection_util.h anomaly_detection_util.cpp
        CLI.h CLI.cpp
        commands.h
        AnomalyDetector.h
        HybridAnomalyDetector.h HybridAnomalyDetector.cpp
        minCircle.h minCircle.cpp
        SimpleAnomalyDetector.h SimpleAnomalyDetector.cpp
        timeseries.h timeseries.cpp

        )
