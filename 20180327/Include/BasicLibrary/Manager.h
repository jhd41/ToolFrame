#if !defined(_MANAGER_H)
#define _MANAGER_H

#include "Macro.h"

//�����Ѿ�����
//������������ȷ�ͷš���д�鷳����ʹ�� ST_INTANCE,����� ST_INTANCE ����һ����λ�Ĺ��ܡ�

// template<class T>
// class Manager {
// 	//friend class  Manager<T> ;//����Ϊ��Ԫ�� ����Ϊ�ڹ����ڲ������ʵ����ʱ������ �����˽�л��߱������ԵĹ��캯��
// private:
// 	static T* _pMgr;
// protected://�����ڹ��������ʱҪ���� ����Ĺ��캯������������������д�� ������
// 	Manager(){};
// 	virtual ~Manager(){
// 		Delete();
// 	};
// public:
// 	static T* Singleton();
// 	static void Delete();//ɾ�� ���� ɾ��Ψһ��ʵ�� Ҳ�������� ���õ���
// };
// 
// template<class T>
// T* Manager<T>::_pMgr=nullptr;
// 
// template<class T>
// T* Manager<T>::Singleton(){
// 	if(!_pMgr)
// 		_pMgr=new T();//�ڴ˵��� ʵ���ı��� ���� ˽�еĳ�Ա �����Ҫ�������� ��Ԫ��
// 
// 	return _pMgr;
// }
// 
// template<class T>
// void Manager<T>::Delete(){
// 	if (_pMgr)
// 	{
// 		delete _pMgr;
// 		_pMgr= nullptr;
// 	}
// }

#endif  //_MANAGER_H

