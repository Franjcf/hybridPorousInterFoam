# tutorials list for python validation script
# adapted from impesFOAM source code in Hourge P. et al (2014))

tutorials = [
	     # Darcy Flow Validation
             {'category' : "DarcyFlowCases", 'case' : "Buckley-Leverett/Flow_Driven_BrooksCorey"}, \
             {'category' : "DarcyFlowCases", 'case' : "Buckley-Leverett/Gravity_Driven_BrooksCorey"}, \
	     {'category' : "DarcyFlowCases", 'case' : "Buckley-Leverett/Flow_Driven_VanGenuchten"}, \
             {'category' : "DarcyFlowCases", 'case' : "Buckley-Leverett/Gravity_Driven_VanGenuchten"}, \
             {'category' : "DarcyFlowCases", 'case' : "GravityCapillarityBalance/Gravity_Capillarity_VanGenuchten"}, \
            
	     # Free-Fluid Validation          
             {'category' : "FreeFlowCases", 'case' : "Bretherton/porousBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "Bretherton/standardBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "CapillaryRiseInTube/porousBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "CapillaryRiseInTube/standardBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "FlatPlateContactAngle/porousBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "FlatPlateContactAngle/standardBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "HeleShawCapillarFlow/porousBoundary"}, \
             {'category' : "FreeFlowCases", 'case' : "HeleShawCapillarFlow/standardBoundary"}, \

             # Example Applications
             {'category' : "ExampleApplications", 'case' : "ViscousFingeringReservoir/viscousFingering"}, \
            # {'category' : "ExampleApplications", 'case' : "CoastalBarrier/coastalBarrier"}, \
            # {'category' : "ExampleApplications", 'case' : "Fracture/fracture"}, \
             {'category' : "ExampleApplications", 'case' : "DrainageAndImbibition/imbibition"}, \
             {'category' : "ExampleApplications", 'case' : "DrainageAndImbibition/drainage"}
            ]
