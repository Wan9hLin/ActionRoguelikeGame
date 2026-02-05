// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "RogueGameTypes.h"
#include "ActionRoguelike/Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"


TAutoConsoleVariable<bool> CVar_InteractionDebugDrawing(TEXT("game.interaction.debugdrawing"), false, 
	TEXT("Enable interaction component debug rendering. (0 = off, 1 =enabled)"),
	ECVF_Cheat);

// Sets default values for this component's properties
URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void URogueInteractionComponent::Interact()
{
	/*IRogueInteractionInterface* InteractionInterface = Cast<IRogueInteractionInterface>(SelectedActor);
	if (InteractionInterface)
	{
		InteractionInterface->Interact();
	}*/
	
	IRogueInteractionInterface::Execute_Interact(SelectedActor);
}

// Called every frame
void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();

	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	AActor* BestActor = nullptr;
	float HighestDotResult = -1.0;
	
	bool bEnabledDebugDraw = CVar_InteractionDebugDrawing.GetValueOnGameThread();
	 
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		if (DotResult > HighestDotResult)
		{
			HighestDotResult = DotResult;
			BestActor = Overlap.GetActor(); 
		}
		
		if (bEnabledDebugDraw)
		{
			DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
			FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
			DrawDebugString(GetWorld(), OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
		}
	}
	
	SelectedActor = BestActor;
	
	if (bEnabledDebugDraw)
	{
		if (BestActor)
		{
			DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
		}	
	
		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	}
}

