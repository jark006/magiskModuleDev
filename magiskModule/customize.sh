$BOOTMODE || abort "
!!! ONLY be installed on Magisk or KernelSU. 
!!! 仅支持在 Magisk 或 KernelSU 下安装。"

[ $ARCH == "arm64" ] || abort "
!!! ONLY support ARM64
!!! 仅支持 ARM64"

chmod a+x $MODPATH/batteryMonitor
chmod a+x $MODPATH/service.sh

module_version="$(grep_prop version $MODPATH/module.prop)"
echo "- 安装 $module_version 完毕, 重启生效"
