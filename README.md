## Dead Simple EULA Set

DSES is a simple tool to set the EULAs for the 3DS to accepted.

## What

In order to play 3DS games online/make use of streetpass, the 3DS makes the user accept an EULA. If this is for in-region titles, this is can be handled by the 3DS itself. If you wish to make use of out-of-region titles however, you will need to use homebrew to set the EULA to accepted.

## Why

A number of EULA setting tools exist already (notably, [SciresM/EULASetter](https://github.com/SciresM/EULASetter), which is the base for this tool).

However, all of these tools I've encountered so far sometimes offer a lot of other features and more importantly, put hex values in front of the user.

This tool does none of that. It does _one_ thing. Set your EULA to accepted if it isn't and to unaccepted if it is. No complications, nothing. Just press A and it changes the EULA.

Note that when unaccepting the EULA, you will need to reaccept it the next time you use a 3DS game in your own region.

## Usage

Download the CIA/3DSX from the releases page and open it with FBI. Press A to change your EULA. After that you can remove the application.

If for whatever reason you need to reset the EULA to its initial values, rerun the application again.
