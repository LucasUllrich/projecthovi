#include <PIC16F1827.h>
#include "hovi_LED_v2.h"


/*---------------------------------------------------------------------------*/
/* Retrieves Object from Pixy                                                */
/* Maximum tries for getting startcondition c = 10, retuns 0 if overrun      */
/* Returns a found Object in struct colorobject                             */
/* Searches for desired object des_obj by controlling with ProofObject()     */
/* Searches for specific objecttype by des_obj_type, desired object type     */
/*      des_obj_type = 0 => searches for normal objects                      */
/*      des_obj_type = 1 => searches for colorcodeobjects                   */
/*---------------------------------------------------------------------------*/
unsigned char GetObject(bit des_obj_type, unsigned int des_obj){
    
    unsigned int start, objcc;
    bit obj_type;       /* declares type of detected object
                         * 0 for normal objects
                         * 1 for colorcode objects*/
    
    typedef struct colorobject{
        unsigned int num; /* num contains as much diggits as colors in the code 
                           * -> color 3, color 7, num = 37*/
        unsigned int pos_x; // X center of object
        unsigned int pos_y; // Y center of object
        unsigned int width; 
        unsigned int height;
        unsigned int angle; // Rotation
        
    };
    
    typedef struct colorobject farben1;
    typedef struct colorobject farben2;
    
    bit frame = 0;
    unsigned char c = 0;    // Counter for following do, while loop
    
    /* Routine for getting startcondition                                    */
    /* Returns 0 after 10 cycles without detecting an object                 */
    /*-----------------------------------------------------------------------*/
    do {
        if(ExchangeSpi2char(PIXY_SYNC, DUMMY) == PIXY_FRAME_OBJ) {
            frame = 1;
            if(ExchangeSpi2char(PIXY_SYNC, DUMMY) == PIXY_FRAME_OBJ) {
                obj_type = 0;
            }else if(ExchangeSpi2char(PIXY_SYNC, DUMMY) == PIXY_COLOURCODE) {
                obj_type = 1;
            }
        }else {
            frame = 0;
        }
        c++;
        if(c > 10) {
            return 0;
        }
    } while(!frame && c <= 10);
    
    unsigned int checksum = ExchangeSpi2char(PIXY_SYNC, DUMMY);
    
    farben1.num =    ExchangeSpi2char(PIXY_SYNC, DUMMY);
    farben1.pos_x =  ExchangeSpi2char(PIXY_SYNC, DUMMY);
    farben1.pos_y =  ExchangeSpi2char(PIXY_SYNC, DUMMY);
    farben1.width =  ExchangeSpi2char(PIXY_SYNC, DUMMY);
    farben1.height = ExchangeSpi2char(PIXY_SYNC, DUMMY);
    farben1.angle =  ExchangeSpi2char(PIXY_SYNC, DUMMY);
        
    ProofObject(des_obj);
    
}

void ProofObject(unsigned int des_obj){
    
    unsigned int pos_x, pos_y, obj_num;
    
    if(){
        
    }
    
    xxx(pos_x, pos_y);
    
}



void LedSignalling(unsigned int pos_x, unsigned int pos_y){
    
    /* Checking condtions for LED in x-direction                             */
    /* Sets LED in which direction the camera should be moved                */
    /* Both LEDs light up if data is nonsense                                */
    /*-----------------------------------------------------------------------*/
     if(pos_x > 170){
         LEDleft = 0;
         LEDright = 1;
     }else if(pos_x < 150){
         LEDleft = 1;
         LEDright = 0;   
     }else if(pos_x >= 150 && pos_x <= 170){
         LEDleft = 0;
         LEDright = 0;  
     }else{
         LEDleft = 1;
         LEDright = 1; 
     }
     
    /* Checking condtions for LED in y-direction                             */
    /* Sets LED in which direction the camera should be moved                */
    /* Both LEDs light up if data is nonsense                                */
    /*-----------------------------------------------------------------------*/
     if(pos_y < 90){
         LEDup = 1;
         LEDdown = 0;
     }else if(pos_y > 110){
         LEDup = 0;
         LEDdown = 1;
     }else if(pos_y >= 90 && pos_y <= 110){
         LEDup = 0;
         LEDdown = 0;
     }else{
         LEDup = 1;
         LEDdown = 1;
     }
     
}


