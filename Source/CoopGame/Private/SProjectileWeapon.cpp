// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileWeapon.h"

void ASProjectileWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (ProjectileClass && MyOwner)
	{
		FVector EyeLocation;		// GetActorLocation()
		FRotator EyeRotation;		// GetActorRotation()
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);
		// FRotator MuzzleRotation = MeshComp->GetSocketRotation("MuzzleFlashSocket");
		FRotator MuzzleRotation = EyeRotation;

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParams);
	}
}
