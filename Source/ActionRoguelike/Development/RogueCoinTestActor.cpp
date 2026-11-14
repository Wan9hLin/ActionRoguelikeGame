// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCoinTestActor.h"

#include "NavigationSystem.h"
#include "Pickup/RogueCoinPickupSubsystem.h"

ARogueCoinTestActor::ARogueCoinTestActor()
{
	DefaultSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComp"));
	RootComponent = DefaultSceneComp;
}

void ARogueCoinTestActor::SpawnCoins(int32 SpawnCount)
{
	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(this);
	FVector ActorLoaction = GetActorLocation();
	
	for (int32 i = 0; i < SpawnCount; i++)
	{
		FNavLocation NavLocation;
		NavSystem->GetRandomPointInNavigableRadius(ActorLoaction, 1024, NavLocation);
		
		CoinLocations.Add(NavLocation.Location);
		CoinAmounts.Add(10);
		
	}	
	
	URogueCoinPickupSubsystem* CoinSystem = GetWorld()->GetSubsystem<URogueCoinPickupSubsystem>();
	
	CoinSystem->AddCoinPickups(CoinLocations, CoinAmounts);
}


