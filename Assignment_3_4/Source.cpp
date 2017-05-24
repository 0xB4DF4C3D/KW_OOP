#include <iostream>

#include "MyClass.h"
#include "Ptr.h"

using namespace std;

#include <memory>;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(216);
	Ptr<MyClass>::Create();
	Ptr<MyClass> mc1 = Ptr<MyClass>::Create();
	Ptr<MyClass> mc2 = Ptr<MyClass>::Create();
	mc1->PrintNum("mc1");
	mc1->PrintNum("mc1");
	mc1 = mc2;

	Ptr<MyClass> temp;
	temp = mc2;
	temp->PrintNum("mc2");
	{
		Ptr<MyClass> temp2 = mc2;
		temp->PrintNum("mc2");
	}
	{
		Ptr<MyClass> temp2 = mc2;
		temp->PrintNum("mc2");
	} 
	return EXIT_SUCCESS;
}

/*

	Ptr�� shared_ptr�� ���� ������ �����̴�. ���� Ptr�� Static �޼����� Create()�� ����
	�����ǰų� ������ ���� ������� �� �ִ�. Create()�� ȣ���� ��� ���ο��� ��������
	newPtr�� ����� ó������ ������ ref cnt�� 0���� 1�� �ǹǷ� �̸� ����Ѵ�. ������
	���� Ư���ϴ�. ��� ���� ���� �ڵ����� �����̶� �������� ������ �и� �� ���� ����
	�� �����Ŷ� Ȯ���Ѵ�. �׷��� ������ �̾�ڴ�. �̷��� ���� ���� newPtr�� 
	Reference count�� -2�� ����� SharedInstance�� ���ο� T ��ü�� �Ҵ��Ѵ�. Shared
	Instance �κ��� �����ϱ� ���쳪 Reference count�� -2�� ����°� �����ϱ� ��ƴ�.
	�� ������ ������ ����. ù��°, ���� Create()�� ȣ���� �� ��ȯ ���� �޴� ��ü�� �ִ��� Ȯ��
	�ϰ� �;���. ���ٸ� Create()�� ������ ��ü�� �ٷ� Reference count�� �ٿ� Deallocate
	�ؾ� �Ǳ� �����̴�. ���� Create() ������ �� ���� ����. �׷��� ��� Trick�� 
	����Ͽ���. ���� ������ ������ newPtr�� �ι� �ı��ȴ�. ���� ���� �ٸ� ��ü�� �� ��
	�ı� ������ newPtr�� Reference count�� ���� �ּҿ� �� �� ���� �ȴ�. �� ��ȯ ����
	�޴� ��ü�� ���ٸ� return�ÿ� ���� ��ü�� �ı� �ɶ� �ѹ�, ��ȯ �� �ӽ� ��ü�� �޴�
	������ ���� �ı� �� �� �ι��̴�. ��ȯ �� �ӽ� ��ü�� �޴� ������ �ִٸ� �ı��Ǵ� ���
	���� �����ڿ� ���� �̵��Ǳ� ������ �ı��� �� ���� �̷������. �ι�°, ���� ������
	����� ���� ��ȯ�ϴ� ��� �ӽ� ��ü�� �����Ǿ� ���� �����ڿ� ���� �ش� ���� ����ǰ�
	�� ���� ������ delete �� �� �ӽ� ��ü�� ��ȯ�Ѵ�. �� �� ���� �������� ��� Create()
	���� ���÷� ���� mc1 = mc2; �� Ptr<MyClass>::Create();�� �ִ�. �� �� ���������
	�� ������ ���� �� ��ü�� Reference count�� 1�ø��� ������ ��ü�� Shared Instance��
	Reference count�� ���� �� ��ü �͵�� �����ϴ� ���̴�. �׷��� Reference count�� 
	-2�� �ϸ� Create���� �ӽ� ��ü�� ���� ���� �� �� Reference count�� -1�� �ǰ� 
	�ı� �ɶ� �ڵ带 ���� Reference count�� -1�� �� 1�� ����� �κ��� �ִ�. Create()��
	�� ���� ������ ��ȯ�Ǹ� Reference count�� 1�� �Ǵ� ���̴�. ���ݱ��� Reference count
	�� -2�� ������ ������ ���� �����ߴ�. ������ �� �̷��� ���ŷο� �۾��� ���� Reference count
	�� 1�� ��ȯ�ϰ� �� ������ ���� �����ϰڴ�. ���� ��ü�� �ı��Ǿ� �� ������ `ref cnt : ~`��
	����ؾ� �ϴµ� ���� ������ �ı��Ǿ� ���°� ����ϸ� �ȵȴ�. �׷��� ���� ������ �ı�
	�� ������ ���� ��ȯ�� �� ������ �ı� �۾��� �� �� ������ �̸� -2 ~ -1 ���� ���� �ذ��Ͽ���.
	�̰��� �� �̷��� ���ŷο� �۾��� ���� 1�� ��ȯ�Ͽ������� ���� �������� Create()��
	���� �����̾���. mc1 = Ptr<MyClass>::Create(); �� ���� ������ Create()�� ����
	�ϸ� �̹� �ߴ�. ���� ����� ���ÿ� assignment ������ ���� �������� ��찡 �ֱ� ������ 
	��κ��� ��� Copy constructor�� ȣ���Ѵ�. [1]  mc1->PrintNum("mc1"); �κ��� ������
	�����ε��� ���� �����ߴ�. ������� �������� �޶� �� �� �ְ����� �� shared_ptr������ -> �����ڰ�
	�����ε��Ǿ� �ִ°��� Ȯ���Ͽ���. ���п� -> �����ڷ� Ptr<MyClass> ��ü�� ��� �ִ�
	���� ��ü mSharedInstance�� �����Ͽ� �ش� �޼��带 ȣ���� �� �ִ� ���̴�. ��
	mSharedInstance�� �� �״�� �����Ǵ� ��ü�ν� �������� �䱸�ߵ��� Reference count
	�� 0�� �Ǹ� �ڵ����� �ı��ȴ�. mc1 = mc2; �� mc1 = Ptr<MyClass>::Create(); ��
	�ٸ��� ���� �����ڰ� �ƴ� ���� �����ڰ� ���ȴ�. �׷� ���� �����ڿ� ���� �����ϰڴ�.
	���� ���� �����ڴ� ���� ��ü�� Shared instance�� �Ǵ��� ��ü�� Shared instance��
	���������� �˻��Ѵ�. ���� ���ٸ� �ƹ��͵� �������� �ʴ´�. �ֳ��ϸ� �Ǵ��� ��ü�� ����
	��ü�� Reference count�� Shared instance�� ������ �� ���� ��ü���� delete ���־�� �Ѵ�.
	�� �� ���� ��ü�� �Ǵ��� ��ü�� Reference count�� Shared instance�� ������ ����
	����Ų�ٸ� �Ǵ��� ��ü�� Reference count�� Shared instance�� delete�� �� ����
	��ü�� Reference count�� Shared instance�� delete�Ǿ� ���̰� �ȴ�. �׷��Ƿ� �̿�
	���� ����ó���� ���־���. �� ��°�� mReference�� nullptr�� �ƴϸ� ������ Reference count�� Shared instance
	�� delete ���ִ� �۾��� �Ѵ�. mReference�� nullptr�� ���� Ptr<MyClass> temp;
	ó�� ���� �ص� ���� �� ���� ���� �ı��� ��ü�� ����. �� ������ �Ǵ��� ��ü��
	Reference count�� Shared instance�� ���� ��ü�� �͵��� �����ϴ� ���� �����̴�.
	���������� ��ü �ı��� ����Ǵ� deleteThis()�� ���� ������ �ϰڴ�. ���⼭�� �Ҹ���
	�� �����ϰ� ���� ����� �Ҹ��ڸ� ȣ���ϴ� ��� deleteThis()�� ����� �Ҹ��ڿ� ����
	�����ڿ��� ȣ���ϰ� �ִ�. �ֳ��ϸ� ���� ����� delete this�� �� ��� �ڽ� ��ü �Ӹ�
	�ƴ϶� �ڱ� �ڽű��� �ı��Ǿ� ���Ŀ� this�� ������ �� read access violation�� �߻�
	�Ѵ�. �׷��Ƿ� ���� �ڽ� ��ü�� �������ִ� �Լ��� ����� ���� ȣ���� ���̴�. 




	[1] http://coliru.stacked-crooked.com/a/708ae8b380c63ba8



*/