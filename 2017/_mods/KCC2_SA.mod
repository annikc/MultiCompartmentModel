:------------------------------------------------------------------------------
TITLE Model of KCC2 transport
:------------------------------------------------------------------------------

COMMENT
----------------------------------------------------------------------------- 
  This file models the KCC2 channel mechanism as a distributed process to
  extrude intracellular chloride to baseline levels and increase chloride 
  concentration in the presence of chloride currents.

  A tonic GABA component is included to maintain chloride levels and is
  equal but opposite to the initial extrusion rate of chloride ions.

  The internal chloride ion concentration should be explicitly set in hoc 
  after inserting KCC2 but before running using
  "cli0_KCC2 = x"
  else the default of 5 mM is used.

  With special thanks to Blake Richards and Annik Carson 

  Authors: Christopher Brian Currin, Joseph Valentino Raimondo

  References:
  - 
-----------------------------------------------------------------------------
ENDCOMMENT

NEURON {
  SUFFIX KCC2_Transport : KCC2_SA
  USEION cl READ icl, ecl, clo WRITE cli VALENCE -1
  USEION k READ ki, ko VALENCE 1
  USEION mkcc2 READ mkcc2i VALENCE 1
  RANGE axD, gtonic, itonic
  RANGE R_T, r_T
  RANGE D, v_T, V_T, transport
  RANGE efflux, Pa 
  GLOBAL celsius
}

UNITS {
    (mV) = (millivolt)
    (um) = (micron)
  (mA) = (milliamp)
  (M)  = (1/liter)
  (mM) = (milliM)
  (J)  = (joule)
  (S)  = (siemens)
  F    = (faraday) (coulombs)
  R    = (k-mole) (joule/degC)
  PI   = (pi) (1)
}

PARAMETER {
  Pa     = 9.6485e-5   (mA/mM2/cm2) :1.9297e-5 : strength of kcc2 extrusion; multiplied by 5 to account for 0.2 of KCC2 being actively extruding at rest
  axD    = 1    (um2/ms) < 0, 1e9 > : axial chloride diffusion constant
}

ASSIGNED {
  v         (mV)     : membrane voltage
  diam      (um)     : compartment diameter
  L         (um)     : compartment length
  icl       (mA/cm2) : chloride current
  ik        (mA/cm2) : potassium current
  itonic    (mA/cm2) : tonic GABA current
  clo       (mM)     : external chloride concentration
  ko        (mM)     : external potassium concentration
  ecl       (mV)     : chloride reversal potential
  celsius   (degC)   : temperature
  mkcc2i    (mM)     : concentration of membrane-bound KCC2
  D         ()     : KCC2 driving force direction
  v_T       (mM/s)   : rate of ion transport by KCC2
  gtonic    (S/cm2)
}

STATE {
  cli (mM) : internal chloride concentration
  ki  (mM) : internal potassium concentration
}

INITIAL {
  : initial value of efflux
  transport_mm(cli,clo,ki,ko,mkcc2i)

  itonic = v_T
  gtonic = itonic/(v - ecl)
  D         = 0
  v_T       = 0
}

BREAKPOINT {
  SOLVE state METHOD sparse
}

KINETIC state {
  tonicgaba(v,ecl)
  transport_mm(cli, clo, ki, ko, mkcc2i)
  
  COMPARTMENT                PI*diam*diam/4 { cli }
  LONGITUDINAL_DIFFUSION axD*PI*diam*diam/4 { cli }
  
  : synaptic chloride current - KCC2 efflux + tonic GABA current
  ~ cli << ((1e4)*icl*diam*PI/F - (1e4)*v_T*PI*diam/F + (1e4)*itonic*diam*PI/F)
}

PROCEDURE tonicgaba(Vm (mV), Em (mV)) {
  itonic = gtonic * (Vm - Em)
}

PROCEDURE transport_mm(Clint (mM), Clout (mM), Kint (mM), Kout (mM), Mkcc2int (mM)) {
  v_T = Pa*(Kint*Clint-Kout*Clout)*(Mkcc2int)
}

