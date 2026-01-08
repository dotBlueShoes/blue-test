1. See what tests other then unit can be applied.
2. Expirement with wave implementation (rename, asm, simd).
3. Add information on how to build the all-build target on github.
4. Restructure CMake files and Quail files to enable all-build + submodule build.

### CPU EXTENSION

SSE3, PCLMULQDQ, DTES64, EST, TM2, SSSE3, FMA, CMPXCHG16B, xTPR_Upd_Ctrl, PDCM, PCID, SSE41, SSE42, MOVBE, POPCNT, AES, XSAVE, OSXSAVE, AVX, F16C, RDRAND, FPU, VME, DE, PSE, TSC, MSR, PAE, MCE, CX8, APIC, SEP, MTRR, PGE, MCA, CMOV, PAT, PSE_36, CLFSH, DS, ACPI, MMX, FXSR, SSE, SSE2, SS, HTT, TM, PBE, FSGSBASE, IA32_TSC_ADJUST, BMI1, HLE, AVX2, SMEP, BMI2, ERMS, INVPCID, RTM, Dep_FPU_CS_DS, Intel_Mem_Prot_Exts, RDSEED, ADX, SMAP, CLFLUSHOPT, IBRS, IBPB, STIBP, IA32_ARCH_CAP_MSR, SSBD, LAHF64, LZCNT, PREFETCHW, SYSCALL64, SYSRET64, EXE_DIS_BIT, OGBP, RDTSCP, LM64

### CMake Restructure sample

```PWSH
-------------------------------------------------------
RELEASE
-------------------------------------------------------

cmake -S project\bluecycle -B build\bluecycle\x64-win-release -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Release -DPROFILE=1
cmake --build C:\Projects\blue\build\bluecycle\x64-win-release

cmake -S project\bluemetric -B build\bluemetric\x64-win-release -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Release -DPROFILE=1
cmake --build C:\Projects\blue\build\bluemetric\x64-win-release

cmake -S project\blueunit -B build\blueunit\x64-win-release -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Release -DPROFILE=1
cmake --build C:\Projects\blue\build\blueunit\x64-win-release

-------------------------------------------------------
DEBUG
-------------------------------------------------------

cmake -S project\bluecycle -B build\bluecycle\x64-win-debug -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build C:\Projects\blue\build\bluecycle\x64-win-debug

cmake -S project\bluemetric -B build\bluemetric\x64-win-debug -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build C:\Projects\blue\build\bluemetric\x64-win-debug

cmake -S project\blueunit -B build\blueunit\x64-win-debug -G Ninja -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_RC_COMPILER="C:/Program Files/LLVM/bin/llvm-rc.exe" -DCMAKE_BUILD_TYPE=Debug -DPROFILE=1
cmake --build C:\Projects\blue\build\blueunit\x64-win-debug
```
