#include <sys/ptrace.h>
#include <sys/syscall.h>
#include "src/sdk/MiHoYoSDK.h"

pthread_t MiHoYoSDK::AntiDebugID = 0;

// 开启反调试线程
void MiHoYoSDK::AntiDebug()
{
    if (pthread_create(&AntiDebugID, NULL, &CheckDebug, NULL) != 0)
        CCC("AntiDebug Error!");

    pthread_detach(AntiDebugID);
}

// 检测Debug状态
void *MiHoYoSDK::CheckDebug(void *)
{
    FILE *fd = nullptr;
    char *name = new char[64];
    char *line = new char[256];
    pid_t pid = syscall(__NR_getpid);
    snprintf(name, 64, GET_SAFE_CHAR(StaticData::STR_procStatus), pid); //proc/pid/status-->TracerPid
    while (true)
    {
        fd = fopen(name, "r");
        if (fd == nullptr)
            CCC("fopen Error!");
        while (fgets(line, 256, fd))
        {
            if (strncmp(line, GET_SAFE_CHAR(StaticData::STR_TracerPid), 9) == 0)
            {
                int status = atoi(&line[10]);
                // LOGE("### TracerPid status = %d, %s", status, line);
                fclose(fd);
                syscall(__NR_close, fd);
                if (status != 0)
                    CCC("CheckDebug Error!");
                break;
            }
        }
        sleep(5u);
    }
}
