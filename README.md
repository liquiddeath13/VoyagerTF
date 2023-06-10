# VoyagerTF

External LOLTF with modded voyager connected.

updated to the latest patch 25.00

TODO every update:

- update viewpoint
- update uworld
- maybe bonearray if it changes and teamindex

use modded pasteager for this shit to work (thanks chase)

Requirements:

- Secure Boot OFF
- Virtualization (AMD SVM/Intel VT-x) ON
- Windows 10 2004-22h2
- Hyper-V Enabled (pasteager should auto enable it)

Known Issues related to pasteager:

- Works on 19041.1021 ideally on both CPU's.
- EAC blocks memory reading on AMD (also happens on some intel machines) Works well on battleye.
- Battleye might sometimes give u an error related to virtual machine, happened to one of my users. Doesnt happen to me though.
- Wont work on WIN 11 / win 10 below 2004 due to signatures, but can be easily updated


Possible Detection Vectors:

- vmexit_key
- mouse_event
- CreateWindow
- the shit source itself


anyways enjoy and dont sell this shit lol, but if u do atleast change aimbot from mouse_event to anything else.
