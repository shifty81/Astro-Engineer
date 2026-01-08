# Quick Start Guide - Astro Engineer

## 🚀 Fastest Way to Get Started (10 minutes)

This is the quickest path to get Astro Engineer's FPS template up and running.

### Step 0: Initial Setup (5 minutes) - **IMPORTANT: DO THIS FIRST!**

Before you can use the Python automation scripts, you need to set up the C++ project:

#### 0.1 Clone the Repository
```bash
git clone https://github.com/shifty81/Astro-Engineer.git
cd Astro-Engineer
```

#### 0.2 Generate Visual Studio Project Files
**On Windows:**
1. Right-click on `AstroEngineer.uproject` in Windows Explorer
2. Select **"Generate Visual Studio project files"**
3. Wait for the process to complete
4. You should now see `AstroEngineer.sln` in the project folder

**Alternative method (if right-click option is missing):**
1. Locate your UE 5.7 installation (e.g., `C:\Program Files\Epic Games\UE_5.7`)
2. Navigate to `Engine\Build\BatchFiles`
3. Run: `GenerateProjectFiles.bat -project="C:\path\to\AstroEngineer.uproject" -game -engine`

#### 0.3 Build the C++ Code
1. Open `AstroEngineer.sln` in Visual Studio 2022
2. Set build configuration to **"Development Editor"** and platform to **"Win64"**
3. Build the solution: `Build` → `Build Solution` (or press Ctrl+Shift+B)
4. Wait for compilation to complete (first build may take 5-15 minutes)
5. Ensure there are **no build errors** before proceeding

#### 0.4 Launch Unreal Editor
1. Double-click `AstroEngineer.uproject`
2. If prompted to rebuild, click **"Yes"**
3. Wait for the editor to load and shaders to compile

### Prerequisites Checklist (Verify before continuing)

- [ ] Unreal Engine 5.7 installed
- [ ] Project cloned from GitHub
- [ ] Visual Studio project files generated (.sln file exists)
- [ ] C++ code compiled successfully in Visual Studio
- [ ] Project opened in Unreal Editor without errors

### Step 1: Enable Python (30 seconds)

1. In Unreal Editor: `Edit` → `Plugins`
2. Search: **"Python Editor Script Plugin"**
3. Check the box and click **"Restart Now"**

### Step 2: Run Automation Scripts (2 minutes)

1. Go to: `Tools` → `Execute Python Script`
2. Navigate to: `Scripts/Python/setup_fps_template.py`
3. Click **Open** and wait for completion
4. Run second script: `Scripts/Python/setup_test_scene.py`
5. Check Output Log for results

### Step 3: Configure Input (2 minutes)

1. Open **BP_AstroPlayerCharacter** (Content/Blueprints/Characters/)
2. Click **Class Defaults**
3. Set these references:
   - Default Mapping Context: **IMC_Default**
   - Move Action: **IA_Move**
   - Look Action: **IA_Look**
   - Interact Action: **IA_Interact**
   - Backpack Action: **IA_Backpack**
4. **Compile** and **Save**

### Step 4: Configure Key Mappings (1 minute)

1. Open **IMC_Default** (Content/Input/)
2. Add mappings:
   - **IA_Move**: W, A, S, D keys
   - **IA_Look**: Mouse X, Mouse Y
   - **IA_Interact**: E key
   - **IA_Backpack**: B key
3. **Save**

### Step 5: Test! (Now!)

1. Open **TestLevel** (Content/Maps/)
2. Click **Play** button
3. Test:
   - ✅ Move with WASD
   - ✅ Look with mouse
   - ✅ Press E to interact
   - ✅ Press B for backpack (toggles cursor)

## 🎯 You're Done!

You now have:
- ✅ Fully functional FPS character
- ✅ Test scene with lighting
- ✅ Input system configured
- ✅ Ready to build your game!

---

## 📚 Need More Details?

### For Implementation Details
- **FPS_TEMPLATE_IMPLEMENTATION.md** - Complete FPS setup guide
- **SCENE_SETUP_GUIDE.md** - Scene creation and modification
- **PYTHON_AUTOMATION_GUIDE.md** - Python automation details

### For Content Creation
- **BLUEPRINT_QUICKSTART.md** - Creating Blueprints and UI
- **ASSET_GUIDELINES.md** - Asset creation standards
- **ARCHITECTURE.md** - System architecture and design

### For Development
- **SETUP.md** - Detailed installation instructions
- **DEVELOPMENT_GUIDE.md** - Coding standards and workflow

---

## 🔧 Manual Setup (Alternative)

If you prefer manual setup or Python doesn't work:

1. **Create Input Assets** (10 min)
   - See FPS_TEMPLATE_IMPLEMENTATION.md → "Input Configuration"

2. **Create Blueprints** (15 min)
   - See FPS_TEMPLATE_IMPLEMENTATION.md → "Creating Blueprint from C++ Class"

3. **Create Test Scene** (20 min)
   - See SCENE_SETUP_GUIDE.md → "Creating Your First Scene"

**Total time**: ~45 minutes vs. 5 minutes with Python automation

---

## ❓ Common Issues

### "Python plugin not found"
- Verify you're using UE 5.7+
- Check Plugins window for availability

### "Failed to create Blueprint"
- Ensure C++ code is compiled
- Check Visual Studio build succeeded
- Verify no compilation errors

### "Character doesn't spawn"
- Check World Settings → Game Mode Override
- Verify Player Start exists in level
- Check BP_AstroGameMode → Default Pawn Class

### "Input not working"
- Verify all Input Action references are set
- Check IMC_Default has key mappings
- Test in PIE (Play In Editor), not just viewport

### Scripts fail to run
- Check Output Log for detailed errors
- Verify Python plugin is enabled
- See PYTHON_AUTOMATION_GUIDE.md → "Troubleshooting"

---

## 🎮 Next Steps

### 1. Create UI (1-2 hours)
Follow **BLUEPRINT_QUICKSTART.md** to create:
- Backpack interface widget
- Inventory grid
- HUD with crosshair

### 2. Add Ship Modules (30 min)
Create Blueprint variants:
- BP_Module_Cockpit_Basic
- BP_Module_Engine_Basic
- BP_Module_FuelTank_Small

### 3. Build Your First Level (1-2 hours)
Use **SCENE_SETUP_GUIDE.md** to create:
- Surface environment with terrain
- Space station interior
- Open space scene

### 4. Implement Gameplay
- Item spawning and pickup
- Crafting recipes
- Research tree
- Ship assembly

---

## 💡 Pro Tips

✅ **Save often** - Unreal can crash, especially during first setups
✅ **Use Python scripts** - They're faster and more consistent
✅ **Test incrementally** - Press Play after each major change
✅ **Read the docs** - Comprehensive guides available for everything
✅ **Check Output Log** - Contains important messages and errors

---

## 📞 Getting Help

- **GitHub Issues**: Report bugs and problems
- **Documentation**: See `/Docs` folder for detailed guides
- **Output Log**: Check for error messages first

---

## ✨ Summary

**Fastest path to working prototype**:
1. Enable Python plugin
2. Run 2 automation scripts
3. Configure input references and key mappings
4. Press Play

**You can be testing your game in under 5 minutes!**

For detailed information on any step, see the comprehensive documentation in the `/Docs` folder.

Happy developing! 🚀
