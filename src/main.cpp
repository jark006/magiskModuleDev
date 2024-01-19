#include "utils.h"
#include "prop.h"

int main(int argc, char** argv) {

  // 可执行文件和模块属性文件在同一目录
  Prop moduleProp(parentDir(string(argv[0])) + "/module.prop");

  int lastCapacity = 0;
  int lastMinute = 0;

  while (true) {

    int nowCapacity = readInt("/sys/class/power_supply/battery/capacity");

    if (lastCapacity != nowCapacity) {
      int nowMinute = time(nullptr) / 60;
      int temperature = readInt("/sys/class/power_supply/battery/temp");

      string tips;
      if (lastMinute == 0) { // 初始化
        lastMinute = nowMinute;
        lastCapacity = nowCapacity;
        tips = "初始化 电量: " + to_string(nowCapacity) + "%  电池温度: " + to_string(temperature / 10) + "℃";
      } else {
        auto deltaMinute = nowMinute - lastMinute;
        string timeStr = deltaMinute < 60 ? (to_string(deltaMinute) + "分") : (to_string(deltaMinute / 60) + "时" + to_string(deltaMinute % 60) + "分");
        tips = "电量: " + to_string(lastCapacity) + "%" + (nowCapacity > lastCapacity ? "充到" : "用到") +
          to_string(nowCapacity) + "% 耗时:" + timeStr + "  电池温度:" + to_string(temperature / 10) + "℃";

        lastMinute = nowMinute;
        lastCapacity = nowCapacity;
      }
      moduleProp["description"] = tips; // 更新描述
      moduleProp.save2file();           // 保存到 module.prop
    }

    sleep(60); // 每检查一次就休眠60秒

  }

  return 0;
}
