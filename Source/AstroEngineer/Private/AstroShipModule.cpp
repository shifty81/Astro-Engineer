// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroShipModule.h"
#include "Components/StaticMeshComponent.h"

AAstroShipModule::AAstroShipModule()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create module mesh
	ModuleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModuleMesh"));
	RootComponent = ModuleMesh;

	// Initialize defaults
	ModuleType = EShipModuleType::Hull;
	Mass = 100.0f;
	PowerConsumption = 0.0f;
	PowerGeneration = 0.0f;
	CrewCapacity = 0;
}

void AAstroShipModule::BeginPlay()
{
	Super::BeginPlay();
}

void AAstroShipModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAstroShipModule::AttachModule(AAstroShipModule* Module, int32 ConnectionIndex)
{
	if (!Module || ConnectionIndex < 0 || ConnectionIndex >= ConnectionPoints.Num())
		return false;

	FModuleConnectionPoint& ConnectionPoint = ConnectionPoints[ConnectionIndex];
	
	// Check if connection point is already occupied
	if (ConnectionPoint.bIsOccupied)
		return false;

	// Check if module type is compatible
	if (Module->ModuleType != ConnectionPoint.AcceptedModuleType && 
		ConnectionPoint.AcceptedModuleType != EShipModuleType::Hull)
		return false;

	// Attach the module
	FAttachmentTransformRules AttachRules(EAttachmentRule::KeepRelative, false);
	Module->AttachToActor(this, AttachRules);
	
	// Set relative transform
	Module->SetActorRelativeLocation(ConnectionPoint.RelativeLocation);
	Module->SetActorRelativeRotation(ConnectionPoint.RelativeRotation);

	// Mark connection as occupied
	ConnectionPoint.bIsOccupied = true;
	AttachedModules.Add(Module);

	return true;
}

void AAstroShipModule::DetachModule(AAstroShipModule* Module)
{
	if (!Module)
		return;

	// Find and free the connection point
	for (FModuleConnectionPoint& ConnectionPoint : ConnectionPoints)
	{
		if (ConnectionPoint.bIsOccupied)
		{
			// Check if this is the right module (simplified)
			ConnectionPoint.bIsOccupied = false;
		}
	}

	// Detach the module
	FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, false);
	Module->DetachFromActor(DetachRules);
	
	AttachedModules.Remove(Module);
}
