// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

#include "Components/SphereComponent.h"
#include "UObject/ObjectMacros.h"

// Sets default values
ABlackHole::ABlackHole()
{
	bAllowTickBeforeBeginPlay = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(MeshComponent);

	GravitySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("GravitySphereComponent"));
	GravitySphereComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	GravitySphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	GravitySphereComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	
	GravitySphereComponent->SetupAttachment(GetRootComponent());
}

void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	GravitySphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::GravityCapture);
	GravitySphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABlackHole::EndGravityCapture);
}

void ABlackHole::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	UE_LOG(LogTemp, Display, TEXT("Gravity Object Detected -----------%s"), *OtherActor->GetName());
}

void ABlackHole::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABlackHole::DestroyGravityObject(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


void ABlackHole::GravityCapture(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Gravity Object Detected%s"), *OtherActor->GetName());
}

void ABlackHole::EndGravityCapture(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("Gravity Object Detected ending %s"), *OtherActor->GetName());
}
