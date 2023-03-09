$ErrorActionPreference = 'Stop'

function log {
    [CmdletBinding()]
    Param
    (
        [Parameter(Mandatory = $true, Position = 0)]
        [string]$LogMessage
    )
    Write-Output ("[{0}] {1}" -f (Get-Date), $LogMessage)
}

if ( (Test-Path build) -ne "True" ) {
    mkdir build
}

log "Building..."

$id = Get-Content magiskModule/module.prop | Where-Object { $_ -match "id=" }
$id = $id.split('=')[1]


# 下载最新工具链
# https://developer.android.com/ndk/downloads
# https://github.com/android/ndk/wiki

# 将 NDK 与其他构建系统配合使用
# https://developer.android.com/ndk/guides/other_build_systems
# https://android.googlesource.com/platform/ndk/+/master/docs/BuildSystemMaintainers.md
$windowsToolchainsDir = "D:/AndroidSDK/ndk/25.2.9519653/toolchains/llvm/prebuilt/windows-x86_64/bin"
$clang = "${windowsToolchainsDir}/clang++.exe"

# Android 10+ Q+ SDK29+ (如果最低支持SDK是28或以下，则需要进行align_fix)
& $clang --target=aarch64-linux-android29 -std=c++20 -static -s -O2 -Wall -Iinclude src/*.cpp -o build/$id
if ( -not $? ) {
    log "Compile fail"
    exit
}
log "Compile success"

# (如果最低支持SDK是28或以下，则需要进行align_fix)
# $res=./align_fix.exe build/$id
# if ( -not $? ) {
#     log "align_fix失败"
#     exit
# }
# log $res
# log "align_fix完成"

log "Compile output: build/$id"
