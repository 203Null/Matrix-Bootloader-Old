#ifndef __MATRIX_H
#define __MATRIX_H

#include "common.h"

// #define MATRIX_MODEL 0x4D585054 //MXPT = Matrix Prototype
// #define MATRIX_VERSION 150 //v1.5 = 150 v1.2 = 120
#ifdef MATRIXINFO

__attribute__((section (".matrix_info"), used))
const struct bootloader_info
{
u32 bootloader_version;
u32 matrix_model;
u32 matrix_version;
u32 matrix_batch;
}
matrix_info =
{
  (u32) BOOTLOADER_VERSION,
  (u32) MATRIX_MODEL,
  (u32) MATRIX_VERSION,
  (u32) MATRIX_BATCH
};

#endif
#endif
