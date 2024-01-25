# Keyboard_I2C

Arduino library for matrix-based keyboards using PCF8574 expander
The maximum size of keyboard is 4x4 buttons, which is 16 buttons in total.

<h2> How it's working? </h2>
Matrix-based means the button contacts are connected into rows and columns so each button can be identified by one row and one column. 
The expander is using one of the dimensions (col/row) as output and the second as input, so by pushing the button, you are connecting an output to input. 
By switching the logical conditions at the input and checking the output if keyboard, you can easily find wh
