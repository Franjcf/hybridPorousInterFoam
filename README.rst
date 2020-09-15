================================================================================
Simulation of Multiphase Flow in Hybrid-Scale Porous Media
================================================================================

This solver simulates single- and two-phase flow in porous media that contains two characteristic length scales: a large scale solid-free domain where flow is solved through the Volume-Of-Fluid Method, and a small scale porous domain where flow is solved through two-phase Darcy's Law. Both domains are coupled and are solved simultaneously with a single momentum equation and within a single mesh.  

The most recent version also includes a simplified solver that can be used exclusively to model single-phase flow in hybrid scale porous media. 

This repository was created by Francisco J. Carrillo and Cyprien Soulaine with the
support of Ian C. Bourg. 

**Conceptual Representation of the Modeling Framework:**

.. figure:: /figures/conceptual.png
    :align: right
    :alt: alternate text
    :figclass: align-right
    

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

The executable solvers "hybridPorousInterFoam" (for multiphase flow) and "hybridPorousPimpleFoam" (for single-phase flow) are also compiled in the standard OpenFOAM user directory $FOAM_USER_APPBIN.

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

  hybridPorousInterFoam (for multiphase flow cases)
  hybridPorousPimpleFoam (for single-phase flow cases)

To clean the directory:

.. code-block:: bash

  ./clean

################################################################################
List of Included Cases
################################################################################

**Case Template**

- A basic template that includes all the neccesary files to run a succesfull simulation. Each variable and parameter within the "0/" directory and the "constant/transportProperties" file is labeled and explained.

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

- Sample cases that show the multi-scale nature of this solver by simulating multiphase systems with a combination of porous and free-fluid regions (i.e. fractures, coastal barriers, drainage, imbibition, and a porous reservoirs). Some of these contain additional single-phase cases for use with the single-phase solver.


**Wave Propagation in Coastal Barriers:**

.. figure:: /figures/coastalBarrier.png

|
|
**Drainage and Imbibition in Porous Fractures:**

.. figure:: /figures/fracture.png
|
|
**Viscous Fingering in Oil Reservoirs:**

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

**porousModels/phaseModels** ( *adapted* ) 

- Incompressible phase model for porous media flows (constant density and viscosity)

----------------------------------------------------------------------------

**porousModels/capillarityModels** ( *adapted* )

- Capillary pressure models (Brooks and Corey, Van Genuchten, Linear)

----------------------------------------------------------------------------

**porousModels/relativePermeabilityModels** ( *adapted*  )
     
- Relative permeability models (Brooks and Corey, Van Genuchten)

----------------------------------------------------------------------------

**Note on Adapted Libraries**

- The libraries marked as "adapted" were obtained from the open-sourced *porousMultiphaseFoam* source code published in Horgue P. et al. (2015). Said code can be used to efficiently model full Darcy-scale flows. 

################################################################################
Citing the Toolbox
################################################################################

If you use this solver, please cite the following paper (theory) and the code (implementation):

**Paper:**
Carrillo F.J., Bourg, I. C., Soulaine, C., Multiphase flow modeling in multiscale porous media: An open-source micro-continuum approach, J. Comput. Phys. (2020), https://doi.org/10.1016/j.jcpx.2020.100073

**Code:** 
https://doi.org/10.5281/zenodo.3724707 (DOI: 10.5281/zenodo.3724707)


################################################################################
Authors' Publications
################################################################################
1. Carrillo, F. J., Bourg, I. C., 2019. A darcy-brinkman-biot approach to modeling the hydrology and mechanics of porous media containing758 macropores and deformable microporous regions. Water Resources Research 55, 8096–8121

2. Soulaine, C., Gjetvaj, F., Garing, C., Roman, S., Russian, A., Gouze, P., Tchelepi, H., May 2016. The impact of sub-resolution porosity of918 x-ray microtomography images on the permeability. Transport in Porous Media 113 (1), 227–243.919

3. Soulaine, C., Roman, S., Kovscek, A., Tchelepi, H. A., 2017. Mineral dissolution and wormholing from a pore-scale perspective. Journal of920 Fluid Mechanics 827, 457–483.921 URL https://www.cambridge.org/core/product/identifier/S0022112017004992/type/journal_article922 

4. Soulaine, C., Roman, S., Kovscek, A., Tchelepi, H. A., 2018. Pore-scale modelling of multiphase reactive ﬂow. Application to mineral923 dissolution with production of CO2. Journal of Fluid Mechanics 855, 616–645.924 Soulaine, C., Tchelepi, H.A., 2016.Micro-continuumapproachforpore-scalesimulationofsubsurface processes.TransportIn PorousMedia925 113, 431–456

5. Soulaine, C., Creux, P., Tchelepi, H. A., 2019. Micro-continuum framework for pore-scale multiphase ﬂuid transport in shale formations.916 31 Transport in Porous Media.

6. Horgue, P., Soulaine, C., Franc, J., Guibert, R., Debenest, G., 2015. An open-source toolbox for multiphase ﬂow in porous media. Computer Physics Communications 187 (0), 217– 226

7. The referenced Darcy-Scale toolbox can be found here: https://github.com/phorgue/porousMultiphaseFoam
