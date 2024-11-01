// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "UObject/ObjectMacros.h"

// Sets default values
ABlackHole::ABlackHole()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(MeshComponent);

	GravitySphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("GravitySphereComponent"));
	GravitySphereComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	GravitySphereComponent->SetCollisionResponseToChannels(ECollisionResponse::ECR_Overlap);
	GravitySphereComponent->SetSphereRadius(4000);
	GravitySphereComponent->SetupAttachment(MeshComponent);


	EventHorizonSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Event Horizon"));
	EventHorizonSphere->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	EventHorizonSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	EventHorizonSphere->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	EventHorizonSphere->SetSphereRadius(500);
	EventHorizonSphere->SetupAttachment(MeshComponent);
}

void ABlackHole::BeginPlay()
{
	Super::BeginPlay();

	EventHorizonSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::DestroyGravityObject);
}

void ABlackHole::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<UPrimitiveComponent*> OverlappedComponents;
	GravitySphereComponent->GetOverlappingComponents(OverlappedComponents);

	if (OverlappedComponents.Num() > 0)
	{
		for (UPrimitiveComponent* OverlappedComponent : OverlappedComponents)
		{
			if (OverlappedComponent && OverlappedComponent->IsSimulatingPhysics())
			{
				// UE_LOG(LogTemp, Display, TEXT("TUT"));
				OverlappedComponent->AddRadialForce(GetActorLocation(), GravitySphereComponent->GetScaledSphereRadius(),
				                                    GravityForce, RIF_Constant, true);
			}
		}
	}
}

void ABlackHole::DestroyGravityObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	
	UE_LOG(LogTemp, Display, TEXT("Destroy GravityObject"));
	if (!OtherActor) return;
	
	OtherActor->Destroy();
}
