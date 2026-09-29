// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetTest03/NetTestCharacter03_RPC.h"
#include "Camera/CameraShakeBase.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

ANetTestCharacter03_RPC::ANetTestCharacter03_RPC()
{
	FireTransform = CreateDefaultSubobject<USceneComponent>(TEXT("FireTransform"));
	const FName FireSocketName = TEXT("Fire");
	FireTransform->SetupAttachment(GetMesh(), FireSocketName);
	//GetMesh()->GetSocketLocation(TEXT("FireSocket"));
}

void ANetTestCharacter03_RPC::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ANetTestCharacter03_RPC::OnTakeDamage);
}

void ANetTestCharacter03_RPC::Test1()
{
	Fire();
}

void ANetTestCharacter03_RPC::OnTakeDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (HasAuthority())
	{
		Health -= Damage;
		OnRepNotify_Health();	// 서버는 리플리케이션이 없기 때문에 UI 수동 갱신용

		Client_OnHit();	// 맞은 클라이언트가 맞은 효과를 보여주게 시키기
		//Client_OnHit_Implementation();	// 로컬 실행. ClientRPC 아님.
	}
}

void ANetTestCharacter03_RPC::Server_Fire_Implementation()
{
	// 서버가 실행하는 코드
	if (ProjectileClass)
	{
		//FVector SpawnLocation = FireTransform->GetComponentLocation();
		//FRotator SpawnRotator = FireTransform->GetComponentRotation();
		FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("Fire"));
		FRotator SpawnRotator = GetMesh()->GetSocketRotation(TEXT("Fire"));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;					// 커넥션을 위해 필수
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(
			ProjectileClass,
			SpawnLocation,
			SpawnRotator,
			SpawnParams
		);
	}
}

void ANetTestCharacter03_RPC::Client_OnHit_Implementation()
{
	// 맞은 클라이언트에서만 실행
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->ClientStartCameraShake(CameraShakeClass);
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		HitVFX,
		GetActorLocation() + FVector::UpVector * 100.0f,
		FRotator::ZeroRotator,
		FVector::OneVector,
		true, true, ENCPoolMethod::AutoRelease
	);
}

void ANetTestCharacter03_RPC::Fire()
{
	if (IsLocallyControlled())	// 내가 조종하고 있는 액터인지 확인
	{
		Server_Fire();			// 서버에게 발사 요청
	}
}
