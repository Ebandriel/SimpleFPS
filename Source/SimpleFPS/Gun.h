// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"
class UParticleSystemComponent;

UCLASS()
class SIMPLEFPS_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	void PullTrigger();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Efects")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category="Efects")
	TArray<USoundBase*> MuzzleSounds;
	UPROPERTY(EditAnywhere, Category="Efects")
	UParticleSystem* Impact;
	UPROPERTY(EditAnywhere, Category="Efects")
	TArray<USoundBase*> ImpactSounds;
	UPROPERTY(EditDefaultsOnly, Category="Balistic Stats")
	float MaxRange = 1000.0f;
	UPROPERTY(EditDefaultsOnly, Category="Balistic Stats")
	float Damage = 50.0f;

	bool GunTrace(FHitResult& Target, FVector& ShotDirection);
	AController* GetOwnerController() const;

};
