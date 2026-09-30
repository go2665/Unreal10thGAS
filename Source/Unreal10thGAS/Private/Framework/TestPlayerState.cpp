// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestPlayerState.h"
#include "Net/UnrealNetwork.h"


void ATestPlayerState::AddMyPlayerScore(int32 InPoint)
{
	if (HasAuthority())
	{
		MyPlayerScore += InPoint;
		OnRepNotify_MyPlayerScore();
	}
}

void ATestPlayerState::SetMyPlayerName(const FString & InNewName)
{
	if (HasAuthority())
	{
		// 서버
		if (InNewName.IsEmpty())
		{
			MyPlayerName = TEXT("플레이어");
		}
		else
		{
			MyPlayerName = InNewName;
		}
		OnRepNotify_MyPlayerName();
	}
	else
	{
		// 클라이언트
		Server_SetMyPlayerName(InNewName);
	}
}

void ATestPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestPlayerState, MyPlayerScore);
	DOREPLIFETIME(ATestPlayerState, MyPlayerName);
}

bool ATestPlayerState::Server_SetMyPlayerName_Validate(const FString& InNewName)
{
	return InNewName.Len() <= 10;
}

void ATestPlayerState::Server_SetMyPlayerName_Implementation(const FString& InNewName)
{
	SetMyPlayerName(InNewName);
}

void ATestPlayerState::OnRepNotify_MyPlayerScore()
{
	// HUD에 점수를 갱신한다.
}

void ATestPlayerState::OnRepNotify_MyPlayerName()
{
	// HUD와 캐릭터 머리위에 있는 이름을 갱신한다.(델리게이트로 알람 보내기)
	OnNameChanged.Broadcast(MyPlayerName);
}
