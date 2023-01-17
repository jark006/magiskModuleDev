$BOOTMODE || abort "
!!! ONLY be installed on Magisk or KernelSU. 
!!! 仅支持在 Magisk 或 KernelSU 下安装。"

[ $ARCH == "arm64" ] || abort "
!!! ONLY support ARM64
!!! 仅支持 ARM64"

module_id="$(grep_prop id $MODPATH/module.prop)"
module_name="$(grep_prop name $MODPATH/module.prop)"
module_version="$(grep_prop version $MODPATH/module.prop)"

chmod a+x $MODPATH/$module_id
chmod a+x $MODPATH/service.sh

echo "- 安装 $module_name $module_version 完毕, 重启生效"