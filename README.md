## Inertial measurement Unit transformations

The present project follows the work of [1].

	[1] PEDLEY, M. Tilt sensing using a three-axis accelerometer.
	Freescale semi-conductor application note, v. 1, p. 2012–2013, 2013.

### Content
- [Calculate roll and pitch using accelerometer data](#calculate-roll--and-pitch-using-accelerometer-data)

- [Calculate tilt angle](#calculate-tilt-angle)

- [Calculate screen rotation](#calculate-screen-rotation)

- [Calculate angle between two acceleration vectors data](#calculate-angle-between-two-acceleration-vectors-data)

- [Calculate normal vector of two acceleration vectors data](#calculate-normal-vector-of-two-acceleration-vectors-data)

- [Exit](#exit)

### Calculate roll and pitch using accelerometer data

Function that calculates roll and pitch using acceleration data. The data is stored with the following pattern [ms]; roll [degree]; pitch [degree] .

void calculate_roll_and_pitch(string file_in);

void calculate_roll_and_pitch(string file_in, string aditional_parameter);

void calculate_roll_and_pitch(string file_in, string aditional_parameter, string file_out);

* aditional_parameter (Optional) - The sequence rotation, accepted values are xyz or yxz. The standard value to this atribute is xyz.

* file_in (Required) - Name of the file which the acceleration data will be read, it must be in the following pattern [<timestamp> [ms]; aceleration in x; aceleration in y; aceleration in z], the standard location of file_in is Data/ .

* file_out (Optional)   Name of the file which the angles will be stored, it has the following pattern  [<timestamp>; roll; pitch]. The standard location of file_out is Data/ . 

Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o program
```
Execution:
```markdown
$ ./program function=calculate_roll_and_pitch file_in=attitude_exam.log file_out=attitude_out.log aditional_parameter=yxz
```
or
```markdown
$./programa
Enter the desired command:
function=calculate_roll_and_pitch file_in=attitude_exam.log file_out=attitude_out.log aditional_parameter=yxz
```

### Calculate tilt angle

The function calculates the angle between the xy plane normal and the local z axis.


void calculatetiltang(string file_in, string file_out);

void calculatetiltang(string file_in);

* file_in (Required) - The file in which it will be read gravitational acceleration.

* file_out (Optional) - The name of the file that the output will be stored. The pattern is  <timestamp> [ms]; <angle> [degree]

Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o program
```
Execution:
```markdown
$ ./program function=calculate_tilt_angle file_in=attitude_exam.log file_out=out.log
```
or
```markdown
$./programa
Enter the desired command:
function=calculate_tilt_angle file_in=attitude_exam.log file_out=out.log
```

### Calculate screen rotation

The function calculates the angle between the xy plane normal and the local z axis.


void screenrotationdetector(string file_in, string file_out);

void screenrotationdetector(string file_in);

* file_in (Required) - The file in which it will be read gravitational acceleration.

* file_out (Optional) - The name of the file that the output will be stored. The pattern is  <timestamp> [ms]; <angle> [degree]

Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o program
```
Execution:
```markdown
$ ./program function=calculate_screen_rotation file_in=attitude_exam.log file_out=out.log
```
or
```markdown
$./programa
Enter the desired command:
function=calculate_screen_rotation file_in=attitude_exam.log file_out=out.log
```

### Calculate angle between two acceleration vectors data

Calculate angle between two acceleration vectors and record in a file with the following pattern  <timestamp> [ms]; <angle> [degree]


void calculateanglebetween2vec(string file_in, string file_in, string file_out);

void calculateanglebetween2vec(string file_in, string file_in);

void calculateanglebetween2vec(string file_in);

* file_in (Required) - The file in which it will be read the acceleration data a.

* file_in (Optional) - The file in wich it will be rad the acceleration data b. It is optional in case where all the data is in the first file_in, in this specific case the data will be sorted as [<timestamp>, a<sub>x</sub>, a<sub>y</sub>, a<sub>z</sub> ... b<sub>x</sub>, b<sub>y</sub>, b<sub>z</sub>]. Where a and b are the two acceleration vector.

* file_out (Optional) - The name of the file that the output will be stored.

Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o program
```
Execution:
```markdown
$ ./program function=calculate_angle_between2vec file_in=attitude_exam.log file_in=attitude_exam2.log file_out=out.log
```
or
```markdown
$./programa
Enter the desired command:
function=calculate_angle_between2vec file_in=attitude_exam.log file_in=attitude_exam2.log file_out=out.log
```
### Calculate normal vector of two acceleration vectors data

Calculate normal vector of two acceleration vectors and record in a file with the following pattern  <timestamp> [ms]; <x>; <y>; <z>


void calculatenormalvector(string file_in, string file_in, string file_out);

void calculatenormalvector(string file_in, string file_in);

void calculatenormalvector(string file_in);

* file_in (Required) - The file in which it will be read the acceleration data a.

* file_in (Optional) - The file in wich it will be rad the acceleration data b. It is optional in case where all the data is in the first file_in, in this specific case the data will be sorted as [<timestamp>, a<sub>x</sub>, a<sub>y</sub>, a<sub>z</sub> ... b<sub>x</sub>, b<sub>y</sub>, b<sub>z</sub>]. Where a and b are the two acceleration vector.

* file_out (Optional) - The name of the file that the output will be stored.

Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o program
```
Execution:
```markdown
$ ./program function=calculate_normal_vector file_in=attitude_exam.log file_in=attitude_exam2.log file_out=out.log
```
or
```markdown
$./programa
Enter the desired command:
function=calculate_normal_vector file_in=attitude_exam.log file_in=attitude_exam2.log file_out=out.log
```

### Exit
The function ends the program by user command. The programm wait a command until another command or an exit command is given.

Compiling:
```markdown
$ g++ -std=gnu++11 main.cpp imu.cpp functions.cpp -o program
```
Execution:
```markdown
$ ./program exit
```
or
```markdown
$./programa
Enter the desired command:
exit
```