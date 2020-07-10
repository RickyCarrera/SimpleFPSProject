// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

// class declarations
class UCameraComponent;
class USkeletalMeshComponent;
class AFPSWeaponBase;

UCLASS()
class SIMPLEFPSPROJECT_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Handles input for moving forward and backward */
	UFUNCTION()
	void MoveForward(float value);

	/* Handles input for moving left and right */
	UFUNCTION()
	void MoveRight(float value);

	/* Sets jump flag when key is pressed */
	UFUNCTION()
	void StartJump();

	/* Clears the jump flag when key is released */
	UFUNCTION()
	void StopJump();

	/* Function that handles firing projectiles */
	// UFUNCTION()
	// void Fire();

	/* Function that handles firing our weapons */
	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartFiring();

	/* Function that handles stopping the firing of our weapons */
	UFUNCTION(BlueprintCallable, Category = "Player")
	void StopFiring();

protected:

	/* FPS camera */
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	/* First-person mesh (arms), visible only to the owning player */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	/* Gun muzzle's offset from the camera location */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	//FVector MuzzleOffset;

	/* Projectile class to spawn */
	// UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	// TSubclassOf<class AFPSProjectile> ProjectileClass;

	/* Weapon that we will attach to our Character */
	UPROPERTY(BlueprintReadOnly)
	AFPSWeaponBase* CurrentWeapon;

	/* The weapon class that we will have to choose from and have our character spawn with */
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class AFPSWeaponBase> StarterWeaponClass;

	/* Socket to attach weapon to*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Player")
	FName WeaponAttachedSocketName;
	 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*  retuns Pawn's eye location orginally but will return our camera_component location instead */
	virtual FVector GetPawnViewLocation() const override;

};
