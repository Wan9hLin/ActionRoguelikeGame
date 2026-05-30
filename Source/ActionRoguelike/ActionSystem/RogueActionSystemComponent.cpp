// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"

#include "RogueAction.h"

// Sets default values for this component's properties
URogueActionSystemComponent::URogueActionSystemComponent()
{
	Attributes.Health = Attributes.MaxHealth;
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	for (TSubclassOf<URogueAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	URogueAction* NewAction = NewObject<URogueAction>(this, NewActionClass);
	Actions.Add(NewAction);
}


void URogueActionSystemComponent::StartAction(FName InActionName)
{
	for (URogueAction* Action: Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StrartAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Nor Action found with name %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FName InActionName)
{
	for (URogueAction* Action: Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Nor Action found with name %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;
	float MaxHealth = Attributes.MaxHealth;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health,OldHealth); 
	}
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, Max Health: %f"), Attributes.Health, MaxHealth);
}

bool URogueActionSystemComponent::IsFullHealth() const
{
	return FMath::IsNearlyEqual(Attributes.MaxHealth, Attributes.Health);
}

float URogueActionSystemComponent::GetMaxHealth() const
{
	return Attributes.MaxHealth;
}

float URogueActionSystemComponent::GetHealth() const
{
	return Attributes.Health;
}


