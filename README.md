# COMP 3004 - Team 59
# Introduction
This project was developed as the final assessment in the COMP3004 Object Oriented Software Engineering course. I will provide the introduction below for the context of the project was developed for:

Raven Microcurrent Biofeedback Inc. (RMB), a manufacturer of a variety of microcurrent
biofeedback devices, has hired you to build them a software-based prototype of a device they
are planning to add to their product line. RMB intends to use this prototype to explore different
capabilities before deciding on the design of the physical product. Your team happily accepts
the task, eager to impress your new employer with your development skills. RMB would like
their device to have the same features as Oasis Pro from Mind Alive Inc. with the a few
additional capabilities related to recording and replay of treatments. The implementation and
testing are to be in C++ using the Qt framework on the COMP3004-F21 VM which has the Qt
Creator IDE installed.

Oasis Pro is an example of a CES device which is a non-invasive neuro-stimulation medical
device that delivers microcurrent via an electrode through the earlobes to stimulate the brain for
the purpose of therapeutic intervention.

For details of Oasis Pro operation refer to the owner’s manual on Brightspace
(OASIS_Pro_Manual.pdf) and the video https://www.youtube.com/watch?v=PDgN03Fx6fg&t=2s

What features of Oasis Pro should be simulated?
1. Power: “Turn On/Turn Off” and “Ending A Session” as described on p4 of the manual.
2. Battery level: battery level and battery low warnings as per “Battery Level” section on p5
of the manual. Your simulation should handle battery depletion as a function of length of
therapy, intensity, and connection to skin.
3. Selecting a session: as per “Selecting A Session” on p5 of the manual but only with 3
groups (20min, 45min and user designated) and 4 session types per group. You can
choose any 4 types from p12 of the manual.
4. Connection test: as per “Connection Test” on p6 of the manual.
5. Intensity: as per “Adjusting Intensity” on p7 of the manual.
What additional features should be simulated?
1. Record: users can choose to record a therapy and add to treatment history. Therapy
session information to be recorded: session type, duration and intensity level (if changed
during therapy choose last selected intensity level). There would be additional interface
needed beyond what Oasis Pro offers to implement this feature, and it is up to you
design it.
2. Replay: users can replay selected treatments from history of treatments.
3. Note that both of the above features need to support different users.

# Table of Contents 
- [Team Members](#Team-Members) 
- [Team's Work](#Documentation) 
  * [Documentation Responsibilities](#Documentation-responsibilities)
  * [Implementation Responsibilities](#Implementation)
- [.h Files](#h-Files) 
- [.cpp Files](#cpp-Files)
- [Test Scenario](#Test-Scenario) 
## <a name = "Team-Members" ></a>Team Members
| Student name  | ID number |
| ------------- | ------------- |
| Omar Khan  | 101168124  |
| Osamah ALQahtaini | 101179283  |
| Haochen Hou  | 101077553  |
| Ishwor Ghimire  | 101211820 | 
| Janessa Orhiobhe  | 101201685  |

## <a name = "Documentation-responsibilities" ></a>Responsibilities
- <a name = "Documentation" ></a>Documentation:

  `use case model`
    - janessa

  `UML class diagram`
    - omar

  `sequence diagram`
    - ishwor

  `traceability matrix` 
    - haochen, osamah
  
  `README`
    - Osamah
- <a name = "Implementation" ></a> Implementation:
  
  `Power`
    - Omar
    - Osamah
  
  `Battery`
    - Osamah
    - Ishwor
  
  `Selecting a session`
    - Omar
  
  `Connection test`
    - Jenessa
  
  `Intensity`
    - Haochen
  
  `record and replay`
    - Haochen
    - Omar
  
  `GUI`
     - Osamah
  
## <a name = "h-Files" ></a>.h and .ui Files
- Header
   * mainwindow.h
   * session.h
   * user.h
- Forms
   * mainwindow.ui

## <a name = "cpp-Files" ></a>.cpp Files
- Souces
   * main.cpp
   * mainwindow.cpp
   * session.cpp
   * user.cpp
 
## <a name = "Test-Scenario" ></a>Tested scenarios
  `Works`
   - Power on/off
   - Soft on/off
   - Battery depletion/Battery warnings
   - Connection test (good, ok, and bad connection)
   - Different users
   - Record/Replay with different users
   - Selecting a session
