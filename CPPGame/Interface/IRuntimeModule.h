
#ifndef CPPGAME_INTERFACE_IRUNTIMEMODULE_H
#define CPPGAME_INTERFACE_IRUNTIMEMODULE_H

class IRuntimeModule{
public:
	virtual ~IRuntimeModule() {};
	/*
	 * ����������ʼ��ģ���
	 */
	virtual int Initialize() = 0;
	/*
	 * ����ģ���ǵ���
	 */
	virtual void Finalize() = 0;
	/*
	 * �����������������ģ��������ģ��ִ�еġ�ÿ����һ�Σ�ģ�����һ����λ�Ĵ���
	 */
	virtual void Tick() = 0;
};
#endif //CPPGAME_INTERFACE_IRUNTIMEMODULE_H