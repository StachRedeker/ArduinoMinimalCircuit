# ArduinoMinimalCircuit
> Build a minimal ATmega328P circuit... so you don't need a full Arduino anymore. And learn something about logic gates along the way.

This project aims at explaining how to build a minimal circuit around the ATmega328P processor. The ATmega328P is commonly found in microcontroller boards such as the Arduino Uno. A minimal circuit is everything that is nessecary to use the processor. So, basically, we will be building a simpler version of the Arduino Uno. We will also add various I/O components to show that the system works. 

Why is a minimal circuit implementation of an Arduino useful? Why not buy an Arduino and use it directly? That's a valid question! Sometimes, we are not interested in every Arduino function. For example, a project might not require all digital and analog pins, or a 3.3 [V] channel. In that case, it might be more elegant to only build what you need; so, building an 'Arduino' from scratch. It is also useful to build your own Arduino if you are limited to a specific physcial size, or if you want to use the least amount of power possible (e.g. when running on batteries).

If you work along with this project, I assume that you have some experience with Arduinos. I assume that you have worked with the Arduino IDE, that you know how to hook up an Arduino to your computer, program it, and that you are able to build basic circuits on breadboard. The final product will look something like this:

![ATmega328P minimal circuit with various I/O components and power supply](/breadboard2.jpeg)



## Features

Not only will we build a minimal circuit for the ATmega328P chip, we will also make a small application that is able to mimic various logic gates. A user should be able to select the gate of its choice using four DIP switches on the breadboard. Then, the user can interact with the system using buttons, and sees the output in real-time thanks to a red LED.


## Hardware design


## Software design



## Instructions




## Improvements



## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

This subchapter also feels appropriate to address the [Trademark & Copyright policy](https://www.arduino.cc/en/trademark) of the Arduino LLC. Altough the hardware design of the Arduino is completely open source, the name 'Arduino' is trademarked. It is therefore **not allowed** to distribute clones under the name 'Arduino' or variants of that name. This project, however, does not aim to sell an (re)branded Arduino product, nor does try to imitate Arduino. This project uses the name 'Arduino' to refer and describe existing Arduino products, namely the basic circuitry of an Arduino Uno, which is allowed as per the Trademark & Copyright policy. 

## Acknowledgments


