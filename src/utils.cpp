#include "utils.h"

vector<string> splitString(const char* str, const char* delim) {
  if (*str == 0)return {};
  string ss(str);
  return splitString(ss, delim);
}

vector<string> splitString(string& str, const char* delim) {
  if (str.length() == 0) return {};
  if (*delim == 0) return { str };

  vector<string> res;
  size_t delimLen = strlen(delim);
  char* targetPtr = (char*)str.c_str();
  while (auto nextDelimPtr = strstr(targetPtr, delim)) {
    if (nextDelimPtr == targetPtr) {
      targetPtr += delimLen;
      continue;
    }
    res.emplace_back(string(targetPtr, nextDelimPtr - targetPtr));
    targetPtr = nextDelimPtr + delimLen;
  }
  if (targetPtr < (str.c_str() + str.length()))
    res.emplace_back(string(targetPtr, (str.c_str() + str.length()) - targetPtr));
  return res;
}

string strReplace(string str, string str1, string str2) {
  auto idx = str.find(str1);
  if (idx == string::npos)
    return str;
  str = str.replace(str.find(str1), str1.length(), str2);
  return strReplace(str, str1, str2);
}

string bin2Hex(const void* bytes, size_t len) {
  const char* charList = "0123456789ABCDEF";
  if (len == 0) return "";
  string res(len * 3, ' ');
  for (size_t i = 0; i < len; i++) {
    uint8_t& value = ((uint8_t*)bytes)[i];
    res[i * 3] = charList[value >> 4];
    res[i * 3 + 1] = charList[value & 0x0f];
  }
  return res;
}

int readInt(const char* path) {
  auto fd = open(path, O_RDONLY);
  if (fd < 0) return 0;
  char buff[16] = { 0 };
  auto len = read(fd, buff, sizeof(buff));
  close(fd);

  if (len == 0)return 0;
  buff[15] = 0;
  return atoi(buff);
}

string readString(const char* path) {
  char buff[64 * 1024];
  readString(path, buff, sizeof(buff));
  return string(buff);
}

size_t readString(const char* path, char* res, size_t Maxlen) {
  auto fd = open(path, O_RDONLY);
  if (fd <= 0) { res[0] = 0; return 0; }
  size_t len = read(fd, res, Maxlen);
  close(fd);
  res[len < Maxlen ? len : Maxlen - 1] = 0; // 终止符
  return len;
}

bool writeInt(const char* path, int value) {
  auto fd = open(path, O_WRONLY);
  if (fd <= 0) return false;

  char tmp[8];
  auto len = snprintf(tmp, sizeof(tmp), "%d", value);
  write(fd, tmp, len);
  close(fd);
  return true;
}

bool writeString(const char* path, const char* buff, size_t len) {
  auto fd = open(path, O_WRONLY);
  if (fd <= 0) return false;

  write(fd, buff, len);
  close(fd);
  return true;
}

bool startWith(const char* prefix, const char* target) {
  int idx = 0;
  while (prefix[idx]) {
    if (prefix[idx] != target[idx])
      return false;
    idx++;
  }
  return true;
}

string parentDir(string path) {
  if (path.back() == '/')
    path.pop_back();
  auto idx = path.find_last_of('/');
  return idx == string::npos ? path : path.substr(0, idx);
}

