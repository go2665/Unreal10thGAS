// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestGASHUD.generated.h"

class UHUDWidget;
class ATestPlayerState;
/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API ATestGASHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitHUD(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
	void InitNetHUD(ATestPlayerState* InPS);

	UFUNCTION(BlueprintCallable)
	UHUDWidget* GetHUDWidget() const { return HUDWidget; }

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHUDWidget> HUDWidget;
	
};
