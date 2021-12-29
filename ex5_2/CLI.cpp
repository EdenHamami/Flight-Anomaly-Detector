#include "CLI.h"

CLI::CLI(DefaultIO* dio) : dio(dio) {
}

void CLI::start() {
    const int NUM_OPTIONS = 5;
    UserInfo userInfo;
    Command *options[NUM_OPTIONS] = {
        new UploadTimeSeries(dio), new AlgorithmSettings(dio, userInfo)
    };
    string line;
    // Read line from user
    while (!(line = dio->read()).empty() && line != "6") {
        dio->write("Welcome to the Anomaly Detection Server.\n"
                   "Please choose an option:\n"
                   "1.upload a time series csv file\n"
                   "2.algorithm settings\n"
                   "3.detect anomalies\n"
                   "4.display results\n"
                   "5.upload anomalies and analyze results\n"
                   "6.exit\n");
        int commandNum = stoi(line); // Get option number
        options[commandNum - 1]->execute(); // Do command
    }

    // Free memory
    for (int i = 0; i < NUM_OPTIONS; i++)
        delete options[i];
}


CLI::~CLI() {
}

