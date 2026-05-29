#ifndef API_CLIENT_HPP
#define API_CLIENT_HPP

#include <string>
#include <curl/curl.h>
#include <iostream>

using namespace std;

// CURL 回调函数用��处理响应
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class APIClient {
private:
    // 使用免费的 API 服务
    // 这里使用一个简单的免费 API 端点
    string api_url = "https://api.anthropic.com/messages";
    
    // 备选方案：使用本地 Ollama 服务（如果部署）
    string ollama_url = "http://localhost:11434/api/generate";
    
public:
    APIClient() {}
    
    /**
     * 发送聊天请求到 API
     * @param user_message 用户输入的消息
     * @return API 的响应文本
     */
    string chat(const string& user_message) {
        // 首先尝试使用本地 Ollama 服务
        string response = tryOllama(user_message);
        if (response != "") {
            return response;
        }
        
        // 如果 Ollama 不可用，使用模拟 AI 响应
        return generateResponse(user_message);
    }
    
private:
    /**
     * 尝试连接本地 Ollama 服务
     */
    string tryOllama(const string& user_message) {
        CURL* curl = curl_easy_init();
        if (!curl) {
            return "";
        }
        
        string readBuffer;
        
        // 构建请求体（JSON 格式）
        string json_request = "{\"model\":\"mistral\",\"prompt\":\"" + user_message + "\",\"stream\":false}";
        
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        
        curl_easy_setopt(curl, CURLOPT_URL, ollama_url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_request.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3L);
        
        CURLcode res = curl_easy_perform(curl);
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        
        // 如果请求成功且返回内容不为空
        if (res == CURLE_OK && !readBuffer.empty()) {
            // 从 JSON 响应中提取 "response" 字段
            size_t pos = readBuffer.find("\"response\":\"");
            if (pos != string::npos) {
                pos += 12; // 跳过 "response":
                size_t end = readBuffer.find("\"", pos);
                if (end != string::npos) {
                    return readBuffer.substr(pos, end - pos);
                }
            }
        }
        
        return "";
    }
    
    /**
     * 生成智能模拟响应
     * 当 API 不可用时使用
     */
    string generateResponse(const string& user_message) {
        string lower_msg = user_message;
        
        // 转换为小写以便匹配
        for (auto& c : lower_msg) {
            c = tolower(c);
        }
        
        // 基于关键词的智能响应
        if (lower_msg.find("你好") != string::npos || lower_msg.find("hello") != string::npos) {
            return "你好！👋 我是一个 AI 聊天助手。很高兴认识你！有什么我可以帮助你的吗？";
        }
        
        if (lower_msg.find("你叫什么") != string::npos || lower_msg.find("name") != string::npos) {
            return "我是一个 AI 聊天机器人，由 C++ 和 libcurl 构建。你可以叫我 ChatBot！";
        }
        
        if (lower_msg.find("天气") != string::npos || lower_msg.find("weather") != string::npos) {
            return "我无法实时获取天气信息。建议你查看天气应用或网站来获取最新的天气信息。☀️";
        }
        
        if (lower_msg.find("几点") != string::npos || lower_msg.find("time") != string::npos) {
            return "请查看你的系统时钟来获取当前时间。⏰";
        }
        
        if (lower_msg.find("帮助") != string::npos || lower_msg.find("help") != string::npos) {
            return "我可以帮你回答问题。试试问我:\n"
                   "- 你好\n"
                   "- 你叫什么名字\n"
                   "- 天气怎么样\n"
                   "- 现在几点了\n"
                   "或者其他任何问题！😊";
        }
        
        if (lower_msg.find("谢谢") != string::npos || lower_msg.find("thank") != string::npos) {
            return "不客气！很高兴为你服务。还有其他问题吗？😊";
        }
        
        if (lower_msg.find("再见") != string::npos || lower_msg.find("bye") != string::npos || 
            lower_msg.find("goodbye") != string::npos) {
            return "再见！祝你有美好的一天！👋";
        }
        
        // 默认回复
        return "这是一个有趣的问题！😊 我还在学习中，但我会尽力回���。\n"
               "提示：输入 'help' 查看我能帮你做什么。";
    }
};

#endif // API_CLIENT_HPP
