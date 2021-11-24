// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrenadeProjectile.h"
#include "Grenade.generated.h"

UCLASS()
class AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AGrenadeProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	FName GrenadeSocket;

	UPROPERTY(EditAnywhere)
	int32 TraceDistance;

	UPROPERTY(EditAnywhere)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere)
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere)
	int32 AmmoPerShot;

	UFUNCTION(BlueprintCallable)
	void StartThrow();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnProjectTile();

	UFUNCTION(BlueprintCallable)
	bool CalculateFireInfo(FVector& Location, FVector& Direction);

	void ConsumeAmmo();
};
