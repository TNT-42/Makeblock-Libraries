/**
 * \par Copyright (C), 2012-2016, MakeBlock
 * \class   MeEncoderNew
 * \brief   Driver for Me Encoder New module.
 * @file    MeEncoderNew.cpp
 * @author  MakeBlock
 * @version V1.0.0
 * @date    2016/03/18
 * @brief   Driver for Me Encoder New module.
 *
 * \par Copyright
 * This software is Copyright (C), 2012-2016, MakeBlock. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * \par Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * \par Description
 * This file is a drive for Me EncoderNew device, The Me EncoderNew inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * \par Method List:
 *
 *    1. void MeEncoderNew::begin();
 *    2. void MeEncoderNew::reset();
 *    3. void MeEncoderNew::move(long angle, float speed, float lock_state);
 *    4. void MeEncoderNew::moveTo(long angle, float speed,float lock_state);
 *    5. void MeEncoderNew::runSpeed(int speed);
 *    6. void MeEncoderNew::runTurns(long turns, float speed,float lock_state);
 *    7. void MeEncoderNew::setSpeedPID(float p,float i,float d);
 *    8. void MeEncoderNew::setPosPID(float p,float i,float d);
 *    8. void MeEncoderNew::reset();
 *    9. void MeEncoderNew::setMode(uint8_t mode);
 *    10. void MeEncoderNew::setPWM(int pwm);
 *    11. long MeEncoderNew::getCurrentPosition();
 *    12. void MeEncoderNew::getSpeedPID(float * p,float * i,float * d);
 *    13. void MeEncoderNew::getPosPID(float * p,float * i,float * d);
 *    14. float MeEncoderNew::getCurrentSpeed();
 *    15. void MeEncoderNew::sendCmd();
 *    16. float MeEncoderNew::getRatio();
 *    17. void MeEncoderNew::setRatio(float r);
 *    18. int MeEncoderNew::getPulse();
 *    19. void MeEncoderNew::setPulse(int p);
 *    20. void MeEncoderNew::setDevid(int devid);
 *    21. void MeEncoderNew::setMode(uint8_t mode);
 *    22. void MeEncoderNew::setPWM(int pwm);
 *    23.void MeEncoderNew::runSpeedAndTime(float speed, float time, float lock_state);
 *
 * \par History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Mark Yan        2016/03/18     1.0.0            build the new
 * </pre>
 *
 * @example EncoderMotorTestMoveTo.ino
 * @example EncoderMotorTestRunSpeed.ino
 * @example EncoderMotorTestRunSpeedAndTime.ino
 * @example EncoderMotorTestRunTurns.ino
 */

#include "MeEncoderNew.h"
#define HOLD 0x40
#define SYNC 0x80
// move state and function
#define CMD_RESET         0x00
#define CMD_MOVE_TO       0x01
#define CMD_MOVE          0x02
#define CMD_MOVE_SPD      0x03
#define CMD_STOP          0x05

// config function
#define CMD_SET_SPEED_PID 0x10
#define CMD_SET_POS_PID   0x11
#define CMD_SET_MODE      0x13
#define CMD_SET_PWM       0x14
#define CMD_SET_RATIO     0x15
#define CMD_SET_PULSE     0x16
#define CMD_SET_DEVID     0x17
// get motor status
#define CMD_GET_SPEED_PID       0x20
#define CMD_GET_POS_PID         0x21
#define CMD_GET_POS             0x23
#define CMD_GET_SPEED           0x24
#define CMD_GET_RATIO           0x25
#define CMD_GET_PULSE           0x26

/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you can set any slot for the Encoder Motor New device. 
 * \param[in]
 *   port - RJ25 port from PORT_1 to M2
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
MeEncoderNew::MeEncoderNew(uint8_t addr,uint8_t slot)
{
  _slot = slot - 1;
  address = addr;
}

/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you can set any slot for the Encoder Motor New device.
 * \param[in]
 *   slot - SLOT1 or SLOT2
 */
MeEncoderNew::MeEncoderNew(uint8_t slot)
{
  _slot = slot - 1;
  address = 0x9;
}

/**
 * Alternate Constructor which can call your own function to map the Encoder Motor New to arduino port,
 * you should initialized slot and slaveAddress here for the Encoder Motor New device.
 * \param[in]
 *   None
 */
MeEncoderNew::MeEncoderNew()
{
  address = 0x09;
}

/**
 * \par Function
 *    begin
 * \par Description
 *    Initialize Encoder Motor New.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::begin()
{
  Wire.begin();
}

/**
 * \par Function
 *    move
 * \par Description
 *    Motor move.
 * \param[in]
 *    angle - The angle move of Motor New.
 * \param[in]
 *    speed - The speed move of Motor New.
 * \param[in]
 *    lock_state - The lock state of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::move(long angle, float speed, float lock_state)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_MOVE;
  memcpy(cmdBuf + 2, &lock_state, 4);
  memcpy(cmdBuf + 6, &angle, 4);
  memcpy(cmdBuf + 10,&speed,4);
  sendCmd();
}

/**
 * \par Function
 *    moveTo
 * \par Description
 *    Motor New move to the aim.
 * \param[in]
 *    angle - The angle move of Motor New.
 * \param[in]
 *    speed - The speed move of Motor New.
 * \param[in]
 *    lock_state - The lock state of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::moveTo(long angle, float speed,float lock_state)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_MOVE_TO;
  memcpy(cmdBuf + 2, &lock_state, 4);
  memcpy(cmdBuf + 6, &angle, 4);
  memcpy(cmdBuf + 10,&speed,4);
  sendCmd();
}

/**
 * \par Function
 *    runSpeed
 * \par Description
 *    The speed of Motor's movement.
 * \param[in]
 *    speed - The speed move of Motor.
 * \param[in]
 *    lock_state - The lock state of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::runSpeed(float speed,float lock_state)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_MOVE_SPD;
  memcpy(cmdBuf + 2, &lock_state, 4);
  memcpy(cmdBuf + 6, &speed, 4);
  sendCmd();
}

/**
 * \par Function
 *    runTurns
 * \par Description
 *    Motor move turns.
 * \param[in]
 *    turns - The turns move of Motor.
 * \param[in]
 *    speed - The speed move of Motor.
 * \param[in]
 *    lock_state - The lock state of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::runTurns(long turns, float speed,float lock_state)
{
    return move(turns * 360, speed,lock_state);
}

/**
 * \par Function
 *    reset
 * \par Description
 *    Reset the parameter of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::reset()
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_RESET;
  sendCmd();
}

/**
 * \par Function
 *    setSpeedPID
 * \par Description
 *    Set speed PID for Motor.
 * \param[in]
 *    p - P means Proportion.
 * \param[in]
 *    i - I means Integration.
 * \param[in]
 *    d - D means Differentiation.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setSpeedPID(float p,float i,float d)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_SPEED_PID;
  memcpy(&cmdBuf[2],&p,4);
  memcpy(&cmdBuf[6],&i,4);
  memcpy(&cmdBuf[10],&d,4);
  sendCmd();
}

/**
 * \par Function
 *    setPosPID
 * \par Description
 *    Set pos PID for Motor.
 * \param[in]
 *    p - P means Proportion.
 * \param[in]
 *    i - I means Integration.
 * \param[in]
 *    d - D means Differentiation.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setPosPID(float p,float i,float d)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_POS_PID;
  memcpy(&cmdBuf[2],&p,4);
  memcpy(&cmdBuf[6],&i,4);
  memcpy(&cmdBuf[10],&d,4);
  sendCmd();
}

/**
 * \par Function
 *    setMode
 * \par Description
 *    Set the work mode to Motor.
 * \param[in]
 *    mode - The work mode of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setMode(uint8_t mode)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_MODE;
  cmdBuf[2] = mode;
  sendCmd();
}

/**
 * \par Function
 *    setPWM
 * \par Description
 *    Set the PWM to Motor.
 * \param[in]
 *    pwm - Pulse-Width Modulation.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setPWM(int pwm)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_PWM;
  memcpy(cmdBuf+2,&pwm,2);
  sendCmd();
}

/**
 * \par Function
 *    getCurrentPosition
 * \par Description
 *    The current position of Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
long MeEncoderNew::getCurrentPosition()
{
  long pos;
  char buf[8];
  Wire.beginTransmission(address); 
  Wire.write(_slot);      
  Wire.write(CMD_GET_POS);            
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);   
  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read();
  }
  pos = *(long*)buf;
  return pos;
}

/**
 * \par Function
 *    getSpeedPID
 * \par Description
 *    Get PID from Motor.
 * \param[in]
 *    p - P means Proportion.
 * \param[in]
 *    i - I means Integration.
 * \param[in]
 *    d - D means Differentiation.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::getSpeedPID(float * p,float * i,float * d)
{
  char buf[8];

  Wire.beginTransmission(address); 
  Wire.write(_slot);       
  Wire.write(CMD_GET_SPEED_PID);             
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)12);  

  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  *p = *(float*)buf;

  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  *i = *(float*)buf;

  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  *d = *(float*)buf;
}

/**
 * \par Function
 *    getPosPID
 * \par Description
 *    Get PID from Motor.
 * \param[in]
 *    p - P means Proportion.
 * \param[in]
 *    i - I means Integration.
 * \param[in]
 *    d - D means Differentiation.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::getPosPID(float * p,float * i,float * d)
{
  char buf[8];

  Wire.beginTransmission(address); 
  Wire.write(_slot);       
  Wire.write(CMD_GET_POS_PID);             
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)12);  

  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  *p = *(float*)buf;

  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  *i = *(float*)buf;

  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  *d = *(float*)buf;
}

/**
 * \par Function
 *    getCurrentSpeed
 * \par Description
 *    The current speed of Motor's movement.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
float MeEncoderNew::getCurrentSpeed()
{
  char buf[8];
  float speed;
  Wire.beginTransmission(address); 
  Wire.write(_slot);      
  Wire.write(CMD_GET_SPEED);             
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);   
  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  speed = *(float*)buf;
  return speed;
}

/**
 * \par Function
 *    sendCmd
 * \par Description
 *    Send command to Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::sendCmd()
{
  Wire.beginTransmission(address); 
  for(int i=0;i<18;i++)
    Wire.write(cmdBuf[i]);       
  Wire.endTransmission();
}

/**
 * \par Function
 *    getRatio
 * \par Description
 *    Get the ratio of Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the ratio of Motor.
 * \par Others
 *    None
 */
float MeEncoderNew::getRatio()
{ 
  char buf[8];
  float ratio;
  Wire.beginTransmission(address); 
  Wire.write(_slot);      
  Wire.write(CMD_GET_RATIO);             
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)4);   
  for(int i=0;i<4;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  ratio = *(float*)buf;
  return ratio;
}

/**
 * \par Function
 *    setRatio
 * \par Description
 *    Set the ratio to Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setRatio(float ratio)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_RATIO;
  memcpy(cmdBuf+2,&ratio,4);
  sendCmd();
}

/**
 * \par Function
 *    getPulse
 * \par Description
 *    Get the pulse of Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    Return the pulse of Motor.
 * \par Others
 *    None
 */
int MeEncoderNew::getPulse()
{ 
  char buf[8];
  int pulse;
  Wire.beginTransmission(address); 
  Wire.write(_slot);      
  Wire.write(CMD_GET_PULSE);             
  Wire.endTransmission(0);
  Wire.requestFrom(address,(uint8_t)2);   
  for(int i=0;i<2;i++)   
  { 
    buf[i] = Wire.read(); 
  }
  pulse = *(int*)buf;
  return pulse;
}

/**
 * \par Function
 *    setPulse
 * \par Description
 *    Set the pulse to Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setPulse(int pulse)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_PULSE;
  memcpy(cmdBuf+2,&pulse,2);
  sendCmd();
}

/**
 * \par Function
 *    setDevid
 * \par Description
 *    Set the devid to Motor.
 * \param[in]
 *    None
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::setDevid(uint8_t devid)
{
  cmdBuf[0] = _slot;
  cmdBuf[1] = CMD_SET_DEVID;
  cmdBuf[2] = devid;
  sendCmd();
}

/**
 * \par Function
 *    runSpeedAndTime
 * \par Description
 *    The speed and time of Motor's movement.
 * \param[in]
 *    speed - The speed move of Motor.
 * \param[in]
 *    time - The time move of Motor.
 * \param[in]
 *    lock_state - The lock state of Motor.
 * \par Output
 *    None
 * \par Return
 *    None
 * \par Others
 *    None
 */
void MeEncoderNew::runSpeedAndTime(float speed, float time, float lock_state)
{
  if(_lastTime == 0)
  {
    _lastTime = millis();
    runSpeed(speed,lock_state);
  }

  if(millis() - _lastTime > (1000 * time))
  {
    _lastTime = 0;
    runSpeed(0,lock_state);
  }
}
