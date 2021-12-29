

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

struct UserInfo {
    HybridAnomalyDetector haDetector;
    vector<AnomalyReport> anomalyList;
};

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
protected:
	DefaultIO* dio;
public:
	Command(DefaultIO* dio):dio(dio){}
	virtual void execute()=0;
	virtual ~Command(){}
};

// implement here your command classes

class FileUploadOption : public Command {
private:
    string name;
public:
    explicit FileUploadOption(DefaultIO *dio, const string& name) : Command(dio), name(name) {
    }
    void execute() override {
        ofstream os(name);

        string line;
        while ((line = dio->read()) != "done") {
            os << line << '\n';
        }

        os.close();
    }
};

class UploadTimeSeries : public Command {
public:
    explicit UploadTimeSeries(DefaultIO *dio) : Command(dio) {}
    void execute() override {
        dio->write("Please upload your local train CSV file.\n");
        FileUploadOption uploader(dio, "trainCSV.csv");
        uploader.execute();
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        FileUploadOption uploader2(dio, "testCSV.csv");
        uploader2.execute();
        dio->write("Upload complete.\n");
    }
};

class AlgorithmSettings : public Command {
private:
    UserInfo &userInfo;
public:
    AlgorithmSettings(DefaultIO *dio, UserInfo& userInfo) : Command(dio), userInfo(userInfo) {
    }
    void execute() override {
        dio->write("The current correlation threshold is: "
            + to_string(userInfo.haDetector.getTopThreshold()) + "\n");
        dio->write("Type a new threshold");
        string input = dio->read();
        float asFloat = stof(input);
        while (asFloat < 0 || asFloat > 1) {
            dio->write("please choose a value between 0 and 1.\n");
            input = dio->read();
            asFloat = stof(input);
        }
        userInfo.haDetector.setTopThreshold(asFloat);
    }
};


#endif /* COMMANDS_H_ */
