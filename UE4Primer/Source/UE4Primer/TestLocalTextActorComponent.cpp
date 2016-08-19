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
	// 需要设置，要不不显示中文，方法是“编辑器偏好设置 -> 区域&语言 -> 本地游戏语言：中文”
	// 本地化文字设置方法：编辑器偏好设置-> Localization Dashboard 勾选上，然后重启
	//		然后：窗口 -> 本地化控制板 -> Targets中的Games -> 编辑Gather Text（加上自己的代码路径） -> 添加语言（中文）-> 翻译 -> 编译
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