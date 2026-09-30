// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetTest04/NetTestCharacter04_PlayerState.h"
#include "Framework/TestGASHUD.h"
#include "Framework/TestPlayerState.h"

void ANetTestCharacter04_PlayerState::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (!IsLocallyControlled()) return;

	// 클라이언트를 위한 HUD 초기화
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ATestGASHUD* TestGASHUD = Cast<ATestGASHUD>(PC->GetHUD()))
		{
			if (ATestPlayerState* PS = Cast<ATestPlayerState>(GetPlayerState()))
			{
				TestGASHUD->InitNetHUD(PS);
			}
		}
	}
}

void ANetTestCharacter04_PlayerState::PossessedBy(AController * NewController)
{
	Super::PossessedBy(NewController);

	if (!IsLocallyControlled()) return;

	// 서버를 위한 HUD 초기화
	if (APlayerController* PC = Cast<APlayerController>(NewController))
	{
		if (ATestGASHUD* TestGASHUD = Cast<ATestGASHUD>(PC->GetHUD()))
		{
			if (ATestPlayerState* PS = Cast<ATestPlayerState>(GetPlayerState()))
			{
				TestGASHUD->InitNetHUD(PS);
			}
		}
	}
}
