/**
 * @file    main.cpp
 * @brief   Application entry point — STM32F103C8T6 bare-metal, C++23
 */


extern "C" int main() {  // NOLINT(clang-diagnostic-main) 裸机 main 由 Reset_Handler bl 调用，必须无 name mangling
    while (true) {
        // User application code goes here
    }
}
