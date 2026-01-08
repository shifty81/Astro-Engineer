# Astro Engineer - Python Automation Scripts

This folder contains Python scripts that automate setup tasks in Unreal Engine 5.7.

## Quick Start

1. **Enable Python in Unreal Engine**:
   - Open Unreal Editor
   - Go to: Edit → Plugins
   - Search: "Python Editor Script Plugin"
   - Enable it and restart

2. **Run Scripts**:
   - In Unreal Editor: Tools → Execute Python Script
   - Select a script from this folder
   - Check Output Log for results

## Available Scripts

### setup_fps_template.py
**Automates FPS template setup**
- Creates Input Actions and Mapping Context
- Creates BP_AstroPlayerCharacter Blueprint
- Creates BP_AstroGameMode Blueprint
- Sets up folder structure

**Time saved**: ~20-30 minutes

### setup_test_scene.py
**Automates test scene creation**
- Creates new TestLevel
- Adds lighting (sun, sky, atmosphere)
- Creates floor and test objects
- Adds Player Start
- Configures World Settings

**Time saved**: ~15-20 minutes

## Documentation

For complete instructions and troubleshooting, see:
- **Docs/PYTHON_AUTOMATION_GUIDE.md** - Complete Python automation guide
- **Docs/FPS_TEMPLATE_IMPLEMENTATION.md** - Manual FPS setup (alternative)
- **Docs/SCENE_SETUP_GUIDE.md** - Manual scene setup (alternative)

## Requirements

- Unreal Engine 5.7+
- Python Editor Script Plugin enabled
- Project opened in Unreal Editor
- C++ code compiled

## Workflow

**Recommended order**:
1. Run `setup_fps_template.py` first
2. Configure input mappings manually (see output log)
3. Run `setup_test_scene.py` second
4. Press Play to test!

## Support

If you encounter issues:
1. Check Output Log for error messages
2. Verify Python plugin is enabled
3. Ensure C++ code is compiled
4. See PYTHON_AUTOMATION_GUIDE.md for troubleshooting
5. Open GitHub issue if problem persists

## Customization

These scripts can be modified to suit your needs:
- Edit paths at the top of each script
- Add custom lighting configurations
- Create additional Blueprints
- Batch create assets

See PYTHON_AUTOMATION_GUIDE.md for examples.
