:------------------------------------------------------------------------------
TITLE Model of KCC2 regulation
:------------------------------------------------------------------------------

NEURON {
  SUFFIX KCC2
  :USEION ca READ ica, cao WRITE cai
  USEION ca READ cai
  USEION mkcc2 WRITE mkcc2i VALENCE 1
  RANGE A_M, B_M
  RANGE R_M, R_MP
  RANGE R_K, R_P, V_K, V_P, H_K, H_P, B_K, B_P
  RANGE kin_active, kin_inactive, cyt, memb, membp, v_K, v_P
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
  A_M  = 0.2533 (/s)    < 0, 1e9 >    : rate of transfer from cytosolic to membrane-bound KCC2
  B_M  = 1.4776 (/s)    < 0, 1e9 >    : rate of transfer from membrane-bound to cytosolic KCC2
  R_M  = 1 		(/s)    < 0, 1e9 >    : KCC2 phosphorylation coefficient
  R_MP = 0.0646	(/s)    < 0, 1e9 >    : KCC2 dephosphorylation coefficient
  R_K  = 2.37e-3 (mM)   < 0, 1e9 >    : concent. of Ca2+ at which kinase activation rate is half max
  R_P  = 7.943e-4 (mM)  < 0, 1e9 >    : concent. of Ca2+ at which phosphotase activation rate is half max
  V_K  = 390  	(/s)    < 0, 1e9 >    : maximum rate of kinase activation
  V_P  = 48.925 (/s)    < 0, 1e9 >    : maximum rate of phosphotase activation
  H_K  = 1.5 	(1)     < 0, 1e9 >    : Hill coefficient for kinase activation equation
  H_P  = 2.9  	(1)     < 0, 1e9 >    : Hill coefficient for phosphotase activation equation
  B_K  = 32.1  	(/s)    < 0, 1e9 >    : rate of kinase inactivation
  B_P  = 10  	(/s)    < 0, 1e9 >    : rate of phosphotase inactivation
  gcal = 7e-3 (mho/cm2) 
}

ASSIGNED {
	v       (mV)	: membrane voltage
	diam 	(um)    : compartment diameter
 	mkcc2i 	(mM) 	: concentration of membrane-bound KCC2
 	cai    (mM) 	: calcium concentration
 	ica    	(mA/cm2): calcium concentration
  	v_K    	(/s) 	: rate of kinase activation
  	v_P    	(/s) 	: rate of phosphotase activation
	celsius (degC)  : temperature
	cao 	(mM)	: extracellular calcium concentration
}

STATE {
	kin_active
	kin_inactive
	phos_active
	phos_inactive
	cyt
	memb
	membp
}

INITIAL {
	kin_active    = 0.1050423664
	kin_inactive  = 0.8949576336
	phos_active   = 0.0222547827
	phos_inactive = 0.9777452173
	cyt           = 0.8000684487
	memb          = 0.1371530442
	membp         = 0.0627785071
}

BREAKPOINT {
  SOLVE states METHOD cnexp
}

DERIVATIVE states {
	enzymes(cai)
	
	cyt'   = (1e-3)*(B_M*memb - A_M*cyt)
	memb'  = (1e-3)*(A_M*cyt - (B_M + R_MP*kin_active)*memb + R_M*phos_active*membp) 
	membp' = (1e-3)*(-R_M*phos_active*membp + R_MP*kin_active*memb) 
	kin_inactive   = 1 - kin_active 
	phos_inactive  = 1 - phos_active 
	:kin_inactive'    = (1e-3)*(-kin_inactive*v_K + B_K*kin_active) 
	:phos_inactive'   = (1e-3)*(-phos_inactive*v_P + B_P*phos_active)
	kin_active'    = (1e-3)*(kin_inactive*v_K - B_K*kin_active) 
	phos_active'   = (1e-3)*(phos_inactive*v_P - B_P*phos_active)
	
	if (memb + membp > 0) {
	  mkcc2i = (memb + membp)*1(mM)
	}
	else {
	  mkcc2i = 0
  	}
}

PROCEDURE enzymes (Caint (mM)) {
  v_K = (V_K*((Caint/1(mM))^H_K))/((R_K/1(mM))^H_K + (Caint/1(mM))^H_K)
  v_P = (V_P*((Caint/1(mM))^H_P))/((R_P/1(mM))^H_P + (Caint/1(mM))^H_P)
}

