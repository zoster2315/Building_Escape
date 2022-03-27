// Copyright Alexey Bekhmatov 2022


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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
        OpenDoor(DeltaTime);
}

void UOpenDoor::OpenDoor(float DeltaTime) const
{
    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    float NextYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45);
    FRotator OpenDoor(0, NextYaw, 0);
    GetOwner()->SetActorRotation(OpenDoor);
}
