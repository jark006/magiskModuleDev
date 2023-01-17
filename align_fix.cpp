
// From https://github.com/Lzhiyong/termux-ndk/blob/master/patches/align_fix.py

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <fstream>

using std::string;
using std::vector;
using std::cout;
using std::to_string;

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

static string bin2Hex(const uint8_t* bytes, size_t len) {
  const char* charList = "0123456789ABCDEF";
  if (len == 0)return "";

  string res(len * 3, 0);

  for (size_t i = 0; i < len; i++) {
    res[i * 3] = charList[bytes[i] >> 4];
    res[i * 3 + 1] = charList[bytes[i] & 0x0f];
    res[i * 3 + 2] = ' ';
  }
  res[len * 3 - 1] = 0;
  return res;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << ("Usage: " + string(argv[0]) + " input_file\n\n");
    cout << "用于修正 NDK24+ 编译的 aarch64 ELF align字段\n";
    cout << "源于 https://github.com/Lzhiyong/termux-ndk/blob/master/patches/align_fix.py\n\n";
    cout << "由 JARK006 转写为 C++\n\n";
    system("pause");
    return -1;
  }

  auto fp = fopen(argv[1], "r+b");
  if (!fp) {
    cout << "File open fail!!!\n";
    return -1;
  }

  char elfMagic[] = { 0x7f, 'E', 'L', 'F', 0 };
  char elfHeader[16] = { 0 };
  fread(elfHeader, 1, 16, fp);

  if (strncmp(elfHeader, elfMagic, 4) || elfHeader[4] != 2) {
    fclose(fp);
    cout << "Only support 64bit ELF file!!!\n";
    cout << "See More in: https://github.com/Lzhiyong/termux-ndk/blob/master/patches/align_fix.py\n\n";
    return -1;
  }

  // winX86_64 ARM64(aarch64) 均属于 小端 Little-endian
  union _union
  {
    uint64_t u64;
    uint32_t u32[2];
    uint16_t u16[4];
    uint8_t u8[8];
  }tmp;

  fseek(fp, 32, SEEK_SET);
  fread(&tmp, 1, 8, fp);
  auto offset = tmp.u64;

  fseek(fp, 54, SEEK_SET);
  fread(&tmp, 1, 8, fp);
  auto phsize = tmp.u16[0];
  auto phnum = tmp.u16[1];

  bool isFix = false;
  for (size_t i = 0; i < phnum; i++) {
    fseek(fp, offset + i * phsize, SEEK_SET);
    fread(&tmp, 1, 8, fp);
    auto t = tmp.u32[0];

    if (t == 7) {
      fseek(fp, 48 - 8, SEEK_CUR);
      fread(&tmp, 1, 8, fp);
      auto align = tmp.u64;

      if (align < 64) {
          //cout << ("Found TLS segment with align = " + to_string(align)) << endl;
          //cout << ("TLS segment is underaligned, patching align to 64") << endl;
        cout << ("patching align[" + to_string(align) + "] to [64]");
        fseek(fp, -8, SEEK_CUR);
        align = 64;
        fwrite(&align, 1, 8, fp);
        isFix = true;
      }
    }
  }
  fclose(fp);
  if (!isFix) cout << "Patch nothing. Attention!!!  Attention!!!  Attention!!!  \n";
  return 0;
}