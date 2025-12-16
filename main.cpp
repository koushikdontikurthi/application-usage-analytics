#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
using namespace std;

// This struct just stores one line of our CSV file
struct Log {
    string user_id;
    string region;
    string application;
    string login_time;
    int duration;
};

int main() {
    vector<Log> logs;
    ifstream file("data.csv");

    if (!file.is_open()) {
        cout << "Cannot open file!" << endl;
        return 0;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        Log log;
        string temp;

        getline(ss, log.user_id, ',');
        getline(ss, log.region, ',');
        getline(ss, log.application, ',');
        getline(ss, log.login_time, ',');
        getline(ss, temp, ',');
        log.duration = stoi(temp);

        logs.push_back(log);
    }

    // Now, calculate total and average duration
    int totalDuration = 0;
    map<string, int> appCount;
    map<string, int> userTime;
    map<string, int> regionDuration;


    for (auto &log : logs) {
        totalDuration += log.duration;
        appCount[log.application]++;
        userTime[log.user_id] += log.duration;
    }

    double avg = (double)totalDuration / logs.size();

    // Find most used app
    string mostUsedApp;
    int maxAppCount = 0;
    for (auto &pair : appCount) {
        if (pair.second > maxAppCount) {
            maxAppCount = pair.second;
            mostUsedApp = pair.first;
        }
    }

    // Find user with most total time
    string topUser;
    int maxUserTime = 0;
    for (auto &pair : userTime) {
        if (pair.second > maxUserTime) {
            maxUserTime = pair.second;
            topUser = pair.first;
        }
    }



    cout << "Total records: " << logs.size() << endl;
    cout << "Average duration: " << avg << " minutes" << endl;
    cout << "App usage count:\n";
    for (auto &pair : appCount) {
        cout << "  " << pair.first << ": " << pair.second << endl;
    }
    cout << "\nMost used app: " << mostUsedApp << " (" << maxAppCount << " sessions)" << endl;
    cout << "User who spent the most total time: " << topUser << " (" << maxUserTime << " minutes)" << endl;
    // --- App and Region Breakdown Reports ---

    // App usage breakdown
    ofstream appReport("app_usage_breakdown.csv");
    if (appReport.is_open()) {
        appReport << "Application,Sessions\n";
        for (auto &pair : appCount) {
            appReport << pair.first << "," << pair.second << "\n";
        }
        appReport.close();
        cout << "app_usage_breakdown.csv exported successfully!\n";
    } else {
        cout << "Could not create app_usage_breakdown.csv\n";
    }

    // Regional performance breakdown
    ofstream regionReport("region_performance.csv");
    if (regionReport.is_open()) {
        regionReport << "Region,TotalDuration\n";
        for (auto &log : logs) {
            regionDuration[log.region] += log.duration;
        }
        for (auto &pair : regionDuration) {
            regionReport << pair.first << "," << pair.second << "\n";
        }
        regionReport.close();
        cout << "region_performance.csv exported successfully!\n";
    } else {
        cout << "Could not create region_performance.csv\n";
    }

        // --- Export results to CSV file ---
        // --- Create filename with current date and time ---
    time_t now = time(0);
    tm* localTime = localtime(&now);
    stringstream filename;
    filename << "report_"
             << (1900 + localTime->tm_year) << "-"
             << setfill('0') << setw(2) << (1 + localTime->tm_mon) << "-"
             << setfill('0') << setw(2) << localTime->tm_mday << "_"
             << setfill('0') << setw(2) << localTime->tm_hour << "-"
             << setfill('0') << setw(2) << localTime->tm_min << "-"
             << setfill('0') << setw(2) << localTime->tm_sec
             << ".csv";

    string fileName = filename.str();
    ofstream report(fileName);

    if (report.is_open()) {
        report << "Metric,Value\n";
        report << "Total Records," << logs.size() << "\n";
        report << "Average Duration (mins)," << avg << "\n";
        report << "Most Used App," << mostUsedApp << "\n";
        report << "Most Used App Sessions," << maxAppCount << "\n";
        report << "Top User (Most Time)," << topUser << "\n";
        report << "Top User Total Time (mins)," << maxUserTime << "\n";
        report.close();
        cout << "\n Results exported to report.csv successfully!\n";
    } else {
        cout << "\n Error: Could not create report.csv file.\n";
    }



    return 0;
}
