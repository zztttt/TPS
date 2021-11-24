// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));

	MaxAmmo = 1024;
	CurrentAmmo = MaxAmmo;
	AmmoPerShot = 1;
	TraceDistance = 100000;
	MuzzleSocket = FName("Muzzle");
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::StartFire()
{
	ConsumeAmmo();
	SpawnProjectTile();
}

void AWeapon::StopFire()
{

}


bool AWeapon::CalculateFireInfo(FVector& Location, FVector& Direction)
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (CameraManager)
	{
		Location = Mesh->GetSocketLocation(MuzzleSocket);
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FVector CameraDirection = CameraManager->GetCameraRotation().Vector();
		Direction = ((CameraLocation + CameraDirection * TraceDistance) - Location).GetSafeNormal();
		return true;
	}
	return false;
}

void AWeapon::ConsumeAmmo()
{
	CurrentAmmo = FMath::Max(0, CurrentAmmo - AmmoPerShot);
}
