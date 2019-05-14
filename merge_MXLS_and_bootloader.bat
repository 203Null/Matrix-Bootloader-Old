cd /d "%~dp0"
.\sketch_combiner\bin_merge_tool\mergesketch.exe .\bootloader_only_binaries\stlinkv2_m1.bin %~f1 .\full_build\%~n1_with_bootloader_for_STLINK_V2_M1.bin

pause