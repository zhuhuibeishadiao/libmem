![libmem-logo](LOGO.png)  
#  

### Usage
Copy the `libmem` folder to your project directory.  
Include `libmem/libmem.h` (C/C++) or `libmem/libmem.hpp` (C++) in your project.  
Compile `libmem/libmem.c` along with your project.  

### Dependencies
Windows:  
- Windows SDK (-luser32, -lpsapi)  
  
Linux:  
- libdl (-ldl)  
  
BSD:  
- libdl (-ldl)  
- libkvm (-lkvm)
- libprocstat (-lprocstat)    
- libelf (-lelf)

### License
Read `LICENSE`  
  
### Overview
```
LM_EnumProcesses
LM_GetProcessId
LM_GetProcessIdEx
LM_GetParentId
LM_GetParentIdEx
LM_OpenProcess
LM_OpenProcessEx
LM_CloseProcess
LM_CloseProcess
LM_GetProcessPath
LM_GetProcessPathEx
LM_GetProcessName
LM_GetProcessNameEx
LM_GetSystemBits
LM_GetProcessBits
LM_GetProcessBitsEx

LM_EnumModules
LM_EnumModulesEx
LM_GetModule
LM_GetModuleEx
LM_GetModulePath
LM_GetModulePathEx
LM_GetModuleName
LM_GetModuleNameEx
LM_LoadModule
LM_LoadModuleEx
LM_UnloadModule
LM_UnloadModuleEx
LM_GetSymbol
LM_GetSymbolEx

LM_EnumPages
LM_EnumPagesEx
LM_GetPage
LM_GetPageEx

LM_ReadMemory
LM_ReadMemoryEx
LM_WriteMemory
LM_WriteMemoryEx
LM_SetMemory
LM_SetMemoryEx
LM_ProtMemory
LM_ProtMemoryEx
LM_AllocMemory
LM_AllocMemoryEx
LM_FreeMemory
LM_FreeMemoryEx
LM_DataScan
LM_DataScanEx
LM_PatternScan
LM_PatternScanEx
LM_SigScan
LM_SigScanEx

LM_SystemCall
LM_SystemCallEx
LM_FunctionCall
LM_FunctionCallEx
LM_DetourCode
LM_DetourCodeEx
LM_MakeTrampoline
LM_MakeTrampolineEx
LM_DestroyTrampoline
LM_DestroyTrampolineEx
```

# Projects
Made with libmem:  
- ![AssaultCube Multihack](https://github.com/rdbo/AssaultCube-Multihack)  
- ![X-Inject](https://github.com/rdbo/x-inject)  
- ![DirectX9 BaseHook](https://github.com/rdbo/DX9-BaseHook)  
- ![DirectX11 BaseHook](https://github.com/rdbo/DX11-BaseHook)  
- ![OpenGL BaseHook](https://github.com/rdbo/GL-BaseHook)  
- ![Counter-Strike 1.6 BaseHook](https://github.com/rdbo/cstrike-basehook)  
- ![Crazymem - NodeJS Memory Library](https://github.com/karliky/Crazymem)  
  
