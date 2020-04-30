#pragma once
#include "src/sdk/Bytes.hpp"

typedef bool (*InitCallBack)(const MiHoYoSDK::Bytes &src);

//SDK
namespace MiHoYoSDK
{

    //Net同步锁
    extern bool NetSyncLock;
    //客户端套接字文件描述符
    extern int NetClient;
    //全局NetRSA对象
    extern RSACrypto *NetRSA;

    // 发送并接收数据
    Bytes SendMsg(const Bytes &sendMsg);
    // 双向验证的发送接收数据
    Bytes SendMsgEX(const Bytes &sendMsg);
    // JSON格式收发数据
    Bytes SendJSON(const char *route, const Json::Value &sendData);

    // 连接服务器
    void LinkServer(InitCallBack callBack);

} // namespace MiHoYoSDK
