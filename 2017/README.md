# MultiCompartmentModel

Last updated: May 25, 2016

Before opening nrngui, make sure to compile code. Simulations can be run on desktop by opening the nrngui and loading the hoc file 
```
promptWindow.hoc
```
##promptWindow
promptWindow gives user access to control of all parameters for STDP experiments. 
### Paired Synapses
The location of these synapses can be set by the user from the dropdown menu. I have not set up synapse distribution throughout the entire cell simultaneously. Synaptic density should be as follows: 
```
soma = 12.5 / um^2
prox = 0.1334 / um^2
midd = 0.009 / um^2
dist = 0.0025 / um^2
```
By default synapses are in the proximal dendrites. 

Start of Paried Synapse Spikes determines the onset of plasticity induction. 
Paired synapses are GABAergic synapses which are pseudo-randomly distributed (per random synapse distribution seed, by default set as 37264 for no particular reason). They are "paired" with current clamp activity -- i.e. the clamp is set to start within some delta_t of the start of paired synapse spikes. (The delta_t value, inconveniently, is set in the mosinit files, in the procedure add_timestep().)
To modify the delta_t value i.e. the time betweeen pre- and post-synaptic inputs, edit the correct *mosinit* file. If data is not recorded (default setting in promptWindow), the "Create Cell" button executes 
```
mosinit_RUNonly.hoc
```
If data is to be recorded (not recommended for desktop runs -- intended to be run on SciNet on large memory nodes), the "Create Cell" button executes
```
mosinit.hoc
```
In both files, delta_t value can be modified by changing the value to be appended to *timesteps*, i.e.: 
```python
proc add_timestep(){
	timesteps.append(5)
}
add_timestep()
```
### Unpaired synapses
***You can ignore the Unpaired Synapses block.*** These basically function the same as the paired synapses. I have set the density to 0 because we're not using them right now. (They are if you want to have one set of synapses activated coincidently with the clamp, and another set activated non-coincidently with the clamp. This was originally to try to replicate results from Woodin & Ormond 2010.)

### Current Clamp
For the standard induction protocol, the defaults should be 
```
Current clamp amp = 3 (nA)
Current clamp dur = 5 (ms)
Interval between clamp events = 200 (ms) 
Number of Clamp events = 150
```

### Random Synapse Distribution seed
Change only if you want new synapse distribution. The default number is totally random.

### Record data
Checking the "Record Data" box is not recommended for desktop simulation runs. This causes "Create Cell" to call mosinit.hoc, which calls for significant memory allocation to record variables after the simulation run. Leaving "Record Data" unchecked calls mosinit_RUNonly.hoc, which does not require any memory allocation. Aside from data recording, mosinit.hoc and mosinit_RUNonly.hoc are identical in the hoc files they call. 

The tree is as follows: 
```
promptWindow.hoc
	mosinit_RUNonly.hoc (or mosinit.hoc)
		setParameters.hoc
		makeCell.hoc
			makeGeometry.hoc
			makeIons.hoc
			makeTransporters.hoc
			makeActiveChannels.hoc
			makePairedUnpaired.hoc
		makeWindows.hoc
```

### Running Simulations of the Cell
Clicking "Create Cell" will generate all of the windows necessary to play with the model specified by the user in the promptWindow. Simulation is run from RunControl window. 

By default, plasticity induction is started ~ 10000s after the simulation begins, and is carried out at 5Hz for 30000 ms with clamp amp and duration at 3nA and 5ms, respectively (this protocol is a modified version of the plasticity induction protocol presented in Woodin et al., 2003). Plasticity induction parameters can be changed in promptWindow (Paired Synapses block). promptWindow defaults should generate the proper plasticity induction protocol.

Most other relevant parameters can be changed in setParameters.hoc. Changes to any hoc files can be implemented by clicking "Create Cell" again, without quitting NEURON all together. Changes to any mod files will require fully exiting NEURON, recompiling code (with *nrnivmodl* for Linux/UNIX or Mac, or the *mknrndll* applet with Windows), and reopening promptWindow.hoc. 




Issues with determining appropriate Ca channel conductances -- 
	Perez-Reyes 2003 (http://physrev.physiology.org/content/83/1/117.long) gives a range of Ttype channel conductances; 3.5pS (pH = 6) - 10.8pS (ph = 9). Our measures of conductance are S/cm^2 or mho/cm^2, therefore need some estimate of T-type channel density. 
	https://www.ncbi.nlm.nih.gov/pmc/articles/PMC1890444/ discusses the role of PKC activity on channel conductance and suggests no change in density due to PKC activity, however density measured by fluorescence and not by quantitative means. 
