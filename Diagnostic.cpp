#include <iostream>
#include <chrono>
//#include <math.h>

#include <Windows.h>
#include <psapi.h>

#include <vector>

int primeGenerator(const int range, const bool print, MEMORYSTATUSEX& memInfo, PROCESS_MEMORY_COUNTERS_EX& pmc);
struct smallStrct;

template <typename N>
int createStruct(const int count);

int createSmallStruct(const int count);

int main()
{
    system("title DIAGNOSTIC");
    std::cout << "Welcome to Diagnostic by LegendsZ#1526 @ Discord\nSingle Thread\n\n";
    std::cout << "Calculating system specs...";

    //TOTAL
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

    //BY THIS PROGRAM
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    std::cout << "OK!\n\n";

    std::cout << "Total virtual memory: " << totalVirtualMem << " bytes!\n";
    std::cout << "Total physical memory: " << memInfo.ullTotalPhys << " bytes!\n\n";

    std::cout << "\nReady to run diagnostic tests!\n\n";
    system("pause");

    int range = 100000;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int found = primeGenerator(range, false, memInfo, pmc);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "\nFound " << found << " prime numbers under " << range << " in " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << " ns!\n";

    
    range = 3;
    begin = std::chrono::steady_clock::now();
    //createStruct<smallStrct>(range);
    createSmallStruct(range);
    end = std::chrono::steady_clock::now();
    std::cout << "\nCreated & deleted " << range << " small structs in " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << " ns!\n\n";
    
    system("pause");
}

struct smallStrct {
private:
    int* FiveInts = nullptr;
    int size;
public:
    smallStrct():size(5) {   
        /*FiveInts = new int[5];
        for (int i = 0; i < size; i++) {
            FiveInts[i] = INT_MAX;
        }*/
        size = 4;
    }
    /*~smallStrct() {
        for (int i = size - 1; i >= 0; i--) {
            delete& FiveInts[i];
        }
    }*/
};

int createSmallStruct(const int count) {
    std::cout << "Creating...\n";
    int counter = 0;
    std::vector<smallStrct> NVec;
    for (counter = 0; counter < count; counter++) {
        smallStrct* strct = new smallStrct();
        NVec.push_back(*strct);
    }
    for (int i = NVec.size() - 1; i >= 0; i--) {
        delete& NVec[i];
    }
    return 1;
}

template <typename N>
int createStruct(const int count) {
    std::cout << "Creating...\n";
    int counter = 0;
    std::vector<N> NVec;
    for (counter = 0; counter < count; counter++) {
        N* strct = new N();
        NVec.push_back(*strct);
    }
    for (int i = NVec.size() - 1; i >= 0; i--) {
        delete &NVec[i];
    }
    return 1;
}

int primeGenerator(const int range, const bool print, MEMORYSTATUSEX& memInfo, PROCESS_MEMORY_COUNTERS_EX& pmc) {
    int found = 0;
    //SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

    for (int i = 2; i < range + 1; i++) {
        bool isPrime = true;
        for (int p = int(i/2); p > 1; p--) {
            if (i % p == 0 && p != 1) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            if (print) { std::cout << i << "\n"; }
            found++;
        }
        /*else {
            if (physMemUsedByMe != pmc.WorkingSetSize) {
                system("cls");
                physMemUsedByMe = pmc.WorkingSetSize;
                std::cout << "Physical memory used by this program: " << physMemUsedByMe << " bytes!\n";
            }
        }*/
    }
    return found;
}