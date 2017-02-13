/* Created by Language version: 6.2.0 */
/* VECTORIZED */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scoplib.h"
#undef PI
 static void _difusfunc();
 
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
#define Pa _p[0]
#define axD _p[1]
#define itonic _p[2]
#define D _p[3]
#define v_T _p[4]
#define gtonic _p[5]
#define L _p[6]
#define icl _p[7]
#define ik _p[8]
#define clo _p[9]
#define ko _p[10]
#define ecl _p[11]
#define mkcc2i _p[12]
#define cli _p[13]
#define Dcli _p[14]
#define ki _p[15]
#define Dki _p[16]
#define v _p[17]
#define _g _p[18]
#define _ion_icl	*_ppvar[0]._pval
#define _ion_ecl	*_ppvar[1]._pval
#define _ion_clo	*_ppvar[2]._pval
#define _ion_cli	*_ppvar[3]._pval
#define _style_cl	*((int*)_ppvar[4]._pvoid)
#define _ion_dicldv	*_ppvar[5]._pval
#define _ion_ki	*_ppvar[6]._pval
#define _ion_ko	*_ppvar[7]._pval
#define _ion_dikdv	*_ppvar[8]._pval
#define _ion_mkcc2i	*_ppvar[9]._pval
#define _ion_dimkcc2dv	*_ppvar[10]._pval
#define diam	*_ppvar[11]._pval
 
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
 static int _hoc_tonicgaba();
 static int _hoc_transport_mm();
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
 "setdata_KCC2_Transport", _hoc_setdata,
 "tonicgaba_KCC2_Transport", _hoc_tonicgaba,
 "transport_mm_KCC2_Transport", _hoc_transport_mm,
 0, 0
};
 /* declare global and static user variables */
#define celsius celsius_KCC2_Transport
 double celsius = 0;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 "axD_KCC2_Transport", 0, 1e+09,
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "celsius_KCC2_Transport", "degC",
 "Pa_KCC2_Transport", "mA/mM2/cm2",
 "axD_KCC2_Transport", "um2/ms",
 "itonic_KCC2_Transport", "mA/cm2",
 "v_T_KCC2_Transport", "mM/s",
 "gtonic_KCC2_Transport", "S/cm2",
 0,0
};
 static double cli0 = 0;
 static double delta_t = 0.01;
 static double ki0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "celsius_KCC2_Transport", &celsius_KCC2_Transport,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[12]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"KCC2_Transport",
 "Pa_KCC2_Transport",
 "axD_KCC2_Transport",
 0,
 "itonic_KCC2_Transport",
 "D_KCC2_Transport",
 "v_T_KCC2_Transport",
 "gtonic_KCC2_Transport",
 0,
 0,
 0};
 static Symbol* _morphology_sym;
 static Symbol* _cl_sym;
 static int _type_icl;
 static Symbol* _k_sym;
 static int _type_ik;
 static Symbol* _mkcc2_sym;
 static int _type_imkcc2;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 19, _prop);
 	/*initialize range parameters*/
 	Pa = 9.6485e-05;
 	axD = 1;
 	_prop->param = _p;
 	_prop->param_size = 19;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 13, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_morphology_sym);
 	_ppvar[11]._pval = &prop_ion->param[0]; /* diam */
 prop_ion = need_memb(_cl_sym);
  _type_icl = prop_ion->_type;
 nrn_check_conc_write(_prop, prop_ion, 1);
 nrn_promote(prop_ion, 3, 1);
 	_ppvar[0]._pval = &prop_ion->param[3]; /* icl */
 	_ppvar[1]._pval = &prop_ion->param[0]; /* ecl */
 	_ppvar[2]._pval = &prop_ion->param[2]; /* clo */
 	_ppvar[3]._pval = &prop_ion->param[1]; /* cli */
 	_ppvar[4]._pvoid = (void*)(&(prop_ion->dparam[0]._i)); /* iontype for cl */
 	_ppvar[5]._pval = &prop_ion->param[4]; /* _ion_dicldv */
 prop_ion = need_memb(_k_sym);
  _type_ik = prop_ion->_type;
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[6]._pval = &prop_ion->param[1]; /* ki */
 	_ppvar[7]._pval = &prop_ion->param[2]; /* ko */
 	_ppvar[8]._pval = &prop_ion->param[4]; /* _ion_dikdv */
 prop_ion = need_memb(_mkcc2_sym);
  _type_imkcc2 = prop_ion->_type;
 nrn_promote(prop_ion, 1, 0);
 	_ppvar[9]._pval = &prop_ion->param[1]; /* mkcc2i */
 	_ppvar[10]._pval = &prop_ion->param[4]; /* _ion_dimkcc2dv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _thread_cleanup(Datum*);
 static void _update_ion_pointer(Datum*);
 _KCC2_SA_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("cl", -1.0);
 	ion_reg("k", 1.0);
 	ion_reg("mkcc2", 1.0);
 	_morphology_sym = hoc_lookup("morphology");
 	_cl_sym = hoc_lookup("cl_ion");
 	_k_sym = hoc_lookup("k_ion");
 	_mkcc2_sym = hoc_lookup("mkcc2_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 3);
  _extcall_thread = (Datum*)ecalloc(2, sizeof(Datum));
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 0, _thread_cleanup);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 13);
 	nrn_writes_conc(_mechtype, 0);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_ldifus1(_difusfunc);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 KCC2_Transport /home/annik/Dropbox/msc/SciNet/2017/SCM/x86_64/KCC2_SA.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
 static double F = 96485.3;
 static double R = 8.31342;
 static double PI = 3.14159;
static int _reset;
static char *modelname = "Model of KCC2 transport";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
static tonicgaba();
static transport_mm();
 extern double *_nrn_thread_getelm();
 
#define _MATELM1(_row,_col) *(_nrn_thread_getelm(_so, _row + 1, _col + 1))
 
#define _RHS1(_arg) _rhs[_arg+1]
  
#define _linmat1  1
 static int _spth1 = 1;
 static int _cvspth1 = 0;
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[1], _dlist1[1]; static double *_temp1;
 static int state();
 
static int state (void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt)
 {int _reset=0;
 {
   double b_flux, f_flux, _term; int _i;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<1;_i++){
  	_RHS1(_i) = -_dt1*(_p[_slist1[_i]] - _p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
}  
_RHS1(0) *= ( PI * diam * diam / 4.0) ;
_MATELM1(0, 0) *= ( PI * diam * diam / 4.0);  }
 tonicgaba ( _threadargscomma_ v , ecl ) ;
   transport_mm ( _threadargscomma_ cli , clo , ki , ko , mkcc2i ) ;
   /* COMPARTMENT PI * diam * diam / 4.0 {
     cli }
   */
 /* LONGITUDINAL_DIFFUSION axD * PI * diam * diam / 4.0 {
     cli }
   */
 /* ~ cli < < ( ( 1e4 ) * icl * diam * PI / F - ( 1e4 ) * v_T * PI * diam / F + ( 1e4 ) * itonic * diam * PI / F )*/
 f_flux = b_flux = 0.;
 _RHS1( 0) += (b_flux =   ( ( 1e4 ) * icl * diam * PI / F - ( 1e4 ) * v_T * PI * diam / F + ( 1e4 ) * itonic * diam * PI / F ) );
 /*FLUX*/
    } return _reset;
 }
 
static int  tonicgaba ( _p, _ppvar, _thread, _nt, _lVm , _lEm ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lVm , _lEm ;
 {
   itonic = gtonic * ( _lVm - _lEm ) ;
    return 0; }
 
static int _hoc_tonicgaba() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 tonicgaba ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) ) ;
 ret(_r);
}
 
static int  transport_mm ( _p, _ppvar, _thread, _nt, _lClint , _lClout , _lKint , _lKout , _lMkcc2int ) double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt; 
	double _lClint , _lClout , _lKint , _lKout , _lMkcc2int ;
 {
   v_T = Pa * ( _lKint * _lClint - _lKout * _lClout ) * ( _lMkcc2int ) ;
    return 0; }
 
static int _hoc_transport_mm() {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 transport_mm ( _p, _ppvar, _thread, _nt, *getarg(1) , *getarg(2) , *getarg(3) , *getarg(4) , *getarg(5) ) ;
 ret(_r);
}
 
/*CVODE ode begin*/
 static int _ode_spec1(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
 {int _i; for(_i=0;_i<1;_i++) _p[_dlist1[_i]] = 0.0;}
 tonicgaba ( _threadargscomma_ v , ecl ) ;
 transport_mm ( _threadargscomma_ cli , clo , ki , ko , mkcc2i ) ;
 /* COMPARTMENT PI * diam * diam / 4.0 {
   cli }
 */
 /* LONGITUDINAL_DIFFUSION axD * PI * diam * diam / 4.0 {
   cli }
 */
 /* ~ cli < < ( ( 1e4 ) * icl * diam * PI / F - ( 1e4 ) * v_T * PI * diam / F + ( 1e4 ) * itonic * diam * PI / F )*/
 f_flux = b_flux = 0.;
 Dcli += (b_flux =   ( ( 1e4 ) * icl * diam * PI / F - ( 1e4 ) * v_T * PI * diam / F + ( 1e4 ) * itonic * diam * PI / F ) );
 /*FLUX*/
  _p[_dlist1[0]] /= ( PI * diam * diam / 4.0);
   } return _reset;
 }
 
/*CVODE matsol*/
 static int _ode_matsol1(void* _so, double* _rhs, double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset=0;{
 double b_flux, f_flux, _term; int _i;
   b_flux = f_flux = 0.;
 {int _i; double _dt1 = 1.0/dt;
for(_i=0;_i<1;_i++){
  	_RHS1(_i) = _dt1*(_p[_dlist1[_i]]);
	_MATELM1(_i, _i) = _dt1;
      
}  
_RHS1(0) *= ( PI * diam * diam / 4.0) ;
_MATELM1(0, 0) *= ( PI * diam * diam / 4.0);  }
 tonicgaba ( _threadargscomma_ v , ecl ) ;
 transport_mm ( _threadargscomma_ cli , clo , ki , ko , mkcc2i ) ;
 /* COMPARTMENT PI * diam * diam / 4.0 {
 cli }
 */
 /* LONGITUDINAL_DIFFUSION axD * PI * diam * diam / 4.0 {
 cli }
 */
 /* ~ cli < < ( ( 1e4 ) * icl * diam * PI / F - ( 1e4 ) * v_T * PI * diam / F + ( 1e4 ) * itonic * diam * PI / F )*/
 /*FLUX*/
    } return _reset;
 }
 
/*CVODE end*/
 
static int _ode_count(_type) int _type;{ return 1;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  icl = _ion_icl;
  ecl = _ion_ecl;
  clo = _ion_clo;
  cli = _ion_cli;
  ki = _ion_ki;
  ko = _ion_ko;
  mkcc2i = _ion_mkcc2i;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  _ion_cli = cli;
 }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 	_pv[0] = &(_ion_cli);
 }
 
static int _ode_matsol(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  icl = _ion_icl;
  ecl = _ion_ecl;
  clo = _ion_clo;
  cli = _ion_cli;
  ki = _ion_ki;
  ko = _ion_ko;
  mkcc2i = _ion_mkcc2i;
 _cvode_sparse_thread(&_thread[_cvspth1]._pvoid, 1, _dlist1, _p, _ode_matsol1, _ppvar, _thread, _nt);
 }}
 
static void _thread_cleanup(Datum* _thread) {
   _nrn_destroy_sparseobj_thread(_thread[_cvspth1]._pvoid);
   _nrn_destroy_sparseobj_thread(_thread[_spth1]._pvoid);
 }
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_cl_sym, _ppvar, 0, 3);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 1, 0);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 2, 2);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 3, 1);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 5, 4);
   nrn_update_ion_pointer(_k_sym, _ppvar, 6, 1);
   nrn_update_ion_pointer(_k_sym, _ppvar, 7, 2);
   nrn_update_ion_pointer(_k_sym, _ppvar, 8, 4);
   nrn_update_ion_pointer(_mkcc2_sym, _ppvar, 9, 1);
   nrn_update_ion_pointer(_mkcc2_sym, _ppvar, 10, 4);
 }
 static void* _difspace1;
extern double nrn_nernst_coef();
static double _difcoef1(int _i, double* _p, Datum* _ppvar, double* _pdvol, double* _pdfcdc, Datum* _thread, _NrnThread* _nt) {
   *_pdvol =  PI * diam * diam / 4.0 ;
 if (_i == 0) {
  *_pdfcdc = nrn_nernst_coef(_type_icl)*( ( ( 1e4 ) * _ion_dicldv  * diam * PI / F - ( 1e4 ) * v_T * PI * diam / F + ( 1e4 ) * itonic * diam * PI / F ));
 }else{ *_pdfcdc=0.;}
   return axD * PI * diam * diam / 4.0 ;
}
 static void _difusfunc(_f, _nt) void(*_f)(); _NrnThread* _nt; {int _i;
  _f(_mechtype, _difcoef1, &_difspace1, 0,  -4, 14 , _nt);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
 {
   transport_mm ( _threadargscomma_ cli , clo , ki , ko , mkcc2i ) ;
   itonic = v_T ;
   gtonic = itonic / ( v - ecl ) ;
   D = 0.0 ;
   v_T = 0.0 ;
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
  icl = _ion_icl;
  ecl = _ion_ecl;
  clo = _ion_clo;
  cli = _ion_cli;
  ki = _ion_ki;
  ko = _ion_ko;
  mkcc2i = _ion_mkcc2i;
 initmodel(_p, _ppvar, _thread, _nt);
  _ion_cli = cli;
  nrn_wrote_conc(_cl_sym, (&(_ion_cli)) - 1, _style_cl);
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
  icl = _ion_icl;
  ecl = _ion_ecl;
  clo = _ion_clo;
  cli = _ion_cli;
  ki = _ion_ki;
  ko = _ion_ko;
  mkcc2i = _ion_mkcc2i;
 { {
 for (; t < _break; t += dt) {
  sparse_thread(&_thread[_spth1]._pvoid, 1, _slist1, _dlist1, _p, &t, dt, state, _linmat1, _ppvar, _thread, _nt);
  
}}
 t = _save;
 } {
   }
  _ion_cli = cli;
}}

}

static terminal(){}

static _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(cli) - _p;  _dlist1[0] = &(Dcli) - _p;
_first = 0;
}
