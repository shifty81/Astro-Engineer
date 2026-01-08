// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroInventoryComponent.h"

UAstroInventoryComponent::UAstroInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxInventorySlots = 40; // 8x5 grid default
}

void UAstroInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAstroInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UAstroInventoryComponent::AddItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0)
		return false;

	// Try to find existing item and stack
	FInventoryItem* ExistingItem = FindItem(ItemID);
	if (ExistingItem)
	{
		if (ExistingItem->Quantity + Quantity <= ExistingItem->MaxStackSize)
		{
			ExistingItem->Quantity += Quantity;
			OnInventoryChanged.Broadcast();
			return true;
		}
		else
		{
			// TODO: Handle overflow to new stack
			int32 RemainingSpace = ExistingItem->MaxStackSize - ExistingItem->Quantity;
			ExistingItem->Quantity = ExistingItem->MaxStackSize;
			Quantity -= RemainingSpace;
		}
	}

	// Check if we have space for new item
	if (InventoryItems.Num() >= MaxInventorySlots)
		return false;

	// Add new item
	FInventoryItem NewItem;
	NewItem.ItemID = ItemID;
	NewItem.Quantity = Quantity;
	// TODO: Load item data from data table
	InventoryItems.Add(NewItem);

	OnInventoryChanged.Broadcast();
	return true;
}

bool UAstroInventoryComponent::RemoveItem(FName ItemID, int32 Quantity)
{
	if (ItemID.IsNone() || Quantity <= 0)
		return false;

	FInventoryItem* Item = FindItem(ItemID);
	if (!Item || Item->Quantity < Quantity)
		return false;

	Item->Quantity -= Quantity;
	
	// Remove item if quantity is 0
	if (Item->Quantity <= 0)
	{
		InventoryItems.RemoveAll([ItemID](const FInventoryItem& Item) {
			return Item.ItemID == ItemID;
		});
	}

	OnInventoryChanged.Broadcast();
	return true;
}

bool UAstroInventoryComponent::HasItem(FName ItemID, int32 Quantity) const
{
	return GetItemQuantity(ItemID) >= Quantity;
}

int32 UAstroInventoryComponent::GetItemQuantity(FName ItemID) const
{
	for (const FInventoryItem& Item : InventoryItems)
	{
		if (Item.ItemID == ItemID)
			return Item.Quantity;
	}
	return 0;
}

void UAstroInventoryComponent::ClearInventory()
{
	InventoryItems.Empty();
	OnInventoryChanged.Broadcast();
}

FInventoryItem* UAstroInventoryComponent::FindItem(FName ItemID)
{
	for (FInventoryItem& Item : InventoryItems)
	{
		if (Item.ItemID == ItemID)
			return &Item;
	}
	return nullptr;
}
