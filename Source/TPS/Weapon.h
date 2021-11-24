// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	void ConsumeAmmo();

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere)
	int32 AmmoPerShot;

	UPROPERTY(EditAnywhere)
	int32 TraceDistance;

	UPROPERTY(EditAnywhere)
	FName MuzzleSocket;
};
