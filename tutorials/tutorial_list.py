# tutorials list for python validation script
# adapted from porousMultiphaseFoam source code, Horgue P. et al. (2014)

tutorials = [
             # Case Template 
             {'solver': "hybridPorousInterFoam",'category' : "Case_Template", 'case' : "template"}, \

	     # Darcy Flow Validation
             {'solver': "hybridPorousInterFoam",'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/flow_Driven_BrooksCorey"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/gravity_Driven_BrooksCorey"}, \
	     {'solver': "hybridPorousInterFoam",'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/flow_Driven_VanGenuchten"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/gravity_Driven_VanGenuchten"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Darcy_Flow_Cases", 'case' : "Gravity_Capillarity_Equilibrium/gravity_Capillarity_VanGenuchten"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Darcy_Flow_Cases", 'case' : "Gravity_Capillarity_Equilibrium/gravity_Capillarity_BrooksCorey"}, \
            
	     # Free-Fluid Validation          
             {'solver': "hybridPorousInterFoam",'category' : "Free_Flow_Cases", 'case' : "Bretherton/porous_Boundary"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Free_Flow_Cases", 'case' : "Bretherton/standard_Boundary"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Free_Flow_Cases", 'case' : "Capillary_Rise/porous_Boundary"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Free_Flow_Cases", 'case' : "Capillary_Rise/standard_Boundary"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Free_Flow_Cases", 'case' : "Flat_Plate_Contact_Angle/porous_Boundary"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Free_Flow_Cases", 'case' : "Flat_Plate_Contact_Angle/standard_Boundary"}, \

             # Example Applications
             {'solver': "hybridPorousInterFoam",'category' : "Example_Applications", 'case' : "Viscous_Fingering_Reservoir/viscous_Fingering"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Example_Applications", 'case' : "Coastal_Barrier/coastal_Barrier"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Example_Applications", 'case' : "Fracture/fracture_Imbibition"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Example_Applications", 'case' : "Fracture/fracture_Drainage"}, \
             {'solver': "hybridPorousPimpleFoam",'category' : "Example_Applications", 'case' : "Fracture/fracture_Single_Phase"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Example_Applications", 'case' : "Drainage_and_Imbibition/imbibition"}, \
             {'solver': "hybridPorousInterFoam",'category' : "Example_Applications", 'case' : "Drainage_and_Imbibition/drainage"}, \
             {'solver': "hybridPorousPimpleFoam",'category' : "Example_Applications", 'case' : "Drainage_and_Imbibition/single_Phase"}
            ]
