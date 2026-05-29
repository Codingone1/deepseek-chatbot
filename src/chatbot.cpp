#include <iostream>
#include <string>
#include <algorithm>
#include "api_client.hpp"

using namespace std;

int main() {
    // 显示欢迎信息
    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗" << endl;
    cout << "║                                                ║" << endl;
    cout << "║       欢迎使用 DeepSeek 智能聊天机器人         ║" << endl;
    cout << "║                                                ║" << endl;
    cout << "║            💬 AI 助手 v1.0                      ║" << endl;
    cout << "║                                                ║" << endl;
    cout << "║   输入你的问题或消息（输入 exit 或 quit 退出） ║" << endl;
    cout << "║   输入 'help' 查看帮助信息                     ║" << endl;
    cout << "║                                                ║" << endl;
    cout << "╚════════════════════════════════════════════════╝" << endl;
    cout << endl;

    // 创建 API 客户端
    APIClient chatbot;
    
    string user_input;
    int message_count = 0;
    
    while (true) {
        cout << "你: ";
        
        // 获取用户输入
        getline(cin, user_input);
        
        // 移除首尾空格
        user_input.erase(0, user_input.find_first_not_of(" \t\n\r"));
        user_input.erase(user_input.find_last_not_of(" \t\n\r") + 1);
        
        // 处理退出命令
        string lower_input = user_input;
        transform(lower_input.begin(), lower_input.end(), lower_input.begin(), ::tolower);
        
        if (lower_input == "exit" || lower_input == "quit" || lower_input == "exit()" || lower_input == "quit()") {
            cout << "\n机器人: 再见！感谢使用本程序。祝你有美好的一天！👋\n" << endl;
            break;
        }
        
        // 处理空输入
        if (user_input.empty()) {
            cout << "机器人: 请输入一些内容...\n" << endl;
            continue;
        }
        
        // 显示加载提示
        cout << "\n🤔 正在思考...\n" << endl;
        
        // 调用 API 获取响应
        string response = chatbot.chat(user_input);
        
        // 显示响应
        cout << "机器人: " << response << endl;
        cout << endl;
        
        message_count++;
    }
    
    return 0;
}
