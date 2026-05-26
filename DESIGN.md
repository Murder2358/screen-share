# 屏幕采集模块技术设计文档

## 模块定位

本模块（`ScreenCapturer`）是整个屏幕共享系统的**数据源头**，负责周期性截取本机屏幕画面，并以 `QImage` 形式通过 Qt 信号发射给发送模块。

```
[屏幕画面]
    ↓
ScreenCapturer（本模块）
    ↓  emit frameCaptured(QImage)
Sender（网络发送，队友负责）
    ↓  TCP/UDP 传输
Receiver（接收端，队友负责）
    ↓
[显示画面]
```

---

## 接口约定

| 项目 | 方案 | 说明 |
|------|------|------|
| 输出信号 | `frameCaptured(const QImage&)` | 每帧截图完成后 emit |
| 图像格式 | `QImage::Format_RGB32` | 兼容性好，便于转换 |
| 帧率 | 30 fps | QTimer 间隔 33 ms |
| 输出分辨率 | 缩放到 1280×720 | 减少网络压力 |
| 压缩 | JPEG quality=60 | 由 Sender 负责，本模块只输出原始 QImage |

---

## 采集方案路线

### 第一期（当前实现）：QScreen::grabWindow()
- **优点**：纯 Qt，无额外依赖，跨平台
- **缺点**：无法截取受 DRM 保护的视频/游戏内容，帧率上限约 30fps

### 第二期（性能优化）：DXGI Desktop Duplication API（Windows）
- **优点**：GPU 直接输出，能截到视频/游戏内容，可达 60fps
- **切换方式**：只需替换 `captureFrame()` 内部实现，对外信号接口不变

---

## 与队友的集成说明

Sender 队友只需一行连接：
```cpp
connect(capturer, &ScreenCapturer::frameCaptured, sender, &Sender::onFrameReady);
```

在 `Sender::onFrameReady` 中将 QImage 压缩为 JPEG bytes 后发送：
```cpp
QByteArray bytes;
QBuffer buf(&bytes);
buf.open(QIODevice::WriteOnly);
frame.save(&buf, "JPEG", 60);
// 然后通过 socket 发送 bytes
```
