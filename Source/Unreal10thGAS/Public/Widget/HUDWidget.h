// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UStatWidget;
class UNameInputWidget;
class UPlayerInfoWidget;
class ATestPlayerState;
class UVerticalBox;
class UEnemyInfoWidget;

/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintCallable)
	virtual void InitializeWithAbilitySystem(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	virtual void InitializePlayerInfo(ATestPlayerState* InPS);

protected:
	void InitGameStateBind();
	void OnPlayerStateAdded(APlayerState* InPS);
	void OnPlayerStateRemoved(APlayerState* InPS);
	bool IsLocalPlayerState(APlayerState* InPS) const;

protected:
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadOnly)
	TObjectPtr<UStatWidget> StatWidget;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UPlayerInfoWidget> PlayerInfo;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UNameInputWidget> NameInput;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	TObjectPtr<UVerticalBox> EnemyInfoList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|EnemyInfo")
	TSubclassOf<UEnemyInfoWidget> EnemyInfoWidgetClass;

private:
	TWeakObjectPtr<ATestPlayerState> LocalPlayerState;

	FTimerHandle TimerHandle_InitGameState;

	TMap<TWeakObjectPtr<APlayerState>, TWeakObjectPtr<UEnemyInfoWidget>> EnemyWidgetMap;
};

