// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetTest04/NetTestCharacter04_PlayerState.h"
#include "Framework/TestGASHUD.h"
#include "Framework/TestPlayerState.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/NameplateWidget.h"

ANetTestCharacter04_PlayerState::ANetTestCharacter04_PlayerState()
{
	NameplateWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameplateWidgetComp"));
	NameplateWidgetComp->SetupAttachment(OverheadWidgetComp);
	NameplateWidgetComp->AddRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
}

void ANetTestCharacter04_PlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFaceCamera)
	{
		UpdateOverheadWidgetRotation();
	}
}

void ANetTestCharacter04_PlayerState::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitNameplateWidget();

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

	InitNameplateWidget();

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

FString ANetTestCharacter04_PlayerState::MakeDebugInfoString() const
{
	FString Name = "-";
	int32 Score = 0;
	if (ATestPlayerState* PS = Cast<ATestPlayerState>(GetPlayerState()))
	{
		Name = PS->GetMyPlayerName();
		Score = PS->GetMyPlayerScore();
	}
	return FString::Printf(TEXT("Name : %s\nScore : %d"), *Name, Score);
}

void ANetTestCharacter04_PlayerState::UpdateOverheadWidgetRotation()
{
	if (!OverheadWidgetComp) return;

	if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		// 카메라의 전방 벡터와 정확히 마주보는 방향(-CameraForward, 사이각 180도)으로 회전
		const FVector CameraForward = CameraManager->GetCameraRotation().Vector();
		FRotator WidgetRotation = (-CameraForward).Rotation();

		if (bLockWidgetPitch)
		{
			WidgetRotation.Pitch = 0.0f;
		}
		if (bLockWidgetRoll)
		{
			WidgetRotation.Roll = 0.0f;
		}

		OverheadWidgetComp->SetWorldRotation(WidgetRotation);
	}
}

void ANetTestCharacter04_PlayerState::InitNameplateWidget()
{
	if (!NameplateWidgetComp) return;
	
	NameplateWidgetComp->InitWidget();	// 위젯이 아직 생성되지 않았을 것을 감안해 즉시 생성하도록 처리
	UNameplateWidget* NameplateWidget = Cast<UNameplateWidget>(NameplateWidgetComp->GetWidget());
	if (NameplateWidget)
	{
		ATestPlayerState* PS = Cast<ATestPlayerState>(GetPlayerState());
		NameplateWidget->InitializePlayerStateBind(PS);
	}
}

