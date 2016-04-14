import struct
import numpy as np
import matplotlib.pyplot as plt
import os
import pdb

################################################
# object declaration: Variable 
class variableList:
	def __init__(self, num_variables):
		self.var_num = num_variables
		self.varList = list()

	def add(self, variable):
		if len(self.varList) >  self.var_num:
			print('trying to add too many sections to a list!')
		else:
			self.varList.append(variable)


################################################
# variable object declaration
class sectionList:

	def __init__(self, name_section, num_sections):
		self.sec_name = name_section
		self.sec_num = num_sections
		self.secList = list()

	def add(self, section):
		if len(self.secList) >  self.sec_num:
			print('trying to add too many sections to a list!')
		else:
			self.secList.append(section)


################################################
# variable object declaration
class dataVector:

	def __init__(self, num_samp):
		self.data = np.zeros(num_samp)

	def add(self, data, count):
		self.data[count] = self.data[0]


################################################
# nrnReader object declaration
class nrnReader:

	def __init__(self, filename):

		# open the file for reading
		self.file = open(filename, 'rb')

		# Main header variables
		self.read_main_header()

		# create VariableList
		self.var_list = variableList(self.num_variables)

		# step through each section list, and store its info in the dictionary SLdict
		for i in range(self.num_variables):
			if i == 0:
				name_variable = 'ECl'
			if i == 1:
				name_variable = 'MP KCC2'
			if i == 2: 
				name_variable = 'Ca2+'
			if i == 3:
				name_variable = 'kinase'
			if i == 4: 
				name_variable = 'phosphatase'

			(num_bytes, val_type) = self.read_segment_subheader()
			sec_list = sectionList(name_variable, self.num_sections)

			for j in range(self.num_sections):
				if j == 0:
					num_samp = self.soma_count
				if j == 1: 
					num_samp = self.prox_count
				if j == 2:
					num_samp = self.midd_count
				if j == 3:
					num_samp = self.dist_count
				
				data_vec = self.variable_data(num_samp, num_bytes, val_type)

				# add data vector to section list
				sec_list.add(data_vec)

			# add section list to variable list
			self.var_list.add(sec_list)

		# close the file
		self.file.close()


	def read_main_header(self):
		self.file.seek(8,0)
		self.num_sections = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of Sectionlists ", self.num_sections
		self.num_variables = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of recorded variables ", self.num_variables
		self.dt = 0.5 # this is hardcoded, should be removed later!
		self.timesteps = int(struct.unpack('d', self.file.read(8))[0])
		#print self.timesteps

		self.soma_count = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of sections in sectionlist soma", self.soma_count
		self.prox_count = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of sections in sectionlist prox", self.prox_count
		self.midd_count = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of sections in sectionlist midd", self.midd_count
		self.dist_count = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of sections in sectionlist dist", self.dist_count

	def read_segment_subheader(self):   # N adds num_samp and precision before every instantiation of a vector ***
		samp = struct.unpack('i', self.file.read(4))[0]
		precision = struct.unpack('i', self.file.read(4))[0]
		
		# Set the right number of bytes per data point
		if precision == 1:
			num_bytes = 1
			val_type = 'c'
		elif precision == 2:
			num_bytes = 2
			val_type = 'h'
		elif precision == 3:
			num_bytes = 4
			val_type = 'f'
		elif precision == 4:
			num_bytes = 8
			val_type = 'd'
		
		else: 
			print "SAMPLE OR PRECISION ERROR"


		return (num_bytes, val_type)

	def variable_data(self, num_samp, num_bytes, val_type):
		data_array = np.zeros((num_samp, 1))

		for i in range(num_samp):
			data_value = struct.unpack(val_type, self.file.read(num_bytes))[0]
			data_array[i, 0] = data_value
		return data_array


def save(path, ext='png', close=True, verbose=True):
    """Save a figure from pyplot.
    Parameters
    ----------
    path : string
        The path (and filename, without the extension) to save the
        figure to.
    ext : string (default='png')
        The file extension. This must be supported by the active
        matplotlib backend (see matplotlib.backends module).  Most
        backends support 'png', 'pdf', 'ps', 'eps', and 'svg'.
    close : boolean (default=True)
        Whether to close the figure after saving.  If you want to save
        the figure multiple times (e.g., to multiple formats), you
        should NOT close it in between saves or you will have to
        re-plot it.
    verbose : boolean (default=True)
        Whether to print information about when and where the image
        has been saved.
    """
    
    # Extract the directory and filename from the given path
    directory = os.path.split(path)[0]
    filename = "%s.%s" % (os.path.split(path)[1], ext)
    if directory == '':
        directory = '.'
 
    # If the directory does not exist, create it
    if not os.path.exists(directory):
        os.makedirs(directory)
 
    # The final path to save to
    savepath = os.path.join(directory, filename)
 
    if verbose:
        print("Saving figure to '%s'..." % savepath),
 
    # Actually save the figure
    plt.savefig(savepath)
    
    # Close it
    if close:
        plt.close()
 
    if verbose:
        print("Done")

soma_pos1 = nrnReader("../../../../../msc/SciNet/data/coarseExpts/soma_1.dat")

print soma_pos1.var_list.varList[1].secList[0]

