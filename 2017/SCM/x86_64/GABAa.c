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
#define gmax _p[0]
#define g _p[1]
#define trans_pres _p[2]
#define nevents _p[3]
#define ron _p[4]
#define roff _p[5]
#define rinf _p[6]
#define rtau _p[7]
#define rdelta _p[8]
#define icl _p[9]
#define ecl _p[10]
#define ihco3 _p[11]
#define ehco3 _p[12]
#define Dron _p[13]
#define Droff _p[14]
#define v _p[15]
#define _g _p[16]
#define _tsav _p[17]
#define _nd_area  *_ppvar[0]._pval
#define _ion_ecl	*_ppvar[2]._pval
#define _ion_icl	*_ppvar[3]._pval
#define _ion_dicldv	*_ppvar[4]._pval
#define _ion_ehco3	*_ppvar[5]._pval
#define _ion_ihco3	*_ppvar[6]._pval
#define _ion_dihco3dv	*_ppvar[7]._pval
 
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
 /* declaration of user functions */
 static int _mechtype;
extern int nrn_get_mechtype();
 extern Prop* nrn_point_prop_;
 static int _pointtype;
 static void* _hoc_create_pnt(_ho) Object* _ho; { void* create_point_process();
 return create_point_process(_pointtype, _ho);
}
 static void _hoc_destroy_pnt();
 static double _hoc_loc_pnt(_vptr) void* _vptr; {double loc_point_process();
 return loc_point_process(_pointtype, _vptr);
}
 static double _hoc_has_loc(_vptr) void* _vptr; {double has_loc_point();
 return has_loc_point(_vptr);
}
 static double _hoc_get_loc_pnt(_vptr)void* _vptr; {
 double get_loc_point_process(); return (get_loc_point_process(_vptr));
}
 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static _hoc_setdata(_vptr) void* _vptr; { Prop* _prop;
 _prop = ((Point_process*)_vptr)->_prop;
   _setdata(_prop);
 }
 /* connect user functions to hoc names */
 static IntFunc hoc_intfunc[] = {
 0,0
};
 static struct Member_func {
	char* _name; double (*_member)();} _member_func[] = {
 "loc", _hoc_loc_pnt,
 "has_loc", _hoc_has_loc,
 "get_loc", _hoc_get_loc_pnt,
 0, 0
};
 /* declare global and static user variables */
#define C C_GABAa
 double C = 1;
#define D D_GABAa
 double D = 1;
#define alpha alpha_GABAa
 double alpha = 5;
#define beta beta_GABAa
 double beta = 0.18;
#define clprm clprm_GABAa
 double clprm = 0.8;
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "C_GABAa", "mM",
 "D_GABAa", "ms",
 "alpha_GABAa", "/ms",
 "beta_GABAa", "/ms",
 "gmax", "uS",
 "g", "uS",
 0,0
};
 static double delta_t = 0.01;
 static double roff0 = 0;
 static double ron0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 "clprm_GABAa", &clprm_GABAa,
 "C_GABAa", &C_GABAa,
 "D_GABAa", &D_GABAa,
 "alpha_GABAa", &alpha_GABAa,
 "beta_GABAa", &beta_GABAa,
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(), nrn_init(), nrn_state();
 static void nrn_cur(), nrn_jacob();
 static void _hoc_destroy_pnt(_vptr) void* _vptr; {
   destroy_point_process(_vptr);
}
 
static int _ode_count(), _ode_map(), _ode_spec(), _ode_matsol();
 
#define _cvode_ieq _ppvar[9]._i
 /* connect range variables in _p that hoc is supposed to know about */
 static char *_mechanism[] = {
 "6.2.0",
"GABAa",
 "gmax",
 0,
 "g",
 "trans_pres",
 "nevents",
 0,
 "ron",
 "roff",
 0,
 0};
 static Symbol* _cl_sym;
 static Symbol* _hco3_sym;
 
static void nrn_alloc(_prop)
	Prop *_prop;
{
	Prop *prop_ion, *need_memb();
	double *_p; Datum *_ppvar;
  if (nrn_point_prop_) {
	_prop->_alloc_seq = nrn_point_prop_->_alloc_seq;
	_p = nrn_point_prop_->param;
	_ppvar = nrn_point_prop_->dparam;
 }else{
 	_p = nrn_prop_data_alloc(_mechtype, 18, _prop);
 	/*initialize range parameters*/
 	gmax = 0.003;
  }
 	_prop->param = _p;
 	_prop->param_size = 18;
  if (!nrn_point_prop_) {
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 10, _prop);
  }
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_cl_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[2]._pval = &prop_ion->param[0]; /* ecl */
 	_ppvar[3]._pval = &prop_ion->param[3]; /* icl */
 	_ppvar[4]._pval = &prop_ion->param[4]; /* _ion_dicldv */
 prop_ion = need_memb(_hco3_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[5]._pval = &prop_ion->param[0]; /* ehco3 */
 	_ppvar[6]._pval = &prop_ion->param[3]; /* ihco3 */
 	_ppvar[7]._pval = &prop_ion->param[4]; /* _ion_dihco3dv */
 
}
 static _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 
#define _tqitem &(_ppvar[8]._pvoid)
 static _net_receive();
 typedef (*_Pfrv)();
 extern _Pfrv* pnt_receive;
 extern short* pnt_receive_size;
 static void _update_ion_pointer(Datum*);
 _GABAa_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("cl", -1.0);
 	ion_reg("hco3", -1.0);
 	_cl_sym = hoc_lookup("cl_ion");
 	_hco3_sym = hoc_lookup("hco3_ion");
 	_pointtype = point_register_mech(_mechanism,
	 nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init,
	 hoc_nrnpointerindex,
	 _hoc_create_pnt, _hoc_destroy_pnt, _member_func,
	 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
  hoc_register_dparam_size(_mechtype, 10);
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 pnt_receive[_mechtype] = _net_receive;
 pnt_receive_size[_mechtype] = 1;
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 GABAa /home/annik/Dropbox/msc/SciNet/2017/SCM/x86_64/GABAa.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "Simplified ionic model of GABA-A synapse, with saturation";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static _modl_cleanup(){ _match_recurse=1;}
 
static int _ode_spec1(), _ode_matsol1();
 static int _slist1[2], _dlist1[2];
 static int release();
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {int _reset = 0; {
   Dron = ( trans_pres * rinf - ron ) / rtau ;
   Droff = - beta * roff ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
 Dron = Dron  / (1. - dt*( ( ( ( - 1.0 ) ) ) / rtau )) ;
 Droff = Droff  / (1. - dt*( (- beta)*(1.0) )) ;
}
 /*END CVODE*/
 static int release (double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) { {
    ron = ron + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / rtau)))*(- ( ( ( (trans_pres)*(rinf) ) ) / rtau ) / ( ( ( ( - 1.0) ) ) / rtau ) - ron) ;
    roff = roff + (1. - exp(dt*((- beta)*(1.0))))*(- ( 0.0 ) / ( (- beta)*(1.0) ) - roff) ;
   }
  return 0;
}
 
static _net_receive (_pnt, _args, _lflag) Point_process* _pnt; double* _args; double _lflag; 
{  double* _p; Datum* _ppvar; Datum* _thread; _NrnThread* _nt;
   _thread = (Datum*)0; _nt = (_NrnThread*)_pnt->_vnt;   _p = _pnt->_prop->param; _ppvar = _pnt->_prop->dparam;
  if (_tsav > t){ extern char* hoc_object_name(); hoc_execerror(hoc_object_name(_pnt->ob), ":Event arrived out of order. Must call ParallelContext.set_maxstep AFTER assigning minimum NetCon.delay");}
 _tsav = t;   if (_lflag == 1. ) {*(_tqitem) = 0;}
 {
   if ( _lflag  == 0.0 ) {
     nevents = nevents + 1.0 ;
     if ( trans_pres  == 0.0 ) {
       ron = roff ;
       roff = 0.0 ;
       }
     trans_pres = 1.0 ;
     net_send ( _tqitem, _args, _pnt, t +  D , 1.0 ) ;
     }
   else {
     nevents = nevents - 1.0 ;
     if ( nevents  == 0.0 ) {
       trans_pres = 0.0 ;
       ron = 0.0 ;
       roff = rdelta ;
       }
     }
   } }
 
static int _ode_count(_type) int _type;{ return 2;}
 
static int _ode_spec(_NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ecl = _ion_ecl;
  ehco3 = _ion_ehco3;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
   }}
 
static int _ode_map(_ieq, _pv, _pvdot, _pp, _ppd, _atol, _type) int _ieq, _type; double** _pv, **_pvdot, *_pp, *_atol; Datum* _ppd; { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 2; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
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
  ecl = _ion_ecl;
  ehco3 = _ion_ehco3;
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_cl_sym, _ppvar, 2, 0);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 3, 3);
   nrn_update_ion_pointer(_cl_sym, _ppvar, 4, 4);
   nrn_update_ion_pointer(_hco3_sym, _ppvar, 5, 0);
   nrn_update_ion_pointer(_hco3_sym, _ppvar, 6, 3);
   nrn_update_ion_pointer(_hco3_sym, _ppvar, 7, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt) {
  int _i; double _save;{
  roff = roff0;
  ron = ron0;
 {
   ron = 0.0 ;
   roff = 0.0 ;
   rinf = C * alpha / ( C * alpha + beta ) ;
   rtau = 1.0 / ( ( alpha * C ) + beta ) ;
   rdelta = rinf * ( 1.0 - exp ( - D / rtau ) ) ;
   trans_pres = 0.0 ;
   nevents = 0.0 ;
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
 _tsav = -1e20;
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
  ecl = _ion_ecl;
  ehco3 = _ion_ehco3;
 initmodel(_p, _ppvar, _thread, _nt);
  }}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, _NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   g = gmax * ( ron + roff ) ;
   icl = g * clprm * ( v - ecl ) ;
   ihco3 = g * ( 1.0 - clprm ) * ( v - ehco3 ) ;
   }
 _current += icl;
 _current += ihco3;

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
  ecl = _ion_ecl;
  ehco3 = _ion_ehco3;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dihco3;
 double _dicl;
  _dicl = icl;
  _dihco3 = ihco3;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dicldv += (_dicl - icl)/.001 * 1.e2/ (_nd_area);
  _ion_dihco3dv += (_dihco3 - ihco3)/.001 * 1.e2/ (_nd_area);
 	}
 _g = (_g - _rhs)/.001;
  _ion_icl += icl * 1.e2/ (_nd_area);
  _ion_ihco3 += ihco3 * 1.e2/ (_nd_area);
 _g *=  1.e2/(_nd_area);
 _rhs *= 1.e2/(_nd_area);
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
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
  ecl = _ion_ecl;
  ehco3 = _ion_ehco3;
 { {
 for (; t < _break; t += dt) {
   release(_p, _ppvar, _thread, _nt);
  
}}
 t = _save;
 }  }}

}

static terminal(){}

static _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = &(ron) - _p;  _dlist1[0] = &(Dron) - _p;
 _slist1[1] = &(roff) - _p;  _dlist1[1] = &(Droff) - _p;
_first = 0;
}
