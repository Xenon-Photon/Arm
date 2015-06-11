ECHO If it returens error, check if the deviec is connected and in USBIsp mode
ECHO If this is the first time you ill need to edit this file with the right drive id
ECHO to find the drive id exute this command "mountvol"
SETLOCAL
SET src=..\Debug\Smart_Garden_Lights.bin
SET dst=\\?\Volume{41e9442c-e683-11e4-8b9e-00241d52f654}\firmware.bin

ECHO Will copy %src% to %dst%

COPY %src% %dst% /Y
