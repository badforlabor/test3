// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestSharedPtrActorComponent.h"

void TestSharedPtr();
void TestSharedRef();
void TestWeakPtr();


// Sets default values for this component's properties
UTestSharedPtrActorComponent::UTestSharedPtrActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestSharedPtrActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TestSharedPtr();

	TestSharedRef();

	TestWeakPtr();
}


// Called every frame
void UTestSharedPtrActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


/************************************************************************/
/* ��������ָ��                                                         */
/************************************************************************/
class FPtrTest1
{
public:
	FPtrTest1()
	{
		Debug(TEXT("construct ptr test1"));
	}
	~FPtrTest1()
	{
		Debug(TEXT("destruct ptr test1"));
	}
	virtual void ShowMe()
	{
		Debug(TEXT("I'm ptr test1"));
	}
};
class FPtrTest2 : FPtrTest1 
{
public:
	virtual void ShowMe() override
	{
		Debug(TEXT("I'm ptr test2"));
	}
};
void TestSharedPtr()
{
	// �������ܣ����Զ�����û�����õĶ���
	Debug(TEXT("tag 0"));
	{
		// ���յ�������־��һ����construct��һ����destruct
		TSharedPtr<FPtrTest1> t1(new FPtrTest1());
		Debug(TEXT("tag 0-1"));
	}
	Debug(TEXT("tag 1"));
	{
		// ���յ�������־��һ����construct��һ����destruct
		TSharedPtr<FPtrTest1> t1(new FPtrTest1());
		t1.Reset();
		Debug(TEXT("tag 1-1"));
	}
	Debug(TEXT("tag 2"));
	{
#if false
		// ��һ��ָ�븳ֵ������sharedPtr���ǲ���ȷ�ģ��ᵼ�±�����
		// ������ò�Ҫ����pp��ֱ������ TSharedPtr<FPtrTest1> t1(new FPtrTest1())
		FPtrTest1* pp = new FPtrTest1();
		TSharedPtr<FPtrTest1> t1(pp);
		TSharedPtr<FPtrTest1> t2(pp);
#else
		TSharedPtr<FPtrTest1> t1(new FPtrTest1());
		TSharedPtr<FPtrTest1> t2(t1);
#endif
		if (t1 == t2)
		{
			Debug(TEXT("equal ptr"));
		}
		if (t2.IsValid())
		{
			Debug(TEXT("t2 is valid"));
		}
	}
	Debug(TEXT("tag 3"));
	{
		// MakeShareable, 
		// StaticCastSharedRef, ConstCastSharedRef, DynamicCastSharedRef
		// StaticCastSharedPtr, ConstCastSharedPtr, DynamicCastSharedPtr
		TSharedPtr<FPtrTest1> t1 = MakeShareable(new FPtrTest1());
		TSharedPtr<FPtrTest2> t2 = StaticCastSharedPtr<FPtrTest2>(t1);
		if (t2.IsValid())
		{
			// ��Ȼt2�ǺϷ��ġ�Υ����ʶ����������ò�Ҫ�� StaticCastSharedPtr
			Debug(TEXT("t2 is valid"));
		}
		t2->ShowMe();
	}
	Debug(TEXT("tag 4"));
}

void TestSharedRef()
{
	// �������ã��ǲ�������Ϊnull�Ĺ���ָ�롣����ζ�������ܴ���һ���յĹ�������
	
	{
		TSharedRef<FPtrTest1> t1(new FPtrTest1());
#if false
		// ��Ҫ����һ���յģ������ᵼ�±�����
		TSharedRef<FPtrTest1> t2;
#endif
	}

	// ����ָ�������ʽת��Ϊ��������
	{
		TSharedPtr<FPtrTest1> t1(new FPtrTest1);
		{
			// ��ʾת��
			TSharedRef<FPtrTest1> t2 = t1.ToSharedRef();
			{
				TSharedPtr<FPtrTest1> t3 = t2;	// ��ʽת��
			}
		}
	}
}

void TestWeakPtr()
{
	// ��ָ�룬�������Ӽ�����Ҳ�������ٶ��������ָ�����õĶ��������ˣ���ô�������Զ����㣨Ҳ����˵������ָ��͹��������ڲ���������ָ�룩
	// ��֧�����ݲ��ݣ���û�С�->�����������������õĶ��󣬵õ���Pin������ת���ɹ���ָ��
	{
		TSharedRef<FPtrTest1> t(new FPtrTest1);
		TWeakPtr<FPtrTest1> weak(t);	// �������Ӽ���
		TSharedPtr<FPtrTest1> t2 = weak.Pin();
		Debug(FString::Printf(TEXT("t2's count=%d"), t2.GetSharedReferenceCount()));
	}

	{
		TSharedPtr<FPtrTest1> t(new FPtrTest1);
		TWeakPtr<FPtrTest1> weak(t);
		t = NULL;	// FPtrTest1����ᱻ����
		if (!weak.IsValid())
		{
			Debug(TEXT("weak is invalid."));
		}
	}

	{
		TSharedPtr<FPtrTest1> t(new FPtrTest1);
		TWeakPtr<FPtrTest1> weak(t);
		weak.Reset();	// FPtrTest1���󲻻ᱻ����
		if (t.IsValid())
		{
			Debug(TEXT("t is valid."));
		}
	}
}