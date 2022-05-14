// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

/*
일단은 HealthComponent, Explode, RadialForceComponent
0이 되면 색이 바뀌고 particle, RadialForce, 배럴을 위로
*/

class USHealthComponent;
class URadialForceComponent;

UCLASS()
class COOPGAME_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* RadialForceComp;

	bool bExploded;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	float ExplosionImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem* ExplodeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UMaterialInterface* ExplodedMaterial;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* BarrelHealthComp, float Health, float HealthDeltaconst, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void Explode();
};
