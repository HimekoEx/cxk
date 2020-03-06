#include <include/openssl/sha.h>
#include "module.h"

using namespace MiHoYoSDK;
using namespace MiHoYoSDK::StaticData;

ulong Sync::Il2cpp = 0;
int Sync::MTP_Off = 0;
bool Sync::UUID_Lock = true;
std::set<std::string> *Sync::OpenFuncs = nullptr;
std::array<ulong, Sync::ADSS_NUM> Sync::Address;
std::map<ulong, std::map<ulong, ulong>> *Sync::PatchData = nullptr;
std::map<std::string, Sync::MainData> *Sync::Config = nullptr;

//初始化地址
void Sync::InitAddress(ulong il2cpp)
{
    Sync::Il2cpp = il2cpp;
    LOGE("il2cpp >> 0x%lX", il2cpp);

    //0-三星条件选择器 LevelChallengeHelperPlugin$$CreateChallengeById
    //1-可触摸隐私部位 BaseGalTouchSystem$$DoNormalReaction 原函数名 GetReaction
    //2-解锁皮肤 DressInfoManager$$UnlockDress
    //3-皮肤重置 DressInfoManager$$OnGetAvatarDataRsp 原类 DressModule
    ulong tmp[ADSS_NUM] = {0x628EA48, 0x695F768, 0x10AF378, 0x10AF0C0};

    for (int i = 0; i < ADSS_NUM; i++)
        Address[i] = tmp[i] + il2cpp;
}

//同步开启状态
void Sync::SyncJsonConfig()
{
    std::string configStr;
    Json::Reader jsonReader;
    Json::Value root;

    //读取文件
    configStr = ReadFile(GET_SAFE_DATA(jsonPath));

    //解析json
    if (!jsonReader.parse(configStr, root))
        RunTimeLog("SJC Error: 0x00") && CloseChaosCore1("Parse Error") && CloseChaosCore2();

    //销毁map内容
    Config->erase(Config->begin(), Config->end());

    //验证json
    if (!root.isMember(GET_SAFE_DATA(versionStr)) || !root.isMember(GET_SAFE_DATA(dataStr)))
        RunTimeLog("SJC Error: 0x01") && CloseChaosCore1("Key Error") && CloseChaosCore2();

    //发送json版本
    // RunTimeLog(
    SendJSON(GET_SAFE_CHAR(loopSyncStr), root[GET_SAFE_DATA(versionStr)]);
    // );

    //解析具体数据到内存中
    Json::Value dataArray = root[GET_SAFE_DATA(dataStr)];
    for (uint i = 0; i < dataArray.size(); ++i)
    {
        Json::Value dataObject = dataArray[i];
        Json::Value subDataArray = dataObject[GET_SAFE_DATA(subDataStr)];
        MainData mainData; //value
        std::string Title; //key
        std::map<std::string, LineData> subData;

        mainData.State = dataObject[GET_SAFE_DATA(stateStr)].asBool();
        Title = dataObject[GET_SAFE_DATA(titleStr)].asString();

        for (uint j = 0; j < subDataArray.size(); j++)
        {
            Json::Value lineDataObjcet = subDataArray[j];
            LineData lineData;     //value
            std::string LineTitle; //key

            LineTitle = lineDataObjcet[GET_SAFE_DATA(lineTitleStr)].asString();
            lineData.LineType = lineDataObjcet[GET_SAFE_DATA(lineTypeStr)].asInt();

            if (lineData.LineType == 1)
                lineData.LineValue = std::stod(lineDataObjcet[GET_SAFE_DATA(lineValueStr)].asString());
            else if (lineData.LineType == 2)
                lineData.LineState = lineDataObjcet[GET_SAFE_DATA(lineStateStr)].asBool();

            subData.insert(make_pair(LineTitle, lineData));
        }
        mainData.SubData = subData;

        Config->insert(make_pair(Title, mainData));
    }

    // Debug_PrintJsonConfig();
}

//SHA256 验证签名
static bool SHA_Check(const char *data, const uint size, int keys[])
{
    uchar hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    char hex[65] = "";

    MiHoYoSDK::DecryptAscii(keys, 0xCD09);
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, size);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        snprintf(hex + (i * 2), 3, "%02x", hash[i]);
    hex[64] = '\0';

    MiHoYoSDK::DecryptAscii(keys, 0x7798);
    MiHoYoSDK::CheakAscii(keys, hex, 0xF4FC);

    return true;
}

//验证回调函数
static bool VerifyBinRsa(const char *buffer, const uint size)
{
    return SHA_Check(buffer, size, MiHoYoSDK::StaticData::binRsaKey2);
}

// 通过服务器发送的配置进行初始化
void Sync::InitConfig(const MiHoYoSDK::Bytes &config)
{
    Json::Reader reader;
    Json::Value root, data;

    // 解析json
    if (!reader.parse(config.c_str(), root))
        RunTimeLog("RIC Error: 0x00") && CloseChaosCore1("Parse Error") && CloseChaosCore2();

    MTP_Off = root[GET_SAFE_DATA(offStr)].asInt();

    // 构建函数Hook
    {
        std::string Funcs = root[GET_SAFE_DATA(funcsStr)].asString();
        if (!reader.parse(Funcs, data))
            RunTimeLog("RIC Error: 0x01") && CloseChaosCore1("Parse Error") && CloseChaosCore2();

        for (int i = 0; i < data.size(); ++i)
        {
            RunTimeLog(ToString(i) + ": " + data[i].asString());
            OpenFuncs->insert(data[i].asString());
        }
    }

    // 自校验
    {
        std::string package = ReadFileLine(GET_SAFE_DATA(cfgPath));

        std::string chaos_path = package + GET_SAFE_DATA(chaosLibPath);
        std::string cybl_path = package + GET_SAFE_DATA(cyblLibPath);
        std::string apk_path = package + GET_SAFE_DATA(apkPath);

        Bytes chaosMD5 = MD5(ReadFile(chaos_path), true);
        LOGE("chaos md5 : %s", chaosMD5.c_str());
        if (chaosMD5 != root[GET_SAFE_DATA(chaosStr)].asCString())
            CloseChaosCore1("chaos md5 err") && CloseChaosCore2();

        Bytes cyblMD5 = MD5(ReadFile(cybl_path), true);
        LOGE("cybl md5  : %s", cyblMD5.c_str());
        if (cyblMD5 != root[GET_SAFE_DATA(cyblStr)].asCString())
            CloseChaosCore1("cybl md5 err") && CloseChaosCore2();

        Bytes apkMD5 = MD5(ReadFile(apk_path), true);
        LOGE("apk  md5  : %s", apkMD5.c_str());
        if (apkMD5 != root[GET_SAFE_DATA(apkStr)].asCString())
            CloseChaosCore1("apk md5 err") && CloseChaosCore2();

        MiHoYoSDK::UncompressApk(apk_path, GET_SAFE_DATA(binRsaPath), VerifyBinRsa);
    }
}

//手动初始化所有全局变量
void Sync::InitAllVariable()
{
    if (OpenFuncs == nullptr)
        OpenFuncs = new std::set<std::string>;

    if (PatchData == nullptr)
        PatchData = new std::map<ulong, std::map<ulong, ulong>>;

    if (Config == nullptr)
        Config = new std::map<std::string, MainData>;
}
