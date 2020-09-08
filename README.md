# LedControlFlex
An Arduino interpreter that expands on the functionality of [LedControl](https://github.com/wayoda/LedControl).

This is currently a functional interpreter that converts 2 dimensional integer arrays into byte arrays for passing to LedControl for MAX7219 and MAX7221 Led display drivers.
As my test display is 32x8 on 4 display drivers it is currently limited to this output

TODO
----
Make total number of displays flexible

Add another dimension to fullScreenImage so that animations can be stored
