// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/NetTest03/PoisonTrap.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
APoisonTrap::APoisonTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	TrapVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TrapVolume"));
	SetRootComponent(TrapVolume);	
	TrapVolume->InitSphereRadius(TrapRadius);

	TrapEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrapEffectComp"));
	TrapEffectComponent->SetupAttachment(TrapVolume);
	TrapEffectComponent->SetAutoActivate(true);
}

void APoisonTrap::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	TrapVolume->SetSphereRadius(TrapRadius);

	if (TrapEffectComponent)
	{
		TrapEffectComponent->SetFloatParameter(FName("Radius"), TrapRadius);
		TrapEffectComponent->SetColorParameter(FName("EffectColor"), ParticleColor);		
	}
}

// Called when the game starts or when spawned
void APoisonTrap::BeginPlay()
{
	Super::BeginPlay();

	TrapVolume->OnComponentBeginOverlap.AddDynamic(this, &APoisonTrap::OnOverlapBegin);
	TrapVolume->OnComponentEndOverlap.AddDynamic(this, &APoisonTrap::OnOverlapEnd);
	
}

void APoisonTrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority() && OtherActor != this)
	{
		DamageTargetActors.Add(OtherActor);
		FTimerManager& TimerManager = GetWorldTimerManager();
		if (!TimerManager.IsTimerActive(DamageTimerHandle))
		{
			TimerManager.SetTimer(
				DamageTimerHandle,
				this,
				&APoisonTrap::ApplyDamage,
				DamageInterval,
				true
			);
		}
	}
}

void APoisonTrap::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (HasAuthority() && OtherActor != this)
	{
		DamageTargetActors.Remove(OtherActor);
		if (DamageTargetActors.IsEmpty())
		{
			FTimerManager& TimerManager = GetWorldTimerManager();
			TimerManager.ClearTimer(DamageTimerHandle);
		}
	}
}

void APoisonTrap::Multicast_OnHit_Implementation(const FVector& InLocation)
{
	if (HitVFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), 
			HitVFX,
			InLocation,
			GetActorRotation(),
			FVector::OneVector,
			true,
			true,
			ENCPoolMethod::AutoRelease
		);
	}
}

void APoisonTrap::ApplyDamage()
{
	if (HasAuthority())
	{
		for (AActor* Target : DamageTargetActors)
		{
			if (IsValid(Target))
			{
				UGameplayStatics::ApplyDamage(Target, Damage, GetInstigatorController(), this, UDamageType::StaticClass());
				Multicast_OnHit(Target->GetActorLocation());
			}
			else
			{
				DamageTargetActors.Remove(Target);
			}
		}
	}
}


