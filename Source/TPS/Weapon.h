// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponProjectile.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TPS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnProjectTile();

	UFUNCTION(BlueprintCallable)
	bool CalculateFireInfo(FVector& Location, FVector& Direction);

	UFUNCTION(BlueprintCallable)
	float GetRemainingPercent();

	UFUNCTION(BlueprintCallable)
	bool IsReloading();

	UFUNCTION(BlueprintCallable)
	void reloading();

	void ConsumeAmmo();


	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere)
	int32 AmmoPerShot;

	UPROPERTY(EditAnywhere)
	int32 TraceDistance;

	UPROPERTY(EditAnywhere)
	FName WeaponSocket;
};
