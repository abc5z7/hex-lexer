//
// Created by 菜包 on 2018-12-08.
//
#include "HexLexer.h"
#include "iostream"
using namespace std;

Hex::Hex(char mark) {
    this->m_cRecordMark = mark;
    m_cBuffer[0] = '\0';
    m_nRecordLength = 0;
    m_pLoadOffset = NULL;
    m_pRecordType = NULL;
    m_pData = NULL;
    m_pChecksum = NULL;
    m_bRecvStatus = false;
} // hex


Hex::~Hex() {
    delete m_pLoadOffset, m_pRecordType, m_pData, m_pChecksum;
} // ~hex


/**
 * 获取记录标识
 *
 * @return ch
 */
char Hex::GetRecordMark() {
    return this->m_cRecordMark;
} // GetRecordMark


/**
 * 获取每条记录的长度
 *
 * @return
 */
size_t Hex::GetRecordLength() {
    if (strlen(m_cBuffer) >= 2) {
        char len[3];
        len[0] = m_cBuffer[0];
        len[1] = m_cBuffer[1];
        len[2] = '\0';
        char *p = NULL;
        return strtol(len, &p, 16);
    } else {
        return 0;
    }
} // GetRecordLength


/**
 * 获取装载偏移
 *
 * @return *ch
 */
char* Hex::GetLoadOffset() {
    if (strlen(m_cBuffer) == (GetRecordLength() + 5) * 2) {
        char *offset = (char*)malloc(sizeof(char) * 5);
        for (int i = 0; i < 4; ++i) {
            offset[i] = m_cBuffer[i + 2];
        }
        offset[4] = '\0';
        m_pLoadOffset = offset;
        offset = NULL;
    }
    return m_pLoadOffset;
} // GetLoadOffset


/**
 * 获取记录类型
 *
 * @return *ch
 */
char* Hex::GetRecordType() {
    if (strlen(m_cBuffer) == (GetRecordLength() + 5) * 2) {
        char *type = (char*)malloc(sizeof(char) * 3);
        type[0] = m_cBuffer[6];
        type[1] = m_cBuffer[7];
        type[2] = '\0';
        m_pRecordType = type;
        type = NULL;
    }
    return m_pRecordType;
} // GetRecordType


/**
 * 获取数据
 *
 * @return *ch
 */
char* Hex::GetData() {
    if (strlen(m_cBuffer) == (GetRecordLength() + 5) * 2) {
        int len = GetRecordLength();
        char *data = (char*)malloc(sizeof(char) * (len * 2 + 1));
        for (int i = 0; i < len * 2; ++i) {
            data[i] = m_cBuffer[i + 8];
        }
        data[len * 2] = '\0';
        m_pData = data;
        data = NULL;
    }
    return m_pData;
} // GetData


/**
 * 获取校验和
 *
 * @return *ch
 */
char* Hex::GetChecksum() {
    int len = GetRecordLength();
    if (strlen(m_cBuffer) == (len + 5) * 2) {
        char *checksum = (char*)malloc(sizeof(char) * 3);
        checksum[0] = m_cBuffer[(len + 5) * 2 - 2];
        checksum[1] = m_cBuffer[(len + 5) * 2 - 1];
        checksum[2] = '\0';
        m_pChecksum = checksum;
        checksum = NULL;
    }
    return m_pChecksum;
} // GetChecksum


/**
 * 解析hex文件中的每一条记录
 *
 * @param ch
 */
void Hex::ParseRecord(char ch) {
    size_t buf_len = strlen(m_cBuffer);
    if (GetRecordMark() == ch) {
        m_bRecvStatus = true;
        m_cBuffer[0] = '\0';
        return;
    }

    if ((buf_len == (GetRecordLength() + 5) * 2 - 1)) {
        // 接收最后一个字符
        m_cBuffer[buf_len] = ch;
        m_cBuffer[buf_len + 1] = '\0';

        // 检验接收的数据
        char temp[3];
        char *p = NULL;
        long int checksum = 0;
        for (int i = 0; i < strlen(m_cBuffer); i += 2) {
            temp[0] = m_cBuffer[i];
            temp[1] = m_cBuffer[i + 1];
            temp[2] = '\0';
            checksum += strtol(temp, &p, 16);
            temp[0] = '\0';
        } // for
        checksum &= 0x00ff;     // 取计算结果的低8位
        if (checksum == 0) {
            cout << "RecordMark " << GetRecordMark() << endl;
            cout << "RecordLength " << GetRecordLength() << endl;
            cout << "LoadOffset " << GetLoadOffset() << endl;
            cout << "RecordType " << GetRecordType() << endl;
            cout << "Data " << GetData() << endl;
            cout << "Checksum " << GetChecksum() << endl;
        } else {
            cout << "ERROR!" << endl;
        }

        m_cBuffer[0] = '\0';
        m_bRecvStatus = false;
        m_nRecordLength = 0;
        m_pLoadOffset = NULL;
        m_pRecordType = NULL;
        m_pChecksum = NULL;
        m_bRecvStatus = false;

    } else if (m_bRecvStatus) {
        m_cBuffer[buf_len] = ch;
        m_cBuffer[buf_len + 1] = '\0';
    } // if
} // ParseRecord


/**
 * 解析hex文件
 *
 * @param data
 */
void Hex::ParseHex(char *data) {
    for (int i = 0; i < strlen(data); ++i) {
        ParseRecord(data[i]);
    }
} // ParseHex