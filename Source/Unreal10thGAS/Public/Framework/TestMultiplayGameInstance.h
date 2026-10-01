// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestMultiplayGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL10THGAS_API UTestMultiplayGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UTestMultiplayGameInstance();

	virtual void Init() override;

	void CreateServer();
	void JoinServer(FString IPAddress);
	void DisconnectServer();

	inline const FString& GetIPAddress() const { return ServerIP; }

private:
	UFUNCTION()
	void HandleNetworkFailure(UWorld* World, UNetDriver* NetDirever, ENetworkFailure::Type FailureType, const FString& ErrorString);

	UFUNCTION()
	void HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString);

protected:
	// 접속할 서버 IP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test")
	FString ServerIP;

	// 게임 시작시 로그인 화면이 보이는 맵
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test")
	TSoftObjectPtr<UWorld> LoginLevelAsset = nullptr;

	// 서버 생성 후 접속할 맵
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test")
	TSoftObjectPtr<UWorld> PlayLevelAsset = nullptr;

	// 최대 접속가능한 플레이어 수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Test")
	int32 MaxPlayers = 2;
};
