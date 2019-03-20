/* *****************************************************************************
* The MIT License
*
* Copyright (c) 2010 LeafLabs LLC.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
* ****************************************************************************/

/**
*  @file main.c
*
*  @brief main loop and calling any hardware init stuff. timing hacks for EEPROM
*  writes not to block usb interrupts. logic to handle 2 second timeout then
*  jump to user code.
*
*/

#include "common.h"
#include "dfu.h"
#include "matrix.h"

extern volatile dfuUploadTypes_t userUploadType;

int main()
{
  bool no_user_jump = FALSE;
  bool dont_wait = FALSE;

  systemReset(); // peripherals but not PC
  setupCLK();
  setupLEDAndButton();
  setupUSB();
  setupFLASH();

  switch(checkAndClearBootloaderFlag())
  {
    case 0x01:
    no_user_jump = TRUE;

    #ifdef FASTBOOT
    dont_wait = FALSE;
    #endif

    break;

    case 0x02:
    dont_wait = TRUE;
    break;

    default:

    #ifdef FASTBOOT
    dont_wait = TRUE;
    #endif

    if (!checkUserCode(USER_CODE_FLASH) || readButtonState())
    {
      no_user_jump = TRUE;
      #ifdef FASTBOOT
      dont_wait = FALSE;
      #endif
    }
    break;
  }

  if (!dont_wait)
  {
    int delay_count = 0;

    while ((delay_count++ < BOOTLOADER_WAIT) || no_user_jump)
    {
      if (dfuUploadStarted())
      {
        dfuFinishUpload(); // systemHardReset from DFU once done
      }

      // if(readButtonState())
      // {
      //   break;
      // }
    }
  }

  if (checkUserCode(USER_CODE_FLASH))
  {
    jumpToUser(USER_CODE_FLASH);
  }
  else
  {
    // Nothing to execute in either Flash or RAM

    systemHardReset();
  }
  
  return 0;// Added to please the compiler
}
