Just lighting up some LEDs using a bit of super hacky arduino flavored C.  

One day I'll get around to learn some proper C. In the meantime, hey, I got this to work so I'm happy.

There's a bit of an abstraction here, in the form of a ghetto letter to LEDs resolver. I suggest you first number all your LEDs with a marker, then place them on your actual physical letters, then go edit those `A` `B` `C` etc variables and put the LED positions in there. Yes I know my map skips position `0`.

Things you'll need:

- LED strings (pro-tip: you can totally string together multiple WS2811 strings by simply stripping their cables and connecting them in serial)
- 5v/10A power for the lights
- 9V/1A power for the arduino
- An arduino board (we used a cheap Uno clone)
- Install [FastLED](http://fastled.io) from the Arduino IDE

Many thanks to this instructables article:  
http://www.instructables.com/id/Arduino-Based-Stranger-Things-Lights/  

Warning:  
There might be profanity in my code. If that triggers you, maybe read more books.

And remember:

> Mornings are for coffee and contemplation.

