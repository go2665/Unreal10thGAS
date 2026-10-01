// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Test/Test03/TestPlayerCharacter03.h"
#include "ANetTestCharacter02_Replication.generated.h"

class UInputMappingContext;
class UWidgetComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float);

/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API AANetTestCharacter02_Replication : public ATestPlayerCharacter03
{
	GENERATED_BODY()
public:
	AANetTestCharacter02_Replication();
		
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual FString MakeDebugInfoString() const;

	UFUNCTION()
	void OnRepNotify_Level();

	UFUNCTION()
	void OnRepNotify_Health();

	UFUNCTION(CallInEditor, Category = "Test")
	void TestLevelUp();

	UFUNCTION()
	virtual void Test1();

	UFUNCTION()
	virtual void Test2();

	UFUNCTION()
	virtual void Test3();

public:
	FOnHealthChange OnHealthChanged;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Test", ReplicatedUsing = OnRepNotify_Level)	// Level이 리플리케이션이 될 떄 OnRepNotify_Level이 실행
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, Category = "Test", ReplicatedUsing = OnRepNotify_Health)	
	float Health = 100.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Test", Replicated)	// 리플리케이션이 된다고 표시
	float Exp = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> TestMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Test1;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Test2;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Test3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> OverheadWidgetComp;
};
