// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBlackhole.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComponent->SetupAttachment(RootComponent);
	
	RadialForceComponent->ForceStrength = -800000.0f; //Negative to pull instead of push out
	RadialForceComponent->Radius = 1200.0f;
	
	RadialForceComponent->bAutoActivate = true;
	RadialForceComponent->bIgnoreOwningActor = true;
	// Avoid sucking player into blackhole
	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	SphereComponent->SetSphereRadius(20.0f);
	SphereComponent->SetCollisionProfileName("Blackhole");
	
	ProjectileMovementComponent->InitialSpeed = 500.0f;
	InitialLifeSpan = 5.0f;
}


void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackhole::OnSphereOverlap);
	
}


void ARogueProjectileBlackhole::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
}

 


