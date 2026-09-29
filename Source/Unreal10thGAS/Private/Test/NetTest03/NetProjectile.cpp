// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetTest03/NetProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
ANetProjectile::ANetProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;				// 이 액터는 리플리케이션이 된다.
	SetReplicatingMovement(true);	// 이 액터의 무브먼트 컴포넌트는 리플리케이션이 된다.

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetRelativeScale3D(FVector(0.35f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000.0f;
	Movement->MaxSpeed = 1000.0f;
	Movement->bShouldBounce = true;
}

// Called when the game starts or when spawned
void ANetProjectile::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ANetProjectile::OnHit);
	
	if (GetInstigator())
	{
		Mesh->IgnoreActorWhenMoving(GetInstigator(), true);	// 인스티게이터는 충돌 무시
	}
}

void ANetProjectile::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority())
	{
		// 이전에 부딪친적이 없고, 다른액터가 캐릭터이어야 하고, 다른 액터가 내가 아니고, 다른 액터가 오너도 아니다
		if (!bHitted && OtherActor->IsA<ACharacter>() && OtherActor != this && GetOwner() != OtherActor)
		{
			bHitted = true;

			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
			
			const FString Str = FString::Printf(TEXT("%s가 %s를 공격했습니다."), 
				GetInstigator() ? *GetInstigator()->GetName() : TEXT("없음"),
				*OtherActor->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Str);

			Multicast_HitEffect(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			SetLifeSpan(3.0f);	// 3초 뒤 삭제
		}
	}
}

void ANetProjectile::Multicast_HitEffect_Implementation(const FVector & InLocation, const FRotator & InRotator)
{
	if (HitVFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitVFX, InLocation, InRotator);
	}
}

