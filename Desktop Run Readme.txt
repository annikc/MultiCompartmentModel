Desktop Run Readme
Annik Carson
Last updated: March 25, 2016

Opening promptWindow gives user access to control of all parameters for STDP experiments. 

Paired synapses are GABAergic synapses which are pseudo-randomly distributed (per random synapse distribution seed, by default set as 37264 for no particular reason). They are "paired" with current clamp activity -- i.e. the clamp is set to start within some delta_t of the start of paired synapse spikes. (The delta_t value, inconveniently, is set in the mosinit files, in the procedure add_timestep().)

The location of these synapses can be set by the user from the dropdown menu. I have not set up synapse distribution throughout the entire cell simultaneously. Start of Paried Synapse Spikes determines the onset of plasticity induction. 

***You can ignore the Unpaired Synapses block.*** These basically function the same as the paired synapses. I have set the density to 0 because we're not using them right now. (They are if you want to have one set of synapses activated coincidently with the clamp, and another set activated non-coincidently with the clamp. This was originally to try to replicate results from Woodin & Ormond 2010.)

In promptWindow, toggling radio button for "Record Data" on calls mosinit.hoc. This is not recommended as mosinit.hoc records E_Cl, membrane phosphorylated KCC2, calcium concentration, active kinase, and active phosphatase. Tracking all of these variables together at a sampling rate of 2000 Hz requires significant memory. This mosinit file was written as a template to be used on the SciNet system on large memory nodes. 

To run the simulation without recording data, leave the radio button unchecked. promptWindow then calls mosinit_RUNonly.hoc, which does not record data from any variables. 

Clicking the Create Cell button calls either mosinit.hoc or mosinit_RUNonly.hoc (depending on whether you selected record data or not)

mosinit.hoc and mosinit_RUNonly.hoc are identical in the hoc files they call. The tree is as follows: 

promptWindow.hoc
	mosinit.hoc
		setParameters.hoc
		makeCell.hoc
			makeGeometry.hoc
			makeIons.hoc
			makeTransporters.hoc
			makeActiveChannels.hoc
			makePairedUnpaired.hoc
		makeWindows.hoc

This should generate all of the windows necessary to play with the model. 

Simulation is run from RunControl window. Plasticity induction is started ~ 10000s after the simulation begins, and is carried out at 5Hz for 30000 ms with clamp amp and duration at 2 nA and 2ms, respectively, as per Woodin et al. (2003). Plasticity induction parameters can be changed in promptWindow (Paired Synapses block). promptWindow defaults should generate the proper plasticity induction protocol.