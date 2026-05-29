# DeepSeek Chatbot

一个使用 C++ 和 libcurl 的交互式 AI 聊天机器人，集成免费的 LLM API。

## 功能特点

- ✅ 基于 C++ 17 开发
- ✅ 使用 libcurl 进行 HTTP 请求
- ✅ JSON 数据处理（nlohmann/json）
- ✅ 支持中英文交互
- ✅ 无需 API 密钥（使用免费 API）
- ✅ 友好的命令行界面

## 系统要求

- C++17 或更高版本
- CMake 3.10 或更高版本
- libcurl
- nlohmann/json

## 安装依赖

### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install -y \
  build-essential \
  cmake \
  libcurl4-openssl-dev \
  nlohmann-json3-dev
```

### macOS
```bash
brew install cmake curl nlohmann-json
```

### Windows (MSVC)
```bash
# 使用 vcpkg
vcpkg install curl:x64-windows nlohmann-json:x64-windows
```

## 编译和运行

### 方法 1: 使用 CMake（推荐）
```bash
mkdir build
cd build
cmake ..
make
./chatbot
```

### 方法 2: 直接编译（需要手动设置路径）
```bash
g++ -std=c++17 -o chatbot src/chatbot.cpp -lcurl
./chatbot
```

## 使用方法

运行程序后，按照提示输入你的问题：

```
╔════════════════════════════════════════╗
║    DeepSeek 智能聊天机器人             ║
║   (输入 'exit' 或 'quit' 来退出)      ║
╚════════════════════════════════════════╝

你: 你好
AI: 你好！我是一个 AI 助手。很高兴认识你！有什么我可以帮助你的吗？
```

### 命令
- 输入任何问题或消息
- 输入 `exit` 或 `quit` 退出程序

## 项目结构

```
deepseek-chatbot/
├── CMakeLists.txt          # CMake 配置文件
├── README.md               # 项目说明
├── src/
│   ├── chatbot.cpp         # 主程序
│   └── api_client.hpp      # API 客户端头文件
└── .gitignore              # Git 忽略配置
```

## 代码示例

### 调用 API
```cpp
APIClient client;
string response = client.chat("你好");
cout << response << endl;
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
- 添加更多 API 支持
- 实现对话历史存储
- 添加多种 AI 模型支持
- 集成语音输入/输出

## 许可证

MIT License

## 贡献

欢迎提交 Issue 和 Pull Request！
