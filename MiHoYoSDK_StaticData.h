#pragma once

#define GET_SAFE_CORT(name) name, sizeof(name)
#define GET_SAFE_CHAR(name) (MiHoYoSDK::SafeChars(name, sizeof(name)).get().c_str())
#define GET_SAFE_DATA(name) (MiHoYoSDK::SafeChars(name, sizeof(name)).get())

//SDK
namespace MiHoYoSDK
{
//静态数据
namespace StaticData
{

extern int serverIP[14];
extern int serverAESKey[32];
extern int clientAESKey[32];

//4096k
extern int safePublicKey[796];
extern int safePrivateKey[3239];

//1024k
// extern int safePublicKey[272];
// extern int safePrivateKey[887];

extern int pathCPUMaxFreq[53];
extern int pathCPUMinFreq[53];
extern int pathCPUInfo[13];
extern int pathMemInfo[13];
extern int pathVersion[13];
extern int pathLog[43];
extern int roData00[17];
extern int roData01[16];
extern int roData02[18];
extern int roData03[17];
extern int roData04[19];
extern int roData05[13];
extern int roData06[11];
extern int roData07[23];
extern int roData08[16];
extern int roData09[13];
extern int roData10[13];
extern int roData11[13];
extern int roData12[28];
extern int roData13[20];
extern int roData14[25];
extern int roData15[24];
extern int roData16[17];
extern int roData17[16];
extern int roData18[20];
extern int roData19[20];
extern int timeFormat[30];
extern int md5Format[4];
extern int mapsPath[15];
extern int uifPath[36];

extern int symbolStr[13];
extern int logStartStr[18];
extern int loginStr[5];
extern int loopSyncStr[8];
extern int uuidStr[4];
extern int uifStr[3];
extern int dateStr[4];
extern int routeStr[5];
extern int dataStr[4];
extern int statusStr[6];
extern int errorStr[5];
extern int versionStr[7];
extern int subDataStr[7];
extern int stateStr[5];
extern int titleStr[5];
extern int lineTitleStr[9];
extern int lineTypeStr[8];
extern int lineValueStr[9];
extern int lineStateStr[9];
extern int offStr[3];
extern int funcsStr[5];

extern int jsonPath[41];
extern int cfgPath[40];
extern int libPath[20];
extern int tpsafeLib[14];
extern int il2cppLib[12];
extern int dlopenV26Str[21];
extern int dlopenV24Str[21];
extern int dlopenV19Str[21];
extern int dlopenStr[14];

extern int binRsaKey[64];

} // namespace StaticData
} // namespace MiHoYoSDK