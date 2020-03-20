#pragma once
#include "src/hook/hook.h"

//Hook架构
namespace Hook
{
//Lib加载模块
namespace Loaded
{

// 加载tersafe2库文件
bool LoadTersafe2Lib(void *handle);

//Tersafe2模块
namespace Tersafe2
{

//文件开启函数
int SysOpen(int a1, const char *a2, int a3, int a4);
extern int (*_SysOpen)(int, const char *, int, int);

}
}
}
