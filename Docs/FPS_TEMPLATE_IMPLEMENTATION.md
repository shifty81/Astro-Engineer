# FPS Template Implementation Guide

## Overview

This document provides precise, step-by-step instructions for implementing the First Person template in Astro Engineer. The FPS template serves as the foundation for the on-foot gameplay experience.

## Table of Contents

1. [Understanding the FPS Template](#understanding-the-fps-template)
2. [Prerequisites](#prerequisites)
3. [Core Components](#core-components)
4. [Enhanced Input System Setup](#enhanced-input-system-setup)
5. [Player Character Implementation](#player-character-implementation)
6. [Creating Blueprint from C++ Class](#creating-blueprint-from-cpp-class)
7. [Input Configuration](#input-configuration)
8. [Camera Setup](#camera-setup)
9. [Movement System](#movement-system)
10. [Interaction System](#interaction-system)
11. [Integration with Game Systems](#integration-with-game-systems)
12. [Testing](#testing)
13. [Troubleshooting](#troubleshooting)

---

## Understanding the FPS Template

The Astro Engineer FPS template is built on Unreal Engine 5.7's Enhanced Input System and provides:

- **First-person camera** attached to a character capsule
- **WASD movement** with mouse look
- **Enhanced Input Actions** for flexible control mapping
- **Component-based inventory system**
- **Interaction raycasting** for world object interaction
- **Backpack interface** toggle system

### Key Differences from Standard UE5 FPS Template

1. **Component-based design**: Inventory, crafting, and research are modular components
2. **Backpack system**: Unique interface that opens when player "kneels"
3. **Movement restriction**: Movement is disabled when backpack interface is open
4. **Extended interaction**: Support for multiple interaction types

---

## Prerequisites

Before implementing the FPS template, ensure:

- ✅ Unreal Engine 5.7 is installed
- ✅ Project is set up and compiling (see SETUP.md)
- ✅ Enhanced Input plugin is enabled (already configured in .uproject)
- ✅ Visual Studio 2022 is installed and project files generated
- ✅ You understand basic Unreal Engine concepts (Actors, Components, Blueprints)

---

## Core Components

The FPS template consists of these C++ classes:

### 1. AAstroPlayerCharacter
**File**: `Source/AstroEngineer/Public/AstroPlayerCharacter.h`

**Purpose**: Main player character for on-foot gameplay

**Key Features**:
- Inherits from `ACharacter` (built-in movement and collision)
- First-person camera component
- Enhanced Input System integration
- Inventory component attachment
- Interaction raycasting
- Backpack interface management

### 2. UAstroInventoryComponent
**File**: `Source/AstroEngineer/Public/AstroInventoryComponent.h`

**Purpose**: Manages player's item collection

**Key Features**:
- 40-slot inventory (configurable)
- Item stacking
- Event broadcasting for UI updates
- Blueprint-accessible functions

### 3. Related Components
- `UAstroCraftingComponent`: Handles crafting recipes
- `UAstroResearchComponent`: Manages technology tree
- Both are designed to be attached to the player character

---

## Enhanced Input System Setup

### Why Enhanced Input?

Enhanced Input provides:
- ✅ Flexible input mapping (rebindable keys)
- ✅ Support for multiple input devices (keyboard, gamepad, touch)
- ✅ Input modifiers and triggers
- ✅ Context-based input (different controls for different game states)

### Verify Plugin is Enabled

1. Open `AstroEngineer.uproject` in a text editor
2. Verify this section exists:
   ```json
   "Plugins": [
       {
           "Name": "EnhancedInput",
           "Enabled": true
       }
   ]
   ```

### Input System Architecture

```
Input Device (Keyboard/Mouse)
        ↓
Enhanced Input System
        ↓
Input Mapping Context (IMC_Default)
        ↓
Input Actions (IA_Move, IA_Look, IA_Interact, IA_Backpack)
        ↓
Player Character Functions (Move, Look, Interact, ToggleBackpack)
```

---

## Player Character Implementation

### Understanding the C++ Class

The `AAstroPlayerCharacter` class is already implemented. Here's what it does:

#### Constructor Setup
```cpp
AAstroPlayerCharacter::AAstroPlayerCharacter()
{
    // Enable ticking for animation updates
    PrimaryActorTick.bCanEverTick = true;

    // Set collision capsule size (42cm radius, 96cm height)
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Create first-person camera at eye level
    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
    FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f)); // Eye height
    FirstPersonCamera->bUsePawnControlRotation = true; // Camera follows controller rotation

    // Create inventory component
    InventoryComponent = CreateDefaultSubobject<UAstroInventoryComponent>(TEXT("InventoryComponent"));

    // Initialize state
    bIsBackpackOpen = false;
    InteractionRange = 200.0f; // 2 meters
}
```

#### Movement Function
```cpp
void AAstroPlayerCharacter::Move(const FInputActionValue& Value)
{
    // Only allow movement when backpack is closed
    if (!bIsBackpackOpen)
    {
        FVector2D MovementVector = Value.Get<FVector2D>();
        
        // Forward/Backward (Y axis)
        AddMovementInput(GetActorForwardVector(), MovementVector.Y);
        
        // Right/Left (X axis)
        AddMovementInput(GetActorRightVector(), MovementVector.X);
    }
}
```

#### Look Function
```cpp
void AAstroPlayerCharacter::Look(const FInputActionValue& Value)
{
    // Only allow looking when backpack is closed
    if (!bIsBackpackOpen)
    {
        FVector2D LookAxisVector = Value.Get<FVector2D>();
        
        AddControllerYawInput(LookAxisVector.X);   // Horizontal rotation
        AddControllerPitchInput(LookAxisVector.Y); // Vertical rotation
    }
}
```

#### Interaction Function
```cpp
void AAstroPlayerCharacter::Interact()
{
    if (bIsBackpackOpen) return;

    // Raycast from camera forward
    FVector Start = FirstPersonCamera->GetComponentLocation();
    FVector End = Start + (FirstPersonCamera->GetForwardVector() * InteractionRange);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
    {
        AActor* HitActor = HitResult.GetActor();
        // Implement interaction logic in Blueprint or derived classes
    }
}
```

---

## Creating Blueprint from C++ Class

Now that you understand the C++ implementation, create a Blueprint to use in-game:

### Step 1: Create Blueprint Class

1. **Open Unreal Editor**
2. **Navigate to Content Browser** → `Content/Blueprints/Characters/` (create folder if needed)
3. **Right-click** in empty space
4. **Select**: `Blueprint Class`
5. **In the class picker**:
   - Click `All Classes` to expand
   - Search for `AstroPlayerCharacter`
   - Select `AstroPlayerCharacter`
6. **Name it**: `BP_AstroPlayerCharacter`
7. **Double-click** to open the Blueprint Editor

### Step 2: Configure Components

#### A. Verify Component Hierarchy
In the **Components** panel (top-left), you should see:
```
BP_AstroPlayerCharacter (self)
├── CapsuleComponent (inherited)
├── Mesh (SkeletalMeshComponent - inherited)
├── FirstPersonCamera (UCameraComponent)
└── InventoryComponent (UAstroInventoryComponent)
```

#### B. Configure Camera
1. Select `FirstPersonCamera` in Components panel
2. In **Details** panel:
   - **Location**: (X=0, Y=0, Z=64) - Already set in C++
   - **Use Pawn Control Rotation**: ✅ Checked
   - **Field of View**: 90.0 (or your preference)

#### C. Configure Capsule Component
1. Select `CapsuleComponent`
2. In **Details** panel:
   - **Capsule Radius**: 42.0
   - **Capsule Half Height**: 96.0
   - Both already set in C++

#### D. Configure Inventory Component
1. Select `InventoryComponent`
2. In **Details** panel:
   - **Max Inventory Slots**: 40 (default, can be changed)

### Step 3: Add First-Person Arms (Optional)

For visual feedback, add first-person arms mesh:

1. **Click** `Add Component` → `Skeletal Mesh`
2. **Name it**: `FirstPersonArms`
3. **Parent to**: `FirstPersonCamera`
4. **In Details**:
   - **Skeletal Mesh**: Select your arms mesh (or use placeholder)
   - **Location**: (X=15, Y=0, Z=-75) - Adjust to your mesh
   - **Rotation**: Adjust to fit camera view
   - **Cast Shadow**: Unchecked (for FPS, arms don't need to cast shadows)
   - **Only Owner See**: ✅ Checked

### Step 4: Configure Class Defaults

1. **Click** `Class Defaults` button in toolbar (or open Class Settings)
2. In **Details** panel, find **AstroPlayerCharacter** section:

   #### Input Settings
   - **Default Mapping Context**: None (we'll set this later)
   - **Move Action**: None (we'll set this later)
   - **Look Action**: None (we'll set this later)
   - **Interact Action**: None (we'll set this later)
   - **Backpack Action**: None (we'll set this later)

   #### Interaction Settings
   - **Interaction Range**: 200.0 (2 meters)

3. **Compile** and **Save**

---

## Input Configuration

### Step 1: Create Input Actions

Input Actions define what can happen (move, look, interact).

1. **Navigate to**: `Content/Input/` (create folder if needed)
2. **Right-click** → `Input` → `Input Action`
3. **Create these Input Actions**:

   #### IA_Move
   - **Name**: `IA_Move`
   - **Value Type**: `Axis2D (Vector2D)`
   - **Description**: Movement input (WASD)

   #### IA_Look
   - **Name**: `IA_Look`
   - **Value Type**: `Axis2D (Vector2D)`
   - **Description**: Camera rotation input (Mouse)

   #### IA_Interact
   - **Name**: `IA_Interact`
   - **Value Type**: `Digital (Bool)`
   - **Description**: Interact with world objects

   #### IA_Backpack
   - **Name**: `IA_Backpack`
   - **Value Type**: `Digital (Bool)`
   - **Description**: Toggle backpack interface

### Step 2: Create Input Mapping Context

Input Mapping Context maps physical keys to Input Actions.

1. **Right-click** in `Content/Input/` → `Input` → `Input Mapping Context`
2. **Name it**: `IMC_Default`
3. **Double-click** to open

#### Configure Move Mapping
1. **Click** `+` next to `Mappings`
2. **Select Input Action**: `IA_Move`
3. **Add keyboard mappings**:
   - **W Key**:
     - Player Key: `W`
     - Modifiers: Add `Swizzle Input Axis Values`
       - Order: `YXZ` (moves Y value to X, and X to Y)
       - Output: This makes W = forward (Y+)
     - Value: (X=0, Y=1)
   - **S Key**:
     - Player Key: `S`
     - Modifiers: Add `Swizzle Input Axis Values` (Order: `YXZ`)
     - Add `Negate` modifier
     - Value: (X=0, Y=-1) - Results in backward movement
   - **A Key**:
     - Player Key: `A`
     - Add `Negate` modifier
     - Value: (X=-1, Y=0) - Left strafe
   - **D Key**:
     - Player Key: `D`
     - Value: (X=1, Y=0) - Right strafe

**Simplified Approach**: Use single mapping with modifier
- **Keyboard WASD Keys** as composite
- Add `Negate` for S and A keys

#### Configure Look Mapping
1. **Add Mapping**: `IA_Look`
2. **Mouse X**:
   - Input: `Mouse X`
   - Modifiers: Add `Scalar` with value `0.5` (sensitivity)
3. **Mouse Y**:
   - Input: `Mouse Y`
   - Modifiers: Add `Scalar` with value `0.5`
   - Add `Negate` (inverts pitch if needed)

#### Configure Interact Mapping
1. **Add Mapping**: `IA_Interact`
2. **E Key**:
   - Input: `E`
   - Trigger: `Pressed`

#### Configure Backpack Mapping
1. **Add Mapping**: `IA_Backpack`
2. **B Key**:
   - Input: `B`
   - Trigger: `Pressed`
3. **Tab Key** (alternative):
   - Input: `Tab`
   - Trigger: `Pressed`

### Step 3: Assign Input to Player Character

1. **Open** `BP_AstroPlayerCharacter`
2. **Open** `Class Defaults`
3. **In Details panel**:
   - **Default Mapping Context**: Select `IMC_Default`
   - **Move Action**: Select `IA_Move`
   - **Look Action**: Select `IA_Look`
   - **Interact Action**: Select `IA_Interact`
   - **Backpack Action**: Select `IA_Backpack`
4. **Compile** and **Save**

---

## Camera Setup

### First-Person Camera Configuration

The camera is already configured in C++, but here's how to customize it:

#### Camera Position
- **Default**: (X=0, Y=0, Z=64) - Eye level at 64cm above capsule base
- **Adjust**: Select `FirstPersonCamera` component, modify Location in Details

#### Field of View (FOV)
- **Default**: 90 degrees
- **Wider FOV** (100-110): Better peripheral vision, more arcade feel
- **Narrower FOV** (70-80): More realistic, less distortion

#### Camera Settings
- **Use Pawn Control Rotation**: ✅ Must be checked for FPS camera
- **Lock to HMD**: ❌ Unchecked (unless using VR)

### Camera Lag (Optional Smoothness)

For smoother camera movement:
1. Add `Camera Lag`
2. Set `Camera Lag Speed` to 10-20
3. This creates slight delay for cinematic feel

---

## Movement System

### Character Movement Component

The `CharacterMovementComponent` is inherited from `ACharacter` and provides:

#### Walking
- **Max Walk Speed**: 600 (default) - Adjust in Blueprint
  - 300-400: Slow/realistic
  - 600: Default
  - 800-1000: Fast/arcade

#### Jump
- **Jump Z Velocity**: 420 (default)
- **Air Control**: 0.05 (default) - How much control while in air

#### Rotation
- **Use Controller Rotation Yaw**: ❌ False for character (camera rotates, not body)
- **Orient Rotation to Movement**: ❌ False for FPS

### Customizing Movement in Blueprint

1. **Open** `BP_AstroPlayerCharacter`
2. **Select** `CharacterMovement` component
3. **In Details → Character Movement: Walking**:
   - **Max Walk Speed**: 600 (adjust as needed)
   - **Max Walk Speed Crouched**: 300
   - **Acceleration**: 2048
   - **Deceleration**: 2048
   - **Ground Friction**: 8.0

### Adding Sprint (Example)

To add sprint functionality:

1. **Create Input Action**: `IA_Sprint` (Digital)
2. **Add to IMC_Default**: Map to `Left Shift`
3. **In Blueprint Event Graph**:

```
Event IA_Sprint
├─ Pressed → Set Max Walk Speed (1200)
└─ Released → Set Max Walk Speed (600)
```

---

## Interaction System

### How Interaction Works

1. Player presses Interact key (E)
2. Raycast from camera forward 200cm
3. Check if ray hits an actor
4. Trigger interaction logic (implemented in Blueprint)

### Implementing Interaction in Blueprint

#### Method 1: Event-Based (Simple)

In `BP_AstroPlayerCharacter` Event Graph:

1. **Override** `Interact` function:
   ```
   Event Interact
   ├─ Line Trace by Channel (Start: Camera Location, End: Forward * 200)
   ├─ Branch (Hit Something?)
   │  ├─ True: Get Hit Actor
   │  │        ├─ Cast to InteractableActor
   │  │        └─ Call OnInteract function
   │  └─ False: Do nothing
   ```

#### Method 2: Interface-Based (Recommended)

Create an interaction interface for clean implementation:

1. **Create Interface**: `BPI_Interactable`
   - Function: `OnInteract` (Input: Player Character)
2. **Implement on objects** you want to be interactable
3. **In Player Character**:
   ```
   Event Interact
   ├─ Line Trace
   ├─ Get Hit Actor
   ├─ Does Implement Interface? (BPI_Interactable)
   │  └─ True: Call OnInteract (Message: BPI_Interactable)
   ```

### Visual Feedback

Add a crosshair and interaction prompt:

1. **Create Widget**: `WBP_InteractionPrompt`
   - Text: "Press E to interact"
   - Show only when looking at interactable object
2. **Update on Tick**: Check raycast, show/hide prompt

---

## Integration with Game Systems

### Inventory Integration

The inventory component is already attached. Access it in Blueprint:

```
Get Inventory Component
└─ Add Item (ItemID, Quantity)
└─ Remove Item (ItemID, Quantity)
└─ Has Item (ItemID) → Returns Bool
```

### Crafting Integration

Add crafting component:

1. **In C++**: Already available as `UAstroCraftingComponent`
2. **In Blueprint**: Add component
   ```cpp
   // In BeginPlay or Constructor
   CraftingComponent = CreateDefaultSubobject<UAstroCraftingComponent>(TEXT("CraftingComponent"));
   ```
3. **Use in Blueprint**:
   ```
   Get Crafting Component
   └─ Start Crafting (RecipeID)
   └─ Get Crafting Progress → Returns Float (0.0 - 1.0)
   ```

### Research Integration

Similar to crafting:

```
Get Research Component
└─ Start Research (NodeID)
└─ Is Node Unlocked (NodeID) → Returns Bool
```

---

## Testing

### Basic Movement Test

1. **Create Test Level** (see SCENE_SETUP_GUIDE.md)
2. **Set Game Mode**: Use `BP_AstroGameMode` with `BP_AstroPlayerCharacter`
3. **Press Play** (PIE - Play In Editor)
4. **Test**:
   - ✅ WASD moves character
   - ✅ Mouse rotates camera
   - ✅ Character can walk around
   - ✅ No clipping through walls

### Input Test

1. **Press Play**
2. **Open Console** (~ key)
3. **Type**: `showdebug input`
4. **Verify**:
   - ✅ Input actions trigger
   - ✅ Values update correctly

### Interaction Test

1. **Place test actor** in level
2. **Implement interaction** (add interface)
3. **Press Play**
4. **Look at object** and press E
5. **Verify**:
   - ✅ Raycast hits object
   - ✅ Interaction triggers
   - ✅ Feedback shows

### Backpack Test

1. **Press B key**
2. **Verify**:
   - ✅ `bIsBackpackOpen` = true
   - ✅ Mouse cursor appears
   - ✅ Movement disabled
3. **Press B again**
4. **Verify**:
   - ✅ `bIsBackpackOpen` = false
   - ✅ Mouse cursor disappears
   - ✅ Movement enabled

---

## Troubleshooting

### Character Doesn't Move

**Possible Causes**:
1. Input Mapping Context not assigned
   - **Fix**: Set `DefaultMappingContext` in Class Defaults
2. Input Actions not bound
   - **Fix**: Verify all Input Action references are set
3. Movement component disabled
   - **Fix**: Check `CharacterMovement` component is enabled

**Debug Steps**:
1. Enable `showdebug input` in console
2. Check if Input Actions fire
3. Add Print String in Move function to verify it's called

### Camera Doesn't Rotate

**Possible Causes**:
1. `bUsePawnControlRotation` not set on camera
   - **Fix**: Select FirstPersonCamera, check this property
2. Controller not assigned
   - **Fix**: Verify player controller exists
3. Look Input Action not bound
   - **Fix**: Check `LookAction` reference in Class Defaults

### Interaction Not Working

**Possible Causes**:
1. Interaction range too short
   - **Fix**: Increase `InteractionRange` (try 500)
2. Wrong collision channel
   - **Fix**: Use `ECC_Visibility` or custom channel
3. Hit actor doesn't implement interface
   - **Fix**: Verify interface implementation

**Debug Steps**:
1. Enable visual debugging:
   ```cpp
   DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
   ```
2. Add Print String to show hit results
3. Check collision settings on target actor

### Backpack Opens But Movement Still Works

**Possible Cause**:
- Input not checking `bIsBackpackOpen` flag

**Fix**:
Verify Move/Look functions have this check:
```cpp
if (!bIsBackpackOpen)
{
    // movement code
}
```

### Enhanced Input Not Working

**Possible Causes**:
1. Plugin not enabled
   - **Fix**: Check .uproject file, enable plugin
2. Input Mapping Context not added
   - **Fix**: Verify `BeginPlay` adds context
3. Wrong Input Action type
   - **Fix**: Ensure `IA_Move` is Axis2D, not Axis1D

---

## Advanced Customization

### Adding Crouch

1. Create `IA_Crouch` Input Action (Digital)
2. Map to `Ctrl` or `C` key
3. In Event Graph:
   ```
   IA_Crouch Pressed → Crouch (Built-in function)
   IA_Crouch Released → UnCrouch (Built-in function)
   ```

### Adding Head Bob

1. Create `BP_CameraShake_Walk` (Camera Shake class)
2. Configure oscillation parameters
3. In Tick or Move function:
   ```
   Is Moving? → Play Camera Shake (BP_CameraShake_Walk)
   ```

### Adding Footstep Sounds

1. Create `BP_FootstepSound` (Sound Cue)
2. In Animation Blueprint (if using):
   - Add Anim Notify at foot contact
   - Call Play Sound at Location
3. Or in Blueprint:
   - On Tick, check velocity
   - Play sound at intervals when moving

---

## Best Practices

### Performance
- ✅ Disable tick when not needed
- ✅ Use events instead of tick for infrequent checks
- ✅ Cache component references
- ✅ Limit interaction raycast distance

### Code Organization
- ✅ Keep C++ for core logic
- ✅ Use Blueprint for content-specific behavior
- ✅ Use interfaces for interaction system
- ✅ Use events for loose coupling

### User Experience
- ✅ Provide visual feedback for interactions
- ✅ Add sound effects for actions
- ✅ Smooth camera transitions
- ✅ Clear UI prompts

---

## Next Steps

After implementing the FPS template:

1. ✅ **Create UI Widgets** - See BLUEPRINT_QUICKSTART.md
2. ✅ **Setup Test Scene** - See SCENE_SETUP_GUIDE.md
3. ✅ **Add Animations** - Character animations for backpack
4. ✅ **Implement Interaction System** - Interface-based interactions
5. ✅ **Create HUD** - Crosshair, health, interaction prompts
6. ✅ **Test Thoroughly** - All movement and interaction scenarios

---

## Additional Resources

- [Enhanced Input Documentation](https://docs.unrealengine.com/5.7/enhanced-input-in-unreal-engine/)
- [Character Movement Component](https://docs.unrealengine.com/5.7/character-movement-component-in-unreal-engine/)
- [First Person Template Tutorial](https://docs.unrealengine.com/5.7/first-person-shooter-in-unreal-engine/)
- Project Files: `Source/AstroEngineer/Public/AstroPlayerCharacter.h`

---

## Summary

You now have:
- ✅ Complete understanding of the FPS template architecture
- ✅ Step-by-step Blueprint creation from C++ classes
- ✅ Enhanced Input System configuration
- ✅ Movement and camera setup
- ✅ Interaction system implementation
- ✅ Testing and debugging procedures

The FPS template is the foundation of Astro Engineer's gameplay. Once implemented, you can build upon it with inventory UI, crafting menus, and the unique backpack interface system.
