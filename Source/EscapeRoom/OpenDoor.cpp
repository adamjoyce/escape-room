// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "OpenDoor.h"
#include "Grabber.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() : DoorTrigger(nullptr),
						 TriggerMass(30.0f),
						 Owner(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts.
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!DoorTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("Door missing trigger zone"));
	}
}


// Called every frame.
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Opens/closes the door based on total mass in trigger zone.
	if (GetTotalMassOfActorOnPlate() > TriggerMass)
		OnOpen.Broadcast();
	else 
		OnClose.Broadcast();
}

// Returns the total mass in the trigger volume.
float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.0f;

	/// Get all actors in the door trigger zone.
	TArray<AActor*> OverlappingActors;
	if (!DoorTrigger) { return 0.0f; }
	DoorTrigger->GetOverlappingActors(OverlappingActors);

	/// Calculate combined mass of overlapping actors.
	FString OverlappingNames;
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s in trigger zone"), *(Actor->GetName()));
	}

	return TotalMass;
}

