#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


class TimeSeries{
private:
    map<string, vector<float>> table;
    vector<string> titles;

    vector<string> cut(string& line){
        vector<string> parts;
        std::string delimiter = ",";

        int pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos) {
            token = line.substr(0, pos);
            parts.push_back(token);
            line.erase(0, pos + delimiter.length());
        }
        token = line.substr(0, (line.length()));
        parts.push_back(token);
        line.erase(0, (line.length()));
        return parts;
    }

public:
    TimeSeries(const char* CSVfileName){
        ifstream is(CSVfileName);
        // Load first line into string
        string names;
        getline(is, names);
        titles = cut(names);
        for (int i=0; i < names.size(); i++) {
            table[titles[i]] = vector<float>();
        }

        string line;
        while (getline(is, line)) {
            vector<string> parts= cut(line);
            for(int i=0;i<parts.size();i++){
                table[titles[i]].push_back(stof(parts[i]));
            }
        }

    }

    // Get number of features
    int getNumFeatures() const {
        return table.size();
    }

    // Get number of rows in table
    int getNumRows() const {
        if (table.empty())
            return 0;
        return table.at(titles[0]).size();
    }

    vector<string> getTitles() const {
        return {titles};
    }

    vector<float> getData(const string& name) const {
        return {table.at(name)};
    }

};



#endif /* TIMESERIES_H_ */