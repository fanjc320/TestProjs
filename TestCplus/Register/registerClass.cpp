#include "stdafx.h"
//背景
//需要根据配置文件中的插件名字获取插件实例，从而需要维护<插件名字，插件实例>的映射关系。
//当有新插件加入项目时，每次都需要在该映射关系中插入一条信息。为了避免避免此操作，通过定义宏
//自动完成 新插件的注册功能。
//
//设计思想
//每个插件在全局域中定义一个注册类，在该注册类的构造函数中将<插件名字，插件实例>插入全局的map中，
//在全局域定义该注册类的一个实例，从而调用构造函数，在map中插入该插件的名字和实例。
//
//代码
//(1)插件基类：
//
//class BasePlugin
//{
//public:
//	virtual bool Run() = 0;
//};
//(2)映射关系--全局域函数
//这里采用函数，而不是直接在全局域定义静态变量是为了解决全局变量相互依赖的问题，
//（如全局对象A依赖于全局对象B，而B晚于A被构造出来）。
//std::map<std::string, BasePlugin*>& GetPlugin()
//{
//	//局部静态对象，只有在使用到时才会被构造出来，由于是在全局对象构造中被调用到，所以不存在多线程问题，
//	//因为这发生在main函数之前，其它线程还没有创建出来
//	static std::map<std::string, BasePlugin*> mapPlugin;
//	return mapPlugin;
//}
//(3)注册类
//当构造该类的对象时，插入<name, BasePlugin*>到mapPlugin中，自动完成注册
//register.h
//#define REGISTER_PLUGIN(name) \
//    class name##Register \
//    { \
//        public:  \
//            name##Register() \
//            { \
//                GetPlugin().insert(std::make_pair(#name, new (std::nothrow) name)); \
//            } \
//    }; \
//    name##Register name##reg;   //调用构造函数
//(4)具体插件类
//1)myplugin.h
//class MyPlugin {
//	MyPlugin() {};
//	~MyPlugin() {};
//	bool Run();
//};
//2)myplugin.cpp(必须在cpp中调用上面定义的宏，原因待解)
//#include "register.h"
//#include <map>
//
////<"MyPlugin", new MyPlugin>被插入到mapPlugin中
//REGISTER_PLUGIN(MyPlugin);
//bool MyPlugin::Run()
//{
//	....
//}