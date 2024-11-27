
<!--- This is a markdown template for creating the README.md file in a GitHub repository. This file is rendered and displayed automatically when someone visits the repository.

This document includes helper text that will not be displayed when rendered. Any text between the less-than sign + exclamation mark + three hyphen-minus (<!---) and matching three hyphen-minus + greater-than sign will not be displayed. This helper text can be deleted once the corresponding section is completed.

This template has a number of fields that can be searched and replaced with other text:
 - <Device_Name> Replace this with filename-friendly version of the device with underscores. e.g., Open_Wobble_Switch
 - <DeviceName> Replace this with the human-readable name of the device with spaces. e.g., Open Wobble Switch
 - <DesignerName> Replace this with the person or organization responsible for the design. e.g., John Doe.
 - <Repository_Link> Replace this with the web address for the repository. e.g., (e.g., https://github.com/makersmakingchange/Open-Wobble-Switch))
 - <MMCWebLink> This is the website address including an alphanumeric id for the Makers Making Change Website. e.g., 01tJR000000698oYAA. This will come from MMC staff.  
 - <MaterialCost> Replace this with the dollar cost and currency (CAD, USD, etc.) of the materials of the device.
 - <ShippingCost> Replace this with the dollar cost and currency (CAD, USD, etc.) of shipping the device (if possible).
 - <YEAR> year(s) of the copyright
 
Any text that is currently holding a space / is an instruction for the person filling in the README is in all capitals, to make it easier to see them in a rendered version.

--->
 

# Willow Joystick


## Overview
<!--- A brief summary of the project. What it does, who it is for, how much it costs. --->
The Willow joystick is a low force joystick that builds off the magnetic gimbal from the LipSync. The Willow is intended to fill a gap in the Makers Making Change joystick selection and provide a low force option similar to something like the Feather joystick.  

The device is comprised of off-the-shelf electronics and 3D printed parts. 

The Willow Joystick is open assistive technology (OpenAT). Under the terms of the open source licenses, the device may be built, used, and improved upon by anyone.

The overall cost of materials is yet to be determined, but the goal is to keep it below the price of the LipSync (plus $8 for component shipping).

<img src="Photos/Willow_Joystick.JPG" width="500" alt="MVP design of Willow joystick.">

## Makers Making Change Assistive Device Library
Device not yet published to MMC library

## How to Obtain the Device
### 1. Do-it-Yourself (DIY) or Do-it-Together (DIT)

This is an open-source assistive technology, so anyone is free to build it. All of the files and instructions required to build the device are contained within this repository. Refer to the Maker Guide below.
As this is a work in progress device not yet published, some files such as User Guide or Maker Guide may not be finished, or even started.

### 2. Request a build of this device

The Willow joystick is still a work in progress, so you cannot request a build of the device at this time.

<!--- You may also submit a build request through the [Makers Making Change Assistive Device Library Listing](<MMCWebLink>) to have a volunteer maker build the device. As the requestor, you are responsible for reimbursing the maker for the cost of materials and any shipping.--->

### 3. Build this device for someone else

The Willow joystick is still a work in progress, so you cannot build the device through the website at this time. Working BoM and build files may be available in this repository.
<!--- If you have the skills and equipment to build this device, and would like to donate your time to create the device for someone who needs it, visit the [MMC Maker Wanted](https://makersmakingchange.com/maker-wanted/) section.--->


## Build Instructions
<!--- Outline the major steps required to create a build --->

### 1. Read through the Maker Guide

The [Maker Guide](/Documentation/Willow_Joystick_Maker_Guide.pdf)  contains all the necessary information to build this device, including tool lists, assembly instructions, programming instructions (if applicable) and testing.
The Maker Guide may not be available at this stage in the project.


### 2. Order the Off-The-Shelf Components

The [Bill of Materials](/Documentation/Willow_Joystick_BOM.xlsx) lists all of the parts and components required to build the device.
A Bill of Materials may not be available at this stage in the project, and is subject to change.


### 3. Print the 3D Printable components

All of the files and individual print files can be found in the [/Build_Files/3D_Printing_Files](/Build_Files/3D_Printing_Files/) folder.
At this stage in the project, these are not the final files and are subject to change at any time.

### 4. Assemble the Willow Joystick

Reference the Assembly Guide section of the [Maker Guide](/Documentation/Willow_Joystick_Maker_Guide.pdf) for the tools and steps required to build the device.

## How to improve this Device
As open source assistive technology, you are welcomed and encouraged to improve upon the design. 

## Files
### Documentation
<!--- Update the name, link, and version for documentation --->
| Document             | Version | Link |
|----------------------|---------|------|
| Design Rationale     | 0.1     | [Willow_Joystick_Design_Rationale](/Documentation/<Device_Name>_Design_Rationale.pdf)     |
| Maker Guide          | 0.1     | [Willow_Joystick_Maker_Guide](/Documentation/<Device_Name>_Maker_Guide.pdf)     |
| Bill of Materials    | 0.1     | [Willow_Joystick_Bill_of_Materials](/Documentation/<Device_Name>_BOM.xlsx)     |
| User Guide           | 0.1     | [Willow_Joystick_User_Guide](/Documentation/<Device_Name>_User_Guide.pdf)    |
| Changelog            | 0.1     | [Changelog](CHANGES.txt)     |

### Design Files
 - [CAD Files](/Design_Files/CAD_Design_Files)
 - [PCB Files](/Design_Files/PCB_Design_Files)

### Build Files
 - [3D Printing Files](/Build_Files/3D_Printing_Files)
 - [PCB Build Files](/Build_Files/PCB_Build_Files)
 - [Firmware Files](/Build/Firmware_Files)


## License
Copyright (c) 2024 Neil Squire Society.

This repository describes Open Hardware:
 - Everything needed or used to design, make, test, or prepare the <DeviceName> is licensed under the [CERN 2.0 Weakly Reciprocal license (CERN-OHL-W v2) or later](https://cern.ch/cern-ohl ) .
 - All software is under the [GNU General Public License v3.0 (GPL-3.0)](https://www.gnu.org/licenses/gpl.html).
 - Accompanying material such as instruction manuals, videos, and other copyrightable works that are useful but not necessary to design, make, test, or prepare the Willow Joystick are published under a [Creative Commons Attribution-ShareAlike 4.0 license (CC BY-SA 4.0)](https://creativecommons.org/licenses/by-sa/4.0/) .

You may redistribute and modify this documentation and make products using it under the terms of the [CERN-OHL-W v2](https://cern.ch/cern-ohl).
This documentation is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE.
Please see the CERN-OHL-W v2 for applicable conditions.

Source Location: https://github.com/makersmakingchange/Willow-Joystick

## Attribution
<!--- Provide any necessary attribution for designs or components that are included in the device or as part of the project. --->
The device was designed by Brad Wellington. 

<!--- This is the attribution for the template. --->
The documentation template was created by Makers Making Change / Neil Squire Society and is used under a CC BY-SA 4.0 license. It is available at the following link: [https://github.com/makersmakingchange/OpenAT-Template](https://github.com/makersmakingchange/OpenAT-Template)

### Contributors
<!--- List the names of the people that contributed to the design. This could include the original source of the idea, designers, testers, documenters, etc. --->
Designers:
 - Brad Wellington
 - Stephen Moyer

Testers:
 - <TESTER 1>
 - <TESTER 2>


---

## About Makers Making Change
<!--- This is standard boilerplate for Makers Making Change. No changes should be required. --->
[<img src="https://raw.githubusercontent.com/makersmakingchange/makersmakingchange/main/img/mmc_logo.svg" width="500" alt="Makers Making Change Logo">](https://www.makersmakingchange.com/)

Makers Making Change is a program of [Neil Squire](https://www.neilsquire.ca/), a Canadian non-profit that uses technology, knowledge, and passion to empower people with disabilities.

Makers Making Change leverages the capacity of community based Makers, Disability Professionals and Volunteers to develop and deliver affordable Open Source Assistive Technologies.

 - Website: [www.MakersMakingChange.com](https://www.makersmakingchange.com/)
 - GitHub: [makersmakingchange](https://github.com/makersmakingchange)
 - X (formerly Twitter): [@makermakechange](https://twitter.com/makermakechange)
 - Instagram: [@makersmakingchange](https://www.instagram.com/makersmakingchange)
 - Facebook: [makersmakechange](https://www.facebook.com/makersmakechange)
 - LinkedIn: [Neil Squire Society](https://www.linkedin.com/company/neil-squire-society/)
 - Thingiverse: [makersmakingchange](https://www.thingiverse.com/makersmakingchange/about)
 - Printables: [MakersMakingChange](https://www.printables.com/@MakersMakingChange)

### Contact Us
For technical questions, to get involved, or to share your experience we encourage you to [visit our website](https://www.makersmakingchange.com/) or [contact us](https://www.makersmakingchange.com/s/contact).
