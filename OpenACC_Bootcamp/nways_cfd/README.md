
Application:
------------
# CFD
Simple 2D regular-grid CFD simulation for teaching parallel scaling concepts

This is a simple simulation of an incompressible fluid flowing in a cavity using the 2D Navier-Stokes equation. The fluid flow can either be viscous (finite Reynolds number and vortices in the flow) on non-viscous (no Reynolds
number specified and no vortices in the flow).

It is deliberately written to be very simple and easy to understand so it can be used as a teaching example.


To build the application, just run the "make". This will produce a binary "cfd". To run the application, just run the executable.

Checking Output:
----------------


## Prerequisites:
To run this tutorial you will need a machine with NVIDIA GPU (**Tested on NVIDIA driver 450.51**)

- Install the [Docker](https://docs.docker.com/get-docker/) or [Singularity](https://sylabs.io/docs/]).
- Install Nvidia toolkit, [Nsight Systems (latest version)](https://developer.nvidia.com/nsight-systems).

## Creating containers
To start with, you will have to build a Docker or Singularity container.

**NOTE: Please build the container on the machine that you are planning to run the container on**.

### Docker Container
To build a docker container, run: 
`sudo docker build -t <imagename>:<tagnumber> .`

For instance:
`sudo docker build -t myimage:1.0 .`

The code labs have been written using Jupyter notebooks and a Dockerfile has been built to simplify deployment. In order to serve the docker instance for a student, it is necessary to expose port 8888 from the container, for instance, the following command would expose port 8888 inside the container as port 8888 on the lab machine:

`sudo docker run --rm -it --gpus=all -p 8888:8888 myimage:1.0`

When this command is run, you can browse to the serving machine on port 8888 using any web browser to access the labs. For instance, from if they are running on the local machine the web browser should be pointed to http://localhost:8888. The `--gpus` flag is used to enable `all` NVIDIA GPUs during container runtime. The `--rm` flag is used to clean an temporary images created during the running of the container. The `-it` flag enables killing the jupyter server with `ctrl-c`. This command may be customized for your hosting environment.

Then, inside the container launch the Jupyter notebook assigning the port you opened:

`jupyter notebook --ip 0.0.0.0 --port 8888 --no-browser --allow-root`


Once inside the container, open the jupyter notebook in browser: http://localhost:8888, and start the lab by clicking on the `minicfd.ipynb` notebook.

### Singularity Container

To build the singularity container, run: 
`singularity build minicfd.simg Singularity`

and copy the files to your local machine to make sure changes are stored locally:
`singularity run minicfd.simg cp -rT /labs ~/labs`

Then, run the container:
`singularity run --nv minicfd.simg jupyter notebook --notebook-dir=~/labs`

Once inside the container, open the jupyter notebook in browser: http://localhost:8888, and start the lab by clicking on the `minicfd.ipynb` notebook.


## Questions?
Please join [OpenACC Slack Channel](https://openacclang.slack.com/messages/openaccusergroup) for questions.
