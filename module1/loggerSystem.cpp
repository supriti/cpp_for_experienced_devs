/*
Simple Logging System.
*/
#include <iostream>
#include <chrono> //for timestamps
#include <string>
#include <sstream>
#include <iomanip> //for put time
#include <thread> //for sleep_for
#include <vector>
#include <fstream>
#include <ctime>
#include <unordered_map>

// It's generally good practice to avoid 'using namespace std;' in headers or large scopes.
// For small examples or .cpp files, it's often tolerated.
using namespace std;

enum logType {
    INFO,
    LOG, 
    WARNING,
    ERROR
};

/*
Hold all the information about a single Log class.
*/
class LogEntry {
    chrono::system_clock::time_point timeStamp;
    logType type;
    string logMessage;
public:
    LogEntry(logType val, const std::string& msg)
    : timeStamp(chrono::system_clock::now()), type(val), logMessage(msg)
    {};

    friend ostream& operator<<(ostream& os, const LogEntry& log);
};

ostream& operator<<(ostream& os, const LogEntry& log) {
    ostringstream oss;
    string logTypeString;

    time_t tt = chrono::system_clock::to_time_t(log.timeStamp);
    tm tm_struct = *localtime(&tt);

    oss << "[" << put_time(&tm_struct, "%Y-%m-%d %H:%M:%S") << "]";
    switch(log.type) {
        case INFO: logTypeString="INFO";       break;
        case LOG: logTypeString="LOG";         break;
        case WARNING: logTypeString="WARNING"; break;
        case ERROR: logTypeString="ERROR";     break;
        default: logTypeString="UNKOWN";       break;

    }

    oss << "[" << logTypeString << "]" << ":" << log.logMessage;
    os << oss.str() << endl;
    return os;
}

/*
Holds and manages a collection of LogEntry class.
*/
class Logger {
    vector<LogEntry> logs;
    fstream logFileStream;
    string logFileName;
    unordered_map<logType, int> logMap;

    static string getLogTypeString(logType type) {
        switch(type) {
            case INFO: return "INFO";
            case LOG: return "LOG";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
public:
    Logger(const string& filename = "application.log"):logFileName(filename){
        logFileStream.open(logFileName, ios::out | ios::app);
        if (!logFileStream.is_open()){
            cerr << "File could not be open" << endl;
        }
        // Initialize log counts for all types to 0
        logMap[INFO] = 0;
        logMap[LOG] = 0;
        logMap[WARNING] = 0;
        logMap[ERROR] = 0;
    }

    ~Logger() {
        cout << "Logger shutting down. Flushing logs..." << endl;
        flushToFile();
        if (logFileStream.is_open()){
            logFileStream.close();
        }
    }

    void logInfo(const string& msg) {
        LogEntry log(INFO, msg);
        logs.push_back(log);
        cout << log;
        logMap[INFO]++;
    }

    void logWarning(const string& msg) {
        LogEntry log(WARNING, msg);
        logs.push_back(log);
        cout << log;
        logMap[WARNING]++;
    }

    void logError(const string& msg) {
        LogEntry log(ERROR, msg);
        logs.push_back(log);
        cout << log;
        logMap[ERROR]++;
    }
    
    void flushToFile() {
        if (logFileStream.is_open()){
            for(const auto& entry:logs){
                logFileStream << entry;
            }
        }
        logFileStream.flush();
        logs.clear();
    }

    void printStats() {
        for(auto const& it : logMap) {
            cout << "Total " << getLogTypeString(it.first) << " :" << it.second << endl;
        }
    }

};


int main(){
    Logger appLogger;

    cout << "\n --- Logging messages --- \n";
    appLogger.logInfo("Application started succesfully.");
    this_thread::sleep_for(chrono::milliseconds(100));
    appLogger.logWarning("Configuration file 'settings.ini' not found. Using defaults.");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    appLogger.logInfo("User 'Alice' logged in from IP 192.168.1.100.");
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    appLogger.logError("Database connection failed: Timeout occurred.");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    appLogger.logInfo("Processing data batch #42 completed.");

    appLogger.flushToFile();
    appLogger.printStats();
    cout << "\n--- End of main() ---\n";
    return 0;
}