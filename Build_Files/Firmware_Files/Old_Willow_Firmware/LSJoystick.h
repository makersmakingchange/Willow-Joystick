/* 
* File: LSJoystick.h
* Firmware: LipSync
* Developed by: MakersMakingChange
* Version: v4.0.rc1 (26 January 2024)
  License: GPL v3.0 or later

  Copyright (C) 2024 Neil Squire Society
  This program is free software: you can redistribute it and/or modify it under the terms of
  the GNU General Public License as published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.
  If not, see <http://www.gnu.org/licenses/>
*/

//Header definition
#ifndef _LSJOYSTICK_H
#define _LSJOYSTICK_H

#include <Tlv493d.h>                    //Infinion TLV493 magnetic sensor

#include <Arduino.h>

#define JOY_RAW_BUFF_SIZE 10            //The size of joystickRawBuffer
#define JOY_INPUT_BUFF_SIZE 5           //The size of joystickInputBuffer
#define JOY_OUTPUT_BUFF_SIZE 5          //The size of joystickOutputBuffer
#define JOY_CENTER_BUFF_SIZE 5          //The size of joystickCenterBuffer

#define JOY_CALIBR_ARRAY_SIZE 5         //The magnetInputCalibration array size
#define JOY_MAG_SAMPLE_SIZE 5           //The sample size used for averaging magnet samples 

//Joystick magnetic directions
#define JOY_DIRECTION_DEFAULT 1
#define JOY_DIRECTION_INVERSE -1
#define JOY_DIRECTION_FAULT 0           //Can be used to notify the end user that there is an issue with hall sensor setup

#define JOY_DIRECTION_X -1              // Coordinate system for joystic axes. Depends on sensor arrangement
#define JOY_DIRECTION_Y -1              // Coordinate system for joystic axes. Depends on sensor arrangement

#define JOY_Z_DIRECTION_THRESHOLD 9     //The threshold used in z axis direction detection 

#define JOY_RAW_XY_MAX 30.0             //The max raw x or y of a calibration point in mT

#define JOY_INPUT_XY_MAX 1024           //The max range of mapped input from float to int(-1024 to 1024)

#define JOY_INPUT_CHANGE_TOLERANCE 0.1 //The output change tolerance in mT

#define JOY_INPUT_DEADZONE 1.0          //The input deadzone in mT

#define JOY_OUTPUT_DEADZONE_STATUS true //The default output deadzone state (True = enable , False = disable)

#define JOY_OUTPUT_DEADZONE_FACTOR 0.05 //The default output deadzone factor (%5 of JOY_INPUT_XY_MAX)

#define JOY_OUTPUT_RANGE_LEVEL 5        //The default output mouse cursor range level or output movement upper range 

#define JOY_OUTPUT_XY_MAX_GAMEPAD  127


class LSJoystick {
  private:
    Tlv493d Tlv493dSensor = Tlv493d();                                    //Create an object of Tlv493d class
    LSCircularBuffer <pointFloatType> joystickRawBuffer;                  //Create a buffer of type pointFloatType to push raw readings 
    LSCircularBuffer <pointIntType> joystickInputBuffer;                  //Create a buffer of type pointIntType to push mapped and filtered readings 
    LSCircularBuffer <pointIntType> joystickOutputBuffer;                 //Create a buffer of type pointIntType to push mapped readings 
    LSCircularBuffer <pointFloatType> joystickCenterBuffer;               //Create a buffer of type pointFloatType to push center input readings     
    int applyDeadzone(int input);                                         //Apply deadzone to the input based on deadzoneValue and JOY_INPUT_XY_MAX.
    bool canSkipInputChange(pointFloatType inputPoint);                  //Check if the output change can be skipped (Low-Pass Filter)
    pointIntType processInputReading(pointFloatType inputPoint);          //Process the input readings and map the input reading from square to circle. (-1024 to 1024 output )
    pointIntType linearizeOutput(pointIntType inputPoint);                //Linearize the output.
    pointIntType processOutputResponse(pointIntType inputPoint);          //Process the output (Including linearizeOutput methods and speed control)
    int mapFloatInt(float input, float inputStart, float inputEnd, int outputStart, int outputEnd); //Custom map function to map float to int.
    pointFloatType absPoint(pointFloatType inputPoint);                   //Get the absolute value of the point.
    float magnitudePoint(pointFloatType inputPoint);                      //Magnitude of a point from er (0,0)
    float magnitudePoint(pointFloatType inputPoint, pointFloatType offsetPoint); //Magnitude of a point from offset center point / Compensation point
    int sgn(float val);                                                   //Get the sign of the value.
    pointFloatType magnetInputCalibration[JOY_CALIBR_ARRAY_SIZE];         //Array of calibration points.
    pointFloatType _rawPoint;                                             //Raw x and y values used for debugging purposes.
    pointIntType _inputPoint;                                             //Mapped and filtered x and y values
    pointIntType _outputPoint;                                            //Output x and y values
    int _joystickXDirection;                                              //Corrected x value after applying _magnetXDirection
    int _joystickYDirection;                                              //Corrected y value after applying _magnetYDirection
    int _magnetZDirection;                                                //Direction of z ( if the board has flipped and has resulted in z-axis being flipped )
    int _magnetXDirection;                                                //Direction of x ( if the board has flipped and has resulted in x axis being flipped )
    int _magnetYDirection;                                                //Direction of y ( if the board has flipped and has resulted in y axis being flipped )
    bool _deadzoneEnabled;                                                //Is deadzone enabled?
    float _deadzoneFactor;                                                //Deadzone factor in percent of total value or max reading JOY_INPUT_XY_MAX
    int _deadzoneValue;                                                   //The calculated deadzone value based on deadzone factor and maximum value JOY_INPUT_XY_MAX.
    int _rangeLevel;                                                      //The range level from 0 to 10 which is used as speed levels.
    int _rangeValue;                                                      //The calculated range value based on range level and an equation. This is maximum output value  for each range level.
    float _inputRadius;                                                   //The minimum radius of operating area calculated using calibration points.
    bool _skipInputChange;                                                //The flag to low-pass filter the input changes 
    int _operatingMode;                                                   //Operating mode, gamepad or mouse
  public:
    LSJoystick();                                                         //Constructor
    void begin();
    void clear();   
    int getMagnetXDirection();                                            //Get the X direction of the magnet.
    void setMagnetXDirection(int magnetXDirection);                       //Set or update the magnet X direction variable.
    int getMagnetYDirection();                                            //Get the Y direction of the magnet.
    void setMagnetYDirection(int magnetYDirection);                       //Set or update the magnet Y direction variable.
    int getMagnetZDirection();                                            //Get the Z direction of the magnet.
    void setMagnetZDirection();                                           //Update the magnet Z direction variable.
    void setMagnetDirection(int magnetXDirection, int magnetYDirection);  //Set magnet direction based on orientation of magnet (z axis), X and Y direction variables.
    void setDeadzone(bool deadzoneEnabled,float deadzoneFactor);          //Enable or disable deadzone and set deadzone scale factor (0.12) 
    int getOutputRange();                                                 //Get the output range or speed levels.
    void setOutputRange(int rangeLevel);                                  //Set the output range or speed levels.
    int getMinimumRadius();                                               //Get the minimum input radius for square to circle mapping.
    void setMinimumRadius();                                              //Set or update the minimum input radius for square to circle mapping.
    pointFloatType getInputCenter();                                      //Get the updated center compensation point.
    void evaluateInputCenter();                                           //Evaluate the center compensation point.
    void updateInputCenterBuffer();                                       //Push new center compensation point to joystickCenter
    pointFloatType getInputMax(int quad);                                 //Get the updated maximum input reading from the selected corner of joystick using the input quadrant. (Calibration purposes)
    void setInputMax(int quad, pointFloatType point);                     //Set the maximum input reading for each corner of joystick using the input quadrant. 
    void zeroInputMax(int quad);                                          //Zero the maximum input reading for each corner of joystick using the input quadrant. 
    void update();                                                        //Update the joystick reading to get new input from the magnetic sensor and calculate the output.
    int getXOut();                                                        //Get the output x value.
    int getYOut();                                                        //Get the output y value.
    pointFloatType getXYRaw();                                            //Get the raw x and y values.
    pointIntType getXYIn();                                               //Get the mapped and filtered x and y values.
    pointIntType getXYOut();                                              //Get the output x and y values.

};

//*********************************//
// Function   : LSJoystick 
// 
// Description: Construct LSJoystick
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
LSJoystick::LSJoystick() {
  joystickRawBuffer.begin(JOY_RAW_BUFF_SIZE);                       //Initialize joystickRawBuffer
  joystickInputBuffer.begin(JOY_INPUT_BUFF_SIZE);                   //Initialize joystickInputBuffer
  joystickOutputBuffer.begin(JOY_OUTPUT_BUFF_SIZE);                 //Initialize joystickOutputBuffer
  joystickCenterBuffer.begin(JOY_CENTER_BUFF_SIZE);                 //Initialize joystickCenterBuffer
}

//*********************************//
// Function   : begin 
// 
// Description: Initialize LSJoystick with default settings 
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::begin() {

  _inputRadius = 0.0;                                                   //Initialize _inputRadius
  _skipInputChange = false;                                            //Initialize _skipInputChange
  _operatingMode = getOperatingMode(false, false);

  Tlv493dSensor.begin();
  setMagnetDirection(JOY_DIRECTION_DEFAULT,JOY_DIRECTION_DEFAULT);      //Set default magnet direction.
  setDeadzone(JOY_OUTPUT_DEADZONE_STATUS,JOY_OUTPUT_DEADZONE_FACTOR);   //Set default deadzone status and deadzone factor.
  setOutputRange(JOY_OUTPUT_RANGE_LEVEL);                               //Set default output range level or speed level.
  clear();                                                              //Clear calibration array and joystickOutputBuffer.
}

//*********************************//
// Function   : clear 
// 
// Description: Clear LSJoystick class
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::clear() {

  //Initialize magnetInputCalibration array
  magnetInputCalibration[0] = {0.00, 0.00};           //Center point
  magnetInputCalibration[1] = {0.00, 0.00};
  magnetInputCalibration[2] = {0.00, 0.00};
  magnetInputCalibration[3] = {0.00, 0.00};
  magnetInputCalibration[4] = {0.00, 0.00};


  joystickRawBuffer.pushElement({0.0,0.0});           //Initialize joystickRawBuffer
  joystickInputBuffer.pushElement({0, 0});            //Initialize joystickInputBuffer
  joystickOutputBuffer.pushElement({0, 0});           //Initialize joystickOutputBuffer
  
}


//*********************************//
// Function   : getMagnetXDirection 
// 
// Description: Get the set magnet x direction ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  void
// 
// Return     : direction : int : Magnet x direction
//*********************************//
int LSJoystick::getMagnetXDirection() {
  return _magnetXDirection;
}

//*********************************//
// Function   : setMagnetXDirection 
// 
// Description: Set magnet x direction ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  magnetXDirection : int : Magnet x direction
// 
// Return     : void
//*********************************//
void LSJoystick::setMagnetXDirection(int magnetXDirection){
   _magnetXDirection = magnetXDirection;
}

//*********************************//
// Function   : getMagnetYDirection 
// 
// Description: Get the set magnet y direction ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  void
// 
// Return     : direction : int : Magnet y direction
//*********************************//
int LSJoystick::getMagnetYDirection() {
  return _magnetYDirection;
}

//*********************************//
// Function   : setMagnetYDirection 
// 
// Description: Set magnet y direction ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  magnetYDirection : int : Magnet y direction
// 
// Return     : void
//*********************************//
void LSJoystick::setMagnetYDirection(int magnetYDirection){
   _magnetYDirection = magnetYDirection;
}

//*********************************//
// Function   : getMagnetZDirection 
// 
// Description: Get the set magnet z direction ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  void
// 
// Return     : direction : int : Magnet z direction
//*********************************//
int LSJoystick::getMagnetZDirection() {
  return _magnetZDirection;
}


//*********************************//
// Function   : setMagnetZDirection 
// 
// Description: Set magnet z direction based on z direction and JOY_Z_DIRECTION_THRESHOLD.
//              ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::setMagnetZDirection() {

  float zReading = 0.0;
  for (int i = 0 ; i < JOY_MAG_SAMPLE_SIZE ; i++){        //Get the average of 5 z direction reading 
    Tlv493dSensor.updateData();
    zReading += Tlv493dSensor.getZ();
  }
  zReading = ((float) zReading) / JOY_MAG_SAMPLE_SIZE;
   
  if (zReading < -1 * JOY_Z_DIRECTION_THRESHOLD)          //Set z direction to inverse 
  {
    _magnetZDirection = JOY_DIRECTION_INVERSE;
  }
  else if (zReading > JOY_Z_DIRECTION_THRESHOLD){         //Set z direction to default 
    _magnetZDirection = JOY_DIRECTION_DEFAULT;
  }
  else {
    _magnetZDirection = JOY_DIRECTION_FAULT;             //Set z direction to fault
  }

}

//*********************************//
// Function   : setMagnetDirection 
// 
// Description: Set joystick x and y final magnet directions based on x,y, and z magnet directions.
//              ( Default = 1, Inverse = -1, Fault = 0)
// 
// Arguments :  magnetXDirection : int : Magnet x direction.
//              magnetYDirection : int : Magnet y direction.
// 
// Return     : void
//*********************************//
void LSJoystick::setMagnetDirection(int magnetXDirection,int magnetYDirection) {

  //Set new x,y, and z magnet directions
  setMagnetXDirection(magnetXDirection);
  setMagnetYDirection(magnetYDirection);
  setMagnetZDirection();
  
  //Evaluate joystick x and y final magnet directions
  _joystickXDirection = -1 * _magnetZDirection * _magnetXDirection; // Flip x- axis due to flipped sensor
  _joystickYDirection = 1 * _magnetZDirection * _magnetYDirection; // Flip y- axis due to flipped sensor
}


//*********************************//
// Function   : setDeadzone 
// 
// Description: Set the deadzone value based on deadzone status and deadzone factor.
// 
// Arguments :  deadzoneEnabled : bool  : is deadzone enabled?
//              deadzoneFactor  : float : deadzoneFactor from 0.01 to 1.0
// 
// Return     : void
//*********************************//
void LSJoystick::setDeadzone(bool deadzoneEnabled,float deadzoneFactor){
  _deadzoneEnabled = deadzoneEnabled;
  
  _deadzoneFactor = deadzoneFactor;
  //Set the deadzone value if it's enabled. The deadzone value is zero if it's disabled.
  //deadzone value is the _deadzoneFactor multiplied by JOY_INPUT_XY_MAX.
  (_deadzoneEnabled) ? _deadzoneValue = round(JOY_INPUT_XY_MAX*_deadzoneFactor):_deadzoneValue=0;   
}

//*********************************//
// Function   : getOutputRange
// 
// Description: Get the output range level or speed level ( 0 to 10 )
// 
// Arguments :  
// 
// Return     : range level : int : range level or speed level ( 0 to 10 )
//*********************************//
int LSJoystick::getOutputRange(){
  return _rangeLevel;
}

//*********************************//
// Function   : setOutputRange 
// 
// Description: Set the output range value based on range level or speed level ( 0 to 10 )
// 
// Arguments :  rangeLevel : int : range level or speed level ( 0 to 10 )
// 
// Return     : void
//*********************************//
void LSJoystick::setOutputRange(int rangeLevel){
  if (_operatingMode == CONF_OPERATING_MODE_MOUSE){
    //Calculate the output range value
    _rangeValue = (int)((0.125 * sq(rangeLevel)) + ( 0.3 * rangeLevel ) + 2);       //Polynomial 
    // [0:2; 1:2; 2:3; 3:4; 4:5; 5:7; 6:8; 7:10; 8:12; 9:15; 10:18]
    
    //_rangeValue = (int)((1.05 * exp(( 0.175 * rangeLevel) + 1.1)) - 1);           //Exponential   
    //Serial.print("_rangeValue:");
    //Serial.println(_rangeValue);
  } else if (_operatingMode == CONF_OPERATING_MODE_GAMEPAD){
    _rangeValue = JOY_OUTPUT_XY_MAX_GAMEPAD ;
  }
  _rangeLevel = rangeLevel;
}

//*********************************//
// Function   : getMinimumRadius 
// 
// Description: Get the minimum operating range as radius of circle from center point using calibration points.
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
int LSJoystick::getMinimumRadius(){
  return _inputRadius;
}

//*********************************//
// Function   : setMinimumRadius 
// 
// Description: Set the minimum operating range as radius of circle from center point using calibration points.
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::setMinimumRadius(){
  float tempRadius = 0.0;
  pointFloatType tempPoint = {JOY_RAW_XY_MAX,JOY_RAW_XY_MAX};
  _inputRadius = magnitudePoint(tempPoint,magnetInputCalibration[0])/sqrt(2.0);
  //Loop through calibration points and calculate the smallest magnitude from center point
  for (int i = 1; i < JOY_CALIBR_ARRAY_SIZE; i++) {
    tempRadius = (sqrt(sq(magnetInputCalibration[i].x - magnetInputCalibration[0].x) + sq(magnetInputCalibration[i].y - magnetInputCalibration[0].y))/sqrt(2.0));
    //Make sure the calibration point is valid and initial value of _inputRadius is charged 
    if(magnitudePoint(magnetInputCalibration[i])> 0.0 && (tempRadius<_inputRadius)) {  //Set smallest magnitude as radius
      _inputRadius = tempRadius; 
    }
  }
  //Serial.println(_inputRadius);
}


//*********************************//
// Function   : getInputCenter 
// 
// Description: Get the compensation center point from magnetInputCalibration array.
// 
// Arguments :  void
// 
// Return     : center point : pointFloatType : The center point
//*********************************//
pointFloatType LSJoystick::getInputCenter() {
  return magnetInputCalibration[0];
}

//*********************************//
// Function   : evaluateInputCenter
// 
// Description: Evaluate the compensation center point fromjoystickCenterBuffer.
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::evaluateInputCenter() {
  float centerX = 0.0;
  float centerY = 0.0;
  pointFloatType centerPoint = {centerX,centerY};
  for(int centerIndex = 0; centerIndex < JOY_CENTER_BUFF_SIZE; centerIndex++){
    centerPoint = joystickCenterBuffer.getElement(centerIndex);
    centerX+=centerPoint.x;
    centerY+=centerPoint.y;
  }
  centerX=centerX/JOY_CENTER_BUFF_SIZE;
  centerY=centerY/JOY_CENTER_BUFF_SIZE;
  magnetInputCalibration[0] = {centerX,centerY};
}


//*********************************//
// Function   : updateInputCenterBuffer
// 
// Description: Update the compensation center point buffer by pushing new value into joystickCenterBuffer.
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::updateInputCenterBuffer() {
  Tlv493dSensor.updateData();
  joystickCenterBuffer.pushElement({Tlv493dSensor.getY(), Tlv493dSensor.getX()});   //Joystick direction mapping
}


//*********************************//
// Function   : getInputMax 
// 
// Description: Get the max point of the input quadrant from magnetInputCalibration array.
// 
// Arguments :  quad : int : input quadrant
// 
// Return     : max point : pointFloatType : The max point
//*********************************//
pointFloatType LSJoystick::getInputMax(int quad) {
  Tlv493dSensor.updateData();
  //Get new x and y reading
  pointFloatType tempCalibrationPoint = {Tlv493dSensor.getY(), Tlv493dSensor.getX()};
//  Serial.print("x:");
//  Serial.print(tempCalibrationPoint.x);
//  Serial.print("y:");
//  Serial.println(tempCalibrationPoint.y);

  //Update the calibration point and minimum radius 
  //Make sure it's a valid quadrant and if new point has larger magnitude from center ( calibration timer loop )
  if((quad >= 0) && 
  (quad < JOY_CALIBR_ARRAY_SIZE) && 
  magnitudePoint(tempCalibrationPoint,magnetInputCalibration[0])>magnitudePoint(magnetInputCalibration[quad],magnetInputCalibration[0])){           //The point with larger magnitude is sent as output 
    magnetInputCalibration[quad] = tempCalibrationPoint;
  }
  
  return magnetInputCalibration[quad];
}


//*********************************//
// Function   : setInputMax 
// 
// Description: Set the max point of the input quadrant in magnetInputCalibration array.
// 
// Arguments :  quad : int : input quadrant
//              inputPoint : pointFloatType : The max point
// 
// Return     : void
//*********************************//
void LSJoystick::setInputMax(int quad,pointFloatType inputPoint) {
 //Update the calibration point 
  magnetInputCalibration[quad] = inputPoint;
}

//*********************************//
// Function   : zeroInputMax 
// 
// Description: Zero the max point of the input quadrant in magnetInputCalibration array.
// 
// Arguments :  quad : int : input quadrant
// 
// Return     : void
//*********************************//
void LSJoystick::zeroInputMax(int quad) {
 //Reset or zer the calibration point 
  magnetInputCalibration[quad] = {0,0};
}

//*********************************//
// Function   : update 
// 
// Description: Set the new sensor readings, process data and push to joystickOutputBuffer
// 
// Arguments :  void
// 
// Return     : void
//*********************************//
void LSJoystick::update() {

  Tlv493dSensor.updateData();
  //Get the new readings as a point
  _rawPoint = {Tlv493dSensor.getY(), Tlv493dSensor.getX()};   
  
  _skipInputChange = canSkipInputChange(_rawPoint);
  joystickRawBuffer.pushElement(_rawPoint);                  //Push raw points to joystickRawBuffer : DON'T MOVE THIS

  if(!_skipInputChange){
    _inputPoint = processInputReading(_rawPoint);            //Mapped and filtered input readings
    joystickInputBuffer.pushElement(_inputPoint);            //Push new input point to joystickInputBuffer
    _outputPoint = processOutputResponse(_inputPoint);       //Process output by applying deadzone, speed control, and linearization
    joystickOutputBuffer.pushElement(_outputPoint);          //Push new output point to joystickOutputBuffer    
  } 
}

//*********************************//
// Function   : getXOut 
// 
// Description: Get the last processed output x value from joystickOutputBuffer
// 
// Arguments :  void
// 
// Return     : x value : int : The output x value 
//*********************************//
int LSJoystick::getXOut() {
  return joystickOutputBuffer.getLastElement().x;
}

//*********************************//
// Function   : getYOut 
// 
// Description: Get the last processed output y value from joystickOutputBuffer
// 
// Arguments :  void
// 
// Return     : x value : int : The output x value 
//*********************************//
int LSJoystick::getYOut() {
  return joystickOutputBuffer.getLastElement().y;
}

//*********************************//
// Function   : getXYRaw
// 
// Description: Get the last raw x and y values from joystickRawBuffer
// 
// Arguments :  void
// 
// Return     : output point : pointFloatType : The raw x and y point
//*********************************//
pointFloatType LSJoystick::getXYRaw() {
  return joystickRawBuffer.getLastElement();
}


//*********************************//
// Function   : getXYIn 
// 
// Description: Get the mapped x and y input point
// 
// Arguments :  void
// 
// Return     : input point : pointIntType : The input x and y point
//*********************************//
pointIntType LSJoystick::getXYIn() {
  return joystickInputBuffer.getLastElement();
}


//*********************************//
// Function   : getXYOut 
// 
// Description: Get the last processed output x and y values from joystickOutputBuffer
// 
// Arguments :  void
// 
// Return     : output point : pointIntType : The output x and y point
//*********************************//
pointIntType LSJoystick::getXYOut() {
  return joystickOutputBuffer.getLastElement();
}


//*********************************//
//********Private******************//
//*********************************//

//*********************************//
// Function   : applyDeadzone 
// 
// Description: Apply the deadzone to the output value 
// 
// Arguments :  input : int : Output without deadzone
// 
// Return     : output : int : Output with deadzone applied
//*********************************//
int LSJoystick::applyDeadzone(int input){

  //Output the input if Deadzone is not enabled 
  int output = input;
  //if Deadzone is not enabled 
  if(_deadzoneEnabled) { 
    if(abs(input)<_deadzoneValue){                    //Output zero if input < _deadzoneValue
      output=0;
    }
    else if(abs(input)>JOY_INPUT_XY_MAX-_deadzoneValue){
      output=sgn(input) * JOY_INPUT_XY_MAX;           //Output JOY_INPUT_XY_MAX if input > JOY_INPUT_XY_MAX-_deadzoneValue
    } else{
      output=input;                                  //Output the input
    }
  }
  return output;
}

//*********************************//
// Function   : canSkipInputChange 
// 
// Description: Check if the input change can be skipped  
// 
// Arguments :  inputPoint : pointFloatType : raw input reading
// 
// Return     : skipInputChange : bool : skip processing if it's true
//*********************************//
bool LSJoystick::canSkipInputChange(pointFloatType inputPoint){      
  pointFloatType prevInputPoint = joystickRawBuffer.getLastElement();           //Get the previous point from buffer 
  bool skipInputChange = abs(_rawPoint.x - prevInputPoint.x) < JOY_INPUT_CHANGE_TOLERANCE 
                 && abs(_rawPoint.y - prevInputPoint.y)  < JOY_INPUT_CHANGE_TOLERANCE;
  return skipInputChange;
}

//*********************************//
// Function   : linearizeOutput 
// 
// Description: Linearize Output value
// 
// Arguments :  inputPoint : pointIntType : Output without linearization
// 
// Return     : outputPoint : pointIntType : Output with linearization applied
//*********************************//
pointIntType LSJoystick::linearizeOutput(pointIntType inputPoint){
  pointIntType outputPoint = {0,0};                                     //Initialize outputPoint
  //Apply final mapping and speed control 
  outputPoint.x = map(inputPoint.x,-1*JOY_INPUT_XY_MAX,JOY_INPUT_XY_MAX,-1*_rangeValue,_rangeValue);
  outputPoint.y = map(inputPoint.y,-1*JOY_INPUT_XY_MAX,JOY_INPUT_XY_MAX,-1*_rangeValue,_rangeValue);
  return outputPoint;  
}

//*********************************//
// Function   : processInputReading 
// 
// Description: Process input value and map the readings
// 
// Arguments :  inputPoint : pointFloatType : Raw magnet input reading
// 
// Return     : outputPoint : pointIntType : Output with mapped reading 
//*********************************//
pointIntType LSJoystick::processInputReading(pointFloatType inputPoint) {

  //Initialize limitPoint, centeredPoint and outputPoint
  pointFloatType limitPoint = {0.00, 0.00};
  pointFloatType centeredPoint = {0.00, 0.00};
  pointIntType outputPoint = {0,0};
  
  if ((sq(inputPoint.x) + sq(inputPoint.y)) >= sq(JOY_INPUT_DEADZONE)) {
    //Center the input point
    centeredPoint = {(inputPoint.x - magnetInputCalibration[0].x)*_joystickXDirection, 
                    (inputPoint.y - magnetInputCalibration[0].y)*_joystickYDirection};
  }


  float thetaVal = atan2(centeredPoint.y, centeredPoint.x);         // Get the angle of the point

  //Find the limiting point on perimeter of circle
  limitPoint.x = sgn(centeredPoint.x) * abs(cos(thetaVal)*_inputRadius);
  limitPoint.y = sgn(centeredPoint.y) * abs(sin(thetaVal)*_inputRadius);

  //Compare the magnitude of two points from center
  //Output point on perimeter of circle if it's outside
  if ((sq(centeredPoint.x) + sq(centeredPoint.y)) >= sq(_inputRadius)) {
    centeredPoint.x = limitPoint.x; 
    centeredPoint.y = limitPoint.y; 
//    Serial.print(centeredPoint.x);  
//    Serial.print(",");  
//    Serial.println(centeredPoint.y); 
  }
    //Map the centered point to int ( -1024 to 1024 )
    outputPoint.x = mapFloatInt(centeredPoint.x, -1*_inputRadius, _inputRadius, -1*JOY_INPUT_XY_MAX, JOY_INPUT_XY_MAX);
    outputPoint.y = mapFloatInt(centeredPoint.y, -1*_inputRadius, _inputRadius, -1*JOY_INPUT_XY_MAX, JOY_INPUT_XY_MAX);
 
 

 
  return outputPoint;
}


//*********************************//
// Function   : processOutputResponse 
// 
// Description: Process output value by applying Deadzone and linearization
// 
// Arguments :  inputPoint : pointIntType : Output before applying Deadzone and linearization
// 
// Return     : outputPoint : pointIntType : Processed Output with mapped reading 
//*********************************//
pointIntType LSJoystick::processOutputResponse(pointIntType inputPoint){
  //Initialize outputPoint and deadzonedPoint
  pointIntType outputPoint,deadzonedPoint = {0,0};
  //Apply Deadzone
  deadzonedPoint = {applyDeadzone(inputPoint.x),applyDeadzone(inputPoint.y)};
  //Apply Linearization
  outputPoint = linearizeOutput(deadzonedPoint);
  return outputPoint;
}


//*********************************//
// Function   : mapFloatInt 
// 
// Description: Map float to int
// 
// Arguments :  input        : float : input value 
//              inputStart   : float : lower limit of input
//              inputEnd     : float : upper limit of input
//              outputStart  : int   : lower limit of output
//              outputEnd    : int   : upper limit of input
// 
// Return     : output : int : Mapped input value 
//*********************************//
int LSJoystick::mapFloatInt(float input, float inputStart, float inputEnd, int outputStart, int outputEnd) {

  //Evaluate input and output range
  float inputRange = inputEnd - inputStart;
  int outputRange = outputEnd - outputStart;

  int output = (int)((input - inputStart) * outputRange / inputRange + outputStart);
  
  return output;
}

//*********************************//
// Function   : absPoint 
// 
// Description: The absolute value of float point
// 
// Arguments :  inputPoint  : pointFloatType : float input point
// 
// Return     : output point : pointFloatType : absolute value of float input point
//*********************************//
pointFloatType LSJoystick::absPoint(pointFloatType inputPoint){
  return {abs(inputPoint.x), abs(inputPoint.y)};
}

//*********************************//
// Function   : magnitudePoint 
// 
// Description: The magnitude of float point from center point (0,0)
// 
// Arguments :  inputPoint  : pointFloatType : float input point
// 
// Return     : magnitude : float : magnitude of float point
//*********************************//
float LSJoystick::magnitudePoint(pointFloatType inputPoint){
  return (sqrt(sq(inputPoint.x) + sq(inputPoint.y)));
}

//*********************************//
// Function   : magnitudePoint 
// 
// Description: The magnitude of float point from offset point
// 
// Arguments :  inputPoint  : pointFloatType : float input point
//              offsetPoint  : pointFloatType : float offset center point
// 
// Return     : magnitude : float : magnitude of float point
//*********************************//
float LSJoystick::magnitudePoint(pointFloatType inputPoint, pointFloatType offsetPoint){
  return (sqrt(sq(inputPoint.x - offsetPoint.x) + sq(inputPoint.y - offsetPoint.y)));
}


//*********************************//
// Function   : sgn 
// 
// Description: The sign of float value ( -1 or +1 )
// 
// Arguments :  val : float : float input value
// 
// Return     : sign : int : sign of float value ( -1 or +1 )
//*********************************//
int LSJoystick::sgn(float val) {
  return (0.0 < val) - (val < 0.0);
}


#endif 
