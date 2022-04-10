// Copyright Alexey Bekhmatov 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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
    void OpenDoor(float DeltaTime);
    void CloseDoor(float DeltaTime);
    float TotalMassOfActors() const;
    void FindAudioComponent();
    void FindPressurePlate();

    bool OpenDoorSound = false;
    bool CloseDoorSound = true;

private:
    float OriginalYaw = 0.f;
    UPROPERTY(EditAnywhere)
        float YawAngle = -90.f;
    float TargetYaw = 0.f;

    UPROPERTY(EditAnywhere)
        float OpenAngleSpeed = 90.f;
    UPROPERTY(EditAnywhere)
        float CloseAngleSpeed = 180.f;
    float DoorLastOpened = 0.f;
    UPROPERTY(EditAnywhere)
        float DoorCloseDelay = 1.5f;

    UPROPERTY(EditAnywhere)
        ATriggerVolume* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
        float MassToOpen = 50.f;

    UPROPERTY()
        UAudioComponent* AudioComponent = nullptr;
};
