#include "stdafx.h"
//����
//��Ҫ���������ļ��еĲ�����ֻ�ȡ���ʵ�����Ӷ���Ҫά��<������֣����ʵ��>��ӳ���ϵ��
//�����²��������Ŀʱ��ÿ�ζ���Ҫ�ڸ�ӳ���ϵ�в���һ����Ϣ��Ϊ�˱������˲�����ͨ�������
//�Զ���� �²����ע�Ṧ�ܡ�
//
//���˼��
//ÿ�������ȫ�����ж���һ��ע���࣬�ڸ�ע����Ĺ��캯���н�<������֣����ʵ��>����ȫ�ֵ�map�У�
//��ȫ�������ע�����һ��ʵ�����Ӷ����ù��캯������map�в���ò�������ֺ�ʵ����
//
//����
//(1)������ࣺ
//
//class BasePlugin
//{
//public:
//	virtual bool Run() = 0;
//};
//(2)ӳ���ϵ--ȫ������
//������ú�����������ֱ����ȫ�����徲̬������Ϊ�˽��ȫ�ֱ����໥���������⣬
//����ȫ�ֶ���A������ȫ�ֶ���B����B����A�������������
//std::map<std::string, BasePlugin*>& GetPlugin()
//{
//	//�ֲ���̬����ֻ����ʹ�õ�ʱ�Żᱻ�����������������ȫ�ֶ������б����õ������Բ����ڶ��߳����⣬
//	//��Ϊ�ⷢ����main����֮ǰ�������̻߳�û�д�������
//	static std::map<std::string, BasePlugin*> mapPlugin;
//	return mapPlugin;
//}
//(3)ע����
//���������Ķ���ʱ������<name, BasePlugin*>��mapPlugin�У��Զ����ע��
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
//    name##Register name##reg;   //���ù��캯��
//(4)��������
//1)myplugin.h
//class MyPlugin {
//	MyPlugin() {};
//	~MyPlugin() {};
//	bool Run();
//};
//2)myplugin.cpp(������cpp�е������涨��ĺ꣬ԭ�����)
//#include "register.h"
//#include <map>
//
////<"MyPlugin", new MyPlugin>�����뵽mapPlugin��
//REGISTER_PLUGIN(MyPlugin);
//bool MyPlugin::Run()
//{
//	....
//}