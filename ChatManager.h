#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include<QMutex>
#include<vector>
#include "ChatRoom.h"
using namespace std;

class ChatManager
{
public:
    static ChatManager* getInstance();
    void insertChat(const ChatRoom& chr);
    void eraseChat(const QString& name);
    vector<ChatRoom> getAllChat()const;
private:
    static ChatManager* instance;
    ChatManager();
    vector<ChatRoom> chatrooms;
    static QMutex mutex;
};
#endif // CHATMANAGER_H
