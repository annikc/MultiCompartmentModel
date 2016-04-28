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
timesteps = np.array([-50, -25, -15, -10, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 10, 15, 25, 50])

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
	soma_syn.append(nrnReader("./data/coarseExpts/soma_{0}.dat".format(timesteps[i])))
	prox_syn.append(nrnReader("./data/coarseExpts/proximal_{0}.dat".format(timesteps[i])))
	midd_syn.append(nrnReader("./data/coarseExpts/middle_{0}.dat".format(timesteps[i])))
	dist_syn.append(nrnReader("./data/coarseExpts/distal_{0}.dat".format(timesteps[i])))

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
	soma_ecl[i] = soma_syn[i].var_list.varList[0].secList[0]
	prox_ecl[i] = prox_syn[i].var_list.varList[0].secList[1][0]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3] 
	##### NOTE: secList indices 1,2,3 contain vectors with recordings from all sections ... how do we want to organize this data?
	midd_ecl[i] = midd_syn[i].var_list.varList[0].secList[2][0]
	dist_ecl[i] = dist_syn[i].var_list.varList[0].secList[3][0]

###########################################
# Membrane Phosphorylated KCC2 (proportion)
###########################################
soma_MP = np.zeros(len(timesteps))
prox_MP = np.zeros(len(timesteps))
midd_MP = np.zeros(len(timesteps))
dist_MP = np.zeros(len(timesteps))

for i in range(len(timesteps)):
	soma_MP[i] = soma_syn[i].var_list.varList[1].secList[0]
	prox_MP[i] = prox_syn[i].var_list.varList[1].secList[1]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3]
	midd_MP[i] = midd_syn[i].var_list.varList[1].secList[2]
	dist_MP[i] = dist_syn[i].var_list.varList[1].secList[3]


###########################################
# Calcium Concentration
###########################################
soma_cal = np.zeros(len(timesteps))
prox_cal = np.zeros(len(timesteps))
midd_cal = np.zeros(len(timesteps))
dist_cal = np.zeros(len(timesteps))

for i in range(len(timesteps)):
	soma_cal[i] = soma_syn[i].var_list.varList[1].secList[0]
	prox_cal[i] = prox_syn[i].var_list.varList[1].secList[1]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3]
	midd_cal[i] = midd_syn[i].var_list.varList[1].secList[2]
	dist_cal[i] = dist_syn[i].var_list.varList[1].secList[3]

###########################################
# Active Kinase (proportion)
###########################################
soma_kin = np.zeros(len(timesteps))
prox_kin = np.zeros(len(timesteps))
midd_kin = np.zeros(len(timesteps))
dist_kin = np.zeros(len(timesteps))

for i in range(len(timesteps)):
	soma_kin[i] = soma_syn[i].var_list.varList[1].secList[0]
	prox_kin[i] = prox_syn[i].var_list.varList[1].secList[1]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3]
	midd_kin[i] = midd_syn[i].var_list.varList[1].secList[2]
	dist_kin[i] = dist_syn[i].var_list.varList[1].secList[3]

###########################################
# Active Phosphatase (proportion)
###########################################
soma_phos = np.zeros(len(timesteps))
prox_phos = np.zeros(len(timesteps))
midd_phos = np.zeros(len(timesteps))
dist_phos = np.zeros(len(timesteps))

for i in range(len(timesteps)):
	soma_phos[i] = soma_syn[i].var_list.varList[1].secList[0]
	prox_phos[i] = prox_syn[i].var_list.varList[1].secList[1]  #<name of file read in>.<list of variables>[Ecl=0/KCC2=1/Ca=2/Kin=3/phos=4].<list of sections>[soma=0/prox=1/midd=2/dist=3]
	midd_phos[i] = midd_syn[i].var_list.varList[1].secList[2]
	dist_phos[i] = dist_syn[i].var_list.varList[1].secList[3]



