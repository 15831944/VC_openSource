/**************************************************************************************
* Copyright (c) 2007 Senselock Data Security Centre.
* All rights reserved.
*
* filename: EleT2.h
*
* brief: EleT2 library interface declaration, return value and some constant definition.
* 
* history:
*
***************************************************************************************/



#ifndef __ELET2_H__
#define __ELET2_H__

#ifdef __cplusplus
extern "C" {
#endif

// ���󷵻�ֵ
#define ELE_T2_SUCCESS                           0x00020000  // �ɹ�
#define ELE_T2_NO_MORE_DEVICE                    0x00020001  // û���ҵ���Ӧ��ģ���豸
#define ELE_T2_INVALID_PASSWORD                  0x00020002  // ��Ч������
#define ELE_T2_INSUFFICIENT_BUFFER               0x00020003  // ����������
#define ELE_T2_BEYOND_DATA_SIZE                  0x00020004  // ��д������Խ��

unsigned long EleT2Read(
    unsigned short usOffset, 
    unsigned char* pucOutbuffer, 
    unsigned short usOutbufferLen, 
    unsigned short* usReadLen
    );
    
unsigned long EleT2Write(
    unsigned short usOffset, 
    char* pcPassword, 
    unsigned char *pucInbuffer, 
    unsigned short usInbufferLen, 
    unsigned short*usWrittenLen
    );

unsigned long EleT2ChangePassword(
    char* pcOldPass,
    char* pcNewPass
    );

#ifdef __cplusplus
}
#endif
#endif  // __ELET2_H__





















