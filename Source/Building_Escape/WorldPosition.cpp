// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
//#include "Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//FString Log = TEXT("Hello!");
	//FString* PrtLog = &Log;

	////int32 Len = Log.Len();
	////int32 PrtLen = PrtLog->Len(); //(*PrtLog).Len();

	//UE_LOG(LogTemp, Warning, TEXT("%s"), **PrtLog);
	// ...
	//FString ActorName = GetOwner()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("Actor name is %s"), *GetOwner()->GetName());
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

