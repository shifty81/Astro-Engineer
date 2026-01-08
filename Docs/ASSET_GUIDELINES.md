# Astro Engineer - Asset Creation Guidelines

## Overview

This guide provides standards and best practices for creating content assets for Astro Engineer in Unreal Engine 5.7.

## General Principles

### Naming Conventions

#### Prefixes
- **BP_** - Blueprints (BP_PlayerCharacter)
- **M_** - Materials (M_MetalShiny)
- **MI_** - Material Instances (MI_MetalShiny_Red)
- **T_** - Textures (T_MetalAlbedo)
- **SM_** - Static Meshes (SM_CockpitModule)
- **SK_** - Skeletal Meshes (SK_Character)
- **A_** - Animation Assets (A_KneelDown)
- **WBP_** - Widget Blueprints (WBP_InventoryGrid)
- **DT_** - Data Tables (DT_Items)
- **E_** - Enums (E_ShipModuleType)
- **F_** - Structs (F_InventoryItem)

#### Naming Structure
Format: `Prefix_BaseAssetName_Variant_Suffix`

Examples:
- `SM_Cockpit_Basic_01`
- `M_Hull_Metallic_Master`
- `WBP_Backpack_Interface`
- `BP_Engine_Thruster_Large`

### Folder Structure

```
Content/
├── Blueprints/
│   ├── Characters/
│   │   └── BP_AstroPlayerCharacter.uasset
│   ├── ShipModules/
│   │   ├── BP_Cockpit_Basic.uasset
│   │   ├── BP_Engine_Thruster.uasset
│   │   └── BP_FuelTank_Small.uasset
│   └── GameModes/
│       └── BP_AstroGameMode.uasset
│
├── UI/
│   ├── Widgets/
│   │   ├── WBP_BackpackInterface.uasset
│   │   ├── WBP_InventoryGrid.uasset
│   │   ├── WBP_CraftingMenu.uasset
│   │   ├── WBP_ResearchTree.uasset
│   │   └── WBP_HUD.uasset
│   ├── Textures/
│   │   └── T_UI_*.uasset
│   └── Materials/
│       └── M_UI_*.uasset
│
├── Materials/
│   ├── Master/
│   │   ├── M_MasterMaterial.uasset
│   │   └── M_UI_Master.uasset
│   └── Instances/
│       └── MI_*.uasset
│
├── Meshes/
│   ├── ShipModules/
│   │   ├── Cockpits/
│   │   ├── Engines/
│   │   ├── FuelTanks/
│   │   ├── Weapons/
│   │   └── Hull/
│   ├── Props/
│   │   └── SM_*.uasset
│   └── Environment/
│       └── SM_*.uasset
│
├── Textures/
│   ├── ShipModules/
│   ├── UI/
│   ├── Environment/
│   └── Items/
│
├── Animations/
│   ├── Character/
│   │   ├── A_BackpackRemove.uasset
│   │   ├── A_Kneel.uasset
│   │   └── A_BackpackEquip.uasset
│   └── Sequences/
│
├── Audio/
│   ├── SFX/
│   │   ├── Interface/
│   │   ├── Crafting/
│   │   └── Ship/
│   └── Music/
│
├── Data/
│   ├── DT_Items.uasset
│   ├── DT_Recipes.uasset
│   ├── DT_ResearchNodes.uasset
│   └── DT_ShipModules.uasset
│
└── Maps/
    ├── MainMenu.umap
    ├── TestLevel.umap
    └── SpaceEnvironment.umap
```

## Asset-Specific Guidelines

### Static Meshes (Ship Modules)

#### Technical Requirements
- **Triangle Count**: 
  - Small modules: 500-2,000 tris
  - Medium modules: 2,000-5,000 tris
  - Large modules: 5,000-15,000 tris
- **Collision**: Custom collision meshes (UCX_ prefix)
- **LODs**: At least 2 LOD levels for large modules
- **Pivot Point**: Center of mass or logical attachment point
- **Scale**: 1 Unreal Unit = 1 cm
- **UV Channels**: 
  - Channel 0: Texture mapping
  - Channel 1: Lightmap UVs (no overlaps)

#### Connection Points
- Use Socket actors for connection points
- Name format: `Socket_Connection_01`, `Socket_Connection_02`
- Include direction indicator in socket rotation
- Document accepted module types

#### Materials
- Use master materials with instances
- Keep material slots to minimum
- Support RGB masking for variation
- Include emissive channel for lights/screens

### Textures

#### Resolution Standards
- **Character/Ship Modules**: 2048x2048 (large), 1024x1024 (medium), 512x512 (small)
- **UI Elements**: 512x512 or 256x256
- **Icons**: 128x128 or 64x64
- **Tileable Textures**: 1024x1024 or 512x512

#### Texture Types
- **Albedo/Base Color**: RGB, no lighting info
- **Normal**: DirectX format (green channel inverted for OpenGL)
- **Roughness**: Grayscale, use compression
- **Metallic**: Grayscale, use compression
- **Ambient Occlusion**: Grayscale
- **Emissive**: RGB for colored lights

#### Texture Packing
Pack similar textures to save memory:
- **ORM Map**: Occlusion (R), Roughness (G), Metallic (B)

#### Format Settings
- **Compression**: 
  - BC1 for simple color/albedo
  - BC5 for normal maps
  - BC4 for single-channel masks
- **sRGB**: Enable for albedo, disable for data maps
- **Mip Maps**: Generate for all textures

### UI Widgets

#### Resolution
- Design for 1920x1080 base resolution
- Use DPI scaling for other resolutions
- Test on 1280x720 and 3840x2160

#### Widget Structure
```
WBP_BackpackInterface (Canvas Panel)
├── Background Image
├── Tabs (Horizontal Box)
│   ├── Tab_Inventory
│   ├── Tab_Crafting
│   ├── Tab_Research
│   └── Tab_Ship
├── Content Switcher
│   ├── WBP_InventoryGrid
│   ├── WBP_CraftingMenu
│   ├── WBP_ResearchTree
│   └── WBP_ShipAssembly
└── Close Button
```

#### Style Guide
- **Colors**: 
  - Primary: Space blue (#1E3A5F)
  - Secondary: Teal accent (#3FBFAA)
  - Background: Dark gray (#1A1A1A)
  - Text: White (#FFFFFF) or light gray (#CCCCCC)
- **Fonts**: 
  - Headers: Size 24-36
  - Body: Size 14-18
  - Small text: Size 10-12
- **Spacing**: 
  - Padding: 10-20 units
  - Margins: 5-15 units
- **Buttons**: 
  - Minimum size: 120x40
  - Hover state: Brighten 20%
  - Pressed state: Darken 10%

#### Performance
- Minimize nested widgets
- Use invalidation boxes for complex layouts
- Limit bind events (use event-driven updates)
- Don't tick widgets unless necessary

### Animations

#### Character Animations
- **Frame Rate**: 30 FPS for gameplay, 60 FPS for cinematics
- **Root Motion**: Enable for movement anims
- **Looping**: Set loop flags appropriately
- **Additive**: Use for layering (e.g., looking while moving)

#### Backpack Animation Sequence
1. **A_BackpackRemove** (2 seconds)
   - Hand reaches back
   - Unclips backpack
   - Brings forward
   - Places on ground
2. **A_Kneel** (1 second)
   - Character kneels
   - Looks down at backpack
3. **A_BackpackEquip** (2 seconds)
   - Picks up backpack
   - Swings over shoulder
   - Clips in place
   - Stands up

### Audio

#### Sound Effects
- **Format**: WAV (uncompressed) for source, compress in engine
- **Sample Rate**: 44.1 kHz or 48 kHz
- **Bit Depth**: 16-bit or 24-bit
- **Channels**: Mono for most SFX, stereo for ambient

#### Categories
- **UI Sounds**: Clicks, swooshes, confirmations
- **Crafting**: Hammering, welding, assembly sounds
- **Ship**: Engine hum, thruster bursts, warning beeps
- **Ambient**: Space ambiance, station sounds

#### Volume Standards
- Normalize to -3dB to -6dB
- Leave headroom for mixing
- Use sound classes for category control

### Data Tables

#### Item Data Table (DT_Items)
```
Columns:
- ItemID (Name)
- ItemName (Text)
- Description (Text)
- Icon (Texture2D)
- MaxStackSize (int32)
- Category (Name)
- Value (int32)
```

#### Recipe Data Table (DT_Recipes)
```
Columns:
- RecipeID (Name)
- RecipeName (Text)
- Description (Text)
- RequiredItems (String - JSON format)
- ResultItemID (Name)
- ResultQuantity (int32)
- CraftingTime (float)
- Icon (Texture2D)
```

#### Research Node Data Table (DT_ResearchNodes)
```
Columns:
- NodeID (Name)
- NodeName (Text)
- Description (Text)
- Prerequisites (String - JSON array)
- RequiredResources (String - JSON format)
- ResearchTime (float)
- UnlocksRecipes (String - JSON array)
- UnlocksModules (String - JSON array)
- Icon (Texture2D)
```

## Blueprint Best Practices

### C++ Base Classes
Always create Blueprint children of C++ classes:
- **BP_AstroPlayerCharacter** extends AAstroPlayerCharacter
- **BP_ShipModule_Cockpit** extends AAstroShipModule
- Allows visual editing while maintaining code functionality

### Event Graph Organization
- Use comments to group functionality
- Collapse complex logic into functions
- Use custom events for reusable code
- Minimize tick usage

### Variable Access
- Use getters/setters for complex logic
- Make Blueprint-editable for designer control
- Use categories for organization
- Add tooltips for documentation

### Performance
- Disable tick if not needed
- Use timers instead of tick when possible
- Cache component references
- Avoid repeated GetComponent calls

## Version Control

### Assets to Commit
- Source meshes (FBX)
- Source textures (PNG, TGA, PSD with layers)
- Blueprints
- Data tables
- Maps
- Materials

### Assets to Ignore
- Derived Data Cache
- Intermediate files
- Saved folders
- User-specific settings

## Quality Checklist

Before submitting assets:

### Meshes
- [ ] Proper scale (test in-game)
- [ ] Collision mesh created
- [ ] Materials assigned
- [ ] LODs generated
- [ ] Sockets placed correctly
- [ ] No errors in static mesh editor

### Textures
- [ ] Correct resolution
- [ ] Proper compression settings
- [ ] sRGB set correctly
- [ ] Mip maps generated
- [ ] Reasonable file size

### Blueprints
- [ ] Compiles without errors
- [ ] No warnings
- [ ] Commented appropriately
- [ ] Variables categorized
- [ ] Tested in play mode

### UI Widgets
- [ ] Responsive layout
- [ ] Works at different resolutions
- [ ] All text readable
- [ ] Buttons functional
- [ ] Navigation logical

### Animations
- [ ] Smooth playback
- [ ] Root motion working
- [ ] Looping set correctly
- [ ] Additive layers functional
- [ ] No foot sliding

## Testing Requirements

### Asset Testing
1. **In-Editor**: Test in editor viewport
2. **PIE (Play in Editor)**: Test in game simulation
3. **Standalone**: Test in packaged build
4. **Multiple Settings**: Test at different quality levels

### Performance Testing
- Check frame rate impact
- Monitor memory usage
- Verify LOD transitions
- Test on minimum spec hardware

## Documentation

### Asset Documentation
Each complex asset should include:
- Purpose and usage
- Technical specifications
- Known issues/limitations
- Example usage
- Created by/date

### Location
- README.txt in asset folder
- Comments in Blueprint event graphs
- Tooltips on variables
- Architecture documentation

## Resources

### Learning Materials
- [UE5 Content Creation](https://docs.unrealengine.com/5.7/content-creation/)
- [Material Editor](https://docs.unrealengine.com/5.7/material-editor/)
- [UMG UI Designer](https://docs.unrealengine.com/5.7/umg-ui-designer/)
- [Animation System](https://docs.unrealengine.com/5.7/animation-system/)

### Asset Sources
- [Unreal Marketplace](https://www.unrealengine.com/marketplace/)
- [Quixel Megascans](https://quixel.com/megascans)
- Free assets for prototyping (always check licenses)

## Conclusion

Following these guidelines ensures:
- Consistent quality across all assets
- Easy maintenance and iteration
- Optimal performance
- Clear organization
- Smooth collaboration

Update these guidelines as project needs evolve.
