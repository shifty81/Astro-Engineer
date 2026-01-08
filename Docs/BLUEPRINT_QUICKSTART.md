# Astro Engineer - Blueprint Quick Start Guide

## Overview

This guide helps you get started creating Blueprint content in the Unreal Editor for Astro Engineer. Follow these steps after completing the setup from SETUP.md.

## Prerequisites

- Unreal Engine 5.7 installed
- Project opened in Unreal Editor
- C++ code compiled successfully
- Editor showing Content Browser

## Step 1: Create Player Character Blueprint

### 1.1 Create Blueprint Class
1. In Content Browser, navigate to `Content/Blueprints/Characters/`
2. Right-click → Blueprint Class
3. Expand "All Classes" section
4. Search for "AstroPlayerCharacter"
5. Select `AstroPlayerCharacter`
6. Name it `BP_AstroPlayerCharacter`

### 1.2 Configure Player Character
1. Open `BP_AstroPlayerCharacter`
2. In Components panel:
   - Verify `FirstPersonCamera` component exists
   - Verify `InventoryComponent` exists
3. In Details panel (Class Defaults):
   - Set `Max Inventory Slots` = 40
   - Set `Interaction Range` = 200.0

### 1.3 Setup Mesh (Optional - for testing)
1. Add Mesh component
2. Set to first-person arms mesh (or use capsule for now)
3. Position below camera

### 1.4 Setup Input Actions
1. Go to Edit → Project Settings → Input
2. Create Input Mapping Context:
   - Name: `IMC_Default`
3. Create Input Actions:
   - `IA_Move` (Vector2D)
   - `IA_Look` (Vector2D)
   - `IA_Interact` (Digital)
   - `IA_Backpack` (Digital)
4. In BP_AstroPlayerCharacter → Class Defaults:
   - Set `Default Mapping Context` = `IMC_Default`
   - Set `Move Action` = `IA_Move`
   - Set `Look Action` = `IA_Look`
   - Set `Interact Action` = `IA_Interact`
   - Set `Backpack Action` = `IA_Backpack`

### 1.5 Add Animation Events (Blueprint Extension)
1. In Event Graph, add events:
   - **Event OnBackpackOpened**
     - Play animation sequence
     - Transition camera to look down
   - **Event OnBackpackClosed**
     - Play reverse animation
     - Reset camera

## Step 2: Create UI Widgets

### 2.1 Create Master Backpack Interface
1. Content Browser → `Content/UI/Widgets/`
2. Right-click → User Interface → Widget Blueprint
3. Name: `WBP_BackpackInterface`

**Layout:**
```
Canvas Panel
├── Background Image (Fill screen)
├── Horizontal Box (Top - Tabs)
│   ├── Button - Inventory Tab
│   ├── Button - Crafting Tab
│   ├── Button - Research Tab
│   └── Button - Ship Tab
├── Widgetcher (Content area)
│   ├── WBP_InventoryGrid
│   ├── WBP_CraftingMenu
│   ├── WBP_ResearchTree
│   └── WBP_ShipAssembly
└── Button - Close (Top right)
```

**Graph:**
1. Create variable: `CurrentTab` (int)
2. On Tab Button Clicked → Set CurrentTab → Switch Widget Switcher
3. On Close Button → Call Character's CloseBackpackInterface

### 2.2 Create Inventory Grid Widget
1. Create Widget: `WBP_InventoryGrid`

**Layout:**
```
Canvas Panel
├── Uniform Grid Panel (8x5 = 40 slots)
│   └── WBP_InventorySlot (x40)
└── Text - Inventory Title
```

**WBP_InventorySlot:**
```
Border
├── Image (Item Icon)
├── Text (Quantity)
└── Button (Interaction)
```

**Graph:**
1. On Construct → Bind to InventoryComponent's OnInventoryChanged
2. On Inventory Changed → Refresh Grid
3. RefreshGrid function:
   - Get Inventory Items from component
   - Update each slot widget with item data

### 2.3 Create Crafting Menu Widget
1. Create Widget: `WBP_CraftingMenu`

**Layout:**
```
Canvas Panel
├── Scroll Box (Left - Recipe List)
│   └── WBP_RecipeItem (multiple)
├── Vertical Box (Right - Details)
│   ├── Image - Recipe Icon
│   ├── Text - Recipe Name
│   ├── Text - Description
│   ├── Vertical Box - Requirements
│   │   └── Text - "Item x Quantity"
│   ├── Progress Bar (Crafting Progress)
│   └── Button - Craft
└── Text - Crafting Menu Title
```

**Graph:**
1. On Construct → Get Available Recipes from CraftingComponent
2. Populate recipe list
3. On Recipe Selected → Display details
4. On Craft Button → Call StartCrafting
5. Tick → Update progress bar from CraftingProgress

### 2.4 Create Research Tree Widget
1. Create Widget: `WBP_ResearchTree`

**Layout:**
```
Canvas Panel
├── Scroll Box (Scrollable area)
│   └── Canvas Panel (Large - for node positioning)
│       └── WBP_ResearchNode (multiple)
└── Text - Research Tree Title
```

**WBP_ResearchNode:**
```
Border
├── Image (Node Icon)
├── Text (Node Name)
├── Button (Select)
└── Image (Lock Icon if not unlocked)
```

**Graph:**
1. Position nodes based on prerequisites (tree layout)
2. Draw lines between prerequisites and nodes
3. On Node Selected → Show details panel
4. On Research Button → Call StartResearch

### 2.5 Create HUD Widget
1. Create Widget: `WBP_HUD`

**Layout:**
```
Canvas Panel
├── Text - Health (Top Left)
├── Text - Interaction Prompt (Center)
└── Image - Crosshair (Center)
```

**Graph:**
1. Update interaction prompt based on line trace
2. Show/hide based on player state

## Step 3: Create Ship Module Blueprints

### 3.1 Create Cockpit Module
1. Content Browser → `Content/Blueprints/ShipModules/`
2. Right-click → Blueprint Class
3. Select `AstroShipModule`
4. Name: `BP_Module_Cockpit_Basic`

**Setup:**
1. Open Blueprint
2. Select `ModuleMesh` component
3. Set Static Mesh (use cube for now)
4. In Details (Class Defaults):
   - Set `Module Type` = Cockpit
   - Set `Module Name` = "Basic Cockpit"
   - Set `Mass` = 500.0
   - Set `Power Consumption` = 50.0
   - Set `Crew Capacity` = 2
5. Add Connection Points:
   - Create socket on mesh for attachment points
   - Add to `Connection Points` array
   - Set `Relative Location` and `Accepted Module Type`

### 3.2 Create Other Module Types
Repeat for:
- `BP_Module_Engine_Basic`
  - Type: Engine
  - Power Generation: 200.0
- `BP_Module_FuelTank_Small`
  - Type: FuelTank
  - Mass: 300.0
- `BP_Module_Hull_Corridor`
  - Type: Hull
  - Multiple connection points

## Step 4: Create Game Mode Blueprint

### 4.1 Setup Game Mode
1. Content Browser → `Content/Blueprints/GameModes/`
2. Right-click → Blueprint Class
3. Select `AstroGameMode`
4. Name: `BP_AstroGameMode`

**Setup:**
1. Open Blueprint
2. In Class Defaults:
   - Set `Default Pawn Class` = `BP_AstroPlayerCharacter`
   - Set `HUD Class` = `BP_AstroHUD` (create this Blueprint)

### 4.2 Create HUD Blueprint
1. Create Blueprint Class
2. Select `HUD`
3. Name: `BP_AstroHUD`

**Graph:**
1. Event BeginPlay → Create WBP_HUD widget → Add to viewport

## Step 5: Create Test Level

### 5.1 Create Level
1. File → New Level
2. Select "Empty Level" or "Basic"
3. Save as `TestLevel` in `Content/Maps/`

### 5.2 Add Essential Actors
1. Add Player Start
2. Add Light Source (Directional Light)
3. Add Skybox/Sky Atmosphere
4. Add floor (plane or cube)

### 5.3 Configure World Settings
1. Window → World Settings
2. Set Game Mode Override = `BP_AstroGameMode`

### 5.4 Test Level
1. Press Play (PIE)
2. Test movement (WASD)
3. Test looking (Mouse)
4. Test backpack toggle (B key - if mapped)

## Step 6: Create Data Tables

### 6.1 Create Item Data Table
1. Right-click in Content Browser → Miscellaneous → Data Table
2. Choose row structure: Create new → Struct
3. Name struct: `ItemData`
4. Add fields:
   - ItemID (Name)
   - DisplayName (Text)
   - Description (Text)
   - Icon (Texture2D)
   - MaxStackSize (Integer)
   - Value (Integer)
5. Create table: `DT_Items`
6. Add rows for items:
   - IronOre
   - IronPlate
   - Electronics
   - etc.

### 6.2 Create Recipe Data Table
1. Create struct: `RecipeData`
2. Fields:
   - RecipeID (Name)
   - DisplayName (Text)
   - RequiredItems (String - JSON format: {"IronOre":5,"Fuel":2})
   - ResultItem (Name)
   - ResultQuantity (Integer)
   - CraftingTime (Float)
3. Create table: `DT_Recipes`
4. Add recipe rows

### 6.3 Link Data Tables to Components
In `BP_AstroPlayerCharacter`:
1. Get CraftingComponent reference
2. Initialize recipes from DT_Recipes
3. Same for Research from DT_ResearchNodes

## Step 7: Setup Enhanced Input

### 7.1 Create Input Mapping Context
1. Content Browser → Input folder
2. Right-click → Input → Input Mapping Context
3. Name: `IMC_Default`

### 7.2 Add Mappings
In IMC_Default:
1. **Move**
   - Action: `IA_Move`
   - Key: W (Forward), S (Backward), A (Left), D (Right)
   - Modifiers: Swizzle for correct axes
2. **Look**
   - Action: `IA_Look`
   - Key: Mouse X, Mouse Y
3. **Interact**
   - Action: `IA_Interact`
   - Key: E
4. **Backpack**
   - Action: `IA_Backpack`
   - Key: B or Tab

## Step 8: Connect UI to Components

### 8.1 Bind Backpack Interface
In `BP_AstroPlayerCharacter`:

**Event Graph:**
```
OnBackpackOpened
├→ Create Widget (WBP_BackpackInterface)
├→ Add to Viewport
└→ Set Input Mode UI Only

OnBackpackClosed
├→ Remove from Parent (cached widget)
└→ Set Input Mode Game Only
```

### 8.2 Pass Component References to Widgets
In WBP_BackpackInterface:
1. Create variable: `OwningCharacter` (AstroPlayerCharacter)
2. In Event Construct:
   - Get Player Character
   - Cast to BP_AstroPlayerCharacter
   - Store reference
3. Pass to child widgets:
   - WBP_InventoryGrid gets InventoryComponent
   - WBP_CraftingMenu gets CraftingComponent
   - etc.

## Step 9: Testing Checklist

### Basic Tests
- [ ] Character spawns correctly
- [ ] Can move with WASD
- [ ] Can look with mouse
- [ ] Press B opens backpack interface
- [ ] Interface shows tabs
- [ ] Can close interface

### Inventory Tests
- [ ] Can add items via console/debug
- [ ] Items appear in grid
- [ ] Stack counts update
- [ ] Full inventory prevents adding

### Crafting Tests
- [ ] Recipes show in list
- [ ] Can select recipe
- [ ] Requirements displayed
- [ ] Craft button works
- [ ] Progress bar updates
- [ ] Result added to inventory

### Ship Building Tests
- [ ] Can spawn ship assembly
- [ ] Can add root module
- [ ] Can attach child modules
- [ ] Connection validation works
- [ ] Power calculation correct

## Debugging Tips

### Common Issues

**Character not spawning:**
- Check Game Mode settings
- Verify Player Start exists
- Check Default Pawn Class

**Input not working:**
- Verify Input Mapping Context assigned
- Check Input Actions exist
- Test in PIE, not just viewport

**UI not showing:**
- Check widget is added to viewport
- Verify Z-order
- Check visibility settings
- Look for Blueprint errors

**Components not found:**
- Verify component exists in C++ class
- Check component is created in constructor
- Use GetComponentByClass as fallback

### Debug Commands

In PIE console (~):
```
stat fps                  // Show FPS
stat unit                 // Show frame time
showdebug                 // Show debug info
```

## Next Steps

After completing basic setup:
1. Create more ship modules with variety
2. Design beautiful UI with proper styling
3. Add sound effects
4. Create particle effects
5. Build actual game levels
6. Add save/load system
7. Implement ship flight mechanics

## Resources

### Tutorials
- [UE5 Blueprint Basics](https://docs.unrealengine.com/5.7/blueprint-basics/)
- [UMG UI Designer](https://docs.unrealengine.com/5.7/umg-ui-designer/)
- [Enhanced Input](https://docs.unrealengine.com/5.7/enhanced-input/)

### Assets
- Start with primitive shapes (cube, sphere)
- Use placeholder textures
- Iterate with proper assets later

## Conclusion

You now have:
- ✅ Player character Blueprint
- ✅ UI widget structure
- ✅ Ship module Blueprints
- ✅ Test level
- ✅ Input configuration

Ready to build your game! 🎮🚀
