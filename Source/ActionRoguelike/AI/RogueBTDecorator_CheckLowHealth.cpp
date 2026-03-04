// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTDecorator_CheckLowHealth.h"
#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"


bool URogueBTDecorator_CheckLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	// BT should have been stopped already with no pawn
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		return (ActionComp->GetHealth() / ActionComp->GetMaxHealth()) < LowHealthPercent;
	}
	
	return false;
}

