# raytracing_in_a_weekend

Code from Ray Tracing in a Week-end book and local changes

From "Ray Tracing in a weekend" Peter Shirley book series and code
Lincesed on same  terms. This repo  includes some personal/local 
modifications (e.g. the integration with EZ-draw to display 
outputs as they are getting generated)

See https://github.com/RayTracing/raytracing.github.io 

Quick Start:

    $ make

this will generate out.ppm and, if in MacOS, attempt to visualize it

see also Example3 bellow for a built-in visualizer
and http://paulbourke.net/dataformats/ppm/ for details on .ppm format.

There are few other targets that allow visualization on a window using 
EZ-draw cross platform graphics library as dependency. 

For those please download this package first 

    $ ./get_ezdraw.sh

check https://pageperso.lis-lab.fr/~edouard.thiel/ez-draw/index-en.html
for other potential installation dependencies, notably:

    - MacOS: XQuartz is required . See https://www.xquartz.org
    - Linux: sudo apt-get install libx11-dev x11proto-xext-dev libxext-dev

Then

Example1: Process as ./dump_rt.x but shows progress graphically
    $ make ez_show_rt
    $ ./ez_show_rt.x

Example2: As above but show progressively more level of detail
    $ make ez_show_rt2
    $ ./ez_show_rt2.x

Example3: A built in PPM visualization utility
    $ make ez_show_ppm
    $ ./ez_show_ppm.x < out.ppm
