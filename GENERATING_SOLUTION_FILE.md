# Generating the Visual Studio Solution File

## Important: The .sln file is NOT in the repository!

The `AstroEngineer.sln` file is **intentionally not included** in the Git repository because it is a **generated file** that is specific to your system configuration.

## Where will the .sln file be located?

After generation, the solution file will be located at:
```
/Astro-Engineer/AstroEngineer.sln
```

This is in the **root directory** of the project, at the same level as `AstroEngineer.uproject`.

## How to Generate the .sln File

### Method 1: Right-Click (Easiest)

1. Navigate to your project folder in Windows Explorer
2. Find `AstroEngineer.uproject`
3. **Right-click** on `AstroEngineer.uproject`
4. Select **"Generate Visual Studio project files"**
5. Wait for the generation to complete (takes 10-30 seconds)
6. You should now see `AstroEngineer.sln` in the same folder

### Method 2: Command Line

If the right-click option is not available:

1. Open Command Prompt or PowerShell
2. Navigate to your project directory:
   ```cmd
   cd "C:\path\to\Astro-Engineer"
   ```
3. Run the generation command:
   ```cmd
   "C:\Program Files\Epic Games\UE_5.7\Engine\Build\BatchFiles\GenerateProjectFiles.bat" -project="%CD%\AstroEngineer.uproject" -game -engine
   ```
   *(Adjust the UE path if your installation is in a different location)*
4. Wait for completion
5. The `.sln` file will now exist in the project root

## Why is the .sln file not in the repository?

1. **System-specific**: Contains paths specific to your UE installation
2. **User-specific**: Different for each developer's environment
3. **Version-specific**: Changes based on UE version and configuration
4. **Regeneratable**: Can always be regenerated from the .uproject file
5. **Best practice**: Standard practice for Unreal Engine projects

## What files ARE in the repository?

The repository contains the **source files** needed to generate the solution:
- `AstroEngineer.uproject` - Project descriptor
- `Source/AstroEngineer.Target.cs` - Game target settings
- `Source/AstroEngineerEditor.Target.cs` - Editor target settings
- `Source/AstroEngineer/AstroEngineer.Build.cs` - Module build settings
- All C++ source files (.h and .cpp)

These are the files that define your project, and the `.sln` is generated from them.

## After Generating the .sln File

Once generated, you can:

1. **Open it in Visual Studio**:
   - Double-click `AstroEngineer.sln`
   - Or open Visual Studio and use File > Open > Project/Solution

2. **Build the project**:
   - Set configuration to **"Development Editor"**
   - Set platform to **"Win64"**
   - Build > Build Solution (Ctrl+Shift+B)

3. **Launch the editor**:
   - After building, double-click `AstroEngineer.uproject`
   - Or use Debug > Start Debugging (F5) in Visual Studio

## Troubleshooting

### "Cannot find .sln file"
- You need to generate it first (see methods above)
- It's not supposed to be in the GitHub repository

### "Right-click option missing"
- Ensure UE 5.7 is properly installed
- Try Method 2 (command line) instead
- Verify UE is associated with .uproject files

### "Generation fails"
- Ensure Visual Studio 2022 is installed
- Check that C++ tools are installed in Visual Studio
- Verify UE 5.7 installation is complete

### Need to regenerate?
- You can regenerate the .sln file anytime
- Useful after:
  - Adding new C++ classes
  - Changing target settings
  - Switching UE versions
  - Corrupted project files

## See Also

- **QUICKSTART.md** - Step 0 has detailed setup instructions
- **README.md** - Setup Instructions section
- **Docs/SETUP.md** - Complete setup and troubleshooting guide
