#ifndef EEPROM_H_INCLUDED 
#define EEPROM_H_INCLUDED 


#define MAX_PAGE_SIZE    64    // Bytes
#define MAX_MEM_LOC     32768 // Bytes
#define NUM_READ_CNTRL    2   // Bytes
#define NUM_WRITE_CNTRL   2   // Bytes

#define START_ADDR    0x0000
#define END_ADDR    0x7FFF


void I2CEEPROMInit();
void I2CEEPROMTerm();
void I2CEEPROMRead(char * pbData, int bAddr, int cSize);
void I2CEEPROMWrite(char * pbData, int bAddr, int cSize);
bool I2CEEPROMIsEmpty();




#endif // EEPROM_H_INCLUDED
