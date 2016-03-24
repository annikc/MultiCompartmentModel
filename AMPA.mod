TITLE Simplified ionic model of AMPA synapse, with saturation

:------------------------------------------------------------------------------
COMMENT
	This file models AMPA mediated synaptic currents using ohmic laws.
	The kinetics of the synaptic conductance is based on the simplified synapse 
	models of Destexhe et al. (1994) and Destexhe et al. (1998). The model 
	contains two major assumptions to produce the simplified synaptic kinetics:
		- a presynaptic spike leads to a constant level of transmitter in the
		  synaptic cleft for a fixed amount of time
		- the synapses saturate at the maximum conductance level, and further
		  inputs can only maintain this level, not increase or decrease it
	Authors: Blake Richards
	
	References:
		- A Destexhe, ZF Mainen, TJ Sejnowski (1994), Neural Comp, 6: 14-18.
		- A Destexhe, ZF Mainen, TJ Sejnowski (1998), in Methods in NeuRonal 
		    Modelling, MIT Press.
		-
ENDCOMMENT

:------------------------------------------------------------------------------
NEURON {
	POINT_PROCESS AMPA
	RANGE trans_pres, nevents, g, gmax
	GLOBAL C, D, alpha, beta, erev
	NONSPECIFIC_CURRENT i
}

:------------------------------------------------------------------------------
UNITS {
	(nA) = (nanoamp)
	(mV) = (millivolt)
	(uS) = (microsiemens)
	(M)  = (1/liter)
	(mM) = (milliM)
}

:------------------------------------------------------------------------------
PARAMETER {
	C       = 1       (mM)      : max transmitter concentration
	D       = 1       (ms)      : transmitter duration (rising phase)
	alpha   = 1.1     (/ms mM)  : forward (binding) rate
	beta    = 0.19    (/ms)     : backward (unbinding) rate
	gmax    = 0.001   (uS)      : maximum synaptic conductance
	erev    = 0       (mV)      : reversal potential
}

:------------------------------------------------------------------------------
ASSIGNED {
	v       (mV)    : postsynaptic voltage
	g       (uS)    : synaptic conductance
	i       (nA)    : synaptic current
	rinf            : steady state channels open
	rtau    (ms)    : time constant of channel binding
	rdelta          : decay term for release vars
	trans_pres      : indicates whether transmitter is present (1 = yes, 0 = no)
	nevents         : counts the number of transmitter events
}

:------------------------------------------------------------------------------
STATE { ron roff }

:------------------------------------------------------------------------------
INITIAL {
	ron = 0
	roff = 0
	rinf = C*alpha / (C*alpha + beta)
	rtau = 1 / ((alpha * C) + beta)
	rdelta = rinf*(1 - exp(-D/rtau))
	trans_pres = 0
	nevents = 0
}

:------------------------------------------------------------------------------
BREAKPOINT {
	SOLVE release METHOD cnexp
	g     = gmax * (ron + roff)
	i     = g * (v - erev)
}

:------------------------------------------------------------------------------
DERIVATIVE release {
	ron'  = (trans_pres*rinf - ron)/rtau
	roff' = -beta*roff
}

:------------------------------------------------------------------------------
NET_RECEIVE (w) { : the NetCon weight is ignored in this model
	if(flag == 0) { 										: spike event, increment events counter
		nevents = nevents + 1
		if (trans_pres == 0) { 								: this is a new event, turn conductance to on mode
			ron = roff
			roff = 0
		}
		trans_pres = 1
		net_send(D, 1) 										: send a signal D later to turn to off mode
	}
	else { 													: received an off signal, decrement the events counter
		nevents = nevents - 1
		if (nevents == 0) { 								: no remaining events, turn conductance to off mode
			trans_pres = 0
			ron = 0
			roff = rdelta
		}
	}
}
