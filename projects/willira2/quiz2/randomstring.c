
I started the development of the tester by looking at the values in the main() which would cause the error to trigger and 
working my way backwards from the failure point. The program fails when string s = "reset" and local variable state = 9.
At this point, I know that string s is created by inputString() and must be five characters long (with a null terminating character) 
and comprised of all lower case characters. Working backwards from that, I next look at what conditions must be met in order for 
state to be equal to 9. I find that the value c is created from inputChar() and needs to be set to 9 unique values in a 
certain order for this to happen. The values that c must have are found in the range 32-125 in the ASCII table.

At this point, I have enough information to create the random tester. 

inputChar() - return a char value from the range 32-125 in the ASCII table.

inputString() - return a string of length 5 comprised of chars found in the range 97-122 from the ASCII table.

The implementation of these two functions were able to find the failure point in 11,466,633 iterations on the first run.
It is possible to create a much more tightly bound random test by restricting the possible values of c and s to solely 
those characters that are specified in the main function. This would greatly reduce the number of iterations needed to find
the failure point. The functions as they exist will find the failure point, though, and I think an argument could be made that 
by keeping a broad range, the test is more flexible as it can be reused without modification when the necessary precondition 
values of c and s are changed (within a certain boundary).
