#ifndef _PROP_H_
#define _PROP_H_

#include "utils.h"

class Prop
{
private:
  string propPath;
  map<string, string> prop = {
    {"id", "Unknown"},
    {"name", "Unknown"},
    {"version", "Unknown"},
    {"versionCode", "0"},
    {"author", "Unknown"},
    {"description", "Unknown"},
  };

public:
  Prop& operator=(Prop&&) = delete;

  Prop(string _propPath):propPath(_propPath) {
    auto fp = fopen(propPath.c_str(), "r");
    if (!fp) {
      return;
    }

    char tmp[1024];
    while (!feof(fp)) {
      fgets(tmp, sizeof(tmp), fp);
      if (!isalpha(tmp[0])) continue;
      tmp[sizeof(tmp) - 1] = 0;
      auto ptr = strstr(tmp, "=");
      if (ptr == nullptr)continue;

      *ptr = 0;
      for (size_t i = (ptr - tmp) + 1; i < sizeof(tmp); i++) {
        if (tmp[i] == '\n' || tmp[i] == '\r') {
          tmp[i] = 0;
          break;
        }
      }
      prop[string(tmp)] = string(ptr + 1);
    }
    fclose(fp);
  }

  ~Prop() { }

  string& operator[](string key) {
    return prop[key];
  }

  bool save2file() {
    auto fp = fopen(propPath.c_str(), "wb");
    if (!fp)
      return false;

    char tmp[512];
    size_t len = snprintf(tmp, 512, "id=%s\nname=%s\nversion=%s\nversionCode=%s\nauthor=%s\ndescription=%s\n",
      prop["id"].c_str(), prop["name"].c_str(), prop["version"].c_str(), prop["versionCode"].c_str(),
      prop["author"].c_str(), prop["description"].c_str());

    size_t writeLen = fwrite(tmp, 1, len, fp);
    fclose(fp);

    return (writeLen == len) ? true : false;
  }

};

#endif