#ifndef MainMCU_h
#define MainMCU_h

#define _PIN_Serial_RX1 0
#define _PIN_Serial_TX1 1
#define _PIN_R_CLEAR_SIGNAL 7
#define _PIN_T_CLEAR_SIGNAL 8

#define LCD_I2C_ADDR 0x27

class ModuleMain{
public:
    void receive_location_data();
    void receive_clear_signal();
    void data_parsing();

private:
    bool clear_signal;
    bool LCD;
    unsigned long taken_time;
    int _parsing_step;
    bool _parsing_done;
};
#endif