#include "TestToValue.h"

CTestToValue::CTestToValue(void)
{
}

CTestToValue::~CTestToValue(void)
{
}

bool CTestToValue::Test()
{
	//布尔类型测试
	{
		//正向
		{
			signed char nSrc = 100;
			bool bDes=0;
			ASSERT_LOG_ERROR(!ToolFrame::ToValue(nSrc,bDes));
			nSrc = 0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(nSrc,bDes));
			ASSERT_LOG_ERROR(bDes == false);
			nSrc = 1;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(nSrc,bDes));
			ASSERT_LOG_ERROR(bDes == true);
			nSrc = 2;
			ASSERT_LOG_ERROR(!ToolFrame::ToValue(nSrc,bDes));
		}

		//逆向
		{
			bool bSrc = 1;
			signed char nDes=0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(bSrc,nDes));
			ASSERT_LOG_ERROR( 1 == nDes);
		}
	}

	//编译通过测试(各种类型)
	{
		bool b;
		char nChar;
		signed char nSignedChar;
		unsigned char uChar;
// 		short nShort;
// 		unsigned short uShort;
// 		long nLong;
// 		unsigned long uLong;
 		int nInt;
 		unsigned int uInt;

		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((char)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((signed char)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((short)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((long)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((int)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned char)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned short)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned long)1,b));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned int)1,b));

		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((char)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((signed char)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((short)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((long)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((int)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned char)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned short)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned long)1,nChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned int)1,nChar));

		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((char)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((signed char)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((short)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((long)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((int)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned char)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned short)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned long)1,nSignedChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned int)1,nSignedChar));

		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((char)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((signed char)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((short)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((long)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((int)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned char)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned short)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned long)1,uChar));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned int)1,uChar));

		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((char)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((signed char)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((short)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((long)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((int)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned char)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned short)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned long)1,nInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned int)1,nInt));

		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((char)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((signed char)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((short)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((long)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((int)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned char)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned short)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned long)1,uInt));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((unsigned int)1,uInt));
	}

	//数值之间转换测试
	{
		bool nSrc1		= 0;
		INT8 nSrc8		= 2;
		INT16 nSrc16	= 3;
		INT32 nSrc32	= 4;
		UINT8 uSrc8		= 5;
		UINT16 uSrc16	= 6;
		UINT32 uSrc32	= 7;
		//bool
		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,nSrc1));
		ASSERT_LOG_ERROR(true == nSrc1);
		ASSERT_LOG_ERROR(ToolFrame::ToValue((INT8)0,nSrc1));
		ASSERT_LOG_ERROR(false == nSrc1);
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT8)30,nSrc1));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT16)30,nSrc1));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT32)30,nSrc1));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((UINT16)30,nSrc1));

		//int8
		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,nSrc8));
		ASSERT_LOG_ERROR(1 == nSrc8);
		ASSERT_LOG_ERROR(ToolFrame::ToValue((INT8)5,nSrc8));
		ASSERT_LOG_ERROR(5 == nSrc8);
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT16)500,nSrc8));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT32)500,nSrc8));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((UINT8)255,nSrc8));

		//int16

		//int32
		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,nSrc32));
		ASSERT_LOG_ERROR(1 == nSrc32);
		ASSERT_LOG_ERROR(ToolFrame::ToValue((INT8)5,nSrc32));
		ASSERT_LOG_ERROR(5 == nSrc32);
		ASSERT_LOG_ERROR(ToolFrame::ToValue((INT16)500,nSrc32));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((INT32)500,nSrc32));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((UINT8)255,nSrc32));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((UINT32)65530,nSrc32));

		//uint8
		ASSERT_LOG_ERROR(ToolFrame::ToValue((bool)1,uSrc8));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT8)-1,uSrc8));
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT32)3000,uSrc8));
		
		//uint32
		ASSERT_LOG_ERROR(!ToolFrame::ToValue((INT32)-1,uSrc32));
		ASSERT_LOG_ERROR(ToolFrame::ToValue((INT32)500,uSrc32));
		ASSERT_LOG_ERROR(500 == uSrc32);
	}

	//String to Value
	{
		{
			if (!TestStringToValue("1b",(bool)1,(bool)0))return false;
			if (!TestStringToValue("1B",(bool)1,(bool)0))return false;
			if (!TestStringToValue("11o",(int)9,(int)0))return false;
			if (!TestStringToValue("11O",(int)9,(int)0))return false;
			if (!TestStringToValue("11",(int)11,(int)0))return false;
			if (!TestStringToValue("0x11",(int)17,(int)0))return false;
			if (!TestStringToValue("0X11",(int)17,(int)0))return false;

			int n=0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue("0x111b",n));

			unsigned char c=0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue("0xff",c));
			ASSERT_LOG_ERROR( 0xff == c );
			ASSERT_LOG_ERROR(!ToolFrame::ToValue("0xffff",c));

			signed char d = 0;
			ASSERT_LOG_ERROR(ToolFrame::ToValue("-50",d));
			ASSERT_LOG_ERROR(-50 == d);

			ASSERT_LOG_ERROR(ToolFrame::ToValue("-0x7f",d));
			ASSERT_LOG_ERROR(-127 == d);

			float f = 0.0f;
			ASSERT_LOG_ERROR(ToolFrame::ToValue("-1.25",f));
			ASSERT_LOG_ERROR(f > -1.2500001 && f < -1.2499999f );
		}
	}

	//测试容器转换
	{
		{
			std::set<int> vInt;
			std::vector<unsigned char> vChar;

			vInt.insert(1);
			vInt.insert(2);
			vInt.insert(4);
			vInt.insert(8);

			ASSERT_LOG_ERROR(ToolFrame::ToValue(vInt,vChar));

			std::vector<unsigned char> vDes;
			vDes.push_back(1);
			vDes.push_back(2);
			vDes.push_back(4);
			vDes.push_back(8);

			ASSERT_LOG_ERROR(ToolFrame::IsEqual(vDes,vChar));
		}
		{
			std::vector<int> vInt;
			std::set<unsigned char> vChar;

			vInt.push_back(1);
			vInt.push_back(2);
			vInt.push_back(4);
			vInt.push_back(-8);

			ASSERT_LOG_ERROR(!ToolFrame::ToValue(vInt,vChar));
		}
		{
			VectorString vString;
			vString.push_back("11");
			vString.push_back("-11");
			vString.push_back("0");
			vString.push_back("11B");
			vString.push_back("-11B");
			vString.push_back("11O");
			vString.push_back("-11O");
			vString.push_back("0x11");
			vString.push_back("-0x11");
			vString.push_back("-0X12");

			VectorInt	vInt;
			std::vector<double> vDouble;
			std::list<int> vListInt;
			VectorString vStringDes;
			VectorInt	vEnd;
			SetInt		vSetInt;

			ASSERT_LOG_ERROR(ToolFrame::ToValue(vString,vInt));
			ASSERT_LOG_ERROR(ToolFrame::ToValue(vInt,vDouble));
			ASSERT_LOG_ERROR(ToolFrame::ToValue(vDouble,vListInt));
			ASSERT_LOG_ERROR(ToolFrame::ToValue(vListInt,vStringDes));

			ASSERT_LOG_ERROR(ToolFrame::ToValue(vStringDes,vEnd));

			VectorInt vIntDes;
			vIntDes.push_back(11);
			vIntDes.push_back(-11);
			vIntDes.push_back(0);
			vIntDes.push_back(3);
			vIntDes.push_back(-3);
			vIntDes.push_back(9);
			vIntDes.push_back(-9);
			vIntDes.push_back(17);
			vIntDes.push_back(-17);
			vIntDes.push_back(-18);

			ASSERT_LOG_ERROR(ToolFrame::IsEqual(vIntDes,vEnd));
			ASSERT_LOG_ERROR(ToolFrame::ToValue(vEnd,vSetInt));
			ASSERT_LOG_ERROR(ToolFrame::IsEqual(vSetInt,vIntDes));
		}
		{
			VectorInt vInt;
			vInt.push_back(11);
			vInt.push_back(-11);
			vInt.push_back(0);
			vInt.push_back(3);
			vInt.push_back(-3);
			vInt.push_back(9);
			vInt.push_back(-9);
			vInt.push_back(17);
			vInt.push_back(-17);
			vInt.push_back(-17);

			VectorString vString;
			ASSERT_LOG_ERROR(ToolFrame::ToValue(vInt,vString));

			VectorString vStringDes;
			vStringDes.push_back("11");
			vStringDes.push_back("-11");
			vStringDes.push_back("0");
			vStringDes.push_back("3");
			vStringDes.push_back("-3");
			vStringDes.push_back("9");
			vStringDes.push_back("-9");
			vStringDes.push_back("17");
			vStringDes.push_back("-17");
			vStringDes.push_back("-17");

			ASSERT_LOG_ERROR(ToolFrame::IsEqual(vString,vStringDes));
		}
	}

	return true;
}
