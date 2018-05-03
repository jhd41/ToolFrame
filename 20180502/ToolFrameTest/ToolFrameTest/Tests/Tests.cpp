////#define _CRT_SECURE_NO_WARNINGS //Modify By SongJ

#include "Macro.h"
#include "MLoger.h"
#include "ToolFrame.h"
#include "TestToValue.h"
#include "TestEval.h"
#include "TestLua.h"
#include "TestXml.h"
#include "TArray.h"
#include "ZipFile.h"
#include "StreamFile.h"
#include "TestHttp.h"
#include "MSystem.h"

// SjFrameTest.cpp : �������̨Ӧ�ó������ڵ㡣
//
using namespace ToolFrame;

bool TestTypeSize(){
	ASSERT_LOG_ERROR(sizeof(INT8)	== 1);
	ASSERT_LOG_ERROR(sizeof(INT16)	== 2);
	ASSERT_LOG_ERROR(sizeof(INT32)	== 4);
	ASSERT_LOG_ERROR(sizeof(INT64)	== 8);
	ASSERT_LOG_ERROR(sizeof(UINT8)	== 1);
	ASSERT_LOG_ERROR(sizeof(UINT16)	== 2);
	ASSERT_LOG_ERROR(sizeof(UINT32)	== 4);
	ASSERT_LOG_ERROR(sizeof(UINT64)	== 8);
	ASSERT_LOG_ERROR(sizeof(FLOAT32)== 4);
	ASSERT_LOG_ERROR(sizeof(FLOAT64)== 8);

	ASSERT_LOG_ERROR(sizeof(int8)	== 1);
	ASSERT_LOG_ERROR(sizeof(int16)	== 2);
	ASSERT_LOG_ERROR(sizeof(int32)	== 4);
	ASSERT_LOG_ERROR(sizeof(uint8)	== 1);
	ASSERT_LOG_ERROR(sizeof(uint16) == 2);
	ASSERT_LOG_ERROR(sizeof(uint32) == 4);

	ASSERT_LOG_ERROR(sizeof(Int8)	== 1);
	ASSERT_LOG_ERROR(sizeof(Int16)	== 2);
	ASSERT_LOG_ERROR(sizeof(Int32)	== 4);
	ASSERT_LOG_ERROR(sizeof(Int64)	== 8);
	ASSERT_LOG_ERROR(sizeof(Uint8)	== 1);
	ASSERT_LOG_ERROR(sizeof(Uint16)	== 2);
	ASSERT_LOG_ERROR(sizeof(Uint32)	== 4);
	ASSERT_LOG_ERROR(sizeof(UINT64)	== 8);
	ASSERT_LOG_ERROR(sizeof(Float32)== 4);
	ASSERT_LOG_ERROR(sizeof(Float64)== 8);

	return true;
}

bool TestFileStream() {
	//�������
	const	INT8	nInInt8 = -1;
	const	INT16	nInInt16 = -2;
	const	INT32	nInInt32 = -3;
	const	INT64	nInInt64 = -4;
	const	UINT8	uInUint8 = 1;
	const	UINT16	uInUint16 = 2;
	const	UINT32	uInUint32 = 3;
	const	UINT64	uInUint64 = 4;
	VectorInt vInVectorInt;
	vInVectorInt.push_back(-1);
	vInVectorInt.push_back(-3);
	vInVectorInt.push_back(-5);
	vInVectorInt.push_back(0);
	vInVectorInt.push_back(1);
	vInVectorInt.push_back(2);
	SetInt	vInSetInt;
	vInSetInt.insert(-1);
	vInSetInt.insert(-4);
	vInSetInt.insert(-3);
	vInSetInt.insert(-5);

	const	std::string sInName = "SongJ";

	VectorString vInString;
	vInString.push_back("SongJ");
	vInString.push_back("Test����");

	SetString vInSetString;
	vInSetString.insert("SongJ");
	vInSetString.insert("Test����");
	vInSetString.insert("!#$^&");

	MapIntString vInIntString;
	ToolFrame::Insert(vInIntString, 55, "55���ֲ���");
	ToolFrame::Insert(vInIntString, 66, "66");

	//�����ļ���д
	const std::string sFileNameTest = "TextStreamFile.txt";

	//����ļ�д
	{
		CStreamFile  sFileStream;
		ASSERT_LOG_ERROR( sFileStream.Open(sFileNameTest, CStreamFile::OP_OUT));

		//д��
		 sFileStream << nInInt8 << nInInt16 << nInInt32 << nInInt64 << uInUint8 << uInUint16 << uInUint32 << uInUint64;
		ASSERT_LOG_ERROR( sFileStream.GetLength() == 30);

		 sFileStream << vInVectorInt << vInSetInt << sInName << nInInt8 << vInString;
		ASSERT_LOG_ERROR( sFileStream.GetLength() == 101);

		 sFileStream << vInSetString;
		ASSERT_LOG_ERROR( sFileStream.GetLength() == 127);

		 sFileStream << vInIntString;
		ASSERT_LOG_ERROR( sFileStream.GetLength() == 153);
	}

	//��ȡ����
	INT8			nOutInt8 = 0;
	INT16			nOutInt16 = 0;
	INT32			nOutInt32 = 0;
	INT64			nOutInt64 = 0;
	UINT8			uOutUint8 = 0;
	UINT16			uOutUint16 = 0;
	UINT32			uOutUint32 = 0;
	UINT64			uOutUint64 = 0;
	VectorInt		vOutVectorInt;
	SetInt			vOutSetInt;
	std::string		sOutName;
	VectorString	vOutString;
	SetString		vOutSetString;
	MapIntString	vOutIntString;

	//����ļ���
	{
		CStreamFile  sFileStream;
		ASSERT_LOG_ERROR( sFileStream.Open(sFileNameTest, CStreamFile::OP_IN));
		 sFileStream >> nOutInt8 >> nOutInt16 >> nOutInt32 >> nOutInt64 >> uOutUint8 >> uOutUint16 >> uOutUint32 >> uOutUint64 >> vOutVectorInt >> vOutSetInt >> sOutName >> nOutInt8 >> vOutString;
		 sFileStream >> vOutSetString;
		 sFileStream >> vOutIntString;

		ASSERT_LOG_ERROR( sFileStream.IsEmpty());
		ASSERT_LOG_ERROR( sFileStream.GetLength() == 0);

		ASSERT_LOG_ERROR(! sFileStream.IsError());
	}

	//У��
	ASSERT_LOG_ERROR(nInInt8 == nOutInt8);
	ASSERT_LOG_ERROR(nInInt16 == nOutInt16);
	ASSERT_LOG_ERROR(nInInt32 == nOutInt32);
	ASSERT_LOG_ERROR(nInInt64 == nOutInt64);

	ASSERT_LOG_ERROR(uInUint8 == uOutUint8);
	ASSERT_LOG_ERROR(uInUint16 == uOutUint16);
	ASSERT_LOG_ERROR(uInUint32 == uOutUint32);
	ASSERT_LOG_ERROR(uInUint64 == uOutUint64);

	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInVectorInt, vOutVectorInt));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInSetInt, vOutSetInt));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(sInName, sOutName));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInString, vOutString));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInSetString, vOutSetString));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInIntString, vOutIntString));
	return true;
}

template<typename TStream>
bool TestBinaryStream(TStream& binStream){
	//�������
	const	INT8	nInInt8 = -1;
	const	INT16	nInInt16 = -2;
	const	INT32	nInInt32 = -3;
	const	INT64	nInInt64 = -4;
	const	UINT8	uInUint8 = 1;
	const	UINT16	uInUint16 = 2;
	const	UINT32	uInUint32 = 3;
	const	UINT64	uInUint64 = 4;
	VectorInt vInVectorInt;
	vInVectorInt.push_back(-1);
	vInVectorInt.push_back(-3);
	vInVectorInt.push_back(-5);
	vInVectorInt.push_back(0);
	vInVectorInt.push_back(1);
	vInVectorInt.push_back(2);
	SetInt	vInSetInt;
	vInSetInt.insert(-1);
	vInSetInt.insert(-4);
	vInSetInt.insert(-3);
	vInSetInt.insert(-5);

	const	std::string sInName ="SongJ";

	VectorString vInString;
	vInString.push_back("SongJ");
	vInString.push_back("Test����");

	SetString vInSetString;
	vInSetString.insert("SongJ");
	vInSetString.insert("Test����");
	vInSetString.insert("!#$^&");

	MapIntString vInIntString;
	ToolFrame::Insert(vInIntString,55,"55���ֲ���");
	ToolFrame::Insert(vInIntString,66,"66");

	uint uInInsertBegin0 = 85;
	uint uInInsertBegin1 = 56;
	uint uInInsertBegin2 = 33;

	//д��
	ASSERT_LOG_ERROR(binStream.Insert(0, &uInInsertBegin0, sizeof(uInInsertBegin0)));
	ASSERT_LOG_ERROR(binStream.Insert(0, &uInInsertBegin1, sizeof(uInInsertBegin1)));

	binStream << nInInt8 << nInInt16 << nInInt32 << nInInt64 << uInUint8 << uInUint16 << uInUint32 << uInUint64;
	ASSERT_LOG_ERROR(binStream.GetLength() == 38);

	binStream << vInVectorInt << vInSetInt << sInName << nInInt8 << vInString;
	ASSERT_LOG_ERROR(binStream.GetLength() == 109);

	ASSERT_LOG_ERROR(binStream.Insert(0, &uInInsertBegin2, sizeof(uInInsertBegin2)));

 	binStream << vInSetString;
	ASSERT_LOG_ERROR(binStream.GetLength() == 139);

 	binStream << vInIntString;
	ASSERT_LOG_ERROR(binStream.GetLength() == 165);

	//��⿽��
	TStream binStreamCopy = binStream;	//��������
	binStreamCopy = binStreamCopy;		//���ҿ���
	binStreamCopy = binStream;

	ASSERT_LOG_ERROR(!binStream.IsError());
	ASSERT_LOG_ERROR(!binStreamCopy.IsError());
	ASSERT_LOG_ERROR(binStreamCopy.GetLength() == binStream.GetLength());
	ASSERT_LOG_ERROR(binStreamCopy.IsEmpty() == binStream.IsEmpty());

	//�����ļ���д
	const std::string sFileNameTest = "TextStreamBin.txt";
	
	//����ļ�д
	{
		TArrayNew<char> arBin(binStreamCopy.GetLength(),true);
		ASSERT_LOG_ERROR(binStreamCopy.Read(arBin.GetPtr(), arBin.GetLength()));

		if (!ToolFrame::SaveFile(sFileNameTest,arBin.GetPtr(),arBin.GetLength(),DIR_TYPE_WRITEABLE))return false;

		//���������
		binStreamCopy.Clear();
		ASSERT_LOG_ERROR(binStreamCopy.IsEmpty());
		ASSERT_LOG_ERROR(binStreamCopy.GetLength() == 0);
		ASSERT_LOG_ERROR(!binStreamCopy.IsError());
		ASSERT_LOG_ERROR(binStreamCopy.GetSize() == 0);
	}

	//����ļ���
	{
		size_t uSizeFile = ToolFrame::GetFileLength(sFileNameTest,DIR_TYPE_WRITEABLE);
		ASSERT_LOG_ERROR(uSizeFile > 0);

		TArrayNew<char> arBin(uSizeFile,true);
		
		ASSERT_LOG_ERROR(ToolFrame::LoadFile(sFileNameTest,arBin.GetPtr(),arBin.GetLength(),DIR_TYPE_WRITEABLE));

		ASSERT_LOG_ERROR(binStreamCopy.Write(arBin.GetPtr(), arBin.GetLength()));

		ASSERT_LOG_ERROR(!binStream.IsError());
		ASSERT_LOG_ERROR(!binStreamCopy.IsError());
		ASSERT_LOG_ERROR(binStreamCopy.GetLength() == binStream.GetLength());
		ASSERT_LOG_ERROR(binStreamCopy.IsEmpty() == binStream.IsEmpty());
	}

	//��ȡ
	//��ȡ����
	INT8			nOutInt8 = 0;
	INT16			nOutInt16 = 0;
	INT32			nOutInt32 = 0;
	INT64			nOutInt64 = 0;
	UINT8			uOutUint8 = 0;
	UINT16			uOutUint16 = 0;
	UINT32			uOutUint32 = 0;
	UINT64			uOutUint64 = 0;
	VectorInt		vOutVectorInt;
	SetInt			vOutSetInt;
	std::string		sOutName;
	VectorString	vOutString;
	SetString		vOutSetString;
	MapIntString	vOutIntString;
	uint			uOutInsertBegin0;
	uint			uOutInsertBegin1;
	uint			uOutInsertBegin2;

	binStreamCopy>>uOutInsertBegin2 >> uOutInsertBegin1>>uOutInsertBegin0;
 	binStreamCopy>>nOutInt8>>nOutInt16>>nOutInt32>>nOutInt64>>uOutUint8>>uOutUint16>>uOutUint32>>uOutUint64>>vOutVectorInt>>vOutSetInt>>sOutName>>nOutInt8>>vOutString;
 	binStreamCopy>>vOutSetString;
 	binStreamCopy>>vOutIntString;
	

	ASSERT_LOG_ERROR(binStreamCopy.IsEmpty());
	ASSERT_LOG_ERROR(binStreamCopy.GetLength()==0);

	ASSERT_LOG_ERROR(!binStreamCopy.IsError());

	//У��
	ASSERT_LOG_ERROR(nInInt8 == nOutInt8);
	ASSERT_LOG_ERROR(nInInt16 == nOutInt16);
	ASSERT_LOG_ERROR(nInInt32 == nOutInt32);
	ASSERT_LOG_ERROR(nInInt64 == nOutInt64);

	ASSERT_LOG_ERROR(uInUint8 == uOutUint8);
	ASSERT_LOG_ERROR(uInUint16 == uOutUint16);
	ASSERT_LOG_ERROR(uInUint32 == uOutUint32);
	ASSERT_LOG_ERROR(uInUint64 == uOutUint64);

	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInVectorInt,vOutVectorInt));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInSetInt,vOutSetInt));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(sInName,sOutName));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInString,vOutString));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInSetString,vOutSetString));
	ASSERT_LOG_ERROR(ToolFrame::IsEqual(vInIntString,vOutIntString));

	ASSERT_LOG_ERROR(uInInsertBegin0 == uOutInsertBegin0);
	ASSERT_LOG_ERROR(uInInsertBegin1 == uOutInsertBegin1);
	ASSERT_LOG_ERROR(uInInsertBegin2 == uOutInsertBegin2);

	//����ڴ��Ƿ��ͷ�
	ASSERT_LOG_ERROR(binStreamCopy.IsEmpty());
	ASSERT_LOG_ERROR(binStreamCopy.GetLength()==0);

	ASSERT_LOG_ERROR(!binStreamCopy.IsError());

	//���� ToStreamBuffer
	CStreamBinary* pBinaryCopy = dynamic_cast<CStreamBinary*>(&binStreamCopy);
	CStreamBinary* pBinStream = dynamic_cast<CStreamBinary*>(&binStream);
	if (pBinaryCopy && pBinStream)
	{
		pBinaryCopy->SetReadCursorBegin();
		pBinaryCopy->SetWriteCursorEnd();
		StreamBufferPtr pStreamBuffer1 = pBinaryCopy->ToStreamBuffer();
		ASSERT_LOG_ERROR(pStreamBuffer1);

		pBinStream->SetReadCursorBegin();
		pBinStream->SetWriteCursorEnd();
		StreamBufferPtr pStreamBuffer2 = pBinStream->ToStreamBuffer();
		ASSERT_LOG_ERROR(pStreamBuffer2);

		ASSERT_LOG_ERROR(pStreamBuffer1->IsEqual(*pStreamBuffer2));
	}
	return true;
}

bool TestStringStream(){
	std::stringstream sStream1;
	sStream1<<"11";
	std::stringstream sStream2;
	sStream2<<"22";
	sStream1<<sStream2;
	std::string s1 = sStream1.str();
	ASSERT_LOG_ERROR(s1 == "1122");

	std::stringstream sStream3;
	sStream1>>sStream3;
	std::string s2 = sStream3.str();
	ASSERT_LOG_ERROR(s2 == "1122");
	return true;
}

bool TestBaseFunction(){
	ListInt vTest;
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,1));
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,2));
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,3));
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,4));
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,5));
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,6));
	ASSERT_LOG_ERROR(ToolFrame::Insert(vTest,7));

	ASSERT_LOG_ERROR(ToolFrame::GetValueByIndex(vTest,0) == 1);
	ASSERT_LOG_ERROR(ToolFrame::GetValueByIndex(vTest,1) == 2);
	ASSERT_LOG_ERROR(ToolFrame::GetValueByIndex(vTest,2) == 3);
	ASSERT_LOG_ERROR(ToolFrame::GetValueByIndex(vTest,6) == 7);

	return true;
}

bool TestToValue(){
	CTestToValue toValue;
	return toValue.Test();
}

//  bool TestZipUtils(){
//  
//  	static const  std::string sSrc = "�����μ�,�������й�,�ܹ���дToolFrame�Ҿ��ú����ҡ�ϣ���ܹ��뿴�����ĵ��˳�Ϊ���ѡ�";
//  	std::string sResult;
//  
//  	TArrayNew<char> buffZip(1024,true);
//  	//�����ѹ����
//  	{
//  		HZIP hZip = CreateZip(buffZip.GetPtr(),buffZip.GetLength(),"");
//  		ZipAdd(hZip,"SongJ",(void*)sSrc.c_str(),sSrc.length()+1);
//  		CloseZip(hZip);
//  	}
//  	
//  	//��ȡ��ѹѹ����
//  	{
//  		TArrayNew<char> buffUnZip(1024,true);
//  		HZIP hZip = OpenZip(buffZip.GetPtr(),buffZip.GetLength(),"");
//  		UnzipItem(hZip,0,(void*)buffUnZip.GetPtr(),buffUnZip.GetLength());
//  		CloseZip(hZip);
//  
//  		sResult = buffUnZip.GetPtr();
//  	}
//  
//  	ASSERT_LOG_ERROR(sSrc == sResult);
//  
//  
//  	return true;
//  }



bool TestZLib(){
	//��ѹ�����ļ�
	{
		CZipFile zipReader(ToolFrame::GetWorkingDir() + "test.zip","");
		if (!zipReader.OpenZipFile("test.txt"))return false;

		TArrayNew<char> buffer(zipReader.GetCurFileUncompressedSize()+1,true);
		if (!zipReader.LoadData(buffer.GetPtr(),buffer.GetLength()))return false;

		std::string s=buffer.GetPtr();
		ToolFrame::OutPut(s);
	}

	//��ѹ�����ﺬ��Ŀ¼���ļ�
	{
		CZipFile zipReader(ToolFrame::GetWorkingDir() + "test.zip","");
		if (!zipReader.OpenZipFile("Test/test.txt"))return false;

		TArrayNew<char> buffer(zipReader.GetCurFileUncompressedSize()+1,true);
		if (!zipReader.LoadData(buffer.GetPtr(),buffer.GetLength()))return false;

		std::string s=buffer.GetPtr();
		ToolFrame::OutPut(s);
	}

	//�򿪲����ڵĵ�ַ
	{
		CZipFile zipReader(ToolFrame::GetWorkingDir() + "55555555/test.zip","");
		if (zipReader.OpenZipFile("Test/test.txt"))return false;//������� �Ų�����
	}

	return true;


	//  	//ԭʼ���� 
	//  	unsigned char pchSrc[] = "xxx...." ; 
	//  	unsigned long nSrcLen = sizeof(pchSrc); 
	//  
	//  	//ѹ��֮������� 
	//  	unsigned char achComp[1024]; 
	//  	unsigned long nCompLen = 1024 ; 
	//  
	//  	//��ѹ��֮������� 
	//  	unsigned char achUncomp[1024]; 
	//  	unsigned long nUncompLen = 1024 ; 
	//  
	//  	//ѹ�� 
	//  	compress(achComp,&nCompLen, pchSrc,nSrcLen); 
	//  
	//  	//��ѹ�� 
	//  	uncompress(achUncomp,&nUncompLen, achComp,nCompLen); 
	//  
	//  	//��ʾԭʼ������Ϣ 
	//  	printf("ԭʼ����(%d):\n%s\n\n", nSrcLen,pchSrc); 
	//  
	//  	//��ʾѹ��֮������� 
	//  	printf("ѹ������(%d):\n%s\n\n", nCompLen,achComp); 
	//  
	//  	//��ʾ��ѹ��֮������� 
	//  	printf("��ѹ����(%d):\n%s\n\n", nUncompLen,achUncomp);



	//  
	return true;
}
bool TestBinaryStreamBinary(){
	{
		CStreamBinary bin;
		ASSERT_LOG_ERROR(TestBinaryStream(bin));
	}
	{
		CStreamBinary bin;
		bin.SetAlloc(CStreamBinary::ALLOC_WRITE_SIZE);
		ASSERT_LOG_ERROR(TestBinaryStream(bin));
	}
	{
		CStreamBinary bin;
		bin.SetAlloc(CStreamBinary::ALLOC_WRITE_POWER_SIZE);
		ASSERT_LOG_ERROR(TestBinaryStream(bin));
	}
	{
		CStreamBinary bin;
		bin.SetAlloc(CStreamBinary::ALLOC_BUFFER_POWER_SIZE);
		ASSERT_LOG_ERROR(TestBinaryStream(bin));
	}
	{
		CStreamBinary bin;
		bin.SetAlloc(CStreamBinary::ALLOC_BLOCK_SIZE);
		ASSERT_LOG_ERROR(TestBinaryStream(bin));
	}
	return true;
}
bool TestBinaryStreamBufferMalloc(){
	CStreamBufferMalloc bin(1024);
	return TestBinaryStream(bin);
}

//���Ա�׼Std����(��Ҫ���㷨)
bool TestToolStd(){
	ASSERT_LOG_ERROR(ToolFrame::IsInClosedInterval(ToolFrame::RandProbability(340,100),3,4));
	return true;
}

bool TestMoney()
{
	uint32 u1 = ToolFrame::StringToMoney("100");
	uint32 u2 = ToolFrame::StringToMoney("100.");
	uint32 u3 = ToolFrame::StringToMoney("100.0");
	uint32 u4 = ToolFrame::StringToMoney("100.111");
	uint32 u5 = ToolFrame::StringToMoney("0.0");
	uint32 u6 = ToolFrame::StringToMoney(".01");
	uint32 u7 = ToolFrame::StringToMoney(".100");
	uint32 u8 = ToolFrame::StringToMoney("1,100");
	uint32 u9 = ToolFrame::StringToMoney("1 100");
	uint32 u10 = ToolFrame::StringToMoney("1,100.00");
	uint32 u11 = ToolFrame::StringToMoney("100s111");
	return true;
};

bool TestReplaceString(){
	MapStringString vMap;
	if (!ToolFrame::Insert(vMap,"111","222"))return false;//��ͨ�滻
	if (!ToolFrame::Insert(vMap,"222","333"))return false;//���������滻
	if (!ToolFrame::Insert(vMap,"��","��"))return false;//�����滻
	if (!ToolFrame::Insert(vMap,"��","��"))return false;//��Ч
	if (!ToolFrame::Insert(vMap,"112","222"))return false;//˳����Ч

	const std::string sSrc = "���,���� �μ�,������ ���ݡ�У������:111222";
	const std::string sDes = "���,���� �μ�,������ ���ݡ�У������:222333";
	
	std::string s = sSrc;
	if ( -1 == ToolFrame::Replace(s,vMap))return false;

	return sDes == s;
}

bool TestTimeToString(){
	time_t t = 1375673120;
	std::string s = ToolFrame::TimeToString(t,"[YYYY-MM-DD hh:mm:ss]����ʱ��r23rny7238ern8?!@#$%^&*()");
	const std::string sDes = "[2013-08-05 11:25:20]����ʱ��r23rny7238ern8?!@#$%^&*()";
	return sDes == s;
}

bool TestTrimPath(const std::string& sSrc,const std::string& sDes){
	return ToolFrame::TrimPath(sSrc) == sDes;
}
bool TestTrimPath(){
	if (!TestTrimPath("/data/data","/data/data"))return false;
	if (!TestTrimPath("/data/data/../","/data/"))return false;
	if (!TestTrimPath("./\\Client/../",""))return false;
	if (!TestTrimPath("",""))return false;
	if (!TestTrimPath("./\\Client/../../../","../../"))return false;
	if (!TestTrimPath("./\\Client/../aap.k","aap.k"))return false;
	if (!TestTrimPath("./\\Client/../../../aap","../../aap"))return false;
	if (!TestTrimPath("./\\Client/../../../aap/","../../aap/"))return false;
	if (!TestTrimPath("aap.k","aap.k"))return false;
	if (!TestTrimPath("aap/","aap/"))return false;
	if (!TestTrimPath("aap\\","aap/"))return false;

	return true;
}

bool TestSaveLoad(const std::string& sFileName){
	const std::string sContent = "Test";
	if (!ToolFrame::SaveFile(sFileName,sContent,DIR_TYPE_WRITEABLE))return false;

	const std::string sLoad = ToolFrame::LoadFile(sFileName,DIR_TYPE_WRITEABLE);

	return sLoad == sContent;
}

bool TestFile(){
	return TestSaveLoad("TestFile.txt");
}

bool TestDir(){
	if (!ToolFrame::MakeDir("TestDir/Hello/Abc"))return false;

	if (!TestSaveLoad("TestDir/Hello/Abc/kkk.txt"))return false;
	if (!TestSaveLoad("TestDir/Hello/kkk.txt"))return false;

	if (!ToolFrame::CopyDir(ToolFrame::GetWriteableDir() + "TestDir/Hello",ToolFrame::GetWriteableDir() + "TestDir/Copy"))return false;
	if (!ToolFrame::IsFileExist(ToolFrame::GetWriteableDir() + "TestDir/Copy/Abc/kkk.txt"))return false;
	
	if (!ToolFrame::RemoveDir("TestDir"))return false;

	return !ToolFrame::IsFileExist("TestDir/Hello/Abc/kkk.txt",DIR_TYPE_WRITEABLE);
}

bool TestRenameClass(){
	std::string s1;
	std::string s2(s1);
	String255 s = "11";
	String255 ss(s2);
	String255 sss(s);
	return true;
}

bool TestID() {
	for (int nIndex =0 ;nIndex<3;++nIndex)
	{
		std::string s = ToolFrame::GenerateID();
		int a = 0;
		++a;
	}
	
		
	return true;
}

bool Tests()
{
	MSystem::Singleton().Init();

	MLoger::Singleton().Init();

	ASSERT_LOG_ERROR(TestFile());
	ASSERT_LOG_ERROR(TestDir());
	ASSERT_LOG_ERROR(TestToolStd());
	ASSERT_LOG_ERROR(TestMoney());
	ASSERT_LOG_ERROR(TestReplaceString());
	ASSERT_LOG_ERROR(TestTimeToString());

	ASSERT_LOG_ERROR(TestTrimPath());
	ASSERT_LOG_ERROR(TestBaseFunction());
	ASSERT_LOG_ERROR(TestTypeSize());
	ASSERT_LOG_ERROR(TestToValue());
	
	ASSERT_LOG_ERROR(TestBinaryStreamBinary());
	ASSERT_LOG_ERROR(TestBinaryStreamBufferMalloc());
	ASSERT_LOG_ERROR(TestFileStream());
	
	ASSERT_LOG_ERROR(TestStringStream());
	//ASSERT_LOG_ERROR(TestEvalExpression());
	//ASSERT_LOG_ERROR(TestEvalScript());
	ASSERT_LOG_ERROR(TestLua());

	ASSERT_LOG_ERROR(TestLua());
	ASSERT_LOG_ERROR(TestLuaDouble());
	ASSERT_LOG_ERROR(TestXml());
	//ASSERT_LOG_ERROR(TestZLib());
	ASSERT_LOG_ERROR(TestHttp());

	ASSERT_LOG_ERROR(TestRenameClass());

	ASSERT_LOG_ERROR(TestID());
	return true ;
}

