'''
Some .dat files missing; resync with SciNet and/or rerun files (move data fom scratch folder permanently)
soma[where syn were present] contains timesteps {-50, -25 ... }
	timesteps[delta t values] contains section lists {soma / prox / mid / dist}
		section lists[soma/prox/midd/dist] contains individual sections i.e. in prox{dend[0], dend[1] ...}
			sections[dend[i], etc] contains vectors of data
''' 
from readNRNdata import * 

##############################################
# Read in Data
##############################################
# Set up vector of STDP spike timing interval values used during data collection
timesteps = np.array([-50, -25, -15, -10, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5])

# set up vector of dendrites in sectionlists Proximal, middle, and distal
prox_seclist = np.array([0, 1, 2, 3, 5, 6, 7, 8, 9, 29, 42, 43, 44, 45, 46, 47, 54, 56])
midd_seclist = np.array([4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 48, 49, 50, 51, 52, 53, 55, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 139, 140, 141, 142, 147, 150, 151, 154, 155, 156, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 174, 175, 176, 177, 178, 179])
dist_seclist = np.array([92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 143, 144, 145, 146, 148, 149, 152, 153, 157, 158, 173])

# set up lists for storing read data
soma_syn = []
prox_syn = []
midd_syn = []
dist_syn = []

for i in range(len(timesteps)):
	soma_syn.append(nrnReader("../../../../../msc/SciNet/data/coarseExpts/soma_{0}.dat".format(timesteps[i])))
	prox_syn.append(nrnReader("../../../../../msc/SciNet/data/coarseExpts/proximal_{0}.dat".format(timesteps[i])))
	midd_syn.append(nrnReader("../../../../../msc/SciNet/data/coarseExpts/middle_{0}.dat".format(timesteps[i])))
	dist_syn.append(nrnReader("../../../../../msc/SciNet/data/coarseExpts/distal_{0}.dat".format(timesteps[i])))

num_var = soma_syn[0].num_variables


# Set up dictionaries for organizing imported data, based on where synaptic connections were present during data collection
somatic_list = dict()
proximal_list = dict()
middle_list = dict()
distal_list = dict()

for i in range(len(timesteps)):
	## SYNAPSES INSERTED IN SOMA
	somatic_list["delta_{0}".format(timesteps[i])] = dict()
	# Dictionaries of data recorded from each area of the cell
	somatic_list["delta_{0}".format(timesteps[i])]["soma"] = dict()
	somatic_list["delta_{0}".format(timesteps[i])]["prox"] = dict()
	somatic_list["delta_{0}".format(timesteps[i])]["midd"] = dict()
	somatic_list["delta_{0}".format(timesteps[i])]["dist"] = dict()

	# add data to dictionaries
	somatic_list["delta_{0}".format(timesteps[i])]["soma"]["soma"] = []
	for k in range(num_var):
		somatic_list["delta_{0}".format(timesteps[i])]["soma"]["soma"].append(soma_syn[i].var_list.varList[k].secList[0][0]) ### what is the seclist[1]?????/not working with index 0 which should be soma

	for j in range(len(prox_seclist)):
		somatic_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])] = []
		for k in range(num_var):
			somatic_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])].append(soma_syn[i].var_list.varList[k].secList[1][j])			

	for j in range(len(midd_seclist)):
		somatic_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])] = []
		for k in range(num_var):
			somatic_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])].append(soma_syn[i].var_list.varList[k].secList[2][j])

	for j in range(len(dist_seclist)):
		somatic_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])] = []
		for k in range(num_var):
			somatic_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])].append(soma_syn[i].var_list.varList[k].secList[3][j])

	## SYNAPSES INSERTED IN PROXIMAL DENDRITES
	proximal_list["delta_{0}".format(timesteps[i])] = dict()
	# Dictionaries of data recorded from each area of the cell
	proximal_list["delta_{0}".format(timesteps[i])]["soma"] = dict()
	proximal_list["delta_{0}".format(timesteps[i])]["prox"] = dict()
	proximal_list["delta_{0}".format(timesteps[i])]["midd"] = dict()
	proximal_list["delta_{0}".format(timesteps[i])]["dist"] = dict()

	# add data to dictionaries
	proximal_list["delta_{0}".format(timesteps[i])]["soma"]["soma"] = []
	for k in range(num_var):
		proximal_list["delta_{0}".format(timesteps[i])]["soma"]["soma"].append(prox_syn[i].var_list.varList[k].secList[0][0]) ### what is the seclist[1]?????/not working with index 0 which should be soma

	for j in range(len(prox_seclist)):
		proximal_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])] = []
		for k in range(num_var):
			proximal_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])].append(prox_syn[i].var_list.varList[k].secList[1][j])			

	for j in range(len(midd_seclist)):
		proximal_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])] = []
		for k in range(num_var):
			proximal_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])].append(prox_syn[i].var_list.varList[k].secList[2][j])

	for j in range(len(dist_seclist)):
		proximal_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])] = []
		for k in range(num_var):
			proximal_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])].append(prox_syn[i].var_list.varList[k].secList[3][j])

	## SYNAPSES INSERTED IN MIDDLE DENDRITES
	middle_list["delta_{0}".format(timesteps[i])] = dict()
	# Dictionaries of data recorded from each area of the cell
	middle_list["delta_{0}".format(timesteps[i])]["soma"] = dict()
	middle_list["delta_{0}".format(timesteps[i])]["prox"] = dict()
	middle_list["delta_{0}".format(timesteps[i])]["midd"] = dict()
	middle_list["delta_{0}".format(timesteps[i])]["dist"] = dict()

	# add data to dictionaries
	middle_list["delta_{0}".format(timesteps[i])]["soma"]["soma"] = []
	for k in range(num_var):
		middle_list["delta_{0}".format(timesteps[i])]["soma"]["soma"].append(midd_syn[i].var_list.varList[k].secList[0][0]) ### what is the seclist[1]?????/not working with index 0 which should be soma

	for j in range(len(prox_seclist)):
		middle_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])] = []
		for k in range(num_var):
			middle_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])].append(midd_syn[i].var_list.varList[k].secList[1][j])			

	for j in range(len(midd_seclist)):
		middle_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])] = []
		for k in range(num_var):
			middle_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])].append(midd_syn[i].var_list.varList[k].secList[2][j])

	for j in range(len(dist_seclist)):
		middle_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])] = []
		for k in range(num_var):
			middle_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])].append(midd_syn[i].var_list.varList[k].secList[3][j])


#print middle_list["delta_-50"]["prox"].keys()
	## SYNAPSES INSERTED IN DISTAL DENDRITES
	distal_list["delta_{0}".format(timesteps[i])] = dict()
	# Dictionaries of data recorded from each area of the cell
	distal_list["delta_{0}".format(timesteps[i])]["soma"] = dict()
	distal_list["delta_{0}".format(timesteps[i])]["prox"] = dict()
	distal_list["delta_{0}".format(timesteps[i])]["midd"] = dict()
	distal_list["delta_{0}".format(timesteps[i])]["dist"] = dict()

	# add data to dictionaries
	distal_list["delta_{0}".format(timesteps[i])]["soma"]["soma"] = []
	for k in range(num_var):
		distal_list["delta_{0}".format(timesteps[i])]["soma"]["soma"].append(dist_syn[i].var_list.varList[k].secList[0][0]) ### what is the seclist[1]?????/not working with index 0 which should be soma

	for j in range(len(prox_seclist)):
		distal_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])] = []
		for k in range(num_var):
			distal_list["delta_{0}".format(timesteps[i])]["prox"]["dend_{0}".format(prox_seclist[j])].append(dist_syn[i].var_list.varList[k].secList[1][j])			

	for j in range(len(midd_seclist)):
		distal_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])] = []
		for k in range(num_var):
			distal_list["delta_{0}".format(timesteps[i])]["midd"]["dend_{0}".format(midd_seclist[j])].append(dist_syn[i].var_list.varList[k].secList[2][j])

	for j in range(len(dist_seclist)):
		distal_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])] = []
		for k in range(num_var):
			distal_list["delta_{0}".format(timesteps[i])]["dist"]["dend_{0}".format(dist_seclist[j])].append(dist_syn[i].var_list.varList[k].secList[3][j])



###########################################
# Cl Reversal Potential
###########################################

soma_ecl = np.zeros(len(timesteps))
prox_ecl = np.zeros(len(timesteps))
midd_ecl = np.zeros(len(timesteps))
dist_ecl = np.zeros(len(timesteps))

for i in range(len(timesteps)):
	#soma_ecl[i] = soma_syn[i].var_list.varList[0].secList[0]
	prox_ecl[i] = prox_syn[i].var_list.varList[0].secList[1][0]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3] 
	##### NOTE: secList indices 1,2,3 contain vectors with recordings from all sections ... how do we want to organize this data?
	#midd_ecl[i] = midd_syn[i].var_list.varList[0].secList[2]
	#dist_ecl[i] = dist_syn[i].var_list.varList[0].secList[3]

	#print prox_ecl[i]

#LTtype_cyt_1 = np.zeros(1200)
#for i in range(1201):
#	LTtype_cyt_1[i-1] = LT_pos1_KCC2.var_data[0][i+20000]
#

###########################################
# Membrane Phosphorylated KCC2 (proportion)
###########################################
soma_MP = np.zeros(len(timesteps))
prox_MP = np.zeros(len(timesteps))
midd_MP = np.zeros(len(timesteps))
dist_MP = np.zeros(len(timesteps))

#for i in range(len(timesteps)):
	#soma_MP[i] = soma_syn[i].var_list.varList[1].secList[0]
	#prox_MP[i] = prox_syn[i].var_list.varList[1].secList[1]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3]
	#midd_MP[i] = midd_syn[i].var_list.varList[1].secList[2]
	#dist_MP[i] = dist_syn[i].var_list.varList[1].secList[3]

	#print prox_ecl[i]

###########################################
# Calcium Concentration
###########################################


###########################################
# Active Kinase (proportion)
###########################################


###########################################
# Active Phosphatase (proportion)
###########################################




#f, axarr = plt.subplots(4, sharex=True)
##### Plot Python generated data
## Plot Ka - Pa i.e. total phosphorylation activity
#axarr[0].plot(LTtype_cyt_1, c=(0,1.0,0))
#axarr[0].plot(Ttype_cyt_1, c=(0,0.8,0), ls='--')
#axarr[0].plot(Ltype_cyt_1, c=(0,0.6,0), ls=':')
##axarr[0].set_xlim([1e-8, 0.0000012])
##axarr[0].set_ylim([0.799, 0.804])
#axarr[0].set_ylabel('KCC2$_{C}$ (%)')
#
## Plot CaDRC for Cytoplasmic KCC2 
#axarr[1].plot(LTtype_memb_1, c=(0,0,1.0))
#axarr[1].plot(Ttype_memb_1, c=(0,0,0.8), ls='--')
#axarr[1].plot(Ltype_memb_1, c=(0,0,0.6), ls=':')
#axarr[1].set_ylim([0.136, 0.146])
#axarr[1].set_ylabel('KCC2$_{M}$ (%)')
## Plot CaDRC for Membrane Unphosphorylated KCC2
#axarr[2].plot(LTtype_membp_1, c=(1.0, 0, 0), label="L- and T-type")
#axarr[2].plot(Ttype_membp_1, c=(0.8, 0, 0), ls="--", label="T-type")
#axarr[2].plot(Ltype_membp_1, c=(0.6, 0, 0), ls=":", label="L-type")
#axarr[2].set_ylim([0.045, 0.065])
#axarr[2].set_ylabel('KCC2$_{M_{P}}$ (%)')
## Plot CaDRC for Membrane Phosphorylated KCC2
#axarr[3].plot(LTtype_volt_1, c=(0,0,0))
#axarr[3].set_ylim([-90, 20])
#axarr[3].set_ylabel('Voltage (mV)')
#plt.legend(loc=0)
#f.text(0.5, 0.03, '$t$ (ms)', ha='center')
#
#
#################################################
## save graphs
##save("../../Thesis/fig/KCC2voltage_trace_1", ext="png", close=True, verbose=True)
#plt.show()