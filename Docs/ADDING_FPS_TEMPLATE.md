# Adding the Unreal Engine FPS Template to Astro Engineer

## Overview

This guide explains how to add the **official First Person Template** that comes with Unreal Engine 5.7 to your existing Astro Engineer project. This gives you the complete FPS content pack including meshes, materials, Blueprints, and animations from Epic's built-in template.

## Why Add the FPS Template?

The built-in FPS Template includes:
- ✅ **Pre-made First Person Character Blueprint** with arms mesh
- ✅ **Weapon system** (gun mesh, projectile, firing logic)
- ✅ **Input configuration** already set up
- ✅ **Animations** for arms and weapons
- ✅ **Materials and textures** for the FPS experience
- ✅ **Example maps** with proper lighting and post-processing
- ✅ **Complete game mode and HUD** implementations

This saves hours of manual asset creation and provides a professional foundation to build upon.

## Prerequisites

- Unreal Engine 5.7 installed
- Astro Engineer project already set up and opening in the editor
- Basic understanding of Unreal Engine content browser

---

## Method 1: Add Feature or Content Pack (Recommended)

This method adds Epic's official FPS template content to your existing project.

### Step 1: Open Unreal Editor

1. Launch Unreal Engine 5.7
2. Open the **AstroEngineer** project
3. Wait for the editor to fully load

### Step 2: Access Content Browser

1. Make sure the **Content Browser** is visible (usually at the bottom)
2. If not visible: **Window** → **Content Browser** → **Content Browser 1**

### Step 3: Add Content Pack

1. In the Content Browser, click the **"Add"** button (green "+ Add" button)
2. Select **"Add Feature or Content Pack..."**
   
   **Alternatively**:
   - Go to **Edit** menu
   - Select **"Add Feature or Content Pack..."**

### Step 4: Choose First Person Template

1. A window titled **"Add Content to the Project"** will appear
2. You'll see two tabs at the top:
   - **Content Packs** (free content from Epic)
   - **Feature Packs** (template content and starter kits)
3. Click on the **"Feature Packs"** tab (if not already selected)
4. Look for **"First Person"** template
   - Icon shows a first-person view with a gun
   - Description: "First Person template with shooting mechanics"
5. Click on the **First Person** template to select it

### Step 5: Configure Installation

1. After selecting, a preview panel appears on the right showing:
   - Template description
   - Content that will be added
   - Preview images
2. At the bottom, you'll see:
   - **"Add to Project"** button
   - Checkbox: **"Show Folder Structure"** (optional - check this to see what gets added)
3. Review the content that will be added
4. Click **"Add to Project"**

### Step 6: Wait for Import

1. Unreal Engine will now copy all FPS template content into your project
2. A progress dialog will appear showing:
   - Files being copied
   - Shaders being compiled
   - Assets being imported
3. **This can take 2-10 minutes** depending on your system
4. **Do not close the editor** during this process

### Step 7: Verify Installation

After the import completes:

1. In the **Content Browser**, navigate to **Content** folder
2. You should now see a new folder called **"FirstPerson"** (or similar)
3. Inside, you'll find:
   - **Blueprints/** - BP_FirstPersonCharacter, BP_FirstPersonGameMode, etc.
   - **Input/** - Input Actions and Mapping Contexts
   - **Maps/** - FirstPersonMap (example level)
   - **Materials/** - Materials for character and weapons
   - **Meshes/** - First person arms, weapon meshes
   - **Textures/** - Texture assets
   - **Audio/** - Sound effects (if included)

---

## Method 2: Migrate from a Separate Project (Alternative)

If the "Add Feature or Content Pack" option doesn't work, you can manually migrate content:

### Step 1: Create Temporary FPS Project

1. Open Epic Games Launcher
2. Go to **Unreal Engine** → **Library**
3. Click **Launch** for Unreal Engine 5.7
4. In the Unreal Project Browser:
   - Select **Games** category
   - Select **First Person** template
   - Choose project location (can be temporary)
   - Name it "TempFPS"
   - Click **Create**
5. Wait for the project to be created and opened

### Step 2: Migrate Content

1. In the TempFPS project, open **Content Browser**
2. Navigate to **Content/FirstPerson** folder
3. **Right-click** on the **FirstPerson** folder
4. Select **"Asset Actions"** → **"Migrate..."**
5. A window shows all assets that will be migrated (dependencies included)
6. Click **OK**
7. Navigate to your **AstroEngineer** project's **Content** folder:
   - Example: `C:/GIT PROJECTS/Astro-Engineer/Content/`
8. Click **"Select Folder"**
9. Wait for the migration to complete
10. Close the TempFPS project

### Step 3: Reload AstroEngineer Project

1. If AstroEngineer project is open, close and reopen it
2. Or use **File** → **Refresh** (if available)
3. In Content Browser, you should now see the **FirstPerson** folder

---

## Integration with Astro Engineer

After adding the FPS Template content, integrate it with your existing Astro Engineer systems:

### Option A: Use FPS Template as Base (Recommended for Beginners)

Replace your player character with the FPS template version:

1. **Open the imported FPS GameMode**:
   - Navigate to `Content/FirstPerson/Blueprints/`
   - Open `BP_FirstPersonGameMode`
   
2. **Set as Default Game Mode**:
   - Go to **Edit** → **Project Settings**
   - Under **Maps & Modes**
   - Set **Default GameMode** to `BP_FirstPersonGameMode`

3. **Test the FPS Template**:
   - Open `Content/FirstPerson/Maps/FirstPersonMap`
   - Press **Play** button
   - You should be able to walk around and shoot

4. **Add Your Components**:
   - Open `Content/FirstPerson/Blueprints/BP_FirstPersonCharacter`
   - In the **Components** panel, click **Add Component**
   - Add your custom components:
     - `AstroInventoryComponent`
     - `AstroCraftingComponent`
     - `AstroResearchComponent`

### Option B: Add FPS Assets to Your Custom Character (Advanced)

Keep your `BP_AstroPlayerCharacter` and add FPS template assets to it:

1. **Open Your Character**:
   - Navigate to `Content/Blueprints/Characters/`
   - Open `BP_AstroPlayerCharacter`

2. **Add First Person Arms**:
   - In **Components** panel, click **Add Component** → **Skeletal Mesh**
   - Name it: `FirstPersonArms`
   - Parent it to: `FirstPersonCamera`
   - In **Details** panel:
     - **Skeletal Mesh**: Select `Content/FirstPerson/Meshes/SK_FPGun` or `SK_Arms`
     - **Location**: (X=15, Y=0, Z=-75) - Adjust as needed
     - **Only Owner See**: ✅ Checked

3. **Copy Input Configuration**:
   - Open `Content/FirstPerson/Input/IMC_Default` (or similar)
   - Review the input mappings
   - Copy any mappings you want to your own Input Mapping Context
   - Or replace your IMC with the FPS template's version

4. **Add Weapon System** (Optional):
   - Add `TP_WeaponComponent` to your character (if available in template)
   - Configure shooting mechanics in your character Blueprint

### Option C: Use as Reference Only

Keep both implementations separate and use FPS template as reference:

1. Study the FPS template's implementation
2. Learn from their Blueprint logic and setup
3. Apply best practices to your own character
4. Copy specific features you want (like weapon firing logic)

---

## Customizing the FPS Template

Once added, customize the template to fit Astro Engineer's theme:

### 1. Replace Meshes

Replace generic FPS assets with space-themed ones:

- **Arms mesh**: Create or import space suit arms
- **Weapon mesh**: Replace gun with multi-tool or scanner device
- **Projectiles**: Change bullets to laser beams or energy projectiles

### 2. Modify Input Actions

Extend the input system for your game:

1. Keep basic movement and look controls
2. Add your custom actions:
   - Backpack toggle (B key)
   - Interact (E key)
   - Scan (Right-click)
   - Tool switching (1-5 keys)

### 3. Integrate Game Systems

Connect FPS character with your components:

1. **Inventory System**: Already have `UAstroInventoryComponent`
2. **Crafting System**: Connect backpack UI to crafting menu
3. **Interaction**: Add raycast interaction to FPS character
4. **HUD**: Create space-themed HUD instead of generic FPS HUD

### 4. Adjust Movement

Modify movement for space game feel:

1. **Slower Walk Speed**: 400-500 (more methodical)
2. **Add Jetpack**: For planetary exploration
3. **Zero-G Movement**: For space station sections
4. **Stamina System**: For realistic survival elements

---

## Folder Organization

After adding FPS template, organize your content:

```
Content/
├── FirstPerson/           (FPS Template assets - mostly reference)
│   ├── Blueprints/
│   ├── Input/
│   ├── Maps/
│   ├── Meshes/
│   └── Materials/
├── AstroEngineer/         (Your main game content)
│   ├── Blueprints/
│   │   ├── Characters/
│   │   │   ├── BP_AstroPlayer_FPS    (Your FPS implementation)
│   │   │   └── BP_AstroPlayer_Ship   (Ship piloting)
│   │   ├── GameMode/
│   │   ├── UI/
│   │   └── Systems/
│   ├── Meshes/
│   │   ├── Characters/
│   │   ├── Ships/
│   │   └── Items/
│   └── Materials/
└── Maps/
    ├── TestLevel
    ├── MainMenu
    └── SpaceStation
```

---

## Troubleshooting

### Issue: "Add Feature or Content Pack" option is grayed out

**Possible Causes**:
- Project not fully loaded
- Editor is compiling shaders
- Another operation in progress

**Solution**:
1. Wait for all background tasks to complete
2. Check bottom-right corner for active tasks
3. Try again after a few minutes

### Issue: FPS Template not visible in Feature Packs

**Possible Causes**:
- Using wrong Unreal Engine version
- Content packs not downloaded
- Cache issue

**Solution**:
1. Verify you're using UE 5.7
2. Check your internet connection
3. Restart the editor
4. Try Method 2 (migrate from separate project)

### Issue: Import takes too long or freezes

**Possible Causes**:
- Large content pack
- Shader compilation
- System resources

**Solution**:
1. Be patient - first import can take 10-15 minutes
2. Check Task Manager - CPU/GPU should be active
3. Don't close editor during import
4. If truly frozen (over 30 minutes), restart and try again

### Issue: FPS Character conflicts with my character

**Possible Causes**:
- Same class names
- Conflicting GameMode settings

**Solution**:
1. Rename one of the characters
2. Keep them in separate folders
3. Use different GameModes for different levels
4. Choose Option A, B, or C from Integration section

### Issue: Input doesn't work after adding template

**Possible Causes**:
- Multiple Input Mapping Contexts
- Conflicting input priorities

**Solution**:
1. Check which IMC is active in your GameMode
2. Merge input mappings into single IMC
3. Set correct priority for each context
4. Remove unused Input Mapping Contexts

---

## Best Practices

### 1. Keep FPS Template Separate
- Don't modify FPS template files directly
- Copy and customize instead
- Easier to update or reference later

### 2. Learn from the Template
- Study how Epic implemented features
- Understand the Blueprint logic
- Apply best practices to your own code

### 3. Gradual Integration
- Add template first, test it works
- Then integrate one system at a time
- Test after each integration step

### 4. Document Your Changes
- Note which FPS assets you're using
- Document any modifications
- Help other team members understand the setup

---

## Alternative: Start Fresh with FPS Template

If you haven't made significant progress yet, consider:

1. **Create new project** using FPS Template
2. **Migrate your C++ code** to the new project
3. **Add your components** to the FPS character
4. **Benefit from** complete FPS setup from the start

**Pros**:
- Clean, professional FPS foundation
- All assets already integrated
- Less configuration needed

**Cons**:
- Lose any existing customization
- Need to re-setup project settings
- More work if you're already far along

---

## Summary

You now know how to:
- ✅ Add the official FPS Template to your project
- ✅ Choose between "Add Feature Pack" or "Migrate" methods
- ✅ Integrate FPS content with your custom systems
- ✅ Customize the template for Astro Engineer
- ✅ Organize content properly
- ✅ Troubleshoot common issues

The FPS Template gives you a professional starting point with all the core FPS mechanics, animations, and assets. You can build your unique space exploration game on top of this solid foundation.

---

## Next Steps

After adding the FPS Template:

1. **Test the template** - Play in FirstPersonMap to understand how it works
2. **Choose integration approach** - Option A, B, or C based on your needs
3. **Add your components** - Inventory, crafting, research to FPS character
4. **Customize visuals** - Replace generic assets with space-themed ones
5. **Extend functionality** - Add backpack system, interaction, etc.
6. **Create your levels** - Build space stations and planetary surfaces

---

## Additional Resources

- [Unreal Engine Templates Documentation](https://docs.unrealengine.com/5.7/unreal-engine-templates/)
- [Content Migration Guide](https://docs.unrealengine.com/5.7/migrating-assets-in-unreal-engine/)
- [First Person Template Overview](https://docs.unrealengine.com/5.7/first-person-shooter-template-in-unreal-engine/)
- **FPS_TEMPLATE_IMPLEMENTATION.md** - Manual implementation guide (if you prefer not using the template)
- **BLUEPRINT_QUICKSTART.md** - Creating custom Blueprints
