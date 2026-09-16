// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAction;	
class URogueAttributeSet;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);
	
	void ApplyHealthChange(float InValueChange);
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	bool IsFullHealth() const;
	
	float GetMaxHealth() const;
	float GetHealth() const;
	
	virtual void InitializeComponent() override;
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
	FGameplayTagContainer ActiveGameplayTags;
	
protected:
	
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> Attributes;
	
	UPROPERTY(EditAnywhere, Category=Attributes, NoClear)
	TSubclassOf<URogueAttributeSet> AttributeSetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
public:
	
	URogueActionSystemComponent();
};
