// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileTeleport.generated.h"


UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileTeleport : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	
	// reuse handle for the initial explosion delay and the teleportation
	FTimerHandle TeleportHandle;
	
	UPROPERTY(EditAnywhere, Category="DestroyTimer")
	float DetonateDelay = 0.2f;
	
	UPROPERTY(EditAnywhere, Category="DestroyTimer")
	float TeleportDelay = 0.2f;

	void OnTeleportBegin();
	
	void StartDelayedTele();
	
	virtual void BeginPlay() override;
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;
	
public:
	// Sets default values for this actor's properties
	ARogueProjectileTeleport();
	
};
