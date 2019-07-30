//
// Created by ���� on 2018/4/21.
//

#ifndef CPPGAME_INTERFACE_IAPPLICATION_H
#define CPPGAME_INTERFACE_IAPPLICATION_H

#include "IRuntimeModule.h"

class IApplication :public IRuntimeModule{
public:
	virtual int Initialize() = 0;

	virtual void Finalize() = 0;

	// One cycle of the main loop
	virtual void Tick() = 0;
	/*
		* ���ڲ�ѯӦ�ó����Ƿ���Ҫ�˳���
		* ������Ϊ���ںܶ�ƽ̨���û��ر�Ӧ�ó�����ͨ��ϵͳ֪ͨ�����ġ�
		* ���ǵĳ�����������ֱ�ӽ����ⷽ����жϡ����Ե������յ������Ĺر�֪ͨ��ʱ��
	*/
	virtual bool IsQuit() = 0;
};
#endif //MAENGINE_IAPPLICATION_H
