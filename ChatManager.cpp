#include "ChatManager.h"


ChatManager *ChatManager::instance = 0;
QMutex ChatManager::mutex;

ChatManager::ChatManager()
{

}


ChatManager* ChatManager::getInstance()
{
    if(instance == 0){
        mutex.lock();
        if(0 == instance){
            instance = new ChatManager();
        }
        mutex.unlock();
    }
    return instance;
}
void ChatManager::insertChat(const ChatRoom& chatroom)
{
    chatrooms.push_back (chatroom);
}

void ChatManager::eraseChat(const QString& name)
{
    vector<ChatRoom>::iterator it;
    for(it = chatrooms.begin (); it != chatrooms.end (); ++it){
        ChatRoom chat = *it;
        if(chat.getUserName () == name){
            chatrooms.erase (it);
            break;
        }
    }
}


vector<ChatRoom> ChatManager::getAllChat()const
{
    return chatrooms;
}
