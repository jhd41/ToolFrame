#pragma once

//前言:
//欢迎使用 由 云都工作室 编写ToolFrame框架库。
//本框架库 可以运行在 ios/android/windows/linux 4个平台上面。其余平台暂时未做测试与兼容。
//云都工作室 保留所有权力,未经 云都工作室 授权,不得 复制/修改/使用 本工具 库

#include "MacroConfig.h"	//预编译配置
#include "MacroAdapter.h"	//兼容匹配

//使得MACRO_LIB_TINYXML支持STL
// #ifdef MACRO_LIB_TINYXML
// #define TIXML_USE_STL
// #endif

//适配Linux
#if MACRO_TARGET_OS == MACRO_OS_LINUX
	typedef int				BOOL;
	#include "MacroDefineStd.h"
#endif // OS_LINUX

//适配IOS
#if MACRO_TARGET_OS == MACRO_OS_IOS
	#include <objc/objc.h>
	#include "MacroDefineStd.h"
#endif //IOS

//适配Android
#if MACRO_TARGET_OS == MACRO_OS_ANDROID
	typedef bool			BOOL;
	#include "MacroDefineStd.h"
#endif //Android

//适配Windows
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	//#define _USE_32BIT_TIME_T
	#ifndef _WIN32_WINDOWS
		#define _WIN32_WINDOWS 0x0410
	#endif

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0500
	#endif

	#ifndef _WINDOWS
		#define _WINDOWS
	#endif

	typedef int				BOOL;
	#include "MacroDefineStd.h"
#endif //Windows

//注意事项:
//VC项目:	需要 1)打开"使用库依赖项输入" 选项(在连接器中) 2)警告视为错误 3)使用MT线程
//XCODE项目:需要 1)LLVM GCC 4.2	2)Symbols Hidden by Default = Yes 3)Other Linker Flag 中填写:-ObjC -all_load

//编写规范:
//首先需要在 MacroUserConfig.h里填写使用的平台,库 不填写则默认匹配。

//命名基本规则:

//变量前缀的规则
//布尔类型			b -> bool
//有符号数值类型	n -> char,int,long,long long(__int64)
//无符号数值类型	u -> unsigned char,unsigned int,unsigned long,unsigned long long (unsigned __int64),size_t,time_t
//字符串类型		s -> std::string
//C字符串类型		sz-> char[]
//容器类型			v -> set,vector,map,mult_map,list,stack
//句柄,处理器		h -> 一般指代处理器指针
//指针				p -> 指针类型
//函数指针			fn -> 函数指针类型
//枚举类型			e -> enum
//控件类型			c -> MFC控件
//模板类型			t -> template<typename T>
//管理器类型		m -> 管理器
//数组类型			a -> 数组

//类前缀的规则
//共用体类型	U -> union
//结构类型		X -> struct	//一般不带有函数,纯粹的数据保存
//类类型		C -> class	//一般指代带有(函数)
//管理器类型	M -> class	//一般指代是管理器,意味着很可能是单件
//处理器类型	H -> class	//一般指代的是处理器，里面一般都是虚函数,也有可能存在纯虚函数
//接口类型		I -> class	//一般指代的是某些接口
//模板类型		T -> class	//一般指代模板类
//API类型		Api-> class	//一般指给外部访问使用的Api函数集合

//权限
//私有变量 加前导下划线 例:_sAccount;(不同单词之间，单词首字母大写)
//临时本地变量不加任何修饰

//变量名全部大写 代表 常量(不同单词之间用下划线'_'隔开)
//函数名全部大写 代表 宏函数(不同单词之间用下划线'_'隔开)
//定义函数时,被操作形参放在第一个(即 通过形参返回的变量),操作所需参数以const修饰 放在随后。
//函数体的以效率最高为原则顺序编写，如果遇到多线程函数 第一步 先对 传入参数做校验，然后 再上锁 判成员变量

//类的声明按照以下顺序进行
//classs CClass{
//friend class 声明
//private:
//内部结构
//public:
//内部类型定义 typedef
//public:
//外部接口函数
//public:
//父类虚函数回调
//private:
//内部成员函数
//public:
//字段
//public:
//构造函数 析构函数
//private:
//成员变量
//};

//函数命名规则(按 使用频率 排序):
//Is		是否 返回布尔值	通常是常函数
//Find		查找 返回指针,返回空指针为找不到
//Get		获取 返回内容，通常和Set成对出现,这通常是一定能获取到的，而Find可能是查找不到。
//Set		设置 设置某值为何值
//Create	创建 该函数通常内部new一块新的内存出来，可能需要外部管理，通常和Destory配对使用。
//Destory	销毁 该函数通常是销毁传入参数所指示的内存块，调用该函数后，原先的内容不能再使用
//Add		添加 仅仅是向某个容器添加自己的索引值，不申请空间。通常与Remove配对使用
//Remove	移除 仅仅是向某个容器移除自己的索引值，不销毁空间，调用该函数后，传入参数的内容仍然可以继续使用。
//Api		接口 引用 具有 依赖其他库的函数。或者是 开放给 外部使用的接口。也就是说 使用了 这个之后 你将 对这个库 产生依赖。
//CallBack	回调 回调函数
//Debug		调试 程序内部自检调试函数，只在Debug模式下 会被编译 运行。 所以不影响效率
//Cal		计算 真实进行运算推导得到的数值。与Get不同的是Get是直接获取现有变量。Cal会有逻辑运算。
//Try		尝试 返回有效值 或者 Bool值,函数内部 若执行成功 则返回有效值，若失败 则 无效。例如 TryLock，只有Lock成功才返回 true
//Sync		同步 同步函数,函数内部通常都有互斥锁 锁住，因此不可以递归 调用。
//Async		异步 异步函数,函数内部通常也有互斥锁，但是如果上锁失败，则会排队后续才调用。若想仅仅加入执行队列 使用Push关键字
//Push		压入 压入队列，通常都在队尾
//Mode		模式 模式特例化函数,为了 专门存放 因为模式不同 而 不同的 的代码语句。
//Tran		翻译 内部变量到查看的字符串的转化函数。
//Mark		标记 无论内部之前什么值，现在一律为什么值
//Ignore	忽略 一般忽略检查,等等
//Cache		缓存 返回缓存的物体，若不存在，则立刻制作该物体，加入缓存,然后返回 缓存的物体指针。通常和Purge配对使用
//Purge		回收 清理缓存的物体，回收后的物体都不存在，但内部会尽可能保证其缓存的安全性，若能够判断出外部在使用，那么久不回收。
//Clone		克隆 内部会创建一个一模一样的实体进行返回。
//Copy		复制 当前的对象的属性 完全从另一个传入的对象进行复制
//On		当..时 一般用于事件回调，比如当加载时
//Splice	拼接 对象内部元素直接被移动过去，主要是性能考虑 参考list::splice
//Reset		重置 将当前对象重置到某状态
//To		转换 转换为另一个对象类型，通常这是新的对象(不会改变当前的类)
//Pop		弹出 将一个元素从一个容器中移出来
//Read		读取 读取某流 某文件 通常和 Write对应
//Write		写入 写入某流 某文件 通常和 Read对应

//其他规则:
//所有的类的析构 必须为 virtual(不含虚函数的结构体可以不为virtual)
//所有继承的函数 都必须 加 override
//逻辑判断 == 时：常量 写在左边。例如 INVAILD == _nSpellID
//操作符两边添加空格。例如 a += 3;不要写成 a+=3;
//在Create之前,将Create返回值所储存的变量首先判空
//禁止使用goto语句
//禁止使用void返回类型，使用bool替代
//尽可能少使用else,使用return 替代。
//尽可能少使用全局变量,使用单件模式替代。
//尽可能少使用强转,使用与正确合适的类型相匹配

//类对象逻辑含义的命名
//CCard		//游戏实际使用中的类对象
//CCardSync	//继承自CCard的类对象，用于客户端变化同步
//XCard		//卡牌变量数据
//XCardData	//卡牌常量数据
//关系
//在服务器端 以 CCard作为核心使用，会有各种的方法方便服务器修改数据
//CCardSync 继承自CCard的类对象，用于客户端变化同步，利用重载的特性，当核心数据CCard发生变化时，同步协议给客户端。
//服务器要将整个Card数据同步给客户端的过程 是 只发送 XCard(会变化的部分)，不变化的部分，客户端本地从配置表文件中读取(XCardData)

//每个文件(.h,.cpp,.mm)末尾 都需要添加一个换行符 以便Linux编译通过
//编写模板函数 使用到迭代器时 使用typename vector::iterator itr;定义变量(以便Linux编译通过)

//每个代码块尽可能保持相对独立，多用ASSERT_LOG_XXX 来判断。
//遇到只是校验数据合法性,但是又是极其消耗机器性能的 可以使用ASSERT_LOG_DEBUG,平时使用ASSERT_LOG_ERROR
//编写 预编译 命令 时 换行很重要 保持代码结构清晰
//
//思路整理: key:键 value:值 index:索引 示例: vector<value> set<value> map<key,value>
//注记:路径(Path) = 文件夹(Dir) + 文件名(FileName)

//全局使用一个命名空间: namespace ToolFrame.。
//一般来说 只要包含文件头 ToolFrame.h 之后。你就可以使用到所有关于这个命名空间的重载函数了。如果你想重载扩充,必须定义在此空间下。
