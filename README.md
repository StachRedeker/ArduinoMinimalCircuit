# ArduinoMinimalCircuit
> Build a minimal ATmega328P circuit... so you don't need a full Arduino anymore. And learn something about logic gates along the way.

---

**Warning: this repository is not complete (yet). Allow me some time to completely fill it.**

---

This project aims at explaining how to build a minimal circuit around the ATmega328P processor. The ATmega328P is commonly found in microcontroller boards such as the Arduino Uno. A minimal circuit is everything that is nessecary to use the processor. So, basically, we will be building a simpler version of the Arduino Uno. We will also add various I/O components to show that the system works. 

Why is a minimal circuit implementation of an Arduino useful? Why not buy an Arduino and use it directly? That's a valid question! Sometimes, we are not interested in every Arduino function. For example, a project might not require all digital and analog pins, or a 3.3 [V] channel. In that case, it might be more elegant to only build what you need; so, building an 'Arduino' from scratch. It is also useful to build your own Arduino if you are limited to a specific physcial size, or if you want to use the least amount of power possible (e.g. when running on batteries).

If you work along with this project, I assume that you have some experience with Arduinos. I assume that you have worked with the Arduino IDE, that you know how to hook up an Arduino to your computer, program it, and that you are able to build basic circuits on breadboard. The final product will look something like this:

![ATmega328P minimal circuit with various I/O components and power supply](/breadboard2.jpeg)
*Figure 1: the final result.*

## Table of contents
  * [Features](#features)
  * [Hardware design](#hardware-design)
  * [Software design](#software-design)
  * [Instructions](#instructions)
  * [Improvements](#improvements)
  * [License](#license)
  * [Acknowledgments](#acknowledgments)
  * [Footnotes](#footnotes)

## Features

Not only will we build a minimal circuit for the ATmega328P chip, we will also make a small application that is able to mimic various logic gates. A user should be able to select the gate of its choice using four DIP switches on the breadboard. Then, the user can interact with the system using buttons, and sees the output in real-time thanks to a red LED.

I decided upon the following gates (please note: the SR latch is not a gate):
1) wire (buffer)
2) NOT
3) OR
4) AND
5) NOR
6) NAND
7) XOR
8) XNOR
9) SR latch


## Hardware design

These components are needed for the build:

* 1x Arduino Uno (yes, you heard that right, we need one for programming!)
* 1x ATmega328P chip, breadboard-friendly package recommended
* breadboard
* 16 [MHz] crystal
* 2x 22 [pF] capacitor
* 1x electrolytic capacitor for stabilizing the power lines, any value is fine
* 3x momentary push button
* 4x DIP switch
* 1x Red LED
* 1x 220 [Ohm] resistor
* 7x 10k [Ohm] resitor
* 1x L7805CV voltage regulator
* various jumper wires
* USB cable to connect the Arduino Uno to your PC

Firstly, build the ATmega328P minimal circuit. You can use Figure 2 as a reference. For this step, you need a 10k [Ohm] resistor, the crystal (will function as a clock), and the three capacitors. Here, a value of 10 [uF] is used for the electrolytic capacitor. Feel free to pick an aribitrary value. The electrolytic capacitor is used to stabilize the voltage on the 5 [V] rails[^stabilize]. This is good practise, but you can omit this capacitor if you do not have one available. The two ceramic capacitors of 22 [pF] cannot be omitted![^ceramic]

[^stabilize]: If you look at Figure 1, you see that my placement of the stabilizing capacitor is not quite correct. It only stabilizes the upper power lanes, and not the lower power lines, because it is placed after the upper lanes branch of from the lower lines. It is best if the capacitor is placed before the branch. Alternatively, one can also place a capacitor across every set of power lines. Nevertheless, the stabilizing capacitor does not really matter if your 5 [V] input is sufficiently stable, which is the case in my circuit.

[^ceramic]: This is not entirely true. The ATmega328P has an inbuild 8 [MHz] oscillator that can be used without 22 [pF] capacitors, or if an external clock signal of 16 [MHz] is not present. However, this internal clock signal is not [accurate](https://electronics.stackexchange.com/questions/27763/using-the-atmega328-with-the-internal-oscillator), so I'll not use it here.

![ATmega328P minimal circuit](/minimalcircuit.webp)
*Figure 2: the minimal circuit for the ATmega328P chip. Image courtesy of [Electrozubous on Instructables](https://www.instructables.com/Bare-Minimum-Arduino-on-Breadboard/) and distributed under the BY-NC-SA Creative Commons licence.*

Then, hook up the ATmega328P to the Arduino Uno that we will use for programming. You can use Figure 3 as a reference. In the 'Instructions' part of this `README`, I shall explain how to actually program the chip. For now, just make sure the connections are there.

![ATmega328P when programming](/minimalcircuitforburning.webp)
*Figure 3: we already prepare some connections for programming. Image courtesy of [Electrozubous on Instructables](https://www.instructables.com/Bare-Minimum-Arduino-on-Breadboard/) and distributed under the BY-NC-SA Creative Commons licence.*

Now is a good time to connect our L7805CV voltage regulator. The L7805CV takes input voltages from ~6 [V] to 35 [V] and converts these to 5 [V]. I use the L7805CV to power the circuit from a 9 [V] battery. If you have a stable (!) 5 [V] power supply that you can use, you might not need a voltage regulator.
The middle pin of the voltage regulator is often the common ground. Connect this to the ground of your circuit, and the ground of your power supply. Consult the datasheet from your voltage regulator to identify the Vin and Vout pins.

Lastly, connect the LED, buttons, and switches. You can use any arbitrary (digital) pins for this, but I opted for the following configuration:

* LED in series with a 220 [Ohm] current-limiting resistor to D8.
* Two buttons to D6 and D7. I used 10k [Ohm] pull-down resitors.
* Four switches to D10, D11, D12, D13. I again used 10k [Ohm] pull-down resistors.
* The last button is used to connect the reset pin of the ATmega328P when pressed. This will be our reset button.

You can use Figure 1 as a reference on how the connections are made.

## Software design

I tried to keep the software for this project lean and readable. The main system is a big `switch` statement that takes the input of the switches and mimics the requested logic gate accordingly. 

I use a clever trick to convert the (binary) input of the switches to an integer. I multiply the most siginifant bit (MSB) with 2^3 (=8), MSB-1 with 2^2 (=4), MSB-2 with 2^1 (=2), and the least significant bit (LSB) with 2^0 (=1). This is binary! So, we converted the 4 1s and 0s to a 4-bit integer. Pretty cool.

``` c++
int getSwitchStatus () {
  return (8*digitalRead(sw1) + 4*digitalRead(sw2) + 2*digitalRead(sw3) + digitalRead(sw4));
}
```

The `switch` statement, based on the obtained integer, calls functions that look like this:

``` c++
bool OR () {
  return (digitalRead(b1) || digitalRead(b2));
}
```

And I allow myself some shortcuts with the inverse version of the gates: [^NAND]

``` c++
bool NAND () {
  return !AND();
}
```


[^NAND]: Observe that this is not how a NAND gate is realized in hardware! In practise, an AND (so not a NAND) gate is made by placing an inverter after a NAND gate. Hence why AND gates are inherently slower than NAND gates. The NAND gate is the universal gate here. So, if I wanted to be 100% accurate, I should have made the `NAND()` function: `return !(digitalRead(b1) && digitalRead(b2));` and the `AND()` function: `return !NAND();`. But this, of course, wouldn't make things more clear. By the way, the same is true for NOR and OR. An OR gate is realized by inverting a NOR gate. (NEEDS SOURCE)






## Instructions




## Improvements



## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

This subchapter also feels appropriate to address the [Trademark & Copyright policy](https://www.arduino.cc/en/trademark) of the Arduino LLC. Altough the hardware design of the Arduino is completely open source, the name 'Arduino' is trademarked. It is therefore **not allowed** to distribute clones under the name 'Arduino' or variants of that name. This project, however, does not aim to sell an (re)branded Arduino product, nor does try to imitate Arduino. This project uses the name 'Arduino' to refer and describe existing Arduino products, namely the basic circuitry of an Arduino Uno, which is allowed as per the Trademark & Copyright policy. 

## Acknowledgments


## Footnotes
<!---
gets rendered automatically
-->

Some footnotes (mostly nerdy additions):
