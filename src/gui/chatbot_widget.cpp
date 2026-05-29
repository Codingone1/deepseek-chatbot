#include "chatbot_widget.hpp"
#include <QApplication>
#include <QDateTime>
#include <QDebug>

ChatbotWidget::ChatbotWidget(QWidget *parent)
    : QWidget(parent), apiClient(std::make_unique<APIClient>()) {
    setupUI();
    
    // 连接信号和槽
    connect(sendButton, &QPushButton::clicked, this, &ChatbotWidget::onSendButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &ChatbotWidget::onClearButtonClicked);
    connect(userInput, &QLineEdit::returnPressed, this, &ChatbotWidget::onInputReturn);
    
    // 设置焦点到输入框
    userInput->setFocus();
    
    // 显示欢迎消息
    displaySystemMessage("欢迎使用 DeepSeek AI 聊天机器人！👋");
    displaySystemMessage("请在下面的输入框中输入你的问题...");
}

void ChatbotWidget::setupUI() {
    setWindowTitle("DeepSeek AI Chatbot");
    setGeometry(100, 100, 800, 600);
    
    // 创建主布局
    mainLayout = new QVBoxLayout(this);
    
    // 创建消息显示区域
    messageDisplay = new QTextEdit();
    messageDisplay->setReadOnly(true);
    messageDisplay->setStyleSheet(
        "QTextEdit {"
        "    background-color: #f5f5f5;"
        "    border: 1px solid #ddd;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    font-size: 11pt;"
        "}"
    );
    
    // 创建输入框
    userInput = new QLineEdit();
    userInput->setPlaceholderText("输入你的问题或消息...");
    userInput->setStyleSheet(
        "QLineEdit {"
        "    border: 1px solid #ddd;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "    font-size: 11pt;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
    );
    
    // 创建按钮
    sendButton = new QPushButton("发送");
    sendButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 20px;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40;"
        "}"
    );
    sendButton->setMinimumWidth(100);
    
    clearButton = new QPushButton("清空");
    clearButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #f44336;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 8px 20px;"
        "    font-size: 11pt;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #da190b;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #ba0000;"
        "}"
    );
    clearButton->setMinimumWidth(100);
    
    // 创建输入区域布局
    inputLayout = new QHBoxLayout();
    inputLayout->addWidget(userInput);
    inputLayout->addWidget(sendButton);
    inputLayout->addWidget(clearButton);
    
    // 添加到主布局
    mainLayout->addWidget(messageDisplay, 1);  // 消息区域占据大部分空间
    mainLayout->addLayout(inputLayout);
    
    setLayout(mainLayout);
}

void ChatbotWidget::onSendButtonClicked() {
    QString userMessage = userInput->text().trimmed();
    
    if (userMessage.isEmpty()) {
        displaySystemMessage("⚠️ 请输入一些内容！");
        return;
    }
    
    // 显示用户消息
    addMessage("你", userMessage);
    
    // 清空输入框
    userInput->clear();
    
    // 显示思考状态
    displaySystemMessage("🤔 正在思考...");
    
    // 调用 API 获取响应
    std::string response = apiClient->chat(userMessage.toStdString());
    
    // 移除"思考"消息
    QString html = messageDisplay->toHtml();
    html.remove(html.lastIndexOf("🤔 正在思考...") - 100, 200);  // 移除最后的思考消息
    messageDisplay->setHtml(html);
    
    // 显示 AI 响应
    addMessage("机器人", QString::fromStdString(response));
    
    // 设置焦点回到输入框
    userInput->setFocus();
}

void ChatbotWidget::onInputReturn() {
    onSendButtonClicked();
}

void ChatbotWidget::onClearButtonClicked() {
    messageDisplay->clear();
    userInput->clear();
    displaySystemMessage("对话记录已清空 🗑️");
    displaySystemMessage("欢迎继续与我聊天！");
    userInput->setFocus();
}

void ChatbotWidget::addMessage(const QString &sender, const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    
    QString htmlMessage;
    if (sender == "你") {
        htmlMessage = QString(
            "<div style='margin: 10px 0;'>"
            "<span style='color: #0066cc; font-weight: bold;'>%1 [%2]</span><br/>"
            "<div style='background-color: #e3f2fd; padding: 10px; border-radius: 5px; margin-top: 5px;'>"
            "%3"
            "</div>"
            "</div>"
        ).arg(sender, timestamp, message);
    } else {
        htmlMessage = QString(
            "<div style='margin: 10px 0;'>"
            "<span style='color: #d32f2f; font-weight: bold;'>%1 [%2]</span><br/>"
            "<div style='background-color: #f3e5f5; padding: 10px; border-radius: 5px; margin-top: 5px;'>"
            "%3"
            "</div>"
            "</div>"
        ).arg(sender, timestamp, message);
    }
    
    messageDisplay->insertHtml(htmlMessage);
    
    // 滚动到底部
    QTextCursor cursor = messageDisplay->textCursor();
    cursor.movePosition(QTextCursor::End);
    messageDisplay->setTextCursor(cursor);
}

void ChatbotWidget::displaySystemMessage(const QString &message) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    
    QString htmlMessage = QString(
        "<div style='margin: 10px 0; text-align: center;'>"
        "<span style='color: #999999; font-size: 10pt;'>[%1] %2</span>"
        "</div>"
    ).arg(timestamp, message);
    
    messageDisplay->insertHtml(htmlMessage);
    
    // 滚动到底部
    QTextCursor cursor = messageDisplay->textCursor();
    cursor.movePosition(QTextCursor::End);
    messageDisplay->setTextCursor(cursor);
}
