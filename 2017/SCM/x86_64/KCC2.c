/* Created by Language version: 6.2.0 */
/* VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 
#include "md1redef.h"
#include "section.h"
#include "md2redef.h"

#if METHOD3
extern int _method3;
#endif

#undef exp
#define exp hoc_Exp
extern double hoc_Exp();
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define A_M _p[0]
#define B_M _p[1]
#define R_M _p[2]
#define R_MP _p[3]
#define R_K _p[4]
#define R_P _p[5]
#define V_K _p[6]
#define V_P _p[7]
#define H_K _p[8]
#define H_P _p[9]
#define B_K _p[10]
#define B_P _p[11]
#define v_K _p[12]
#define v_P _p[13]
#define kin_active _p[14]
#define kin_inactive _p[15]
#define phos_active _p[16]
#define phos_inactive _p[17]
#define cyt _p[18]
#define memb _p[19]
#define membp _p[20]
#define mkcc2i _p[21]
#define cai _p[22]
#define ica _p[23]
#define cao _p[24]
#define Dkin_active _p[25]
#define Dkin_inactive _p[26]
#define Dphos_active _p[27]
#define Dphos_inactive _p[28]
#define Dcyt _p[29]
#define Dmemb _p[30]
#define Dmembp _p[31]
#define v _p[32]
#define _g _p[33]
#define _ion_cai	*_ppvar[0]._pval
#define _ion_mkcc2i	*_ppvar[1]._pval
#define _style_mkcc2	*((int*)_ppvar[2]._pvoid)
#define diam	*_ppvar[3]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 extern double celsius;
 /* declaration of user functions */
 static int _hoc_enzymes();
 static int _mechtype;
extern int nrn_get_mechtype();
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range();
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 ret(1.);
}
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 "setdata_KCC2", _hoc_setdata,
 "enzymes_KCC2", _hoc_enzymes,
 0, 0
};
 /* declare global and static user variables */
#define gcal gcal_KCC2
 double gcal = 0.007;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "A_M_KCC2", 0, 1e+09,
 "B_P_KCC2", 0, 1e+09,
 "B_K_KCC2", 0, 1e+09,
 "B_M_KCC2", 0, 1e+09,
 "H_P_KCC2", 0, 1e+09,
 "H_K_KCC2", 0, 1e+09,
 "R_P_KCC2", 0, 1e+09,
 "R_K_KCC2", 0, 1e+09,
 "R_MP_KCC2", 0, 1e+09,
 "R_M_KCC2", 0, 1e+09,
 "V_P_KCC2", 0, 1e+09,
 "V_K_KCC2", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gcal_KCC2", "mho/cm2",
 "A_M_KCC2", "/s",
 "B_M_KCC2", "/s",
 "R_M_KCC2", "/s",
 "R_MP_KCC2", "/s",
 "R_K_KCC2", "mM",
 "R_P_KCC2", "mM",
 "V_K_KCC2", "/s",
 "V_P_KCC2", "/s",
 "H_K_KCC2", "1",
 "H_P_KCC2", "1",
 "B_K_KCC2", "/s",
 "B_P_KCC2", "/s",
 "v_K_KCC2", "/s",
 "v_P_KCC2", "/s",
 0,0
};
 static double cyt0 = 0;
 static double delta_t = 0.01;
 static double kin_inactive0 = 0;
 static double kin_active0 = 0;
 static double membp0 = 0;
 static double memb0 = 0;
 static double phos_inactive0 = 0;
 static double phos_active0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "gcal_KCC2", &gcal_KCC2,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[4]._i
 static _ode_synonym();
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"KCC2",
 "A_M_KCC2",
 "B_M_KCC2",
 "R_M_KCC2",
 "R_MP_KCC2",
 "R_K_KCC2",
 "R_P_KCC2",
 "V_K_KCC2",
 "V_P_KCC2",
 "H_K_KCC2",
 "H_P_KCC2",
 "B_K_KCC2",
 "B_P_KCC2",
 0,
 "v_K_KCC2",
 "v_P_KCC2",
 0,
 "kin_active_KCC2",
 "kin_inactive_KCC2",
 "phos_active_KCC2",
 "phos_inactive_KCC2",
 "cyt_KCC2",
 "memb_KCC2",
 "membp_KCC2",
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _ca_sym;
 static Symbol* _mkcc2_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 34, _prop);
 	/*initialize range parameters*/
 	A_M = 0.2533;
 	B_M = 1.4776;
 	R_M = 1;
 	R_MP = 0.0646;
 	R_K = 0.00237;
 	R_P = 0.0007943;
 	V_K = 390;
 	V_P = 48.925;
 	H_K = 1.5;
 	H_P = 2.9;
 	B_K = 32.1;
 	B_P = 10;
 	_prop->param = _p;
 	_prop->param_size = 34;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 5, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[3]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_ca_sym);
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[0]._pval = &prop_ion->param[1]; /* cai */
 prop_ion = need_memb(_mkcc2_sym);
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 0);
 	_ppvar[1]._pval = &prop_ion->param[1]; /* mkcc2i */
 	_ppvar[2]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for mkcc2 */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 _KCC2_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("ca", -10000.);
 	ion_reg("mkcc2", 1.0);
 	_morphology_sym = hoc_lookup("morphology");
 	_ca_sym = hoc_lookup("ca_ion");
 	_mkcc2_sym = hoc_lookup("mkcc2_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 5);
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_synonym(_mechtype, _ode_synonym);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 KCC2 /home/annik/Dropbox/msc/SciNet/2017/SCM/x86_64/KCC2.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double F = 96485.3;
 static double R = 8.31342;
 static double PI = 3.14159;
static int _reset;
static char *modelname = "Model of KCC2 regulation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static enzymes();
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[5], _dlist1[5];
 static int states();
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   enzymes ( _threadargscomma_ cai ) ;
   Dcyt = ( 1e-3 ) * ( B_M * memb - A_M * cyt ) ;
   Dmemb = ( 1e-3 ) * ( A_M * cyt - ( B_M + R_MP * kin_active ) * memb + R_M * phos_active * membp ) ;
   Dmembp = ( 1e-3 ) * ( - R_M * phos_active * membp + R_MP * kin_active * memb ) ;
   kin_inactive = 1.0 - kin_active ;
   phos_inactive = 1.0 - phos_active ;
   Dkin_active = ( 1e-3 ) * ( kin_inactive * v_K - B_K * kin_active ) ;
   Dphos_active = ( 1e-3 ) * ( phos_inactive * v_P - B_P * phos_active ) ;
   if ( memb + membp > 0.0 ) {
     mkcc2i = ( memb + membp ) * 1.0 ;
     }
   else {
     mkcc2i = 0.0 ;
     }
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 enzymes ( _threadargscomma_ cai ) ;
 Dcyt = Dcyt  / (1. - dt*( (( 1e-3 ))*(( ( - (A_M)*(1.0) ) )) )) ;
 Dmemb = Dmemb  / (1. - dt*( (( 1e-3 ))*(( ( - (( B_M + R_MP * kin_active ))*(1.0) ) )) )) ;
 Dmembp = Dmembp  / (1. - dt*( (( 1e-3 ))*(( (- R_M * phos_active)*(1.0) )) )) ;
 kin_inactive = 1.0 - kin_active ;
 phos_inactive = 1.0 - phos_active ;
 Dkin_active = Dkin_active  / (1. - dt*( (( 1e-3 ))*(( ( - (B_K)*(1.0) ) )) )) ;
 Dphos_active = Dphos_active  / (1. - dt*( (( 1e-3 ))*(( ( - (B_P)*(1.0) ) )) )) ;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
   enzymes ( _threadargscomma_ cai ) ;
    cyt = cyt + (1. - exp(dt*((( 1e-3 ))*(( ( - (A_M)*(1.0) ) )))))*(- ( (( 1e-3 ))*(( (B_M)*(memb) )) ) / ( (( 1e-3 ))*(( ( - (A_M)*(1.0)) )) ) - cyt) ;
    memb = memb + (1. - exp(dt*((( 1e-3 ))*(( ( - (( B_M + R_MP * kin_active ))*(1.0) ) )))))*(- ( (( 1e-3 ))*(( (A_M)*(cyt) + ((R_M)*(phos_active))*(membp) )) ) / ( (( 1e-3 ))*(( ( - (( B_M + (R_MP)*(kin_active) ))*(1.0)) )) ) - memb) ;
    membp = membp + (1. - exp(dt*((( 1e-3 ))*(( (- R_M * phos_active)*(1.0) )))))*(- ( (( 1e-3 ))*(( ((R_MP)*(kin_active))*(memb) )) ) / ( (( 1e-3 ))*(( ((- R_M)*(phos_active))*(1.0) )) ) - membp) ;
   kin_inactive = 1.0 - kin_active ;
   phos_inactive = 1.0 - phos_active ;
    kin_active = kin_active + (1. - exp(dt*((( 1e-3 ))*(( ( - (B_K)*(1.0) ) )))))*(- ( (( 1e-3 ))*(( (kin_inactive)*(v_K) )) ) / ( (( 1e-3 ))*(( ( - (B_K)*(1.0)) )) ) - kin_active) ;
    phos_active = phos_active + (1. - exp(dt*((( 1e-3 ))*(( ( - (B_P)*(1.0) ) )))))*(- ( (( 1e-3 ))*(( (phos_inactive)*(v_P) )) ) / ( (( 1e-3 ))*(( ( - (B_P)*(1.0)) )) ) - phos_active) ;
   if ( memb + membp > 0.0 ) {
     mkcc2i = ( memb + membp ) * 1.0 ;
     }
   else {
     mkcc2i = 0.0 ;
     }
   }
  return 0;
}
 
static int  enzymes ( _p, _ppvar, _thread, _nt, _lCaint ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lCaint ;
 {
   v_K = ( V_K * ( pow( ( _lCaint / 1.0 ) , H_K ) ) ) / ( pow( ( R_K / 1.0 ) , H_K ) + pow( ( _lCaint / 1.0 ) , H_K ) ) ;
   v_P = ( V_P * ( pow( ( _lCaint / 1.0 ) , H_P ) ) ) / ( pow( ( R_P / 1.0 ) , H_P ) + pow( ( _lCaint / 1.0 ) , H_P ) ) ;
    return 0; }
 
static int _hoc_enzymes() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 enzymes ( _p, _ppvar, _thread, _nt, *getarg(1) ) ;
 ret(_r);
}
 
static int _ode_count(_type) int _type;{ return 5;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  mkcc2i = _ion_mkcc2i;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  _ion_mkcc2i = mkcc2i;
 }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 5; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 static _ode_synonym(_cnt, _pp, _ppd) int _cnt; double** _pp; Datum** _ppd; { 
	double* _p; Datum* _ppvar;
 	int _i; 
	for (_i=0; _i < _cnt; ++_i) {_p = _pp[_i]; _ppvar = _ppd[_i];
 _ion_mkcc2i =  ( memb + membp ) * 1.0 ;
 }}
 
static int _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  cai = _ion_cai;
  mkcc2i = _ion_mkcc2i;
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_ca_sym, _ppvar, 0, 1);
   nrn_update_ion_pointer(_mkcc2_sym, _ppvar, 1, 1);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  cyt = cyt0;
  kin_inactive = kin_inactive0;
  kin_active = kin_active0;
  membp = membp0;
  memb = memb0;
  phos_inactive = phos_inactive0;
  phos_active = phos_active0;
 {
   kin_active = 0.1050423664 ;
   kin_inactive = 0.8949576336 ;
   phos_active = 0.0222547827 ;
   phos_inactive = 0.9777452173 ;
   cyt = 0.8000684487 ;
   memb = 0.1371530442 ;
   membp = 0.0627785071 ;
   }
 
}
}

static void nrn_init(_NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  cai = _ion_cai;
  mkcc2i = _ion_mkcc2i;
 initmodel(_p, _ppvar, _thread, _nt);
  _ion_mkcc2i = mkcc2i;
  nrn_wrote_conc(_mkcc2_sym, (&(_ion_mkcc2i)) - 1, _style_mkcc2);
}}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{
} return _current;
}

static void nrn_cur(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 
}}

static void nrn_jacob(_NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}}

static void nrn_state(_NrnThread* _nt, _Memb_list* _ml, int _type) {
 double _break, _save;
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 _break = t + .5*dt; _save = t;
 v=_v;
{
  cai = _ion_cai;
  mkcc2i = _ion_mkcc2i;
 { {
 for (; t < _break; t += dt) {
   states(_p, _ppvar, _thread, _nt);
  
}}
 t = _save;
 } {
   }
  _ion_mkcc2i = mkcc2i;
}}

}

static terminal(){}

static _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(cyt) - _p;  _dlist1[0] = &(Dcyt) - _p;
 _slist1[1] = &(memb) - _p;  _dlist1[1] = &(Dmemb) - _p;
 _slist1[2] = &(membp) - _p;  _dlist1[2] = &(Dmembp) - _p;
 _slist1[3] = &(kin_active) - _p;  _dlist1[3] = &(Dkin_active) - _p;
 _slist1[4] = &(phos_active) - _p;  _dlist1[4] = &(Dphos_active) - _p;
_first = 0;
}
