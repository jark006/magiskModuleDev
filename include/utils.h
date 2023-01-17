#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>
#include <limits>
#include <set>
#include <map>

#include <cstdio>
#include <cerrno>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cstdarg>
#include <cstdlib>
#include <csignal>
#include <cctype>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sched.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/input.h>

#include <sys/un.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <sys/system_properties.h>

using std::set;
using std::map;
using std::stringstream;
using std::lock_guard;
using std::unique_ptr;
using std::ifstream;
using std::vector;
using std::string;
using std::thread;
using std::mutex;

using std::make_unique;
using std::to_string;



vector<string> splitString(const char* str, const char* delim);
vector<string> splitString(string& str, const char* delim);
string strReplace(string str, string str1, string str2);
string bin2Hex(const void* bytes, size_t len);

int readInt(const char* path);
string readString(const char* path);
size_t readString(const char* path, char* res, size_t Maxlen);
bool writeInt(const char* path, int value);
bool writeString(const char* path, const char* buff, size_t len);

bool startWith(const char* p1, const char* p2);
string parentDir(string path);

#endif
