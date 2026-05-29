#include <QApplication>
#include "chatbot_widget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // 设置应用程序样式
    app.setStyle("Fusion");
    
    // 创建聊天窗口
    ChatbotWidget chatbotWindow;
    chatbotWindow.show();
    
    return app.exec();
}
