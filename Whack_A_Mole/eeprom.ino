//                            
//
//#include "LaunchPad.h"
////#include "I2CEEPROM.h"
//#include "delay.h"
//
//
//#define bI2CEEPROMAddress 0x50
//
///* I2C Transmit Commands
//*/
//#define bcmdWrite     0xA0
//#define bcmdRead      0xA1
//
///* Bit Masks
//
//#define mskHB       0x00007F00    // bit 15 is a don't care for memory addressing
//#define mskLB       0x000000FF
//
//
////#define READ        true
////#define WRITE       false
//
//
//char rgbfNotEmpty[3];
//bool fReadNec;
//
//
//char I2CTransmit(char * pbData, int cSize, bool fRW);
//bool I2CIsNotIdle();
//
//
//*/
//void I2CEEPROMInit() {
//  
//
////  int i2cFreq = 400000;
//
////  I2CConfigure(I2C2, I2C_ENABLE_HIGH_SPEED);
////  I2CSetFrequency(I2C2, 80000000, i2cFreq);
////  I2CSetSlaveAddress(I2C2, bI2CEEPROMAddress, 0, I2C_USE_7BIT_ADDRESS);
//
//  
////  I2CReceiverEnable(I2C2, FALSE);
//
////  I2CEnable(I2C2, TRUE);
//    
//
//  rgbfNotEmpty[0] = START_ADDR;
//  rgbfNotEmpty[1] = START_ADDR;
//  rgbfNotEmpty[2] = 0x12;
//
//
////  EEPROMTerm();
//}
//
//
//
//void I2CEEPROMTerm() {
//
//  char  rgbClearEEPROM[4] = {0};
//  
//  rgbClearEEPROM[0] = bcmdWrite;
//  rgbClearEEPROM[1] = 0x00;
//  rgbClearEEPROM[2] = 0x00;
//  rgbClearEEPROM[3] = 0;
//
//  /* Erase the EEPROM Full indicator
//  */
//  fReadNec = true;
//  I2CTransmit(rgbClearEEPROM, 1, WRITE);
//
//}
//
//
//bool I2CEEPROMIsEmpty() {
//
//  char bTemp;
//
//
//  if(fReadNec) {
//    I2CEEPROMRead(&bTemp, START_ADDR, 1);
//
//    if(bTemp == rgbfNotEmpty[2]) {
//  
//      fReadNec = false;
//      
//    }
//    else {
//      
//      fReadNec = true;
//      
//    }
//  }
//
//  return fReadNec;
//}
//
//
//void I2CEEPROMRead(char * pbData, int bAddr, int cSize) {
//
//  int   ib;         // byte index
//  int   ipg;        // page index
//  int   cPages;
//  char *  pbTransBuf;
//  char *  pbTemp;
//  char  bMemAddrHB;
//  char  bMemAddrLB;
//  char  rgbI2CTransmitBuf[MAX_PAGE_SIZE + NUM_READ_CNTRL] = {0};  // 1st byte is write control byte
//                                    // 2nd/3rd byte are address bytes
//                                    // 4th byte is control byte 
//                                    // subsequent bytes are read data bytes (# data bytes = cSize)
//
//  /* Make sure cSize is a valid number
//  ** cSize = 1 is the smallest value
//  ** cSize = MAX_MEM_LOC is the largest value
//  */
//  if(cSize >= MAX_MEM_LOC) {
//    cSize = MAX_MEM_LOC;
//  }
//  else if( cSize < 1) {
//    cSize = 1;
//  }
//
//  DelayMs(5);
//
//  /* Set the page counter to the number of 
//  ** data bytes divided by the max number of pages
//  ** Since this is integer division, add 1
//  */
//  cPages = cSize/MAX_PAGE_SIZE + 1;
//
//  /* Since the EEPROM can only be written to in
//  ** MAX_PAGE_SIZE byte pages, we will configure
//  ** the buffer for each page. The Address will change
//  ** by the current page index times MAX_PAGE_SIZE
//  */
//  for(ipg = 0; ipg < cPages; ipg++) {
//
//    /* Write the Write control byte to the
//    ** transmit buffer
//    */
////    rgbI2CTransmitBuf[0] = bcmdWrite;
//  
//    /* Write the Mem Address bytes. Address is 15 bits
//    ** so mask off High Byte and Low Byte
//    */
//    bAddr += ipg*MAX_PAGE_SIZE;
//    bMemAddrHB = (bAddr & mskHB) >> 8;
//    bMemAddrLB = (bAddr & mskLB);
//  
//    rgbI2CTransmitBuf[0] = bMemAddrHB;
//    rgbI2CTransmitBuf[1] = bMemAddrLB;
//  
//    /* Write the Read control byte to the
//    ** transmit buffer
//    */
////    rgbI2CTransmitBuf[3] = bcmdRead;
//  
//    /* Transmit the Buffer and receive specified bytes
//    */
//    pbTransBuf = rgbI2CTransmitBuf; 
//  
//    I2CTransmit(pbTransBuf, cSize, READ);
//  
//    /* Write data to user's data array
//    */
//    pbTemp = &rgbI2CTransmitBuf[NUM_READ_CNTRL + 1];
//  
//    for(ib = 0; ib < cSize; ib++) {
//      
//      *pbData = *pbTemp;
//  
//      pbTemp++;
//      pbData++;
//      
//    }
//  }
//
//}
//
///* ------------------------------------------------------------ */
///***  ProcName
//**
//**  Parameters:
//**    none
//**
//**  Return Value:
//**    none
//**
//**  Errors:
//**    none
//**
//**  Description:
//**    Writes to the specified location in EEPROM. The allocated
//**  and initialized data that pbData points to should only include
//**  the desired chars to write to memory.
//*/
//void I2CEEPROMWrite(char * pbData, int bAddr, int cSize) {
//
//  int   ib;         // byte index
//  int   ipg;        // page index
//  int   cPages;
//  char *  pbTransBuf;
//  char *  pbTemp;
//  char  bMemAddrHB;
//  char  bMemAddrLB;
//  char  rgbI2CTransmitBuf[MAX_PAGE_SIZE + NUM_WRITE_CNTRL] = {0};   // 1st byte is control byte
//                                      // 2nd/3rd byte are address bytes
//                                      // subsequent bytes are data bytes (# data bytes = cSize)
//
//
//  if(I2CEEPROMIsEmpty()) {
//    /* Write to first address to indicate that
//    ** EEPROM is not Empty
//    */
//    I2CTransmit(rgbfNotEmpty, 1, WRITE);
//  }
//
//  DelayMs(5);
//
//  /* Increment Address
//  ** This is a horrible way to do this. Always
//  ** assume that the Not Empty byte doesn't exist
//  ** when choosing addresses to write to
//  */  
//  bAddr += 1;
//
//  /* Make sure cSize is a valid number
//  ** cSize = 1 is the smallest value
//  ** cSize = MAX_MEM_LOC is the largest value
//  */
//  if(cSize >= MAX_MEM_LOC) {
//    cSize = MAX_MEM_LOC;
//  }
//  else if( cSize < 1) {
//    cSize = 1;
//  }
//
//  /* Set the page counter to the number of 
//  ** data bytes divided by the max number of pages
//  ** Since this is integer division, add 1
//  */
//  cPages = cSize/MAX_PAGE_SIZE + 1;
//
//  /* Since the EEPROM can only be written to in
//  ** MAX_PAGE_SIZE byte pages, we must configure
//  ** the buffer for each page. The Address will change
//  ** by the current page index times MAX_PAGE_SIZE
//  */
//  for(ipg = 0; ipg < cPages; ipg++) {
//
//    /* Write the Write control byte to the
//    ** transmit buffer
//    */
////    rgbI2CTransmitBuf[0] = bcmdWrite;
//    
//    /* Write the Mem Address bytes. Address is 15 bits
//    ** so mask off High Byte and Low Byte
//    */
//    bAddr += ipg*MAX_PAGE_SIZE;
//    bMemAddrHB = (bAddr & mskHB) >> 8;
//    bMemAddrLB = (bAddr & mskLB);
//  
//    rgbI2CTransmitBuf[0] = bMemAddrHB;
//    rgbI2CTransmitBuf[1] = bMemAddrLB;
//  
//    /* Write data to transmit buffer
//    */
//    pbTemp = &rgbI2CTransmitBuf[NUM_WRITE_CNTRL];
//  
//    for(ib = 0; (ib < cSize) || ib < (MAX_PAGE_SIZE); ib++) {
//      
//      *pbTemp = *pbData;
//  
//      pbTemp++;
//      pbData++;
//      
//    }
//  
//    /* Declare a temporary pointer at the
//    ** beginning of the transmit buffer
//    */
//    pbTransBuf = rgbI2CTransmitBuf;
//  
//    /* Transmit. Add on the number of control bytes
//    ** to the total number of data bytes
//    */
//    I2CTransmit(pbTransBuf, cSize, WRITE);
//  } 
//}
//
//
///********************************************************************************/
////////////////////////////////////////////////
////        Internal I2C Functions    //
////////////////////////////////////////////////
///********************************************************************************/
//
///* ------------------------------------------------------------ */
///***  I2CTransmit
//**
//**  Parameters:
//**    pbData  - Pointer to transmit buffer (read or write)
//**    cSize - Number of byte transactions to take place
//**
//**  Return Value:
//**    none
//**
//**  Errors:
//**    none
//**
//**  Description:
//**    Transmits data to a device via the I2C bus
//**      
//*/
//char I2CTransmit(char * pbData, int cSize, bool fRW) {
//
//  int     i;
//  char *    pbTemp;
//
//  pbTemp = pbData;
//
///*Start*/
//  
///*Send Address High Byte*/
//  /* Send Write Block Cmd
//  */
//  I2CMasterSlaveAddrSet(I2C0_BASE, EEPROMADDR, WRITE);
//  I2CMasterDataPut(I2C0_BASE, *pbTemp);
//
//  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
//
//  while(I2CMasterBusy(I2C0_BASE));
//
//  while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
//  }
//
//  /* Idle wait
//  */
//  while(I2CIsNotIdle());
//
//  /* Increment data pointer
//  */
//  pbTemp++;
//
///*Send Address Low Byte*/
//  /* Send Write Block Cmd
//  */
//  I2CMasterDataPut(I2C0_BASE, *pbTemp);
//  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
//
//  while(I2CMasterBusy(I2C0_BASE));
//
//  while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
//  }
//
//  /* Idle wait
//  */
//  while(I2CIsNotIdle());
//
//  /* Increment data pointer
//  */
//  pbTemp++;
//
///*Execute Read or Write*/
//
//  if(fRW == READ) {
//    
//    /* Resend Start condition
//    ** Then send new control byte
//    ** then begin reading
//    */
//    I2CMasterSlaveAddrSet(I2C0_BASE, EEPROMADDR, READ);
//
//    while(I2CMasterBusy(I2C0_BASE));
//
//    /* Begin Reading
//    */
//    for(i = 0; i < cSize; i++) {
//      
//      if(i == cSize - 1) {
//        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
//
//        while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
//        }
//
//        while(I2CMasterBusy(I2C0_BASE));
//      }
//      else if(i == 0) {
//        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
//
//        while(I2CMasterBusy(I2C0_BASE));
//
//        while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
//        }
//
//        /* Idle wait
//        */
//        while(I2CIsNotIdle());
//      }
//      else {
//        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
//
//        while(I2CMasterBusy(I2C0_BASE));
//
//        while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
//        }
//
//        /* Idle wait
//        */
//        while(I2CIsNotIdle());
//      }
//
//      while(I2CMasterBusy(I2C0_BASE));
//
//      /* Read Data
//      */
//      *pbTemp = (char)I2CMasterDataGet(I2C0_BASE);
//
//      while(I2CMasterBusy(I2C0_BASE));
//  
//      pbTemp++;
//
//    }
//
//  }
//  else if(fRW == WRITE) {
//    
//    /*Loop data bytes
//    */
//    for(i = 0; i < cSize; i++) {
//      /* Send Data
//      */
//      I2CMasterDataPut(I2C0_BASE, *pbTemp);
//
//      while(I2CMasterBusy(I2C0_BASE));
//
//      if(i == cSize - 1) {
//        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
//
//        while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
//        }
//
//        while(I2CMasterBusy(I2C0_BASE));
//      }
//      else {
//        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
//
//        while(I2CMasterBusy(I2C0_BASE));
//
//        while(I2CMasterErr(I2C0_BASE) != I2C_MASTER_ERR_NONE) {
//          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
//        }
//
//        /* Idle wait
//        */
//        while(I2CIsNotIdle());
//      }
//  
//      pbTemp++;
//    }
//    
//  }
//
///*Stop*/
//
//  return 0x00;
//
//}
//
///* ------------------------------------------------------------ */
///***  I2CIsNotIdle()
//**
//**  Parameters:
//**    pbData  - Pointer to transmit buffer (read or write)
//**    cSize - Number of byte transactions to take place
//**
//**  Return Value:
//**    TRUE is bus is not idle, FALSE if bus is idle
//**
//**  Errors:
//**    none
//**
//**  Description:
//**    Returns TRUE if the bus is not idle
//**      
//*/
//bool I2CIsNotIdle() {
//
//  return !I2CMasterBusBusy(I2C0_BASE);
//
//}

