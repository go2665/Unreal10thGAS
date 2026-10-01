// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestGameState.h"
#include "GameFramework/PlayerState.h"

void ATestGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	if (PlayerState && !PlayerState->IsInactive())
	{
		OnPlayerStateAdded.Broadcast(PlayerState);
	}
}

void ATestGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	if (PlayerState)
	{
		OnPlayerStateRemoved.Broadcast(PlayerState);
	}
}

