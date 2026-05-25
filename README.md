# 局域网屏幕共享软件

基于 **C++ / Qt 6.5 / libwebrtc** 实现的局域网屏幕共享工具，支持 Windows 和 macOS。

---

## 分工与进度

| 模块 | 平台 | 负责人 | 分支 | 职责 |
|------|------|--------|------|------|
| 屏幕共享模块 | Windows | 蒋宗原 | `jzy` | 窗口枚举与显示 |
| 屏幕共享模块 | Windows | 韦燕丹 | `wyd` | 屏幕采集 |
| 屏幕共享模块 | macOS | 俞哲钊 | `yzz` | 窗口枚举与显示 |
| 屏幕共享模块 | macOS | 邢雨茁 | `xyz` | 屏幕采集 |
| 客户端业务架构 | macOS | 黄俊杰 | `hjj` | 客户端主体框架 |
| 客户端业务架构 | Windows | 赵芃年 | `zpn` | 客户端主体框架 |

---

## Milestone

### Week 1
- 开发环境搭建（Qt 6.5 + libwebrtc 预编译包）
- 实现窗口或屏幕枚举（能列出当前系统所有窗口/屏幕）
- 在自己的分支上完成初步开发

### Week 2
- 实现屏幕或窗口的实际采集（抓到画面内容）
- 与客户端同学进行联调
- 完成功能验收

---

## 开发环境搭建

### 1. 安装 Qt 6.5 LTS
前往 [Qt 官网](https://www.qt.io/download) 下载安装包。
- Windows：选择 **MSVC 2022** 编译器
- macOS：选择 **Clang** 编译器

### 2. 获取 libwebrtc 预编译包

> ⚠️ 不要自行编译源码（需 30GB 磁盘 + 数小时），直接使用预编译包

前往 [libwebrtc-bin Releases](https://github.com/crow-misia/libwebrtc-bin/releases) 下载对应平台：
- Windows：`libwebrtc-win-x64.zip`
- macOS Apple Silicon：`libwebrtc-mac-arm64.zip`
- macOS Intel：`libwebrtc-mac-x64.zip`

解压到项目根目录 `third_party/libwebrtc/` 下。

### 3. 编译项目
```bash
cmake -B build -DCMAKE_PREFIX_PATH=/path/to/Qt/6.5.0
cmake --build build
```

---

## Git 工作流

```bash
# 1. 克隆仓库
git clone https://github.com/xueying24100-source/screen-share.git

# 2. 切换到自己的分支（换成自己的分支名）
git checkout jzy

# 3. 开发完成后提交
git add .
git commit -m "feat: 实现屏幕枚举"
git push origin jzy
```

> 每人只在自己的分支开发，不要直接提交到 `main`。

---

## 注意事项

- **macOS 屏幕权限**：首次运行需在「系统设置 → 隐私与安全性 → 屏幕录制」中手动授权，否则采集到黑屏
- **Windows/macOS 像素格式不同**：Windows 截图为 BGRA，macOS 为 ARGB，使用 libyuv 转换时注意区分
- **遇到问题**：卡超过 1 小时立刻发群里，不要一个人闷头卡着

---

## 参考资料

- [libwebrtc-bin 预编译包](https://github.com/crow-misia/libwebrtc-bin)
- [Qt 6.5 文档](https://doc.qt.io/qt-6/)
- [WebRTC DesktopCapturer](https://chromium.googlesource.com/external/webrtc/+/refs/heads/master/modules/desktop_capture/)
