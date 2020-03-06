#include <sys/system_properties.h>
#include <include/openssl/md5.h>
#include <include/openssl/rsa.h>
#include <include/openssl/aes.h>
#include <include/openssl/pem.h>
#include <include/openssl/bio.h>
#include <include/zip/zip.h>

#include "MiHoYoSDK.h"
#include "MiHoYoSDK_StaticData.h"

#define BufferSize 1024 * 4
#define ReadDataSize 1552

const short MiHoYoSDK::SafeChars::key = 0x7BFA;
JavaVM *MiHoYoSDK::Jvm = nullptr;
int MiHoYoSDK::Client = -1;
uint MiHoYoSDK::ReadNullDataTimes = 0;
bool MiHoYoSDK::SyncLock = false;
uint MiHoYoSDK::Times = 0;
std::ofstream *MiHoYoSDK::RunTimeStream = nullptr;
MiHoYoSDK::RSACrypto *MiHoYoSDK::Rsa = nullptr;

//获取UUID
MiHoYoSDK::Bytes GetUUID()
{
#define BytesMD5(data) MD5(buff.append(MD5(data)))

    using namespace MiHoYoSDK;
    using namespace MiHoYoSDK::StaticData;

    Bytes buff;
    char tmp[PROP_VALUE_MAX] = "";
    int len = 0;

    //主板系统
    if ((len = __system_property_get(GET_SAFE_CHAR(roData00), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x00") && CloseChaosCore1("UUID roData00 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //机器品牌
    if ((len = __system_property_get(GET_SAFE_CHAR(roData01), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x01") && CloseChaosCore1("UUID roData01 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //CPU类型
    if ((len = __system_property_get(GET_SAFE_CHAR(roData02), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x02") && CloseChaosCore1("UUID roData02 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //设备名
    if ((len = __system_property_get(GET_SAFE_CHAR(roData03), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x03") && CloseChaosCore1("UUID roData03 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //显示标识
    if ((len = __system_property_get(GET_SAFE_CHAR(roData04), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x04") && CloseChaosCore1("UUID roData04 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //系统主机名
    if ((len = __system_property_get(GET_SAFE_CHAR(roData05), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x05") && CloseChaosCore1("UUID roData05 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //构建ID
    if ((len = __system_property_get(GET_SAFE_CHAR(roData06), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x06") && CloseChaosCore1("UUID roData06 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //制造商
    if ((len = __system_property_get(GET_SAFE_CHAR(roData07), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x07") && CloseChaosCore1("UUID roData07 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //机器型号
    if ((len = __system_property_get(GET_SAFE_CHAR(roData08), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x08") && CloseChaosCore1("UUID roData08 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //系统标记
    if ((len = __system_property_get(GET_SAFE_CHAR(roData09), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x09") && CloseChaosCore1("UUID roData09 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //系统编译类型
    if ((len = __system_property_get(GET_SAFE_CHAR(roData10), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x10") && CloseChaosCore1("UUID roData10 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //系统用户名
    if ((len = __system_property_get(GET_SAFE_CHAR(roData11), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x11") && CloseChaosCore1("UUID roData11 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //版本的增加说明
    if ((len = __system_property_get(GET_SAFE_CHAR(roData12), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x12") && CloseChaosCore1("UUID roData12 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //系统编译的SDK
    if ((len = __system_property_get(GET_SAFE_CHAR(roData13), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x13") && CloseChaosCore1("UUID roData13 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //版本编码名称
    if ((len = __system_property_get(GET_SAFE_CHAR(roData14), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x14") && CloseChaosCore1("UUID roData14 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //公布的版本
    if ((len = __system_property_get(GET_SAFE_CHAR(roData15), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x15") && CloseChaosCore1("UUID roData15 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //系统编译的时间
    if ((len = __system_property_get(GET_SAFE_CHAR(roData16), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x16") && CloseChaosCore1("UUID roData16 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //编译设备名
    if ((len = __system_property_get(GET_SAFE_CHAR(roData17), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x17") && CloseChaosCore1("UUID roData17 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //用户的KEY
    if ((len = __system_property_get(GET_SAFE_CHAR(roData18), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x18") && CloseChaosCore1("UUID roData18 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //机身码
    if ((len = __system_property_get(GET_SAFE_CHAR(roData19), tmp)) <= 0)
        RunTimeLog("GLI Error: 0x19") && CloseChaosCore1("UUID roData19 error!") && CloseChaosCore2();
    buff = BytesMD5(Bytes(tmp, len));

    //cpu最大频率
    std::string cpu_max_freq = ReadFileLine(GET_SAFE_CHAR(pathCPUMaxFreq));
    buff = BytesMD5(cpu_max_freq);

    //cpu最小频率
    std::string cpu_min_freq = ReadFileLine(GET_SAFE_CHAR(pathCPUMinFreq));
    buff = BytesMD5(cpu_min_freq);

    //cpu信息
    std::string cpu_info = ReadFile(GET_SAFE_CHAR(pathCPUInfo));
    buff = BytesMD5(MD5(cpu_info));

    //内存信息
    std::string mem_info = ReadFileLine(GET_SAFE_CHAR(pathMemInfo));
    DeleteAllMark(mem_info, " "); //删掉空格
    buff = BytesMD5(mem_info);

    //系统版本
    std::string version = ReadFileLine(GET_SAFE_CHAR(pathVersion));
    DeleteAllMark(version, " "); //删掉空格
    buff = BytesMD5(version);

    //整体的MD5
    buff = BytesMD5(buff);

    return buff;
#undef BytesMD5
}

//有参构造 公匙string地址, 私匙string地址
MiHoYoSDK::RSACrypto::RSACrypto(const std::string &publicKey, const std::string &privateKey)
{
    if (!publicKey.empty())
    {
        BIO *bio = NULL;

        if ((bio = BIO_new_mem_buf((void *)publicKey.data(), -1)) == NULL)
            RunTimeLog("RC Init Error: 0x01") && CloseChaosCore1("BIO NULL!") && CloseChaosCore2();

        if ((PublicRsa = PEM_read_bio_RSA_PUBKEY(bio, &PublicRsa, NULL, NULL)) == NULL)
            RunTimeLog("RC Init Error: 0x02") && CloseChaosCore1("PublicRsa NULL!") && CloseChaosCore2();

        BIO_set_close(bio, BIO_CLOSE);
        BIO_free(bio);
    }

    if (!privateKey.empty())
    {
        BIO *bio = NULL;

        if ((bio = BIO_new_mem_buf((void *)privateKey.data(), -1)) == NULL)
            RunTimeLog("RC Init Error: 0x03") && CloseChaosCore1("BIO NULL!") && CloseChaosCore2();

        if ((PrivateRsa = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL)) == NULL)
            RunTimeLog("RC Init Error: 0x04") && CloseChaosCore1("PrivateRsa NULL!") && CloseChaosCore2();

        BIO_set_close(bio, BIO_CLOSE);
        BIO_free(bio);
    }

    if (PublicRsa == nullptr || PrivateRsa == nullptr)
        RunTimeLog("RC Init Error: 0x00") && CloseChaosCore1("RSA Init Error!") && CloseChaosCore2();
}

//公匙加密
MiHoYoSDK::Bytes MiHoYoSDK::RSACrypto::publicEncrypt(const Bytes &data)
{
    if (PublicRsa == nullptr)
        RunTimeLog("PE Error: 0x00") && CloseChaosCore1("PublicRsa Null Error!") && CloseChaosCore2();

    Bytes result;
    int status = 0;                                           //每次加密的长度
    int input_len = data.length();                            //数据总长度
    const int key_size = RSA_size(PublicRsa);                 //密匙长度
    const int block_size = key_size - RSA_PKCS1_PADDING_SIZE; //分块加密的块大小
    uchar *to = (uchar *)malloc(key_size + 1);                //存储加密的数据
    memset(to, 0x00, key_size + 1);

    for (int i = 0; i < input_len; i += block_size)
    {
        status = RSA_public_encrypt(std::min(block_size, input_len - i),
                                    (uchar *)&data.c_str()[i], to, PublicRsa, RSA_PKCS1_PADDING);

        if (status < 0)
            RunTimeLog("PE Error: 0x01") && CloseChaosCore1("PublicEncrypt status: " + ToString(status)) && CloseChaosCore2();

        result.append((char *)to, status);
    }

    free(to); //资源释放
    return result;
}

//公匙验证
bool MiHoYoSDK::RSACrypto::publicVerify(const Bytes &data, const Bytes &sign)
{
    if (PublicRsa == nullptr)
        return RunTimeLog("PV Error: 0x00") && CloseChaosCore1("PublicRsa Null Error!") && CloseChaosCore2();

    EVP_MD_CTX *rsa_verify_ctx = EVP_MD_CTX_create();
    EVP_PKEY *pub_key = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pub_key, PublicRsa);

    if (EVP_DigestVerifyInit(rsa_verify_ctx, NULL, EVP_sha256(), NULL, pub_key) <= 0)
        return RunTimeLog("PV Error: 0x01") && CloseChaosCore1("VerifyInit Error!") && CloseChaosCore2();

    if (EVP_DigestVerifyUpdate(rsa_verify_ctx, data.c_str(), data.length()) <= 0)
        return RunTimeLog("PV Error: 0x02") && CloseChaosCore1("VerifyUpdate Error!") && CloseChaosCore2();

    if (EVP_DigestVerifyFinal(rsa_verify_ctx, (uchar *)sign.c_str(), sign.length()) <= 0)
        return RunTimeLog("PV Error: 0x03") && CloseChaosCore1("VerifyFinal Error!") && CloseChaosCore2();

    EVP_PKEY_free(pub_key);
    EVP_MD_CTX_destroy(rsa_verify_ctx);
    return false;
}

//私匙解密
MiHoYoSDK::Bytes MiHoYoSDK::RSACrypto::privateDecrypt(const Bytes &data)
{
    if (PrivateRsa == nullptr)
        RunTimeLog("PD Error: 0x00") && CloseChaosCore1("PrivateRsa Null Error!") && CloseChaosCore2();

    Bytes result;
    int status = 0;
    const int key_size = RSA_size(PrivateRsa);
    uchar *to = (uchar *)malloc(key_size + 1);
    memset(to, 0x00, key_size + 1);

    for (int i = 0; i < data.length(); i += key_size)
    {
        status = RSA_private_decrypt(std::min(key_size, (int)data.length() - i),
                                     (uchar *)&data.c_str()[i], to, PrivateRsa, RSA_PKCS1_PADDING);

        if (status < 0)
            RunTimeLog("PD Error: 0x01") && CloseChaosCore1("PrivateDecrypt status: " + ToString(status)) && CloseChaosCore2();

        result.append((char *)to, status);
    }

    free(to); //资源释放
    return result;
}

//私匙签名
MiHoYoSDK::Bytes MiHoYoSDK::RSACrypto::privateSign(const Bytes &data)
{
    if (PrivateRsa == nullptr)
        RunTimeLog("PS Error: 0x00") && CloseChaosCore1("PrivateRsa Null Error!") && CloseChaosCore2();

    EVP_MD_CTX *rsa_sign_ctx = EVP_MD_CTX_create();
    EVP_PKEY *pri_key = EVP_PKEY_new();
    EVP_PKEY_set1_RSA(pri_key, PrivateRsa);

    if (EVP_DigestSignInit(rsa_sign_ctx, NULL, EVP_sha256(), NULL, pri_key) <= 0)
        RunTimeLog("PS Error: 0x01") && CloseChaosCore1("SignInit Error!") && CloseChaosCore2();

    if (EVP_DigestSignUpdate(rsa_sign_ctx, data.c_str(), data.length()) <= 0)
        RunTimeLog("PS Error: 0x02") && CloseChaosCore1("SignUpdate Error!") && CloseChaosCore2();

    size_t sign_len;
    if (EVP_DigestSignFinal(rsa_sign_ctx, NULL, &sign_len) <= 0)
        RunTimeLog("PS Error: 0x03") && CloseChaosCore1("SignLength Error!") && CloseChaosCore2();

    uchar *buff = (uchar *)malloc(sign_len);
    memset(buff, 0x00, sign_len);
    if (EVP_DigestSignFinal(rsa_sign_ctx, buff, &sign_len) <= 0)
        RunTimeLog("PS Error: 0x04") && CloseChaosCore1("SignFinal Error!") && CloseChaosCore2();

    Bytes result((char *)buff, sign_len);
    free(buff);
    EVP_PKEY_free(pri_key);
    EVP_MD_CTX_destroy(rsa_sign_ctx);
    return result;
}

//获取模块基址
ulong MiHoYoSDK::GetModuleBaseAdderss(const char *module_name)
{
    FILE *fp;
    ulong addr = 0;
    char *pch;
    char line[1024];

    if ((fp = fopen(GET_SAFE_CHAR(StaticData::mapsPath), "r")) == NULL)
        RunTimeLog("MBA Error: 0x00") && CloseChaosCore1("Fopen Error") && CloseChaosCore2();

    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, module_name))
        {
            pch = strtok(line, "-");
            addr = strtoul(pch, NULL, 16);
            if (addr == 0x8000)
                addr = 0;
            break;
        }
    }

    fclose(fp);
    return addr;
}

//子串删除
std::string &MiHoYoSDK::DeleteAllMark(std::string &src, const std::string &mark)
{
    if (src.empty())
        return src;

    size_t size = mark.size();
    while (true)
    {
        size_t pos = src.find(mark);
        if (pos == std::string::npos)
            break;
        src.erase(pos, size);
    }

    return src;
}

//子串替换
std::string &MiHoYoSDK::ReplaceAll(std::string &src, const std::string &from, const std::string &to)
{
    if (src.empty() || from.empty())
        return src;
    size_t start_pos = 0;
    size_t size = from.size();
    while ((start_pos = src.find(from, start_pos)) != std::string::npos)
    {
        src.replace(start_pos, size, to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }

    return src;
}

//读取文件到字符串
std::string MiHoYoSDK::ReadFile(const std::string &path)
{
    std::ifstream fs(path);
    std::stringstream buffer;
    buffer << fs.rdbuf();
    fs.close();
    return buffer.str();
}

//读取文件到字符串(单行)
std::string MiHoYoSDK::ReadFileLine(const std::string &path)
{
    std::string tmp;
    std::ifstream in(path);
    std::getline(in, tmp, '\n');
    in.close();
    return tmp.substr(0, tmp.find_last_not_of(" \n\r\t") + 1);
}

//写出到文件
void MiHoYoSDK::WriteFile(const std::string &src, const std::string &path)
{
    std::ofstream out(path, std::ios::trunc);
    out << src;
    out.close();
}

//获取当前时间(毫秒级)
const std::string MiHoYoSDK::NowTime()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    time_t t = time(NULL);
    tm *ptm = localtime(&t);

    static char szTime[19];
    snprintf(szTime, sizeof(szTime), GET_SAFE_CHAR(StaticData::timeFormat),
             ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, tv.tv_usec);
    szTime[18] = 0;

    return std::string(szTime);
}

//获取JINEnv
JNIEnv *MiHoYoSDK::EnsureEnvCreated()
{
    JNIEnv *env;
    Jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
    return env;
}

//关闭ChaosCore
bool MiHoYoSDK::CloseChaosCore1(std::string msg)
{
    if (msg.empty())
        LOGE("CCC call!");
    else
        LOGE("CCC! Error: %s", msg.c_str());

    JNIEnv *env = EnsureEnvCreated();
    env->ExceptionDescribe();
    env->ExceptionClear();
    return true;
}

//解压APK并且调用回调
void MiHoYoSDK::UncompressApk(const std::string &path, const std::string &name, verifyCallBack callBack)
{
    struct zip *apkArchive = nullptr;
    struct zip_stat fileStat;
    struct zip_file *file = nullptr;

    if ((apkArchive = zip_open(path.c_str(), 0, nullptr)) == nullptr)
        RunTimeLog("UPA Error: 0x00") && CloseChaosCore1("zip open Error") && CloseChaosCore2();

    if ((file = zip_fopen(apkArchive, name.c_str(), 0)) == nullptr)
        RunTimeLog("UPA Error: 0x01") && CloseChaosCore1("zip fopen Error") && CloseChaosCore2();

    zip_stat_init(&fileStat);
    zip_stat(apkArchive, name.c_str(), 0, &fileStat);

    char *buffer = (char *)malloc(fileStat.size);
    zip_fread(file, buffer, fileStat.size);

    if (!callBack(buffer, fileStat.size))
        RunTimeLog("UPA Error: 0x02") && CloseChaosCore1() && CloseChaosCore2();

    free(buffer);
    zip_fclose(file);
    zip_close(apkArchive);
}

//解密Ascii
void MiHoYoSDK::DecryptAscii(int data[], const short key)
{
    for (int i = 0; i < 64; ++i)
        data[i] ^= key;
}

//验证Ascii
void MiHoYoSDK::CheakAscii(int data[], char src[], const short key)
{
    for (int i = 0; i < 64; ++i)
        if (src[i] != (char)((data[i] ^ key) >> 2))
            CloseChaosCore1("CA Error") && CloseChaosCore2();
        else
            data[i] = src[i] = 0xff;
}

//获取MD5
MiHoYoSDK::Bytes MiHoYoSDK::MD5(const Bytes &src, bool notNull)
{
    if (notNull)
        if (src.length() <= 0)
            CloseChaosCore1("MD5 Error") && CloseChaosCore2();

    char hex[33] = "";
    uchar digest[MD5_DIGEST_LENGTH];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, src.c_str(), src.length());
    MD5_Final(digest, &ctx);

    memset(hex, 0, sizeof(hex));
    for (int i = 0; i != sizeof(digest); i++)
        snprintf(hex + (i * 2), 3, GET_SAFE_CHAR(StaticData::md5Format), digest[i]);
    hex[32] = '\0';

    return Bytes(hex, 32);
}

//AES加密
MiHoYoSDK::Bytes MiHoYoSDK::AESEncode(const Bytes &src, const std::string &key)
{
    int block_count = 0;
    int quotient = src.length() / AES_BLOCK_SIZE;
    int mod = src.length() % AES_BLOCK_SIZE;
    block_count = quotient + 1;
    int out_size = AES_BLOCK_SIZE * block_count;

    //填充数据
    int padding = AES_BLOCK_SIZE - mod;
    char *in = (char *)malloc(out_size);
    memset(in, padding, out_size);
    memcpy(in, src.c_str(), src.length());

    //out
    char *out = (char *)malloc(out_size);
    memset(out, 0x00, out_size);

    //初始向量为全0
    uchar iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);

    //获取密匙
    AES_KEY aes;
    if (AES_set_encrypt_key((uchar *)key.c_str(), key.length() * 8, &aes) < 0)
        RunTimeLog("AE Error: 0x00") && CloseChaosCore1("AESEncode Error!") && CloseChaosCore2();

    //加密
    AES_cbc_encrypt((uchar *)in, (uchar *)out, out_size, &aes, iv, AES_ENCRYPT);

    Bytes result(out, out_size);
    free(out);
    free(in);
    return result;
}

//AES解密
MiHoYoSDK::Bytes MiHoYoSDK::AESDecode(const Bytes &src, const std::string &key)
{
    //初始向量为全0
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);

    //密匙
    AES_KEY aes;
    if (AES_set_decrypt_key((uchar *)key.c_str(), key.length() * 8, &aes) < 0)
        RunTimeLog("AD Error: 0x00") && CloseChaosCore1("AESDecrypt Error!") && CloseChaosCore2();

    const int src_len = src.length();
    char *tmp = (char *)malloc(src_len);
    memset(tmp, 0x00, src_len);
    AES_cbc_encrypt((uchar *)src.c_str(), (uchar *)tmp, src_len, &aes, iv, AES_DECRYPT);

    //PKCS5 UNPADDING
    int unpadding = tmp[src_len - 1];
    int out_len = src_len - unpadding;
    char *out = (char *)malloc(out_len);
    memcpy(out, tmp, out_len);

    Bytes result(out, out_len);
    free(out);
    free(tmp);
    return result;
}

//Base64加密
MiHoYoSDK::Bytes MiHoYoSDK::Base64Encode(const Bytes &src)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, src.c_str(), src.length());
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);
    Bytes result(buff, bptr->length);
    free(buff);
    return result;
}

//Base64解密
MiHoYoSDK::Bytes MiHoYoSDK::Base64Decode(const Bytes &src);

//连接服务器
void MiHoYoSDK::LinkServer(const uint channelID, void (*initCallback)(const Bytes &src))
{
    MiHoYoSDK::RunTimeInit();

    Rsa = new RSACrypto(GET_SAFE_DATA(StaticData::safePublicKey),
                        GET_SAFE_DATA(StaticData::safePrivateKey));

    SafeChars ip(GET_SAFE_CORT(StaticData::serverIP));
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7557);                        //端口
    server_addr.sin_addr.s_addr = inet_addr(ip.get().c_str()); //远程服务器IP
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.2");    //本地调试IP

    if ((Client = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        RunTimeLog("LS Error: 0x00") && CloseChaosCore1("Socket Create Error!") && CloseChaosCore2();

    //链接套接字
    if (connect(Client, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        RunTimeLog("LS Error: 0x01") && CloseChaosCore1("Socket Connect Error!") && CloseChaosCore2();

    static struct timeval timeout = {15, 0};
    if (setsockopt(Client, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) != 0)
        RunTimeLog("LS Error: 0x06-" + ToString(errno)) && CloseChaosCore1("Setsockopt Error!") && CloseChaosCore2();
    if (setsockopt(Client, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) != 0)
        RunTimeLog("LS Error: 0x07-" + ToString(errno)) && CloseChaosCore1("Setsockopt Error!") && CloseChaosCore2();

    Json::Value root;
    root[GET_SAFE_DATA(StaticData::versionStr)] = GET_SAFE_DATA(StaticData::version);
    root[GET_SAFE_DATA(StaticData::channelStr)] = channelID;
    root[GET_SAFE_DATA(StaticData::uuidStr)] = GetUUID().c_str();
    root[GET_SAFE_DATA(StaticData::uifStr)] = ReadFile(GET_SAFE_DATA(StaticData::uifPath));

    initCallback(SendJSON(GET_SAFE_CHAR(StaticData::loginStr), root));
}

//发送并接收数据
MiHoYoSDK::Bytes MiHoYoSDK::SendMsg(const Bytes &msg)
{
    for (uint i = 0; i < 20; i++) //防止死锁
    {
        if (i == 19)
            RunTimeLog("SM Error: 0x00") && CloseChaosCore1("SyncLock Error!") && CloseChaosCore2();
        if (SyncLock)
            sleep(1);
        else
            break;
    }
    SyncLock = true;

    char lenBuf[6] = "";
    uint msg_len = msg.length();
    snprintf(lenBuf, 6, "%05u", msg_len);
    Bytes send_msg(lenBuf, 5);
    send_msg.append(msg);

    if (send(Client, send_msg.c_str(), send_msg.length(), 0) <= 0)
        RunTimeLog("SM Error: 0x01-" + ToString(errno)) && CloseChaosCore1("Errno: " + ToString(errno)) && CloseChaosCore2();

    Bytes read_data;
    int rec_len = 0;
    int data_len = 0;
    static char buff[BufferSize] = "";
    for (int count = 0; count < 10; ++count)
    {
        if ((rec_len = recv(Client, buff, BufferSize, 0)) <= 0)
        {
            if (rec_len < 0)
                RunTimeLog("SM Error: 0x02-" + ToString(errno)) && CloseChaosCore1("Errno: " + ToString(errno)) && CloseChaosCore2();

            RunTimeLog("SM Error: 0x03") && CloseChaosCore1("Read Null Data") && CloseChaosCore2();
        }

        if (data_len == 0)
        {
            data_len = std::stoi(std::string(buff, 5));
            if (data_len <= 0)
                RunTimeLog("SM Error: 0x04") && CloseChaosCore1("data_len Error") && CloseChaosCore2();
            read_data.append(Bytes(buff + 5, rec_len - 5));
        }
        else
            read_data.append(buff, rec_len);

        if (read_data.length() == data_len)
            break;
    }

    SyncLock = false;
    return read_data;
}

//双向验证的发送接收数据
MiHoYoSDK::Bytes MiHoYoSDK::SendMsgEX(const Bytes &send_msg)
{
    using namespace StaticData;
    Bytes symbol(GET_SAFE_DATA(symbolStr));
    if (Rsa == nullptr)
        RunTimeLog("EX Error: 0x00") && CloseChaosCore1("Rsa Null Error!") && CloseChaosCore2();

    Bytes send_cipher_data = Rsa->publicEncrypt(send_msg); //加密数据
    Bytes send_sign = Rsa->privateSign(send_cipher_data);  //签名
    send_cipher_data.append(symbol);
    send_cipher_data.append(send_sign);
    Bytes send_base_data = Rsa->publicEncrypt(send_cipher_data);                  //整体加密
    Bytes send_aes_data = AESEncode(send_base_data, GET_SAFE_DATA(serverAESKey)); //AES保护

    //发送数据
    Bytes read_msg = SendMsg(send_aes_data);
    Bytes read_aes_data = AESDecode(read_msg, GET_SAFE_DATA(clientAESKey)); //AES解包
    Bytes read_base_data = Rsa->privateDecrypt(read_aes_data);              //整体解密

    int index = read_base_data.find(symbol);
    if (index < 0)
        RunTimeLog("EX Error: 0x01") && CloseChaosCore1("Symbol not find!") && CloseChaosCore2();

    //提取数据
    Bytes read_cipher_data = Bytes(read_base_data.c_str(), index);
    Bytes read_sign = Bytes(read_base_data.c_str() + index + symbol.length(),
                            read_base_data.length() - symbol.length() - read_cipher_data.length());

    //验证数据
    if (Rsa->publicVerify(read_cipher_data, read_sign))
        RunTimeLog("EX Error: 0x02") && CloseChaosCore1("Verify Error!") && CloseChaosCore2();
    Bytes data = Rsa->privateDecrypt(read_cipher_data); //解密数据
    return data;
}

//JSON格式收发数据
MiHoYoSDK::Bytes MiHoYoSDK::SendJSON(const char *route, const Json::Value &send_data)
{
    using namespace StaticData;
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value send_root, read_root;
    send_root[GET_SAFE_DATA(dateStr)] = NowTime();
    send_root[GET_SAFE_DATA(routeStr)] = route;
    send_root[GET_SAFE_DATA(dataStr)] = writer.write(send_data);

    Bytes json = writer.write(send_root);
    Bytes read_data = SendMsgEX(json);

    //解析JSON
    if (!reader.parse(read_data.c_str(), read_root))
        RunTimeLog("SJ Error: 0x00") && CloseChaosCore1("Parse Error!") && CloseChaosCore2();
    if (!read_root.isMember(GET_SAFE_DATA(statusStr)) ||
        !read_root.isMember(GET_SAFE_DATA(dataStr)) ||
        !read_root.isMember(GET_SAFE_DATA(errorStr)))
        RunTimeLog("SJ Error: 0x01") && CloseChaosCore1("Key Error!") && CloseChaosCore2();

    int status = read_root[GET_SAFE_DATA(statusStr)].asInt();
    std::string error = read_root[GET_SAFE_DATA(errorStr)].asString();
    // std::string Data = read_root[GET_SAFE_DATA(dataStr)].asString();
    std::string Data = writer.write(read_root[GET_SAFE_DATA(dataStr)]);

    // RunTimeLog("status:#" + std::to_string(status) + "#");
    // RunTimeLog("error:#" + error + "#");
    // RunTimeLog("Data:#" + Data + "#");

    if (!error.empty() || status != 200)
        RunTimeLog(ToString(status) + ": " + error) && CloseChaosCore1("Server Error!") && CloseChaosCore2();

    return Data;
}

//初始化运行日志
void MiHoYoSDK::RunTimeInit()
{
    if (RunTimeStream != nullptr)
        return;

    RunTimeStream = new std::ofstream(GET_SAFE_DATA(StaticData::pathLog),
                                      std::ios::out | std::ios::trunc | std::ios::binary);

    if (RunTimeStream == nullptr && RunTimeStream->is_open() == false)
        CloseChaosCore1("RT Open Error!!!") && CloseChaosCore2();

    RunTimeLog(GET_SAFE_DATA(StaticData::logStartStr));
}
