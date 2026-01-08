// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstroInventoryComponent.generated.h"

class UAstroItemData;

/**
 * Inventory item structure
 */
USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	FInventoryItem()
		: ItemID(NAME_None)
		, ItemName(FText::GetEmpty())
		, Quantity(0)
		, MaxStackSize(99)
		, Icon(nullptr)
	{}
};

/**
 * Inventory Component for managing player items
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASTROENGINEER_API UAstroInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAstroInventoryComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Add item to inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(FName ItemID, int32 Quantity = 1);

	/** Remove item from inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(FName ItemID, int32 Quantity = 1);

	/** Check if inventory has item */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(FName ItemID, int32 Quantity = 1) const;

	/** Get item quantity */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetItemQuantity(FName ItemID) const;

	/** Get all inventory items */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventoryItem> GetInventoryItems() const { return InventoryItems; }

	/** Clear entire inventory */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearInventory();

protected:
	virtual void BeginPlay() override;

	/** Find item in inventory */
	FInventoryItem* FindItem(FName ItemID);

public:	
	/** Maximum inventory slots */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventorySlots;

	/** Current inventory items */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItem> InventoryItems;

	/** Delegate called when inventory changes */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryChanged OnInventoryChanged;
};
