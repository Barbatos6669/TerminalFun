#include <iostream>
#include <iomanip>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <sys/statvfs.h>

// System Statistics getter functions
float getCpuTempC();
double getCpuUsagePercent();
int getRamPercent();
int getDiskPercent();
std::string getUptime();

// terminal UI rendering funcitons
void printHeader();
void printCpuSection(float cpuTemp, double cpuUsage);
void printMemorySection(int piRam,int  piDisk);
void printUptime(std::string piUptime);
void printfooter();
                                                                                                    
int main() {	
	while(true){
		system("clear");

		float cpuTempeture = getCpuTempC();
		double usage = getCpuUsagePercent();
		int ram = getRamPercent();
		int disk = getDiskPercent();
		std::string uptime = getUptime();

		printHeader();
		printCpuSection(cpuTempeture, usage);
		printMemorySection(ram, disk);
		printUptime(uptime);
		printfooter();			
		sleep(1);
	}	

	return 0;
}

// System Statistics getter Function Defined
float getCpuTempC(){
	std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
	int tempMilliC = 0;
	if (file.is_open()) {
		file >> tempMilliC;
		file.close();
		return tempMilliC / 1000.0;
	} else {
		std::cerr << "Error: Unable to open temperature file." << std::endl;
		return -1.0; // Return an error value
	}
}
double getCpuUsagePercent() {
    static long prevIdle = 0, prevTotal = 0;

    std::ifstream file("/proc/stat");
    std::string line;
    std::getline(file, line);
    file.close();

    std::istringstream iss(line);
    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    long idleTime = idle + iowait;
    long totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    long diffIdle = idleTime - prevIdle;
    long diffTotal = totalTime - prevTotal;

    prevIdle = idleTime;
    prevTotal = totalTime;

    if (diffTotal == 0) return 0.0;
    return (100.0 * (diffTotal - diffIdle) / diffTotal);
}
int getRamPercent(){
    std::ifstream file("/proc/meminfo");
    std::string line;
    long total = 0, available = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        long value;
        std::string unit;
        iss >> key >> value >> unit;
        if (key == "MemTotal:") total = value;
        if (key == "MemAvailable:") available = value;
        if (total && available) break;
    }
    file.close();

    if (total == 0) return -1; // Error
    long used = total - available;
    return static_cast<int>((100.0 * used) / total);
}
int getDiskPercent(){
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) {
        // Error reading disk stats
        return -1;
    }
    unsigned long total = stat.f_blocks * stat.f_frsize;
    unsigned long free = stat.f_bfree * stat.f_frsize;
    unsigned long used = total - free;
    if (total == 0) return -1;
    return static_cast<int>((100.0 * used) / total);
}
std::string getUptime(){
    std::ifstream file("/proc/uptime");
    double uptimeSeconds = 0.0;
    if (file.is_open()) {
        file >> uptimeSeconds;
        file.close();
        int hours = static_cast<int>(uptimeSeconds) / 3600;
        int minutes = (static_cast<int>(uptimeSeconds) % 3600) / 60;
        int seconds = static_cast<int>(uptimeSeconds) % 60;
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds;
        return oss.str();
    }
    return "??:??:??";
}

// Terminal UI rendeing functions defined

void printHeader(){

	std::cout << std::setfill ('=') << std::setw (100) << "" << std::endl;
	std::cout << std::setfill (' ') << std::setw (100 / 2) <<  " Raspberry Pi Monitor " << std::endl;
	std::cout << std::setfill ('=') << std::setw (100) << "" << std::endl;
	std::cout << std::setfill (' ') << std::endl;
}
void printCpuSection(float cpuTemp, double cpuUsage){
	std::cout << std::left << std::setw(20) << "CPU Temp:"
		      << std::right << std::setw(12) << cpuTemp << " C" << std::endl;
	std::cout << std::left << std::setw(20) << "CPU Usage:"
		      << std::right << std::setw(12) << cpuUsage << " %" << std::endl;
}
void printMemorySection(int piRam,int  piDisk){
	std::cout << std::left << std::setw(20) << "RAM Usage:"
		      << std::right << std::setw(12) << piRam << " %" << std::endl;
	std::cout << std::left << std::setw(20) << "Disk Usage:"
		      << std::right << std::setw(12) << piDisk << " %" << std::endl;
}
void printUptime(std::string piUptime){
	std::cout << std::left << std::setw(20) << "Uptime:"
		      << std::right << std::setw(12) << piUptime << std::endl;
	std::cout << std::endl;
}
void printfooter(){
	std::cout << std::setfill ('=') << std::setw (100) << "" << std::endl;
	std::cout << std::setfill (' ') << " To exit, press Ctrl+C "<< std::endl;
	std::cout << std::setfill ('=') << std::setw (100) << "" << std::endl;
	std::cout << std::setfill (' ') << std::endl;
}


