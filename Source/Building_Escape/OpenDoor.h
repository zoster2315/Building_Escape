// Copyright Alexey Bekhmatov 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UOpenDoor();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void OpenDoor(float DeltaTime) const;
    void CloseDoor(float DeltaTime) const;

private:
    float OriginalYaw = 0.f;
    UPROPERTY(EditAnywhere)
        float YawAngle = -90.f;
    float TargetYaw = 0.f;
    UPROPERTY(EditAnywhere)
        ATriggerVolume* PressurePlate;

    UPROPERTY(EditAnywhere)
        APawn* ActorThatOpen;
};
