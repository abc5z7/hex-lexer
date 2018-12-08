//
// Created by 菜包 on 2018-12-08.
//

#ifndef HEX_HEXLEXER_H
#define HEX_HEXLEXER_H

#include "cstdio"
#include "cstring"
#include "cstdlib"
/**
 * hex文件解析器
 */

#pragma warning(disable:4996)
#define MAX_BUFFER_SIZE 43

class Hex {
public:
    Hex(char mark);
    ~Hex();
    void ParseHex(char *data);      // 解析hex文件
    void ParseRecord(char ch);      // 解析每一条记录
    size_t GetRecordLength();       // 获得记录长度
    char GetRecordMark();       // 获取记录标识
    char *GetLoadOffset();      // 获取内存装载偏移
    char *GetRecordType();      // 获取记录类型
    char *GetData();        // 获取数据
    char *GetChecksum();        // 获取校验和
private:
    char m_cBuffer[MAX_BUFFER_SIZE];        // 存储待解析的记录
    char m_cRecordMark;     // 记录标识
    size_t m_nRecordLength;     // 记录长度
    char *m_pLoadOffset;     // 装载偏移
    char *m_pRecordType;        // 记录类型
    char *m_pData;      // 数据字段
    char *m_pChecksum;      // 校验和
    bool m_bRecvStatus;     // 接收状态标识
};


#endif //HEX_HEXLEXER_H
