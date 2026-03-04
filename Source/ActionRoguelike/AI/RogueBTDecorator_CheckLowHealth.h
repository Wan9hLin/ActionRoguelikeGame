// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RogueBTDecorator_CheckLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueBTDecorator_CheckLowHealth : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	
	// Threshold that is considered 'low health' (e.g. 0.3 is 30% of maximum hitpoints)
	UPROPERTY(EditAnywhere, Category="AI", meta = (ClampMin="0.0", ClampMax="1.0"))
	float LowHealthPercent = 0.3f;
	
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
