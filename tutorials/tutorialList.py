# tutorials list for python validation script
# adapted from impesFOAM source code in Hourge P. et al (2014))

tutorials = [
	     # Darcy Flow Validation
             {'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/flow_Driven_BrooksCorey"}, \
             {'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/gravity_Driven_BrooksCorey"}, \
	     {'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/flow_Driven_VanGenuchten"}, \
             {'category' : "Darcy_Flow_Cases", 'case' : "Buckley-Leverett/gravity_Driven_VanGenuchten"}, \
             {'category' : "Darcy_Flow_Cases", 'case' : "Gravity_Capillarity_Equilibrium/gravity_Capillarity_VanGenuchten"}, \
             {'category' : "Darcy_Flow_Cases", 'case' : "Gravity_Capillarity_Equilibrium/gravity_Capillarity_BrooksCorey"}, \
            
	     # Free-Fluid Validation          
             {'category' : "Free_Flow_Cases", 'case' : "Bretherton/porous_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Bretherton/standard_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Capillary_Rise/porous_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Capillary_Rise/standard_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Flat_Plate_Contact_Angle/porous_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Flat_Plate_Contact_Angle/standard_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Hele-Shaw_Capillary_Flow/porous_Boundary"}, \
             {'category' : "Free_Flow_Cases", 'case' : "Hele-Shaw_Capillary_Flow/standard_Boundary"}, \

             # Example Applications
             {'category' : "Example_Applications", 'case' : "Viscous_Fingering_Reservoir/viscous_Fingering"}, \
             {'category' : "Example_Applications", 'case' : "Coastal_Barrier/coastal_Barrier"}, \
             {'category' : "Example_Applications", 'case' : "Fracture/fracture_Imbibition"}, \
             {'category' : "Example_Applications", 'case' : "Fracture/fracture_Drainage"}, \
             {'category' : "Example_Applications", 'case' : "Drainage_and_Imbibition/imbibition"}, \
             {'category' : "Example_Applications", 'case' : "Drainage_and_Imbibition/drainage"}
            ]
