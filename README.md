# DeepSeek Chatbot

一个使用 C++ 和 libcurl 的交互式 AI 聊天机器人，集成免费的 LLM API。现已支持 Qt5 图形化界面！

## 功能特点

- ✅ 基于 C++ 17 开发
- ✅ 使用 libcurl 进行 HTTP 请求
- ✅ JSON 数据处理（nlohmann/json）
- ✅ 支持中英文交互
- ✅ 无需 API 密钥（使用免费 API）
- ✅ **🎨 Qt5 图形化界面**
- ✅ 消息显示区域（带时间戳）
- ✅ 用户输入框
- ✅ 发送按钮
- ✅ 清空对话记录按钮
- ✅ 命令行版本（CLI）

## 系统要求

- C++17 或更高版本
- CMake 3.10 或更高版本
- libcurl
- nlohmann/json
- Qt5（仅用于 GUI 版本）

## 安装依赖

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y \
  build-essential \
  cmake \
  libcurl4-openssl-dev \
  nlohmann-json3-dev \
  qt5-qmake \
  qtbase5-dev
```

### macOS
```bash
brew install cmake curl nlohmann-json qt5
```

### Windows (MSVC)
```bash
# 使用 vcpkg
vcpkg install curl:x64-windows nlohmann-json:x64-windows qt5:x64-windows
```

## 编译和运行

### 方法 1: 使用 CMake（推荐）

**编译两个版本（CLI + GUI）：**
```bash
mkdir build
cd build
cmake ..
make
```

**运行 GUI 版本：**
```bash
./chatbot_gui
```

**运行 CLI 版本：**
```bash
./chatbot_cli
```

### 方法 2: 仅编译 CLI 版本
```bash
g++ -std=c++17 -o chatbot src/chatbot.cpp -lcurl
./chatbot
```

## 使用方法

### GUI 版本

运行 `./chatbot_gui` 后，会打开一个现代化的窗口：

**主要功能：**
- 📝 **消息显示区域** - 显示完整的聊天记录，不同颜色区分用户和机器人消息
- ✍️ **输入框** - 输入你的问题或消息
- 📤 **发送按钮** - 发送消息（也可按 Enter 键）
- 🗑️ **清空按钮** - 清除所有对话记录

**界面特点：**
- 带时间戳的消息显示
- 用户消息（蓝色背景）
- 机器人响应（紫色背景）
- 系统消息（灰色）
- 自动滚动到最新消息

### CLI 版本

```
╔════════════════════════════════════════╗
║    DeepSeek 智能聊天机器人             ║
║   (输入 'exit' 或 'quit' 来退出)      ║
╚═══���════════════════════════════════════╝

你: 你好
机器人: 你好！👋 我是一个 AI 聊天助手。很高兴认识你！有什么我可以帮助你的吗？
```

**命令：**
- 输入任何问题或消息
- 输入 `exit` 或 `quit` 退出程序

## 项目结构

```
deepseek-chatbot/
├── CMakeLists.txt              # CMake 配置文件
├── README.md                   # 项目说明
├── src/
│   ├── chatbot.cpp             # CLI 主程序
│   ├── api_client.hpp          # API 客户端头文件
│   └── gui/
│       ├── main_gui.cpp        # GUI 主程序入口
│       ├── chatbot_widget.hpp  # 聊天窗口部件头文件
│       └── chatbot_widget.cpp  # 聊天窗口部件实现
└── .gitignore                  # Git 忽略配置
```

## 代码示例

### 调用 API
```cpp
APIClient client;
string response = client.chat("你好");
cout << response << endl;
```

### Qt5 GUI 集成
```cpp
ChatbotWidget chatbot;
chatbot.show();
```

## 故障排除

### 编译错误：找不到 curl.h
```bash
# Ubuntu/Debian
sudo apt-get install libcurl4-openssl-dev

# macOS
brew install curl
```

### 编译错误：找不到 nlohmann/json.hpp
```bash
# Ubuntu/Debian
sudo apt-get install nlohmann-json3-dev

# macOS
brew install nlohmann-json
```

### 编译错误：找不到 Qt5
```bash
# Ubuntu/Debian
sudo apt-get install qt5-qmake qtbase5-dev

# macOS
brew install qt5

# Windows
# 从 https://www.qt.io/download 下载并安装 Qt5
```

### 运行时网络错误
- 检查网络连接
- 确保防火墙允许 HTTPS 连接
- 尝试检查 API 服务是否可用

## API 信息

本程序使用开放的免费 API 服务，无需密钥。支持的 API 包括：
- Ollama（本地部署）
- 其他免费 LLM API

## 扩展功能

你可以轻松扩展此项目：
- ✨ 添加更多 API 支持
- 💾 实现对话历史存储
- 🤖 添加多种 AI 模型支持
- 🎤 集成语音输入/输出
- 🎨 自定义主题和样式
- 📱 添加更多 GUI 功能

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！

---

## 快速开始指南

### 第一次使用？

1. **克隆仓库**
   ```bash
   git clone https://github.com/Codingone1/deepseek-chatbot.git
   cd deepseek-chatbot
   ```

2. **安装依赖**
   - Ubuntu/Debian: 见上文
   - macOS: 见上文
   - Windows: 见上文

3. **编译**
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

4. **运行**
   - GUI: `./chatbot_gui`
   - CLI: `./chatbot_cli`

祝你使用愉快！🎉
