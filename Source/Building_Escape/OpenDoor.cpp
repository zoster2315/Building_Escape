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
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
    UE_LOG(LogTemp, Warning, TEXT("Target Yaw is: %f"), TargetYaw);
    UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

    float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
    float NextYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45); /*startingYaw, targetYaw*, 0-1*/
    UE_LOG(LogTemp, Warning, TEXT("Target Yaw is: %f"), NextYaw);

    FRotator OpenDoor(0, NextYaw, 0);
    GetOwner()->SetActorRotation(OpenDoor);
}

