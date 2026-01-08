// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AstroShipModule.generated.h"

/**
 * Ship module types
 */
UENUM(BlueprintType)
enum class EShipModuleType : uint8
{
	Cockpit,
	Engine,
	FuelTank,
	Weapon,
	Shield,
	Cargo,
	LifeSupport,
	Sensor,
	Hull
};

/**
 * Ship module connection point
 */
USTRUCT(BlueprintType)
struct FModuleConnectionPoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RelativeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EShipModuleType AcceptedModuleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOccupied;

	FModuleConnectionPoint()
		: RelativeLocation(FVector::ZeroVector)
		, RelativeRotation(FRotator::ZeroRotator)
		, AcceptedModuleType(EShipModuleType::Hull)
		, bIsOccupied(false)
	{}
};

/**
 * Base class for modular ship parts
 */
UCLASS()
class ASTROENGINEER_API AAstroShipModule : public AActor
{
	GENERATED_BODY()
	
public:	
	AAstroShipModule();

	virtual void Tick(float DeltaTime) override;

	/** Get module mesh */
	UFUNCTION(BlueprintCallable, Category = "Ship Module")
	UStaticMeshComponent* GetModuleMesh() const { return ModuleMesh; }

	/** Get connection points */
	UFUNCTION(BlueprintCallable, Category = "Ship Module")
	TArray<FModuleConnectionPoint> GetConnectionPoints() const { return ConnectionPoints; }

	/** Attach another module to this one */
	UFUNCTION(BlueprintCallable, Category = "Ship Module")
	bool AttachModule(AAstroShipModule* Module, int32 ConnectionIndex);

	/** Detach a module */
	UFUNCTION(BlueprintCallable, Category = "Ship Module")
	void DetachModule(AAstroShipModule* Module);

protected:
	virtual void BeginPlay() override;

public:	
	/** Module mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship Module")
	UStaticMeshComponent* ModuleMesh;

	/** Module type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module")
	EShipModuleType ModuleType;

	/** Module name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module")
	FText ModuleName;

	/** Connection points for attaching other modules */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module")
	TArray<FModuleConnectionPoint> ConnectionPoints;

	/** Attached child modules */
	UPROPERTY(BlueprintReadOnly, Category = "Ship Module")
	TArray<AAstroShipModule*> AttachedModules;

	/** Module stats */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module|Stats")
	float Mass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module|Stats")
	float PowerConsumption;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module|Stats")
	float PowerGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Module|Stats")
	int32 CrewCapacity;
};
