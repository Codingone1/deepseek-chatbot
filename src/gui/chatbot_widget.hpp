#ifndef CHATBOT_WIDGET_HPP
#define CHATBOT_WIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <memory>
#include "../api_client.hpp"

class ChatbotWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChatbotWidget(QWidget *parent = nullptr);
    ~ChatbotWidget() = default;

private slots:
    void onSendButtonClicked();
    void onInputReturn();
    void onClearButtonClicked();

private:
    void setupUI();
    void addMessage(const QString &sender, const QString &message);
    void displaySystemMessage(const QString &message);

    // UI 组件
    QTextEdit *messageDisplay;      // 消息显示区域
    QLineEdit *userInput;            // 用户输入框
    QPushButton *sendButton;         // 发送按钮
    QPushButton *clearButton;        // 清空按钮
    
    // 布局
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *inputLayout;
    
    // API 客户端
    std::unique_ptr<APIClient> apiClient;
};

#endif // CHATBOT_WIDGET_HPP
