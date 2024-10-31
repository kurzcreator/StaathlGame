// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "SGObjectiveActor.generated.h"

class USphereComponent;
class UNiagaraSystem;

UCLASS()
class STEALTHGAME_API ASGObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASGObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComponent; // for collision

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UNiagaraSystem* FXNiagara;

	virtual void BeginPlay() override;

	void PlayEffect();

public:	
	// Called every frame
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
