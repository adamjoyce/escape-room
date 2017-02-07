// Copyright Adam Joyce 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties.
	UGrabber();

	// Called when the game starts.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// The distance the player can grab objects in cm.
	UPROPERTY(EditAnywhere)
	float Reach;

	// The player controller of the pawn this component is attached to.
	APlayerController* PlayerController;
};
