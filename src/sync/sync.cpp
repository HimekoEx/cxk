#include <include/openssl/sha.h>
#include "src/verify/verify.h"
#include "sync.h"

using namespace MiHoYoSDK;
using namespace MiHoYoSDK::StaticData;

ulong Sync::Il2cpp = 0;
int Sync::Off_MTP = 0;
std::set<std::string> *Sync::OpenFunc = nullptr;
std::array<ulong, Sync::ADSS_NUM> Sync::Address;
std::map<ulong, std::map<ulong, ulong>> *Sync::PatchData = nullptr;
std::map<std::string, Sync::MainData> *Sync::Config = nullptr;

//手动初始化所有全局变量
void Sync::InitAllVariable()
{
    srand((uint)time(nullptr));
    if (OpenFunc == nullptr)
        OpenFunc = new std::set<std::string>;

    if (PatchData == nullptr)
        PatchData = new std::map<ulong, std::map<ulong, ulong>>;

    if (Config == nullptr)
        Config = new std::map<std::string, MainData>;
}

//初始化地址
void Sync::InitAddress(ulong il2cpp)
{
    Sync::Il2cpp = il2cpp;
    LOGE("il2cpp >>> 0x%lX <<<", il2cpp);

    //0-三星条件选择器 LevelChallengeHelperPlugin$$CreateChallengeById
    //1-可触摸隐私部位 BaseGalTouchSystem$$DoNormalReaction 原函数名 GetReaction
    //2-解锁皮肤 DressModule$$UnlockDress 原类DressInfoManager public void \w{11}\(int \w{11}\);
    //3-皮肤重置 DressModule$$OnGetAvatarDataRsp    private bool \w{11}\(GetAvatarDataRsp \w{11}\);
    ulong tmp[ADSS_NUM] = {0x2001834, 0x38BB17C, 0x2D3AE74, 0x2D3AB30};

    for (int i = 0; i < ADSS_NUM; i++)
        Address[i] = tmp[i] + il2cpp;

    SyncJsonConfig();
}

//同步开启状态
void Sync::SyncJsonConfig()
{
    std::string configStr;
    Json::Reader jsonReader;
    Json::Value configRoot, sendRoot, readRoot;

    //读取文件
    configStr = FileRead(GET_SAFE_DATA(PATH_Main) + IDToProject(ProjectID).get() + ".json");

    //解析json
    if (!jsonReader.parse(configStr, configRoot))
        RT("SC Error: 0x01") && CCC("Parse Error");

    //验证json
    if (!configRoot.isMember(GET_SAFE_DATA(STR_version)) || !configRoot.isMember(GET_SAFE_DATA(STR_data)))
        RT("SC Error: 0x02") && CCC("Key Error");

    //发送数据
    // sendRoot[GET_SAFE_DATA(STR_version)] = configRoot[GET_SAFE_DATA(STR_version)];
    // int tmp = (100 + rand()) % 100;
    // if (tmp > 95)//%95
    // {
    //     Verify::VerifyVFC();
    //     sendRoot["chaos"] = Verify::GetChaosMD5().get();
    //     sendRoot["cybl"] = Verify::GetCyBLMD5().get();
    //     sendRoot["apk"] = Verify::GetAPKMD5().get();
    //     Verify::LocalVFC++;
    // }
    // Bytes raw = SendJSON(GET_SAFE_CHAR(STR_loopSync), sendRoot);
    // if (tmp > 95)
    //     Verify::VerifyFileByJson(raw);
    // if (!jsonReader.parse(raw.get(), readRoot))
    //     RT("SC Error: 0x03") && CCC("Parse Error");
    // Verify::RemoteVFC = readRoot["vfc"].asUInt();

    //销毁map内容
    Config->erase(Config->begin(), Config->end());

    //解析具体数据到内存中
    Json::Value dataArray = configRoot[GET_SAFE_DATA(STR_data)];
    for (uint i = 0; i < dataArray.size(); ++i)
    {
        Json::Value dataObject = dataArray[i];
        Json::Value subDataArray = dataObject[GET_SAFE_DATA(STR_subData)];
        MainData mainData; //value
        std::string Title; //key
        std::map<std::string, LineData> subData;

        mainData.State = dataObject[GET_SAFE_DATA(STR_state)].asBool();
        Title = dataObject[GET_SAFE_DATA(STR_title)].asString();

        for (uint j = 0; j < subDataArray.size(); j++)
        {
            Json::Value lineDataObjcet = subDataArray[j];
            LineData lineData;     //value
            std::string LineTitle; //key

            LineTitle = lineDataObjcet[GET_SAFE_DATA(STR_lineTitle)].asString();
            lineData.LineType = lineDataObjcet[GET_SAFE_DATA(STR_lineType)].asInt();

            if (lineData.LineType == 1)
                lineData.LineValue = std::stod(lineDataObjcet[GET_SAFE_DATA(STR_lineValue)].asString()); //TODO: 未测试是否识别负号
            else if (lineData.LineType == 2)
                lineData.LineState = lineDataObjcet[GET_SAFE_DATA(STR_lineState)].asBool();

            subData.insert(make_pair(LineTitle, lineData));
        }
        mainData.SubData = subData;

        Config->insert(make_pair(Title, mainData));
    }
}

// 通过服务器发送的配置进行初始化
bool Sync::InitConfig(MiHoYoSDK::Bytes &&config)
{
    Json::Reader reader;
    Json::Value root, data;

    // 解析json
    if (!reader.parse(config.get(), root))
        RT("IC Error: 0x01") && CCC("Parse Error");

    Off_MTP = root[GET_SAFE_DATA(STR_offM)].asInt();

    // 构建开启函数
    {
        std::string Funcs = root[GET_SAFE_DATA(STR_func)].asString();
        if (!reader.parse(Funcs, data))
            RT("IC Error: 0x02") && CCC("Parse Error");

        for (int i = 0; i < data.size(); ++i)
        {
            RT("open -->> " + data[i].asString());
            OpenFunc->insert(data[i].asString());
        }
#ifdef RELEASE
        RT("IC done.");
#endif
    }

    // 自校验
    {
        std::string package = FileLine(GET_SAFE_DATA(PATH_Pack));
        std::string apk_path = package + GET_SAFE_DATA(PATH_baseAPK);

        Verify::VerifyFile(root[GET_SAFE_DATA(STR_chaos)].asString(),
                           root[GET_SAFE_DATA(STR_cybl)].asString(),
                           root[GET_SAFE_DATA(STR_apk)].asString());

        MiHoYoSDK::UncompressAPK(apk_path, GET_SAFE_DATA(PATH_RSA), Verify::VerifyCertRsaIns);
#ifdef RELEASE
        RT("IC-VF done.");
#endif
    }

    return false;
}
