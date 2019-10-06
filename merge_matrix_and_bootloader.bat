cd /d "%~dp0"
.\sketch_combiner\bin_merge_tool\mergesketch.exe .\bootloader_only_binaries\matrix_v120.bin %~f1 .\full_build\%~n1_with_bootloader_V120.bin
.\sketch_combiner\bin_merge_tool\mergesketch.exe .\bootloader_only_binaries\matrix_v150.bin %~f1 .\full_build\%~n1_with_bootloader_V150.bin
.\sketch_combiner\bin_merge_tool\mergesketch.exe .\bootloader_only_binaries\matrix_v210.bin %~f1 .\full_build\%~n1_with_bootloader_V210.bin
.\sketch_combiner\bin_merge_tool\mergesketch.exe .\bootloader_only_binaries\matrix_v210_safe.bin %~f1 .\full_build\%~n1_with_bootloader_V210_safe.bin

pause