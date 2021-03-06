# affine_sift
This repository contains a code for doing SIFT matching using Affine SIFT algorithm


This directory contains the C++ code for ASIFT, a fully affine invariant image 
matching algorithm. 

************************** Unix/Linux/Mac Users **************************
For Unix/Linux and Mac users, the code is ready to be compiled. The 
executable adapted to your computer system is generated after compiling.
**************************************************************************

**************************** Matlab Interface ****************************
Although the ASIFT program is standalone and can be executed without Matlab,
a Matlab interface is provided (for Unix/Linux/Mac/Windows users). 
**************************************************************************


I. UNIX/LINUX/MAC USER GUIDE

The source code needs to be compiled before the software can be used. 
The compilation requires the make program, and is typically straightforward.

- Library. 
This code requires the libpng library. You can automatically download, 
compile and include this library to the compiled program by adding the 
LOCAL_LIBS=1 option to the make commands.

- Image format. 
Only the PNG format is supported. 
 
-------------------------------------------------------------------------
Source compilation and software usage
1. Download the ASIFT code package and extract it. Go to that directory. 

2. Compile the source code (on Unix/Linux/Mac OS). 
There are two ways to compile the code. 
(1) RECOMMENDED, with Open Multi-Processing multithread parallelization 
(http://openmp.org/). Roughly speaking, it accelerates the program using the 
multiple processors in the computer. Run
make OMP=1

OR
(2) If the complier does not support OpenMp, run 
make

ATTENTION:
If libpng (the official PNG reference library) is not installed in your computer, 
an option LOCAL_LIBS=1 should be added after make. Example
make OMP=1 LOCAL_LIBS=1
The compilation will automatically download and compile libpng and zlib and 
include the library to the program.

3. Run ASIFT. 
./demo_ASIFT imgIn1.png, imgIn2.png imgOutVert.png imgOutHori.png matchings.txt 

keys1.txt keys2.txt

-- imgIn1.png, imgIn2.png: Input images (in png format).
-- imgOutVert.png, imgOutHori.png: Output images (vertical/horizontal concatenated). 
The detected matches are connected by write lines.
-- matchings.txt: The file format starts with 1 integer giving the total number 
of matches. Then each line specifies the coordinates (col1, row1, col2, row2) 
of a pair of matched points. (col: horizontal axis, from left to right. 

row: vertical axis, from top to bottom.)
-- keys1.txt keys2.txt: ASIFT keypoints in the two images, in the same format 
as the SIFT keypoints of David Lowe. The file starts with 2 integers giving 
the total number of keypoints and the length of the descriptor vector for each 
keypoint (128). Then the location of each keypoint in the image is specified 
by 4 floating point numbers giving subpixel column and row location, scale, 
and orientation (in radians from -PI to PI). Finally, the invariant descriptor
 vector for the keypoint is given as a list of 128 integers in range [0,255]. 
-- [optional 0/1]. 1: input images resize to an area equal to 800x600 for ASIFT,
 in keeping the aspect ratio (by default). 0: no resize. The resize is to limit
 the ASIFT computation time. The results (output images, keypoint coordinates
 and scales) are normalized to the original image size, so the resize is 
"transparent" to the user. 

Example, run
./demo_ASIFT adam1.png adam2.png imgOutVert.png imgOutHori.png matchings.txt 

keys1.txt keys2.txt 

You get on the screen 
"WARNING: The input images are resized to 800x600 for ASIFT. 
         But the results will be normalized to the original image size.

Computing keypoints on the two images...
12928 ASIFT keypoints are detected. 
8972 ASIFT keypoints are detected. 
Keypoints computation accomplished in 24 seconds.
Matching the keypoints...
The two images match! 914 matchings are identified. log(nfa)=-1496.88.
Keypoints matching accomplished in 4 seconds."

-------------------------------------------------------------------------
-------------------------------------------------------------------------
II. WINDOWS USER GUIDE

_________________________________________________________________________
A. SOURCE COMPILATION
_________________________________________________________________________
Windows users who want to recompile the source code themselves, please follow the 
guidelines below for a smooth compilation. 

It is assumed that the CMake and Visual Studio are installed. Moreover, 
the Intel C++ compiler, which supports vectorization, is highly recommended. 
For an optimized software execution speed, it is crucial that both OpenMP
and vectorization are activated and effective (see below). (Note that
the CPU must have SSE2 or higher instruction sets in order to make vectorization
possible. The /arch:SSE2 opiton must be turned on, which should have
been normally the case.)

1. If you don't have CMake, an open-source build system,
then download and install it from http://cmake.org

2. Launch the CMake program cmake-gui.exe

3. Provide the paths
- "Where is the source code :" (the path that leads to CMakeLists.txt and 
the ASIFT source code), e.g., E:/demo_ASIFT_src

- Create a subdirectory Build under demo_ASIFT_src

- "Where to build the binaries:" (the directory where build project and 
object files will be stored), e.g., E:/demo_ASIFT_src/Build

4. Press "Configure" and select "Use default native compilers" and 
select the code IDE that you have in your machine, e.g., Visual Studio 10.

5. Press "Generate". A Visual Studio solution file ASIFT.sln will
be created under E:/demo_ASIFT_src/Build

6. Launch Visual Studio 10, and open ASIFT.sln. 

7. Switch the mode from Debug to Release.

8. Not mandatory, but HIGHLY RECOMMENDED (for program acceleration).
- Switch from the Microsoft Visual C++ 
compiler to the Intel C++ compiler, if you have it. 

- Turn on OpenMP
Click the demo_ASIFT project in the Solution Explorer. Select the menu 
Project -> Property -> Configuration Properties -> C/C++ -> Language [Intel C++]
Set OpenMP Support to "Generate Parallel Code (/Qopenmp)"

- Open demo_lib_sift.cpp under demo_ASIFT/Source Files in the Solution Explorer.
Make the following code change in demo_lib_sift.cpp.
unsigned short distsq = 0; ----> int distsq = 0;

Note: This manipulation allows the compiler to vectorize the SIFT code
comparison, which accelerates the ASIFT keypoint matching by a factor of
 from 5 to 20. To have the vectorization possible, this distsq variable must
 be in unsigned short when compiled with make on Linux/Mac, and be instead
int when complied with the Intel C++ on Windows. Therefore 
this format should be adapted according to the compiler. (So don't
 forget to change it back if you want to compile the code on Linux/Mac.) 
This vectorization is not achieved with the Visual C++ compiler. 

9. Build solution. An executable will be created in Build/Release. 
Run it in a Dos command prompt. 
demo_ASIFT adam1.png adam2.png imgOutVert.png imgOutHori.png matchings.txt
 keys1.txt keys2.txt
(It follows the same syntax of that for Unix/Linux/Mac described above.)

-------------------------------------------------------------------------
-------------------------------------------------------------------------
III. MATLAB INTERFACE (OPTIONAL)
Run ASIFT via Matlab: Open test_demo_ASIFT.m in Matlab and execute the script. 
The Matlab interface reads most standard image formats.

-------------------------------------------------------------------------
-------------------------------------------------------------------------
CREDITS
- The epipolar geometry filtering algorithm ORSA of Moisan and Stival is 
used at the end of the ASIFT algorithm 
to eliminate false matches. 
http://www.math-info.univ-paris5.fr/~moisan/epipolar/

Pierre Moulon contributed to the SVD subroutine of ORSA. The SVD subroutine
uses 
the toolbox Eigen, which is LGPL-licensed. 

- We would like to thank Nicolas Limare for his help on developing the program, 
and Pierre Moulon for his help on making the Windows compilation much easier with 
CMake. 


