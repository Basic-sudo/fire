#ifndef _SERIALPORT_HPP_
#define _SERIALPORT_HPP_
#include <Head.hpp>

using namespace std;

typedef enum {
    e_port_init = 0,
    e_port_rx_find = 1,
    e_port_rx_rough_detect,
    e_port_rx_fined_detect,
    e_port_rx_stop_detect,
} E_SERIAL_PORT_STATE;

class SerialPort {
public:
    SerialPort(const std::string &path);
    ~SerialPort();
    enum BaudRate {	//波特率 枚举 
        BR0 = 0000000,
        BR50 = 0000001,
        BR75 = 0000002,
        BR110 = 0000003,
        BR134 = 0000004,
        BR150 = 0000005,
        BR200 = 0000006,
        BR300 = 0000007,
        BR600 = 0000010,
        BR1200 = 0000011,
        BR1800 = 0000012,
        BR2400 = 0000013,
        BR4800 = 0000014,
        BR9600 = 0000015,
        BR19200 = 0000016,
        BR38400 = 0000017,
        BR57600 = 0010001,
        BR115200 = 0010002,
        BR230400 = 0010003,
        BR460800 = 0010004,
        BR500000 = 0010005,
        BR576000 = 0010006,
        BR921600 = 0010007,
        BR1000000 = 0010010,
        BR1152000 = 0010011,
        BR1500000 = 0010012,
        BR2000000 = 0010013,
        BR2500000 = 0010014,
        BR3000000 = 0010015,
        BR3500000 = 0010016,
        BR4000000 = 0010017
    };

    enum DataBits { //数据位 {
        DataBits5,
        DataBits6,
        DataBits7,
        DataBits8,
    };

    enum StopBits {	//停止位
        StopBits1,
        StopBits2
    };

    enum Parity { 	//校验位
        ParityNone,
        ParityEven,
        PariteMark,
        ParityOdd,
        ParitySpace
    };

    struct OpenOptions { //串口参数结构体
        bool autoOpen;
        BaudRate baudRate;
        DataBits dataBits;
        StopBits stopBits;
        Parity parity;
        bool xon;
        bool xoff;
        bool xany;
        int vmin;
        int vtime;
    };
  
    static BaudRate BaudRateMake(unsigned long baudrate);
    static const OpenOptions defaultOptions;
	
	//串口打开
    bool open();
    bool open(const std::string &path, const OpenOptions &options);

    bool isOpen() const;
	
	//写数据
    int write(const void *data, int length);
    //读数据
    int read(void *data, int length);
	//串口及监听线程关闭
    void close();
	//串口监听线程
    void openThread();
private:
    std::string _path;          //port address
    OpenOptions _open_options;  //port data
    int _tty_fd;                //opened port
    bool _is_open = false;      //open state
protected:
    void termiosOptions(termios &tios, const OpenOptions &options);
};
// 初始化
int SerialPortInit(IN SerialPort& port, IN string path);
// 重载操作符
bool operator==(const SerialPort::OpenOptions& lhs, const SerialPort::OpenOptions& rhs);
bool operator!=(const SerialPort::OpenOptions& lhs, const SerialPort::OpenOptions& rhs);

#endif