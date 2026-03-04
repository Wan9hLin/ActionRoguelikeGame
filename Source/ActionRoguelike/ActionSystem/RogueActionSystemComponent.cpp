// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"

// Sets default values for this component's properties
URogueActionSystemComponent::URogueActionSystemComponent()
{
	Attributes.Health = Attributes.MaxHealth;
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
