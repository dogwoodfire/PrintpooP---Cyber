To add medlogger partition scheme in arduino ide

//------------------------------------
1. Edit partition scheme menu in 'boards.txt'

Windows - open folder C:\Users\{username}\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.17
macOS
- shift+command+dot (show hidden files)
- open folder /Users/{username/Library/Arduino15/packages/esp32/hardware/esp32j/2.0.17
- edit file 'boards.txt'
- find menu 'esp32.menu.PartitionScheme' 
- add these lines
esp32.menu.PartitionScheme.max_app_only=Max App Only (3.9MB App)
esp32.menu.PartitionScheme.max_app_only.build.partitions=max_app_only
esp32.menu.PartitionScheme.max_app_only.upload.maximum_size=4128768
- save

//------------------------------------
2. Add partition file into partition folder

Windows - open folder C:\Users\{user}\AppData\Local\Arduino15\packages\esp32\hardware\esp32\2.0.17\tools\partitions
macOS - open folder /Users/{username/Library/Arduino15/packages/esp32/hardware/esp32j/2.0.17/tools/partitions

- copy file 'max_app_only.csv' into partitions folder

//------------------------------------
3. Delete cache please delete the following folder ( if necessary)

macOS - /Users/ratthaninwartcheeranon/Library/Application Support/Arduino-ide
Windows - C:\Users\{username}\AppData\Roaming\arduino-ide


//------------------------------------
4. restart arduino app
