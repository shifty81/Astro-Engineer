# Python Automation Guide for Astro Engineer

## Overview

This guide explains how to use Python scripts to automate the setup of the FPS template and test scenes in Unreal Engine. These scripts significantly reduce manual work and ensure consistent setup across different installations.

## Table of Contents

1. [Prerequisites](#prerequisites)
2. [Enabling Python in Unreal Engine](#enabling-python-in-unreal-engine)
3. [Available Scripts](#available-scripts)
4. [Running Python Scripts](#running-python-scripts)
5. [Script Descriptions](#script-descriptions)
6. [Troubleshooting](#troubleshooting)
7. [Advanced Usage](#advanced-usage)
8. [Creating Custom Scripts](#creating-custom-scripts)

---

## Prerequisites

### Required
- ✅ Unreal Engine 5.7 installed
- ✅ Astro Engineer project loaded in Unreal Editor
- ✅ Python Editor Script Plugin enabled (see below)

### Recommended
- ✅ Basic understanding of Python (for customization)
- ✅ Familiarity with Unreal Engine Editor
- ✅ Read FPS_TEMPLATE_IMPLEMENTATION.md first

---

## Enabling Python in Unreal Engine

### Step 1: Enable the Python Editor Script Plugin

1. **Open Unreal Editor** with your project
2. **Go to**: `Edit` → `Plugins`
3. **Search for**: `Python Editor Script Plugin`
4. **Check the box** to enable it
5. **Click**: `Restart Now`
6. **Wait** for the editor to restart

### Step 2: Verify Python is Working

1. **Open Output Log**: `Window` → `Developer Tools` → `Output Log`
2. **Type** in the output log command line:
   ```python
   py print("Python is working!")
   ```
3. **Press Enter**
4. **Verify**: You should see `Python is working!` in the output log

If you see the message, Python is ready to use!

---

## Available Scripts

The following Python scripts are available in `Scripts/Python/`:

### 1. setup_fps_template.py
**Purpose**: Automates creation of FPS template assets

**Creates**:
- Input Actions (IA_Move, IA_Look, IA_Interact, IA_Backpack)
- Input Mapping Context (IMC_Default)
- Blueprint: BP_AstroPlayerCharacter
- Blueprint: BP_AstroGameMode
- Required folder structure

**Time Saved**: ~20-30 minutes of manual work

### 2. setup_test_scene.py
**Purpose**: Automates creation of a test scene/level

**Creates**:
- New level (TestLevel.umap)
- Basic lighting (Directional Light, Sky Light, Sky Atmosphere)
- Floor plane
- Player Start actor
- Test objects for spatial reference
- Configured World Settings

**Time Saved**: ~15-20 minutes of manual work

---

## Running Python Scripts

### Method 1: Execute Python Script Menu (Easiest)

1. **Open Unreal Editor**
2. **Go to**: `Tools` → `Execute Python Script`
3. **Navigate** to the script file:
   - Example: `AstroEngineer/Scripts/Python/setup_fps_template.py`
4. **Select** the script
5. **Click**: `Open`
6. **Wait** for the script to complete
7. **Check Output Log** for results

### Method 2: Output Log Command Line

1. **Open Output Log**: `Window` → `Developer Tools` → `Output Log`
2. **Type** in the command line:
   ```python
   py "C:/Path/To/AstroEngineer/Scripts/Python/setup_fps_template.py"
   ```
   Replace with your actual path (use forward slashes)
3. **Press Enter**
4. **Watch Output Log** for progress

### Method 3: Python Scripts Panel (Convenient)

1. **Go to**: `Window` → `Python Scripts`
2. **Browse** to `Scripts/Python/` folder
3. **Click** on a script to run it
4. **Watch Output Log** for progress

### Method 4: Drag and Drop (Quick)

1. **Open File Explorer**
2. **Navigate** to `Scripts/Python/`
3. **Drag** the `.py` file into the Unreal Editor viewport
4. **Script executes automatically**

---

## Script Descriptions

### setup_fps_template.py - Detailed Workflow

**What it does**:

#### 1. Creates Input System Assets
```
Content/Input/
├── IA_Move (Input Action - Axis2D)
├── IA_Look (Input Action - Axis2D)
├── IA_Interact (Input Action - Boolean)
├── IA_Backpack (Input Action - Boolean)
└── IMC_Default (Input Mapping Context)
```

#### 2. Creates Blueprint Structure
```
Content/Blueprints/
├── Characters/
│   └── BP_AstroPlayerCharacter
├── GameModes/
│   └── BP_AstroGameMode
└── ShipModules/ (empty, ready for use)
```

#### 3. Configures Blueprints
- Sets parent class to C++ classes
- Initializes components
- Prepares for input configuration

**After Running**: You still need to:
1. Open BP_AstroPlayerCharacter
2. Set Input Action references in Class Defaults
3. Configure key mappings in IMC_Default
4. See output log for detailed instructions

**Example Output**:
```
[AstroEngineer Setup] Creating directory: /Game/Input
[AstroEngineer Setup] Created Input Action: IA_Move (AXIS2D)
[AstroEngineer Setup] Created Input Action: IA_Look (AXIS2D)
[AstroEngineer Setup] Created Blueprint: BP_AstroPlayerCharacter
[AstroEngineer Setup] FPS Template Setup Complete!
```

---

### setup_test_scene.py - Detailed Workflow

**What it does**:

#### 1. Creates New Level
```
Content/Maps/
└── TestLevel.umap
```

#### 2. Adds Lighting Actors
- **Directional Light**: Simulates sun
  - Position: Angled downward
  - Intensity: 10.0
  - Color: Warm white
- **Sky Light**: Ambient lighting
  - Intensity: 1.0
  - Source: Captured Scene
- **Sky Atmosphere**: Realistic sky gradient
- **Exponential Height Fog**: Atmospheric depth

#### 3. Creates Environment
- **Floor**: 10000x10000 scaled cube
  - Position: Z=0 (ground level)
- **Test Cubes**: 4 cubes as spatial markers
  - Forward, backward, left, right positions

#### 4. Adds Gameplay Elements
- **Player Start**: Spawn point at (0, 0, 100)

#### 5. Configures World Settings
- Sets Game Mode to BP_AstroGameMode
- Enables physics
- Configures world bounds

**After Running**: 
- Level is ready to test!
- Press Play (PIE) to test immediately
- Customize as needed

**Example Output**:
```
[Scene Setup] Creating new level...
[Scene Setup] Created Directional Light (Sun)
[Scene Setup] Created Sky Light
[Scene Setup] Created Player Start
[Scene Setup] Set Game Mode to BP_AstroGameMode
[Scene Setup] Level saved successfully
[Scene Setup] Test Scene Setup Complete!
```

---

## Troubleshooting

### Issue: "Python Editor Script Plugin not found"

**Solution**:
1. Verify you're using Unreal Engine 5.7+
2. Check if plugin is available in Plugins window
3. Try reinstalling Unreal Engine if missing

### Issue: "Failed to create asset"

**Possible Causes**:
1. Asset already exists
   - **Solution**: Delete existing asset or rename in script
2. Invalid path
   - **Solution**: Check Content Browser paths match script
3. Missing parent class
   - **Solution**: Ensure C++ code is compiled

**Debug Steps**:
```python
# Check if C++ class exists
py unreal.load_class(None, "/Script/AstroEngineer.AstroPlayerCharacter")
# Should return a class object, not None
```

### Issue: "ImportError: No module named 'unreal'"

**Solution**:
- This error shouldn't occur in UE5.7+
- Ensure script is run **from within Unreal Editor**, not external Python
- Python scripts must use UE's built-in Python interpreter

### Issue: Script runs but assets don't appear

**Solution**:
1. **Refresh Content Browser**: Right-click → Refresh
2. **Check Output Log**: Look for error messages
3. **Verify paths**: Assets may be in different folder
4. **Check filters**: Content Browser may be filtered

### Issue: "Level creation failed"

**Solution**:
1. Close any open levels first
2. Ensure Maps folder exists
3. Check disk space
4. Try creating level manually first to test

### Issue: Character Blueprint doesn't have components

**Cause**: C++ class not properly compiled

**Solution**:
1. Close Unreal Editor
2. Rebuild C++ code in Visual Studio
3. Reopen editor
4. Run script again

---

## Advanced Usage

### Running Multiple Scripts in Sequence

Create a master script:

```python
# master_setup.py
import unreal

# Run FPS template setup
exec(open(r"C:/Path/To/setup_fps_template.py").read())

# Wait a moment
import time
time.sleep(2)

# Run test scene setup
exec(open(r"C:/Path/To/setup_test_scene.py").read())
```

### Customizing Scripts

#### Example: Change Input Folder Location

Edit `setup_fps_template.py`:
```python
# Change this line:
INPUT_PATH = f"{CONTENT_ROOT}/Input"

# To:
INPUT_PATH = f"{CONTENT_ROOT}/MyCustomFolder/Input"
```

#### Example: Add Custom Lighting to Test Scene

Edit `setup_test_scene.py`, add to `setup_lighting()` function:
```python
# Add point light
point_light = spawn_actor(
    unreal.PointLight,
    location=(0, 0, 300),
    name="PointLight_Custom"
)
if point_light:
    light_component = point_light.get_component_by_class(unreal.PointLightComponent)
    if light_component:
        light_component.set_editor_property("intensity", 5000.0)
        light_component.set_editor_property("attenuation_radius", 1000.0)
```

### Creating Asset Variations

Loop through and create multiple blueprints:

```python
# Create multiple ship module blueprints
module_types = ["Cockpit", "Engine", "FuelTank"]

for module_type in module_types:
    bp_name = f"BP_Module_{module_type}_Basic"
    # Create blueprint code here...
```

---

## Creating Custom Scripts

### Template for Custom Script

```python
"""
My Custom Astro Engineer Setup Script

Description: What this script does

Usage: How to run it
"""

import unreal

def log(message):
    """Helper function for logging"""
    unreal.log(f"[My Script] {message}")

def main():
    """Main function"""
    try:
        log("Starting setup...")
        
        # Your setup code here
        
        log("Setup complete!")
        
        # Show dialog
        unreal.EditorDialog.show_message(
            "Success",
            "Setup completed successfully!",
            unreal.AppMsgType.OK
        )
        
    except Exception as e:
        log(f"Error: {str(e)}")
        unreal.EditorDialog.show_message(
            "Error",
            f"Setup failed:\n{str(e)}",
            unreal.AppMsgType.OK
        )

if __name__ == "__main__":
    main()
```

### Useful Unreal Python API Functions

#### Asset Operations
```python
# Check if asset exists
unreal.EditorAssetLibrary.does_asset_exist("/Game/MyAsset")

# Load asset
asset = unreal.load_asset("/Game/MyAsset")

# Save asset
unreal.EditorAssetLibrary.save_loaded_asset(asset)

# Delete asset
unreal.EditorAssetLibrary.delete_asset("/Game/MyAsset")

# Rename asset
unreal.EditorAssetLibrary.rename_asset("/Game/Old", "/Game/New")
```

#### Level Operations
```python
# Get current world
world = unreal.EditorLevelLibrary.get_editor_world()

# Load level
unreal.EditorLevelLibrary.load_level("/Game/Maps/MyLevel")

# Save level
unreal.EditorLoadingAndSavingUtils.save_current_level()

# Get all actors
actors = unreal.EditorLevelLibrary.get_all_level_actors()
```

#### Spawn Actors
```python
# Spawn actor
editor_actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
actor = editor_actor_subsystem.spawn_actor_from_class(
    unreal.StaticMeshActor,
    unreal.Vector(0, 0, 0),
    unreal.Rotator(0, 0, 0)
)
```

#### Blueprint Operations
```python
# Create Blueprint
factory = unreal.BlueprintFactory()
factory.set_editor_property("parent_class", unreal.Actor)

blueprint = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
    asset_name="BP_MyBlueprint",
    package_path="/Game/Blueprints",
    asset_class=unreal.Blueprint,
    factory=factory
)
```

---

## Best Practices

### Script Development

✅ **Test incrementally**: Run script often during development
✅ **Add logging**: Use `log()` function liberally
✅ **Error handling**: Use try-except blocks
✅ **Check existence**: Verify assets exist before creating
✅ **Document**: Add comments explaining what code does

### Running Scripts

✅ **Save work first**: Scripts may modify project
✅ **Close unrelated levels**: Avoid conflicts
✅ **Check output log**: Always read script output
✅ **Backup project**: Before running untested scripts
✅ **Run in order**: FPS template → Test scene

### Script Organization

✅ **One purpose per script**: Don't do too much in one file
✅ **Reusable functions**: Create helper functions
✅ **Configuration at top**: Easy to modify settings
✅ **Version control**: Commit working scripts to Git

---

## Workflow Examples

### Complete Project Setup from Scratch

**Goal**: Set up entire FPS template and test environment

**Steps**:
1. Clone repository
2. Generate project files
3. Compile C++ code in Visual Studio
4. Open project in Unreal Editor
5. Enable Python Editor Script Plugin (restart)
6. Run `setup_fps_template.py`
7. Open BP_AstroPlayerCharacter, configure inputs
8. Configure IMC_Default key mappings
9. Run `setup_test_scene.py`
10. Press Play to test

**Total Time**: ~15 minutes (vs. 1+ hour manual)

### Iterative Level Design

**Goal**: Quickly test different scene configurations

**Steps**:
1. Modify `setup_test_scene.py` with your preferences
2. Run script
3. Test in PIE
4. Make adjustments to script
5. Delete level
6. Run script again
7. Repeat until satisfied

---

## Python API Resources

### Official Documentation
- [Unreal Engine Python API](https://docs.unrealengine.com/5.7/python-api/)
- [Scripting the Editor](https://docs.unrealengine.com/5.7/scripting-the-editor-using-python/)

### API Reference
- [unreal Module](https://docs.unrealengine.com/5.7/python-api/unreal/)
- [Editor Subsystems](https://docs.unrealengine.com/5.7/python-api/unreal/#editor-subsystems)

### Example Scripts
- Engine Installation: `Engine/Plugins/Experimental/PythonScriptPlugin/Content/Python/`

---

## Common Use Cases

### 1. Batch Create Ship Modules

```python
module_types = [
    ("Cockpit", "Basic"),
    ("Cockpit", "Advanced"),
    ("Engine", "Small"),
    ("Engine", "Large"),
    ("FuelTank", "Small"),
    ("FuelTank", "Large")
]

for module_type, variant in module_types:
    # Create blueprint for each combination
    create_ship_module_blueprint(module_type, variant)
```

### 2. Setup Multiple Test Levels

```python
level_configs = [
    ("TestLevel_Day", "day_lighting"),
    ("TestLevel_Night", "night_lighting"),
    ("TestLevel_Space", "space_lighting")
]

for level_name, lighting_preset in level_configs:
    create_level(level_name)
    setup_lighting(lighting_preset)
    save_level()
```

### 3. Batch Import Assets

```python
import os

asset_folder = "C:/MyAssets/"
for filename in os.listdir(asset_folder):
    if filename.endswith(".fbx"):
        import_mesh(os.path.join(asset_folder, filename))
```

---

## Conclusion

Python automation in Unreal Engine 5.7 is a powerful tool for:
- ✅ Reducing repetitive manual work
- ✅ Ensuring consistency across setups
- ✅ Enabling rapid iteration
- ✅ Scaling content creation
- ✅ Customizing project setup

**Key Takeaways**:
1. Enable Python Editor Script Plugin first
2. Run scripts from within Unreal Editor
3. Check Output Log for results
4. Start with provided scripts, customize as needed
5. Test scripts thoroughly before using on production

**Next Steps**:
1. Run `setup_fps_template.py` to create FPS assets
2. Configure input mappings manually (script creates assets)
3. Run `setup_test_scene.py` to create test level
4. Press Play to test your setup
5. Create custom scripts for your specific needs

For more information, see:
- FPS_TEMPLATE_IMPLEMENTATION.md - Manual FPS setup
- SCENE_SETUP_GUIDE.md - Manual scene setup
- BLUEPRINT_QUICKSTART.md - Blueprint creation guide

Happy automating! 🚀
