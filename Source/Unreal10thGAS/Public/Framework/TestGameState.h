// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*);

/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;

public:
	FOnPlayerStateChanged OnPlayerStateAdded;
	FOnPlayerStateChanged OnPlayerStateRemoved;
};
