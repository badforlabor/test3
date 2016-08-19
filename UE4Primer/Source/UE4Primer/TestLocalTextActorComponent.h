// Fill out your copyright notice in the Description page of Project Settings.

/************************************************************************/
/* ����FText, FString, FName, ���ػ�����, �ַ�����float��ת��           */
/************************************************************************/
#pragma once

#include "Components/ActorComponent.h"
#include "TestLocalTextActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRIMER_API UTestLocalTextActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestLocalTextActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
