#
# Author : Abhash Jain (ajain28) - CSC591 - HW2

## Chord Protocol Implementation
***
**Note: To run the abobe code files run the bootstrap file on every console.**

Reference Paper: 
* [Chord: A scalable peer-to-peer lookup service for internet applications](http://pdos.csail.mit.edu/papers/chord:sigcomm01/chord_sigcomm.pdf)
* [Wiki](https://en.wikipedia.org/wiki/Chord_(peer-to-peer))

Steps to Execute the Program:

1.  Clone the Git repo into your local System.

    `$ git clone https://github.ncsu.edu/ajain28/ajain28-HW2-CSC591.git`
2. Go to  the root of directory.
    
    `$ cd ajain28-HW2-CSC591`
3. Run the Bootstrap file on the console.

    `$ . bootstrap`
4. To build this C++ project use make Command.

    `$ make`
5. All the required Executables are generated and Now we can execute the code. As mentioned in the homework we can run this in batch mode or interactive mode.
    
    __Format: chord [-i <input_file_name>] <number_of_node>__

    __e.g.__
    
    `$ chord -i input.txt 3` 

    `$ chord 3`

6. It will display output on stdout.

__NOTE: All the exection needs to be run from the Project directory which in this case is ajain28-HW2-CSC591.__

__Note: All '$' written here means your prompt.__

You also have Interactive mode. which can be used by running the code as follows:
    `$ chord <number_of_nodes>`

7. After adding/dropping the node to chord ring you have to call stabalize and fix_finger to make it stablize explicitly. There is no periodic call to these method in this Chord Simulation.
