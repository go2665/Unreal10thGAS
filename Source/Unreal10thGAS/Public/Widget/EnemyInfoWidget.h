// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyInfoWidget.generated.h"

class UTextBlock;
class ATestPlayerState;
/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API UEnemyInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitializePlayerStateBind(ATestPlayerState* InPS);

protected:
	void UpdateEnemyName(const FString& InName);
	void UpdateEnemyScore(int32 InScore);


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> EnemyName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> EnemyScore;

	
};
