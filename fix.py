# coding=utf-8
import hashlib
import random
import string
import re

# 混淆后的变量/方法名
new_name_list = []


def hash_name(name):
    """生成随机名字"""
    m = hashlib.md5()
    # 生成随机变量名
    m.update(name.encode("utf-8"))
    # 生成随机盐
    salt = ''.join(random.sample(string.ascii_letters + string.digits, 32))
    m.update(salt.encode("utf-8"))
    # 生成一个32位的字串
    temp_name = m.hexdigest()

    # 强制以字母作为变量/方法名的开头
    while temp_name[0].isdigit():
        salt = ''.join(random.sample(string.ascii_letters + string.digits, 32))
        m.update(salt.encode("utf-8"))
        temp_name = m.hexdigest()

    # 不能重名
    while temp_name in new_name_list:
        # 强制以字母作为变量/方法名的开头
        while temp_name[0].isdigit():
            salt = ''.join(random.sample(
                string.ascii_letters + string.digits, 32))
            m.update(salt.encode("utf-8"))
            temp_name = m.hexdigest()
    else:
        new_name_list.append(temp_name)

    return temp_name


def backup(file_in):
    """备份文件"""
    bak = open(file_in.name + '.bak', 'w', encoding='utf-8')
    bak.write(file_in.read())
    bak.close()
    file_in.seek(0)


def confuse(path_filename):
    """混淆"""
    reg = re.compile(r'#define (?P<fun_name>\w*) (?P<cf_name>\w*)')
    file_content = ''
    try:
        file_in = open(path_filename, encoding='utf-8')
        backup(file_in)

        while True:
            line = file_in.readline()
            if len(line) == 0:
                break

            regMatch = reg.match(line)
            if regMatch != None:
                linebits = regMatch.groupdict()
                new_name = hash_name(linebits['fun_name'])
                line = line.replace(linebits['cf_name'], new_name)

            file_content += line

        file_in.close()
        # 重写文件
        file_in = open(path_filename, 'w', encoding="utf-8")
        file_in.write(file_content)
        file_in.close()

    except Exception as err:
        print('发生异常: ' + str(err))


if __name__ == "__main__":
    confuse(r"""E:\HonkaiImpact3RD\Dark\dev-s\jni\fix.h""")
