// Copyright Alexey Bekhmatov 2022

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;


    // ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
    Super::BeginPlay();
    OriginalYaw = GetOwner()->GetActorRotation().Yaw;
    TargetYaw = OriginalYaw + YawAngle;

    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s has OpenDoor componetn but no PressurePlate set"), *GetOwner()->GetName());
    }

    ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
    {
        OpenDoor(DeltaTime);
        DoorLastOpened = GetWorld()->GetTimeSeconds();
    }
    else
    {
        if (GetWorld()->GetTimeSeconds() > DoorLastOpened + DoorCloseDelay)
            CloseDoor(DeltaTime);
    }
}

void UOpenDoor::OpenDoor(float DeltaTime) const
{
    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    float NextYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, OpenAngleSpeed);
    FRotator OpenDoor(0, NextYaw, 0);
    GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::CloseDoor(float DeltaTime) const
{
    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    float NextYaw = FMath::FInterpConstantTo(CurrentYaw, OriginalYaw, DeltaTime, CloseAngleSpeed);
    FRotator CloseDoor(0, NextYaw, 0);
    GetOwner()->SetActorRotation(CloseDoor);
}

