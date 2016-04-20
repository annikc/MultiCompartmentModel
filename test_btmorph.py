import btmorph
import numpy
import matplotlib.pyplot as plt
import morphometricdata

cell_1 = geomReader("./CA1geometry.dat")
morpho = cell_1.data_vec

swc_tree= btmorph.STree2()
swc_tree.read_SWC_tree_from_file("./n123.swc")

stats = btmorph.BTStats(swc_tree)

# get the total length
total_length = stats.total_length()
print "total_length = %f" % total_length

# get the max degree, i.e., degree of the soma
max_degree = stats.degree_of_node(swc_tree.get_root())

# generate and save the dendrogram
btmorph.plot_2D_SWC("./n123.swc",show_axis=False,color_scheme='default',depth='Y')
plt.show()
#plt.savefig('examplar_dendrogram.pdf')