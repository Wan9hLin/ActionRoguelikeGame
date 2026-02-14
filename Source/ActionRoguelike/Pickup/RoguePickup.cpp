// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickup.h"
#include "Components/SphereComponent.h"


// Sets default values
ARoguePickup::ARoguePickup()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(128.0f);
	SphereComponent->SetCollisionProfileName("Pickup");
	RootComponent = SphereComponent;
	
}

void ARoguePickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoguePickup::OnSphereOverlap);
}

void ARoguePickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	//Destroy();
}






