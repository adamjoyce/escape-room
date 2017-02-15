// Copyright Adam Joyce 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties.
	UOpenDoor();

	// Open door event for blueprint.
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	// Close door event for blueprint.
	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

	// Called when the game starts.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Trigger volume for the door.
	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger;

	// Total mass needed to trigger door.
	UPROPERTY(EditAnywhere)
	float TriggerMass;

	// The door with this component class attached.
	AActor* Owner;

	// Returns the total mass in the trigger volume.
	float GetTotalMassOfActorOnPlate();
};
