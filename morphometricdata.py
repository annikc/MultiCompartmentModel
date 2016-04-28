import struct
import numpy as np
import matplotlib.pyplot as plt
import os
import pdb

################################################
# geomReader object declaration
class geomReader:

	def __init__(self, filename):

		# open the file for reading
		self.file = open(filename, 'rb')

		# Main header variables
		num_items = self.read_header()

		#read in morphometric data from each section
		self.data_vec = self.morpho_data(num_items)

		# close the file
		self.file.close()


	def read_header(self):
		self.file.seek(8,0)
		self.num_somatic = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of Sections in SectionList 'Somatic' ", self.num_somatic
		self.num_proximal = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of Sections in SectionList 'Proximal' ", self.num_proximal
		self.num_middle = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of Sections in SectionList 'Middle' ", self.num_middle
		self.num_distal = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of Sections in SectionList 'Distal' ", self.num_distal
		num_items = int(struct.unpack('d', self.file.read(8))[0])
		#print "Number of Items in Geometry Output ", num_items

		return num_items


	def morpho_data(self, num_items):
		self.file.seek(8,1)
		
		entries = (num_items)/8
		#print "number of entries", entries
		data_array = np.zeros((entries, 8))

		for i in range(entries):
			for j in range(8):
				data_value = struct.unpack('d', self.file.read(8))[0]
				data_array[i, j] = data_value
			#print data_array[i, :]

		'''
		NEED TO FIX geometry to have only necessary info -- no NEURON indices
		'''
		geometry = np.delete(data_array, 2, axis=1)
		section_connection = np.delete(data_array, [3,4,5,6], axis=1 )
		
		#print section_connection[0:100, :]
		#print geometry[0:10, :]

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

#cell_1 = geomReader("./CA1geometry.dat")



## cell_1.data_vec is the geometry information needed for input for btmorph 