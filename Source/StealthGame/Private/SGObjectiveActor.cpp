// Fill out your copyright notice in the Description page of Project Settings.


#include "SGObjectiveActor.h"

#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "StealthGame/StealthGameCharacter.h"

// Sets default values
ASGObjectiveActor::ASGObjectiveActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(MeshComponent);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASGObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASGObjectiveActor::PlayEffect()
{
	auto NiagaraEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXNiagara, GetActorLocation());
}


void ASGObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Display, TEXT("Start Overlap"));
	PlayEffect();
	auto StealthCharacter = Cast<AStealthGameCharacter>(OtherActor);
	
	if (StealthCharacter)
	{
		StealthCharacter->IsCarryingObjective = true;
		Destroy();
	}
}

