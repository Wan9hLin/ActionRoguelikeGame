// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

class URogueActionSystemComponent;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Actions")
	FName ActionName;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	float CooldownTime = 0.0f;
	
public:
	
	UFUNCTION(BlueprintCallable)
	URogueActionSystemComponent* GetOwningComponent() const;
	
	bool CanStart() const;
	
	bool IsRunning() const
	{
		return bIsRunning;
	}

	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StrartAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StopAction();
	
	// implementaion inline
	FName GetActionName() const
	{
		return ActionName;
	}
	
	float GetCooldownTimeRemaining() const;
	
protected:
	// GameTime until the Action is available again
	UPROPERTY(Transient)
	float CooldownUntil = 0;
	
	UPROPERTY(Transient)
	bool bIsRunning = false;
	
};
