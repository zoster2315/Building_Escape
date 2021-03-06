// Copyright Alexey Bekhmatov 2022


#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();

    FindPhysicsHandle();
    SetUpInputComponent();
}


void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Graber pressed"));

    FHitResult HitResult = GetFirstPhysicsBodyInReach();

    if (HitResult.GetActor())
    {
        if (!PhysicsHandle)
        {
            return;
        }
        PhysicsHandle->GrabComponentAtLocation(HitResult.GetComponent(), NAME_None, HitResult.Location);
    }
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Grabber released"));

    if (!PhysicsHandle)
    {
        return;
    }
    if (PhysicsHandle->GrabbedComponent)
        PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component found on %s"), *GetOwner()->GetName())
    }
}

void UGrabber::SetUpInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input component founded on %s"), *GetOwner()->GetName());
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PhysicsHandle)
    {
        return;
    }

    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(GetPlayersReach());
    }

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    FHitResult Hit;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(OUT Hit, GetPlayerWorldPos(), GetPlayersReach(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

    AActor* HitedActor = Hit.GetActor();
    if (HitedActor != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hited actor: %s"), *HitedActor->GetName());
    }

    return Hit;

}

FVector UGrabber::GetPlayersReach() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

}

FVector UGrabber::GetPlayerWorldPos() const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

    return PlayerViewPointLocation;
}


