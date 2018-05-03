#if !defined(_MANAGER_H)
#define _MANAGER_H

#include "Macro.h"

//此类已经作废
//单件不可以正确释放。书写麻烦，请使用 ST_INTANCE,此类比 ST_INTANCE 多了一个复位的功能。

// template<class T>
// class Manager {
// 	//friend class  Manager<T> ;//设置为友元类 是因为在构造内部对象的实例的时候会调用 对象的私有或者保护属性的构造函数
// private:
// 	static T* _pMgr;
// protected://子类在构造和析构时要调用 父类的构造函数和析构函数，所以写成 保护的
// 	Manager(){};
// 	virtual ~Manager(){
// 		Delete();
// 	};
// public:
// 	static T* Singleton();
// 	static void Delete();//删除 用于 删除唯一的实例 也可以用于 重置单件
// };
// 
// template<class T>
// T* Manager<T>::_pMgr=nullptr;
// 
// template<class T>
// T* Manager<T>::Singleton(){
// 	if(!_pMgr)
// 		_pMgr=new T();//在此调用 实例的保护 或者 私有的成员 因此需要事先声明 友元类
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

