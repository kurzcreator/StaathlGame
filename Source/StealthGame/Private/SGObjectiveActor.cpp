// Fill out your copyright notice in the Description page of Project Settings.


#include "SGObjectiveActor.h"

#include "Components/SphereComponent.h"

// Sets default values
ASGObjectiveActor::ASGObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASGObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

