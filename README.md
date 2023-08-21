# AVR-ATmega324PA
This repository contains a microcontroller programming project.

## TODO
* [x] Drawing concept diagram.
* [x] Add SVG: `tranmission.h`
* [x] Refactoring code.
* [x] Adding documentation.
* [ ] Add a (good) `README.md`

## File Directory
```bash
.
│   .gitignore
│   LICENSE
│   README.md
│
├───.vscode
│       c_cpp_properties.json
│       settings.json
│
├───inital_project
│   ├───app
│   │       6163.svg
│   │       deplacement.cpp
│   │       deplacement.h
│   │       main.cpp
│   │       makefile
│   │       reception.py
│   │
│   └───lib
│           can.cpp
│           can.h
│           capteurs.cpp
│           capteurs.h
│           communicationRS232.cpp
│           communicationRS232.h
│           controlPort.cpp
│           controlPort.h
│           debug.cpp
│           debug.h
│           frequencePwm.h
│           interupteurs.cpp
│           interupteurs.h
│           lumiere.cpp
│           lumiere.h
│           makefile
│           memoire_24.cpp
│           memoire_24.h
│           minuterie.cpp
│           minuterie.h
│           MinuteriePwm.cpp
│           MinuteriePwm.h
│           robot.cpp
│           robot.h
│           sonarite.cpp
│           sonarite.h
│           transmission.cpp
│           transmission.h
│
└───refactored_project
    ├───app-refactored
    │   │   main.cpp
    │   │   makefile
    │   │   reception.py
    │   │   RobotManager.cpp
    │   │   RobotManager.h
    │   │
    │   └───detection-strategies
    │           strategy.h
    │           Strategy0-0-Right.cpp
    │           Strategy0-0UP.cpp
    │           Strategy0-12.cpp
    │           Strategy0-3.cpp
    │           Strategy16-0.cpp
    │           Strategy16-12.cpp
    │           Strategy16-3.cpp
    │           Strategy7-0.cpp
    │           Strategy7-12.cpp
    │           Strategy7-3.cpp
    │
    └───library_refactored
            AbsPosition.h
            can.cpp
            can.h
            IOPorts.cpp
            IOPorts.h
            LEDController.cpp
            LEDController.h
            Map.cpp
            Map.h
            memoire_24.cpp
            memoire_24.h
            MotorsController.cpp
            MotorsController.h
            Pole.cpp
            Pole.h
            RobotController.cpp
            RobotController.h
            RobotTracker.cpp
            RobotTracker.h
            RS232communication.cpp
            RS232communication.h
            Sensors.cpp
            Sensors.h
            SoundController.cpp
            SoundController.h
            SwitchButtons.cpp
            SwitchButtons.h
            Tile.cpp
            Tile.h
            transmission.cpp
            transmission.h
```
