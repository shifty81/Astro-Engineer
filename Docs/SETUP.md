# Astro Engineer - Setup Guide

## System Requirements

### Minimum Requirements
- **OS**: Windows 10 64-bit or Ubuntu 20.04+ 
- **Processor**: Quad-core Intel or AMD, 2.5 GHz or faster
- **Memory**: 16 GB RAM
- **Graphics**: DirectX 12 compatible graphics card
- **Storage**: 50 GB available space

### Recommended Requirements
- **OS**: Windows 11 64-bit or Ubuntu 22.04+
- **Processor**: 8-core Intel or AMD, 3.0 GHz or faster
- **Memory**: 32 GB RAM
- **Graphics**: NVIDIA RTX 3060 or AMD equivalent
- **Storage**: 100 GB SSD

## Installation Steps

### 1. Install Unreal Engine 5.7

#### Via Epic Games Launcher (Recommended)
1. Download and install [Epic Games Launcher](https://www.epicgames.com/store/download)
2. Sign in with your Epic Games account
3. Navigate to "Unreal Engine" tab
4. Click "Install Engine"
5. Select version 5.7
6. Choose installation location
7. Wait for download and installation

#### From Source (Advanced)
1. Clone UE5 repository from GitHub (requires Epic Games account linkage)
2. Follow compilation instructions for your platform
3. Build for version 5.7

### 2. Install Development Tools

#### Windows
1. **Visual Studio 2022**
   - Download Community Edition from Microsoft
   - During installation, select:
     - Desktop development with C++
     - Game development with C++
     - .NET desktop development
   - Include Windows 10/11 SDK

2. **Additional Tools**
   - Git for Windows
   - GitHub Desktop (optional)

#### Linux
1. **Build Tools**
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential
   sudo apt-get install clang
   sudo apt-get install mono-complete
   sudo apt-get install cmake
   ```

2. **Git**
   ```bash
   sudo apt-get install git
   ```

### 3. Clone the Repository

```bash
# Using HTTPS
git clone https://github.com/shifty81/Astro-Engineer.git

# Using SSH (if configured)
git clone git@github.com:shifty81/Astro-Engineer.git

# Navigate to project
cd Astro-Engineer
```

### 4. Generate Project Files

#### Windows
1. Right-click on `AstroEngineer.uproject`
2. Select "Switch Unreal Engine version..."
3. Choose your installed 5.7 version
4. Right-click again and select "Generate Visual Studio project files"
5. Wait for generation to complete

#### Linux
```bash
# From project root
/path/to/UE5/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh -project="/path/to/AstroEngineer/AstroEngineer.uproject" -game -engine
```

### 5. Build the Project

#### Windows
1. Open `AstroEngineer.sln` in Visual Studio
2. Select "Development Editor" configuration
3. Select "Win64" platform
4. Build > Build Solution (or press Ctrl+Shift+B)
5. Wait for compilation (first build takes 10-30 minutes)

#### Linux
```bash
# From project root
/path/to/UE5/Engine/Build/BatchFiles/Linux/Build.sh AstroEngineerEditor Linux Development "/path/to/AstroEngineer/AstroEngineer.uproject" -waitmutex
```

### 6. Launch the Editor

#### Windows
- Double-click `AstroEngineer.uproject`
- Or launch from Visual Studio (F5 or Debug > Start Debugging)

#### Linux
```bash
/path/to/UE5/Engine/Binaries/Linux/UnrealEditor "/path/to/AstroEngineer/AstroEngineer.uproject"
```

### 7. First Launch Setup

When the editor opens for the first time:

1. **Shader Compilation**
   - Wait for initial shader compilation (5-20 minutes)
   - Progress shown in bottom-right corner

2. **Create Initial Content**
   - Create a new level: File > New Level
   - Select "Empty Level" or "Default"
   - Save as `TestLevel` in `Content/Maps/`

3. **Project Settings**
   - Edit > Project Settings
   - Verify settings match Config files
   - Check Input settings for Enhanced Input

## Troubleshooting

### Issue: "AstroEngineerEditor modifies the values of properties" Build Error
**Error Message**:
```
AstroEngineerEditor modifies the values of properties: [ UndefinedIdentifierWarningLevel: Off != Error ]. 
This is not allowed, as AstroEngineerEditor has build products in common with UnrealEditor.
```

**Solution**: This error occurs when build settings are outdated. The project has been updated to use BuildSettingsVersion.V6 which includes the correct settings. If you encounter this:
1. Ensure you have the latest version from GitHub
2. Regenerate project files (right-click .uproject > Generate Visual Studio project files)
3. Clean and rebuild the solution in Visual Studio
4. Verify `Source/AstroEngineerEditor.Target.cs` contains:
   - `DefaultBuildSettings = BuildSettingsVersion.V6;`
   - `BuildEnvironment = TargetBuildEnvironment.Unique;`

### Issue: "Using backward-compatible build settings" Warning
**Warning Message**:
```
Using backward-compatible build settings. The latest version of UE sets the following values by default...
Suppress this message by setting 'DefaultBuildSettings = BuildSettingsVersion.V6;'
```

**Solution**: This is resolved in the latest version. Ensure both Target.cs files use V6:
- Check `Source/AstroEngineer.Target.cs`
- Check `Source/AstroEngineerEditor.Target.cs`
- Both should have `DefaultBuildSettings = BuildSettingsVersion.V6;`

### Issue: No .sln file exists
**Problem**: Cannot find `AstroEngineer.sln` to open in Visual Studio

**Solution**: 
1. The solution file must be generated before first use
2. Right-click `AstroEngineer.uproject` and select "Generate Visual Studio project files"
3. If right-click option is missing, run from command prompt:
   ```cmd
   "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\GenerateProjectFiles.bat" -project="%CD%\AstroEngineer.uproject" -game -engine
   ```
4. After generation completes, you should see `AstroEngineer.sln` in the project root

### Issue: "Could not find NetFxSDK install dir"
**Solution**: Install .NET Framework SDK from Visual Studio Installer

### Issue: "UnrealBuildTool.exe failed"
**Solution**: 
- Ensure Visual Studio 2022 is fully updated
- Verify C++ tools are installed
- Try regenerating project files

### Issue: "Failed to open descriptor file"
**Solution**:
- Verify .uproject file is valid JSON
- Check file permissions
- Ensure all paths are correct

### Issue: Slow shader compilation
**Solution**:
- Enable shader caching in Project Settings
- Close other applications during first launch
- Be patient - first compile is always slow

### Issue: Missing DLL errors
**Solution**:
- Rebuild the project completely
- Check Binaries folder exists
- Verify Visual Studio redistributables installed

### Issue: Linux compilation errors
**Solution**:
- Ensure clang is properly installed
- Check mono version compatibility
- Verify all dependencies installed

## Verification

After setup, verify everything works:

1. **Project Opens**: Editor launches without errors
2. **C++ Classes Visible**: Content Browser shows C++ Classes folder
3. **Blueprints Can Be Created**: Can create BP based on C++ classes
4. **Play in Editor Works**: Can press Play button
5. **No Compilation Errors**: Output log shows no errors

## Next Steps

After successful setup:
1. Read ARCHITECTURE.md to understand code structure
2. Review DEVELOPMENT_GUIDE.md for coding standards
3. Check ASSET_GUIDELINES.md before creating content
4. Start with creating Blueprint classes based on C++ classes
5. Build UI widgets for the backpack interface

## Additional Resources

- [Unreal Engine Documentation](https://docs.unrealengine.com/5.7/)
- [Enhanced Input Documentation](https://docs.unrealengine.com/5.7/enhanced-input-in-unreal-engine/)
- [C++ Programming Guide](https://docs.unrealengine.com/5.7/unreal-engine-cpp-programming/)
- Project Discord/Forum (if available)

## Getting Help

If you encounter issues not covered here:
1. Check GitHub Issues for similar problems
2. Review Unreal Engine documentation
3. Ask in project Discord/Forum
4. Create a new GitHub issue with:
   - Detailed description
   - Error messages
   - System specifications
   - Steps to reproduce
