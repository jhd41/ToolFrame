#pragma once

template<typename T1,typename T2,typename T3>
class STemplateStruct{
public:
	T1 _t1;
	T2 _t2;
	T3 _t3;
public:
	STemplateStruct(){};
	STemplateStruct(T1 t1,T2 t2,T3 t3){
		_t1 = t1;
		_t2 = t2;
		_t3 = t3;
	}
};

#define  DECLARE_CLASS_3(classname,T1,v1,T2,v2,T3,v3) \
class classname{\
public:\
	T1 _v1;\
	T2 _v2;\
	T3 _v3;\
public:\
	classname(){};\
	classname(T1 v1,T2 v2,T3 v3){\
	_v1 = v1;\
	_v2 = v2;\
	_v3 = v3;\
};


//template<typename T1,typename T2>
//class STemplateStruct{
//public:
//	T1 _t1;
//	T2 _t2;
//public:
//	STemplateStruct(){};
//	STemplateStruct(T1 t1,T2 t2){
//		_t1 = t1;
//		_t2 = t2;
//	}
//};