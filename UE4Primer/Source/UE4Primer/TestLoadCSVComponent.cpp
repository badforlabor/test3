// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestLoadCSVComponent.h"


// Sets default values for this component's properties
UTestLoadCSVComponent::UTestLoadCSVComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestLoadCSVComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// ����csv��������ʾ��һ������
	UDataTable* csv = LoadObject<UDataTable>(NULL, TEXT("DataTable'/Game/csv/test1.test1'"));
	if (csv != NULL && csv->GetRowNames().Num() > 0)
	{
		// ��ȡid=1�����е�����
		FTestDataRow* row = csv->FindRow<FTestDataRow>(TEXT("1"), TEXT(""));
		if (row != NULL)
		{
			Debug(FString::Printf(TEXT("csv, row time="), row->time));
		}
	}

	// ��̬��ȡcsv�ļ������������ֻ����Editorģʽ���У������Ҫ�ڷ����������У���ô�Լ��½�һ����
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameDir()) + FString::Printf(TEXT("csv/test1.csv"));
	FString Data;
	if (FFileHelper::LoadFileToString(Data, *FilePath))
	{
		UDataTable* DataTable = NewObject<UDataTable>(GetTransientPackage(), FName(TEXT("CSV_Test")));
		DataTable->RowStruct = FTestDataRow::StaticStruct();
		DataTable->CreateTableFromCSVString(Data);
		Debug(FString::Printf(TEXT("%d"), DataTable->GetRowNames().Num()));
	}
}


// Called every frame
void UTestLoadCSVComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

