// Fill out your copyright notice in the Description page of Project Settings.


#include "SGObjectiveActor.h"

#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ASGObjectiveActor::ASGObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

// Called every frame
void ASGObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASGObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	UE_LOG(LogTemp, Display, TEXT("Start Overlap"));
	PlayEffect();
}

