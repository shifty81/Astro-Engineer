# Astro Engineer - Architecture Documentation

## System Architecture Overview

Astro Engineer uses a component-based architecture built on Unreal Engine 5.7's framework. The game is structured around modular systems that communicate through events and direct references.

## Core Architecture Principles

### 1. Component-Based Design
- Major systems implemented as ActorComponents
- Allows flexible attachment to different actors
- Promotes reusability and testing
- Clear separation of concerns

### 2. Event-Driven Communication
- Delegates for loose coupling
- UI updates through events
- System notifications via broadcasts
- Reduces direct dependencies

### 3. Blueprint-C++ Hybrid
- Core logic in C++ for performance
- Gameplay tweaking in Blueprints
- Visual scripting for designers
- Best of both worlds approach

## System Hierarchy

```
AAstroGameMode
├── AAstroPlayerCharacter (Pawn)
│   ├── UCameraComponent
│   ├── UAstroInventoryComponent
│   ├── UAstroCraftingComponent
│   └── UAstroResearchComponent
│
AAstroShipAssembly (Actor)
├── AAstroShipModule (Root)
│   └── AAstroShipModule (Children)
│       └── AAstroShipModule (Grandchildren)
│           └── ...
```

## Component Details

### Player Character System

**AAstroPlayerCharacter**
- **Purpose**: Main player controller for on-foot gameplay
- **Key Features**:
  - Enhanced Input integration
  - First-person camera control
  - Interaction raycasting
  - Backpack interface management
  - Movement state management
- **Dependencies**: 
  - UAstroInventoryComponent
  - Enhanced Input System
  - UMG for UI
- **Communication**:
  - Direct component access for inventory/crafting
  - Input events from Enhanced Input
  - UI widget binding

**Input Flow**:
```
Enhanced Input Action → AAstroPlayerCharacter::Move/Look/Interact
                    ↓
                 Process Input
                    ↓
          Apply to Character/Camera
```

### Inventory System

**UAstroInventoryComponent**
- **Purpose**: Manage player's item collection
- **Data Structure**:
  ```cpp
  TArray<FInventoryItem> InventoryItems
  - FName ItemID (unique identifier)
  - int32 Quantity
  - int32 MaxStackSize
  - UTexture2D* Icon
  ```
- **Key Operations**:
  - AddItem(): Stack logic, slot checking
  - RemoveItem(): Quantity management
  - HasItem(): Query for requirements
  - GetItemQuantity(): Read-only access
- **Events**:
  - OnInventoryChanged: Broadcast after modifications
- **Performance**: O(n) lookups, acceptable for small inventories

**Add Item Flow**:
```
AddItem(ItemID, Quantity)
       ↓
Find existing item
       ↓
Stack if possible → Update quantity → Broadcast event
       ↓
Create new item → Add to array → Broadcast event
```

### Crafting System

**UAstroCraftingComponent**
- **Purpose**: Handle recipe-based item creation
- **Data Structure**:
  ```cpp
  FCraftingRecipe:
  - FName RecipeID
  - TMap<FName, int32> RequiredItems
  - FName ResultItemID
  - float CraftingTime
  - bool bIsUnlocked
  ```
- **State Machine**:
  ```
  Idle → CanCraft Check → Start Crafting → Crafting
                                             ↓
  Idle ← Complete Craft ← Progress (Tick) ←┘
  ```
- **Validation**: Checks inventory, recipe unlock status
- **Integration**: Requires reference to UAstroInventoryComponent

**Crafting Flow**:
```
StartCrafting(RecipeID)
       ↓
CanCraftRecipe() → Check inventory → Check unlock status
       ↓
Remove required items from inventory
       ↓
Start timer, set bIsCrafting = true
       ↓
Tick updates progress (0.0 - 1.0)
       ↓
On complete: Add result to inventory, broadcast event
```

### Research System

**UAstroResearchComponent**
- **Purpose**: Technology progression and unlocking
- **Data Structure**:
  ```cpp
  FResearchNode:
  - FName NodeID
  - TArray<FName> Prerequisites
  - TMap<FName, int32> RequiredResources
  - TArray<FName> UnlocksRecipes
  - float ResearchTime
  - bool bIsUnlocked
  ```
- **Graph Structure**: Tree with prerequisites
- **Validation**: Recursive prerequisite checking
- **Effects**: Unlocks recipes, modules, features

**Research Flow**:
```
StartResearch(NodeID)
       ↓
Check prerequisites (all unlocked?)
       ↓
Check resources (has required items?)
       ↓
Start research timer
       ↓
Tick updates progress
       ↓
On complete: Set bIsUnlocked, unlock recipes/modules, broadcast
```

### Ship Module System

**AAstroShipModule**
- **Purpose**: Individual ship component actors
- **Hierarchy**: Parent-child attachment system
- **Connection Points**:
  ```cpp
  FModuleConnectionPoint:
  - FVector RelativeLocation
  - FRotator RelativeRotation
  - EShipModuleType AcceptedModuleType
  - bool bIsOccupied
  ```
- **Module Types**: Enum for cockpit, engine, fuel, weapons, etc.
- **Stats**: Mass, power consumption/generation, crew capacity

**AAstroShipAssembly**
- **Purpose**: Manage complete ship construction
- **Responsibilities**:
  - Module spawning and attachment
  - Validation (required modules present)
  - Calculations (mass, power balance)
  - Flight readiness checking
  - Finalization (convert to flyable)

**Ship Building Flow**:
```
Create AAstroShipAssembly
       ↓
AddModule(CockpitClass, null, 0) → Spawn → Set as RootModule
       ↓
AddModule(EngineClass, Cockpit, 1) → Spawn → Attach to connection point
       ↓
AddModule(FuelClass, Cockpit, 2) → Spawn → Attach to connection point
       ↓
IsShipFlyable() → Check requirements → Check power → Return bool
       ↓
FinalizeShip() → Convert to flyable pawn
```

## Data Flow Patterns

### 1. User Input → Game State
```
Input Device → Enhanced Input System → AAstroPlayerCharacter
                                              ↓
                                     Component Functions
                                              ↓
                                      Update Game State
                                              ↓
                                     Broadcast Events
                                              ↓
                                        UI Updates
```

### 2. Crafting Process
```
UI Craft Button → UAstroCraftingComponent::StartCrafting()
                            ↓
               Check UAstroInventoryComponent
                            ↓
                  Remove Required Items
                            ↓
                   Start Crafting Timer
                            ↓
                     Tick (Progress)
                            ↓
                    Complete Crafting
                            ↓
            Add Result to UAstroInventoryComponent
                            ↓
               Broadcast OnCraftingCompleted
                            ↓
                      UI Updates
```

### 3. Research Unlock
```
Research Complete → UAstroResearchComponent::CompleteResearch()
                                ↓
                    Mark Node as Unlocked
                                ↓
                  Get Unlocked Recipes List
                                ↓
     For each recipe → UAstroCraftingComponent::UnlockRecipe()
                                ↓
                  Update UI (available recipes)
```

## Memory Management

### Object Lifetime
- **Components**: Owned by Actor, destroyed with Actor
- **Ship Modules**: Spawned actors, manually destroyed
- **Inventory Items**: Value types (structs) in TArray
- **Recipes/Research Nodes**: Data assets, loaded on demand

### Performance Considerations
- **Inventory**: Limited to MaxInventorySlots (default 40)
- **Ship Modules**: No hard limit, but affects performance
- **Tick Functions**: Only active when needed (crafting, research)
- **UI Updates**: Event-driven, not polled

## Thread Safety

Unreal Engine is primarily single-threaded for gameplay:
- **Game Thread**: All gameplay logic, components, actors
- **Render Thread**: Separate, handled by engine
- **No custom threading**: Keep it simple, use game thread

## Extensibility Points

### Adding New Item Types
1. Add entry to data table
2. Create icon asset
3. No code changes needed

### Adding New Module Types
1. Add enum value to EShipModuleType
2. Create Blueprint child of AAstroShipModule
3. Set module type in Blueprint
4. Design mesh and connection points

### Adding New Crafting Recipes
1. Create FCraftingRecipe entry
2. Set required items and result
3. Add to CraftingRecipes array
4. Optionally link to research node

### Adding New Research Nodes
1. Create FResearchNode entry
2. Set prerequisites
3. Set unlocked recipes/modules
4. Add to ResearchNodes array

## Blueprint Integration Points

### C++ Classes Designed for Blueprint Extension
- **AAstroPlayerCharacter**: Animation events, UI binding
- **AAstroShipModule**: Visual customization, stats
- **UAstroInventoryComponent**: UI widget binding
- **UAstroCraftingComponent**: Recipe data, UI updates
- **UAstroResearchComponent**: Tech tree visualization

### Recommended Blueprint Usage
- **Character BP**: Animations, mesh setup, effects
- **UI Widgets**: All interface elements
- **Module BPs**: Visual design, connection points
- **GameMode BP**: Spawn logic, game rules
- **HUD BP**: On-screen displays

## Configuration

### Config Files
- **DefaultEngine.ini**: Engine settings, game mode
- **DefaultInput.ini**: Input mappings
- **DefaultGame.ini**: Game-specific settings

### Data Tables (To Be Created)
- **DT_Items**: All craftable/collectible items
- **DT_Recipes**: All crafting recipes
- **DT_ResearchNodes**: Technology tree
- **DT_ShipModules**: Module specifications

## Error Handling

### Validation Patterns
- Check pointers before use
- Validate array indices
- Verify component references
- Return bool for success/failure
- Use ensure() for debug validation

### Example
```cpp
bool UAstroInventoryComponent::AddItem(FName ItemID, int32 Quantity)
{
    // Validate input
    if (ItemID.IsNone() || Quantity <= 0)
        return false;
    
    // Validate capacity
    if (InventoryItems.Num() >= MaxInventorySlots)
        return false;
    
    // Perform operation
    // ...
    
    return true;
}
```

## Future Architecture Considerations

### Multiplayer Support
- Components are already actor-based (good for replication)
- Would need to add:
  - UPROPERTY(Replicated) for synchronized data
  - Server RPC functions for actions
  - Client RPC for cosmetic updates

### Save System
- Serialize component data to save game object
- Save inventory, research progress, ship designs
- Load on game start

### Modding Support
- Data-driven design facilitates modding
- External data tables for content
- Blueprint-based modules
- No hardcoded content in C++

## Performance Profiling

### Key Metrics to Watch
- **Tick Time**: Component tick functions
- **Memory**: Inventory item arrays, ship modules
- **Draw Calls**: Ship module count impacts rendering
- **UI Updates**: Event frequency

### Optimization Strategies
- Disable tick when not needed (bIsCrafting)
- Pool ship modules instead of spawning
- Batch UI updates
- LOD for distant ship modules

## Debugging Tips

### Common Issues
- **Inventory not updating**: Check OnInventoryChanged binding
- **Crafting stuck**: Verify CraftingProgress increments
- **Research won't unlock**: Check prerequisites recursively
- **Modules won't attach**: Verify connection point types

### Debug Tools
- Visual Logger for component states
- Draw Debug for connection points
- Print String for flow validation
- Breakpoints in C++ code

## Conclusion

This architecture provides:
- ✅ Modularity through components
- ✅ Flexibility through events
- ✅ Performance through efficient data structures
- ✅ Extensibility through Blueprint integration
- ✅ Maintainability through clear separation

The system is designed to grow as the game develops, with clear extension points and minimal coupling between systems.
