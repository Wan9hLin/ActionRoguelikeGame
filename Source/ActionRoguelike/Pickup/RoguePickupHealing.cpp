// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickupHealing.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARoguePickupHealing::ARoguePickupHealing()
{
	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMeshComp"));
	PickupMeshComponent->SetCollisionProfileName("NoCollision");
	PickupMeshComponent->SetupAttachment(RootComponent);
}

void ARoguePickupHealing::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	URogueActionSystemComponent* ActionComp = OtherActor->GetComponentByClass<URogueActionSystemComponent>();
	
	// Assert if null, then we misconfigured what we can overlap whith
	// Skip healing if already full health
	if (ensure(ActionComp != nullptr) && !ActionComp->IsFullHealth())
	{
		ActionComp->ApplyHealthChange(healingPoint);
		
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator);
	
		Destroy();
	}
	
}



