Use coarse_script_gen.sh to run simulations with delta_t in {-50, -25, -15, -10, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 10, 15, 25, 50} 

Use fine_script_gen.sh to run simulations with delta_t increments of 0.1 ms from -5 ms to 5 ms

Anything containing "template" (i.e. run_<section>_template.hoc,
template_mosinit.hoc, template_runscript.sh) is called by the *_script_gen.sh
to generate the appropriate files and submit jobs to the queue. 

README last updated: March 24, 2016
