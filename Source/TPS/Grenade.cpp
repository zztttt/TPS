// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/PlayerCameraManager.h"
#include "Grenade.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(FName("GrenadeMesh"));
	MaxAmmo = 3;
	CurrentAmmo = 3;
	AmmoPerShot = 1;
	TraceDistance = 100000;
	GrenadeSocket = FName("weapon_hand");
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGrenade::CalculateFireInfo(FVector& Location, FVector& Direction)
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (CameraManager)
	{
		Location = Mesh->GetSocketLocation(GrenadeSocket);
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector CameraDirection = CameraManager->GetCameraRotation().Vector();
		Direction = ((CameraLocation + CameraDirection * TraceDistance) - Location).GetSafeNormal();
		return true;
	}
	return false;
}

void AGrenade::StartThrow()
{
	ConsumeAmmo();

	FVector Location, Direction;
	CalculateFireInfo(Location, Direction);

	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		bool bNoCollisionFail = true;
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = bNoCollisionFail ? \
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn : \
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		FRotator rotation = UKismetMathLibrary::MakeRotFromX(Direction);
		auto x = World->SpawnActor<AGrenadeProjectile>(ProjectileClass, Location, rotation, ActorSpawnParams);
	}
}


void AGrenade::ConsumeAmmo()
{
	CurrentAmmo = FMath::Max(0, CurrentAmmo - AmmoPerShot);
}

