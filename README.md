# PropTreeLib
A flexible and feature-rich input file reader designed for use in scientific computing applications.

## Description
This project was inspired by extensive work with a number of scientific computing codes.
A typical structure for one of these codes is to have an input file that contains every runtime parameter.
The solver then reads this file and sets parameters accordingly.

The very nature of scientific computing means that every run counts. If you aren't debugging, the code is likely to run for
days, possibly even weeks, at a time. This costs a lot of money and effort, so it makes sense to make sure that every parameter is correct!

Sometimes, however, deadlines can get to us. Small mistakes are made, such as a typo on one input option that causes it to be ignored and/or
set to a default value. In some cases, this can cause an entire simulation to be garbage.

## Purpose
PropTreeLib is designed to fix the following symptoms of primitive input file readers, each of which has been found in an existing, large-scale scientific computing code:

* You run 10 different cases with slightly varying input parameters, but forgot to print the values of the parameters to the slurm log. Now half of the data is meaningless
and needs to be run again! With a `PropTreeLib::PropertyTree input` object, simply call `input.DebugPrint()` and everything is there.

* All of your runtime parameters have default values but you can't remember what subsection or name a certain one of them has.
Using a `PropTreeLib::Interactive i` object, and a command-line argument `PTL:defaultVals`, simply call `i.Run()` to create a
full input file with every option set to its default value (GUI generation coming soon!).

* There is some quantity that you compute using different methods, but your methods are (poorly) labeled with integers.
You can't remember what `method=1`, `method=2`, etc. correspond to. Using a `PropTreeLib::Variables::PTLEnum` or `PropTreeLib::Variables::PTLAutoEnum`
object, options like this can have meaningful enumeration-style labels.

* Your input file options are not comprehensively documented. All PropTreeLib variables take a string description argument so that
every input option is documented. This is a huge help to rapidly bring newcomers onboard with your code!

* You have multiple separate submodules / objects / libraries that all have different input files. With `PropTreeLib::PropertyTree subInput, mainInput`
object, you can branch `mainInput` into a subtree using `subInput.SetAsSubtree(mainInput["mySubSection"])`, so every component is initialized from one file.

* You have multiple parameters in your input file that, for some reason, all have to have the same value. The `PropTreeLib::PreProcessContext` object is a part of every
`PropTreeLib::PropertyTree` (and is automatically active) and allows for contextualized `#define` directives, e.g. `#define myDefinedValue 0.1`, and then
`someOtherValue = $(myDefinedValue)`



## License
[MIT](https://choosealicense.com/licenses/mit/)