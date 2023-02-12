# elantia
Fast, lightweight neural net for ML/AI.

This software is a work in progress, however it does allow creating and training a neural net and making predictions.

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
