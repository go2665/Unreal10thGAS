// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NameplateWidget.generated.h"

class ATestPlayerState;
class UTextBlock;
/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API UNameplateWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void InitializePlayerStateBind(ATestPlayerState* InPS);

protected:
	virtual void UpdateName(const FString& InName);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

};
