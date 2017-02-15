// Copyright Adam Joyce 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties.
	UOpenDoor();

	// Called when the game starts.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Open door angle.
	UPROPERTY(EditAnywhere)
	float OpenAngle;

	// The delay before the door closes once opened.
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay;

	// Trigger volume for the door.
	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger;

	// The door with this component class attached.
	AActor* Owner;

	// Time since the game began at which the door was last open.
	float LastDoorOpenTime;

	// True if the door is open.
	bool IsDoorOpen;

	// Returns the total mass in the trigger volume.
	float GetTotalMassOfActorOnPlate();

	// Opens the door.
	void OpenDoor();

	// Closes the door.
	void CloseDoor();
};
