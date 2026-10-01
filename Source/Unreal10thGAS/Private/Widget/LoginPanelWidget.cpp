// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LoginPanelWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/TestMultiplayGameInstance.h"

void ULoginPanelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &ULoginPanelWidget::OnCreateButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ULoginPanelWidget::OnJoinButtonClicked);
	}

	if (DisconnectButton)
	{
		DisconnectButton->OnClicked.AddDynamic(this, &ULoginPanelWidget::OnDisconnectButtonClicked);
	}

	ENetMode NetMode = GetWorld() ? GetWorld()->GetNetMode() : NM_Standalone;
	const bool bInGame = (NetMode == NM_Client || NetMode == NM_ListenServer || NetMode == NM_DedicatedServer);	// 네트워크로 접속된 상태인지 확인

	CreateButton->SetIsEnabled(!bInGame);
	JoinButton->SetIsEnabled(!bInGame);
	DisconnectButton->SetIsEnabled(bInGame);
}

void ULoginPanelWidget::OnCreateButtonClicked()
{
	UTestMultiplayGameInstance* GI = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->CreateServer();
	}
}

void ULoginPanelWidget::OnJoinButtonClicked()
{
	UTestMultiplayGameInstance* GI = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		FString IPAddress = GI->GetIPAddress();
		if (InputIPAddress)
		{
			FString InputIP = InputIPAddress->GetText().ToString();
			if (!InputIP.IsEmpty())
			{
				IPAddress = InputIP;
			}
		}

		GI->JoinServer(IPAddress);
	}
}

void ULoginPanelWidget::OnDisconnectButtonClicked()
{
	UTestMultiplayGameInstance* GI = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->DisconnectServer();
	}
}

