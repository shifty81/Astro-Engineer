// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroShipAssembly.h"

AAstroShipAssembly::AAstroShipAssembly()
{
	PrimaryActorTick.bCanEverTick = true;

	RootModule = nullptr;
	bIsComplete = false;
	bRequiresCockpit = true;
	bRequiresEngine = true;
	bRequiresFuelTank = true;
}

void AAstroShipAssembly::BeginPlay()
{
	Super::BeginPlay();
}

void AAstroShipAssembly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AAstroShipAssembly::AddModule(TSubclassOf<AAstroShipModule> ModuleClass, AAstroShipModule* ParentModule, int32 ConnectionIndex)
{
	if (!ModuleClass)
		return false;

	// Spawn the module
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AAstroShipModule* NewModule = GetWorld()->SpawnActor<AAstroShipModule>(ModuleClass, GetActorLocation(), GetActorRotation(), SpawnParams);

	if (!NewModule)
		return false;

	// If no parent, this is the root module
	if (!ParentModule)
	{
		if (!RootModule)
		{
			RootModule = NewModule;
			ShipModules.Add(NewModule);
			return true;
		}
		return false; // Root already exists
	}

	// Attach to parent module
	if (ParentModule->AttachModule(NewModule, ConnectionIndex))
	{
		ShipModules.Add(NewModule);
		return true;
	}

	// Failed to attach, destroy the module
	NewModule->Destroy();
	return false;
}

void AAstroShipAssembly::RemoveModule(AAstroShipModule* Module)
{
	if (!Module || Module == RootModule)
		return;

	// Detach from parent
	AActor* ParentActor = Module->GetAttachParentActor();
	if (AAstroShipModule* ParentModule = Cast<AAstroShipModule>(ParentActor))
	{
		ParentModule->DetachModule(Module);
	}

	// Remove from list
	ShipModules.Remove(Module);

	// Destroy the module
	Module->Destroy();
}

float AAstroShipAssembly::CalculateTotalMass() const
{
	float TotalMass = 0.0f;
	for (AAstroShipModule* Module : ShipModules)
	{
		if (Module)
		{
			TotalMass += Module->Mass;
		}
	}
	return TotalMass;
}

float AAstroShipAssembly::CalculatePowerBalance() const
{
	float TotalGeneration = 0.0f;
	float TotalConsumption = 0.0f;

	for (AAstroShipModule* Module : ShipModules)
	{
		if (Module)
		{
			TotalGeneration += Module->PowerGeneration;
			TotalConsumption += Module->PowerConsumption;
		}
	}

	return TotalGeneration - TotalConsumption;
}

bool AAstroShipAssembly::IsShipFlyable() const
{
	if (ShipModules.Num() == 0)
		return false;

	bool bHasCockpit = false;
	bool bHasEngine = false;
	bool bHasFuelTank = false;

	for (AAstroShipModule* Module : ShipModules)
	{
		if (Module)
		{
			switch (Module->ModuleType)
			{
			case EShipModuleType::Cockpit:
				bHasCockpit = true;
				break;
			case EShipModuleType::Engine:
				bHasEngine = true;
				break;
			case EShipModuleType::FuelTank:
				bHasFuelTank = true;
				break;
			default:
				break;
			}
		}
	}

	// Check required modules
	if (bRequiresCockpit && !bHasCockpit)
		return false;
	if (bRequiresEngine && !bHasEngine)
		return false;
	if (bRequiresFuelTank && !bHasFuelTank)
		return false;

	// Check power balance
	if (CalculatePowerBalance() < 0.0f)
		return false;

	return true;
}

void AAstroShipAssembly::FinalizeShip()
{
	if (!IsShipFlyable())
		return;

	bIsComplete = true;
	
	// Here you would convert the assembly into a flyable ship pawn
	// This would involve creating physics constraints, setting up controls, etc.
	
	OnShipFinalized.Broadcast();
}
