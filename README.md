## Windows Sockets Experiment
* Program listens on 127.0.0.1:8080 then sends a "Success" string to client(browser etc.)

# Analyzing Structures ( C style Polymorphism )
* struct sockaddr {
*    unsigned short sa_family;    // 2 Byte AF_INET, AF_BLUETOOTH vb.)
*    char           sa_data[14];  // 14 Byte
* }; 

* When (SOCKADDR*)&serverAddr passed to functions (bind,accept...) ,
* Function checks first two bytes (which is common in both structures) ,
* and decides whether it is a ipv4 address or not , then simply reads that memory for struct sockaddr_in definition.

*  struct sockaddr_in { 
*    short          sin_family;   // 2 Byte (AF_INET)
*    unsigned short sin_port;     // 2 Byte (Port )
*    struct in_addr sin_addr;     // 4 Byte (IP )
*    char           sin_zero[8];  // 8 Byte 

* };

Pseudo Base Struct => struct sockaddr
Pseudo Derived Struct => struct sockaddr_in
*** Result = Pointing derived struct with base pointer *** 

AF_INET (2) → Treats memory as struct sockaddr_in

AF_INET6 (23) → Treats memory as struct sockaddr_in6

AF_BLUETOOTH (32) → Treats memory as Bluetooth-specific structure

<img width="444" height="154" alt="image" src="https://github.com/user-attachments/assets/b9f235cd-4974-4fd7-92af-edb1d13b8129" />
<img width="320" height="34" alt="image" src="https://github.com/user-attachments/assets/9fa6612f-eab8-4834-bde1-0b74b7def3ef" />
<img width="204" height="73" alt="image" src="https://github.com/user-attachments/assets/e4f44a5e-5c94-418d-bab6-02fff28e6563" />
