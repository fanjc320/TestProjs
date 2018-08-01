// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// TestRb1.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������

const char* StringToANSI(const char*   pUtf8Buf)
{
#ifdef WIN32
	DWORD   UniCodeLen = MultiByteToWideChar(CP_UTF8, 0, pUtf8Buf, -1, NULL, 0);
	std::vector <wchar_t>   vWCH(UniCodeLen);
	MultiByteToWideChar(CP_UTF8, 0, pUtf8Buf, -1, &vWCH[0], UniCodeLen);
	DWORD   dwASCIILen = WideCharToMultiByte(CP_ACP, 0, &vWCH[0], UniCodeLen, NULL, NULL, NULL, NULL);
	ASSERT(dwASCIILen + 1 < 2048);
	memset(StringConversionStorage, 0, (sizeof(char)*dwASCIILen) + 1);
	WideCharToMultiByte(CP_ACP, 0, &vWCH[0], UniCodeLen, StringConversionStorage, dwASCIILen, NULL, NULL);
	return &StringConversionStorage[0];
#else
	//CharsetConvertor *conv1 = FlyWeight::GetCharsetConvertor(CharsetConvertor::CHARSET_GBK, CharsetConvertor::CHARSET_UTF8);
	sLog.outError("", "StringToANSI 1  ------------ ");
	std::string str1;
	std::string str2;
	//if (IsStringUTF8(pUtf8Buf)==false)
	{
		sLog.outError("", "StringToANSI 2  ------------ ");
		return pUtf8Buf;
	}
	sLog.outError("", "StringToANSI 3  ------------ ");
	CharsetConvertor conv2(CharsetConvertor::CHARSET_UTF8, CharsetConvertor::CHARSET_GBK);
	sLog.outError("", "StringToANSI 3 1  ------------ ");
	str2 = pUtf8Buf;
	str1 = conv2.Convert(str2);
	sLog.outError("", "StringToANSI 4  ------------ ");
	return str1.c_str();
#endif
}