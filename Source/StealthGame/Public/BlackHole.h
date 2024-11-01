// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"


class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class STEALTHGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()

public:
	ABlackHole();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Components")
	float GravityForce = -4500.0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	float RadiusGravitySphere = 4000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	float RadiusHorizonEventSphere = 190;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> GravitySphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> EventHorizonSphere;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void DestroyGravityObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
