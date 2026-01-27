// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	ProjectileMovementComponent->InitialSpeed = 6000.0f;
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ThisClass::StartDelayedTele, DetonateDelay);
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	GetWorldTimerManager().ClearTimer(TeleportHandle);
	
	StartDelayedTele();
}

void ARogueProjectileTeleport::StartDelayedTele()
{
	PlayExplodeEffects();
	
	ProjectileMovementComponent->StopMovementImmediately();
	LoopedNiagaraComponent->Deactivate();
	LoopedAudioComponent->Stop();
	SetActorEnableCollision(false);
	
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ARogueProjectileTeleport::OnTeleportBegin, TeleportDelay);
}

void ARogueProjectileTeleport::OnTeleportBegin()
{
	APawn* ActorToTeleport = GetInstigator();
	check(ActorToTeleport); // TODO: we should check if is still valid once implment death
	
	ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	Destroy();
}



