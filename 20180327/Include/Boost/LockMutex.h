#pragma once

#include <boost/thread.hpp>
#include <boost/thread/recursive_mutex.hpp>

#include <boost/smart_ptr/detail/spinlock.hpp>

//�߳����
//��ת��:ʹ����ѭ����ʵ�ֶ�������,�ǳ�����CPU,���Ҳ��ͷ�ռ��,�ص�����Ӧ�ٶȿ�ӵ����ߵ����ȼ�
//������:��ʹ���ź�����ʵ�ֵ���,�ǳ�����,�����ʵ��ٽ����������߳�ռ�ûὫ�Լ������̶߳��� �� �ȴ��ͷŵ��ź�������

//��ת��
typedef boost::detail::spinlock					CSpinLock;//��ת��

//����Boost������ ��д�� ������� ��
//////////////////////////////////////////////////////////////////////////
//�ݹ黥����
//�ڵ�ǰ�����ŵ��ý������Զ�����,ͬһ���߳̿��Զ������
class CMutexRecursive
{
public:
	virtual bool Lock();				//ǿ������(����������ȴ�)
	virtual bool TryLock();				//��������(�����Ƿ����ɹ�)
	virtual bool UnLock();				//�ͷŴ���
public:
	CMutexRecursive();
	virtual ~CMutexRecursive();
private:
	boost::recursive_mutex _mutex;
};

//////////////////////////////////////////////////////////////////////////
//�ݹ���
class CLockScoped
{
public:
	virtual bool UnLock();		//�ͷŴ���
	virtual bool Lock();		//ǿ������(����������ȴ�)
	virtual bool TryLock();		//��������(�����Ƿ����ɹ�)
	virtual bool IsLocked()const;//�Ƿ������ɹ�
public:
	CLockScoped(CMutexRecursive& mutex,bool bTry = false);//����(��bTryΪfalse �� �������ɹ� ʱ��ȴ�����Ϊ true ����Ҫ�߼����ж� IsLocked() �Ƿ������ɹ� �������� )
	virtual ~CLockScoped();
private:
	bool _bLocked;
	CMutexRecursive& _mutex;
};

//////////////////////////////////////////////////////////////////////////
//��д������
//�ڵ�ǰ�����ŵ��ý������Զ�����,���� ������,��д����,дд���⡣ͬһ�̲߳��ܶ������
class CMutexReadWrite
{
public:
	virtual bool Lock();				//ǿ����д��(����������ȴ�)
	virtual bool TryLock();				//������д��(�����Ƿ����ɹ�)
	virtual bool UnLock();				//�ͷŴ�д��

	virtual bool LockShared();			//ǿ���϶���(����������ȴ�)
	virtual bool TryLockShared();		//�����϶���(�����Ƿ����ɹ�)
	virtual bool UnLockShared();		//�ͷŴ˶���
public:
	CMutexReadWrite();
	virtual ~CMutexReadWrite();
private:
	boost::shared_mutex _mutex;
};

//////////////////////////////////////////////////////////////////////////
//��д������ - ����
class CLockRead
{
public:
	virtual bool UnLock();		//�ͷŴ���
	virtual bool Lock();		//ǿ������(����������ȴ�)
	virtual bool TryLock();		//��������(�����Ƿ����ɹ�)
	virtual bool IsLocked()const;//�Ƿ������ɹ�
public:
	CLockRead(CMutexReadWrite& mutex, bool bTry = false);//����(��bTryΪfalse �� �������ɹ� ʱ��ȴ�����Ϊ true ����Ҫ�߼����ж� IsLocked() �Ƿ������ɹ� �������� )
	virtual ~CLockRead();
private:
	bool _bLocked;
	CMutexReadWrite& _mutex;
};

//////////////////////////////////////////////////////////////////////////
//��д������ - д��
class CLockWrite
{
public:
	virtual bool UnLock();		//�ͷŴ���
	virtual bool Lock();		//ǿ������(����������ȴ�)
	virtual bool TryLock();		//��������(�����Ƿ����ɹ�)
	virtual bool IsLocked()const;//�Ƿ������ɹ�
public:
	CLockWrite(CMutexReadWrite& mutex, bool bTry = false);//����(��bTryΪfalse �� �������ɹ� ʱ��ȴ�����Ϊ true ����Ҫ�߼����ж� IsLocked() �Ƿ������ɹ� �������� )
	virtual ~CLockWrite();
private:
	bool _bLocked;
	CMutexReadWrite& _mutex;
};
