# C/C++开发Magisk模块工程

### 这是一个简易的电池电量日志模块，记录电量变化，温度等等

![](preview.png)

## 上手步骤(适合Windows下开发):

1. 下载 [vscode](https://code.visualstudio.com/) 或者使用其他你熟悉的编辑器或IDE，打开本文件夹。

1. 如果你已安装`AndroidStudio`，其SDK目录下一般含有NDK工具链，否则需要下载最新 [NDK工具链](https://developer.android.com/ndk/downloads) 并解压， 并在 `autoBuild.ps1` 中设置好路径 `$windowsToolchainsDir`。

1. 执行 `autoBuild.ps1` 即可一键编译并自动打包zip, 可以直接到Magisk刷入。

1. 开始编辑c++代码和module.prop, 开发你的模块吧~ 

- 编辑完代码，记得先 `ctrl + s` 保存，再开始编译

![](readme.png)
