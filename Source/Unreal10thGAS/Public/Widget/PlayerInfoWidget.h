// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoWidget.generated.h"

class UTextBlock;
class ATestPlayerState;
/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API UPlayerInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializePlayerStatBind(ATestPlayerState* InPS);

protected:
	void UpdatePlayerName(const FString& InName);

	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerScore;
};
