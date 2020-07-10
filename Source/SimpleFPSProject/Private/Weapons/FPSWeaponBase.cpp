// Fill out your copyright notice in the Description page of Project Settings.

#include "..\..\Public\Weapons\FPSWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
AFPSWeaponBase::AFPSWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh for the visual representation
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;


	RateOfFire = 600.f;
}

// Called when the game starts or when spawned
void AFPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60.0f / RateOfFire;
	
}

void AFPSWeaponBase::Fire()
{
	// Find out who's holding the weapon
	AActor* WeaponOwner = GetOwner();
	if (WeaponOwner)
	{
		// Get Actor eyes transform
		FVector EyeLocation;
		FRotator EyeRotation;
		WeaponOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		FVector ShootDirection = EyeRotation.Vector();
		FVector TracerEnd = EyeLocation + (ShootDirection * 10000);


		// Transform MuzzleOffset from camera space to world space
		FVector MuzzleLocation = EyeLocation + FTransform(EyeRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = EyeRotation;

		// skew the aim to be slightly upwards
		// MuzzleRotation.Pitch += 10.0f;

		// @TODO: maybe add some bullet spread


		// Line Tracing
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(WeaponOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bReturnPhysicalMaterial = true;
		QueryParams.bTraceComplex = true;

		FVector TracerEndPoint = TracerEnd;
		FHitResult HitResults;
		if (GetWorld()->LineTraceSingleByChannel(HitResults, EyeLocation, TracerEnd, ECollisionChannel::ECC_Visibility, QueryParams))
		{
			// Get the Actor we hit
			AActor* HitActor = HitResults.GetActor();


			TracerEndPoint = HitResults.ImpactPoint;
		}

		// Draw a line from the trace start (eye_location) to trace end (Trace_end).
		DrawDebugLine(GetWorld(), EyeLocation, TracerEnd, FColor::Green, false, 1.0, 0, 1.0f);

		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, WeaponMesh, "Muzzle");
		}

		// Keep track of time since last shot
		LastTimeFired = GetWorld()->TimeSeconds;

	}
}

// Called every frame
void AFPSWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSWeaponBase::StartFiring()
{
	float FirstDelay = FMath::Max(LastTimeFired + TimeBetweenShots - GetWorld()->TimeSeconds, 0.0f);

	GetWorldTimerManager().SetTimer(TimerHandleTimeBetweenShots,this, &AFPSWeaponBase::Fire,TimeBetweenShots,true,FirstDelay);
}

void AFPSWeaponBase::StopFiring()
{
	GetWorldTimerManager().ClearTimer(TimerHandleTimeBetweenShots);
}

