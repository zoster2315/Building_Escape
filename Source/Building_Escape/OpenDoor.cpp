// Copyright Alexey Bekhmatov 2022

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/AudioComponent.h"
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

    FindPressurePlate();
    FindAudioComponent();
}

void UOpenDoor::FindPressurePlate()
{
    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s has OpenDoor componetn but no PressurePlate set"), *GetOwner()->GetName());
    }
}

void UOpenDoor::FindAudioComponent()
{
    AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
    if (!AudioComponent)
        UE_LOG(LogTemp, Error, TEXT("$s Missing audio component!"), *GetOwner()->GetName())

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (PressurePlate && TotalMassOfActors() >= MassToOpen)
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

float UOpenDoor::TotalMassOfActors() const
{
    float mass = 0.f;
    if (!PressurePlate)
        return mass;
    TArray<AActor*> OverlapingActors;
    PressurePlate->GetOverlappingActors(OverlapingActors);
    for (AActor* OverlapingActor : OverlapingActors)
    {
        mass += OverlapingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return mass;
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    float NextYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, OpenAngleSpeed);
    FRotator OpenDoor(0, NextYaw, 0);
    GetOwner()->SetActorRotation(OpenDoor);

    CloseDoorSound = false;
    if (!AudioComponent)
        return;
    if (!OpenDoorSound)
    {
        AudioComponent->Play();
        OpenDoorSound = true;
    }
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    float NextYaw = FMath::FInterpConstantTo(CurrentYaw, OriginalYaw, DeltaTime, CloseAngleSpeed);
    FRotator CloseDoor(0, NextYaw, 0);
    GetOwner()->SetActorRotation(CloseDoor);

    OpenDoorSound = false;
    if (!AudioComponent)
        return;
    if (!CloseDoorSound)
    {
        AudioComponent->Play();
        CloseDoorSound = true;
    }
}

