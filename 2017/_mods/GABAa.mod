TITLE Simplified ionic model of GABA-A synapse, with saturation

:------------------------------------------------------------------------------
COMMENT
    This file models GABA-A mediated synaptic currents using chloride and 
    bicarbonate flux to determine overall current. The ionic components of the 
    model were based on the work of Staley & Proctor (1999). The kinetics of the 
    synaptic conductance is based on the simplified synapse models of 
    Destexhe et al. (1994) and Destexhe et al. (1998). The first reference is the 
    source for the ionic parameters and the other two references are the source 
    for the kinetic parameters. The model contains two major assumptions to 
    produce the simplified synaptic kinetics:
      - a presynaptic spike leads to a constant level of transmitter in the
        synaptic cleft for a fixed amount of time
      - the synapses saturate at the maximum conductance level, and further
        inputs can only maintain this level, not increase or decrease it
    Authors: Blake Richards
    
    References:
      - KJ Staley, WR Proctor (1999), J Physiol, 519: 693-712.
      - A Destexhe, ZF Mainen, TJ Sejnowski (1994), Neural Comp, 6: 14-18.
      - A Destexhe, ZF Mainen, TJ Sejnowski (1998), in Methods in NeuRonal 
          Modelling, MIT Press.
      -
ENDCOMMENT

:------------------------------------------------------------------------------
NEURON {
    POINT_PROCESS GABAa
    RANGE trans_pres, nevents, g, gmax
    USEION cl READ ecl WRITE icl VALENCE -1
    USEION hco3 READ ehco3 WRITE ihco3 VALENCE -1
    GLOBAL clprm, C, D, alpha, beta
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
    clprm   = 0.8               : chloride permeability (hco3prm is 1-clprm)
    C       = 1       (mM)      : max transmitter concentration (From Mainen & Sejnowski 1998)
    D       = 1       (ms)      : transmitter duration (rising phase) (From Mainen & Sejnowski 1998)
    alpha   = 5       (/ms mM)  : forward (binding) rate (From Mainen & Sejnowski 1998)
    beta    = 0.18    (/ms)     : backward (unbinding) rate (From Mainen & Sejnowski 1998)
    gmax    = 0.003   (uS)      : maximum synaptic conductance // from Gupta Wang & Markram 2000, see also https://bbp.epfl.ch/nmc-portal/microcircuit#/pathway/L23_LBC-L23_PC/details
}

:------------------------------------------------------------------------------
ASSIGNED {
    v       (mV)    : postsynaptic voltage
    g       (uS)    : synaptic conductance
    rinf            : steady state channels open
    rtau    (ms)    : time constant of channel binding
    rdelta          : decay term for release vars
    trans_pres      : indicates whether transmitter is present (1 = yes, 0 = no)
    nevents         : counts the number of transmitter events
    icl     (nA)    : chloride current
    ecl     (mV)    : chloride reversal
    ihco3   (nA)    : bicarbonate current
    ehco3   (mV)    : bicarbonate reversal
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
    icl   = g * clprm * (v - ecl)
    ihco3 = g * (1 - clprm) * (v - ehco3) 
}

:------------------------------------------------------------------------------
DERIVATIVE release {
    ron'  = (trans_pres*rinf - ron)/rtau
    roff' = -beta*roff
}

:------------------------------------------------------------------------------
NET_RECEIVE (w) { : the NetCon weight is ignored in this model
    if(flag == 0) { : spike event, increment events counter
        nevents = nevents + 1
        if (trans_pres == 0) {                              : this is a new event, turn conductance to on mode
            ron = roff
            roff = 0
        }
        trans_pres = 1
        net_send(D, 1)                                      : send a signal D later to turn to off mode
    } 
    else {                                                  : received an off signal, decrement the events counter
        nevents = nevents - 1
        if (nevents == 0) {                                 : no remaining events, turn conductance to off mode
            trans_pres = 0
            ron = 0
            roff = rdelta
        }
    }
}
