// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAction;	

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY()
	
	FRogueAttributeSet(): 
	Health(100.0f),
	MaxHealth(100.0f) {}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	void StartAction(FName InActionName);
	
	void ApplyHealthChange(float InValueChange);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	bool IsFullHealth() const;
	
	float GetMaxHealth() const;
	float GetHealth() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
public:
	
	URogueActionSystemComponent();
};
