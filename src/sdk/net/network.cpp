#include <sys/socket.h>
#include <arpa/inet.h>
#include "src/sdk/MiHoYoSDK.h"

bool MiHoYoSDK::NetSyncLock = false;
int MiHoYoSDK::NetClient = -1;
MiHoYoSDK::RSACrypto *MiHoYoSDK::NetRSA = nullptr;

//发送并接收数据
MiHoYoSDK::Bytes MiHoYoSDK::SendMsg(const Bytes &sendMsg)
{
    //防止死锁
    for (uint i = 0; i < 20; i++)
    {
        if (i == 19)
            RT("SM Error 0x01") && CCC("NetSyncLock Error!");
        if (NetSyncLock)
            usleep(500000u); //0.5s
        else
            break;
    }
    NetSyncLock = true;

    //构建发送的数据长度
    char len_buff[6] = "";
    uint msg_len = sendMsg.length();
    snprintf(len_buff, 6, GET_SAFE_CHAR(StaticData::STR_lenForm), msg_len);
    Bytes send_msg(len_buff, 5);
    send_msg.append(sendMsg);

    //发送
    if (send(NetClient, send_msg.c_str(), send_msg.length(), 0) <= 0)
        RT("SM Error 0x02-" + ToString(errno)) && CCC("send Errno: " + ToString(errno));

    Bytes read_data;
    int rec_len = 0;
    int data_len = 0;
    char *read_buff = new char[4096];
    do
    {
        if ((rec_len = recv(NetClient, read_buff, 4096, 0)) <= 0)
        {
            if (rec_len < 0)
                RT("SM Error 0x03-" + ToString(errno)) &&
                    CCC("recv Errno: " + ToString(errno));

            RT("SM Error 0x04") && CCC("Read Null Data!");
        }

        if (data_len == 0)
        {
            data_len = std::stoi(std::string(read_buff, 5));
            if (data_len <= 0)
                RT("SM Error 0x05") && CCC("data_len Error");
            read_data.append(Bytes(read_buff + 5, rec_len - 5));
        }
        else
            read_data.append(read_buff, rec_len);
    } while (read_data.length() < data_len);

    delete[] read_buff;
    NetSyncLock = false;
    return read_data;
}

//双向验证的发送接收数据
MiHoYoSDK::Bytes MiHoYoSDK::SendMsgEX(const Bytes &sendMsg)
{
    Bytes symbol(GET_SAFE_DATA(StaticData::STR_symbol));

    Bytes send_cipher_data = NetRSA->publicEncrypt(sendMsg); //加密数据
    Bytes send_sign = NetRSA->privateSign(send_cipher_data); //签名
    send_cipher_data.append(symbol);
    send_cipher_data.append(send_sign);
    Bytes send_base_data = NetRSA->publicEncrypt(send_cipher_data); //整体加密
    Bytes send_aes_data = AESEncode(
        send_base_data, GET_SAFE_DATA(StaticData::ServerAESKey)); //AES保护

    //发送数据
    Bytes read_msg = SendMsg(send_aes_data);
    Bytes read_aes_data = AESDecode(
        read_msg, GET_SAFE_DATA(StaticData::ClientAESKey));       //AES解包
    Bytes read_base_data = NetRSA->privateDecrypt(read_aes_data); //整体解密

    //分割
    int index = read_base_data.find(symbol);
    if (index < 0)
        RT("EX Error 0x01") && CCC("Symbol Not Find!");

    //提取数据
    Bytes read_cipher_data = Bytes(read_base_data.c_str(), index);
    Bytes read_sign = Bytes(read_base_data.c_str() + index + symbol.length(),
                            read_base_data.length() - symbol.length() - read_cipher_data.length());

    //验证数据
    if (NetRSA->publicVerify(read_cipher_data, read_sign))
        RT("EX Error 0x02") && CCC("RSA Verify Error!");

    Bytes data = NetRSA->privateDecrypt(read_cipher_data); //解密数据
    return data;
}

//JSON格式收发数据
MiHoYoSDK::Bytes MiHoYoSDK::SendJSON(const char *route, const Json::Value &sendData)
{
    using namespace StaticData;
    Json::Value send_root, read_root;

    //构建JSON
    send_root[GET_SAFE_DATA(STR_date)] = NowTime();
    send_root[GET_SAFE_DATA(STR_route)] = route;
    send_root[GET_SAFE_DATA(STR_data)] = JsonWriter.write(sendData);

    //发送 & 读取
    Bytes json = JsonWriter.write(send_root);
    Bytes read_data = SendMsgEX(json);

    //解析JSON
    if (!JsonReader.parse(read_data.c_str(), read_root))
        RT("SJ Error 0x01") && CCC("Json Parse Error!");
    if (!read_root.isMember(GET_SAFE_DATA(STR_status)) ||
        !read_root.isMember(GET_SAFE_DATA(STR_data)) ||
        !read_root.isMember(GET_SAFE_DATA(STR_error)))
        RT("SJ Error 0x02") && CCC("Json Key Error!");

    //读取值
    int status = read_root[GET_SAFE_DATA(STR_status)].asInt();
    std::string error = read_root[GET_SAFE_DATA(STR_error)].asString();
    std::string Data = JsonWriter.write(read_root[GET_SAFE_DATA(STR_data)]);

    // RT("status:#" + std::to_string(status) + "#");
    // RT("error:#" + error + "#");
    // RT("Data:#" + Data + "#");

    if (!error.empty() || status != 200)
        RT(ToString(status) + ": " + error) && CCC("Server Error!");

    return Data;
}

//连接服务器
void MiHoYoSDK::LinkServer(InitCallBack callBack)
{
    NetRSA = new RSACrypto(GET_SAFE_DATA(StaticData::ServerPublicKey),
                           GET_SAFE_DATA(StaticData::ClientPrivateKey));

    SafeChars ip(GET_SAFE_CORT(StaticData::ServerIP));
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7557);                        //端口
    server_addr.sin_addr.s_addr = inet_addr(ip.get().c_str()); //远程服务器IP
#ifdef LocalHost
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.2"); //本地调试IP
#endif

    if ((NetClient = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        RT("LS Error 0x01") && CCC("Socket Create Error!");

    //链接套接字
    if (connect(NetClient, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        RT("LS Error 0x02") && CCC("Socket Connect Error!");

    static struct timeval timeout = {15, 0};
    if (setsockopt(NetClient, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) != 0)
        RT("LS Error 0x03-" + ToString(errno)) && CCC("Setsockopt Error!");
    if (setsockopt(NetClient, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) != 0)
        RT("LS Error 0x04-" + ToString(errno)) && CCC("Setsockopt Error!");

    Json::Value root;
    root[GET_SAFE_DATA(StaticData::STR_version)] = GET_SAFE_DATA(StaticData::BUILD_VERSION);
    root[GET_SAFE_DATA(StaticData::STR_project)] = ProjectID;
    root[GET_SAFE_DATA(StaticData::STR_channel)] = ChannelID;
    root[GET_SAFE_DATA(StaticData::STR_uuid)] = GetUUID().get();
    root[GET_SAFE_DATA(StaticData::STR_uif)] = FileRead(GET_SAFE_DATA(StaticData::PATH_uif));

    if (callBack(SendJSON(GET_SAFE_CHAR(StaticData::STR_login), root)))
        RT("LS Error 0x05") && CCC("CallBark Error!");
}
