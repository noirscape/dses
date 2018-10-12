// DSES - Dead Simple EULA Set
// Copyright (C) 2018 Valentijn "noirscape" V.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#define TITLEID 0x000400000EF10200
#define SLEEPTIME 5000000000

int main(int argc, char* argv[])
{
    // noop call to shut up the compiler
    (void)argc;

    // Service initialization
    aptInit();
    gfxInitDefault();
    hidInit();
    cfguInit();
    // Variables
    Result res;
    bool done = false;
    uint8_t eulaData[4];

    PrintConsole topScreen;
    consoleInit(GFX_TOP, &topScreen);
    consoleSelect(&topScreen);

    printf("Dead Simple EULA Set - v1.1.0\n\n");

    // read magic
    res = CFGU_GetConfigInfoBlk2(4, 0xD0000, eulaData);
    if (R_FAILED(res))
    {
        printf("Something weird happened. Couldn't get EULA data.\n\nPress Start to exit.");
        done = true;
    }

    if(!done)
        printf(eulaData[0] == 0xFF && eulaData[1] == 0xFF ? "Press A to unset the 3DS EULAs.\n\n" : "Press A to set the 3DS EULAs.\n\n");

    while(aptMainLoop())
    {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_A && !done)
        {
            if (eulaData[0] == 0xFF && eulaData[1] == 0xFF) // FFFF == EULAs have been set, so unset them.
                eulaData[0] = eulaData[1] = 0x00;
            else // Anything else: EULAs have not been set, so set them.
                eulaData[0] = eulaData[1] = 0xFF;
            res = CFG_SetConfigInfoBlk8(4, 0xD0000, eulaData);
            if(R_FAILED(res))
                printf("Something went wrong...\n\n");
            else
                printf(eulaData[0] == 0xFF ? "Setting the EULA succeeded.\n\n" : "Unsetting the EULA succeeded.\n\n");
            printf("Press START to exit.\nPress Select to exit + remove application.\n");
            done = true;
        }
        if (kDown & KEY_START)
        {
            printf("Exiting...\n");
            break;
        }
        if (kDown & KEY_SELECT) 
        {
            char* endmsg = "Successfully removed application.\n";
            printf("Removing application and exiting...\n");
            if (envIsHomebrew())
            {
                remove(argv[0]);
                printf(endmsg);
            }
            else 
            {
                amInit();
                res = AM_DeleteAppTitle(MEDIATYPE_SD, (u64)TITLEID);
                if(R_FAILED(res))
                    printf("Couldn\'t remove DSES. Try removing it manually through System Settings.\n");
                else
                    printf(endmsg);
            }
            amExit();
            svcSleepThread(SLEEPTIME);
            break;
        }
    }

    aptExit();
    gfxExit();
    hidExit();
    cfguExit();
    return 0;
}
