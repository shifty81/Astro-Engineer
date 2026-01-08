// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AstroShipModule.h"
#include "AstroShipAssembly.generated.h"

/**
 * Ship assembly manager for building modular spacecraft
 */
UCLASS()
class ASTROENGINEER_API AAstroShipAssembly : public AActor
{
	GENERATED_BODY()
	
public:	
	AAstroShipAssembly();

	virtual void Tick(float DeltaTime) override;

	/** Add module to ship */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	bool AddModule(TSubclassOf<AAstroShipModule> ModuleClass, AAstroShipModule* ParentModule, int32 ConnectionIndex);

	/** Remove module from ship */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	void RemoveModule(AAstroShipModule* Module);

	/** Get all ship modules */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	TArray<AAstroShipModule*> GetAllModules() const { return ShipModules; }

	/** Calculate total ship mass */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	float CalculateTotalMass() const;

	/** Calculate total power balance */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	float CalculatePowerBalance() const;

	/** Check if ship is flyable */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	bool IsShipFlyable() const;

	/** Finalize ship assembly and make it controllable */
	UFUNCTION(BlueprintCallable, Category = "Ship Assembly")
	void FinalizeShip();

protected:
	virtual void BeginPlay() override;

public:	
	/** Root module (usually cockpit) */
	UPROPERTY(BlueprintReadOnly, Category = "Ship Assembly")
	AAstroShipModule* RootModule;

	/** All modules in the ship */
	UPROPERTY(BlueprintReadOnly, Category = "Ship Assembly")
	TArray<AAstroShipModule*> ShipModules;

	/** Ship name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Assembly")
	FText ShipName;

	/** Is ship completed and ready to fly */
	UPROPERTY(BlueprintReadOnly, Category = "Ship Assembly")
	bool bIsComplete;

	/** Minimum required modules for flight */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Assembly")
	bool bRequiresCockpit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Assembly")
	bool bRequiresEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship Assembly")
	bool bRequiresFuelTank;

	/** Delegate called when ship is finalized */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShipFinalized);
	UPROPERTY(BlueprintAssignable, Category = "Ship Assembly")
	FOnShipFinalized OnShipFinalized;
};
