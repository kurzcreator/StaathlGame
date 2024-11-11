// Fill out your copyright notice in the Description page of Project Settings.


#include "SGExtractionZone.h"

#include "Components/BoxComponent.h"

// Sets default values
ASGExtractionZone::ASGExtractionZone()
{
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetHiddenInGame(false);
	OverlapComponent->SetBoxExtent(FVector(200));
	RootComponent = OverlapComponent;
}

void ASGExtractionZone::BeginPlay()
{
	Super::BeginPlay();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGExtractionZone::HandleOverlap);
}

void ASGExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("ASGExtractionZone::HandleOverlap %s"), *OtherActor->GetName());
}
