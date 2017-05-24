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

	Ptr은 shared_ptr을 직접 구현한 버전이다. 먼저 Ptr은 Static 메서드인 Create()를 통해
	생성되거나 선언을 통해 만들어질 수 있다. Create()를 호출할 경우 내부에서 지역변수
	newPtr을 만들고 처음에는 무조건 ref cnt가 0에서 1로 되므로 이를 출력한다. 다음은
	조금 특이하다. 고민 끝에 만든 코드지만 정석이라 생각되지 않으며 분명 더 나은 설계
	가 있을거라 확신한다. 그래도 설명을 이어가겠다. 이렇게 새로 만든 newPtr의 
	Reference count를 -2로 만들고 SharedInstance에 새로운 T 객체를 할당한다. Shared
	Instance 부분은 이해하기 쉬우나 Reference count를 -2로 만드는건 이해하기 어렵다.
	그 이유는 다음과 같다. 첫번째, 나는 Create()를 호출할 때 반환 값을 받는 객체가 있는지 확인
	하고 싶었다. 없다면 Create()로 생성한 객체는 바로 Reference count를 줄여 Deallocate
	해야 되기 때문이다. 물론 Create() 측에서 알 수는 없다. 그래서 몇가지 Trick을 
	사용하였다. 지역 변수로 생성한 newPtr은 두번 파괴된다. 물론 각각 다른 객체가 두 번
	파괴 되지만 newPtr의 Reference count는 같은 주소에 두 번 접근 된다. 즉 반환 값을
	받는 객체가 없다면 return시에 지역 객체가 파괴 될때 한번, 반환 된 임시 객체를 받는
	변수가 없어 파괴 될 때 두번이다. 반환 된 임시 객체를 받는 변수가 있다면 파괴되는 대신
	대입 연산자에 의해 이동되기 때문에 파괴는 한 번만 이루어진다. 두번째, 지역 변수를
	만들어 값을 반환하는 경우 임시 객체가 생성되어 복사 생성자에 의해 해당 값이 복사되고
	이 지역 변수를 delete 한 뒤 임시 객체를 반환한다. 이 때 복사 생성자의 경우 Create()
	말고도 예시로 나온 mc1 = mc2; 나 Ptr<MyClass>::Create();가 있다. 이 때 복사생성자
	에 역할은 대입 될 객체의 Reference count를 1늘리고 대입할 객체의 Shared Instance와
	Reference count를 대입 될 객체 것들로 대입하는 것이다. 그래서 Reference count를 
	-2로 하면 Create에서 임시 객체에 복사 생성 될 때 Reference count가 -1이 되고 
	파괴 될때 코드를 보면 Reference count가 -1일 때 1로 만드는 부분이 있다. Create()에
	서 값이 완전히 반환되면 Reference count가 1이 되는 것이다. 지금까지 Reference count
	를 -2로 설정한 이유에 대해 설명했다. 다음은 왜 이렇게 번거로운 작업을 거쳐 Reference count
	가 1을 반환하게 한 이유에 대해 설명하겠다. 먼저 객체가 파괴되어 질 때마다 `ref cnt : ~`를
	출력해야 하는데 지역 변수가 파괴되어 지는건 출력하면 안된다. 그래서 지역 변수가 파괴
	될 때부터 값이 반환될 때 까지는 파괴 작업을 할 수 없었고 이를 -2 ~ -1 값을 통해 해결하였다.
	이것이 왜 이렇게 번거로운 작업을 거쳐 1을 반환하였는지에 대한 이유이자 Create()에
	대한 설명이었다. mc1 = Ptr<MyClass>::Create(); 에 대한 설명은 Create()를 설명
	하며 이미 했다. 변수 선언과 동시에 assignment 연산은 아주 예외적인 경우가 있긴 하지만 
	대부분의 경우 Copy constructor를 호출한다. [1]  mc1->PrintNum("mc1"); 부분은 연산자
	오버로딩을 통해 구현했다. 벤더사와 버전별로 달라 질 수 있겠지만 내 shared_ptr에서는 -> 연산자가
	오버로딩되어 있는것을 확인하였다. 덕분에 -> 연산자로 Ptr<MyClass> 객체가 담고 있는
	실제 객체 mSharedInstance에 접근하여 해당 메서드를 호출할 수 있는 것이다. 이
	mSharedInstance는 말 그대로 공유되는 객체로써 과제에서 요구했듯이 Reference count
	가 0이 되면 자동으로 파괴된다. mc1 = mc2; 는 mc1 = Ptr<MyClass>::Create(); 와
	다르게 복사 생성자가 아닌 대입 연산자가 사용된다. 그럼 대입 연산자에 대해 설명하겠다.
	먼저 대입 연산자는 대입 객체의 Shared instance와 피대입 객체의 Shared instance가
	동일한지를 검사한다. 만약 같다면 아무것도 수행하지 않는다. 왜냐하면 피대입 객체에 대입
	객체의 Reference count와 Shared instance를 대입할 때 기존 객체들을 delete 해주어야 한다.
	이 때 대입 객체와 피대입 객체의 Reference count와 Shared instance가 동일한 값을
	가리킨다면 피대입 객체의 Reference count와 Shared instance를 delete할 때 대입
	객체의 Reference count와 Shared instance도 delete되어 꼬이게 된다. 그러므로 이에
	대한 예외처리를 해주었다. 두 번째로 mReference가 nullptr이 아니면 기존의 Reference count와 Shared instance
	를 delete 해주는 작업을 한다. mReference가 nullptr인 경우는 Ptr<MyClass> temp;
	처럼 선언만 해둔 경우며 이 때는 따로 파괴할 객체가 없다. 그 다음은 피대입 객체의
	Reference count와 Shared instance에 대입 객체의 것들을 대입하는 것이 전부이다.
	마지막으로 객체 파괴시 수행되는 deleteThis()에 대한 설명을 하겠다. 여기서는 소멸자
	를 구현하고 대입 연산시 소멸자를 호출하는 대신 deleteThis()를 만들고 소멸자와 대입
	연산자에서 호출하고 있다. 왜냐하면 대입 연산시 delete this를 할 경우 자식 객체 뿐만
	아니라 자기 자신까지 파괴되어 이후에 this를 참조할 때 read access violation이 발생
	한다. 그러므로 따로 자식 객체만 해제해주는 함수를 만들고 각각 호출한 것이다. 




	[1] http://coliru.stacked-crooked.com/a/708ae8b380c63ba8



*/