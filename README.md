# ESL_hw1
NTHU EE6470 ESL homework 1

## Part 1 (filter without input buffer)
### To compile and run the program. <br>
In the top most directory.
```bash 
$ cd ./hw1_part1
$ mkdir build
$ cd build
$ cmake ..
$ make
```
#### Testing 1
```bash 
$ ./filter ../../lena_color_256_noise.bmp ./lena_color_256_out.bmp
```
Open **lena_color_256_out.bmp** to check the image and the number of pixel transfer is shown on the terminal.
<br>

#### Testing 2
```bash 
$ ./filter ../../peppers_color_noise.bmp ./peppers_color_out.bmp
```
Open **peppers_color_out.bmp** to check the image and the number of pixel transfer is shown on the terminal.
<br>


## Part 2 (filter with input buffer)
### To compile and run the program. <br>
In the top most directory.
```bash 
$ cd ./hw1_part2
$ mkdir build
$ cd build
$ cmake ..
$ make
```
#### Testing 1
```bash 
$ ./filter ../../lena_color_256_noise.bmp ./lena_color_256_out.bmp
```
Open **lena_color_256_out.bmp** to check the image and the number of pixel transfer is shown on the terminal.
<br>

#### Testing 2
```bash 
$ ./filter ../../peppers_color_noise.bmp ./peppers_color_out.bmp
```
Open **peppers_color_out.bmp** to check the image and the number of pixel transfer is shown on the terminal.
<br>
