// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "Components/SHealthComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../CoopGame.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	// Radial component affect barrel
	MeshComp->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	RootComponent = MeshComp;

	HealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ASExplosiveBarrel::OnHealthChanged);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = 250.f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bAutoActivate = false;
	RadialForceComp->bIgnoreOwningActor = true;

	ExplosionImpulse = 400.f;

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("Material'/Game/Challenges/M_ExplosiveBarrelExploded.M_ExplosiveBarrelExploded'"));
	if (FoundMaterial.Succeeded())
	{
		ExplodedMaterial = FoundMaterial.Object;
	}
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASExplosiveBarrel::OnHealthChanged(USHealthComponent* BarrelHealthComp, float Health, float HealthDeltaconst, 
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bExploded)
	{
		return;
	}

	if (Health <= 0)
	{
		bExploded = true;

		Explode();
	}
}

void ASExplosiveBarrel::Explode()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeEffect, GetActorLocation());

	RadialForceComp->FireImpulse();	

	MeshComp->SetSimulatePhysics(true);

	FVector BoostIntensity = FVector::UpVector * ExplosionImpulse;
	MeshComp->AddImpulse(BoostIntensity, NAME_None, true);

	MeshComp->SetMaterial(0, ExplodedMaterial);
}

