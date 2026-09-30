// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UStatWidget;
class UNameInputWidget;
class UPlayerInfoWidget;
class ATestPlayerState;
/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void InitializeWithAbilitySystem(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	virtual void InitializePlayerInfo(ATestPlayerState* InPS);

protected:
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UStatWidget> StatWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UPlayerInfoWidget> PlayerInfo;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UNameInputWidget> NameInput;
};
