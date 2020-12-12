// ------------------------------------------------------------------------
// ARD1939 - SAE J1939 Protocol Stack for Arduino Uno and Mega2560
// ------------------------------------------------------------------------
//
// IMPOPRTANT: Depending on the CAN shield used for this programming sample,
//             please make sure you set the proper CS pin in ARD1939.h.
//
//  This Arduino program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.

#include <stdlib.h>
#include <inttypes.h>
#include <SPI.h>

#include "ARD1939.h"

ARD1939 j1939;

int nCounter = 0;

void(* resetFunc) (void) = 0; //declare reset function @ address 0


// ------------------------------------------------------------------------
//  Setup routine runs on power-up or reset
// ------------------------------------------------------------------------
void setup() 
{
  // Set the serial interface baud rate
  Serial.begin(MONITOR_BAUD_RATE);
  
  // Initialize the J1939 protocol including CAN settings
  if(j1939.Init(SYSTEM_TIME) == 0)
    Serial.print("CAN Controller Init OK.\n\r\n\r");
  else{
    Serial.print("CAN Controller Init Failed.\n\r");
    delay(100);
    resetFunc();
  }    
 // Set the preferred address and address range
 j1939.SetPreferredAddress(SA_PREFERRED);
 j1939.SetAddressRange(ADDRESSRANGEBOTTOM, ADDRESSRANGETOP);
 
 // Set the message filter
 //j1939.SetMessageFilter(59999);
 
 //j1939.SetMessageFilter(65242);
 //j1939.SetMessageFilter(65259);
 //j1939.SetMessageFilter(65267);
 
 // Set the NAME
 j1939.SetNAME(NAME_IDENTITY_NUMBER,
               NAME_MANUFACTURER_CODE,
               NAME_FUNCTION_INSTANCE,
               NAME_ECU_INSTANCE,
               NAME_FUNCTION,
               NAME_VEHICLE_SYSTEM,
               NAME_VEHICLE_SYSTEM_INSTANCE,
               NAME_INDUSTRY_GROUP,
               NAME_ARBITRARY_ADDRESS_CAPABLE);
               
}// end setup

// ------------------------------------------------------------------------
// Main Loop - Arduino Entry Point
// ------------------------------------------------------------------------
void loop()
{
  // J1939 Variables
  byte nMsgId;
  byte nDestAddr;
  byte nSrcAddr;
  byte nPriority;
  byte nJ1939Status;
  
  int nMsgLen;
  
  long lPGN;
  char sString[80];
  byte pMsg[J1939_MSGLEN];
  
  // Variables for proof of concept tests
  byte msgFakeNAME[] = {0xde, 0xad, 0xbe, 0xef, 0, 0, 0, 0x69};
  
  // Establish the timer base in units of milliseconds
  delay(SYSTEM_TIME);
  
  // Call the J1939 protocol stack
  nJ1939Status = j1939.Operate(&nMsgId, &lPGN, &pMsg[0], &nMsgLen, &nDestAddr, &nSrcAddr, &nPriority);
  
  /*
  // Block certain claimed addresses
  if(nMsgId == J1939_MSG_PROTOCOL)
  {
    if(lPGN == 0x00EE00)
    {
      if(nSrcAddr >= 129 && nSrcAddr <= 134)
        j1939.Transmit(6, 0x00EE00, nSrcAddr, 255, msgFakeNAME, 8);
    
    }// end if
    
  }// end if
  */
  
  /*
  // Send out a periodic message with a length of more than 8 bytes
  // BAM Session
  if(nJ1939Status == NORMALDATATRAFFIC)
  {
    nCounter++;
    
    if(nCounter == (int)(5000/SYSTEM_TIME))
    {
      nSrcAddr = j1939.GetSourceAddress();
      j1939.Transmit(6, 59999, nSrcAddr, 255, msgLong, 15);
      nCounter = 0;
      
    }// end if
  
  }// end if
  */
  
  // Test Periodic Message
  if(nJ1939Status == NORMALDATATRAFFIC)
  {
    nCounter++;
    
    if(nCounter == (int)(30/SYSTEM_TIME))
    {
      nSrcAddr = j1939.GetSourceAddress();
      j1939.Transmit(6, 60416, nSrcAddr, 0x33, msgFakeNAME,8);
      nCounter = 0;
      
    }// end if
  
  }// end if
  

  // Check for reception of PGNs for our ECU/CA
  //if(nMsgId == J1939_MSG_APP)
  //{
    // Check J1939 protocol status
    switch(nJ1939Status)
    {

      case ADDRESSCLAIM_INPROGRESS:
      
        break;
        
      case NORMALDATATRAFFIC:
        if(nMsgLen != 0 ){
          sprintf(sString, "PGN: 0x%X Src: 0x%X Dest: 0x%X ", (int)lPGN, nSrcAddr, nDestAddr);
          Serial.print(sString);
          Serial.print("Data: ");
          for(int nIndex = 0; nIndex < nMsgLen; nIndex++)
          {          
            sprintf(sString, "0x%X ", pMsg[nIndex]);
            Serial.print(sString);
            
          }// end for
          Serial.print("\n\r");
          nMsgId = J1939_MSG_NONE;
        }
       break;
        
      case ADDRESSCLAIM_FAILED:
      
        break;
      
    }// end switch(nJ1939Status)  
  //}// end if
 
}// end loop