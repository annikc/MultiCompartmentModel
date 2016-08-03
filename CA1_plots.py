import math
from readGEOMinfo import *
from readSYNinfo import *
from readNRNdata import * 
from collections import defaultdict
from numpy import mean,cov,double,cumsum,dot,linalg,array,rank
from pylab import plot,subplot,axis,stem,show,figure
import matplotlib as mpl
import matplotlib.gridspec as gridspec
import matplotlib.pyplot as plt
import matplotlib.colors as col
import matplotlib.cm as cm
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import pdb

'''
- Fix up get_data() to use define_timesteps in second block when gathering both coarse and fine data
- Fix up strings for data locations (i.e. a better way of managing lowG) -- find another place to dump data? 
- 
'''


def data_types(Ktype, Ctype):
	if Ktype == 0 and Ctype == 0:
		KCC2_type = 'vol'
		Ca_Type = 'LT' 
		ca_channel_string = "L- and T-Type Calcium Channels"
	elif Ktype == 1 and Ctype == 0:
		KCC2_type = 'SA'
		Ca_Type = 'LT' 
		ca_channel_string = "L- and T-Type Calcium Channels"
	elif Ktype == 0 and Ctype == 1:
		KCC2_type = 'vol'
		Ca_Type = 'T_only'
		ca_channel_string = "T-Type Channels Only"
	elif Ktype == 1 and Ctype == 1:
		KCC2_type = 'SA'
		Ca_Type = 'T_only'
		ca_channel_string = "T-Type Channels Only"

	return (KCC2_type, Ca_Type, ca_channel_string)

ktype_picker = 1
catype_picker = 1

KCC2_type = data_types(ktype_picker,catype_picker)[0]
print KCC2_type
Ca_Type = data_types(ktype_picker,catype_picker)[1]
ca_channel_string = data_types(ktype_picker,catype_picker)[2]
#KCC2_type = 'vol'
#Ca_Type = 'LT'
##############################################
# Read in Data
##############################################
np.set_printoptions(suppress=True)

# set up vector of dendrites in sectionlists Proximal, middle, and distal
prox_seclist = np.array([0, 1, 2, 3, 5, 6, 7, 8, 9, 29, 42, 43, 44, 45, 46, 47, 54, 56])
midd_seclist = np.array([4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 48, 49, 50, 51, 52, 53, 55, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 139, 140, 141, 142, 147, 150, 151, 154, 155, 156, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 174, 175, 176, 177, 178, 179])
dist_seclist = np.array([92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 143, 144, 145, 146, 148, 149, 152, 153, 157, 158, 173])

# set up lists for storing read data
soma_syn = []
prox_syn = []
midd_syn = []
dist_syn = []

def define_timesteps(start,end,stepsize=1):
	timesteps = np.arange(start,end,stepsize)
	if stepsize >= 1:
		res = 'coarse'
	elif 0 < stepsize < 1:
		res = 'fine'
	return (timesteps, res)

def get_data(delta_t_array):
	T_vals = []
	if delta_t_array == 0:
		starttime = -50
		endtime = 39
		timesteps = define_timesteps(starttime,endtime)[0]
		res = define_timesteps(starttime,endtime)[1]
		for j in range(len(timesteps)):
			T_vals.append(int(timesteps[j]))
		for i in range(len(timesteps)):
			if res == 'coarse':
				#soma_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/soma_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
				prox_syn.append(nrnReader("./data/Ca_{0}/lowG/coarseExpts/proximal_{1}.dat".format(Ca_Type, T_vals[i])))
				#midd_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/middle_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
				#dist_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/distal_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
			if res == 'fine':
				soma_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/soma_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[i]*10))))
				prox_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/proximal_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[i]*10))))
				midd_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/middle_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[i]*10))))
				dist_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/distal_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[i]*10))))
			
	if delta_t_array == 1:
		coarse_array1 = np.arange(-50, 5)
		for j in range(len(coarse_array1)):
			T_vals.append(int(coarse_array1[j]))
		for i in range(len(coarse_array1)):
			#soma_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/soma_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
			prox_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/proximal_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
			#midd_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/middle_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
			#dist_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/distal_{2}.dat".format(Ca_Type, KCC2_type, T_vals[i])))
		fine_array = np.arange(-5, 5.1, 0.1)
		for j in range(len(fine_array)):
			T_vals.append(round(fine_array[j],1))
		for i in range(len(fine_array)):
			#soma_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/soma_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[len(coarse_array1) + i]*10))))
			prox_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/proximal_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[len(coarse_array1) + i]*10))))
			#midd_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/middle_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[len(coarse_array1) + i]*10))))
			#dist_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/fineExpts/distal_pt_{2}.dat".format(Ca_Type, KCC2_type, int(T_vals[len(coarse_array1) + i]*10))))
		coarse_array2 = np.arange(6, 51)
		for j in range(len(coarse_array2)):
			T_vals.append(int(coarse_array2[j]))
		for i in range(len(coarse_array2)):
			#soma_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/soma_{2}.dat".format(Ca_Type, KCC2_type, T_vals[len(coarse_array1) + len(fine_array) + i])))
			prox_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/proximal_{2}.dat".format(Ca_Type, KCC2_type, T_vals[len(coarse_array1) + len(fine_array) + i])))
			#midd_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/middle_{2}.dat".format(Ca_Type, KCC2_type, T_vals[len(coarse_array1) + len(fine_array) + i])))
			#dist_syn.append(nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/distal_{2}.dat".format(Ca_Type, KCC2_type, T_vals[len(coarse_array1) + len(fine_array) + i])))

	return T_vals

T_vals = get_data(0)
#num_var = soma_syn[0].num_variables

def filter_data(syn_location, variable):
	data = {}
	if syn_location == 0: # GABA synapses inserted in soma
		for i in range(len(T_vals)):
			data[T_vals[i]] = {}

			data[T_vals[i]][999] = soma_syn[i].var_list.varList[variable].secList[0]
			for j in range(len(prox_seclist)): 
				data[T_vals[i]][prox_seclist[j]] = soma_syn[i].var_list.varList[variable].secList[1][j]

			for j in range(len(midd_seclist)): 
				data[T_vals[i]][midd_seclist[j]] = soma_syn[i].var_list.varList[variable].secList[2][j]

			for j in range(len(dist_seclist)): 
				data[T_vals[i]][dist_seclist[j]] = soma_syn[i].var_list.varList[variable].secList[3][j]

	if syn_location == 1: # GABA synapses inserted in proximal dendrites
		for i in range(len(T_vals)):
			data[T_vals[i]] = {}

			data[T_vals[i]][999] = prox_syn[i].var_list.varList[variable].secList[0]
			for j in range(len(prox_seclist)): 
				data[T_vals[i]][prox_seclist[j]] = prox_syn[i].var_list.varList[variable].secList[1][j]

			for j in range(len(midd_seclist)): 
				data[T_vals[i]][midd_seclist[j]] = prox_syn[i].var_list.varList[variable].secList[2][j]

			for j in range(len(dist_seclist)): 
				data[T_vals[i]][dist_seclist[j]] = prox_syn[i].var_list.varList[variable].secList[3][j]

	if syn_location == 2: # GABA synapses inserted in middle dendrites
		for i in range(len(T_vals)):
			data[T_vals[i]] = {}

			data[T_vals[i]][999] = midd_syn[i].var_list.varList[variable].secList[0]
			for j in range(len(prox_seclist)): 
				data[T_vals[i]][prox_seclist[j]] = midd_syn[i].var_list.varList[variable].secList[1][j]

			for j in range(len(midd_seclist)): 
				data[T_vals[i]][midd_seclist[j]] = midd_syn[i].var_list.varList[variable].secList[2][j]

			for j in range(len(dist_seclist)): 
				data[T_vals[i]][dist_seclist[j]] = midd_syn[i].var_list.varList[variable].secList[3][j]

	if syn_location == 3: # GABA synapses inserted in distal dendrites 
		for i in range(len(T_vals)):
			data[T_vals[i]] = {}

			data[T_vals[i]][999] = dist_syn[i].var_list.varList[variable].secList[0]
			for j in range(len(prox_seclist)): 
				data[T_vals[i]][prox_seclist[j]] = dist_syn[i].var_list.varList[variable].secList[1][j]

			for j in range(len(midd_seclist)): 
				data[T_vals[i]][midd_seclist[j]] = dist_syn[i].var_list.varList[variable].secList[2][j]

			for j in range(len(dist_seclist)): 
				data[T_vals[i]][dist_seclist[j]] = dist_syn[i].var_list.varList[variable].secList[3][j]

	return data


def plot_CA1(syn_location, variable, time):
	if syn_location == 0: 
		loc_string = 'somatic'
	elif syn_location == 1:
		loc_string = 'proximal'
	elif syn_location == 2: 
		loc_string = 'middle'
	elif syn_location == 3: 
		loc_string = 'distal'
	else: 
		print "Synaptic Location Error"

	data = filter_data(syn_location, variable)
	max_vals = []
	min_vals = []
	for i in range(len(T_vals)):
		max_vals.append(max(data[T_vals[i]][999]))
		min_vals.append(min(data[T_vals[i]][999]))	
	for i in range(len(T_vals)):
		for j in range(180): 
			max_vals.append(max(data[T_vals[i]][j]))
			min_vals.append(min(data[T_vals[i]][j]))
	norm_min = min(min_vals)
	norm_max = max(max_vals)

	#Get info to draw cell geometry
	cell_1 = geomReader("./CA1geometry.dat")
	morpho = cell_1.data_vec
	items = len(morpho[0,:])
	entries = len(morpho[:,0])


	indicies = []
	indicies.append(int(999))
	for i in range(180):
		indicies.append(int(i))


	sections_list = {}
	for i in range(181):
		segments = list()
		for j in range(entries):
			py_ind = morpho[j, 1]
			if py_ind == i:
				(x,y,z,r,N_ind) = (morpho[j,3], morpho[j,4], morpho[j,5], morpho[j,6],int(morpho[j,2]))
				segments.append((x,y,z,r,N_ind))
		sections_list[i] = segments


	CA1 = {}
	for i in range(len(sections_list)):
		sec_info = []
		x_vals = []
		y_vals = []
		z_vals = []
		r_vals = []
		for j in range(len(sections_list[i])):
			x_vals.append(sections_list[i][j][0])
			y_vals.append(sections_list[i][j][1])
			z_vals.append(sections_list[i][j][2])
			r_vals.append(sections_list[i][j][3])
		sec_info.append(x_vals)
		sec_info.append(y_vals)
		sec_info.append(z_vals)
		sec_info.append(r_vals)
		CA1[sections_list[i][0][4]] = sec_info

	# Define connections between sections
	parent_child = []
	parent_child.append((0,0,999,0.5))
	parent_child.append((1,0,0,1))
	parent_child.append((2,0,1,1))
	parent_child.append((3,0,2,1))
	parent_child.append((4,0,3,1))
	parent_child.append((5,0,3,1))
	parent_child.append((6,0,5,1))
	parent_child.append((7,0,5,1))
	parent_child.append((8,0,2,1))
	parent_child.append((9,0,8,1))
	parent_child.append((10,0,9,1))
	parent_child.append((11,0,10,1))
	parent_child.append((12,0,11,1))
	parent_child.append((13,0,11,1))
	parent_child.append((14,0,10,1))
	parent_child.append((15,0,14,1))
	parent_child.append((16,0,15,1))
	parent_child.append((17,0,15,1))
	parent_child.append((18,0,17,1))
	parent_child.append((19,0,17,1))
	parent_child.append((20,0,19,1))
	parent_child.append((21,0,19,1))
	parent_child.append((22,0,21,1))
	parent_child.append((23,0,21,1))
	parent_child.append((24,0,14,1))
	parent_child.append((25,0,24,1))
	parent_child.append((26,0,25,1))
	parent_child.append((27,0,25,1))
	parent_child.append((28,0,24,1))
	parent_child.append((29,0,9,1))
	parent_child.append((30,0,29,1))
	parent_child.append((31,0,30,1))
	parent_child.append((32,0,30,1))
	parent_child.append((33,0,32,1))
	parent_child.append((34,0,32,1))
	parent_child.append((35,0,29,1))
	parent_child.append((36,0,35,1))
	parent_child.append((37,0,35,1))
	parent_child.append((38,0,37,1))
	parent_child.append((39,0,38,1))
	parent_child.append((40,0,38,1))
	parent_child.append((41,0,37,1))
	parent_child.append((42,0,8,1))
	parent_child.append((43,0,1,1))
	parent_child.append((44,0,0,1))
	parent_child.append((45,0,44,1))
	parent_child.append((46,0,44,1))
	parent_child.append((47,0,46,1))
	parent_child.append((48,0,47,1))
	parent_child.append((49,0,48,1))
	parent_child.append((50,0,48,1))
	parent_child.append((51,0,47,1))
	parent_child.append((52,0,51,1))
	parent_child.append((53,0,51,1))
	parent_child.append((54,0,46,1))
	parent_child.append((55,0,54,1))
	parent_child.append((56,0,54,1))
	parent_child.append((57,0,56,1))
	parent_child.append((58,0,56,1))
	parent_child.append((59,0,58,1))
	parent_child.append((60,0,58,1))
	parent_child.append((61,0,999,0.5))
	parent_child.append((62,0,61,1))
	parent_child.append((63,0,62,1))
	parent_child.append((64,0,63,1))
	parent_child.append((65,0,64,1))
	parent_child.append((66,0,65,1))
	parent_child.append((67,0,65,1))
	parent_child.append((68,0,64,1))
	parent_child.append((69,0,68,1))
	parent_child.append((70,0,69,1))
	parent_child.append((71,0,69,1))
	parent_child.append((72,0,68,1))
	parent_child.append((73,0,72,1))
	parent_child.append((74,0,73,1))
	parent_child.append((75,0,73,1))
	parent_child.append((76,0,75,1))
	parent_child.append((77,0,76,1))
	parent_child.append((78,0,77,1))
	parent_child.append((79,0,77,1))
	parent_child.append((80,0,76,1))
	parent_child.append((81,0,80,1))
	parent_child.append((82,0,80,1))
	parent_child.append((83,0,82,1))
	parent_child.append((84,0,83,1))
	parent_child.append((85,0,83,1))
	parent_child.append((86,0,85,1))
	parent_child.append((87,0,86,1))
	parent_child.append((88,0,87,1))
	parent_child.append((89,0,88,1))
	parent_child.append((90,0,89,1))
	parent_child.append((91,0,90,1))
	parent_child.append((92,0,91,1))
	parent_child.append((93,0,92,1))
	parent_child.append((94,0,92,1))
	parent_child.append((95,0,94,1))
	parent_child.append((96,0,95,1))
	parent_child.append((97,0,96,1))
	parent_child.append((98,0,97,1))
	parent_child.append((99,0,98,1))
	parent_child.append((100,0,99,1))
	parent_child.append((101,0,100,1))
	parent_child.append((102,0,100,1))
	parent_child.append((103,0,99,1))
	parent_child.append((104,0,103,1))
	parent_child.append((105,0,104,1))
	parent_child.append((106,0,105,1))
	parent_child.append((107,0,105,1))
	parent_child.append((108,0,104,1))
	parent_child.append((109,0,103,1))
	parent_child.append((110,0,98,1))
	parent_child.append((111,0,110,1))
	parent_child.append((112,0,111,1))
	parent_child.append((113,0,111,1))
	parent_child.append((114,0,110,1))
	parent_child.append((115,0,114,1))
	parent_child.append((116,0,115,1))
	parent_child.append((117,0,115,1))
	parent_child.append((118,0,117,1))
	parent_child.append((119,0,117,1))
	parent_child.append((120,0,114,1))
	parent_child.append((121,0,97,1))
	parent_child.append((122,0,96,1))
	parent_child.append((123,0,122,1))
	parent_child.append((124,0,123,1))
	parent_child.append((125,0,123,1))
	parent_child.append((126,0,125,1))
	parent_child.append((127,0,126,1))
	parent_child.append((128,0,126,1))
	parent_child.append((129,0,125,1))
	parent_child.append((130,0,122,1))
	parent_child.append((131,0,95,1))
	parent_child.append((132,0,94,1))
	parent_child.append((133,0,132,1))
	parent_child.append((134,0,132,1))
	parent_child.append((135,0,91,1))
	parent_child.append((136,0,90,1))
	parent_child.append((137,0,89,1))
	parent_child.append((138,0,88,1))
	parent_child.append((139,0,87,1))
	parent_child.append((140,0,139,1))
	parent_child.append((141,0,139,1))
	parent_child.append((142,0,141,1))
	parent_child.append((143,0,142,1))
	parent_child.append((144,0,142,1))
	parent_child.append((145,0,141,1))
	parent_child.append((146,0,86,1))
	parent_child.append((147,0,85,1))
	parent_child.append((148,0,147,1))
	parent_child.append((149,0,147,1))
	parent_child.append((150,0,82,1))
	parent_child.append((151,0,150,1))
	parent_child.append((152,0,151,1))
	parent_child.append((153,0,151,1))
	parent_child.append((154,0,150,1))
	parent_child.append((155,0,154,1))
	parent_child.append((156,0,155,1))
	parent_child.append((157,0,156,1))
	parent_child.append((158,0,156,1))
	parent_child.append((159,0,155,1))
	parent_child.append((160,0,159,1))
	parent_child.append((161,0,159,1))
	parent_child.append((162,0,154,1))
	parent_child.append((163,0,75,1))
	parent_child.append((164,0,72,1))
	parent_child.append((165,0,164,1))
	parent_child.append((166,0,165,1))
	parent_child.append((167,0,165,1))
	parent_child.append((168,0,164,1))
	parent_child.append((169,0,63,1))
	parent_child.append((170,0,169,1))
	parent_child.append((171,0,170,1))
	parent_child.append((172,0,170,1))
	parent_child.append((173,0,172,1))
	parent_child.append((174,0,172,1))
	parent_child.append((175,0,169,1))
	parent_child.append((176,0,62,1))
	parent_child.append((177,0,61,1))
	parent_child.append((178,0,177,1))
	parent_child.append((179,0,177,1))

	# Get info to draw synapses
	synapses = synReader("./CA1{0}synapses.dat".format(loc_string))
	print len(CA1[999][0])
	section_length = {}
	synapse_length = {}
	syn_coords = []
	for i in range(len(synapses.data_vec)):
		print "section index", int(synapses.data_vec[i][0])
		print "number of segments in section", len(CA1[int(synapses.data_vec[i][0])][0])
		coord = {}
		d = []
		for j in range(len(CA1[int(synapses.data_vec[i][0])][0])-1):
			if j == 0: 
				d.append(np.sqrt((CA1[int(synapses.data_vec[i][0])][0][j+1] - CA1[int(synapses.data_vec[i][0])][0][j])**2 + (CA1[int(synapses.data_vec[i][0])][1][j+1] - CA1[int(synapses.data_vec[i][0])][1][j])**2 + (CA1[int(synapses.data_vec[i][0])][2][j+1] - CA1[int(synapses.data_vec[i][0])][2][j])**2))
				coord[j] = ([CA1[int(synapses.data_vec[i][0])][0][j],CA1[int(synapses.data_vec[i][0])][1][j],CA1[int(synapses.data_vec[i][0])][2][j]],[CA1[int(synapses.data_vec[i][0])][0][j+1],CA1[int(synapses.data_vec[i][0])][1][j+1],CA1[int(synapses.data_vec[i][0])][2][j+1]])
			else:
				d.append(d[j-1] + np.sqrt((CA1[int(synapses.data_vec[i][0])][0][j+1] - CA1[int(synapses.data_vec[i][0])][0][j])**2 + (CA1[int(synapses.data_vec[i][0])][1][j+1] - CA1[int(synapses.data_vec[i][0])][1][j])**2 + (CA1[int(synapses.data_vec[i][0])][2][j+1] - CA1[int(synapses.data_vec[i][0])][2][j])**2))
				coord[j] = ([CA1[int(synapses.data_vec[i][0])][0][j],CA1[int(synapses.data_vec[i][0])][1][j],CA1[int(synapses.data_vec[i][0])][2][j]],[CA1[int(synapses.data_vec[i][0])][0][j+1],CA1[int(synapses.data_vec[i][0])][1][j+1],CA1[int(synapses.data_vec[i][0])][2][j+1]])
		section_length[i] = d[len(d)-1]
		synapse_length[i] = section_length[i]*synapses.data_vec[i][1]
		for k in range(len(d)-1):
			if synapse_length[i] < d[k]:
				#print "Synapse length is ", synapse_length[i], " while d[k] is ", d[k], " d[k+1] is ", d[k+1]
				continue
			elif d[k] <= synapse_length[i] <= d[k+1]:
				print "Synapse somewhere in between", d[k-1], " and ", d[k]
				d_syn = synapse_length[i] - d[k]
				d_length = d[k+1] - d[k]
				del_d = d_syn/d_length
				del_x = coord[k][0][0] - coord[k][1][0]
				del_y = coord[k][0][1] - coord[k][1][1]
				del_z = coord[k][0][2] - coord[k][1][2]
				syn_coords.append((coord[k][0][0] + del_d*del_x, coord[k][0][1] + del_d*del_y, coord[k][0][2] + del_d*del_z))
			#else:
			#	print "to be continued"


	# Set Colourmap properties
	norm = col.Normalize(vmin=norm_min, vmax=norm_max)
	cmap = cm.spring
	m = cm.ScalarMappable(norm=norm, cmap=cmap)

	# Map Data onto CA1 neuron morphology using colour mapping 
	fig, ax = plt.subplots(figsize=(10,12))
	for i in range(len(indicies)):
		for j in range(len(CA1[indicies[i]][0])-1):
			x1 = CA1[indicies[i]][0][j]
			x2 = CA1[indicies[i]][0][j+1]
			y1 = CA1[indicies[i]][1][j]
			y2 = CA1[indicies[i]][1][j+1]
			if i == 0:
				colour = m.to_rgba(data[time][indicies[i]][0][0])
			else:
				colour = m.to_rgba(data[time][indicies[i]][0])
			ax.plot([x1,x2], [y1,y2], c=colour)
	
	for i in range(len(parent_child)):
		if parent_child[i][3] == 1:
			x1 = CA1[parent_child[i][0]][0][0]
			x2 = CA1[parent_child[i][2]][0][(len(CA1[parent_child[i][2]][0]))-1]
			y1 = CA1[parent_child[i][0]][1][0]
			y2 = CA1[parent_child[i][2]][1][(len(CA1[parent_child[i][2]][0]))-1]
			if i == 0:
				colour = m.to_rgba(data[time][indicies[i]][0][0])
			else:
				colour = m.to_rgba(data[time][indicies[i]][0])
			ax.plot([x1,x2], [y1,y2], c=colour)

		elif parent_child[i][3] == 0.5:
			x1 = CA1[parent_child[i][0]][0][0]
			x2 = CA1[parent_child[i][2]][0][(len(CA1[parent_child[i][2]][0])/2)-1]
			y1 = CA1[parent_child[i][0]][1][0]
			y2 = CA1[parent_child[i][2]][1][(len(CA1[parent_child[i][2]][0])/2)-1]
			if i == 0:
				colour = m.to_rgba(data[time][indicies[i]][0][0])
			else:
				colour = m.to_rgba(data[time][indicies[i]][0])
			ax.plot([x1,x2], [y1,y2], c=colour)
		else:
			print "Indexing Error"
	## Add synapse markers 
	#for i in range(len(syn_coords)):
	#	ax.plot(syn_coords[i][0], syn_coords[i][1], 'k', marker ='x')

	#Plot Features
	ax.set_title("$\Delta$t = %s ms" %time)
	ax1 = fig.add_axes([0.825, 0.175, 0.02, 0.65])
	cb1 = mpl.colorbar.ColorbarBase(ax1, cmap=cmap, norm=norm)

	if variable == 0:
		cb1.set_label('$\Delta E_{Cl^{-}}$ (mV)')
		var_string = 'ECl'
	elif variable == 1:
		cb1.set_label('$\Delta$ KCC2$_{MP}')
		var_string = 'MP'
	elif variable == 2: 
		cb1.set_label('Average $Ca^{2+}$ (mM)')
		var_string = 'Ca2+'
	elif variable == 3: 
		cb1.set_label('Proportion of Active Kinase (%)')
		var_string = 'kin'
	elif variable == 4:
		cb1.set_label('Proportion of Active Phosphatase')
		var_string = 'phos'
	else: 
		print "Variable Error"

	#for i in range(2):
	#	if i == 0:
	#		file_type = 'png'
	#	elif i == 1: 
	#		file_type = 'svg'
	#	else:
	#		print "File Type Error"
	#save('./data/Ca_{0}/KCC2_{1}/PythonPlots/{2}/{2}_{3}_{4}'.format(Ca_Type, KCC2_type, var_string, loc_string, time), ext='svg')
	plt.show()


def plot_STDP(syn_location, variable, timescale):
	soma_points = np.zeros(len(timescale))
	prox_points = np.zeros(len(timescale))
	midd_points = np.zeros(len(timescale))
	dist_points = np.zeros(len(timescale))

	if syn_location == 0: # GABA synapses inserted in soma
		for i in range(len(timescale)):
			soma_points[i] = soma_syn[i].var_list.varList[variable].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + soma_syn[i].var_list.varList[variable].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + soma_syn[i].var_list.varList[variable].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + soma_syn[i].var_list.varList[variable].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)


	if syn_location == 1: # GABA synapses inserted in proximal dendrites
		for i in range(len(timescale)):
			soma_points[i] = prox_syn[i].var_list.varList[variable].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + prox_syn[i].var_list.varList[variable].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + prox_syn[i].var_list.varList[variable].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + prox_syn[i].var_list.varList[variable].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)

	if syn_location == 2: # GABA synapses inserted in middle dendrites
		for i in range(len(timescale)):
			soma_points[i] = midd_syn[i].var_list.varList[variable].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + midd_syn[i].var_list.varList[variable].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + midd_syn[i].var_list.varList[variable].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + midd_syn[i].var_list.varList[variable].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)

	if syn_location == 3: # GABA synapses inserted in distal dendrites 
		for i in range(len(timescale)):
			soma_points[i] = dist_syn[i].var_list.varList[variable].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + dist_syn[i].var_list.varList[variable].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + dist_syn[i].var_list.varList[variable].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + dist_syn[i].var_list.varList[variable].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)

	#Plot Features
	fig, ax = plt.subplots(figsize=(12,8))
	
	soma_plot = ax.plot(timescale, soma_points, label='Soma', color='red', marker='.')
	prox_plot = ax.plot(timescale, prox_points, label='Proximal Dendrites', color='orange', marker='.')
	midd_plot = ax.plot(timescale, midd_points, label='Middle Dendrites', color='green', marker ='.')
	dist_plot = ax.plot(timescale, dist_points, label='Distal Dendrites', color='blue', marker='.')

	if syn_location == 0: 
		loc_string = 'Soma'
	elif syn_location == 1:
		loc_string = 'Proximal Dendrites'
	elif syn_location == 2: 
		loc_string = 'Middle Dendrites'
	elif syn_location == 3: 
		loc_string = 'Distal Dendrites'
	else: 
		print "Synaptic Location Error"

	if variable == 0:
		ax.set_xlim(min(T_vals), max(T_vals))
		ax.set_ylim(-0.5,2.5)
		ax.set_xlabel('$\Delta t$ (ms)')
		ax.set_ylabel('Average $\Delta E_{Cl^{-}}$ (mV)')
		fig.suptitle('GABAergic Synapses in {0}'.format(loc_string), fontsize=14)
		var_string = 'ECl'
	elif variable == 1:
		ax.set_xlim(min(T_vals), max(T_vals))
		ax.set_ylim(-3.0, 0.5)
		ax.set_xlabel('$\Delta t$ (ms)')
		ax.set_ylabel('Average $\Delta$ KCC2$_{MP}$')
		fig.suptitle('GABAergic Synapses in {0}'.format(loc_string), fontsize=14)
		var_string = 'MP'
	elif variable == 2: 
		ax.set_xlim(min(T_vals), max(T_vals))
		ax.set_ylim(0.00, 0.12)
		ax.set_xlabel('$\Delta t$ (ms)')
		ax.set_ylabel('Average $Ca^{2+}$ (mM)')
		fig.suptitle('GABAergic Synapses in {0}'.format(loc_string), fontsize=14)
		var_string = 'Ca2+'
	elif variable == 3:
		ax.set_xlim(min(T_vals), max(T_vals))
		#ax.set_ylim() 
		ax.set_xlabel('$\Delta t$ (ms)')
		ax.set_ylabel('Proportion of Active Kinase (%)')
		fig.suptitle('GABAergic Synapses in {0}'.format(loc_string), fontsize=14)
		var_string = 'kin'
	elif variable == 4:
		ax.set_xlim(min(T_vals), max(T_vals))
		#ax.set_ylim()
		ax.set_xlabel('$\Delta t$ (ms)')
		ax.set_ylabel('Average Peak Voltage Reached During Plasticity Induction (mV)')
		fig.suptitle('GABAergic Synapses in {0}'.format(loc_string), fontsize=14)
		var_string = 'volt'
	else: 
		print "Variable Error"

	ax.legend(loc=0)
	for i in range(2):
		if i == 0:
			file_type = 'png'
		elif i == 1: 
			file_type = 'svg'
		else:
			print "File Type Error"
		#save('./data/Ca_{0}/KCC2_{1}/PythonPlots/STDPcurves/{2}_{3}'.format(Ca_Type, KCC2_type, var_string, syn_location), ext=file_type)
	plt.show()
	
def plot_bar_ECL(syn_location):
	if syn_location == 0: 
		loc_string = 'Soma'
	elif syn_location == 1:
		loc_string = 'Proximal Dendrites'
	elif syn_location == 2: 
		loc_string = 'Middle Dendrites'
	elif syn_location == 3: 
		loc_string = 'Distal Dendrites'
	else: 
		print "Synaptic Location Error"

	soma_points = np.zeros(len(T_vals))
	prox_points = np.zeros(len(T_vals))
	midd_points = np.zeros(len(T_vals))
	dist_points = np.zeros(len(T_vals))

	if syn_location == 0: # GABA synapses inserted in soma
		for i in range(len(T_vals)):
			soma_points[i] = soma_syn[i].var_list.varList[0].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + soma_syn[i].var_list.varList[0].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + soma_syn[i].var_list.varList[0].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + soma_syn[i].var_list.varList[0].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)
		

	if syn_location == 1: # GABA synapses inserted in proximal dendrites
		for i in range(len(T_vals)):
			soma_points[i] = prox_syn[i].var_list.varList[0].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + prox_syn[i].var_list.varList[0].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + prox_syn[i].var_list.varList[0].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + prox_syn[i].var_list.varList[0].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)
		pre_only_data = nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/proximal_preonly.dat".format(Ca_Type, KCC2_type))
		pre_only_soma = pre_only_data.var_list.varList[0].secList[0]
		pre_prox_avg = 0
		for j in range(len(prox_seclist)): 
			pre_prox_avg = pre_prox_avg + pre_only_data.var_list.varList[0].secList[1][j]
		pre_prox_point = pre_prox_avg/len(prox_seclist)
		
		pre_midd_avg = 0
		for j in range(len(midd_seclist)): 
			pre_midd_avg = pre_midd_avg + pre_only_data.var_list.varList[0].secList[2][j]
		pre_midd_point = pre_midd_avg/len(midd_seclist)
		
		pre_dist_avg = 0
		for j in range(len(dist_seclist)): 
			pre_dist_avg = pre_dist_avg + pre_only_data.var_list.varList[0].secList[3][j]
		pre_dist_point = pre_dist_avg/len(dist_seclist)

			
		post_only_data = nrnReader("./data/Ca_{0}/KCC2_{1}/coarseExpts/postonly.dat".format(Ca_Type, KCC2_type))
		post_only_soma = post_only_data.var_list.varList[0].secList[0]
		print "post only soma", post_only_soma
		post_prox_avg = 0
		for j in range(len(prox_seclist)): 
			post_prox_avg = post_prox_avg + post_only_data.var_list.varList[0].secList[1][j]
		post_prox_point = post_prox_avg/len(prox_seclist)
		
		post_midd_avg = 0
		for j in range(len(midd_seclist)): 
			post_midd_avg = post_midd_avg + post_only_data.var_list.varList[0].secList[2][j]
		post_midd_point = post_midd_avg/len(midd_seclist)
		
		post_dist_avg = 0
		for j in range(len(dist_seclist)): 
			post_dist_avg = post_dist_avg + post_only_data.var_list.varList[0].secList[3][j]
		post_dist_point = post_dist_avg/len(dist_seclist)

	if syn_location == 2: # GABA synapses inserted in middle dendrites
		for i in range(len(T_vals)):
			soma_points[i] = midd_syn[i].var_list.varList[0].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + midd_syn[i].var_list.varList[0].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + midd_syn[i].var_list.varList[0].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + midd_syn[i].var_list.varList[0].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)

	if syn_location == 3: # GABA synapses inserted in distal dendrites 
		for i in range(len(T_vals)):
			soma_points[i] = dist_syn[i].var_list.varList[0].secList[0]

			prox_avg = 0
			for j in range(len(prox_seclist)): 
				prox_avg = prox_avg + dist_syn[i].var_list.varList[0].secList[1][j]
			prox_points[i] = prox_avg/len(prox_seclist)

			midd_avg = 0
			for j in range(len(midd_seclist)): 
				midd_avg = midd_avg + dist_syn[i].var_list.varList[0].secList[2][j]
			midd_points[i] = midd_avg/len(midd_seclist)

			dist_avg = 0
			for j in range(len(dist_seclist)): 
				dist_avg = dist_avg + dist_syn[i].var_list.varList[0].secList[3][j]
			dist_points[i] = dist_avg/len(dist_seclist)
	
	coincident = {}
	noncoincident = {}
	coincident['soma'] = []
	coincident['prox'] = []
	coincident['midd'] = []
	coincident['dist'] = []
	noncoincident['soma'] = []
	noncoincident['prox'] = []
	noncoincident['midd'] = []
	noncoincident['dist'] = []
	for i in range(len(T_vals)):
		if T_vals[i] <= -50:
			noncoincident['soma'].append(soma_points[i])
			noncoincident['prox'].append(prox_points[i])
			noncoincident['midd'].append(midd_points[i])
			noncoincident['dist'].append(dist_points[i])
		if -20 <= T_vals[i] <= 20:
			coincident['soma'].append(soma_points[i])
			coincident['prox'].append(prox_points[i])
			coincident['midd'].append(midd_points[i])
			coincident['dist'].append(dist_points[i])
		elif T_vals[i] >= 50:
			noncoincident['soma'].append(soma_points[i])
			noncoincident['prox'].append(prox_points[i])
			noncoincident['midd'].append(midd_points[i])
			noncoincident['dist'].append(dist_points[i])

	co_soma_avg = sum(coincident['soma'])/len(coincident['soma'])
	co_prox_avg = sum(coincident['prox'])/len(coincident['prox'])
	co_midd_avg = sum(coincident['midd'])/len(coincident['midd'])
	co_dist_avg = sum(coincident['dist'])/len(coincident['dist'])
	nonco_soma_avg = sum(noncoincident['soma'])/len(noncoincident['soma'])
	nonco_prox_avg = sum(noncoincident['prox'])/len(noncoincident['prox'])
	nonco_midd_avg = sum(noncoincident['midd'])/len(noncoincident['midd'])
	nonco_dist_avg = sum(noncoincident['dist'])/len(noncoincident['dist'])

	if syn_location == 1:
		pre_only = {}
		pre_only['soma'] = pre_only_soma
		pre_only['prox'] = pre_prox_point
		pre_only['midd'] = pre_midd_point
		pre_only['dist'] = pre_dist_point
		post_only = {}
		post_only['soma'] = post_only_soma
		post_only['prox'] = post_prox_point
		post_only['midd'] = post_midd_point
		post_only['dist'] = post_dist_point

	ind = np.arange(4)  # the x locations for the groups
	width = 0.25       # the width of the bars

	somatic = np.array([co_soma_avg, nonco_soma_avg, pre_only_soma, post_only_soma])
	proximal = np.array([co_prox_avg, nonco_prox_avg, pre_prox_point , post_prox_point])
	middle = np.array([co_midd_avg, nonco_midd_avg, pre_midd_point, post_midd_point])
	distal = np.array([co_dist_avg, nonco_dist_avg, pre_dist_point, post_dist_point])
	#coincident = np.array([co_soma_avg, co_prox_avg, co_midd_avg, co_dist_avg])
	#noncoincident = np.array([nonco_soma_avg, nonco_prox_avg, nonco_midd_avg, nonco_dist_avg])

	fig, ax = plt.subplots(figsize=(8,10))
	soma_plot = ax.bar(ind, somatic, width, color='red')
	prox_plot = ax.bar(ind+0.75*width, proximal, width, color='orange')
	midd_plot = ax.bar(ind+1.5*width, middle, width, color='green')
	dist_plot = ax.bar(ind+2.25*width, distal, width, color='blue')

	# add some text for labels, title and axes ticks
	fig.suptitle('GABAergic Synapses in {0} \n KCC2 Distribution by {1} \n {2}'.format(loc_string, KCC2_type, ca_channel_string), fontsize=14)
	ax.set_ylim(-0.1,2.5)
	ax.set_ylabel('Average $\Delta E_{Cl^{-}}$ (mV)')
	ax.set_xticks(ind+(2*width))
	ax.set_xticklabels( ('Coincident', 'Non-coincident', 'Presynaptic \n Activation \n Only', 'Postsynaptic \n Activation \n Only') )
	
	ax.legend( (soma_plot[0], prox_plot[0], midd_plot[0], dist_plot[0]), ('Soma', 'Proximal Dendrites', 'Middle Dendrites', 'Distal Dendrites') )
	
	# Save graph
	#for i in range(2):
	#	if i == 0:
	#		file_type = 'png'
	#	elif i == 1: 
	#		file_type = 'svg'
	#	else:
	#		print "File Type Error"
	# 	save('./data/Summary/CoNonCo/Ca_{0}_KCC2_{1}_{2}'.format(Ca_Type, KCC2_type, syn_location), ext=file_type)
	plt.show()



#for i in range(1): # run through syn_loc
#	for j in range(1): # run through variables
#		for k in range(1): #(len(T_vals)):
#			print k
#			print T_vals[k]
#			plot_CA1(2, 0, 10)

#plot_CA1(1,0,-50)

for i in range(1): # run through syn_loc
	for j in range(1): # run through variables
			plot_STDP(1, 0, T_vals)



			
#for k in range(1):
#	plot_bar_ECL(1)
#