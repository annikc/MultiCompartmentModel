TITLE Current clamp that can receive NetStim input

:------------------------------------------------------------------------------
COMMENT
  This file models a current clamp that can receive input from a NetStim
  object via a NetCon object.
ENDCOMMENT

:------------------------------------------------------------------------------
NEURON
{
	POINT_PROCESS CClamp
	RANGE pulseon, nevents, amp, dur
	NONSPECIFIC_CURRENT i
}

:------------------------------------------------------------------------------
UNITS {
	(nA) = (nanoamp)
}

:------------------------------------------------------------------------------
PARAMETER {
	amp = 1 (nA)
	dur = 10 (ms)
}

:------------------------------------------------------------------------------
ASSIGNED {
	i       (nA) : synaptic current
	pulseon      : current conductance boolean
	nevents      : number of current events
}

:------------------------------------------------------------------------------
INITIAL {
	i       = 0
	pulseon = 0
	nevents = 0
}

:------------------------------------------------------------------------------
BREAKPOINT {
	i = -amp*pulseon
}

:------------------------------------------------------------------------------
NET_RECEIVE (w) {                                         	: the NetCon weight is ignored in this model
	if(flag == 0) {                                         : spike event, increment events counter
		nevents = nevents + 1
		if (pulseon == 0) { 								: this is a new event, turn conductance to on mode
			pulseon = 1
		}
	net_send(dur, 1) 										: send a signal dur later to turn to off mode
  	} 

	else { 													: received an off signal, decrement the events counter
		nevents = nevents - 1
		if (nevents == 0) { 								: no remaining events, turn conductance to off mode
	  		pulseon = 0
		}
	}
}
