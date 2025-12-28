// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY(EditAnywhere, Category="Explosive Barrel")
	float ExplosionDelay = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel")
	TObjectPtr<UNiagaraSystem> BurningEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel")
	TObjectPtr<USoundBase> BurningSound;
	
	UPROPERTY(EditDefaultsOnly, Category="Explosive Barrel")
	TObjectPtr<USoundBase> ExplosionSound;
	
	void Explode();
	
	bool bExploded = false;
	
	FTimerHandle ExplosionTimerHandle;
	
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp = nullptr;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	virtual void PostInitializeComponents() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
