// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeaponBase.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;

UCLASS()
class SIMPLEFPSPROJECT_API AFPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Function that handles the weapon firing */
	virtual void Fire();


protected:

	/* Visual representation of the weapon */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<UDamageType> DamageType;

	/* Muzzle flash particle that will appear with each shot */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
	UParticleSystem* MuzzleFlash;

	/* Bullets per minute */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	/* Records time in between shots */
	FTimerHandle TimerHandle_TimeBetweenShots;
	float LastTimeFired;

	/* derived from RateOfFire */
	float TimeBetweenShots;

	/* Stores the timer that is sets inbetween shots and will also be cleared inbetween shots */
	FTimerHandle TimerHandleTimeBetweenShots;

	/* Gun muzzle's offset from the camera location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartFiring();
	virtual void StopFiring();
};
