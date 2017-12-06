## Inertial measurement Unit transformations

The present project follows the work of [1].

	[1]PEDLEY, M. Tilt sensing using a three-axis accelerometer.
	Freescale semi-conductor application note, v. 1, p. 2012–2013, 2013.

### Content
- [Usage](#usage)

### Usage


*Calculate roll and pitch using accelerometer data (function calculate_roll_and_pitch)
function calculate_roll_and_pitch(string file_in)
function calculate_roll_and_pitch(string file_in, string aditional_parameter)
function calculate_roll_and_pitch(string file_in, string aditional_parameter, string file_out)
aditional_parameter (Optional) - The sequence rotation, accepted values are xyz or yxz. The stantandard value to this atribute is xyz
file_in (Required) - Name of the file which the acceleration data will be read, it must be in the following pattern [timestamp; aceleration in x; aceleration in y; aceleration in z], the standard location of file_in is Data/ 
file_out (Optional)   Name of the file which the angles will be stored, it has the following pattern  [timestamp; roll; pitch]. The standard location of file_out is Data/ 
Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o programa 
```
Execution:
```markdown
$ ./program function=calculate_roll_and_pitch file_in=attitude_exam.log file_out=attitude_out.log
```
or
```markdown
$./programa
Enter the desired command:
function=calculate_roll_and_pitch file_in=attitude_exam.log file_out=attitude_out.log
```