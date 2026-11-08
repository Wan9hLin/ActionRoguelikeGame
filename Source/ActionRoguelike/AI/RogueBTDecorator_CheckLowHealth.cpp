// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTDecorator_CheckLowHealth.h"
#include "AIController.h"
#include "SharedGameplayTag.h"
#include "ActionSystem/RogueActionSystemComponent.h"


bool URogueBTDecorator_CheckLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	// BT should have been stopped already with no pawn
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		float HealthFraction = ActionComp->GetAttributeValue(SharedGameplayTag::Attribute_Health) / 
			ActionComp->GetAttributeValue(SharedGameplayTag::Attribute_HealthMax);
		
		return HealthFraction < LowHealthPercent;
	}
	
	return false;
}

