// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoguePickup.h"
#include "RoguePickupHealing.generated.h"

class UStaticMeshComponent;
class USoundBase;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARoguePickupHealing : public ARoguePickup
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> PickupMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> PickupSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	float healingPoint = 50.0f;
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	ARoguePickupHealing();


};
