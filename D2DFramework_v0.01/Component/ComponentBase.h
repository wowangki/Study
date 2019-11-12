#pragma once

class ComponentBase
{
public:
	virtual ~ComponentBase()
	{
		//�� �̰� �ȵɰ� ������.. delete Ű����� ���� �Ҹ��ڿ��� �ڱ��ڽ� �Ҹ��Ű�� ��������
		delete this; 
	}

	virtual void Update(void) = 0;
};

