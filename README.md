# elantia

# About
Fast, lightweight neural net for ML/AI.
Named for the word for "doe" in Gaulish. A doe is fast and lightweight, like this application.

This software is a work in progress, however it does allow creating and training a neural net and making predictions.

# Example Usage
Example usage (after checking out the code and running `make`):

`bin/elantia create my_neural_net.ai --inputs 3 --outputs 2 --layers 2 --neurons 50 --function SELU`

This will create a neural net with 3 input nodes, 2 output nodes, and 2 middle layers of 50 neurons each using the SELU function.
The neural net will be saved to a file named `my_neural_net.ai` for later reuse.

To train the net, use a command like the following:

`bin/elantia train my_neural_net training_set.txt --iter 10000`

The `--iter` parameter specifies how many training iterations.
The training data file should be in a format similar to:

```
0: 1.0 0.7 0.0
1: 0.0 0.7 1.0
0: 0.3 0.2 0.2
0: 0.6 0.4 0.3
0: 0.8 0.7 0.5
1: 0.1 0.2 0.5
1: 0.2 0.5 0.6
0: 0.9 0.1 0.3
1: 0.7 0.9 0.8
1: 0.6 0.8 1.0
```

The above data will train the neural net to identify rising number sequences as output 1 and falling sequences as output 0.

To make a prediction, you can then run:

`bin/elantia predict my_neural_net 0.2 0.5 0.9`

This should give an output of 1 with a confidence percentage.

Note: for both predictions and for training, input values should *never* exceed the range of -1.0 to 1.0.

# Color Recognition
You can see the elantia ML engine in action using the color identification test, located at `tests/color_recognition`.
When run, this test will create a neural net, train it to seven saturated colors (red, orange, yellow, green, blue, violet, magenta),
and then have it categorize several randomly generated colors. The neural net will be saved as `color_test.ai` for reuse.
This file contains all that's necessary to identify your own categories among the seven options, for example:

`bin/elantia predict color_test.ai 0.2 0.5 0.3`

...which will most likely output 3, meaning green (the output values are a zero-based index).
You can also train it on the provided color training data, or your own data, substituting the .txt filename below if necessary:

`bin/elantia train color_test.ai tests/color_training_data.txt --iter 1000000`





