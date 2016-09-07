// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TestLoadCSVComponent.generated.h"

/************************************************************************/
/* 
	����csv���Ӧ�Ľṹ��
		ע�⣬�ṹ���г�Ա����������Ҫ��csv�����һһ��Ӧ
		��Ȼ��csv��ĵ�һ�У�һ������Ϊid������Ҫ�����ڽṹ����
	���磬��������ṹ������csv�����ݣ��������ģ�id, time, scene_id
	�ٱ��磬�ҵ��롰id,time,scene_idx����ʱ�򣬾ͻ�ʧ�ܣ���Ϊ�ͽṹ���Ӧ���ϣ�

	������ṹ�����ӳ�Ա���������߼��ٳ�Ա��������ðѾ�csvɾ��֮���ٵ��룬��Ҫִ�С����µ��롱��Ҫ���ᵼ�¶��С�
*/
/************************************************************************/
USTRUCT()
struct FTestDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test)
		float time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test)
		int scene_id;

	// ����û�ӡ�EditAnywhere��������������޷���editor�б༭���ٺ١�
	UPROPERTY()
		float alpha;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRIMER_API UTestLoadCSVComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestLoadCSVComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
