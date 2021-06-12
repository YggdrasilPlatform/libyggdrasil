.. _WorldConnector:

World Connector
===============

The World Connector is the most important connector on Yggdrasil. It's a ``SOMIDD314`` slot fitting one of the SoC Modules that come with the Yggdrasil platform.

.. note::
    | The entire pinout is designed to work with the `Toradex Apalis Series <https://www.toradex.com/computer-on-modules/apalis-arm-family>`_ of boards.
    | However, not all peripherals will be usable on the Apalis boards since the majority of peripherals are layed out to use with the World boards.

Connector
---------

===  ==========================  ===  =================
Pin  Description                 Pin  Description 
===  ==========================  ===  =================
1    Led A                       2    Timer B Channel A
3    Led B                       4    Timer B Channel B
5    Led C                       6    Timer B Channel C
7    Led D                       8    Timer B Channel D
9    GND                         10   VDD
11   Button A                    12   CAN A RX
13   Button B                    14   CAN A TX
15   Button C                    16   CAN B RX
17   Button D                    18   CAN B TX
|                                |                        
|                                |     
23   GND                         24   PONKEYn / TP 28
25                               26   Subnet reset
27                               28   NRST
29   GND                         30   VDD
31   Timer A Channel A           32   MDI2_P
33   Timer C Channel A           34   MDI2_N
35                               36   VDD
37   TP 31                       38   MDI3_P
39   GND                         40   MDI3_N
41                               42   LED Yellow
43                               44   LED Green
45   GND                         46   
47                               48   MDI0_N
49                               50   MDI0_P
51   GND                         52   VDD
53                               54   MDI1_N
55                               56   MDI1_P
57   GND                         58   VDD
59   GPIO A                      60   OTG VBUS
61   GPIO B                      62   
63   GPIO C                      64   
65   GPIO D                      66   VDD
67                               68   
69   GND                         70   
71                               72   OTG ID
73                               74   USB1_P
75   GND                         76   USB1_N
77                               78   VDD
79                               80   USB2_P
81   GND                         82   USB2_N
83                               84   
85   NJRST                       86   
87   JTDO / Trace SWO            88   
89   JTDI                        90   VDD
91   JTCK / SWCLK                92   
93   GND                         94   
95   JTMS / SWDIO                96   
97   STLink UART RX              98   
99   STLink UART TX              100  
101                              102  VDD
103                              104  
105  GND                         106  
107                              108  VDD
109                              110  
111  GND                         112  USART A TX
113                              114  USART A RTS
115                              116  USART A CTS
117  GND                         118  USART A RX
119                              120  
121                              122  
123                              124  
125                              126  
127                              128  
129  GND                         130  
131                              132  
133                              134  UART B TX
135                              136  UART B RX
137                              138  BOOT 0
139                              140  BOOT 1
141  GND                         142  GND
143                              144  BOOT 2
145                              146  
147  GND                         148  
149                              150  
151                              152  
153  GND                         154  
155                              156  
157  DCMI D11                    158  
159  DCMI D10                    160  
161  DCMI D9                     162  
163  DCMI D8                     164  
165  GND                         |     
|                                |     
|                                |     
|                                |     
173  DCMI D7                     174  Backup supply
175  DCMI D6                     176  
177  DCMI D5                     178  
179  DCMI D4                     180  
181  DCMI D3                     182  GND
183  DCMI D2                     184  
185  DCMI D1                     186  
187  DCMI D0                     188  
189  GND                         190  
191  DCMI PIXCK                  192  GND
193                              194  I2SA MCK
195  DCMI VSYNC                  196  I2SA SDO
197  DCMI HSYNC                  198  JACK
199  GND                         200  I2SA CK
201  I2C D SDA                   202  I2SA SDI
203  I2C D SCL                   204  I2SA WS
205  I2C B SDA                   206  GND
207  I2C B SCL                   208  Encoder Channel A
209  I2C A SDA                   210  Encoder Channel B
211  I2C A SCL                   212  Encoder Button
213  GND                         214  
215  MCO A (Master Clock Out)    216  
217  MCO B (Master Clock Out)    218  GND
219  GND                         220  
221  SPI C SCK                   222  
223  SPI C MISO                  224  
225  SPI C MOSI                  226  GND
227  SPI C NSS                   228  
229  SPI A MISO                  230  
231  SPI A MOSI                  232  
233  SPI A NSS                   234  
235  SPI A SCK                   236  
237  GND                         238  GND
239  SPI B MISO                  240  I2C C SCL
241  GND                         242  I2C C SDA
243  SPI B MOSI                  244  GND
245  SPI B SCK                   246  DSI CK_P
247  SPI B CE                    248  DSI CK_N
249                              250  GND
251  Segment A                   252  DSI D0_P
253  Segment B                   254  DSI D0_N
255  Segment C                   256  GND
257  Segment D                   258  DSI D1_P
259  Segment E                   260  DSI D1_N
261  Segment F                   262  
263  Segment G                   264  DSI TE
265  Segment DP                  266  DSI Reset
267  GND                         268  GND
269  Segment Select A            270  LCD Backlight Controll
271  Segment Select B            272  
273  Segment Select C            274  Touch Interrupt
275  Segment Select D            276  ICM-42605 Interrupt Line 1
277  QSPI BK2 IO0                278  ICM-42605 Interrupt Line 2
279  QSPI BK2 IO1                280  GND
281  QSPI BK2 IO2                282  LPS22HBTR Interrupt Line
283  QSPI BK2 IO3                284  RV-3028-C7 Interrupt Line
285  GND                         286  
287  QSPI BK1 IO0                288  TCS34725FN Interrupt Line
289  QSPI BK1 IO1                290  TC78H660FTG Mode selection
291  QSPI BK1 IO2                292  GND
293  QSPI BK1 IO3                294  TC78H660FTG Standby
295  QSPI BK1 NCS                296  TC78H660FTG Error
297                              298  GND
299  QSPI BK2 NCS                300  SK9822 Enable
301  QSPI CLK                    302  uSD Detect
303  GND                         304  GND
305  ADC Channel A               306  Button Joystick A
307  ADC Channel B               308  GND
309  ADC Channel C               310  Button Joystick B
311  ADC Channel D               312  Error LED
313  GND                         314  VDD
315  ADC Potentiometer           316  LightUp LED
317  GND                         318  
319  DAC Channel A               320  VDD
321  DAC Channel B               |     
===  ==========================  ===  =================