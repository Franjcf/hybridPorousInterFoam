================================================================================
Simulation of Multiphase Flow in Hybrid-Scale Porous Media
================================================================================

This solver simulates two-phase flow in porous media that contains two characteristic length scales: a large scale solid-free domain where flow is solved through the Volume-Of-Fluid Method, and a small scale porous domain where flow is solved through two-phase Darcy's Law. Both domains are coupled and are solved simultaneously with a single momentum equation and within a single mesh.  

This repository was created by Francisco J. Carrillo and Cyprien Soulaine with the
support of Ian C. Bourg. 

.. figure:: /figures/conceptual.png
    :align: right
    :alt: alternate text
    :figclass: align-right
    Conceptual Representation of the Modeling Framework.

----------------------------------------------------------------------------

.. contents::

################################################################################
General Information
################################################################################

- This toolbox is compatible with OpenFOAM 7.0 and later.

- This toolbox needs only a standard OpenFOAM installation (see www.openfoam.org)

- Read the LICENCE_OPENFOAM file for information about OpenFOAM and this toolbox Copyrights.

################################################################################
Installation
################################################################################

First, make sure to source the OpenFOAM file, as shown in the following example code:

.. code-block:: bash

  source /opt/openfoam7x/etc/bashrc

Then, in the "hybridPorousInterFoam" directory, run: 

.. code-block:: bash

  ./Allwmake

This compiles the libraries "lporousInterfaceProperties.so", "lporousModels.so","lporousTwoPhaseProperties.so" and "lporousImmiscibleIncompressibleTwoPhaseMixture.so" in the standard OpenFOAM user directory : $FOAM_USER_LIBBIN;

The executable solver "hybridPorousInterFoam" is also compiled in the standard OpenFOAM user directory $FOAM_USER_APPBIN.

----------------------------------------------------------------------------

To remove temporary files, dynamic libraries, and executables, run:

.. code-block:: bash

  ./Allwclean 

################################################################################
Running the Tutorials
################################################################################

To test if the solver was installed correctly, you can run all the included tutorial cases by typing the following code within the "tutorials" subdirectory:

.. code-block:: bash

  python runTutorials.py

Note that this will only run each case for a single time step. Still, it might take a while. Also make sure to use python2 to run the associated script.  

----------------------------------------------------------------------------

Each tutorial directory contains "run" and "clean" files to test installation and validate the solver. To run a particular tutorial for more than a single time step just replace "writeNow" with "endTime" within its "system/controlDict" file. Then you can run said tutorial by typing:

.. code-block:: bash

  ./run

or equivalently:

.. code-block:: bash

  hybridPorousInterFoam

To clean the directory:

.. code-block:: bash

  ./clean

################################################################################
List of Included Cases
################################################################################

**Case Template**

- A basic template that includes all the neccesary files to run a succesfull simulation. Each variable within the "0/" directory and the "constant/transportProperties" file is labeled to make it easier to understand 

---------------------------------------------------------------------------- 

**Darcy Flow Cases**

- Test cases related to the verification of the solver in a domain completely occupied by porous media (Replicatino of the 1-D Buckley-Leverett analytical solution and determination of a capillarity-gravity equilibirum)

.. figure:: /figures/Darcy.png
    :align: right
    :alt: alternate text
    :figclass: align-right

----------------------------------------------------------------------------

**Free Flow Cases**

- Test cases related to the verification of the solver in a domain where there is no porous media or just a porous boundary (capillary-driven flows, contact angle implementations, Bretherton thin film-dynamics)

.. figure:: /figures/FreeFlow.png
    :align: right
    :alt: alternate text
    :figclass: align-right

----------------------------------------------------------------------------

**Example Applications**

- Sample cases that show the multi-scale nature of this solver by simulating systems with a combination of porous and free-fluid regions (fractures, coastal barriers, drainage, imbibition, porous fluid reservoir).


**Wave Propagation in Coastal Barriers**

.. figure:: /figures/coastalBarrier.png

|
|
**Drainage and Imbibition in Porous Fractures**

.. figure:: /figures/fracture.png
|
|
**Viscous Fingering in Oil Reservoirs**

.. figure:: /figures/viscousFingering.png
   
    
################################################################################
List of Included Libraries
################################################################################

**porousInterfaceProperties**

- Implementation of a constant contact angle interface condition at the porous media-fluid interface.

----------------------------------------------------------------------------

**porousImmicscibleIncompressibleTwoPhaseMixture**
              
- Implementation of an immicisble incompressible two-phase fluid class that allows for the use of porousInterfaceProperties

----------------------------------------------------------------------------

**porousTwoPhaseProperties:**
     
- Defenition of two-phase fluid properties that allows for the use of porousInterfaceProperties

----------------------------------------------------------------------------

**porousModels/capillarityModels** ( adapted from from Horgue P. & Soulaine C. (2015) )

- Capillary pressure models (Brooks and Corey, Van Genuchten, Linear)

----------------------------------------------------------------------------

**porousModels/phaseModels** ( adapted from from Horgue P. & Soulaine C. (2015) ) 

- Incompressible phase model for porous media flows (constant density and viscosity)

----------------------------------------------------------------------------

**porousModels/relativePermeabilityModels** ( adapted from from Horgue P. & Soulaine C. (2015) )
     
- Relative permeability models (Brooks and Corey, Van Genuchten)

################################################################################
Citing the Toolbox
################################################################################

If you use this solver, please cite the following paper (this will be updated once the publication is accepted):

Carrillo, F. J., Bourg, I. C., Soulaine, C., 2020, Multiphase Flow Modelling in Multiscale Porous Media: An Open-Sourced Micro-Continuum Approach, arXiv:2003.08374

https://arxiv.org/abs/2003.08374

################################################################################
Authors' Publications
################################################################################
1. Carrillo, F. J., Bourg, I. C., 2019. A darcy-brinkman-biot approach to modeling the hydrology and mechanics of porous media containing758 macropores and deformable microporous regions. Water Resources Research 55, 8096–8121

2. Soulaine, C., Gjetvaj, F., Garing, C., Roman, S., Russian, A., Gouze, P., Tchelepi, H., May 2016. The impact of sub-resolution porosity of918 x-ray microtomography images on the permeability. Transport in Porous Media 113 (1), 227–243.919

3. Soulaine, C., Roman, S., Kovscek, A., Tchelepi, H. A., 2017. Mineral dissolution and wormholing from a pore-scale perspective. Journal of920 Fluid Mechanics 827, 457–483.921 URL https://www.cambridge.org/core/product/identifier/S0022112017004992/type/journal_article922 

4. Soulaine, C., Roman, S., Kovscek, A., Tchelepi, H. A., 2018. Pore-scale modelling of multiphase reactive ﬂow. Application to mineral923 dissolution with production of CO2. Journal of Fluid Mechanics 855, 616–645.924 Soulaine, C., Tchelepi, H.A., 2016.Micro-continuumapproachforpore-scalesimulationofsubsurface processes.TransportIn PorousMedia925 113, 431–456

5. Soulaine, C., Creux, P., Tchelepi, H. A., 2019. Micro-continuum framework for pore-scale multiphase ﬂuid transport in shale formations.916 31 Transport in Porous Media.

6. Horgue, P., Soulaine, C., Franc, J., Guibert, R., Debenest, G., 2015. An open-source toolbox for multiphase ﬂow in porous media. Computer810 Physics Communications 187 (0), 217– 226

