// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestLocalTextActorComponent.h"

void TestLocalization();
void TestFText();
void TestFString();
void TestFName();

// Sets default values for this component's properties
UTestLocalTextActorComponent::UTestLocalTextActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestLocalTextActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TestLocalization();
	TestFName();
	TestFString();
	TestFText();
}


// Called every frame
void UTestLocalTextActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void TestLocalization()
{
	// ��Ҫ���ã�Ҫ������ʾ���ģ������ǡ��༭��ƫ������ -> ����&���� -> ������Ϸ���ԣ����ġ�
	// ���ػ��������÷������༭��ƫ������-> Localization Dashboard ��ѡ�ϣ�Ȼ������
	//		Ȼ�󣺴��� -> ���ػ����ư� -> Targets�е�Games -> �༭Gather Text�������Լ��Ĵ���·���� -> ������ԣ����ģ�-> ���� -> ����
	{
		FText t = NSLOCTEXT("UE4Primer", "Test_Loc1", "test localization 1");
		Debug(t.ToString());
	}
}
void TestFName()
{

}
void TestFString()
{

}
void TestFText()
{

}