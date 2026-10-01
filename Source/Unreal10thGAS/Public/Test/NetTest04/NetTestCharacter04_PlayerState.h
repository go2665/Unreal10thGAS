// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Test/NetTest03/NetTestCharacter03_RPC.h"
#include "NetTestCharacter04_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API ANetTestCharacter04_PlayerState : public ANetTestCharacter03_RPC
{
	GENERATED_BODY()
	
public:
	ANetTestCharacter04_PlayerState();
	virtual void Tick(float DeltaTime) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual FString MakeDebugInfoString() const override;

	/** 카메라 시선과 마주보도록(카메라 Forward의 반대 방향, 사이각 180도) 위젯 컴포넌트의 월드 회전을 갱신 */
	virtual void UpdateOverheadWidgetRotation();

private:
	void InitNameplateWidget();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> NameplateWidgetComp;

	/** 위젯이 항상 카메라를 바라보도록 회전할지 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Overhead")
	bool bFaceCamera = true;

	/** 빌보드 회전 시 상하 기울기(Pitch)를 고정(0)할지 여부 (true면 수평 유지, false면 카메라 시선과 정확히 일치) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Overhead")
	bool bLockWidgetPitch = false;

	/** 빌보드 회전 시 좌우 기울기(Roll)를 고정(0)할지 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Overhead")
	bool bLockWidgetRoll = true;
};
